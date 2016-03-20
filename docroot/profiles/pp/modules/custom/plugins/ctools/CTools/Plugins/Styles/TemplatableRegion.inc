<?php
/**
 * @file
 * Definition of style plugin for templating region wrappers.
 */

namespace CTools\Plugins\Styles;

/**
 * Class TemplatableRegion.
 *
 * @package CTools\Plugins\Styles
 */
class TemplatableRegion extends Templatable  implements StylesRegionInterface {

  /**
   * {@inheritdoc}
   */
  public static function themeVariants() {
    return [
      'node-cv-header' => t('Node Header (CV)'),
    ];
  }

  /**
   * {@inheritdoc}
   */
  public static function preprocess(\panels_display $display, array &$settings, array &$variables) {

  }

}
