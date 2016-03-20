<?php
/**
 * @file
 * config_path_patterns.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function config_path_patterns_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_server_pattern';
  $strongarm->value = 'server/[node:title]';
  $export['pathauto_node_server_pattern'] = $strongarm;

  return $export;
}
