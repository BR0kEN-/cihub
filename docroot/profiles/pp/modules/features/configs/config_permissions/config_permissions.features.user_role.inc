<?php
/**
 * @file
 * config_permissions.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function config_permissions_user_default_roles() {
  $roles = array();

  // Exported role: Hub manager.
  $roles['Hub manager'] = array(
    'name' => 'Hub manager',
    'weight' => 2,
  );

  return $roles;
}
