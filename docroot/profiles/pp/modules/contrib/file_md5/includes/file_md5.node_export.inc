<?php
/**
 * @file
 * Node Export related functionality.
 */

/**
 * Process file field on a node.
 *
 * @param \stdClass $node
 *   Node object.
 * @param callable $process
 *   Processing callback.
 */
function file_md5_node_export_process_file_field(\stdClass $node, callable $process) {
  $langcodes = field_language('node', $node);
  // @see node_export_file_field_export()
  $types = array_map('trim', explode(',', variable_get('node_export_file_supported_fields', 'file, image')));

  foreach (field_info_instances('node', $node->type) as $field_name => $field) {
    $field_info = field_info_field($field_name);

    if (in_array($field_info['type'], $types)) {
      $langcode = $langcodes[$field_name];

      if (!empty($node->{$field_name}[$langcode])) {
        foreach ($node->{$field_name}[$langcode] as $i => $item) {
          $process($node->{$field_name}[$langcode][$i]);
        }

        $node->{$field_name}[$langcode] = array_filter($node->{$field_name}[$langcode]);
      }
    }
  }
}
