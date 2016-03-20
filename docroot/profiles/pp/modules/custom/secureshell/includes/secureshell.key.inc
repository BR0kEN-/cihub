<?php
/**
 * @file
 * Callbacks and helper functions for the "ssh_key" entity.
 *
 * NOTE! SSH key entity is completely depends on user.
 */

/**
 * Check existence of a machine name of a key.
 *
 * @param string $machine_name
 *   Specified machine name.
 * @param array $form
 *   Form definition.
 * @param array $form_state
 *   A state of form.
 *
 * @return bool
 *   A state of checking.
 */
function secureshell_key_machine_name_exists($machine_name, array &$form, array &$form_state) {
  list($account) = $form_state['build_info']['entity_wildcard']['arguments'];

  return FALSE !== secureshell_key_load($account, $machine_name);
}

/**
 * Replace "%user" wildcard in path to entity.
 *
 * @param \stdClass $account
 *   An object of a user.
 *
 * @return string
 *   String where "%user" replaced by used ID.
 */
function secureshell_key_overview_page_uri(\stdClass $account) {
  return str_replace('%user', $account->uid, SECURESHELL_KEYS_ADMIN_PATH);
}

/**
 * Load SSH key of a user.
 *
 * @param \stdClass $account
 *   An object of a user.
 *
 * @return \SecureShell\Key
 *   SSH key objects.
 */
function secureshell_key_load_all(\stdClass $account) {
  $entities = entity_load('ssh_key', FALSE, [
    'uid' => $account->uid,
  ]);

  return $entities;
}

/**
 * Load SSH key.
 *
 * @param \stdClass $account
 *   An object of a user.
 * @param string $machine_name
 *   Machine name of a key.
 *
 * @return \SecureShell\Key|bool
 *   SSH key object or FALSE if it cannot be loaded.
 */
function secureshell_key_load(\stdClass $account, $machine_name) {
  $entities = entity_load('ssh_key', FALSE, [
    'uid' => $account->uid,
    'name' => $machine_name,
  ]);

  return reset($entities);
}
