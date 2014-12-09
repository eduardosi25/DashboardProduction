<?php
/**
 * @file
 * Administrative page callbacks for the digiteka module.
 */
/**
 * Implements hook_admin_settings() for module settings configuration.
 */
function digiteka_admin_settings_form($form_state) {
  /**
   * Check if it is adrenalina form
   */
  $path=arg(4);
  //Get values
  if($path=='adrenalina'){
    $status=variable_get('digiteka_status_adrenalina',FALSE);
    $settings=variable_get('digiteka_settings_adrenalina', NULL);
  }else{
    $status=variable_get('digiteka_status',FALSE);
    $settings=variable_get('digiteka_settings', NULL);
  }

  $form['#submit'][]='digiteka_admin_settings_form_submit';
  $form['digiteka'] = array(
    '#type' => 'fieldset',
    '#title' => t('Digiteka'),
  );

  $form['digiteka']['digiteka_status'] = array(
    '#title' => t('Enabled Digiteka Integration'),
    '#type' => 'checkbox',
    '#default_value' => $status,
    '#description' => t('Enabled or disabled Digiteka Integration'),
  );

  $form['digiteka']['digiteka_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Settings'),
    '#tree' => TRUE,
  );

  $form['digiteka']['digiteka_settings']['mdtk'] = array(
    '#title' => t('MDTK Number provider by site (Digiteka send this number)'),
    '#type' => 'textfield',
    '#default_value' => isset($settings['mdtk']) && !empty($settings['mdtk']) ? $settings['mdtk'] : '09847474',
    '#size' => 80,
    '#maxlength' => 20,
    '#description' => t('You need to provide a valid MDTK number. <b>If you have any question, please contact the administrator.</b> <em>Default number 09847474 is for Excelsior.com.mx</em>.'),
  );

  $form['digiteka']['digiteka_settings']['zone'] = array(
    '#title' => t('Zone number provider by site && with segmentation purpose (Digiteka send this number)'),
    '#type' => 'textfield',
    '#default_value' => isset($settings['zone']) && !empty($settings['zone']) ? $settings['zone'] : '0',
    '#size' => 80,
    '#maxlength' => 3,
    '#description' => t('You need to provide a valid ZONE number. <b>If you have any question, please contact the administrator.</b> <em>Default number 0 is for all sections</em>.'),
  );

  $form['digiteka']['digiteka_settings']['target'] = array(
    '#title' => t('HTML target wrapper name'),
    '#type' => 'textfield',
    '#default_value' => isset($settings['target']) && !empty($settings['target']) ? $settings['target'] : 'ultimedia_wrapper',
    '#size' => 80,
    '#maxlength' => 255,
    '#description' => t('You need to provide a valid MDTK number. If you have any question, please contact the administrator.'),
  );

  $form['digiteka']['digiteka_settings']['date'] = array(
    '#title' => t('Published or Updated Date'),
    '#type' => 'select',
    '#default_value' => isset($settings['date']) && !empty($settings['date']) ? $settings['date'] : 'node->created',
    '#options' => array(
      'created' => 'Publish Date',
      'changed' => 'Last Update Date'
    ),
    '#description' => t('Indicate the correct ObjectField from Node for Publish or Update Dates. Created or Changed are possible.'),
  );

  $form['digiteka']['digiteka_settings']['async'] = array(
    '#title' => t('Enabled Async Integration'),
    '#type' => 'checkbox',
    '#default_value' => $settings['async'],
    '#description' => t('Enabled or disabled Digiteka Async Integration'),
  );

  $form['digiteka']['digiteka_settings']['resize'] = array(
    '#title' => t('Enabled Resize Integration'),
    '#type' => 'checkbox',
    '#default_value' => $settings['resize'],
    '#description' => t('Enabled or disabled Digiteka Resize Integration'),
  );

  $form['digiteka']['digiteka_settings']['title'] = array(
    '#title' => t('HTML title wrapper code'),
    '#type' => 'textfield',
    '#default_value' => isset($settings['title']) && !empty($settings['title']) ? $settings['title'] : '<h4 id="article-related-node-title" class="spriteFull">Video Recomendado</h4>',
    '#size' => 200,
    '#maxlength' => 255,
    '#description' => t('You need to provide a valid HTML wrapper code title.'),
  );

  return system_settings_form($form);
}
/**
 * Implements _form_validate().
 */
function digiteka_admin_settings_form_validate($form, &$form_state) {
  //Valid a field value or catch error
  if(!isset($form_state['values']['digiteka_settings']['mdtk']) || empty($form_state['values']['digiteka_settings']['mdtk'])){
    form_set_error('digiteka_settings][mdtk', t('You need to provide a valid MDTK Number'));
  }
  if(!isset($form_state['values']['digiteka_settings']['target']) || empty($form_state['values']['digiteka_settings']['target'])){
    form_set_error('digiteka_settings][target', t('You need to provide a valid target value'));
  }
}
/**
 * Implements _form_submit().
 */
function digiteka_admin_settings_form_submit($form, &$form_state){
  /**
   * Check if it is adrenalina form
   */
  $path=arg(4);
  //Save values
  if($path=='adrenalina'){
    variable_set('digiteka_status_adrenalina',$form_state['values']['digiteka_status']);
    variable_set('digiteka_settings_adrenalina',$form_state['values']['digiteka_settings']);
  }else{
    variable_set('digiteka_status',$form_state['values']['digiteka_status']);
    variable_set('digiteka_settings',$form_state['values']['digiteka_settings']);
  }
}
