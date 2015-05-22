<?php

function sipi_login(){
  global $user;
  if(!$user->uid){
    module_load_include('module','user');
    return drupal_get_form('user_login');
  }else{
    return sipi_dashboard();
  }
}

function sipi_dashboard(){
  global $user;

  $dashboard=null;
  if (in_array('sipi_god', $user->roles)) {
    // Check if the user has the 'sipi_god' role.
    //$dashboard=drupal_render(sipi_expire_list('sipi_god'));
    $dashboard=drupal_get_form('sipi_clients_list_form');
  }else if (in_array('sipi_director', $user->roles)) {
    // Check if the user has the 'sipi_director' role.
    $dashboard=drupal_get_form('sipi_clients_list_form');
  }else if (in_array('sipi_manager', $user->roles)) {
    // Check if the user has the 'sipi_manager' role.
    $dashboard=sipi_expire_list('sipi_manager');
  }else if (in_array('sipi_executive', $user->roles)) {
    // Check if the user has the 'sipi_executive' role.
    $dashboard=sipi_expire_list('sipi_executive');
  }else if (in_array('sipi', $user->roles)) {
    // Check if the user has the 'sipi' role.
    $dashboard=sipi_expire_list();
  }

  return $dashboard;
}

function sipi_expire_list($role='sipi') {
  global $user;
  //Boundrys or limits
  $limit=30; //Days or Frequency
  $limit=$limit*24*60*60; //Get seconds
  $today=mktime(0,0,0,date('m'),date('d'),date('Y'));
  $nextLimit=$today+$limit; //Next time expiring $today+$limit

  $header = array(
    array(
      'data' => t('CID'),
      'field' => 'c.cid',
    ),
    array(
      'data' => t('Clientes'),
      'field' => 'c.name',
    ),
    array(
      'data' => t('Ejecutivo de atención'),
      'field' => 'manager',
    ),
    array(
      'data' => t('Sitio'),
      'field' => 'site',
    ),
    array(
      'data' => t('Plan'),
      'field' => 'plan',
    ),
    array(
      'data' => t('Estatus'),
      'field' => 'pc.status'
    ),
    array(
      'data' => t('Contenidos Publicados'),
    ),
    array(
      'data' => t('Contenidos Restantes'),
    ),
    array(
      'data' => t('Fecha de inicio'),
      'field' => 'pc.start_date'
    ),
    array(
      'data' => t('Fecha de término'),
      'field' => 'pc.end_date'
    ),
    array(
      'data' => t('Acciones'),
    ),
  );

  // Default ordering
  if (!isset($_GET['order']) && !isset($_GET['sort'])) {
    $_GET['order'] = t('CID');
    $_GET['sort'] = 'ASC';
  }

  $query = db_select('sipi_clients', 'c')->extend('PagerDefault');
  $query->join('sipi_plans_clients', 'pc', 'pc.cid=c.cid');
  $query->join('sipi_plans', 'p', 'p.pid=pc.pid');
  $query->join('users', 'u', 'u.uid=pc.uid');
  $query->join('taxonomy_term_data', 'td', 'td.tid=pc.site');
  $query->limit(10);
  $query->fields('c', array('cid', 'name'));
  $query->addField('pc', 'status', 'status');
  $query->addField('pc', 'start_date', 'start_date');
  $query->addField('pc', 'end_date', 'end_date');
  $query->addField('p', 'name', 'plan');
  $query->addField('u', 'name', 'manager');
  $query->addField('td', 'name', 'site');
  if ($role == 'sipi_executive') {
    $query->condition('pc.uid', $user->uid, '=');
  }
  $query->condition('pc.end_date',array($today,$nextLimit),'BETWEEN');

  $query=$query->extend('TableSort')->orderByHeader($header);
  $result=$query->execute();
  $rows=array();
  foreach ($result as $row) {
    $rows[] = array(
      $row->cid,
      l($row->name, "sipi/client/$row->cid/view",array('query'=>array('destination'=>'sipi'))),
      $row->manager,
      $row->site,
      $row->plan,
      ($row->status==0 ? t('Disabled') : ($row->status==1 ? t('Enabled') : 'N/D')),
      'contents published',
      'remain contents',
      date('Y-m-d',$row->start_date),
      date('Y-m-d',$row->end_date),
      l(t('Details'),"sipi/client/$row->cid/view"  ,array('query'=>array('destination'=>'sipi'))) .' <br> '.
      l(t('Edit')   ,"sipi/client/$row->cid/edit"  ,array('query'=>array('destination'=>'sipi'))),
    );
  }
  if (count($rows) && ($pager = theme('pager'))) {
    $rows[] = array(
      array(
        'data' => $pager,
        'colspan' => 11,
      ),
    );
  }
  $build['sipi_client_list'] = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
    '#empty' => t('There are no plans or accounts that expire in the next few days.'),
    '#caption' => t('Next expires'),
  );
  return $build;

}


function sipi_clients_list_form($form, &$form_state){
  $form=array();
  $form['sipi_filter_clients'] = array(
    '#type' => 'fieldset',
    '#title' => t('Filters'),
  );

  $sipi_filter=isset($_SESSION['sipi_filters']) ? $_SESSION['sipi_filters'] : array();
  if(isset($form_state['filters'])){
    $sipi_filter=array(
      'date'   => $form_state['filters']['date'],
      'status' => $form_state['filters']['status'],
    );
  }
  $date_format = 'F';
  $date = date($date_format);

  $header = array(
    array(
      'data' => t('Clientes'),
      'field' => 'c.name',
    ),
    array(
      'data' => t('Ejecutivo de atención'),
      'field' => 'manager',
    ),
    array(
      'data' => t('Sitio'),
      'field' => 'site',
    ),
    array(
      'data' => t('Plan'),
      'field' => 'plan',
    ),
    array(
      'data' => t('Estatus'),
      'field' => 'pc.status'
    ),
    array(
      'data' => t('Contenidos Publicados'),
    ),
    array(
      'data' => t('Contenidos Restantes'),
    ),
    array(
      'data' => t('Fecha de inicio'),
      'field' => 'pc.start_date'
    ),
    array(
      'data' => t('Fecha de término'),
      'field' => 'pc.end_date'
    ),
    array(
      'data' => t('Acciones'),
    ),
  );

  // Default ordering
  if (!isset($_GET['order']) && !isset($_GET['sort'])) {
    $_GET['order'] = t('Fecha de inicio');
    $_GET['sort'] = 'DESC';
  }

  // Form ordering

  $query = db_select('sipi_clients', 'c')->extend('PagerDefault');
  $query->join('sipi_plans_clients','pc','pc.cid=c.cid');
  $query->join('sipi_plans','p','p.pid=pc.pid');
  $query->join('users','u','u.uid=pc.uid');
  $query->join('taxonomy_term_data','td','td.tid=pc.site');
  $query->join('sipi_clients_invent_users','ui','ui.cid=c.cid');
  $query->limit(10);
  $query->fields('c',array('cid','name'));
  $query->addField('pc','status','status');
  $query->addField('pc','start_date','start_date');
  $query->addField('pc','end_date','end_date');
  $query->addField('p','name','plan');
  $query->addField('p','contents','contents_limit');
  $query->addField('ui','nodes_published','contents_published');
  $query->addField('u','name','manager');
  $query->addField('td','name','site');

  $query=$query->extend('TableSort')->orderByHeader($header);
  $result=$query->execute();
  $rows=array();
  foreach ($result as $row) {
    $rows[] = array(
      l($row->name, "sipi/client/$row->cid/view",array('query'=>array('destination'=>'sipi/client'))),
      $row->manager,
      $row->site,
      $row->plan,
      ($row->status==0 ? t('Disabled') : ($row->status==1 ? t('Enabled') : 'N/D')),
      $row->contents_published,
      ($row->contents_published>0 ? $row->contents_limit-$row->contents_published : 0),
      date('Y-m-d',$row->start_date),
      date('Y-m-d',$row->end_date),
      l(t('Details'),"sipi/client/$row->cid/view"  ,array('query'=>array('destination'=>'sipi/client'))),
    );
  }
  if (count($rows) && ($pager = theme('pager'))) {
    $rows[] = array(
      array(
        'data' => $pager,
        'colspan' => 10,
      ),
    );
  }

  $form['sipi_filter_clients']['sipi_filter_date'] = array(
    '#type' => 'date_select',
    '#date_format' => $date_format,
    '#default_value' => isset($sipi_filter['date']) && !empty($sipi_filter['date']) ? $sipi_filter['date'] : $date,
    '#date_label_position' => 'left',
    '#date_timezone' => 'America/Mexico_City',
    '#date_year_range' => '-3:+3',
    '#description' => t('Select a month'),
    '#attributes' => array('class' => array('left')),
  );

  $form['sipi_filter_clients']['sipi_filter_status'] = array(
    '#title' => t('Status'),
    '#type' => 'select',
    '#options' => array(
      'select'     => t('Select a status'),
      'all'        => t('All'),
      'disabled'   => t('Disabled'),
      'enabled'    => t('Enabled'),
      'terminated' => t('Terminated'),
      'suspended'  => t('Suspended'),
      'canceled'   => t('Canceled'),
    ),
    '#default_value' => isset($sipi_filter['status']) && !empty($sipi_filter['status']) ? $sipi_filter['status'] : 'select',
    '#description' => t('Select a status'),
    '#attributes' => array('class' => array('left')),
  );

  $form['sipi_filter_clients']['sipi_filter_submit'] = array(
    '#value' => t('Filter'),
    '#type'  => 'submit',
    '#attributes' => array('class' => array('left')),
  );

  $form['sipi_filter_clients']['sipi_filter_submit'] = array(
    '#value' => t('Filter'),
    '#type'  => 'submit',
    '#attributes' => array('class' => array('left')),
  );

  $form['table'] = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
    '#empty' => t('There are no clients in the system.'),
    '#caption' => t('Clients List'),
  );

  return $form;
}

function sipi_clients_list_form_submit($form, &$form_state){
  //Session filters
  $values=$form_state['values'];
  $status=isset($values['sipi_filter_status']) && $values['sipi_filter_status']!=='select' ? $values['sipi_filter_status'] : 'select';
  $month =isset($values['sipi_filter_date']) ? $values['sipi_filter_date'] : date('n');
  $form_state['filters']=array(
    'date'  => $month,
    'status' => $status,
  );
  $_SESSION['sipi_filters']=$form_state['filters'];
  $form_state['rebuild']=TRUE;
}
