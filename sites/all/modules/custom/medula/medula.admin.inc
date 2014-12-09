<?php
/**
 * @file
 * Administrative page callbacks for the medula module.
 */
/**
 * Implements hook_admin_settings() for module settings configuration.
 */
function medula_admin_settings_form($form_state) {
  $form['#submit'][]='medula_admin_settings_form_submit';
  $form['medula'] = array(
    '#type' => 'fieldset',
    '#title' => t('Medula settings'),
  );
  $form['medula']['medula_status'] = array(
    '#title' => t('Enabled Medula Integration'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('medula_status',FALSE),
    '#description' => t('Enabled or disabled Medula Integration'),  
  );    
  $form['medula']['medula_debug'] = array(
    '#title' => t('Debugging Medula Integration'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('medula_debug',FALSE),
    '#description' => t('Enabled or disabled Debugging Medula Integration. Remember to disabled this field when this module are on Production'),  
  );    
  $form['medula']['medula_sitename'] = array(
    '#title' => t('Site name'),
    '#type' => 'textfield',
    '#default_value' => variable_get('medula_sitename',''),
    '#size' => 60,
    '#maxlength' => 100,
    '#required' => TRUE,
    '#description' => t('Site name, normally from the domain name'),  
  );    
  $form['medula']['medula_seccionname'] = array(
    '#title' => t('Seccion name'),
    '#type' => 'textfield',
    '#default_value' => variable_get('medula_seccionname',''),
    '#size' => 40,
    '#maxlength' => 32,
    '#required' => TRUE,
    '#description' => t('Set the seccion name for the Medula Integration Block. Remember to change position on their region on Admin > Structure > <a href="@url">Blocks</a>.', array('@url' => '/admin/structure/block')),  
  );    
  return system_settings_form($form);
}
/**
 * Implements _form_validate().
 */
function medula_admin_settings_form_validate($form, &$form_state) {
  // Trim some text values.
  $form_state['values']['medula_sitename'] = trim($form_state['values']['medula_sitename']);
  //Valid a field value or catch error
  if(!isset($form_state['values']['medula_sitename']) || empty($form_state['values']['medula_sitename'])){
    form_set_error('medula_sitename', t('You need to provide a site name.'));
  }
  // Trim some text values.
  $form_state['values']['medula_seccionname'] = trim($form_state['values']['medula_seccionname']);
  //Valid a field value or catch error
  if(!isset($form_state['values']['medula_seccionname']) || empty($form_state['values']['medula_seccionname'])){
    form_set_error('medula_seccionname', t('You need to provide a seccion name.'));
  }
}
/**
 * Implements _form_submit().
 */
function medula_admin_settings_form_submit($form, &$form_state){
  //Save values
  variable_set('medula_status',$form_state['values']['medula_status']);
  variable_set('medula_debug',$form_state['values']['medula_debug']);
  variable_set('medula_sitename',$form_state['values']['medula_sitename']);
  variable_set('medula_seccionname',$form_state['values']['medula_seccionname']);
}
