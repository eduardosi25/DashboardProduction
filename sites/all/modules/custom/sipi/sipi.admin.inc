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
    '#title' => t('CODIGA Settings'),
  );
  $status=variable_get('sipi_status',FALSE);
  $form['sipi']['sipi_status'] = array(
    '#title' => t('Enabled CODIGA Integration'),
    '#type' => 'checkbox',
    '#default_value' => $status,
    '#description' => t('Enabled or disabled CODIGA Integration'),
  );
  /**
   * Settings for SIPI
   * @see http://[API_DOMAIN]/[API_VERSION]/[API_SITENAME]/[API_USERS/API_CONTENTS].[API_FORMAT]/[API_TOKEN]
   * @see http://api.inventmx.com/v1/gamedots/sipi.json/3a5877fc16b6fcbf8eedbe55d091938a
   * @see http://api.inventmx.com/v1/gamedots/sipi-analytics.json/3a5877fc16b6fcbf8eedbe55d091938a
   * @see http://api.inventmx.com/v1/gamedots/sipi.json/3a5877fc16b6fcbf8eedbe55d091938a?limit=1&name=Gameloft
   * @see http://api.inventmx.com/v1/gamedots/sipi-analytics.json/3a5877fc16b6fcbf8eedbe55d091938a?limit=1&name=Gameloft
   */
  $settings=variable_get('sipi_settings',NULL);
  $form['sipi']['sipi_settings'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
    '#title' => t('CODIGA Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => variable_get('sipi_status', FALSE),
  );
  $form['sipi']['sipi_settings']['debug'] = array(
    '#title' => t('Debug'),
    '#type' => 'checkbox',
    '#default_value' => isset($settings['debug']) ? $settings['debug'] : FALSE,
    '#description' => t('Enabled debug mode'),
  );
  $form['sipi']['sipi_settings']['protocol'] = array(
    '#title' => t('API Protocol'),
    '#type' => 'select',
    '#options' => array(
      'none' => t('Select the protocol'),
      'http' => 'HTTP',
      'https' => 'HTTPS',
    ),
    '#default_value' => isset($settings['protocol']) ? $settings['protocol'] : NULL,
  );
  $form['sipi']['sipi_settings']['domain'] = array(
    '#title' => t('API Domain'),
    '#type' => 'textfield',
    '#default_value' => isset($settings['domain']) ? $settings['domain'] : NULL,
    '#size' => 30,
    '#maxlength' => 254,
  );
  $form['sipi']['sipi_settings']['version'] = array(
    '#title' => t('API Version'),
    '#type' => 'textfield',
    '#default_value' => isset($settings['version']) ? $settings['version'] : NULL,
    '#size' => 10,
    '#maxlength' => 32,
  );
  $form['sipi']['sipi_settings']['sites'] = array(
    '#title' => t('Select the sites with CODIGA Activated'),
    '#type' => 'checkboxes',
    '#options' => get_sites_options(),
    '#default_value' => get_checked_options($settings['sites']),
  );
  $form['sipi']['sipi_settings']['users'] = array(
    '#title' => t('API Repo Users'),
    '#description' => t('The repo name for query about CODIGA Users'),
    '#type' => 'textfield',
    '#default_value' => isset($settings['users']) ? $settings['users'] : NULL,
    '#size' => 20,
    '#maxlength' => 254,
  );
  $form['sipi']['sipi_settings']['contents'] = array(
    '#title' => t('API Repo COntents'),
    '#description' => t('The repo name for query about CODIGA Contents with Analytics'),
    '#type' => 'textfield',
    '#default_value' => isset($settings['contents']) ? $settings['contents'] : NULL,
    '#size' => 20,
    '#maxlength' => 254,
  );
  $form['sipi']['sipi_settings']['format'] = array(
    '#title' => t('API Format'),
    '#type' => 'select',
    '#options' => array(
      'none' => t('Select a format'),
      'json'   => 'JSON',
      'rss'    => 'RSS',
      'jsonlt' => 'JSON Lite (MSN)',
      'xml'    => 'XML Standard'
    ),
    '#default_value' => isset($settings['format']) ? $settings['format'] : NULL,
  );
  $form['sipi']['sipi_settings']['token'] = array(
    '#title' => t('Token Access API Invent'),
    '#type' => 'textfield',
    '#default_value' => isset($settings['token']) ? $settings['token'] : '339fd1e0444ddbbd4d4528d8df161108',
    '#size' => 150,
    '#maxlength' => 254,
  );
  return system_settings_form($form);
}
function get_sites_options(){
  $query="select td.tid, td.name
          from taxonomy_term_data td
          inner join field_data_field_api_container fac on fac.entity_id=td.tid
          where td.vid=1
          order by td.weight ASC";
  $result=db_query($query);
  $items=array();
  foreach($result as $row){
    $items[$row->tid]=$row->name;
  }
  return $items;
}
function get_checked_options($options){
  if(!isset($options) || empty($options))
    return array();
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
  cache_clear_all('sipi_variables', 'cache');
}


/**
 * Create Navigation Menu with Links for this module named as: menu-sipi
 * According to the links that we have in the hook_menu
 * @see sipi.module
 */
function _create_sipi_menu(){
  //Create SIPI menu
  $menu = array(
    'menu_name'   => 'menu-codiga',
    'title'       => t('Menú CODIGA'),
    'description' => 'COntenidos DIgitales GArantizados',
  );

  //Search previous menu
  $menuOld=menu_load($menu['menu_name']);
  if($menuOld){
    menu_delete($menu);
  }

  if(!menu_tree($menu['menu_name'])){
    menu_save($menu);
    //Create links
    $item = array (
      'link_title' => 'Inicio',
      'description'=> 'CODIGA Home',
      'link_path'  => 'codiga',
      'menu_name'  => 'menu-codiga',
      'weight'     => 0,
      'plid'       => 0,
    );
    menu_link_save($item);
    $item = array (
      'link_title' => t('Dashboard'),
      'description'=> t('CODIGA Dashboard'),
      'link_path'  => 'codiga/dashboard',
      'menu_name'  => 'menu-codiga',
      'weight'     => 1,
      'plid'       => 0,
    );
    menu_link_save($item);
    //Parent :: Plans
    $item = array (
      'link_title' => 'Planes',
      'description'=> 'Planes SIPI',
      'link_path'  => 'codiga/plans',
      'menu_name'  => 'menu-codiga',
      'weight'     => 2,
      'plid'       => 0,
    );
    $plid = menu_link_save($item);
    $item = array (
      'link_title' => 'Planes',
      'description'=> 'Planes SIPI',
      'link_path'  => 'codiga/plans',
      'menu_name'  => 'menu-codiga',
      'expanded'   => true,
      'weight'     => 0,
      'plid'       => $plid,
    );
    menu_link_save($item);
    $item = array (
      'link_title' => 'Agregar nuevo plan',
      'description'=> 'Agregar nuevo Plan SIPI',
      'link_path'  => 'codiga/plans/add',
      'menu_name'  => 'menu-codiga',
      'expanded'   => true,
      'weight'     => 1,
      'plid'       => $plid,
    );
    menu_link_save($item);
    //Parent :: Client
    $item = array (
      'link_title' => 'Clientes',
      'description'=> 'Clientes SIPI',
      'link_path'  => 'codiga/client',
      'menu_name'  => 'menu-codiga',
      'weight'     => 3,
      'plid'       => 0,
    );
    $plid = menu_link_save($item);
    $item = array (
      'link_title' => 'Clientes',
      'link_path'  => 'codiga/client',
      'description'=> 'Clientes SIPI',
      'menu_name'  => 'menu-codiga',
      'expanded'   => true,
      'weight'     => 0,
      'plid'       => $plid,
    );
    menu_link_save($item);
    $item = array (
      'link_title' => 'Agregar nuevo cliente',
      'description'=> 'Agregar nuevo Cliente SIPI',
      'link_path'  => 'codiga/client/add',
      'menu_name'  => 'menu-codiga',
      'expanded'   => true,
      'weight'     => 1,
      'plid'       => $plid,
    );
    menu_link_save($item);
    drupal_set_message('CODIGA Menu Created.','status');
    return t('CODIGA Menu Created.');
  }else{
    drupal_set_message('The CODIGA Menu already exists.','error');
    $holders=array(
      '@url1'=>'/admin/config/development/performance',
      '@url2'=>'/admin/structure/menu/manage/menu-codiga'
    );
    return t('The CODIGA Menu already exists. If you cant see it, please try to <a href="@url1"">clear cache</a> or visit it in <a href="@url2">Manage Menu Page</a>',$holders);
  }
}

