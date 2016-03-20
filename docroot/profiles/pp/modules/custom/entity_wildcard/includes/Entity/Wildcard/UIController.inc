<?php
/**
 * @file
 * Entity Wildcard UI Controller.
 */

namespace Entity\Wildcard;

/**
 * Class UIController.
 *
 * The following methods can be implemented by a child:
 * - entityForm
 * - entityFormValidate
 * - entityFormSubmit
 * - entityFormAjaxHandler
 * - entity<BundleName>Form
 * - entity<BundleName>Validate
 * - entity<BundleName>Submit
 * - entity<BundleName>FormAjaxHandler
 *
 * @package Entity\Wildcard
 */
class UIController extends \EntityDefaultUIController {

  /**
   * Menu wildcard.
   *
   * @var string
   */
  protected $wildcard = '';
  /**
   * An array of wildcard arguments.
   *
   * @var array
   */
  protected $arguments = [];

  /**
   * {@inheritdoc}
   */
  public function __construct($entity_type, $entity_info) {
    parent::__construct($entity_type, $entity_info);

    // Process wildcards.
    // This line is really weird but, when Drupal is on installation
    // mode ('install' === MAINTENANCE_MODE) then "menu_get_item()"
    // function goes to recursion and everything fails with:
    // - Maximum function nesting level of '1000' reached, aborting!
    $menu_item = drupal_static('menu_get_item', [])[$_GET['q']];
    $path = '';

    foreach (explode('/', $this->path) as $i => $arg) {
      if (strpos($arg, '%') !== FALSE) {
        // Form an array with numbers of wildcard positions.
        $this->arguments[] = $i;
        // Replace named wildcard.
        $arg = '%';
      }

      $path .= "/$arg";
    }

    if (strpos($menu_item['path'], ltrim($path, '/')) !== FALSE) {
      $this->path = $menu_item['href'];
    }

    // Entity type MUST always be the last argument.
    $this->arguments[] = $this->entityType;
    $this->wildcard = isset($this->entityInfo['admin ui']['menu wildcard']) ? $this->entityInfo['admin ui']['menu wildcard'] : '%entity_wildcard_object';
  }

  /**
   * {@inheritdoc}
   */
  // @codingStandardsIgnoreStart
  public function hook_menu() {
    // @codingStandardsIgnoreEnd
    $items = parent::hook_menu();
    $wildcard_position = $this->id_count + 1;
    $wildcard_operation = $wildcard_position + 1;

    // Replace wildcard from a parent class.
    foreach ($items as $path => $info) {
      if (strpos($path, '%entity_object') !== FALSE) {
        $items[str_replace('%entity_object', $this->wildcard, $path)] = $info;
        unset($items[$path]);
      }
    }

    // Entity ID is null for empty object initialization.
    $items["$this->path/add"]['page arguments'] = [NULL, $this->id_count];
    $items["$this->path/manage/$this->wildcard"]['page arguments'] = [$wildcard_position, 'edit'];
    // @todo Add wrappers for operation forms.
    $items["$this->path/manage/$this->wildcard/clone"]['page arguments'] = [$wildcard_position, $wildcard_operation];

    // Alter menu items.
    $this->hookMenu($items);

    // Process arguments of the menu items.
    foreach ($items as $path => $info) {
      if (isset($info['access callback'])) {
        $items[$path]['access callback'] = 'entity_wildcard_access';

        $key = array_search($this->entityType, $info['access arguments']);

        if (FALSE !== $key) {
          unset($info['access arguments'][$key]);
        }

        $items[$path]['access arguments'] = array_merge($info['access arguments'], $this->arguments);
      }

      // Update load arguments with wildcards.
      if (isset($info['load arguments'])) {
        $items[$path]['load arguments'] = $this->arguments;
      }

      // Add wildcard numbers and entity type to the end of array of arguments.
      if (isset($info['page arguments'])) {
        $items[$path]['page arguments'] = array_merge($info['page arguments'], $this->arguments);
      }

      if (isset($info['page callback']) && 'entity_ui_get_form' === $info['page callback']) {
        $items[$path]['page callback'] = 'entity_wildcard_' . $info['page callback'];
      }
    }

    return $items;
  }

  /**
   * Load data by wildcard.
   *
   * @see entity_wildcard_object_load()
   *
   * @example
   * The next path: "user/%user/ENTITY_PATH/manage/ENTITY_ID" will be
   * transformed to a set of arguments: "ENTITY_ID, ENTITY_TYPE, [UID]".
   *
   * @param string|int $entity_id
   *   An unique name or ID of an entity.
   * @param string $entity_type
   *   Then type of entity.
   * @param array $wildcards
   *   Arguments in order by wildcards.
   *
   * @return mixed
   *   Wildcard data.
   */
  public static function loadWildcard($entity_id, $entity_type, array $wildcards) {
    return entity_object_load($entity_id, $entity_type);
  }

  /**
   * Check access to entity.
   *
   * @see entity_wildcard_access()
   *
   * @param string $operation
   *   Operation over the entity.
   * @param string $entity_type
   *   The type of entity.
   * @param array $wildcards
   *   Arguments in order by wildcards.
   *
   * @return bool
   *   A state of checking.
   */
  public static function access($operation, $entity_type, array $wildcards) {
    return entity_access($operation, $entity_type, array_pop($wildcards));
  }

  /**
   * Process menu routes.
   *
   * @param array $items
   *   Menu routes.
   */
  public function hookMenu(array &$items) {

  }

}
