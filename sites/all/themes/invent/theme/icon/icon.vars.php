<?php
/**
 * @file
 * icon.vars.php
 */

/**
 * Implements hook_preprocess_icon().
 *
 * Invent requires an additional "glyphicon" class for all icons.
 *
 * @see icon_preprocess_icon_image()
 * @see template_preprocess_icon()
 */
function invent_preprocess_icon(&$variables) {
  $bundle = &$variables['bundle'];
  if ($bundle['provider'] === 'invent') {
    $variables['attributes']['class'][] = 'glyphicon';
  }
}
