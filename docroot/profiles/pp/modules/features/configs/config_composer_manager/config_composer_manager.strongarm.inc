<?php
/**
 * @file
 * config_composer_manager.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function config_composer_manager_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'composer_manager_file_dir';
  $strongarm->value = 'profiles/pp';
  $export['composer_manager_file_dir'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'composer_manager_vendor_dir';
  $strongarm->value = 'profiles/pp/vendor';
  $export['composer_manager_vendor_dir'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'composer_manager_autobuild_file';
  $strongarm->value = TRUE;
  $export['composer_manager_autobuild_file'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'composer_manager_autobuild_packages';
  $strongarm->value = FALSE;
  $export['composer_manager_autobuild_packages'] = $strongarm;

  return $export;
}
