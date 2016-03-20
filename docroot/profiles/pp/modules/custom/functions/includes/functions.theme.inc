<?php
/**
 * @file
 * Auxiliary functionality for theming.
 */

/**
 * Render file by file ID.
 *
 * @see theme_image()
 * @see theme_image_style()
 *
 * @param string|int|array|\stdClass $file
 *   File ID or object.
 * @param string[] $settings
 *   Available values: "alt", "title", "image_style".
 *
 * @return string
 *   Empty string when file does not exist or type is not supported or HTML.
 */
function media_file(&$file, array $settings = []) {
  if (!empty($file)) {
    // Could be an array when loaded as part of entity.
    if (is_array($file)) {
      $file = (object) $file;
    }
    elseif (is_scalar($file)) {
      $file = function_exists('file_md5_load_file') ? file_md5_load_file($file) : file_load($file);
    }

    if (is_object($file) && !empty($file->type)) {
      $file->url = empty($file->uri) ? '' : file_create_url($file->uri);

      switch ($file->type) {
        case 'image':
          $dimensions = [];
          $attributes = [
            'role' => 'img',
          ];

          foreach (['alt', 'title'] as $prop) {
            $attributes[$prop] = empty($file->$prop) ? (empty($settings[$prop]) ? '' : $settings[$prop]) : $file->$prop;
          }

          if (!empty($file->image_dimensions)) {
            $dimensions = $file->image_dimensions;
          }

          $attributes += $dimensions;
          $attributes = array_filter($attributes);

          if (!empty($settings['image_style'])) {
            $image_styles = image_style_options();

            if (isset($image_styles[$settings['image_style']])) {
              return theme('image_style', $dimensions + [
                'path' => $file->uri,
                'style_name' => $settings['image_style'],
                'attributes' => $attributes,
              ]);
            }
          }

          // @codingStandardsIgnoreStart
          return theme('image', [
            'path' => $file->uri,
            'attributes' => $attributes,
          ]);
          // @codingStandardsIgnoreEnd
      }
    }
  }

  return '';
}

/**
 * Load default image for a field.
 *
 * @param string $field_name
 *   Field name.
 *
 * @return bool|\stdClass
 *   FALSE if image does not exist or cannot be loaded, file object otherwise.
 */
function field_default_image($field_name) {
  $info = field_info_field($field_name);

  return empty($info['settings']['default_image']) ? FALSE : file_load($info['settings']['default_image']);
}
