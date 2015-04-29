<?php
/**
 * @file
 * Administrative page callbacks for the Play Integration module.
 */
/**
 * Implements hook_admin_settings() for module settings configuration.
 */
function play_admin_settings_form($form_state) {
  $form['#submit'][]='play_admin_settings_form_submit';
  $form['play'] = array(
    '#type' => 'fieldset',
    '#title' => t('play settings'),
  );
  $form['play']['play_status'] = array(
    '#title' => t('Enabled play Integration'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('play_status',FALSE),
    '#description' => t('Enabled or disabled play Integration'),
  );
  $form['play']['play_debug'] = array(
    '#title' => t('Enabled debug mode'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('play_debug',FALSE),
    '#description' => t('Enabled or disabled debug mode'),
  );    
  $form['play']['play_wrapper'] = array(
    '#title' => t('play Wrapper ID'),
    '#type' => 'textfield',
    '#default_value' => variable_get('play_wrapper','play-wrapper'),
    '#size' => 60,
    '#maxlength' => 100,
    '#required' => TRUE,
    '#description' => t('play wrapper ID'),
  );    
  return system_settings_form($form);
}
/**
 * Implements _form_validate().
 */
function play_admin_settings_form_validate($form, &$form_state) {
  // Trim some text values.
  $form_state['values']['play_wrapper'] = trim($form_state['values']['play_wrapper']);
  //Valid a field value or catch error
  if(!isset($form_state['values']['play_wrapper']) || empty($form_state['values']['play_wrapper'])){
    form_set_error('play_wrapper', t('You need to provide a wrapper ID name.'));
  }
}
/**
 * Implements _form_submit().
 */
function play_admin_settings_form_submit($form, &$form_state){
  //Save values
  variable_set('play_status',$form_state['values']['play_status']);
  variable_set('play_debug',$form_state['values']['play_debug']);
  variable_set('play_wrapper',$form_state['values']['play_wrapper']);
}
