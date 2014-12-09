<?php
/**
 * @file
 * Administrative page callbacks for the ovni module.
 */
/**
 * Manage actions for OVNI Integration
 * @param string $action
 * @return string
 */
function ovni_admin_actions($action='manage'){
  switch($action){
    case 'manage':
    case 'tasks':
    case 'cache':
    case 'api':
      $action=call_user_func('ovni_admin_'.$action);
    break;
  }
  return $action;
}
/**
 * Manage OVNI Integration
 */
function ovni_admin_manage(){
  $html='
<h1>Manage</h1>
<section>
<div>Div</div>
<p>Parrafo</p>
<p>Parrafo <span>Spaneado</span></p>
</section>
';
  return $html;
}
/**
 * Manage Tasks for OVNI
 */
function ovni_admin_tasks(){
  return;
}
/**
 * Manage Cache for OVNI
 */
function ovni_admin_cache(){
  return;
}
/**
 * Manage API for OVNI
 */
function ovni_admin_api(){
}

/**
 * Implements hook_admin_settings() for module settings configuration.
 */
function ovni_player_admin_settings_form($form_state) {
  $ovni_player=variable_get('ovni_player', array());
  $form['#submit'][]='ovni_player_admin_settings_form_submit';
  $form['ovni_player'] = array(
    '#type' => 'fieldset',
    '#title' => t('OVNI Player'),
  );
  $delta=0;
  $form['ovni_player']['ovni_player']['#tree'] = TRUE;
  $form['ovni_player']['ovni_player']['src'] = array(
    '#title' => t('Source or Resource Script of Player for OVNI Integration'),
    '#type' => 'textfield',
    '#default_value' => isset($ovni_player['src']) && !empty($ovni_player['src']) ? $ovni_player['src'] : '',
    '#size' => 80,
    '#maxlength' => 255,
    '#description' => t('You need to provide with a full URL for load source or resources for the player like JWPlayer. If you have any question, please contact the administrator.'),
  );
  $form['ovni_player']['ovni_player']['code'] = array(
    '#title' => t('Add Player for OVNI Integration'),
    '#type' => 'textarea',
    '#cols' => 80,
    '#rows' => 20,
    '#attributes' => array(
      'style' => 'font-family:"Courier","Times New Roman";font-size:1.2em;',
    ),
    '#default_value' => isset($ovni_player['code']) && !empty($ovni_player['code']) ? $ovni_player['code'] : '',
    '#description' => t('You need to add a valid player script tag like JWPlayer. Make sure that you consider everything to use this script in substitution of Youtube Player. If you have any question, please contact the administrator.'),
  );
  return system_settings_form($form);
}
/**
 * Implements _form_validate().
 */
function ovni_player_admin_settings_form_validate($form, &$form_state) {
  //Valid a field value or catch error
  if(!isset($form_state['values']['ovni_player']['src']) || empty($form_state['values']['ovni_player']['src'])){
    form_set_error('ovni_player][src', t('You need to provide a valid player script resource or source tag. If you don\'t know it contact the administrator.'));
  }
  //Valid a field value or catch error
  if(!isset($form_state['values']['ovni_player']['code']) || empty($form_state['values']['ovni_player']['code'])){
    form_set_error('ovni_player][code', t('You need to provide a valid player script tag. Take care about placeholders.'));
  }
}

/**
 * Implements _form_submit().
 */
function ovni_player_admin_settings_form_submit($form, &$form_state){
  //Save values
  variable_set('ovni_player',$form_state['values']['ovni_player']);
}


function jwplayer_html(){
  $player=variable_get('ovni_player',array());
  $placeholders=array();
  foreach($player as $key => $value){
    $placeholders['@'.$key]=$value;
  }
  $html='
<div id="@playerid"></div>
<script type="text/javascript">
  jwplayer("@playerid").setup({
    file        : "@stream",
    image       : "@poster",
    title       : "@title",
    width       : "@width",
    aspectratio : "@aspect",
    skin        : "@skin",
    primary     : "@primary",
    ga          : "{}",
    advertising : {
      client     : "vast",
      tag        : "@vast",
      admessage  : "@admessage",
      skipoffset : "@skiptime"
    }
  });
</script>';

  return format_string($html, $placeholders);

}



/**
 * Implements hook_admin_settings() for module settings configuration.
 */
function ovni_admin_settings_form($form_state) {
  $ovni_status=variable_get('ovni_status', FALSE);
  $collapsed=$ovni_status ? TRUE : FALSE;
  $youtube=variable_get('ovni_youtube',array());

  $form['#submit'][]='ovni_admin_settings_form_submit';
  $form['ovni'] = array(
    '#type' => 'fieldset',
    '#title' => t('OVNI Settings'),
  );
  $form['ovni']['ovni_status'] = array(
    '#title' => t('Enabled OVNI Integration'),
    '#type' => 'checkbox',
    '#default_value' => $ovni_status,
    '#description' => t('Enabled or disabled OVNI Integration'),
  );
  $form['ovni']['ovni_youtube'] = array(
    '#type' => 'fieldset',
    '#title' => t('Youtube Settings API'),
    '#tree' => TRUE,
  );
  $form['ovni']['ovni_youtube']['projectid'] = array(
    '#title' => t('Project ID'),
    '#type' => 'textfield',
    '#default_value' => isset($youtube['projectid']) && !empty($youtube['projectid']) ? $youtube['projectid'] : '',
    '#size' => 60,
    '#maxlength' => 128,
    '#description' => t('Project ID for API APP. See <a href="@url" _target="@target">Google Console</a>',array('@url'=>'https://console.developers.google.com/','@target'=>'_blank')),
  );
  $form['ovni']['ovni_youtube']['projectnumber'] = array(
    '#title' => t('Project Number'),
    '#type' => 'textfield',
    '#default_value' => isset($youtube['projectnumber']) && !empty($youtube['projectnumber']) ? $youtube['projectnumber'] : '',
    '#size' => 60,
    '#maxlength' => 128,
  );
  $form['ovni']['ovni_youtube']['apikey'] = array(
    '#title' => t('API Key'),
    '#type' => 'textfield',
    '#default_value' => isset($youtube['apikey']) && !empty($youtube['apikey']) ? $youtube['apikey'] : '',
    '#size' => 60,
    '#maxlength' => 128,
  );
  $form['ovni']['ovni_youtube']['oauth'] = array(
    '#type' => 'fieldset',
    '#title' => t('Youtube OAuth Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => $collapsed,
    '#tree' => TRUE,
  );
  $form['ovni']['ovni_youtube']['oauth']['engine'] = array(
    '#type' => 'fieldset',
    '#title' => t('Cloud Engine && App Engine Settings'),
    '#tree' => TRUE,
  );
  $form['ovni']['ovni_youtube']['oauth']['engine']['clientid'] = array(
    '#title' => t('Client ID'),
    '#type' => 'textfield',
    '#default_value' => isset($youtube['oauth']['engine']['clientid']) && !empty($youtube['oauth']['engine']['clientid']) ? $youtube['oauth']['engine']['clientid'] : '',
    '#size' => 60,
    '#maxlength' => 128,
  );
  $form['ovni']['ovni_youtube']['oauth']['engine']['emailaddress'] = array(
    '#title' => t('Email address engine'),
    '#type' => 'textfield',
    '#default_value' => isset($youtube['oauth']['engine']['emailaddress']) && !empty($youtube['oauth']['engine']['emailaddress']) ? $youtube['oauth']['engine']['emailaddress'] : '',
    '#size' => 60,
    '#maxlength' => 128,
  );
  $form['ovni']['ovni_youtube']['oauth']['service'] = array(
    '#type' => 'fieldset',
    '#title' => t('Service Account Settings'),
    '#tree' => TRUE,
  );
  $form['ovni']['ovni_youtube']['oauth']['service']['clientid'] = array(
    '#title' => t('Client ID'),
    '#type' => 'textfield',
    '#default_value' => isset($youtube['oauth']['service']['clientid']) && !empty($youtube['oauth']['service']['clientid']) ? $youtube['oauth']['service']['clientid'] : '',
    '#size' => 60,
    '#maxlength' => 128,
  );
  $form['ovni']['ovni_youtube']['oauth']['service']['emailaddress'] = array(
    '#title' => t('Email address service'),
    '#type' => 'textfield',
    '#default_value' => isset($youtube['oauth']['service']['emailaddress']) && !empty($youtube['oauth']['service']['emailaddress']) ? $youtube['oauth']['service']['emailaddress'] : '',
    '#size' => 60,
    '#maxlength' => 128,
  );
  $form['ovni']['ovni_youtube']['oauth']['service']['publickeyfp'] = array(
    '#title' => t('Public Key Fingerprint'),
    '#type' => 'textfield',
    '#default_value' => isset($youtube['oauth']['service']['publickeyfp']) && !empty($youtube['oauth']['service']['publickeyfp']) ? $youtube['oauth']['service']['publickeyfp'] : '',
    '#size' => 60,
    '#maxlength' => 128,
  );
  return system_settings_form($form);
}
/**
 * Implements _form_validate().
 */
function ovni_admin_settings_form_validate($form, &$form_state) {
  //Valid a field value or catch error
  if($form_state['values']['ovni_status'] && (!isset($form_state['values']['ovni_youtube']['apikey']) || empty($form_state['values']['ovni_youtube']['apikey']))){
    form_set_error('ovni_youtube][apikey', t('You need to provide a valid API Key.'));
  }
}
/**
 * Implements _form_submit().
 */
function ovni_admin_settings_form_submit($form, &$form_state){
  //Save values
  variable_set('ovni_status',$form_state['values']['ovni_status']);
  variable_set('ovni_youtube',$form_state['values']['ovni_youtube']);
}
