<?php
/**
 * Implements hook_admin_settings() for module settings configuration.
 */
function cxense_admin_settings_form($form_state) {
  $form['#submit'][]='cxense_admin_settings_form_submit';
  $form['cxense'] = array(
    '#type' => 'fieldset',
    '#title' => t('Cxense settings'),
  );
  $form['cxense']['cxense_status'] = array(
    '#title' => t('Enabled Cxense Integration'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('cxense_status',FALSE),
    '#description' => t('Enabled or disabled Cxense Integration'),  
  );    
  $form['cxense']['cxense_accountid'] = array(
    '#title' => t('Account ID'),
    '#type' => 'textfield',
    '#default_value' => variable_get('cxense_accountid',''),
    '#size' => 60,
    '#maxlength' => 128,
    '#required' => TRUE,
    '#description' => t('Account ID on this site for Cxense'),  
  );    
  $form['cxense']['cxense_siteid'] = array(
    '#title' => t('Site ID'),
    '#type' => 'textfield',
    '#default_value' => variable_get('cxense_siteid',''),
    '#size' => 50,
    '#maxlength' => 128,
    '#required' => TRUE,
    '#description' => t('Site ID on this site for Cxense'),  
  );    
  $form['cxense']['cxense_track'] = array(
    '#title' => t('Tracking events'),
    '#type' => 'textfield',
    '#default_value' => variable_get('cxense_track','sendPageViewEvent'),
    '#size' => 50,
    '#maxlength' => 255,
    '#required' => TRUE,
    '#description' => t('Add events tracking according to Cxense API, separate each one by a comma, Default: ["sendPageViewEvent"]'),  
  );    
  return system_settings_form($form);
}
/**
 * Implements _form_validate().
 */
function cxense_admin_settings_form_validate($form, &$form_state) {
  // Trim some text values.
  $form_state['values']['cxense_accountid'] = trim($form_state['values']['cxense_accountid']);
  //Valid a field value or catch error
  if(!isset($form_state['values']['cxense_accountid']) || empty($form_state['values']['cxense_accountid'])){
    form_set_error('cxense_accountid', t('You need to provide ac account ID.'));
  }
  // Trim some text values.
  $form_state['values']['cxense_siteid'] = trim($form_state['values']['cxense_siteid']);
  //Valid a field value or catch error
  if(!isset($form_state['values']['cxense_siteid']) || empty($form_state['values']['cxense_siteid'])){
    form_set_error('cxense_siteid', t('You need to provide a site ID.'));
  }
  $form_state['values']['cxense_track'] = trim($form_state['values']['cxense_track']);
  //Valid a field value or catch error
  if(!isset($form_state['values']['cxense_track']) || empty($form_state['values']['cxense_track'])){
    form_set_error('cxense_track', t('You need to provide at least one event.'));
  }
}
/**
 * Implements _form_submit().
 */
function cxense_admin_settings_form_submit($form, &$form_state){
  //Save values
  variable_set('cxense_status',$form_state['values']['cxense_status']);
  variable_set('cxense_accountid',$form_state['values']['cxense_accountid']);
  variable_set('cxense_siteid',$form_state['values']['cxense_siteid']);
  variable_set('cxense_track',$form_state['values']['cxense_track']);
}
