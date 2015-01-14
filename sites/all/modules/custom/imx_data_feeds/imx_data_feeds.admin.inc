<?php
/**
 * @file
 * Administrative page callbacks for the imx_data_feeds module.
 */
/**
 * Implements hook_admin_settings() for module settings configuration.
 */
function imx_data_feeds_admin_settings_form($form_state) {

  $status=variable_get('imx_data_feeds_status',FALSE);
  $settings=variable_get('imx_data_feeds_settings', NULL);

  $form['#submit'][]='imx_data_feeds_admin_settings_form_submit';
  $form['imx_data_feeds'] = array(
    '#type' => 'fieldset',
    '#title' => t('Invent Data Feeds'),
  );

  $form['imx_data_feeds']['imx_data_feeds_status'] = array(
    '#title' => t('Enabled Invent Data Feeds Integration'),
    '#type' => 'checkbox',
    '#default_value' => $status,
    '#description' => t('Enabled or disabled Invent Data Feeds Integration'),
  );

  $form['imx_data_feeds']['imx_data_feeds_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Settings'),
    '#tree' => TRUE,
  );

  $form['imx_data_feeds']['imx_data_feeds_settings']['cache_dir'] = array(
    '#title' => t('Cache Directory'),
    '#type' => 'textfield',
    '#default_value' => isset($settings['cache_dir']) && !empty($settings['cache_dir']) ? $settings['cache_dir'] : DRUPAL_ROOT.'/web/data',
    '#size' => 80,
    '#maxlength' => 255,
    '#description' => t('You need to provide a valid cache directory and this one must have public access.'),
  );

  $form['imx_data_feeds']['imx_data_feeds_settings']['expire'] = array(
    '#title' => t('Enabled Expire Cache'),
    '#type' => 'checkbox',
    '#default_value' => $settings['expire'],
    '#description' => t('Enabled or disabled expire cache'),
  );

  $form['imx_data_feeds']['imx_data_feeds_settings']['cronjob'] = array(
    '#title' => t('Enabled Cronjob'),
    '#type' => 'checkbox',
    '#default_value' => $settings['cronjob'],
    '#description' => t('Enabled or disabled cronjob for rebuilding cache'),
  );

    return system_settings_form($form);
}
/**
 * Implements _form_validate().
 */
function imx_data_feeds_admin_settings_form_validate($form, &$form_state) {
  //Valid a field value or catch error
  if(!isset($form_state['values']['imx_data_feeds_settings']['cache_dir']) || empty($form_state['values']['imx_data_feeds_settings']['cache_dir'])){
    form_set_error('imx_data_feeds_settings][cache_dir', t('You need to provide a valid directory path'));
  }
}
/**
 * Implements _form_submit().
 */
function imx_data_feeds_admin_settings_form_submit($form, &$form_state){
  variable_set('imx_data_feeds_status',$form_state['values']['imx_data_feeds_status']);
  variable_set('imx_data_feeds_settings',$form_state['values']['imx_data_feeds_settings']);
}
