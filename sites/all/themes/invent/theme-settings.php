<?php
/**
 * @file
 * theme-settings.php
 *
 * Provides theme settings for Invent based themes when admin theme is not.
 *
 * @see theme/settings.inc
 */

/**
 * Include common Invent functions.
 */
include_once dirname(__FILE__) . '/theme/common.inc';

/**
 * Implements hook_form_FORM_ID_alter().
 */
function invent_form_system_theme_settings_alter(&$form, $form_state, $form_id = NULL) {
  // Work-around for a core bug affecting admin themes.
  // @see https://drupal.org/node/943212
  if (isset($form_id)) {
    return;
  }
  // Include theme settings file.
  invent_include('invent', 'theme/settings.inc');
  // Alter theme settings form.
  _invent_settings_form($form, $form_state);
}
