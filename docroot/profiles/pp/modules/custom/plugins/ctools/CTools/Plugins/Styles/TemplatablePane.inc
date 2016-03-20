<?php
/**
 * @file
 * Definition of style plugin for templating pane wrappers.
 */

namespace CTools\Plugins\Styles;

/**
 * Class TemplatablePane.
 *
 * @package CTools\Plugins\Styles
 */
class TemplatablePane extends Templatable implements StylesPaneInterface {

  /**
   * {@inheritdoc}
   */
  public static function themeVariants() {
    return [];
  }

  /**
   * {@inheritdoc}
   */
  public static function preprocess(\stdClass $content, array &$settings, array &$variables) {

  }

}
