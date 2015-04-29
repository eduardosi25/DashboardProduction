<?php
/**
 * @file
 * Administrative page callbacks for the Play Feeds Integration module.
 */
/**
 * Implements hook_admin_settings() for module settings configuration.
 */
function play_feeds_admin_settings_form($form_state) {
  $form['#submit'][]='play_feeds_admin_settings_form_submit';
  $form['play_feeds'] = array(
    '#type' => 'fieldset',
    '#title' => t('play_feeds settings'),
  );
  $form['play_feeds']['play_feeds_status'] = array(
    '#title' => t('Enabled play_feeds Integration'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('play_feeds_status',FALSE),
    '#description' => t('Enabled or disabled play_feeds Integration'),
  );
  $form['play_feeds']['play_feeds_debug'] = array(
    '#title' => t('Enabled debug mode'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('play_feeds_debug',FALSE),
    '#description' => t('Enabled or disabled debug mode'),
  );    
  $form['play_feeds']['play_feeds_wrapper'] = array(
    '#title' => t('play_feeds Wrapper ID'),
    '#type' => 'textfield',
    '#default_value' => variable_get('play_feeds_wrapper','play_feeds-wrapper'),
    '#size' => 60,
    '#maxlength' => 100,
    '#required' => TRUE,
    '#description' => t('play_feeds wrapper ID'),
  );    
  return system_settings_form($form);
}
/**
 * Implements _form_validate().
 */
function play_feeds_admin_settings_form_validate($form, &$form_state) {
  // Trim some text values.
  $form_state['values']['play_feeds_wrapper'] = trim($form_state['values']['play_feeds_wrapper']);
  //Valid a field value or catch error
  if(!isset($form_state['values']['play_feeds_wrapper']) || empty($form_state['values']['play_feeds_wrapper'])){
    form_set_error('play_feeds_wrapper', t('You need to provide a wrapper ID name.'));
  }
}
/**
 * Implements _form_submit().
 */
function play_feeds_admin_settings_form_submit($form, &$form_state){
  //Save values
  variable_set('play_feeds_status',$form_state['values']['play_feeds_status']);
  variable_set('play_feeds_debug',$form_state['values']['play_feeds_debug']);
  variable_set('play_feeds_wrapper',$form_state['values']['play_feeds_wrapper']);
}
