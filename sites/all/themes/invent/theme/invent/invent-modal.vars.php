<?php
/**
 * @file
 * invent-modal.vars.php
 */

/**
 * Implements theme_preprocess_invent_modal().
 *
 * @todo: Replace with "invent_effect_fade" theme setting.
 */
function invent_preprocess_invent_modal(&$variables) {
  if (empty($variables['attributes']['id'])) {
    $variables['attributes']['id'] = drupal_html_id(strip_tags($variables['heading']));
  }
  $variables['attributes']['class'][] = 'modal';
  $variables['attributes']['class'][] = 'fade';
  $variables['attributes']['tabindex'] = -1;
  $variables['attributes']['role'] = 'dialog';
  $variables['attributes']['aria-hidden'] = 'true';

  $variables['heading'] = $variables['html_heading'] ? $variables['heading'] : check_plain($variables['heading']);
}

/**
 * Implements theme_process_invent_modal().
 */
function invent_process_invent_modal(&$variables) {
  $variables['attributes'] = drupal_attributes($variables['attributes']);
  $variables['body'] = render($variables['body']);
  $variables['footer'] = render($variables['footer']);
}
