<?php
/**
 * @file
 * Administrative page callbacks for the pandg module.
 */
/**
 * Implements hook_admin_settings() for module settings configuration.
 */
function pandg_admin_settings_form($form_state) {
  $form['#submit'][]='pandg_admin_settings_form_submit';
  $form['pandg'] = array(
    '#type' => 'fieldset',
    '#title' => t('P&G Integration Settings'),
  );
  $form['pandg']['pandg_status'] = array(
    '#title' => t('Enabled P&G Integration'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('pandg_status',FALSE),
    '#description' => t('Enabled or disabled P&G Integration'),
  );
  $form['pandg']['pandg_debug'] = array(
    '#title' => t('Debugging P&G Integration'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('pandg_debug',FALSE),
    '#description' => t('Enabled or disabled Debugging P&G Integration. Remember to disabled this field when this module are on Production'),
  );
  $form['pandg']['pandg_partnername'] = array(
    '#title' => t('Partner name'),
    '#type' => 'textfield',
    '#default_value' => variable_get('pandg_partnername',''),
    '#size' => 60,
    '#maxlength' => 100,
    '#required' => TRUE,
    '#description' => t('Partner name, this apply for all network'),
  );
  $form['pandg']['pandg_sendcategory'] = array(
    '#title' => t('Send Category Name'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('pandg_sendcategory',FALSE),
    '#description' => t('Enabled or disabled sending Category Name to P&G Integration Tag Script.'),
  );
  $form['pandg']['pandg_vocabulary'] = array(
    '#title' => t('Vocabulary'),
    '#type' => 'select',
    '#default_value' => variable_get('pandg_vocabulary',0),
    '#options' => _get_vocabulary(),
    '#description' => t('Select one option of Vocabulary to send as Category. Maybe this change on future'),
  );
  return system_settings_form($form);
}
/**
 * Implements _form_validate().
 */
function pandg_admin_settings_form_validate($form, &$form_state) {
  // Trim some text values.
  $form_state['values']['pandg_partnername'] = trim($form_state['values']['pandg_partnername']);
  //Valid a field value or catch error
  if(!isset($form_state['values']['pandg_partnername']) || empty($form_state['values']['pandg_partnername'])){
    form_set_error('pandg_partnername', t('You need to provide a partner name.'));
  }
}
/**
 * Implements _form_submit().
 */
function pandg_admin_settings_form_submit($form, &$form_state){
  //Save values
  variable_set('pandg_status',$form_state['values']['pandg_status']);
  variable_set('pandg_debug',$form_state['values']['pandg_debug']);
  variable_set('pandg_partnername',$form_state['values']['pandg_partnername']);
  variable_set('pandg_sendcategory',$form_state['values']['pandg_sendcategory']);
  variable_set('pandg_vocabulary',$form_state['values']['pandg_vocabulary']);
}

function _get_vocabulary(){
  $vocabulary=taxonomy_get_vocabularies();
  $items[0]=t('Ninguno');
  foreach($vocabulary as $tid => $term){
    $items[$tid]=$term->name;
  }
  return $items;
}