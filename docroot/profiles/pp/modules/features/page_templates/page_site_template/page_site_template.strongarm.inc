<?php
/**
 * @file
 * page_site_template.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function page_site_template_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panels_everywhere_site_template_enabled';
  $strongarm->value = FALSE;
  $export['panels_everywhere_site_template_enabled'] = $strongarm;

  return $export;
}
