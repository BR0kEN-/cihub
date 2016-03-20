<?php
/**
 * @file
 * Default field template.
 *
 * @var array $items
 * @var string $classes
 * @var string $attributes
 * @var bool $label_hidden
 * @var string $title_attributes
 * @var string $label
 * @var string $content_attributes
 * @var array $item_attributes
 */
?>
<?php foreach ($items as $item): ?>
  <?php print render($item); ?>
<?php endforeach; ?>
