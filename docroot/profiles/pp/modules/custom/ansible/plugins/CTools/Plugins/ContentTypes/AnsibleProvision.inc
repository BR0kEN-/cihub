<?php
/**
 * @file
 * Ansible Provision CTools content type.
 */

namespace CTools\Plugins\ContentTypes;

/**
 * Class AnsibleProvision.
 *
 * @package CTools\Plugins\ContentTypes
 */
class AnsibleProvision implements ContentTypesInterface {

  /**
   * {@inheritdoc}
   */
  public static function name() {
    return t('Ansible Provision');
  }

  /**
   * {@inheritdoc}
   */
  public static function info() {
    return [
      'required context' => new \ctools_context_required(t('Context'), 'node'),
    ];
  }

  /**
   * {@inheritdoc}
   */
  public static function themeVariants() {
    return [];
  }

  /**
   * {@inheritdoc}
   */
  public static function dependencies() {
    return [];
  }

  /**
   * {@inheritdoc}
   */
  public static function preprocess(array &$variables, array &$arguments, \ctools_context $context = NULL) {
    $variables['form'] = '';

    if ($context) {
      $variables['form'] = drupal_get_form('ansible_provision_form', $context->data);
    }
  }

  /**
   * {@inheritdoc}
   */
  public static function configurationForm(array &$form, array &$form_state, array &$conf) {

  }

  /**
   * {@inheritdoc}
   */
  public static function configurationFormValidate(array &$form, array &$form_state, array &$values) {

  }

  /**
   * {@inheritdoc}
   */
  public static function configurationFormSubmit(array &$form, array &$form_state, array &$conf) {

  }

  /**
   * {@inheritdoc}
   */
  public static function configurationFormElementCallback(array &$form, array &$form_state, array &$conf, array &$commands, array $element) {

  }

}
