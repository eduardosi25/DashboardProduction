<?php
/**
 * @file
 * Administrative page callbacks for the imx_dax module.
 */
/**
 * Implements hook_admin_settings() for module settings configuration.
 */
function imx_dax_admin_settings_form($form_state) {
  $form['#submit'][]='imx_dax_admin_settings_form_submit';
  $form['imx_dax'] = array(
    '#type' => 'fieldset',
    '#title' => t('DAX Comscore settings'),
  );
  $form['imx_dax']['imx_dax_status'] = array(
    '#title' => t('Enabled DAX Comscore Integration'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('imx_dax_status',FALSE),
    '#description' => t('Enabled or disabled DAX Comscore Integration'),  
  );    
  $form['imx_dax']['imx_dax_loadername'] = array(
    '#title' => t('Loader name'),
    '#type' => 'textfield',
    '#default_value' => variable_get('imx_dax_loadername',''),
    '#size' => 60,
    '#maxlength' => 100,
    '#required' => TRUE,
    '#description' => t('Loader name, normally from the domain name'),  
  );    
  $form['imx_dax']['imx_dax_regionname'] = array(
    '#title' => t('Region name'),
    '#type' => 'textfield',
    '#default_value' => variable_get('imx_dax_regionname',''),
    '#size' => 40,
    '#maxlength' => 32,
    '#required' => TRUE,
    '#description' => t('Set the region name for the imx_dax Integration Block. Remember to change weight on their region on Admin > Structure > <a href="@url">Blocks</a>.', array('@url' => '/admin/structure/block')),  
  );    
  return system_settings_form($form);
}
/**
 * Implements _form_validate().
 */
function imx_dax_admin_settings_form_validate($form, &$form_state) {
  // Trim some text values.
  $form_state['values']['imx_dax_loadername'] = trim($form_state['values']['imx_dax_loadername']);
  //Valid a field value or catch error
  if(!isset($form_state['values']['imx_dax_loadername']) || empty($form_state['values']['imx_dax_loadername'])){
    form_set_error('imx_dax_loadername', t('You need to provide a loader name.'));
  }
  // Trim some text values.
  $form_state['values']['imx_dax_regionname'] = trim($form_state['values']['imx_dax_regionname']);
  //Valid a field value or catch error
  if(!isset($form_state['values']['imx_dax_regionname']) || empty($form_state['values']['imx_dax_regionname'])){
    form_set_error('imx_dax_regionname', t('You need to provide a region name.'));
  }
}
/**
 * Implements _form_submit().
 */
function imx_dax_admin_settings_form_submit($form, &$form_state){
  //Save values
  variable_set('imx_dax_status',$form_state['values']['imx_dax_status']);
  variable_set('imx_dax_loadername',$form_state['values']['imx_dax_loadername']);
  variable_set('imx_dax_regionname',$form_state['values']['imx_dax_regionname']);
}
