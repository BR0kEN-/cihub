<?php
/**
 * @file
 * Enables modules and site configuration for a pp site installation.
 */

if (file_exists('vendor/autoload.php')) {
  require_once 'vendor/autoload.php';
}

/**
 * Implements hook_form_FORM_ID_alter().
 *
 * @see install_configure_form()
 */
function pp_form_install_configure_form_alter(array &$form, array &$form_state) {
  // Pre-populate the site name with the server name.
  $form['site_information']['site_name']['#default_value'] = $_SERVER['SERVER_NAME'];
}
