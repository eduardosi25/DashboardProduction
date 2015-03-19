<?php
/**
 * @file
 * Administrative page callbacks for the sipi module.
 */
/**
 * Implements hook_admin_settings() for module settings configuration.
 */
function sipi_admin_settings_form($form_state) {
  $form['#submit'][]='sipi_admin_settings_form_submit';
  $form['sipi'] = array(
    '#type' => 'fieldset',
    '#title' => t('SIPI Settings'),
  );
  $form['sipi']['sipi_status'] = array(
    '#title' => t('Enabled SIPI Integration'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('sipi_status',FALSE),
    '#description' => t('Enabled or disabled SIPI Integration'),
  );
  /**
   * Settings
   */
  $settings=variable_get('sipi_settings',NULL);
  $form['sipi']['settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Skin Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => variable_get('sipi_status', FALSE),
  );
  $form['sipi']['settings']['apikey'] = array(
    '#title' => t('API Key Background Imagen for Skin'),
    '#type' => 'textfield',
    '#default_value' => isset($skin['url']) ? $skin['url'] : '',
    '#size' => 150,
    '#maxlength' => 254,
    '#description' => t('Set url logo.  If the image are a greek, please dont forget to put repeated On'),
  );
  $form['sipi']['settings']['skin_repeat'] = array(
    '#title' => t('Background repeated'),
    '#type' => 'checkbox',
    '#default_value' => isset($skin['repeat']) ? $skin['repeat'] : FALSE,
    '#description' => t('Background repeat. <a href="@url" target="@target">CSS background-repeat Property</a>.', array('@url' => 'http://www.w3schools.com/cssref/pr_background-repeat.asp', '@target' => '_blank')),
  );
  $form['sipi']['settings']['skin_position_left'] = array(
    '#title' => t('Position background left'),
    '#type' => 'textfield',
    '#default_value' => isset($skin['position_left']) ? $skin['position_left'] : 'center',
    '#size' => 15,
    '#maxlength' => 32,
    '#description' => t('Position left. <a href="@url" target="@target">CSS background-position Property</a>', array('@url' => 'http://www.w3schools.com/cssref/pr_background-position.asp', '@target' => '_blank')),
  );
  $form['sipi']['settings']['skin_position_top'] = array(
    '#title' => t('Position background top'),
    '#type' => 'textfield',
    '#default_value' => isset($skin['position_top']) ? $skin['position_top'] : 'top',
    '#size' => 15,
    '#maxlength' => 32,
    '#description' => t('Position top. <a href="@url" target="@target">CSS background-position Property</a>', array('@url' => 'http://www.w3schools.com/cssref/pr_background-position.asp', '@target' => '_blank')),
  );
  $form['sipi']['settings']['skin_color'] = array(
    '#title' => t('Color background'),
    '#type' => 'textfield',
    '#default_value' => isset($skin['color']) ? $skin['color'] : '#FFFFFF',
    '#size' => 15,
    '#maxlength' => 32,
    '#description' => t('Color #AAAAAA. <a href="@url" target="@target">CSS background-color Property</a>', array('@url' => 'http://www.w3schools.com/cssref/pr_background-color.asp', '@target' => '_blank')),
  );

  return system_settings_form($form);
}
/**
 * Implements _form_validate().
 */
function sipi_admin_settings_form_validate($form, &$form_state) {
  //Valid a field value or catch error
  if(!isset($form_state['values']['sipi_token']) || empty($form_state['values']['sipi_token'])){
    form_set_error('sipi_token', t('You need to provide a valid Key.'));
  }
}
/**
 * Implements _form_submit().
 */
function sipi_admin_settings_form_submit($form, &$form_state){
  //Save values
  variable_set('sipi_status',$form_state['values']['sipi_status']);
  /**
   * Skin
   */
  #if(isset($form_state['values']['skin_url']) && !empty($form_state['values']['skin_url'])){
    $settings=array(
      'debug'        => $form_state['values']['skin_url'],
      'apikey'        => $form_state['values']['skin_url'],
      'repos'         => $form_state['values']['skin_repeat'],
      'frequency'     => $form_state['values']['skin_position_left'],
      'position_top'  => $form_state['values']['skin_position_top'],
      'color'         => $form_state['values']['skin_color'],
    );
    variable_set('sipi_settings',$settings);
  #

  //Clear cache
  cache_clear_all('sipi_variables', 'cache');
}
