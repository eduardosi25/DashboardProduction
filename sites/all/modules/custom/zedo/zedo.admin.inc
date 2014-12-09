<?php
/**
 * @file
 * Administrative page callbacks for the zedo module.
 */
/**
 * Implements hook_admin_settings() for module settings configuration.
 */
function zedo_admin_settings_form($form_state) {
  $form['#submit'][]='zedo_admin_settings_form_submit';
  $form['zedo'] = array(
    '#type' => 'fieldset',
    '#title' => t('Zedo settings'),
  );
  $form['zedo']['zedo_status'] = array(
    '#title' => t('Enabled Zedo Integration'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('zedo_status',FALSE),
    '#description' => t('Enabled or disabled Zedo Integration'),
  );
  $form['zedo']['zedo_debug'] = array(
    '#title' => t('Enabled debug mode'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('zedo_debug',FALSE),
    '#description' => t('Enabled or disabled debug mode'),
  );    
  $form['zedo']['zedo_wrapper'] = array(
    '#title' => t('Zedo Wrapper ID'),
    '#type' => 'textfield',
    '#default_value' => variable_get('zedo_wrapper','zedo-wrapper'),
    '#size' => 60,
    '#maxlength' => 100,
    '#required' => TRUE,
    '#description' => t('Zedo wrapper ID'),
  );    
  return system_settings_form($form);
}
/**
 * Implements _form_validate().
 */
function zedo_admin_settings_form_validate($form, &$form_state) {
  // Trim some text values.
  $form_state['values']['zedo_wrapper'] = trim($form_state['values']['zedo_wrapper']);
  //Valid a field value or catch error
  if(!isset($form_state['values']['zedo_wrapper']) || empty($form_state['values']['zedo_wrapper'])){
    form_set_error('zedo_wrapper', t('You need to provide a wrapper ID name.'));
  }
}
/**
 * Implements _form_submit().
 */
function zedo_admin_settings_form_submit($form, &$form_state){
  //Save values
  variable_set('zedo_status',$form_state['values']['zedo_status']);
  variable_set('zedo_debug',$form_state['values']['zedo_debug']);
  variable_set('zedo_wrapper',$form_state['values']['zedo_wrapper']);
}
