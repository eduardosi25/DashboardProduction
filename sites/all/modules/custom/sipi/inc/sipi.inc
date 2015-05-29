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

  // Check if the user has the 'sipi_god' role.
  if (in_array('sipi_god', $user->roles)) {
    $dashboard=sipi_expire_list('sipi_god');
  }
  // Check if the user has the 'sipi_director' role.
  if (in_array('sipi_director', $user->roles)) {
    $dashboard=sipi_expire_list('sipi_director');
  }
  // Check if the user has the 'sipi_manager' role.
  if (in_array('sipi_manager', $user->roles)) {
    $dashboard=sipi_expire_list('sipi_manager');
  }
  // Check if the user has the 'sipi_executive' role.
  if (in_array('sipi_executive', $user->roles)) {
    $dashboard=sipi_expire_list('sipi_executive');
  }
  // Check if the user has the 'sipi' role.
  if (in_array('sipi', $user->roles)) {
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
    '#empty' => t('There are no clients.'),
    '#caption' => 'Próximas finalizaciones',
  );
  return $build;

}
