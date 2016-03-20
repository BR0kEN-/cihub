<?php
/**
 * @file
 * config_path_patterns.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function config_path_patterns_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
