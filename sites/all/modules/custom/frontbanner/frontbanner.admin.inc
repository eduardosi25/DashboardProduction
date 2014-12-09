<?php
/**
 * @file
 * Administrative page callbacks for the frontbanner module.
 */
/**
 * Implements hook_admin_settings() for module settings configuration.
 */
function frontbanner_admin_settings_form($form_state) {
  $form['#submit'][]='frontbanner_admin_settings_form_submit';
  $form['frontbanner'] = array(
    '#type' => 'fieldset',
    '#title' => t('Front Banner Settings'),
  );
  $form['frontbanner']['frontbanner_status'] = array(
    '#title' => t('Enabled Front Banner Page'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('frontbanner_status',FALSE),
    '#description' => t('Enabled or disabled Front Banner for Pages'),
  );
  $form['frontbanner']['frontbanner_expire'] = array(
    '#title' => t('Frecuency time to show Front Banner'),
    '#type' => 'select',
    '#options' => array(
      '1m'  => '1 minute',
      '5m'  => '5 minutes',
      '10m' => '10 minutes',
      '30m' => '15 minutes',
      '60m' => '60 minutes',
      '6h'  => '6 hours',
      '12h' => '12 hours',
      '24h' => '24 hours',
      '2d'  => '2 days',
      '4d'  => '4 days',
      '6d'  => '6 days',
      '12d' => '12 days',
      '24d' => '24 days',
      '48d' => '48 days',
      '90d' => '90 days'
    ),
    '#default_value' => variable_get('frontbanner_expire','24h'),
    '#description' => t('Select a frecuency time for show Front Banner to users. This works with cookies, be careful.'),
  );
  $form['frontbanner']['frontbanner_match'] = array(
    '#title' => t('Matching Expressions for show Front Banner'),
    '#type' => 'textarea',
    '#cols' => 60,
    '#rows' => 10,
    '#resizable' => FALSE,
    '#default_value' => variable_get('frontbanner_match','*'),
    '#description' => t("Specify pages by using their paths. Enter one path per line. The '*' character is a wildcard. Example paths are %blog for the blog page and %blog-wildcard for every personal blog. %front is the front page."),
  );
  $form['frontbanner']['frontbanner_token'] = array(
    '#title' => t('Token'),
    '#type' => 'textfield',
    '#default_value' => variable_get('frontbanner_token', md5($_SERVER['HTTP_HOST'])),
    '#size' => 60,
    '#maxlength' => 100,
    '#required' => TRUE,
    '#description' => t('Token Key for authenticated requests @see hook_menu_module_port(command)] on module file. Default value md5(domain).'),
  );
  $frontbanner_status=variable_get('frontbanner_status', FALSE);
  $collapsed=$frontbanner_status ? TRUE : FALSE;
  /**
   * Skin
   */
  $skin=variable_get('frontbanner_skin','');
  $form['frontbanner']['skin'] = array(
    '#type' => 'fieldset',
    '#title' => t('Skin Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => $collapsed,
  );
  $form['frontbanner']['skin']['skin_url'] = array(
    '#title' => t('URL Background Imagen for Skin'),
    '#type' => 'textfield',
    '#default_value' => isset($skin['url']) ? $skin['url'] : '',
    '#size' => 150,
    '#maxlength' => 254,
    '#description' => t('Set url logo.  If the image are a greek, please dont forget to put repeated On'),
  );
  $form['frontbanner']['skin']['skin_repeat'] = array(
    '#title' => t('Background repeated'),
    '#type' => 'checkbox',
    '#default_value' => isset($skin['repeat']) ? $skin['repeat'] : FALSE,
    '#description' => t('Background repeat. <a href="@url" target="@target">CSS background-repeat Property</a>.', array('@url' => 'http://www.w3schools.com/cssref/pr_background-repeat.asp', '@target' => '_blank')),
  );
  $form['frontbanner']['skin']['skin_position_left'] = array(
    '#title' => t('Position background left'),
    '#type' => 'textfield',
    '#default_value' => isset($skin['position_left']) ? $skin['position_left'] : 'center',
    '#size' => 15,
    '#maxlength' => 32,
    '#description' => t('Position left. <a href="@url" target="@target">CSS background-position Property</a>', array('@url' => 'http://www.w3schools.com/cssref/pr_background-position.asp', '@target' => '_blank')),
  );
  $form['frontbanner']['skin']['skin_position_top'] = array(
    '#title' => t('Position background top'),
    '#type' => 'textfield',
    '#default_value' => isset($skin['position_top']) ? $skin['position_top'] : 'top',
    '#size' => 15,
    '#maxlength' => 32,
    '#description' => t('Position top. <a href="@url" target="@target">CSS background-position Property</a>', array('@url' => 'http://www.w3schools.com/cssref/pr_background-position.asp', '@target' => '_blank')),
  );
  $form['frontbanner']['skin']['skin_color'] = array(
    '#title' => t('Color background'),
    '#type' => 'textfield',
    '#default_value' => isset($skin['color']) ? $skin['color'] : '#FFFFFF',
    '#size' => 15,
    '#maxlength' => 32,
    '#description' => t('Color #AAAAAA. <a href="@url" target="@target">CSS background-color Property</a>', array('@url' => 'http://www.w3schools.com/cssref/pr_background-color.asp', '@target' => '_blank')),
  );
  /**
   * Container
   */
  $container=variable_get('frontbanner_container','');
  $form['frontbanner']['container'] = array(
    '#type' => 'fieldset',
    '#title' => t('Container Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => $collapsed,
  );
  $form['frontbanner']['container']['container_width'] = array(
    '#title' => t('Width container'),
    '#type' => 'textfield',
    '#default_value' => isset($container['width']) ? $container['width'] : '768px',
    '#size' => 15,
    '#maxlength' => 32,
    '#description' => t('Container width. <a href="@url" target="@target">CSS width Property</a>', array('@url' => 'http://www.w3schools.com/cssref/pr_dim_width.asp', '@target' => '_blank')),
  );
  $form['frontbanner']['container']['container_height'] = array(
    '#title' => t('Height container'),
    '#type' => 'textfield',
    '#default_value' => isset($container['height']) ? $container['height'] : '100%',
    '#size' => 15,
    '#maxlength' => 32,
    '#description' => t('Container height. <a href="@url" target="@target">CSS height Property</a>', array('@url' => 'http://www.w3schools.com/cssref/pr_dim_height.asp', '@target' => '_blank')),
  );
  /**
   * Header
   */
  $header=variable_get('frontbanner_header','');
  $form['frontbanner']['header'] = array(
    '#type' => 'fieldset',
    '#title' => t('Header Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => $collapsed,
  );
  $form['frontbanner']['header']['header_url'] = array(
    '#title' => t('URL Logo Image'),
    '#type' => 'textfield',
    '#default_value' => isset($header['url']) ? $header['url'] : '',
    '#size' => 150,
    '#maxlength' => 254,
    '#description' => t('Set url for background image. Like a logo, dont use repeated'),
  );
  $form['frontbanner']['header']['header_repeat'] = array(
    '#title' => t('Background repeated'),
    '#type' => 'checkbox',
    '#default_value' => isset($header['repeat']) ? $header['repeat'] : FALSE,
    '#description' => t('Background repeat. <a href="@url" target="@target">CSS background-repeat Property</a>.', array('@url' => 'http://www.w3schools.com/cssref/pr_background-repeat.asp', '@target' => '_blank')),
  );
  $form['frontbanner']['header']['header_position_left'] = array(
    '#title' => t('Position background left'),
    '#type' => 'textfield',
    '#default_value' => isset($header['position_left']) ? $header['position_left'] : '20px',
    '#size' => 15,
    '#maxlength' => 32,
    '#description' => t('Position left. <a href="@url" target="@target">CSS background-position Property</a>', array('@url' => 'http://www.w3schools.com/cssref/pr_background-position.asp', '@target' => '_blank')),
  );
  $form['frontbanner']['header']['header_position_top'] = array(
    '#title' => t('Position background top'),
    '#type' => 'textfield',
    '#default_value' => isset($header['position_top']) ? $header['position_top'] : 'center',
    '#size' => 15,
    '#maxlength' => 32,
    '#description' => t('Position top. <a href="@url" target="@target">CSS background-position Property</a>', array('@url' => 'http://www.w3schools.com/cssref/pr_background-position.asp', '@target' => '_blank')),
  );
  $form['frontbanner']['header']['header_color'] = array(
    '#title' => t('Color background'),
    '#type' => 'textfield',
    '#default_value' => isset($header['color']) ? $header['color'] : '#666666',
    '#size' => 15,
    '#maxlength' => 32,
    '#description' => t('Color #AAAAAA. <a href="@url" target="@target">CSS background-color Property</a>', array('@url' => 'http://www.w3schools.com/cssref/pr_background-color.asp', '@target' => '_blank')),
  );
  $form['frontbanner']['header']['header_height'] = array(
    '#title' => t('Height header'),
    '#type' => 'textfield',
    '#default_value' => isset($header['height']) ? $header['height'] : '51px',
    '#size' => 15,
    '#maxlength' => 32,
    '#description' => t('Container height. <a href="@url" target="@target">CSS height Property</a>', array('@url' => 'http://www.w3schools.com/cssref/pr_dim_height.asp', '@target' => '_blank')),
  );
  /**
   * Close
   */
  $close=variable_get('frontbanner_close','');
  $form['frontbanner']['close'] = array(
    '#type' => 'fieldset',
    '#title' => t('Close Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => $collapsed,
  );
  $form['frontbanner']['close']['close_width'] = array(
    '#title' => t('Width container'),
    '#type' => 'textfield',
    '#default_value' => isset($close['width']) ? $close['width'] : '231px',
    '#size' => 15,
    '#maxlength' => 32,
    '#description' => t('Container width. <a href="@url" target="@target">CSS width Property</a>', array('@url' => 'http://www.w3schools.com/cssref/pr_dim_width.asp', '@target' => '_blank')),
  );
  $form['frontbanner']['close']['close_color'] = array(
    '#title' => t('Color background'),
    '#type' => 'textfield',
    '#default_value' => isset($close['color']) ? $close['color'] : '#01669c',
    '#size' => 15,
    '#maxlength' => 32,
    '#description' => t('Color #AAAAAA. <a href="@url" target="@target">CSS background-color Property</a>', array('@url' => 'http://www.w3schools.com/cssref/pr_background-color.asp', '@target' => '_blank')),
  );
  $form['frontbanner']['close']['close_textcolor'] = array(
    '#title' => t('Text color'),
    '#type' => 'textfield',
    '#default_value' => isset($close['textcolor']) ? $close['textcolor'] : '#FFFFFF',
    '#size' => 15,
    '#maxlength' => 32,
    '#description' => t('Color #AAAAAA. <a href="@url" target="@target">CSS color Property</a>', array('@url' => 'http://www.w3schools.com/cssref/pr_text_color.asp', '@target' => '_blank')),
  );
  $form['frontbanner']['close']['close_decoration'] = array(
    '#title' => t('Text decoration'),
    '#type' => 'textfield',
    '#default_value' => isset($close['decoration']) ? $close['decoration'] : '#FFFFFF',
    '#size' => 32,
    '#maxlength' => 64,
    '#description' => t('Text decoration. <a href="@url" target="@target">CSS text-decoration Property</a>', array('@url' => 'http://www.w3schools.com/cssref/pr_text_text-decoration.asp', '@target' => '_blank')),
  );
  /**
   * Main
   */
  $main=variable_get('frontbanner_main','');
  $form['frontbanner']['main'] = array(
    '#type' => 'fieldset',
    '#title' => t('Main Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => $collapsed,
  );
  $form['frontbanner']['main']['main_disabled_mobile'] = array(
    '#title' => t('Mobile Disabled'),
    '#type' => 'checkbox',
    '#default_value' => isset($main['disabled_mobile']) ? $main['disabled_mobile'] : FALSE,
    '#description' => t('Check this if you wish avoid mobile devices.'),
  );
  $form['frontbanner']['main']['main_height'] = array(
    '#title' => t('Height container'),
    '#type' => 'textfield',
    '#default_value' => isset($main['height']) ? $main['height'] : '480px',
    '#size' => 15,
    '#maxlength' => 32,
    '#description' => t('Container height. <a href="@url" target="@target">CSS height Property</a>', array('@url' => 'http://www.w3schools.com/cssref/pr_dim_height.asp', '@target' => '_blank')),
  );
  $form['frontbanner']['main']['main_color'] = array(
    '#title' => t('Color background'),
    '#type' => 'textfield',
    '#default_value' => isset($main['color']) ? $main['color'] : '#FFFFFF',
    '#size' => 15,
    '#maxlength' => 32,
    '#description' => t('Color #AAAAAA. <a href="@url" target="@target">CSS background-color Property</a>', array('@url' => 'http://www.w3schools.com/cssref/pr_background-color.asp', '@target' => '_blank')),
  );
  $form['frontbanner']['main']['main_position'] = array(
    '#title' => t('Position'),
    '#type' => 'select',
    '#options' => array(
      'center' => 'center',
      'top'    => 'top',
      'bottom' => 'bottom',
    ),
    '#default_value' => isset($main['position']) ? $main['position'] : 'top',
    '#description' => t('Select a position'),
  );
  $form['frontbanner']['main']['main_countdown'] = array(
    '#title' => t('Countdown Enabled'),
    '#type' => 'checkbox',
    '#default_value' => isset($main['countdown']) ? $main['countdown'] : FALSE,
    '#description' => t('Check this if you need or want enable the countdown.'),
  );
  $form['frontbanner']['main']['main_countdown_duration'] = array(
    '#title' => t('Duration in seconds for Countdown'),
    '#type' => 'textfield',
    '#default_value' => isset($main['countdown_duration']) ? $main['countdown_duration'] : '20',
    '#size' => 5,
    '#maxlength' => 5,
    '#description' => t('Duration in seconds for automatic remove the frontbanner'),
  );
  $form['frontbanner']['main']['main_countdown_message'] = array(
    '#title' => t('Message tes for duration in Countdown'),
    '#type' => 'textfield',
    '#default_value' => isset($main['countdown_message']) ? $main['countdown_message'] : 'Este anuncio se cerrará automáticamente en',
    '#size' => 100,
    '#maxlength' => 200,
    '#description' => t('Duration in seconds for automatic remove the frontbanner'),
  );

  return system_settings_form($form);
}
/**
 * Implements _form_validate().
 */
function frontbanner_admin_settings_form_validate($form, &$form_state) {
  // Trim some text values.
  $form_state['values']['frontbanner_token'] = trim($form_state['values']['frontbanner_token']);
  //Valid a field value or catch error
  if(!isset($form_state['values']['frontbanner_token']) || empty($form_state['values']['frontbanner_token'])){
    form_set_error('frontbanner_token', t('You need to provide a valid Key.'));
  }
}
/**
 * Implements _form_submit().
 */
function frontbanner_admin_settings_form_submit($form, &$form_state){
  //Save values
  variable_set('frontbanner_status',$form_state['values']['frontbanner_status']);
  variable_set('frontbanner_expire',$form_state['values']['frontbanner_expire']);
  variable_set('frontbanner_match',$form_state['values']['frontbanner_match']);
  variable_set('frontbanner_token',$form_state['values']['frontbanner_token']);
  /**
   * Skin
   */
  #if(isset($form_state['values']['skin_url']) && !empty($form_state['values']['skin_url'])){
    $skin=array(
      'url'    => $form_state['values']['skin_url'],
      'repeat' => $form_state['values']['skin_repeat'],
      'position_left' => $form_state['values']['skin_position_left'],
      'position_top'  => $form_state['values']['skin_position_top'],
      'color'  => $form_state['values']['skin_color'],
    );
    variable_set('frontbanner_skin',$skin);
  #}
  /**
   * Container
   */
  $container=array(
    'width'  => $form_state['values']['container_width'],
    'height' => $form_state['values']['container_height'],
  );
  variable_set('frontbanner_container',$container);
  /**
   * Header
   */
  if(isset($form_state['values']['header_url']) && !empty($form_state['values']['header_url'])){
    $header=array(
      'url'    => $form_state['values']['header_url'],
      'repeat' => $form_state['values']['header_repeat'],
      'position_left' => $form_state['values']['header_position_left'],
      'position_top'  => $form_state['values']['header_position_top'],
      'color'  => $form_state['values']['header_color'],
      'height' => $form_state['values']['header_height'],
    );
    variable_set('frontbanner_header',$header);
  }
  /**
   * Close
   */
  $close=array(
    'width'      => $form_state['values']['close_width'],
    'color'      => $form_state['values']['close_color'],
    'textcolor'  => $form_state['values']['close_textcolor'],
    'decoration' => $form_state['values']['close_decoration'],
  );
  variable_set('frontbanner_close',$close);
  /**
   * Main
   */
  $main=array(
    'disabled_mobile'    => $form_state['values']['main_disabled_mobile'],
    'height'             => $form_state['values']['main_height'],
    'color'              => $form_state['values']['main_color'],
    'position'           => $form_state['values']['main_position'],
    'countdown'          => $form_state['values']['main_countdown'],
    'countdown_duration' => $form_state['values']['main_countdown_duration'],
    'countdown_message'  => $form_state['values']['main_countdown_message'],
  );
  variable_set('frontbanner_main',$main);

  //Clear cache
  cache_clear_all('frontbanner', 'cache');

  //Remove cookie Prehome
  if (isset($_COOKIE['frontbanner'])) {
    unset($_COOKIE['frontbanner']);
    setcookie('frontbanner', null, -1, '/');
  }
}
