<?php
/**
 * @file
 * Administrative page callbacks module.
 */
/**
 * Implements hook_admin_settings() for module settings configuration.
 */
function imx_dashboard_admin_settings_form($form_state) {
  //Get values
  $settings=variable_get('imx_dashboard_settings', NULL);
  $form['#submit'][]='imx_dashboard_admin_settings_form_submit';
  $form['dashboard'] = array(
    '#type' => 'fieldset',
    '#title' => t('Api Site Integration'),
  );
  $form['dashboard']['imx_dashboard_settings']['status'] = array(
    '#title' => t('Enable API Site Integration'),
    '#type' => 'checkbox',
    '#default_value' => isset($settings['status']) && !empty($settings['status']) ? $settings['status'] : TRUE,
    '#description' => t('Enable or Disable API Site Actions'),
  );
  $form['dashboard']['imx_dashboard_settings']['debug'] = array(
    '#title' => t('Debug Mode'),
    '#type' => 'checkbox',
    '#default_value' => isset($settings['debug']) && !empty($settings['debug']) ? $settings['debug'] : FALSE,
    '#description' => t('Enable or disable Debug Mode'),
  );
  return system_settings_form($form);
}
/**
 * Implements _form_submit().
 */
function imx_dashboard_admin_settings_form_submit($form, &$form_state){
  $settings=array(
    'status' => $form_state['values']['status'],
    'debug'  => $form_state['values']['debug'],
  );
  //Save values
  variable_set('imx_dashboard_settings',$settings);
}
