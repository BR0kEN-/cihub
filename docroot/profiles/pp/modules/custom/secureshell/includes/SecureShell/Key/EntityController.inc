<?php
/**
 * @file
 * SSH key entity controller.
 */

namespace SecureShell\Key;

/**
 * Class EntityController.
 *
 * @package SecureShell\Key
 */
class EntityController extends \EntityAPIController {

  /**
   * {@inheritdoc}
   */
  public function delete($ids, \DatabaseTransaction $transaction = NULL) {
    /* @var \SecureShell\Key $key */
    foreach (entity_load('ssh_key', $ids) as $key) {
      $key->setPublic(NULL);
      $key->setPrivate(NULL);
      $key->save();
    }

    parent::delete($ids, $transaction);
  }

}
