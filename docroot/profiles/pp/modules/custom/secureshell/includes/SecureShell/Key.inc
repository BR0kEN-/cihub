<?php
/**
 * @file
 * SSH key entity.
 */

namespace SecureShell;

/**
 * Class Key.
 *
 * @package SecureShell
 */
class Key extends \Entity {

  /**
   * The type of entity.
   */
  const ENTITY_TYPE = 'ssh_key';
  /**
   * Identifier of a public key.
   */
  const KEY_PUBLIC = 'public';
  /**
   * Identifier of a private key.
   */
  const KEY_PRIVATE = 'private';

  /**
   * Internal identifier of a key.
   *
   * @var int
   */
  public $id = 0;
  /**
   * An ID of key owner.
   *
   * @var int
   */
  public $uid = 0;
  /**
   * Key type: public or private.
   *
   * @var int
   */
  public $type = 0;
  /**
   * Machine name of a key.
   *
   * @var string
   */
  public $name = '';
  /**
   * Label of a key.
   *
   * @var string
   */
  public $label = '';
  /**
   * An associative array where keys are one of "static::KEY_*" constants.
   *
   * @var string[]
   */
  private $keys = [];
  /**
   * An array where keys are stream wrapper schemas and values - paths to file.
   *
   * @var string[]
   */
  private $path = [
    'private' => '',
    'temporary' => '',
  ];
  /**
   * An object of a user.
   *
   * @var \stdClass
   */
  private $account;
  /**
   * Are internal properties were initialized.
   *
   * @var bool
   */
  private $initialized = FALSE;

  /**
   * {@inheritdoc}
   */
  public function __construct(array $values = []) {
    parent::__construct($values, static::ENTITY_TYPE);

    $this->initialize()
      ->cleanTemporary();
  }

  /**
   * Return path of private or public key when casting a string type.
   *
   * @return string
   *   Path of private or public key.
   */
  public function __toString() {
    return $this->getPrivatePath() ?: $this->getPublicPath();
  }

  /**
   * {@inheritdoc}
   */
  public function save() {
    // Need to reinitialize all data to save correct values.
    $this->initialized = FALSE;
    $this->initialize();

    // Generate public key if it is missed and private is set.
    if (empty($this->keys[static::KEY_PUBLIC]) && !empty($this->keys[static::KEY_PRIVATE])) {
      // Get path to a file on a private file system.
      $filename = $this->getPrivatePath();

      // Save the file and generate a public key.
      if (file_put_contents($filename, $this->keys[static::KEY_PRIVATE])) {
        $this->keys[static::KEY_PUBLIC] = shell_exec("ssh-keygen -y -q -f $filename");
        // No need to additionally save a private key because we've made
        // this couple lines before.
        unset($this->keys[static::KEY_PRIVATE]);
      }
    }

    // Save/delete keys.
    foreach ($this->keys as $type => $content) {
      $filename = $this->getFilename($type, FALSE);

      // Allow remove a key where passed no content.
      if (empty($content)) {
        file_exists($filename) && unlink($filename);
      }
      else {
        file_put_contents($filename, $content);
      }
    }

    return parent::save();
  }

  /**
   * Set an object of a user.
   *
   * @param \stdClass $account
   *   An object of a user.
   */
  public function setUser(\stdClass $account) {
    // Our entity is on the path with "%user" wildcard and this method
    // also will be called automatically by "entity_wildcard_entity_form()"
    // function.
    $this->uid = $account->uid;
    $this->account = $account;
  }

  /**
   * Get value of a public key.
   *
   * @return string
   *   Value of a public key.
   */
  public function getPublic() {
    return $this->getKey(static::KEY_PUBLIC);
  }

  /**
   * Get path of public key file.
   *
   * @return string
   *   Path of public key file.
   */
  public function getPublicPath() {
    return $this->getFilename(static::KEY_PUBLIC, FALSE);
  }

  /**
   * Set new value of a public key.
   *
   * @param string $content
   *   Value of a public key.
   *
   * @return bool
   *   A state of setting.
   */
  public function setPublic($content) {
    return $this->setKey(static::KEY_PUBLIC, $content);
  }

  /**
   * Get value of a private key.
   *
   * @return string
   *   Value of a private key.
   */
  public function getPrivate() {
    return $this->getKey(static::KEY_PRIVATE);
  }

  /**
   * Get path of private key file.
   *
   * @return string
   *   Path of private key file.
   */
  public function getPrivatePath() {
    return $this->getFilename(static::KEY_PRIVATE, FALSE);
  }

  /**
   * Set new value of a private key.
   *
   * @param string $content
   *   Value of a private key.
   *
   * @return bool
   *   A state of setting.
   */
  public function setPrivate($content) {
    return $this->setKey(static::KEY_PRIVATE, $content);
  }

  /**
   * Generate temporary key pair.
   *
   * @return $this
   *   An instance of the object.
   */
  public function generatePair() {
    $this->initialize();
    // Generate new key pair.
    shell_exec("ssh-keygen -t rsa -b 4096 -C {$this->account->mail} -N '' -q -f " . $this->getFilename(static::KEY_PRIVATE));
    // When keys were generated then their values will be used as default.
    $this->keys = $this->cleanTemporary(TRUE);

    return $this;
  }

  /**
   * Set values from a $form_state['values'].
   *
   * @param array $values
   *   An associative array where keys should be named as public properties
   *   of this object. Additional subarray could be located under "keys" key
   *   and should contain value of one of "static::KEY_*" constants.
   *
   * @return $this
   *   An instance of the object.
   */
  public function setValues(array $values) {
    // Ensure that all necessary properties were initialized.
    $this->initialize();

    // Import values for all public properties.
    foreach ((new \ReflectionClass(static::class))->getProperties(\ReflectionProperty::IS_PUBLIC) as $property) {
      if (isset($values[$property->name])) {
        $this->{$property->name} = $values[$property->name];
      }
    }

    // If "$values" has a "keys" and it is an array then try to set key pair.
    if (!empty($values['keys']) && is_array($values['keys'])) {
      foreach ([static::KEY_PUBLIC, static::KEY_PRIVATE] as $key_type) {
        if (array_key_exists($key_type, $values['keys'])) {
          $this->setKey($key_type, $values['keys'][$key_type]);
        }
      }
    }

    return $this;
  }

  /**
   * Initialize an object.
   *
   * @return $this
   *   An instance of the object.
   */
  protected function initialize() {
    if (!$this->initialized) {
      $filename = empty($this->name) || empty($this->uid) ? session_id() : "$this->uid-$this->name";

      if (empty($this->account->uid)) {
        $this->account = user_load($this->uid);
        $this->initialized = (bool) $this->account;
      }

      foreach ($this->path as $scheme => $value) {
        /* @var \DrupalLocalStreamWrapper $stream_wrapper */
        $stream_wrapper = file_stream_wrapper_get_instance_by_scheme($scheme);

        if (FALSE !== $stream_wrapper) {
          // Detect real path to directory.
          $this->path[$scheme] = $stream_wrapper->realpath() . '/ssh_keys';

          // Create an empty directory if it is not exists.
          if (!file_exists($this->path[$scheme])) {
            $this->initialized &= file_prepare_directory($this->path[$scheme], FILE_CREATE_DIRECTORY | FILE_MODIFY_PERMISSIONS);
          }

          $this->path[$scheme] .= "/$filename";
        }
        else {
          throw new \RuntimeException(t('You are not configured a "@scheme" file system or it is unavailable.', [
            '@scheme' => $scheme,
          ]));
        }
      }

      $this->initialized = (bool) $this->initialized;
    }

    return $this;
  }

  /**
   * Get path to key file.
   *
   * @param string $type
   *   One of "static::KEY_*" constants.
   * @param bool $temporary
   *   Get path to temporary file or stored in a private FS.
   *
   * @return string
   *   Path to file.
   */
  protected function getFilename($type, $temporary = TRUE) {
    $filename = $this->path[$temporary ? 'temporary' : 'private'];

    if (static::KEY_PUBLIC === $type) {
      $filename .= '.pub';
    }

    return $filename;
  }

  /**
   * Get content of a file with a key.
   *
   * @param string $type
   *   One of "static::KEY_*" constants.
   *
   * @return string
   *   File content or an empty string if it is not exists.
   */
  protected function getKey($type) {
    if (empty($this->keys[$type])) {
      $filename = $this->getFilename($type, FALSE);
      $this->keys[$type] = file_exists($filename) ? file_get_contents($filename) : '';
    }

    return $this->keys[$type];
  }

  /**
   * Save content to a key file.
   *
   * @param string $type
   *   One of "static::KEY_*" constants.
   * @param string $content
   *   SSH key value.
   *
   * @return bool
   *   A state of saving/removing.
   */
  protected function setKey($type, $content) {
    $this->keys[$type] = $content;
    $this->type = empty($this->keys[static::KEY_PRIVATE]) ? static::KEY_PUBLIC : static::KEY_PRIVATE;
  }

  /**
   * Clean temporary data.
   *
   * @param bool $read
   *   Read data from temporary files.
   *
   * @return string[]
   *   An associative array where keys are one of "static::KEY_*" constants.
   */
  protected function cleanTemporary($read = FALSE) {
    $data = [];

    foreach ([static::KEY_PUBLIC, static::KEY_PRIVATE] as $type) {
      // Get the name of temporary file with a key.
      $filename = $this->getFilename($type);
      // Set empty value.
      $data[$type] = '';

      // Remove file if it exists, but read it before.
      if (file_exists($filename)) {
        if ($read) {
          $data[$type] = file_get_contents($filename);
        }

        drupal_unlink($filename);
      }
    }

    return $data;
  }

}
