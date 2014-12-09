<?php
/**
 * @file
 * Administrative page callbacks for the legales module.
 */
/**
 * Implements hook_admin_settings() for module settings configuration.
 */
function legales_admin_settings_form($form_state) {
  $form['#submit'][]='legales_admin_settings_form_submit';
  $form['legales'] = array(
    '#type' => 'fieldset',
    '#title' => t('Legales settings'),
  );
  $form['legales']['legales_privacy'] = array(
    '#title' => t('URL Aviso de privacidad'),
    '#type' => 'textfield',
    '#default_value' => variable_get('legales_privacy',''),
    '#size' => 100,
    '#maxlength' => 255,
    '#required' => TRUE,
    '#description' => t('URL para lectura del HTML del Aviso de Privacidad'),  
  );    
  $form['legales']['legales_terms'] = array(
    '#title' => t('URL Términos y condiciones de uso'),
    '#type' => 'textfield',
    '#default_value' => variable_get('legales_terms',''),
    '#size' => 100,
    '#maxlength' => 255,
    '#required' => TRUE,
    '#description' => t('URL para lectura del HTML de los Términos y Condiciones de Uso'),  
  );    
  $form['legales']['legales_environmental'] = array(
    '#title' => t('URL Política Ambiental'),
    '#type' => 'textfield',
    '#default_value' => variable_get('legales_environmental',''),
    '#size' => 100,
    '#maxlength' => 255,
    '#required' => TRUE,
    '#description' => t('URL para lectura del HTML de la Política Ambiental'),  
  );    
  return system_settings_form($form);
}
/**
 * Implements _form_validate().
 */
function legales_admin_settings_form_validate($form, &$form_state) {
  // Trim some text values.
  $form_state['values']['legales_privacy'] = trim($form_state['values']['legales_privacy']);
  //Valid a field value or catch error
  if(!isset($form_state['values']['legales_privacy']) || empty($form_state['values']['legales_privacy'])){
    form_set_error('legales_privacy', t('Necesitas agregar una URL para el Aviso de Privacidad.'));
  }
  // Trim some text values.
  $form_state['values']['legales_terms'] = trim($form_state['values']['legales_terms']);
  //Valid a field value or catch error
  if(!isset($form_state['values']['legales_terms']) || empty($form_state['values']['legales_terms'])){
    form_set_error('legales_terms', t('Necesitas agregar una URL para los Términos y Condiciones de Uso.'));
  }
  // Trim some text values.
  $form_state['values']['legales_environmental'] = trim($form_state['values']['legales_environmental']);
  //Valid a field value or catch error
  if(!isset($form_state['values']['legales_environmental']) || empty($form_state['values']['legales_environmental'])){
    form_set_error('legales_environmental', t('Necesitas agregar una URL para la Política Ambiental.'));
  }
}
/**
 * Implements _form_submit().
 */
function legales_admin_settings_form_submit($form, &$form_state){
  //Save values
  variable_set('legales_privacy',$form_state['values']['legales_privacy']);
  variable_set('legales_terms',$form_state['values']['legales_terms']);
  variable_set('legales_environmental',$form_state['values']['legales_environmental']);
  
  //Delete cache files
  legales_flush_cache();
}
function legales_flush_cache(){
  $path=DRUPAL_ROOT.'/'.variable_get('file_public_path','').'/legales/';
  $files=array('aviso-de-privacidad.html','terminos-y-condiciones-de-uso.html','politica-ambiental.html');
  foreach($files as $file){
    $filename=$path.$file;
    if(file_exists($filename)){
      unlink($filename);
    }
  }
}
