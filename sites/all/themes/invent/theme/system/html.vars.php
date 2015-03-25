<?php
/**
 * @file
 * html.vars.php
 *
 * @see html.tpl.php
 */

/**
 * Implements hook_preprocess_html().
 */
function invent_preprocess_html(&$variables) {
  switch (theme_get_setting('invent_navbar_position')) {
    case 'fixed-top':
      $variables['classes_array'][] = 'navbar-is-fixed-top';
      break;

    case 'fixed-bottom':
      $variables['classes_array'][] = 'navbar-is-fixed-bottom';
      break;

    case 'static-top':
      $variables['classes_array'][] = 'navbar-is-static-top';
      break;
  }
}
