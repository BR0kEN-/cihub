<?php
/**
 * @file
 * Custom includes loader.
 */

/**
 * Load files from "includes/" directory of a module.
 *
 * @example
 * /<module>
 * |-- includes
 * |   |-- <module>.<type>.inc
 *
 * @param string $module
 *   The name of module.
 * @param string $type
 *   The type of content of file (part of file extension).
 *
 * @return bool|string
 *   FALSE if file not found, full path otherwise.
 */
function load_include($module, $type) {
  return module_load_include('inc', $module, "includes/$module.$type");
}
