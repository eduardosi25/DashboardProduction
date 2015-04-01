<?php
function sipi_user(){
  return 'Listado de usuarios';

  return sipi_user_list();
}
function sipi_user_add(){
  return drupal_get_form('sipi_users_form');
}
function sipi_user_edit($user){
  return drupal_get_form('sipi_users_form',$user);
}
function sipi_user_delete($user){
  return drupal_get_form('sipi_users_form',$user);
}
function sipi_user_view($user){
  return drupal_get_form('sipi_users_form',$user);
}

function sipi_users_form($form, &$form_state, $user=NULL){
  $admin = user_access('sipi admin users');
  // If we aren't admin but already logged on, go to the dashboard
  if (!$admin) {
    drupal_goto('sipi');
  }
  $form=array();
  $form['#tree'] = TRUE;

  $form['sipi_user'] = array(
    '#type'  => 'fieldset',
    '#title' => !isset($user) || empty($user) ? t('SIPI User :: Add') : t('SIPI User :: Edit'),
    '#tree'  => TRUE,
  );
  $form['sipi_user']['uid']  = array(
    '#type' => 'hidden',
    '#value' => isset($user['uid']) && !empty($user['uid']) ? $user['uid'] : 0,
  );
  $form['sipi_user']['client'] = array(
    '#type'  => 'fieldset',
    '#title' => !isset($user) || empty($user) ? t('Add Client') : t('Edit Client'),
    '#tree'  => TRUE,
  );
  $form['sipi_user']['client']['firstname'] = array(
    '#title'         => t('Name'),
    '#type'          => 'textfield',
    '#size'          => 30,
    '#maxlength'     => 100,
    '#default_value' => isset($user['firstname']) && !empty($user['firstname']) ? $user['firstname'] : '',
    '#description'   => t('First name'),
    '#required'      => TRUE,
  );
  $form['sipi_user']['client']['lastname'] = array(
    '#title'         => t('Last name'),
    '#type'          => 'textfield',
    '#size'          => 30,
    '#maxlength'     => 100,
    '#default_value' => isset($user['lastname']) && !empty($user['lastname']) ? $user['lastname'] : '',
    '#description'   => t('Last name'),
    '#required'      => TRUE,
  );
  $form['sipi_user']['client']['mail'] = array(
    '#title'         => t('Email'),
    '#type'          => 'textfield',
    '#size'          => 60,
    '#maxlength'     => 150,
    '#default_value' => isset($user['mail']) && !empty($user['mail']) ? $user['mail'] : '',
    '#description'   => t('Email'),
    '#required'      => TRUE,
  );
  $form['sipi_user']['client']['pass'] = array(
    '#type'          => 'password_confirm',
    '#size'          => 15,
    '#maxlength'     => 32,
    '#description'   => t('Password'),
    '#required'      => TRUE,
  );
  $form['sipi_user']['client']['company'] = array(
    '#title'         => t('Company'),
    '#type'          => 'textfield',
    '#size'          => 60,
    '#maxlength'     => 150,
    '#default_value' => isset($user['company']) && !empty($user['company']) ? $user['company'] : '',
    '#description'   => t('Social posts'),
    '#required'      => TRUE,
  );
  $form['sipi_user']['client']['cellphone'] = array(
    '#title'         => t('Cell phone'),
    '#type'          => 'textfield',
    '#size'          => 20,
    '#maxlength'     => 20,
    '#default_value' => isset($user['cellphone']) && !empty($user['cellphone']) ? $user['cellphone'] : '',
    '#description'   => t('Cell phone'),
    '#required'      => TRUE,
  );
  $form['sipi_user']['client']['phone'] = array(
    '#title'         => t('Phone'),
    '#type'          => 'textfield',
    '#size'          => 30,
    '#maxlength'     => 60,
    '#default_value' => isset($user['phone']) && !empty($user['phone']) ? $user['phone'] : '',
    '#description'   => t('Phone'),
    '#required'      => TRUE,
  );
  $form['sipi_user']['client']['extention'] = array(
    '#title'         => t('Extention'),
    '#type'          => 'textfield',
    '#size'          => 10,
    '#maxlength'     => 10,
    '#default_value' => isset($user['extention']) && !empty($user['extention']) ? $user['extention'] : '',
    '#description'   => t('Extention'),
  );
  $form['sipi_user']['client']['web'] = array(
    '#title'         => t('Web page'),
    '#type'          => 'textfield',
    '#size'          => 10,
    '#maxlength'     => 150,
    '#default_value' => isset($user['web']) && !empty($user['web']) ? $user['web'] : '',
    '#description'   => t('Web page'),
  );
  $form['sipi_user']['client']['logo'] = array(
    '#title'         => t('Logo'),
    '#type'          => 'textfield',
    '#size'          => 10,
    '#maxlength'     => 150,
    '#default_value' => isset($user['logo']) && !empty($user['logo']) ? $user['logo'] : '',
    '#description'   => t('Logo'),
  );
  $form['sipi_user']['client']['description'] = array(
    '#title'         => t('Description'),
    '#type'          => 'textfield',
    '#size'          => 10,
    '#maxlength'     => 150,
    '#default_value' => isset($user['description']) && !empty($user['description']) ? $user['description'] : '',
    '#description'   => t('Description'),
  );
  $form['sipi_user']['client']['facebook'] = array(
    '#title'         => t('Facebook'),
    '#type'          => 'textfield',
    '#size'          => 40,
    '#maxlength'     => 150,
    '#default_value' => isset($user['facebook']) && !empty($user['facebook']) ? $user['facebook'] : '',
    '#description'   => t('Facebook'),
  );
  $form['sipi_user']['client']['twitter'] = array(
    '#title'         => t('Twitter'),
    '#type'          => 'textfield',
    '#size'          => 40,
    '#maxlength'     => 150,
    '#default_value' => isset($user['twitter']) && !empty($user['twitter']) ? $user['twitter'] : '',
    '#description'   => t('Twitter'),
  );
  $form['sipi_user']['client']['googleplus'] = array(
    '#title'         => t('Google+'),
    '#type'          => 'textfield',
    '#size'          => 40,
    '#maxlength'     => 150,
    '#default_value' => isset($user['googleplus']) && !empty($user['googleplus']) ? $user['googleplus'] : '',
    '#description'   => t('Google+'),
  );
  $form['sipi_user']['client']['youtube'] = array(
    '#title'         => t('Youtube'),
    '#type'          => 'textfield',
    '#size'          => 40,
    '#maxlength'     => 150,
    '#default_value' => isset($user['youtube']) && !empty($user['youtube']) ? $user['youtube'] : '',
    '#description'   => t('Youtube'),
  );
  $form['sipi_user']['client']['instagram'] = array(
    '#title'         => t('Instagram'),
    '#type'          => 'textfield',
    '#size'          => 40,
    '#maxlength'     => 150,
    '#default_value' => isset($user['instagram']) && !empty($user['instagram']) ? $user['instagram'] : '',
    '#description'   => t('Instagram'),
  );
  $form['sipi_user']['client']['linkedin'] = array(
    '#title'         => t('Linkedin'),
    '#type'          => 'textfield',
    '#size'          => 40,
    '#maxlength'     => 150,
    '#default_value' => isset($user['linkedin']) && !empty($user['linkedin']) ? $user['linkedin'] : '',
    '#description'   => t('Linkedin'),
  );
  $form['sipi_user']['client']['pinterest'] = array(
    '#title'         => t('Pinterest'),
    '#type'          => 'textfield',
    '#size'          => 40,
    '#maxlength'     => 150,
    '#default_value' => isset($user['pinterest']) && !empty($user['pinterest']) ? $user['pinterest'] : '',
    '#description'   => t('Pinterest'),
  );
  $form['sipi_user']['client']['vine'] = array(
    '#title'         => t('Vine'),
    '#type'          => 'textfield',
    '#size'          => 40,
    '#maxlength'     => 150,
    '#default_value' => isset($user['vine']) && !empty($user['vine']) ? $user['vine'] : '',
    '#description'   => t('Vine'),
  );

  $form['sipi_user']['invent'] = array(
    '#type'   => 'fieldset',
    '#title'  => t('Invent'),
    '#tree'   => TRUE,
    '#prefix' => '<div id="invent-fieldset-wrapper">',
    '#suffix' => '</div>',
  );

  if (empty($form_state['sipi_user']['invent']['items'])) {
    $form_state['sipi_user']['invent']['items'] = 1;
  }

  for ($i = 0; $i < $form_state['sipi_user']['invent']['items']; $i++) {
    $form['sipi_user']['invent']['data'][$i] = array(
      '#type'   => 'fieldset',
      '#title'  => t('User Data :: '.($i+1)),
      '#tree'   => TRUE,
    );

    $form['sipi_user']['invent']['data'][$i]['site'] = array(
      '#title' => t('Site name'),
      '#type' => 'select',
      '#options' => get_sipi_sites(),
      '#default_value' => isset($user['site']) && !empty($user['site']) ? $user['site'] : '',
      '#description' => t('Site name'),
      '#required' => TRUE,
    );
    $form['sipi_user']['invent']['data'][$i]['manager'] = array(
      '#title' => t('Manager'),
      '#type' => 'select',
      '#options' => get_sipi_user_manager(array('sipi_manager')),
      '#default_value' => isset($user['manager']) && !empty($user['manager']) ? $user['manager'] : '',
      '#description' => t('Manager'),
      '#required' => TRUE,
    );
    $form['sipi_user']['invent']['data'][$i]['plan'] = array(
      '#title' => t('Plan'),
      '#type' => 'select',
      '#options' => get_sipi_plans(),
      '#default_value' => isset($user['plan']) && !empty($user['plan']) ? $user['plan'] : '',
      '#description' => t('Plans'),
      '#required' => TRUE,
    );
    $format = 'Y-m-d';
    $date = date($format);
    $form['sipi_user']['invent']['data'][$i]['start_date'] = array(
      '#title' => t('Start date'),
      '#type' => 'date_select',
      '#default_value' => isset($user['start_date']) && !empty($user['start_date']) ? $user['start_date'] : $date,
      '#date_format' => $format,
      '#date_label_position' => 'within',
      '#date_timezone' => 'America/Mexico_City',
      '#date_year_range' => '-3:+3',
      '#required' => TRUE,
      '#attributes' => array('class' => array('left')),
    );
    $form['sipi_user']['invent']['data'][$i]['end_date'] = array(
      '#title' => t('End date'),
      '#type' => 'date_select',
      '#default_value' => isset($user['end_date']) && !empty($user['end_date']) ? $user['end_date'] : $date,
      '#date_format' => $format,
      '#date_label_position' => 'within',
      '#date_timezone' => 'America/Mexico_City',
      '#date_year_range' => '-3:+3',
      '#required' => TRUE,
      '#attributes' => array('class' => array('left')),
    );
    $form['sipi_user']['invent']['data'][$i]['status'] = array(
      '#title' => t('Status'),
      '#type' => 'select',
      '#options' => array(
        '0' => t('Disabled'),
        '1' => t('Enabled'),
        '2' => t('Suspended'),
      ),
      '#default_value' => isset($user['status']) && !empty($user['status']) ? $user['status'] : '',
      '#description' => t('Status'),
      '#required' => TRUE,
    );
    if ($form_state['sipi_user']['invent']['items'] > 1) {
      $form['sipi_user']['invent']['data'][$i]['remove'] = array(
        '#type' => 'submit',
        '#value' => t('Remove'),
        '#submit' => array('sipi_user_remove_one'),
        '#ajax' => array(
          'callback' => 'sipi_user_add_more',
          'wrapper'  => 'invent-fieldset-wrapper',
        ),
      );
    }
  }
  $form['sipi_user']['invent']['add'] = array(
    '#title' => t('Add more'),
    '#type'  => 'submit',
    '#submit' => array('sipi_user_add_more_add_one'),
    '#value' => t('Add more'),
    '#ajax'  => array(
      'callback' => 'sipi_user_add_more',
      'wrapper'  => 'invent-fieldset-wrapper',
    ),
  );

  $form['cancel'] = array(
    '#markup' => l(t('Cancel'), 'sipi/user', array('attributes' => array('style'=>'display:inline-block;float:left;padding:8px;'))),
  );
  $form['submit'] = array(
    '#type'   => 'submit',
    '#value'  => t('Save'),
  );

  return $form;
}

function sipi_user_add_more_add_one($form, &$form_state) {
  $form_state['sipi_user']['invent']['items']++;
  $form_state['rebuild'] = TRUE;
}
function sipi_user_remove_one($form, &$form_state) {
  if ($form_state['sipi_user']['invent']['items'] > 1) {
    $form_state['sipi_user']['invent']['items']--;
  }
  $form_state['rebuild'] = TRUE;
}
function sipi_user_add_more($form, $form_state){
  return $form['sipi_user']['invent'];
}

function sipi_users_form_validate($form, &$form_state){
  /**
#sipi_users_form_submit
#values
  array(6) {
    ["sipi_user"]=>
  array(3) {
      ["uid"]=>
    int(0)
    ["client"]=>
    array(19) {
        ["firstname"]=>
      string(4) "Luis"
      ["lastname"]=>
      string(9) "Contreras"
      ["mail"]=>
      string(17) "luis@inventmx.com"
      ["pass"]=>
      string(8) "sapidecv"
      ["company"]=>
      string(6) "invent"
      ["cellphone"]=>
      string(13) "0445522525275"
      ["phone"]=>
      string(8) "51283600"
      ["extention"]=>
      string(4) "2027"
      ["web"]=>
      string(12) "inventmx.com"
      ["logo"]=>
      string(0) ""
      ["description"]=>
      string(61) "Somos una catapulta para el talento independiente en Internet"
      ["facebook"]=>
      string(27) "facebook.com/luis.contreras"
      ["twitter"]=>
      string(20) "twitter.com/imx_luis"
      ["googleplus"]=>
      string(29) "googleplus.com/luis.contreras"
      ["youtube"]=>
      string(26) "youtube.com/luis.contreras"
      ["instagram"]=>
      string(28) "instagram.com/luis.contreras"
      ["linkedin"]=>
      string(27) "linkedin.com/luis.contreras"
      ["pinterest"]=>
      string(28) "pinterest.com/luis.contreras"
      ["vine"]=>
      string(23) "vine.com/luis.contreras"
    }
    ["invent"]=>
    array(2) {
        ["data"]=>
      array(2) {
          [0]=>
        array(7) {
            ["site"]=>
          string(1) "1"
          ["manager"]=>
          string(2) "24"
          ["plan"]=>
          string(1) "1"
          ["start_date"]=>
          string(10) "2015-04-15"
          ["end_date"]=>
          string(10) "2015-07-15"
          ["status"]=>
          string(1) "1"
          ["remove"]=>
          string(6) "Remove"
        }
        [1]=>
        array(7) {
            ["site"]=>
          string(1) "3"
          ["manager"]=>
          string(2) "24"
          ["plan"]=>
          string(1) "2"
          ["start_date"]=>
          string(10) "2015-04-15"
          ["end_date"]=>
          string(10) "2015-07-15"
          ["status"]=>
          string(1) "1"
          ["remove"]=>
          string(6) "Remove"
        }
      }
      ["add"]=>
      string(8) "Add more"
    }
  }
  ["submit"]=>
  string(4) "Save"
  ["form_build_id"]=>
  string(48) "form-FVRFfvSldtrE9Wf3PrcX8OkY7_9cAf6p4tfVSlhqSBs"
  ["form_token"]=>
  string(43) "9HHBc9Zqi0zpJjiERAo0tlTO8ePixMiGbmGVUxFeevI"
  ["form_id"]=>
  string(15) "sipi_users_form"
  ["op"]=>
  string(4) "Save"
  */

}

function sipi_users_form_submit($form, &$form_state){
  $values=$form_state['values'];
  $timestamp=time();
  $fields=array(
    'sipi_users' => array(
      'uid'         => isset($values['uid']) && !empty($values['uid']) ? intval($values['uid']) : 0,
      'firstname'   => isset($values['firstname']) && !empty($values['firstname']) ? $values['firstname'] : '',
      'lastname'    => isset($values['lastname']) && !empty($values['lastname']) ? $values['lastname'] : '',
      'mail'        => isset($values['mail']) && !empty($values['mail']) ? $values['mail'] : '',
      'pass'        => isset($values['pass']) && !empty($values['pass']) ? $values['pass'] : '',
      'company'     => isset($values['company']) && !empty($values['company']) ? $values['company'] : '',
      'cellphone'   => isset($values['cellphone']) && !empty($values['cellphone']) ? $values['cellphone'] : '',
      'phone'       => isset($values['phone']) && !empty($values['phone']) ? $values['phone'] : '',
      'extention'   => isset($values['extention']) && !empty($values['extention']) ? $values['extention'] : '',
      'web'         => isset($values['web']) && !empty($values['web']) ? $values['web'] : '',
      'logo'        => isset($values['logo']) && !empty($values['logo']) ? $values['logo'] : '',
      'description' => isset($values['description']) && !empty($values['description']) ? $values['description'] : '',
      'facebook'    => isset($values['facebook']) && !empty($values['facebook']) ? $values['facebook'] : '',
      'twitter'     => isset($values['twitter']) && !empty($values['twitter']) ? $values['twitter'] : '',
      'googleplus'  => isset($values['googleplus']) && !empty($values['googleplus']) ? $values['googleplus'] : '',
      'youtube'     => isset($values['youtube']) && !empty($values['youtube']) ? $values['youtube'] : '',
      'instagram'   => isset($values['instagram']) && !empty($values['instagram']) ? $values['instagram'] : '',
      'linkedin'    => isset($values['linkedin']) && !empty($values['linkedin']) ? $values['linkedin'] : '',
      'pinterest'   => isset($values['pinterest']) && !empty($values['pinterest']) ? $values['pinterest'] : '',
      'vine'        => isset($values['vine']) && !empty($values['vine']) ? $values['vine'] : '',
      'created'     => $timestamp,
      'changed'     => $timestamp,
      'access'      => $timestamp,
      'login'       => $timestamp,
    ),
  );

  foreach($values['invent']['data'] as $plan){
    $fields['sipi_plans_users'][]=array(
      'mid'        => isset($plan['mid']) && !empty($plan['mid']) ? intval($plan['mid']) : 0,
      'pid'        => isset($plan['pid']) && !empty($plan['pid']) ? intval($plan['pid']) : '',
      'uid'        => isset($plan['uid']) && !empty($plan['uid']) ? intval($plan['uid']) : 0,
      'manager'    => isset($plan['manager']) && !empty($plan['manager']) ? intval($plan['manager']) : 0,
      'status'     => isset($plan['status']) && !empty($plan['status']) ? $plan['status'] : 0,
      'site'       => isset($plan['site']) && !empty($plan['site']) ? $plan['site'] : '',
      'start_date' => isset($plan['']) && !empty($plan['']) ? $plan[''] : '',
      'end_date'   => isset($plan['']) && !empty($plan['']) ? $plan[''] : '',
    );
  }
}

function sipi_users_save($values){
  $uid=isset($values['uid']) && !empty($values['uid']) ? $values['uid'] : 0;
  $data=array(
    'name'     => $values['name'],
    'contents' => $values['contents'],
    'posts'    => $values['posts'],
    'duration' => $values['duration'],
    'price'    => $values['price'],
  );

  //Search
  $query=db_select('sipi_users','su');
  $query->fields('su', array('uid','firstname','lastname','mail','pass','company','cellphone','phone','extention','web','logo','description','facebook','twitter','googleplus','youtube','instagram','linkedin','pinterest','vine','created','changed','access','login'));
  $query->condition('su.uid',$uid,'=');
  $result=$query->execute()->fetchAssoc();
  if($result){
    sipi_users_save_op('update',$data,$result);
  }else{
    sipi_users_save_op('insert',$data,$result);
  }
}

/**
 *
 * @param array $field Fields array for insert or update values
 * @return boolean
 */
function sipi_users_save_op($delta='insert',$fields,$result){
  global $user;
  switch($delta){
    case 'insert':
      $query=db_insert('sipi_users');
      drupal_set_message('User inserted.','status');
      sipi_logging('Insert new user:['.$fields['firstname'].'] by user:['.$user->name.']','info');
      break;
    case 'update':
      $fields['uid']=$result['uid'];
      $query=db_update('sipi_users');
      $query->condition('uid',$result['uid'],'=');
      drupal_set_message('User updated.','status');
      sipi_logging('Update user:['.$fields['firtname'].'] by user:['.$user->name.']','info');
      break;
  }
  $query->fields($fields);
  $result=$query->execute();
  if($result){
    sipi_logging('Done!','info');
  }else{
    sipi_logging('Something went wrong. Error['.mysql_error().'].','error');
  }
}

function get_sipi_user_manager($roles=array('sipi_manager')){
  $query=db_select('users','u');
  $query->fields('u', array('uid','name','mail'));
  $query->join('users_roles','ur','ur.uid=u.uid');
  $query->join('role','r','r.rid=ur.rid AND r.name in (\''.implode("','",$roles).'\')');
  $result=$query->execute();
  if($result){
    $items=array(
      0 => t('Select one manager for this client'),
    );
    foreach($result as $row){
      $items[$row->uid]=$row->name;
    }
    return $items;
  }
  return null;
}

function get_sipi_plans(){
  $query=db_select('sipi_plans','p');
  $query->fields('p', array('pid','name'));
  $result=$query->execute();
  if($result){
    $items=array(
      0 => t('Select one plan for this client'),
    );
    foreach($result as $row){
      $items[$row->pid]=$row->name;
    }
    return $items;
  }
  return null;
}

function get_sipi_sites(){
  $query=db_select('taxonomy_term_data','td');
  $query->fields('td', array('tid','name'));
  $query->condition('td.vid',1,'=');
  $query->orderBy('td.vid','ASC');
  $result=$query->execute();
  if($result){
    $items=array(
      0 => t('Select one Site for this client'),
    );
    foreach($result as $row){
      $items[$row->tid]=$row->name;
    }
    return $items;
  }
  return null;
}


function sipi_user_list(){
  $header = array(
    array(
      'data' => t('UID'),
      'field' => 'u.uid',
    ),
    array(
      'data' => t('Clientes'),
      'field' => 'u.name',
    ),
    array(
      'data' => t('Ejecutivo de atención'),
      'data' => 'manager.name',
    ),
    array(
      'data' => t('Sitio'),
      'field' => 's.name',
    ),
    array(
      'data' => t('Plan'),
      'field' => 'p.name',
    ),
    array(
      'data' => t('Estatus'),
      'field' => 'pu.status'
    ),
    array(
      'data' => t('Contenidos Publicados'),
      'field' => 'pu.published',
    ),
    array(
      'data' => t('Contenidos Restantes'),
    ),
    array(
      'data' => t('Fecha de inicio'),
    ),
    array(
      'data' => t('Fecha de término'),
    ),
    array(
      'data' => t('Acciones'),
    ),
  );

  // Default ordering
  if (!isset($_GET['order']) && !isset($_GET['sort'])) {
    $_GET['order'] = t('UID');
    $_GET['sort'] = 'ASC';
  }

  $query = db_select('sipi_user', 'p')->extend('PagerDefault');
  $query->limit(20);
  $query->fields('p', array('pid','name','contents','posts','duration','price'));
  $query = $query->extend('TableSort')->orderByHeader($header);
  $result = $query->execute();
  $rows = array();
  foreach ($result as $row) {
    $rows[] = array(
      $row->pid,
      l($row->name, "sipi/plans/$row->pid/edit"),
      $row->contents,
      $row->posts,
      $row->duration.' '.t('month(s)'),
      '$ '.$row->price.' '.t('MXN'),
      l(t('Edit'),"sipi/plans/$row->pid/edit",array(),'destination=sipi/plans') .' | '. l(t('Delete'),"sipi/plans/$row->pid/delete",array(),'destination=sipi/plans'),
    );
  }
  if (count($rows) && ($pager = theme('pager'))) {
    $rows[] = array(
      array(
        'data' => $pager,
        'colspan' => 7,
      ),
    );
  }
  $build['sipi_user_list'] = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
    '#empty' => t('There are no plans.'),
  );
  return $build;

}