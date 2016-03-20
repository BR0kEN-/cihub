<?php
/**
 * @file
 * SSH Key UI Controller.
 */

namespace SecureShell\Key\UI;

use Entity\Wildcard\UIController;

/**
 * Class EntityController.
 *
 * @package SecureShell\Key\UI
 */
class EntityController extends UIController {

  /**
   * {@inheritdoc}
   */
  public function hookMenu(array &$items) {
    $items[$this->path]['type'] = MENU_LOCAL_TASK;
    $items["$this->path/add"]['title'] = t('Add');
    unset($items["$this->path/add"]['title callback']);
  }

  /**
   * {@inheritdoc}
   */
  public static function access($operation, $entity_type, array $wildcards) {
    global $user;

    if (1 == $user->uid) {
      return TRUE;
    }

    /* @var \stdClass $account */
    /* @var \SecureShell\Key $key */
    list($account, $key) = $wildcards;

    if (NULL === $account) {
      $account = $user;
    }

    $access = $user->uid == $account->uid | user_access('administer ssh keys');

    if (isset($key)) {
      $access &= $key->uid == $account->uid | $key->uid == $user->uid;
    }

    return $access & user_access('manage own ssh keys', $account);
  }

  /**
   * {@inheritdoc}
   */
  public function overviewForm($form, &$form_state) {
    list($entity_type, $account) = $form_state['build_info']['args'];

    // Filter loading results by a user ID.
    $form['table'] = $this->overviewTable([
      'uid' => $account->uid,
    ]);

    $form['pager'] = [
      '#theme' => 'pager',
    ];

    return $form;
  }

  /**
   * Implements entityForm().
   *
   * @param array $form
   *   Form definition
   * @param array $form_state
   *   A state of form.
   * @param \stdClass $account
   *   An object of a user.
   * @param \SecureShell\Key $key
   *   SSH key object.
   * @param string $operation
   *   Operation over the entity.
   * @param string $entity_type
   *   The type of entity.
   */
  public static function entityForm(
    array &$form, array &$form_state, \stdClass $account, \SecureShell\Key $key, $operation, $entity_type
  ) {
    $disabled = !empty($form_state['rebuild']);

    $form['note'] = [
      // @see theme_item_list()
      '#theme' => 'item_list',
      '#title' => t('Make sure that you have met all these notes'),
      '#items' => [
        t('SSH key MUST not be protected with a password phrase!'),
        t('If you will generate new key pair then do not forget to add a public key to necessary places.'),
      ],
    ];

    $form['generate'] = [
      '#ajax' => 'generateKeyPair',
      '#type' => 'button',
      '#value' => t('Generate'),
      '#limit_validation_errors' => [],
    ];

    $form['label'] = [
      '#type' => 'textfield',
      '#title' => t('Label'),
      '#required' => TRUE,
      '#default_value' => $key->label,
    ];

    $form['name'] = [
      '#type' => 'machine_name',
      '#title' => t('Machine name'),
      '#disabled' => 'add' !== $operation,
      '#default_value' => $key->name,
      '#machine_name' => [
        'exists' => 'secureshell_key_machine_name_exists',
        'source' => ['label'],
      ],
    ];

    $form['keys'] = [
      '#tree' => TRUE,
      '#disabled' => $disabled,
    ];

    $form['keys'][$key::KEY_PUBLIC] = [
      '#type' => 'textarea',
      '#rows' => 5,
      '#title' => t('Public'),
      '#default_value' => $key->getPublic(),
    ];

    $form['keys'][$key::KEY_PRIVATE] = [
      '#type' => 'textarea',
      '#rows' => 5,
      '#title' => t('Private'),
      '#default_value' => $key->getPrivate(),
    ];

    $form['uid'] = [
      '#type' => 'hidden',
      '#value' => $account->uid,
    ];

    $form['actions'] = [
      '#type' => 'actions',
    ];

    $form['actions']['submit'] = [
      '#type' => 'submit',
      '#value' => t('Save'),
    ];

    $form['actions']['cancel'] = [
      '#type' => 'link',
      '#href' => secureshell_key_overview_page_uri($account),
      '#title' => t('Cancel'),
    ];
  }

  /**
   * Implements entityFormValidate().
   *
   * {@inheritdoc}
   */
  public static function entityFormValidate(
    array &$form, array &$form_state, \stdClass $account, \SecureShell\Key $key, $operation, $entity_type
  ) {
    if (empty(array_filter($form_state['values']['keys']))) {
      form_error($form['keys'][$key::KEY_PUBLIC], t('You need to set at least public key.'));
    }
  }

  /**
   * Implements entityFormSubmit().
   *
   * {@inheritdoc}
   */
  public static function entityFormSubmit(
    array $form, array &$form_state, \stdClass $account, \SecureShell\Key $key, $operation, $entity_type
  ) {
    $key->setValues($form_state['values'])->save();

    // @todo When we face with translation problems you can come to me.
    // I'm not sure that this is a good idea.
    drupal_set_message(t('!action %entity %label.', [
      // E.g.: edited, added, cloned, reverted, deleted.
      '!action' => ucfirst($operation) . (strrpos($operation, 'e') === 0 ? 'ed' : 'd'),
      '%entity' => $key->entityInfo()['label'],
      '%label' => $key->label,
    ]));

    $form_state['redirect'] = $form['actions']['cancel']['#href'];
  }

  /**
   * Implements entityFormAjaxHandler().
   *
   * {@inheritdoc}
   *
   * @see entity_wildcard_entity_form_ajax()
   */
  public static function generateKeyPair(
    array &$form, array &$form_state, \stdClass $account, \SecureShell\Key $key, $operation, $entity_type, array &$commands, array $element
  ) {
    // Generate new key pair.
    $key->generatePair();
    // Set label for this key to email of current user.
    $form_state['input']['label'] = $account->mail;
    // Rebuild the form to apply changes.
    $form_state['rebuild'] = TRUE;
  }

}
