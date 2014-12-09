<?php
/**
 * @file
 * Administrative page callbacks for the taboola module.
 */
/**
 * Implements hook_admin_settings() for module settings configuration.
 */
function taboola_admin_settings_form($form_state) {
  $form['#submit'][]='taboola_admin_settings_form_submit';
  $form['taboola'] = array(
    '#type' => 'fieldset',
    '#title' => t('Taboola settings'),
  );
  $form['taboola']['taboola_status'] = array(
    '#title' => t('Enabled Taboola Integration'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('taboola_status',FALSE),
    '#description' => t('Enabled or disabled Taboola Integration'),  
  );    
  $form['taboola']['taboola_loadername'] = array(
    '#title' => t('Loader name'),
    '#type' => 'textfield',
    '#default_value' => variable_get('taboola_loadername',''),
    '#size' => 60,
    '#maxlength' => 100,
    '#required' => TRUE,
    '#description' => t('Loader name, normally from the domain name'),  
  );    
  $form['taboola']['taboola_regionname'] = array(
    '#title' => t('Region name'),
    '#type' => 'textfield',
    '#default_value' => variable_get('taboola_regionname',''),
    '#size' => 40,
    '#maxlength' => 32,
    '#required' => TRUE,
    '#description' => t('Set the region name for the Taboola Integration Block. Remember to change weight on their region on Admin > Structure > <a href="@url">Blocks</a>.', array('@url' => '/admin/structure/block')),  
  );    
  return system_settings_form($form);
}
/**
 * Implements _form_validate().
 */
function taboola_admin_settings_form_validate($form, &$form_state) {
  // Trim some text values.
  $form_state['values']['taboola_loadername'] = trim($form_state['values']['taboola_loadername']);
  //Valid a field value or catch error
  if(!isset($form_state['values']['taboola_loadername']) || empty($form_state['values']['taboola_loadername'])){
    form_set_error('taboola_loadername', t('You need to provide a loader name.'));
  }
  // Trim some text values.
  $form_state['values']['taboola_regionname'] = trim($form_state['values']['taboola_regionname']);
  //Valid a field value or catch error
  if(!isset($form_state['values']['taboola_regionname']) || empty($form_state['values']['taboola_regionname'])){
    form_set_error('taboola_regionname', t('You need to provide a region name.'));
  }
}
/**
 * Implements _form_submit().
 */
function taboola_admin_settings_form_submit($form, &$form_state){
  //Save values
  variable_set('taboola_status',$form_state['values']['taboola_status']);
  variable_set('taboola_loadername',$form_state['values']['taboola_loadername']);
  variable_set('taboola_regionname',$form_state['values']['taboola_regionname']);
}
