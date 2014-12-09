<?php
/**
 * @file
 * Administrative page callbacks for the node_analytics module.
 */
/**
 * Implements hook_admin_settings() for module settings configuration.
 */
function node_analytics_admin_settings_form($form_state) {
  //Get values
  $status=variable_get('node_analytics_status',FALSE);
  $debug=variable_get('node_analytics_debug',FALSE);
  $gaApi=variable_get('node_analytics_api', NULL);
  $settings=variable_get('node_analytics_settings', NULL);

  $form['#submit'][]='node_analytics_admin_settings_form_submit';
  $form['node_analytics'] = array(
    '#type' => 'fieldset',
    '#title' => t('Node Analytics Integration'),
  );
  $form['node_analytics']['node_analytics_status'] = array(
    '#title' => t('Enabled Node Analytics'),
    '#type' => 'checkbox',
    '#default_value' => $status,
    '#description' => t('Enabled or disabled Node Analytics Integration'),
  );
  $form['node_analytics']['node_analytics_debug'] = array(
    '#title' => t('Enabled Debug for Node Analytics'),
    '#type' => 'checkbox',
    '#default_value' => $debug,
    '#description' => t('Enabled or disabled Debug Mode for Node Analytics Integration'),
  );

  $form['node_analytics']['node_analytics_api'] = array(
    '#type' => 'fieldset',
    '#title' => t('API Settings'),
    '#tree' => TRUE,
    '#collapsible' => $status,
    '#collapsed' => $status,
  );
  $form['node_analytics']['node_analytics_api']['CLIENT_ID'] = array(
    '#title' => t('CLIENT_ID'),
    '#type' => 'textfield',
    '#default_value' => isset($gaApi['CLIENT_ID']) && !empty($gaApi['CLIENT_ID']) ? $gaApi['CLIENT_ID'] : '',
    '#size' => 120,
    '#maxlength' => 255,
    '#description' => t('You need a valid CLIENT_ID from Google Developers. <b>If you have any question, please contact the administrator.[https://console.developers.google.com/project]</b>'),
  );
  $form['node_analytics']['node_analytics_api']['CLIENT_EMAIL'] = array(
    '#title' => t('CLIENT_EMAIL'),
    '#type' => 'textfield',
    '#default_value' => isset($gaApi['CLIENT_EMAIL']) && !empty($gaApi['CLIENT_EMAIL']) ? $gaApi['CLIENT_EMAIL'] : '',
    '#size' => 120,
    '#maxlength' => 255,
    '#description' => t('You need a valid CLIENT_EMAIL.'),
  );
  $form['node_analytics']['node_analytics_api']['PUBLIC_KEY'] = array(
    '#title' => t('PUBLIC_KEY'),
    '#type' => 'textfield',
    '#default_value' => isset($gaApi['PUBLIC_KEY']) && !empty($gaApi['PUBLIC_KEY']) ? $gaApi['PUBLIC_KEY'] : '',
    '#size' => 120,
    '#maxlength' => 255,
    '#description' => t('You need a valid PUBLIC_KEY.'),
  );
  $form['node_analytics']['node_analytics_api']['API_KEY'] = array(
    '#title' => t('API_KEY'),
    '#type' => 'textfield',
    '#default_value' => isset($gaApi['PUBLIC_KEY']) && !empty($gaApi['API_KEY']) ? $gaApi['API_KEY'] : '',
    '#size' => 120,
    '#maxlength' => 255,
    '#description' => t('You need a valid API_KEY.'),
  );
  $form['node_analytics']['node_analytics_api']['KEY_FILE'] = array(
    '#title' => t('KEY_FILE'),
    '#type' => 'textfield',
    '#default_value' => isset($gaApi['KEY_FILE']) && !empty($gaApi['KEY_FILE']) ? $gaApi['KEY_FILE'] : '',
    '#size' => 120,
    '#maxlength' => 255,
    '#description' => t('You need a valid KEY_FILE.'),
  );
  $form['node_analytics']['node_analytics_api']['GA_SCOPE_FULL'] = array(
    '#title' => t('GA_SCOPE_FULL'),
    '#type' => 'textfield',
    '#default_value' => isset($gaApi['GA_SCOPE_FULL']) && !empty($gaApi['GA_SCOPE_FULL']) ? $gaApi['GA_SCOPE_FULL'] : '',
    '#size' => 120,
    '#maxlength' => 255,
    '#description' => t('You need a valid GA_SCOPE_FULL.'),
  );
  $form['node_analytics']['node_analytics_api']['GA_SCOPE_READ'] = array(
    '#title' => t('GA_SCOPE_READ'),
    '#type' => 'textfield',
    '#default_value' => isset($gaApi['GA_SCOPE_READ']) && !empty($gaApi['GA_SCOPE_READ']) ? $gaApi['GA_SCOPE_READ'] : '',
    '#size' => 120,
    '#maxlength' => 255,
    '#description' => t('You need a valid GA_SCOPE_READ.'),
  );
  $form['node_analytics']['node_analytics_api']['APP_NAME'] = array(
    '#title' => t('APP_NAME'),
    '#type' => 'textfield',
    '#default_value' => isset($gaApi['APP_NAME']) && !empty($gaApi['APP_NAME']) ? $gaApi['APP_NAME'] : 'Node Analytics - Inventmx',
    '#size' => 120,
    '#maxlength' => 255,
  );

  $form['node_analytics']['node_analytics_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Settings'),
    '#tree' => TRUE,
    '#collapsible' => $status,
    '#collapsed' => $status,
  );
  $form['node_analytics']['node_analytics_settings']['ids'] = array(
    '#title' => t('Table ID'),
    '#type' => 'textfield',
    '#default_value' => isset($settings['ids']) && !empty($settings['ids']) ? $settings['ids'] : 'ga:54331725',
    '#size' => 80,
    '#maxlength' => 100,
    '#description' => t('Check properties from Account Explorer on https://ga-dev-tools.appspot.com/account-explorer/.'),
  );
  $form['node_analytics']['node_analytics_settings']['metrics'] = array(
    '#title' => t('Metrics'),
    '#type' => 'textarea',
    '#cols' => 120,
    '#rows' => 6,
    '#default_value' => isset($settings['metrics']) && !empty($settings['metrics']) ? $settings['metrics'] : 'ga:sessions,ga:pageviews,ga:uniquePageviews,ga:timeOnPage,ga:sessionDuration,ga:exits,ga:avgSessionDuration,ga:pageviewsPerSession,ga:avgTimeOnPage',
    '#description' => t('Check options on Query Explorer on https://ga-dev-tools.appspot.com/explorer/.'),
  );
  $form['node_analytics']['node_analytics_settings']['dimensions'] = array(
    '#title' => t('Dimensions'),
    '#type' => 'textfield',
    '#default_value' => isset($settings['dimensions']) && !empty($settings['dimensions']) ? $settings['dimensions'] : 'ga:pagePath',
    '#size' => 80,
    '#maxlength' => 100,
    '#description' => t('Enabled or disabled node_analytics Async Integration'),
  );
  $form['node_analytics']['node_analytics_settings']['max-results'] = array(
    '#title' => t('Max results'),
    '#type' => 'textfield',
    '#default_value' => isset($settings['max-results']) && !empty($settings['max-results']) ? $settings['max-results'] : 100,
    '#size' => 10,
    '#maxlength' => 3,
    '#description' => t('API Limit 100 results per request'),
  );

  return system_settings_form($form);
}
/**
 * Implements _form_submit().
 */
function node_analytics_admin_settings_form_submit($form, &$form_state){
  //Save values
  variable_set('node_analytics_status',$form_state['values']['node_analytics_status']);
  variable_set('node_analytics_debug',$form_state['values']['node_analytics_debug']);
  variable_set('node_analytics_api',$form_state['values']['node_analytics_api']);
  variable_set('node_analytics_settings',$form_state['values']['node_analytics_settings']);
  //Constant Values
  $constants=array(
    'secret'   => 'notasecret',
    'script'   => 'cron.standalone.php',
    'mode'     => 'offline_access',
    'redirect' => 'http://'.$_SERVER['HTTP_HOST'].'/oauth2callback',
  );
  variable_set('node_analytics_constants',$constants);
}
