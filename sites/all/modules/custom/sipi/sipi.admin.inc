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
  $status=variable_get('sipi_status',FALSE);
  $form['sipi']['sipi_status'] = array(
    '#title' => t('Enabled SIPI Integration'),
    '#type' => 'checkbox',
    '#default_value' => $status,
    '#description' => t('Enabled or disabled SIPI Integration'),
  );
  /**
   * Settings for SIPI
   * @see http://api.inventmx.com/v1/gamedots/sipi.json/3a5877fc16b6fcbf8eedbe55d091938a
   * @see http://api.inventmx.com/v1/gamedots/sipi-analytics.json/3a5877fc16b6fcbf8eedbe55d091938a
   * @see http://api.inventmx.com/v1/gamedots/sipi.json/3a5877fc16b6fcbf8eedbe55d091938a?limit=1&name=Gameloft
   * @see http://api.inventmx.com/v1/gamedots/sipi-analytics.json/3a5877fc16b6fcbf8eedbe55d091938a?limit=1&name=Gameloft
   */
  $settings=variable_get('sipi_settings',NULL);
  $form['sipi']['sipi_settings'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
    '#title' => t('SIPI Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => variable_get('sipi_status', FALSE),
  );
  $form['sipi']['sipi_settings']['debug'] = array(
    '#title' => t('Debug'),
    '#type' => 'checkbox',
    '#default_value' => isset($settings['debug']) ? $settings['debug'] : FALSE,
    '#description' => t('Enabled debug mode'),
  );
  $form['sipi']['sipi_settings']['token'] = array(
    '#title' => t('Token Access API Invent'),
    '#type' => 'textfield',
    '#default_value' => isset($settings['token']) ? $settings['token'] : '339fd1e0444ddbbd4d4528d8df161108',
    '#size' => 150,
    '#maxlength' => 254,
  );
  $form['sipi']['sipi_settings']['sites'] = array(
    '#title' => t('Select the sites with SIPI Users'),
    '#type' => 'checkboxes',
    '#options' => array(
      "atraccion360"   => "Atraccion360"  ,
      "salud180"       => "Salud180"      ,
      "imagen"         => "Imagen Radio"  ,
      "cadenatres"     => "CadenaTres"    ,
      "actitudfem"     => "ActitudFEM"    ,
      "dineroenimagen" => "DineroenImagen",
      "excelsior"      => "Excélsior"     ,
      "gamedots"       => "GameDots"      ,
      "reporte"        => "Reporte 98.5"  ,
      "melodijolola"   => "Melodijolola"  ,
      "rsvp"           => "RSVPOnline"    ,
      "estrategia45"   => "Estrategia45"  ,
      "adrenalina"     => "Adrenalina360" ,
      "garuyo"         => "Garuyo"        ,
      "hub-inventmx"   => "HUB-Invent.mx" ,
      "excelsior-tv"   => "Excélsior TV"  ,
      "adrenalina360"  => "Adrenalina360" ,
      "swagger"        => "Swagger"       ,
      "inventmx"       => "Invent.mx"     ,
    ),
    '#default_value' => get_checked_options($settings['sites']),
  );
  return system_settings_form($form);
}
function get_checked_options($options){
  $items=array();
  foreach($options as $key=>$value){
    if($value){
      $items[]=$key;
    }
  }
  return $items;
}
/**
 * Implements _form_validate().
 */
function sipi_admin_settings_form_validate($form, &$form_state) {
  //Valid a field value or catch error
  if(!isset($form_state['values']['sipi_settings']['token']) || empty($form_state['values']['sipi_settings']['token'])){
    form_set_error('sipi_settings][token', t('You need to provide a valid Token Access API Key.'));
  }
}
/**
 * Implements _form_submit().
 */
function sipi_admin_settings_form_submit($form, &$form_state){
  //Save values
  variable_set('sipi_status',$form_state['values']['sipi_status']);
  /**
   * Settings
   */
  $settings=array(
    'debug' => $form_state['values']['sipi_settings']['debug'],
    'token' => $form_state['values']['sipi_settings']['token'],
    'sites' => $form_state['values']['sipi_settings']['sites'],
  );
  variable_set('sipi_settings',$settings);

  //Clear cache
  //cache_clear_all('sipi_variables', 'cache');
}
