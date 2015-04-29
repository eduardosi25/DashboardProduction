<?php
/**
 * @file
 * Administrative page callbacks for the Play Web Integration module.
 */
/**
 * Implements hook_admin_settings() for module settings configuration.
 */
function play_web_admin_settings_form($form_state) {
  $form['#submit'][]='play_web_admin_settings_form_submit';
  $form['play_web'] = array(
    '#type' => 'fieldset',
    '#title' => t('play_web settings'),
  );
  $form['play_web']['play_web_status'] = array(
    '#title' => t('Enabled play_web Integration'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('play_web_status',FALSE),
    '#description' => t('Enabled or disabled play_web Integration'),
  );
  $form['play_web']['play_web_debug'] = array(
    '#title' => t('Enabled debug mode'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('play_web_debug',FALSE),
    '#description' => t('Enabled or disabled debug mode'),
  );    
  $form['play_web']['play_web_wrapper'] = array(
    '#title' => t('play_web Wrapper ID'),
    '#type' => 'textfield',
    '#default_value' => variable_get('play_web_wrapper','play_web-wrapper'),
    '#size' => 60,
    '#maxlength' => 100,
    '#required' => TRUE,
    '#description' => t('play_web wrapper ID'),
  );    
  return system_settings_form($form);
}
/**
 * Implements _form_validate().
 */
function play_web_admin_settings_form_validate($form, &$form_state) {
  // Trim some text values.
  $form_state['values']['play_web_wrapper'] = trim($form_state['values']['play_web_wrapper']);
  //Valid a field value or catch error
  if(!isset($form_state['values']['play_web_wrapper']) || empty($form_state['values']['play_web_wrapper'])){
    form_set_error('play_web_wrapper', t('You need to provide a wrapper ID name.'));
  }
}
/**
 * Implements _form_submit().
 */
function play_web_admin_settings_form_submit($form, &$form_state){
  //Save values
  variable_set('play_web_status',$form_state['values']['play_web_status']);
  variable_set('play_web_debug',$form_state['values']['play_web_debug']);
  variable_set('play_web_wrapper',$form_state['values']['play_web_wrapper']);
}
