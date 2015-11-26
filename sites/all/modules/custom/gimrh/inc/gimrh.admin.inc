<?php
/**
 * @file
 * Administrative page callbacks for the gimrh module.
 */
/**
 * Implements hook_admin_settings() for module settings configuration.
 */
function gimrh_admin_settings_form($form_state) {
  $form['#submit'][]='gimrh_admin_settings_form_submit';
  $form['gimrh'] = array(
    '#type' => 'fieldset',
    '#title' => t('GIM RH Settings'),
  );
  $status=variable_get('gimrh_status',FALSE);
  $form['gimrh']['gimrh_status'] = array(
    '#title' => t('Enabled GIM RH Integration'),
    '#type' => 'checkbox',
    '#default_value' => $status,
    '#description' => t('Enabled or disabled GIM RH Integration'),
  );
  $settings=variable_get('gimrh_settings',NULL);
    $form['gimrh']['gimrh_settings'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
    '#title' => t('GIM RH - Administration'),
    '#collapsible' => TRUE,
    '#collapsed' => variable_get('gimrh_status', FALSE),
  );
  $form['gimrh']['gimrh_settings']['debug'] = array(
    '#title' => t('Debug'),
    '#type' => 'checkbox',
    '#default_value' => isset($settings['debug']) ? $settings['debug'] : FALSE,
    '#description' => t('Enabled debug mode'),
  );
  $form['gimrh']['gimrh_settings']['email'] = array(
    '#title' => t('Email reciever'),
    '#type' => 'textfield',
    '#default_value' => isset($settings['email']) ? $settings['email'] : NULL,
    '#size' => 80,
    '#maxlength' => 254,
  );
  $form['gimrh']['gimrh_settings']['privacy'] = array(
      '#title' => t('Privacy notice'),
      '#type' => 'text_format',
      '#default_value' => isset($settings['privacy']['value']) ? $settings['privacy']['value'] : NULL,
      '#format' => isset($settings['privacy']['format']) ? $settings['privacy']['format'] : 'filtered_html',
  );
  $form['gimrh']['gimrh_settings']['confidential'] = array(
    '#title' => t('Confidentiality notice'),
    '#type' => 'text_format',
    '#default_value' => isset($settings['confidential']['value']) ? $settings['confidential']['value'] : NULL,
    '#format' => isset($settings['confidential']['format']) ? $settings['confidential']['format'] : 'filtered_html',
  );
  return system_settings_form($form);
}
/**
 * Implements _form_validate().
 */
function gimrh_admin_settings_form_validate($form, &$form_state) {
  //Valid a field value or catch error
  if(!isset($form_state['values']['gimrh_settings']['email']) || empty($form_state['values']['gimrh_settings']['email'])){
    form_set_error('gimrh_settings][email', t('You need to provide a valid Email.'));
  }
}
/**
 * Implements _form_submit().
 */
function gimrh_admin_settings_form_submit($form, &$form_state){
  //Save values
  variable_set('gimrh_status',$form_state['values']['gimrh_status']);
  /**
   * Settings
   */
  $settings=array(
    'debug'   => $form_state['values']['gimrh_settings']['debug'],
    'email'   => $form_state['values']['gimrh_settings']['email'],
    'privacy' => $form_state['values']['gimrh_settings']['privacy'],
    'confidential' => $form_state['values']['gimrh_settings']['confidential'],
  );
  variable_set('gimrh_settings',$settings);

  //Clear cache
  cache_clear_all('gimrh_variables', 'cache');
}
