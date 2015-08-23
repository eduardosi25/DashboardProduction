<?php
/**
 * @file
 * Administrative page callbacks for the Play Integration module.
 */
/**
 * Implements hook_admin_settings() for module settings configuration.
 */
function sipi_users_admin_settings_form($form_state) {
  $form['#submit'][]='sipi_users_admin_settings_form_submit';
  $form['sipi_users'] = array(
    '#type' => 'fieldset',
    '#title' => t('SIPI Users Settings'),
  );
  $form['sipi_users']['sipi_users_status'] = array(
    '#title' => t('Enabled SIPI Users Registration'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('sipi_users_status',FALSE),
    '#description' => t('Enabled or disabled SIPI Users Registration'),
  );
  $roles = array_map('check_plain', user_roles(TRUE));
  // The disabled checkbox subelement for the 'authenticated user' role
  // must be generated separately and added to the checkboxes element,
  // because of a limitation in Form API not supporting a single disabled
  // checkbox within a set of checkboxes.
  // @todo This should be solved more elegantly. See issue #119038.
  $checkbox_authenticated = array(
    '#type' => 'checkbox',
    '#title' => $roles[DRUPAL_AUTHENTICATED_RID],
    '#default_value' => TRUE,
    '#disabled' => TRUE,
  );
  unset($roles[DRUPAL_AUTHENTICATED_RID]);
  $form['sipi_users']['sipi_users_role'] = array(
    '#title' => t('Select a valid Role for SIPI Users'),
    '#description' => t('You need to select a default role for SIPI Users'),
    '#type' => 'checkboxes',
    '#default_value' => variable_get('sipi_users_role',array()),
    '#options' => $roles,
    '#access' => $roles && user_access('administer users'),
    DRUPAL_AUTHENTICATED_RID => $checkbox_authenticated,
  );
  return system_settings_form($form);
}
/**
 * Implements _form_validate().
 */
function sipi_users_admin_settings_form_validate($form, &$form_state) {
  //Valid a field value or catch error
  if(!isset($form_state['values']['sipi_users_role']) || empty($form_state['values']['sipi_users_role'])){
    form_set_error('sipi_users_role', t('You need to select a valid role for SIPI Users.'));
  }else{
    $roles=array();
    foreach($form_state['values']['sipi_users_role'] as $key => $value){
      if(isset($value) && !empty($value)){
        $roles[$key]=intval($value);
      }
    }
    $form_state['values']['sipi_users_role']=$roles;
  }
}
/**
 * Implements _form_submit().
 */
function sipi_users_admin_settings_form_submit($form, &$form_state){
  //Save values
  variable_set('sipi_users_status',$form_state['values']['sipi_users_status']);
  variable_set('sipi_users_role',$form_state['values']['sipi_users_role']);
}
