<?php
/**
 * @file
 * Auxiliary functionality for export/import nodes.
 */

/**
 * Import/export field collections content.
 *
 * @param string $entity_type
 *   The type of entity.
 * @param object $entity
 *   An entity object.
 */
function node_export_field_collection_recursive_export_import($entity_type, $entity) {
  list(,, $bundle) = entity_extract_ids($entity_type, $entity);
  $fields_info = field_info_fields();
  $langcodes = field_language($entity_type, $entity);

  foreach (field_info_instances($entity_type, $bundle) as $field_name => $instance) {
    // Processing non-empty field collections only.
    if (
      // Field should be attached to an entity.
      isset($entity->{$field_name}) &&
      // Language code should exist for a field.
      isset($langcodes[$field_name]) &&
      // Field definition should exist.
      isset($fields_info[$field_name]) &&
      // Field data should be accessible by language code.
      isset($entity->{$field_name}[$langcodes[$field_name]]) &&
      // Field type should be the "field_collection".
      'field_collection' === $fields_info[$field_name]['type']
    ) {
      // Walk through the items of collection.
      foreach ($entity->{$field_name}[$langcodes[$field_name]] as $delta => &$item) {
        // The structure of existing items:
        // @code
        // [
        //   'value' => 12,
        //   'revision_id' => 14,
        // ];
        // @endcode
        if (is_array($item) && !array_key_exists('value', $item) && !array_key_exists('revision_id', $item)) {
          // An "entity" key will be present when host entity is set. In this
          // case nothing should be done.
          if (empty($item['entity'])) {
            /* @var \FieldCollectionItemEntity $new_entity */
            $new_entity = entity_create('field_collection_item', $item);
            // Field collection entity depends on another entity that must be
            // a parent for it.
            $new_entity->setHostEntity($entity_type, $entity, $langcodes[$field_name]);
            // Make an import of nested collections come true.
            call_user_func_array(__FUNCTION__, [$new_entity->entityType(), $new_entity]);
            // Completely remove existing item.
            unset($entity->{$field_name}[$langcodes[$field_name]][$delta]);
          }
        }
        else {
          /* @var \FieldCollectionItemEntity $item */
          $item = field_collection_field_get_entity($item);

          // Prevent cases, when:
          // @code
          // [
          //   'value' => NULL,
          //   'revision_id' => NULL,
          // ];
          // @endcode
          if (FALSE !== $item) {
            // Make an export of nested collections come true.
            call_user_func_array(__FUNCTION__, [$item->entityType(), $item]);
            // Redundant information should not be exported.
            unset($item->item_id, $item->revision_id, $item->default_revision);
            // Make an array from the object for easy export.
            $item = get_object_vars($item);
          }
        }
      }
    }
  }
}
