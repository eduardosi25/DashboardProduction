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
  if (in_array('sipi_god', $user->roles) || user_access('administer')) {
    // Check if the user has the 'sipi_god' role.
    //$dashboard=drupal_render(sipi_expire_list('sipi_god'));
    $dashboard=drupal_get_form('sipi_clients_list_form');
  }else if (in_array('sipi_director', $user->roles) || user_access('administer')) {
    // Check if the user has the 'sipi_director' role.
    $dashboard=drupal_get_form('sipi_clients_list_form');
  }else if (in_array('sipi_manager', $user->roles) || user_access('administer')) {
    // Check if the user has the 'sipi_manager' role.
    $dashboard=sipi_expire_list('sipi_manager');
  }else if (in_array('sipi_executive', $user->roles) || user_access('administer')) {
    // Check if the user has the 'sipi_executive' role.
    $dashboard=sipi_expire_list('sipi_executive');
  }else if (in_array('sipi', $user->roles) || user_access('administer')) {
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
  $query->limit(20);
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
      l($row->name, "codiga/client/$row->cid/view",array('query'=>array('destination'=>'sipi'))),
      $row->manager,
      $row->site,
      $row->plan,
      ($row->status==0 ? t('Disabled') : ($row->status==1 ? t('Enabled') : 'N/D')),
      'contents published',
      'remain contents',
      date('Y-m-d',$row->start_date),
      date('Y-m-d',$row->end_date),
      l(t('Details'),"codiga/client/$row->cid/view"  ,array('query'=>array('destination'=>'sipi'))) .' <br> '.
      l(t('Edit')   ,"codiga/client/$row->cid/edit"  ,array('query'=>array('destination'=>'sipi'))),
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
    '#empty' => 'No se encontraron planes o clientes que puedan expirar en los próximos días.',
    '#caption' => 'Próximas finalizaciones',
  );
  return $build;

}


function sipi_clients_list_form($form, &$form_state){
  $form=array();
  $form['sipi_filter_clients'] = array(
    '#type' => 'fieldset',
    '#title' => 'Filtros',
  );

  $sipi_filter=isset($_SESSION['sipi_filters']) ? $_SESSION['sipi_filters'] : array();

  #echo '<pre>';
  #var_dump($sipi_filter);
  #echo '</pre><hr>';

  if(isset($form_state['filters'])){
    $sipi_filter=array(
      'year'   => $form_state['filters']['year'],
      'month'  => $form_state['filters']['month'],
      'status' => $form_state['filters']['status'],
    );
  }

  #echo '<pre>';
  #var_dump($sipi_filter);
  #echo '</pre><hr>';

  $date_format_year = 'Y';
  $date_format_month = 'F';
  $date_year = date($date_format_year);
  $date_month = date($date_format_month);

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

  $query = db_select('sipi_clients', 'c')->extend('PagerDefault');
  $query->join('sipi_plans_clients','pc','pc.cid=c.cid');
  $query->join('sipi_plans','p','p.pid=pc.pid');
  $query->join('users','u','u.uid=pc.uid');
  $query->join('taxonomy_term_data','td','td.tid=pc.site');
  $query->leftJoin('sipi_clients_invent_users','ui','ui.cid=c.cid');
  $query->limit(10);

  $query->fields('c',array('cid','name'));
  $query->addField('pc','status','status');
  $query->addField('pc','start_date','start_date');
  $query->addField('pc','end_date','end_date');
  $query->addField('pc','uid','uid');
  $query->addField('p','name','plan');
  $query->addField('p','contents','contents_limit');

  #$query->addField('ui','nodes_published','contents_published');

  $query->addField('u','name','manager');
  $query->addField('td','name','site');
  $query->addField('td','tid','idsite');

  $query->addField('ui','uid','uid_invent');

  $query->groupBy('c.cid');
  $query->groupBy('c.name');
  $query->groupBy('td.tid');

  #print $query;
  #die();

  if(isset($sipi_filter) && !empty($sipi_filter) && count($sipi_filter)>0){
    if($sipi_filter['status']!=='select' && $sipi_filter['status']!=='all'){
      $query->condition('pc.status',sipi_filters_get_status_plans_clients($sipi_filter['status']),'=');
    }
    if(isset($sipi_filter['year']) || isset($sipi_filter['month'])){
      $queryDates=sipi_filters_get_dates_plans_clients($sipi_filter);
      $query->condition('pc.start_date',$queryDates,'BETWEEN');
    }
  }

  $query=$query->extend('TableSort')->orderByHeader($header);
  $result=$query->execute();

  $rows=array();
  foreach ($result as $row) {
    $contents_published=sipi_client_get_nodes_published($row->cid, $row->idsite);
    $rows[] = array(
      l($row->name, "codiga/client/$row->cid/view/".$row->idsite,array('query'=>array('destination'=>'codiga/client'))),
      $row->manager,
      $row->site,
      $row->plan,
      ($row->status==0 ? t('Disabled') : ($row->status==1 ? t('Enabled') : 'N/D')),
      (isset($contents_published) && !empty($contents_published) ? (count($contents_published)>0 ? count($contents_published) : 0) : 0),
      (isset($contents_published) && !empty($contents_published) ? $row->contents_limit-count($contents_published) : 0),
      date('Y-m-d',$row->start_date),
      date('Y-m-d',$row->end_date),
      l(t('Details'),"codiga/client/$row->cid/view/".$row->idsite  ,array('query'=>array('destination'=>'codiga/client'))),
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

  $form['sipi_filter_clients']['sipi_filter_year'] = array(
    '#type' => 'date_select',
    '#date_format' => $date_format_year,
    '#default_value' => isset($sipi_filter['year']) && !empty($sipi_filter['year']) ? $sipi_filter['year'] : $date_year,
    '#date_label_position' => 'left',
    '#date_timezone' => 'America/Mexico_City',
    '#date_year_range' => '-3:+3',
    '#description' => 'Selecciona un a&nacute;o',
    '#attributes' => array('class' => array('left')),
  );

  $form['sipi_filter_clients']['sipi_filter_month'] = array(
    '#type' => 'date_select',
    '#date_format' => $date_format_month,
    '#default_value' => isset($sipi_filter['month']) && !empty($sipi_filter['month']) ? $sipi_filter['month'] : $date_month,
    '#date_label_position' => 'left',
    '#date_timezone' => 'America/Mexico_City',
    '#description' => 'Selecciona un mes',
    '#attributes' => array('class' => array('left')),
  );

  $form['sipi_filter_clients']['sipi_filter_status'] = array(
    '#title' => t('Status'),
    '#type' => 'select',
    '#options' => array(
      'select'     => t('Elige...'),
      'all'        => t('All'),
      'disabled'   => t('Disabled'),
      'enabled'    => t('Enabled'),
      'terminated' => t('Terminated'),
      'suspended'  => t('Suspended'),
      'canceled'   => t('Canceled'),
    ),
    '#default_value' => isset($sipi_filter['status']) && !empty($sipi_filter['status']) ? $sipi_filter['status'] : 'select',
    '#description' => t('Selecciona un estatus'),
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
    '#empty' => 'No se encontraron clientes registrados.',
    '#caption' => 'Clientes',
  );

  return $form;
}

function sipi_client_get_nodes_published($cid, $tid){

  $query = db_select('sipi_clients_invent_contents', 'ic');
  $query->join('sipi_clients_invent_users','iu','iu.uid=ic.uid');
  $query->join('sipi_clients','c','c.cid=ic.cid');

  $query->fields('c',array('cid','name','mail','company'));
  $query->addField('iu','uid','uid');
  $query->addField('iu','sitename','sitename');
  $query->addField('iu','pageviews','pageviews');
  $query->addField('iu','uid','uid');
  $query->condition('c.cid',$cid,'=');
  $query->condition('iu.tid',$tid,'=');
  $result=$query->execute();

  //print $query;

  //print_r($result->rowCount());


  if($result->rowCount()>0){
    $items=array();
    foreach($result as $row){
      $items[]=$row;
    }
    return $items;
  }
  return 0;
}

function sipi_clients_list_form_submit($form, &$form_state){
  //Session filters
  $values=$form_state['values'];
  $year  =isset($values['sipi_filter_year']) ? $values['sipi_filter_year'] : date('Y');
  $month =isset($values['sipi_filter_month']) ? $values['sipi_filter_month'] : 0;
  $status=isset($values['sipi_filter_status']) && $values['sipi_filter_status']!=='select' ? $values['sipi_filter_status'] : 'select';
  $form_state['filters']=array(
    'year'   => $year,
    'month'  => $month,
    'status' => $status,
  );
  $_SESSION['sipi_filters']=$form_state['filters'];
  $form_state['rebuild']=TRUE;
}

function sipi_filters_get_status_plans_clients($status){
  if(!isset($status) || empty($status) || $status==='select' || $status==='all')
    return null;

  switch($status){
    case 'disabled':
      return 0;
      break;
    case 'enabled':
      return 1;
      break;
    case 'terminated':
      return 2;
      break;
    case 'suspended':
      return 3;
      break;
    case 'canceled':
      return 4;
      break;
    default:
      return null;
      break;
  }
}

function sipi_filters_get_dates_plans_clients($filter) {

  //Only year
  if(!isset($filter['month']) || empty($filter['month']) || intval($filter['month']<=0)){
    $dates=array(
      0 => $filter['year'].'-01-01',
      1 => $filter['year'].'-12-31',
    );
  }

  //Only month
  if(!isset($filter['year']) || empty($filter['year']) || intval($filter['year']<=0)){
    $dates=array(
      0 => date('Y').'-'.$filter['month'].'-01',
      1 => date('Y').'-'.$filter['month'].'-'.date('t',strtotime(date('Y').'-'.$filter['month'].'-01')),
    );
  }

  //Year && month
  if(isset($filter['year']) && isset($filter['month']) && (intval($filter['year'])>0 && intval($filter['month']))){
    $dates=array(
      0 => $filter['year'].'-'.$filter['month'].'-01',
      1 => $filter['year'].'-'.$filter['month'].'-'.date('t',strtotime($filter['year'].'-'.$filter['month'].'-01')),
    );
  }

  $items=array();
  foreach($dates as $date){
    $items[]=strtotime($date);
  }
  $dates=$items;

  /*
  //Only year
  if(!isset($filter['month']) || empty($filter['month'])){
    $dates=array(
      0 => strtotime($filter['year'].'-01-01'),
      1 => strtotime($filter['year'].'-12-31'),
    );
  }
  //Only month
  if(!isset($filter['year']) || empty($filter['year'])){
    $dates=array(
      0 => strtotime(date('Y').'-'.$filter['month'].'-01'),
      1 => strtotime(date('Y').'-'.$filter['month'].'-31'),
    );
  }
  //Year && month
  if(isset($filter['year']) && isset($filter['month'])){
    $dates=array(
      0 => strtotime($filter['year'].'-'.$filter['month'].'-01'),
      1 => strtotime($filter['year'].'-'.$filter['month'].'-31'),
    );
  }
  */

  return $dates;
}