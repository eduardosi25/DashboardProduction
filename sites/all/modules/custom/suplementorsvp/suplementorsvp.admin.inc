<?php
/**
 * @file
 * Administrative page callbacks
 * Implements hook_admin_settings()
 */
function suplementorsvp_admin_settings_form($form_state) {
  $form['#submit'][]='suplementorsvp_admin_settings_form_submit';
  $form['suplementorsvp'] = array(
    '#type' => 'fieldset',
    '#title' => t('Configuración del suplemento digital de R.S.V.P.'),
  );
  $form['suplementorsvp']['suplementorsvp_status'] = array(
    '#title' => t('Enabled RSVP Magazine'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('suplementorsvp_status',FALSE),
    '#description' => t('Enabled or disabled RSVP magazine'),  
  );    
  $form['suplementorsvp']['suplementorsvp_apiurl'] = array(
    '#title' => t('API Url'),
    '#type' => 'textfield',
    '#default_value' => variable_get('suplementorsvp_apiurl',''),
    '#size' => 100,
    '#maxlength' => 250,
    '#required' => TRUE,
    '#description' => t('API Url needed for retrieve data for this magazine'),  
  );    
  $form['suplementorsvp']['suplementorsvp_effect'] = array(
    '#title' => t('Image effect'),
    '#type' => 'textfield',
    '#default_value' => variable_get('suplementorsvp_effect',''),
    '#size' => 70,
    '#maxlength' => 128,
    '#required' => TRUE,
    '#description' => t('Image effect for hover event'),  
  );    
  return system_settings_form($form);
}
/**
 * Implements _form_validate().
 */
function suplementorsvp_admin_settings_form_validate($form, &$form_state) {
  // Trim some text values.
  $form_state['values']['suplementorsvp_apiurl'] = trim($form_state['values']['suplementorsvp_apiurl']);
  //Valid a field value or catch error
  if(!isset($form_state['values']['suplementorsvp_apiurl']) || empty($form_state['values']['suplementorsvp_apiurl'])){
    form_set_error('suplementorsvp_apiurl', t('You need to provide an API Url.'));
  }
  // Trim some text values.
  $form_state['values']['suplementorsvp_effect'] = trim($form_state['values']['suplementorsvp_effect']);
  //Valid a field value or catch error
  if(!isset($form_state['values']['suplementorsvp_effect']) || empty($form_state['values']['suplementorsvp_effect'])){
    form_set_error('suplementorsvp_effect', t('You need to provide a image effect.'));
  }
}
/**
 * Implements _form_submit().
 */
function suplementorsvp_admin_settings_form_submit($form, &$form_state){
  //Save values
  variable_set('suplementorsvp_status',$form_state['values']['suplementorsvp_status']);
  variable_set('suplementorsvp_apiurl',$form_state['values']['suplementorsvp_apiurl']);
  variable_set('suplementorsvp_effect',$form_state['values']['suplementorsvp_effect']);
}
