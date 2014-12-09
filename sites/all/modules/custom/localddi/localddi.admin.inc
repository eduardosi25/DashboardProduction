<?php
/**
 * @file
 * Administrative page callbacks for the localddi module.
 */
/**
 * Implements hook_admin_settings() for module settings configuration.
 */
function localddi_admin_settings_form($form_state) {
  $form['#submit'][]='localddi_admin_settings_form_submit';
  $form['localddi'] = array(
    '#type' => 'fieldset',
    '#title' => t('Zedo settings'),
  );
  $form['localddi']['localddi_status'] = array(
    '#title' => t('Enabled Zedo Integration'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('localddi_status',FALSE),
    '#description' => t('Enabled or disabled Zedo Integration'),
  );
  $form['localddi']['localddi_debug'] = array(
    '#title' => t('Enabled debug mode'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('localddi_debug',FALSE),
    '#description' => t('Enabled or disabled debug mode'),
  );    
  $form['localddi']['localddi_wrapper'] = array(
    '#title' => t('Zedo Wrapper ID'),
    '#type' => 'textfield',
    '#default_value' => variable_get('localddi_wrapper','localddi-wrapper'),
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
function localddi_admin_settings_form_validate($form, &$form_state) {
  // Trim some text values.
  $form_state['values']['localddi_wrapper'] = trim($form_state['values']['localddi_wrapper']);
  //Valid a field value or catch error
  if(!isset($form_state['values']['localddi_wrapper']) || empty($form_state['values']['localddi_wrapper'])){
    form_set_error('localddi_wrapper', t('You need to provide a wrapper ID name.'));
  }
}
/**
 * Implements _form_submit().
 */
function localddi_admin_settings_form_submit($form, &$form_state){
  //Save values
  variable_set('localddi_status',$form_state['values']['localddi_status']);
  variable_set('localddi_debug',$form_state['values']['localddi_debug']);
  variable_set('localddi_wrapper',$form_state['values']['localddi_wrapper']);
}
