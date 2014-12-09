<?php
/**
 * @file
 * Administrative page callbacks for the imagebrowser_legacy module.
 */
/**
 * Implements hook_admin_settings() for module settings configuration.
 */
function imagebrowser_legacy_admin_settings_form($form_state) {
  $form['#submit'][]='imagebrowser_legacy_admin_settings_form_submit';
  $form['imagebrowser_legacy'] = array(
    '#type' => 'fieldset',
    '#title' => t('imagebrowser_legacy settings'),
  );
  $form['imagebrowser_legacy']['imagebrowser_legacy_status'] = array(
    '#title' => t('Enabled imagebrowser_legacy Integration'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('imagebrowser_legacy_status',FALSE),
    '#description' => t('Enabled or disabled imagebrowser_legacy Integration'),  
  );    
  $form['imagebrowser_legacy']['imagebrowser_legacy_stylename'] = array(
    '#title' => t('Style name'),
    '#type' => 'textfield',
    '#default_value' => variable_get('imagebrowser_legacy_stylename',''),
    '#size' => 60,
    '#maxlength' => 100,
    '#required' => FALSE,
    '#description' => t('Style name, if not set or blank mean that return original image'),  
  );    
  return system_settings_form($form);
}

/**
 * Implements _form_submit().
 */
function imagebrowser_legacy_admin_settings_form_submit($form, &$form_state){
  //Save values
  variable_set('imagebrowser_legacy_status',$form_state['values']['imagebrowser_legacy_status']);
  variable_set('imagebrowser_legacy_stylename',$form_state['values']['imagebrowser_legacy_stylename']);
}
