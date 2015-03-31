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
  $form['sipi_user'] = array(
    '#type'  => 'fieldset',
    '#title' => !isset($user) || empty($user) ? t('Add a user') : t('Edit a user'),
  );
  $form['sipi_user']['uid']  = array(
    '#type' => 'hidden',
    '#value' => isset($user['uid']) && !empty($user['uid']) ? $user['uid'] : 0,
  );
  $form['sipi_user']['firstname'] = array(
    '#title'         => t('Name'),
    '#type'          => 'textfield',
    '#size'          => 30,
    '#maxlength'     => 100,
    '#default_value' => isset($user['firstname']) && !empty($user['firstname']) ? $user['firstname'] : '',
    '#description'   => t('First name'),
    '#required'      => TRUE,
  );
  $form['sipi_user']['lastname'] = array(
    '#title'         => t('Last name'),
    '#type'          => 'textfield',
    '#size'          => 30,
    '#maxlength'     => 100,
    '#default_value' => isset($user['lastname']) && !empty($user['lastname']) ? $user['lastname'] : '',
    '#description'   => t('Last name'),
    '#required'      => TRUE,
  );
  $form['sipi_user']['mail'] = array(
    '#title'         => t('Email'),
    '#type'          => 'textfield',
    '#size'          => 60,
    '#maxlength'     => 150,
    '#default_value' => isset($user['mail']) && !empty($user['mail']) ? $user['mail'] : '',
    '#description'   => t('Email'),
    '#required'      => TRUE,
  );
  $form['sipi_user']['pass'] = array(
    '#title'         => t('Confirm password'),
    '#type'          => 'password_confirm ',
    '#size'          => 15,
    '#maxlength'     => 32,
    '#description'   => t('Password'),
    '#required'      => TRUE,
  );
  $form['sipi_user']['company'] = array(
    '#title'         => t('Company'),
    '#type'          => 'textfield',
    '#size'          => 60,
    '#maxlength'     => 150,
    '#default_value' => isset($user['company']) && !empty($user['company']) ? $user['company'] : '',
    '#description'   => t('Social posts'),
  );
  $form['sipi_user']['cellphone'] = array(
    '#title'         => t('Cell phone'),
    '#type'          => 'textfield',
    '#size'          => 20,
    '#maxlength'     => 20,
    '#default_value' => isset($user['cellphone']) && !empty($user['cellphone']) ? $user['cellphone'] : '',
    '#description'   => t('Cell phone'),
  );
  $form['sipi_user']['phone'] = array(
    '#title'         => t('Phone'),
    '#type'          => 'textfield',
    '#size'          => 30,
    '#maxlength'     => 60,
    '#default_value' => isset($user['phone']) && !empty($user['phone']) ? $user['phone'] : '',
    '#description'   => t('Phone'),
  );
  $form['sipi_user']['extention'] = array(
    '#title'         => t('Extention'),
    '#type'          => 'textfield',
    '#size'          => 10,
    '#maxlength'     => 10,
    '#default_value' => isset($user['extention']) && !empty($user['extention']) ? $user['extention'] : '',
    '#description'   => t('Extention'),
  );
  $form['sipi_user']['web'] = array(
    '#title'         => t('Web page'),
    '#type'          => 'textfield',
    '#size'          => 10,
    '#maxlength'     => 10,
    '#default_value' => isset($user['web']) && !empty($user['web']) ? $user['web'] : '',
    '#description'   => t('Web page'),
  );
  $form['sipi_user']['logo'] = array(
    '#title'         => t('Logo'),
    '#type'          => 'textfield',
    '#size'          => 10,
    '#maxlength'     => 10,
    '#default_value' => isset($user['logo']) && !empty($user['logo']) ? $user['logo'] : '',
    '#description'   => t('Logo'),
  );
  $form['sipi_user']['description'] = array(
    '#title'         => t('Description'),
    '#type'          => 'textfield',
    '#size'          => 10,
    '#maxlength'     => 10,
    '#default_value' => isset($user['description']) && !empty($user['description']) ? $user['description'] : '',
    '#description'   => t('Description'),
  );
  $form['sipi_user']['facebook'] = array(
    '#title'         => t('Facebook'),
    '#type'          => 'textfield',
    '#size'          => 40,
    '#maxlength'     => 150,
    '#default_value' => isset($user['facebook']) && !empty($user['facebook']) ? $user['facebook'] : '',
    '#description'   => t('Facebook'),
  );
  $form['sipi_user']['twitter'] = array(
    '#title'         => t('Twitter'),
    '#type'          => 'textfield',
    '#size'          => 40,
    '#maxlength'     => 150,
    '#default_value' => isset($user['twitter']) && !empty($user['twitter']) ? $user['twitter'] : '',
    '#description'   => t('Twitter'),
  );
  $form['sipi_user']['googleplus'] = array(
    '#title'         => t('Google+'),
    '#type'          => 'textfield',
    '#size'          => 40,
    '#maxlength'     => 150,
    '#default_value' => isset($user['googleplus']) && !empty($user['googleplus']) ? $user['googleplus'] : '',
    '#description'   => t('Google+'),
  );
  $form['sipi_user']['youtube'] = array(
    '#title'         => t('Youtube'),
    '#type'          => 'textfield',
    '#size'          => 40,
    '#maxlength'     => 150,
    '#default_value' => isset($user['youtube']) && !empty($user['youtube']) ? $user['youtube'] : '',
    '#description'   => t('Youtube'),
  );
  $form['sipi_user']['instagram'] = array(
    '#title'         => t('Instagram'),
    '#type'          => 'textfield',
    '#size'          => 40,
    '#maxlength'     => 150,
    '#default_value' => isset($user['instagram']) && !empty($user['instagram']) ? $user['instagram'] : '',
    '#description'   => t('Instagram'),
  );
  $form['sipi_user']['Linkedin'] = array(
    '#title'         => t('linkedin'),
    '#type'          => 'textfield',
    '#size'          => 40,
    '#maxlength'     => 150,
    '#default_value' => isset($user['linkedin']) && !empty($user['linkedin']) ? $user['linkedin'] : '',
    '#description'   => t('Linkedin'),
  );
  $form['sipi_user']['pinterest'] = array(
    '#title'         => t('Pinterest'),
    '#type'          => 'textfield',
    '#size'          => 40,
    '#maxlength'     => 150,
    '#default_value' => isset($user['pinterest']) && !empty($user['pinterest']) ? $user['pinterest'] : '',
    '#description'   => t('Pinterest'),
  );
  $form['sipi_user']['vine'] = array(
    '#title'         => t('Vine'),
    '#type'          => 'textfield',
    '#size'          => 40,
    '#maxlength'     => 150,
    '#default_value' => isset($user['vine']) && !empty($user['vine']) ? $user['vine'] : '',
    '#description'   => t('Vine'),
  );

  $form['sipi_user_invent'] = array(
    '#type'  => 'fieldset',
    '#title' => !isset($user) || empty($user) ? t('Add Data Invent') : t('Edit Data Invent'),
  );
  $form['sipi_user_invent']['site'] = array(
    '#title'         => t('Site name'),
    '#type'          => 'select',
    '#options'       => get_sipi_sites(),
    '#default_value' => isset($user['site']) && !empty($user['site']) ? $user['site'] : '',
    '#description'   => t('Site name'),
    '#required'      => TRUE,
  );
  $form['sipi_user_invent']['manager'] = array(
    '#title'         => t('Manager'),
    '#type'          => 'select',
    '#options'       => get_sipi_user_manager(array('sipi_manager')),
    '#default_value' => isset($user['manager']) && !empty($user['manager']) ? $user['manager'] : '',
    '#description'   => t('Manager'),
    '#required'      => TRUE,
  );
  $form['sipi_user_invent']['plan'] = array(
    '#title'         => t('Plan'),
    '#type'          => 'select',
    '#options'       => get_sipi_plans(),
    '#default_value' => isset($user['plan']) && !empty($user['plan']) ? $user['plan'] : '',
    '#description'   => t('Plans'),
    '#required'      => TRUE,
  );
  $format = 'Y-m-d';
  $date = date($format);
  $form['sipi_user_invent']['start_date'] = array(
    '#title'         => t('Start date'),
    '#type'          => 'date_select',
    '#default_value' => isset($user['start_date']) && !empty($user['start_date']) ? $user['start_date'] : $date,
    '#date_format'   => $format,
    '#date_label_position' => 'within',
    '#date_timezone' => 'America/Mexico_City',
    '#date_year_range' => '-3:+3',
    '#required'      => TRUE,
    '#attributes'    => array('class' => array('left')),
  );
  $form['sipi_user_invent']['end_date'] = array(
    '#title'         => t('End date'),
    '#type'          => 'date_select',
    '#default_value' => isset($user['end_date']) && !empty($user['end_date']) ? $user['end_date'] : $date,
    '#date_format'   => $format,
    '#date_label_position' => 'within',
    '#date_timezone' => 'America/Mexico_City',
    '#date_year_range' => '-3:+3',
    '#required'      => TRUE,
    '#attributes'    => array('class' => array('left')),
  );
  $form['sipi_user_invent']['status'] = array(
    '#title'         => t('Status'),
    '#type'          => 'select',
    '#options'       => array(
      '0' => t('Disabled'),
      '1' => t('Enabled'),
      '2' => t('Suspended'),
    ),
    '#default_value' => isset($user['status']) && !empty($user['status']) ? $user['status'] : '',
    '#description'   => t('Status'),
    '#required'      => TRUE,
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