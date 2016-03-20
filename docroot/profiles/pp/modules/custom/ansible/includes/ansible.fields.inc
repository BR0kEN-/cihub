<?php
/**
 * @file
 * Field definitions.
 */

/**
 * Default fields schema.
 *
 * @param string $entity_type
 *   The type of entity.
 * @param string $bundle
 *   The type of entity bundle.
 *
 * @return array[]
 *   Field definitions.
 */
function ansible_fields_schema($entity_type, $bundle) {
  $fields = [];

  $fields['ansible_host'] = [
    'type' => 'text',
    // Instance settings below.
    'label' => 'Host',
    'required' => TRUE,
  ];

  $fields['ansible_port'] = [
    'type' => 'number_integer',
    // Instance settings below.
    'label' => 'Port',
  ];

  $fields['ansible_ssh_private_key_file'] = [
    'type' => 'entityreference',
    // Instance settings below.
    'label' => 'SSH keys',
    'required' => TRUE,
    'cardinality' => -1,
    'settings' => [
      'handler' => 'base',
      'target_type' => 'ssh_key',
    ],
  ];

  foreach ($fields as $field_name => $field_definition) {
    $fields[$field_name] += [
      'bundle' => $bundle,
      'entity_type' => $entity_type,
    ];
  }

  return $fields;
}

/**
 * Delete fields.
 *
 * This function deletes tables: "field_data_NAME" and "field_revision_NAME"
 * and entries in "field_config" and "field_config_instances".
 *
 * @param string[] $field_names
 *   An array with field names.
 */
function ansible_fields_delete(array $field_names) {
  foreach ($field_names as $field_name) {
    // Delete tables.
    foreach (['data', 'revision'] as $table_type) {
      $table = "field_{$table_type}_{$field_name}";

      if (db_table_exists($table)) {
        db_drop_table($table);
      }
    }

    // Delete entries.
    foreach (['config', 'config_instance'] as $table_type) {
      db_delete("field_$table_type")
        ->condition('field_name', $field_name)
        ->execute();
    }
  }
}

/**
 * Create fields tree recursively.
 *
 * @param array[] $fields
 *   Field definitions.
 * @param bool $delete
 *   Indicates that fields should be removed previously.
 */
function ansible_create_fields(array $fields, $delete = FALSE) {
  foreach ($fields as $field_name => $field) {
    $field['locked'] = TRUE;
    $field['field_name'] = $field_name;

    foreach (['widget', 'settings'] as $property) {
      $field += [$property => []];
    }

    switch ($field['type']) {
      case 'field_collection':
        // Set unlimited cardinality by default.
        $field += [
          'cardinality' => -1,
        ];

        // Set an embed widget by default.
        $field['widget'] += [
          'type' => 'field_collection_embed',
        ];
        break;

      case 'number_integer':
        $field['widget'] += [
          'type' => 'number',
        ];

        $field['settings'] += [
          'max' => '',
          'min' => 1,
          'prefix' => '',
          'suffix' => '',
          'max_length' => 10,
        ];
        break;

      case 'text_long':
        $field['widget'] += [
          'type' => 'text_textarea',
        ];

        $field['settings'] += [
          'text_processing' => TRUE,
          'allowed_formats_toggle' => TRUE,
        ];
        break;

      case 'text':
        $field['widget'] += [
          'type' => 'text_textfield',
        ];

        $field['settings'] += [
          'allowed_formats_toggle' => TRUE,
        ];
        break;
    }

    if ($delete) {
      ansible_fields_delete([$field_name]);
    }

    if (!field_info_field($field_name)) {
      field_create_field($field);
    }

    if (!field_info_instance($field['entity_type'], $field_name, $field['bundle'])) {
      field_create_instance($field);
    }

    if (!empty($field['#children'])) {
      // Build fields tree.
      foreach ($field['#children'] as $i => $child) {
        $field['#children'][$i] += [
          'bundle' => $field_name,
          'entity_type' => 'field_collection_item',
        ];
      }

      call_user_func(__FUNCTION__, $field['#children']);
    }
  }
}
