<?php
/**
 * @file
 * Default theme variant for Ansible Provision content type plugin.
 *
 * @see \CTools\Plugins\ContentTypes\AnsibleProvision
 *
 * @var array $content
 */
dpm(
  get_defined_vars()
);
?>
<?php print render($content['form']); ?>
