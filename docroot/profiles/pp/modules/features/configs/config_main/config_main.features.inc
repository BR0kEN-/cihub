<?php
/**
 * @file
 * config_main.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function config_main_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
