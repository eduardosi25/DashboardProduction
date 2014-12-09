<?php
/**
 * Implements hook_form_FORM_ID_alter().
 *
 * @param $form
 *   The form.
 * @param $form_state
 *   The form state.
 */
function rsvponline_form_system_theme_settings_alter(&$form, &$form_state) {
  $form['resp_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('R.S.V.P. Theme Settings'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );
  $form['resp_settings']['breadcrumbs'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show breadcrumbs in a page'),
    '#default_value' => theme_get_setting('breadcrumbs','rsvponline'),
    '#description'   => t("Check this option to show breadcrumbs in page. Uncheck to hide."),
  );
  $form['resp_settings']['socialicon'] = array(
    '#type' => 'fieldset',
    '#title' => t('Social Icon'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['resp_settings']['socialicon']['socialicon_display'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show Social Icon'),
    '#default_value' => theme_get_setting('socialicon_display','rsvponline'),
    '#description'   => t("Check this option to show Social Icon. Uncheck to hide."),
  );
  $form['resp_settings']['socialicon']['twitter_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Twitter Profile URL'),
    '#default_value' => theme_get_setting('twitter_url', 'rsvponline'),
	  '#description'   => t("Enter your Twitter Profile URL. Leave blank to hide."),
  );
  $form['resp_settings']['socialicon']['facebook_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Facebook Profile URL'),
    '#default_value' => theme_get_setting('facebook_url', 'rsvponline'),
	  '#description'   => t("Enter your Facebook Profile URL. Leave blank to hide."),
  );
  $form['resp_settings']['socialicon']['googleplus_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Google+ Profile URL'),
    '#default_value' => theme_get_setting('googleplus_url', 'rsvponline'),
	  '#description'   => t("Enter your Google+ Profile URL. Leave blank to hide."),
  );
  $form['resp_settings']['socialicon']['youtube_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Youtube Profile URL'),
    '#default_value' => theme_get_setting('youtube_url', 'rsvponline'),
    '#description'   => t("Enter your Youtube Profile URL. Leave blank to hide."),
  );
  $form['resp_settings']['socialicon']['instagram_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Instagram Profile URL'),
    '#default_value' => theme_get_setting('instagram_url', 'rsvponline'),
	  '#description'   => t("Enter your Instagram Profile URL. Leave blank to hide."),
  );
}
