<?php
/**
 * @file
 * Main panel pane template.
 *
 * @var array $content
 * @var \stdClass $pane
 * @var \panels_display $display
 */
?>
<?php print render($content); ?>

<?php if (!empty($pane->links)): ?>
  <?php print render($pane->links); ?>
<?php endif; ?>
