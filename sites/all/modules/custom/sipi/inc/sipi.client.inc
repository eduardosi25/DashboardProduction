<?php
function sipi_client(){
  return sipi_client_list();
}
function sipi_client_add(){
  return drupal_get_form('sipi_clients_form');
}
function sipi_client_view($client){
  return module_invoke('sipi', 'block_view', 'sipi_client_detail');
}
function sipi_client_report($client){
  module_load_include('inc','sipi','inc/sipi.report');
  $report=new sipiClientReport();
  $args=arg();
  $tid=isset($args[4]) && !empty($args[4]) ? $args[4] : 0;
  $report->getData($client,$tid);
  $report->renderHTML();
  die();
}
function sipi_client_report_pdf($client){
  module_load_include('inc','sipi','inc/sipi.report');
  $report=new sipiClientReport();
  $args=arg();
  $tid=isset($args[4]) && !empty($args[4]) ? $args[4] : 0;
  $report->getData($client,$tid);
  $report->renderPDF();
  die();
}

/**
 * Implements send email
 * @see mailsystem && swiftmailer - All setup include a tpl un theme switfmailer.tpl.php
 * @param $client
 * @return string
 */
function sipi_client_report_email($client){
  module_load_include('inc','sipi','inc/sipi.report');
  $report=new sipiClientReport();
  $args=arg();
  $tid=isset($args[4]) && !empty($args[4]) ? $args[4] : 0;
  $report->getData($client,$tid);
  $HTML=$report->getHTML('mail');

  //Basic settings
  $settings=array(
    'module'  => 'sipi',
    'delta'   => __FUNCTION__,
    'from'    => 'Webmaster Invent.mx <webmaster@invent.mx>',
    'to'      => 'luis@inventmx.com, axl75mx@gmail.com',
    'params'  => array(
      'text'    => array($HTML),
      'subject' => 'Reporte de cliente CODIGA - '.$client->name,
      'bcc'     => 'axl75mx@gmail.com',
    ),
  );

  // Send message.
  $result=drupal_mail($settings['module'], $settings['delta'], $settings['to'], language_default(), $settings['params'], $settings['from']);
  if($result['send']){
    drupal_set_message('Reporte de métricas enviado a: '.$settings['to'],'status');
  }
  return '<a href="javascript:window.close();" style="color: white;background-color: darkred;font-weight: 700;padding: 13px;border-radius: 5px;">Cerrar ventana</a>';
}

function sipi_client_report_xls($client){
  module_load_include('inc','sipi','inc/sipi.report');
  $report=new sipiClientReport();
  $args=arg();
  $tid=isset($args[4]) && !empty($args[4]) ? $args[4] : 0;
  $report->getData($client,$tid);
  $report->renderXLS();
  die();
}
function sipi_client_cancel($client){
  return drupal_get_form('sipi_client_cancel_account_form',$client);
}
function sipi_client_edit($client){
  return drupal_get_form('sipi_clients_form',$client);
}
/**
 * Form builder; confirm form for cancelling client account.
 */
function sipi_client_cancel_account_form($form, &$form_state, $client=NULL) {
  global $user;

  $admin = user_access('sipi admin clients');
  // If we aren't admin but already logged on, go to the dashboard
  if (!$admin) {
    drupal_goto('sipi');
  }else if(!isset($client->cid)){
    drupal_goto('sipi/client');
  }

  $form=array();
  $form['sipi_client'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Are you sure you want to cancel the account %name?', array('%name' => $client->name)),
    '#tree'  => TRUE,
  );
  $form['sipi_client']['client'] = array(
    '#type' => 'value',
    '#value' => $client
  );
  $form['sipi_client']['cancel'] = array(
    '#markup' => l(t('Cancel'), 'sipi/client/'.$client->cid.'/view', array('attributes' => array('style'=>'display:inline-block;float:left;padding:8px;'))),
  );
  $form['sipi_client']['submit'] = array(
    '#type'   => 'submit',
    '#value'  => t('Delete'),
  );
  $form['#redirect'] = 'sipi/client';
  return $form;
}

/**
 * Submit handler for the account cancellation confirm form.
 *
 * @see sipi_client_cancel_account_form()
 * @see sipi_client_cancel_account_form_submit()
 */
function sipi_client_cancel_account_form_submit($form, &$form_state) {
  global $user;
  $client = $form_state['values']['sipi_client']['client'];
  if (user_access('sipi admin clients')) {
    $transaction = db_transaction();
    try {
      db_delete('sipi_plans_clients')
        ->condition('cid', $client->cid, '=')
        ->execute();
      db_delete('sipi_clients')
        ->condition('cid', $client->cid, '=')
        ->execute();
      $form_state['redirect'] = 'sipi/client';
      $form_state['rebuild'] = TRUE;
      drupal_set_message($client->name.' - client account deleted!','error');
    } catch (Exception $e) {
      $transaction->rollback();
      watchdog_exception('SIPI Client Cancel Account', $e);
      throw $e;
    }
    $form_state['redirect'] = 'sipi/client';
    $form_state['rebuild'] = TRUE;
  }
}


/**
 * Implements hook_form().
 */
function sipi_clients_form($form, &$form_state, $client=NULL){
  $admin = user_access('sipi admin clients');
  // If we aren't admin but already logged on, go to the dashboard
  if (!$admin) {
    drupal_goto('sipi');
  }
  $form=array();
  $form['#tree'] = TRUE;

  $form['sipi_client'] = array(
    '#type'  => 'fieldset',
    '#title' => !isset($client) || empty($client) ? t('SIPI User :: Add') : t('SIPI User :: Edit'),
    '#tree'  => TRUE,
  );
  $form['sipi_client']['cid']  = array(
    '#type' => 'hidden',
    '#value' => isset($client->cid) && !empty($client->cid) ? intval($client->cid) : 0,
  );
  $form['sipi_client']['client'] = array(
    '#type'  => 'fieldset',
    '#title' => !isset($client) || empty($client) ? t('Add Client') : t('Edit Client'),
    '#tree'  => TRUE,
  );
  $form['sipi_client']['client']['name'] = array(
    '#title'         => t('Name'),
    '#type'          => 'textfield',
    '#size'          => 30,
    '#maxlength'     => 100,
    '#default_value' => isset($client->name) && !empty($client->name) ? $client->name : '',
    '#description'   => t('Name'),
    '#required'      => TRUE,
  );
  $form['sipi_client']['client']['mail'] = array(
    '#title'         => t('Email'),
    '#type'          => 'textfield',
    '#size'          => 60,
    '#maxlength'     => 150,
    '#default_value' => isset($client->mail) && !empty($client->mail) ? $client->mail : '',
    '#description'   => t('Email'),
    '#required'      => TRUE,
  );
  $form['sipi_client']['client']['company'] = array(
    '#title'         => t('Company'),
    '#type'          => 'textfield',
    '#size'          => 60,
    '#maxlength'     => 150,
    '#default_value' => isset($client->company) && !empty($client->company) ? $client->company : '',
    '#description'   => t('Company name'),
    '#required'      => TRUE,
  );
  $form['sipi_client']['client']['cellphone'] = array(
    '#title'         => t('Cell phone'),
    '#type'          => 'textfield',
    '#size'          => 20,
    '#maxlength'     => 20,
    '#default_value' => isset($client->cellphone) && !empty($client->cellphone) ? $client->cellphone : '',
    '#description'   => t('Cell phone'),
    '#required'      => TRUE,
  );
  $form['sipi_client']['client']['phone'] = array(
    '#title'         => t('Phone'),
    '#type'          => 'textfield',
    '#size'          => 30,
    '#maxlength'     => 60,
    '#default_value' => isset($client->phone) && !empty($client->phone) ? $client->phone : '',
    '#description'   => t('Phone'),
    '#required'      => TRUE,
  );
  $form['sipi_client']['client']['extention'] = array(
    '#title'         => t('Extention'),
    '#type'          => 'textfield',
    '#size'          => 10,
    '#maxlength'     => 10,
    '#default_value' => isset($client->extention) && !empty($client->extention) ? $client->extention : '',
    '#description'   => t('Phone Extention'),
  );
  $form['sipi_client']['client']['web'] = array(
    '#title'         => t('Web page'),
    '#type'          => 'textfield',
    '#size'          => 10,
    '#maxlength'     => 150,
    '#default_value' => isset($client->web) && !empty($client->web) ? $client->web : '',
    '#description'   => t('Web page'),
  );
  $form['sipi_client']['client']['logo'] = array(
    '#type' => 'managed_file',
    '#title' => t('Logo'),
    '#description' => t('Allowed extensions: png jpg jpeg'),
    '#default_value' => (isset($client->logo) ? $client->logo : ''),
    '#upload_validators' => array(
      'file_validate_extensions' => array('png jpg jpeg'),
      'file_validate_size' => array(1*1024*1024),
    ),
    '#upload_location' => 'public://sipi_clients/',
    '#process' => array('sipi_client_file_element_process'),
  );
  $form['sipi_client']['client']['description'] = array(
    '#title'         => t('Description'),
    '#type'          => 'textarea',
    '#cols'          => 10,
    '#rows'          => 5,
    '#default_value' => isset($client->description) && !empty($client->description) ? $client->description : '',
    '#description'   => t('Description'),
  );
  $form['sipi_client']['client']['facebook'] = array(
    '#title'         => t('Facebook'),
    '#type'          => 'textfield',
    '#size'          => 40,
    '#maxlength'     => 150,
    '#default_value' => isset($client->facebook) && !empty($client->facebook) ? $client->facebook : '',
    '#description'   => t('Facebook URL'),
  );
  $form['sipi_client']['client']['twitter'] = array(
    '#title'         => t('Twitter'),
    '#type'          => 'textfield',
    '#size'          => 40,
    '#maxlength'     => 150,
    '#default_value' => isset($client->twitter) && !empty($client->twitter) ? $client->twitter : '',
    '#description'   => t('Twitter URL'),
  );
  $form['sipi_client']['client']['googleplus'] = array(
    '#title'         => t('Google+'),
    '#type'          => 'textfield',
    '#size'          => 40,
    '#maxlength'     => 150,
    '#default_value' => isset($client->googleplus) && !empty($client->googleplus) ? $client->googleplus : '',
    '#description'   => t('Google+ URL'),
  );
  $form['sipi_client']['client']['youtube'] = array(
    '#title'         => t('Youtube'),
    '#type'          => 'textfield',
    '#size'          => 40,
    '#maxlength'     => 150,
    '#default_value' => isset($client->youtube) && !empty($client->youtube) ? $client->youtube : '',
    '#description'   => t('Youtube URL'),
  );
  $form['sipi_client']['client']['instagram'] = array(
    '#title'         => t('Instagram'),
    '#type'          => 'textfield',
    '#size'          => 40,
    '#maxlength'     => 150,
    '#default_value' => isset($client->instagram) && !empty($client->instagram) ? $client->instagram : '',
    '#description'   => t('Instagram URL'),
  );
  $form['sipi_client']['client']['linkedin'] = array(
    '#title'         => t('Linkedin'),
    '#type'          => 'textfield',
    '#size'          => 40,
    '#maxlength'     => 150,
    '#default_value' => isset($client->linkedin) && !empty($client->linkedin) ? $client->linkedin : '',
    '#description'   => t('Linkedin URL'),
  );
  $form['sipi_client']['client']['pinterest'] = array(
    '#title'         => t('Pinterest'),
    '#type'          => 'textfield',
    '#size'          => 40,
    '#maxlength'     => 150,
    '#default_value' => isset($client->pinterest) && !empty($client->pinterest) ? $client->pinterest : '',
    '#description'   => t('Pinterest URL'),
  );
  $form['sipi_client']['client']['vine'] = array(
    '#title'         => t('Vine'),
    '#type'          => 'textfield',
    '#size'          => 40,
    '#maxlength'     => 150,
    '#default_value' => isset($client->vine) && !empty($client->vine) ? $client->vine : '',
    '#description'   => t('Vine URL'),
  );

  $form['sipi_client']['invent'] = array(
    '#type'   => 'fieldset',
    '#title'  => t('Invent'),
    '#tree'   => TRUE,
    '#prefix' => '<div id="invent-fieldset-wrapper">',
    '#suffix' => '</div>',
  );

  if((isset($client->plans) && !empty($client->plans)) && empty($form_state['sipi_client']['invent']['items'])){
    $form_state['sipi_client']['invent']['items'] = count($client->plans);
  } else if(empty($form_state['sipi_client']['invent']['items'])){
    $form_state['sipi_client']['invent']['items'] = 1;
  }

  for ($i = 0; $i < $form_state['sipi_client']['invent']['items']; $i++) {
    $form['sipi_client']['invent']['data'][$i] = array(
      '#type'   => 'fieldset',
      '#title'  => t('User Data :: '.($i+1)),
      '#tree'   => TRUE,
      '#attributes' => array('class' => array('sipi-client-invent-fieldset'))
    );
    $form['sipi_client']['invent']['data'][$i]['mid']  = array(
      '#type' => 'hidden',
      '#value' => isset($client->plans[$i]->mid) && !empty($client->plans[$i]->mid) ? intval($client->plans[$i]->mid) : 0,
    );
    $form['sipi_client']['invent']['data'][$i]['site'] = array(
      '#title' => t('Site name'),
      '#type' => 'select',
      '#options' => get_sipi_sites(),
      '#default_value' => isset($client->plans[$i]->site) && !empty($client->plans[$i]->site) ? $client->plans[$i]->site : '',
      '#description' => t('Site name'),
      '#required' => TRUE,
    );
    $form['sipi_client']['invent']['data'][$i]['uid'] = array(
      '#title' => t('Manager'),
      '#type' => 'select',
      '#options' => get_sipi_client_manager(array('sipi_executive')),
      '#default_value' => isset($client->plans[$i]->uid) && !empty($client->plans[$i]->uid) ? intval($client->plans[$i]->uid) : '',
      '#description' => t('Manager'),
      '#required' => TRUE,
    );
    $form['sipi_client']['invent']['data'][$i]['pid'] = array(
      '#title' => t('Plan'),
      '#type' => 'select',
      '#options' => get_sipi_plans(),
      '#default_value' => isset($client->plans[$i]->pid) && !empty($client->plans[$i]->pid) ? intval($client->plans[$i]->pid) : '',
      '#description' => t('Plans'),
      '#required' => TRUE,
    );
    $date_format = 'd/m/Y';
    $date = date('Y-m-d H:i:s');
    $form['sipi_client']['invent']['data'][$i]['start_date'] = array(
      '#title' => t('Start date'),
      '#type' => 'date_popup',
      '#date_format' => $date_format,
      '#default_value' => isset($client->plans[$i]->start_date) && !empty($client->plans[$i]->start_date) ? date('Y-m-d',$client->plans[$i]->start_date) : $date,
      '#date_label_position' => 'none',
      '#date_timezone' => 'America/Mexico_City',
      '#date_year_range' => '-3:+3',
      '#required' => TRUE,
      '#attributes' => array('class' => array('left')),
    );
    $form['sipi_client']['invent']['data'][$i]['end_date'] = array(
      '#title' => t('End date'),
      '#type' => 'date_popup',
      '#date_format' => $date_format,
      '#default_value' => isset($client->plans[$i]->end_date) && !empty($client->plans[$i]->end_date) ? date('Y-m-d',$client->plans[$i]->end_date) : $date,
      '#date_label_position' => 'none',
      '#date_timezone' => 'America/Mexico_City',
      '#date_year_range' => '-3:+3',
      '#required' => TRUE,
      '#attributes' => array('class' => array('left')),
    );
    $form['sipi_client']['invent']['data'][$i]['status'] = array(
      '#title' => t('Status'),
      '#type' => 'select',
      '#options' => array(
        '0' => t('Disabled'),
        '1' => t('Enabled'),
        '2' => t('Suspended'),
      ),
      '#default_value' => isset($client->plans[$i]->status) && !empty($client->plans[$i]->status) ? intval($client->plans[$i]->status) : 0,
      '#description' => t('Status'),
    );
    if ($form_state['sipi_client']['invent']['items'] > 1) {
      $form['sipi_client']['invent']['data'][$i]['remove'] = array(
        '#type' => 'submit',
        '#value' => t('Remove'),
        '#submit' => array('sipi_client_remove_one'),
        '#ajax' => array(
          'callback' => 'sipi_client_add_more',
          'wrapper'  => 'invent-fieldset-wrapper',
        ),
      );
    }
  }
  $form['sipi_client']['invent']['add'] = array(
    '#title' => t('Add more'),
    '#type'  => 'submit',
    '#submit' => array('sipi_client_add_more_add_one'),
    '#value' => t('Add more'),
    '#ajax'  => array(
      'callback' => 'sipi_client_add_more',
      'wrapper'  => 'invent-fieldset-wrapper',
    ),
    '#prefix' => '<div id="invent-fieldset-wrapper-addmore">',
    '#suffix' => '</div>',
  );

  $form['cancel'] = array(
    '#markup' => l(t('Cancel'), 'codiga/user', array('attributes' => array('style'=>'display:inline-block;float:left;padding:8px;'))),
  );
  $form['submit'] = array(
    '#type'   => 'submit',
    '#value'  => t('Save'),
  );

  return $form;
}

function sipi_clients_form_validate($form, &$form_state){
  $cid = isset($form_state['values']['cid']) && !empty($form_state['values']['cid']) ? intval($form_state['values']['cid']) : 0;
  $client=$form_state['values']['sipi_client']['client'];
  $invent=$form_state['values']['sipi_client']['invent']['data'];
  if(isset($client['name']) && !empty($client['name'])){
    $form_state['values']['sipi_client']['client']['pass']=sipi_client_generate_name_pass($client['name']);
  }
}

function sipi_clients_form_submit($form, &$form_state){

  $cid = isset($form_state['values']['sipi_client']['cid']) && !empty($form_state['values']['sipi_client']['cid']) ? intval($form_state['values']['sipi_client']['cid']) : 0;
  $client=$form_state['values']['sipi_client']['client'];
  $invent=$form_state['values']['sipi_client']['invent']['data'];

  $timestamp = time();
  $fields = array();
  $fields['client'] = array(
    'cid'         => $cid,
    'name'        => isset($client['name']) && !empty($client['name']) ? $client['name'] : '',
    'mail'        => isset($client['mail']) && !empty($client['mail']) ? $client['mail'] : '',
    'pass'        => isset($client['pass']) && !empty($client['pass']) ? $client['pass'] : '',
    'company'     => isset($client['company']) && !empty($client['company']) ? $client['company'] : '',
    'cellphone'   => isset($client['cellphone']) && !empty($client['cellphone']) ? $client['cellphone'] : '',
    'phone'       => isset($client['phone']) && !empty($client['phone']) ? $client['phone'] : '',
    'extention'   => isset($client['extention']) && !empty($client['extention']) ? $client['extention'] : '',
    'web'         => isset($client['web']) && !empty($client['web']) ? $client['web'] : '',
    'logo'        => isset($client['logo']) && !empty($client['logo']) ? $client['logo'] : '',
    'description' => isset($client['description']) && !empty($client['description']) ? $client['description'] : '',
    'facebook'    => isset($client['facebook']) && !empty($client['facebook']) ? $client['facebook'] : '',
    'twitter'     => isset($client['twitter']) && !empty($client['twitter']) ? $client['twitter'] : '',
    'googleplus'  => isset($client['googleplus']) && !empty($client['googleplus']) ? $client['googleplus'] : '',
    'youtube'     => isset($client['youtube']) && !empty($client['youtube']) ? $client['youtube'] : '',
    'instagram'   => isset($client['instagram']) && !empty($client['instagram']) ? $client['instagram'] : '',
    'linkedin'    => isset($client['linkedin']) && !empty($client['linkedin']) ? $client['linkedin'] : '',
    'pinterest'   => isset($client['pinterest']) && !empty($client['pinterest']) ? $client['pinterest'] : '',
    'vine'        => isset($client['vine']) && !empty($client['vine']) ? $client['vine'] : '',
    'created'     => $timestamp,
    'changed'     => $timestamp,
    'access'      => $timestamp,
    'login'       => $timestamp,
  );

  //Save log file
  if(isset($client['logo']) && !empty($client['logo'])){
    $file = file_load($client['logo']);
    $file->status = FILE_STATUS_PERMANENT;
    file_usage_add($file, 'sipi', 'user', '1');
    file_save($file);
  }

  foreach ($invent as $plan) {
    $fields['invent'][] = array(
      'mid'        => isset($plan['mid']) && !empty($plan['mid']) ? intval($plan['mid']) : 0,
      'pid'        => isset($plan['pid']) && !empty($plan['pid']) ? intval($plan['pid']) : '',
      'cid'        => $cid,
      'uid'        => isset($plan['uid']) && !empty($plan['uid']) ? intval($plan['uid']) : 0,
      'status'     => isset($plan['status']) && !empty($plan['status']) ? $plan['status'] : 0,
      'site'       => isset($plan['site']) && !empty($plan['site']) ? $plan['site'] : '',
      'start_date' => isset($plan['start_date']) && !empty($plan['start_date']) ? _get_timestmap_from_date($plan['start_date']) : time(),
      'end_date'   => isset($plan['end_date']) && !empty($plan['end_date']) ? _get_timestmap_from_date($plan['end_date']) : time(),
    );
  }
  return sipi_clients_save($fields);
}

function sipi_clients_save($fields){
  if(isset($fields['client']['cid']) && !empty($fields['client']['cid'])){
    //Search
    $query=db_select('sipi_clients','c');
    $query->fields('c', array('cid','name'));
    $query->condition('c.cid',$fields['client']['cid'],'=');
    $result=$query->execute()->fetchAssoc();
    if($result){
      //Update
      sipi_clients_save_op('update',$fields);
      sipi_plans_clients_save_op('update',$fields,$fields['client']['cid']);
    }else{
      drupal_set_message('Error, the client '.$fields['client']['name'].' doesnt exists. Rectify please.','error');
      return false;
    }
  }else{
    //Insert
    $cid=sipi_clients_save_op('insert',$fields);
    $pids=sipi_plans_clients_save_op('insert',$fields,$cid);
    if($cid>0 && count($pids)>0){
      //Send email
      sipi_clients_save_send_email($cid);
    }
  }
}

/**
 *
 * @param array $field Fields array for insert or update values
 * @return boolean
 */
function sipi_clients_save_op($delta='insert',$fields){
  global $user;
  if(!isset($fields) && empty($fields)){
    return false;
  }
  switch($delta){
    case 'insert':
      $client=$fields['client'];
      array_shift($client);
      $query=db_insert('sipi_clients')->fields($client)->execute();
      drupal_set_message('User '.$fields['client']['name'].' inserted.','status');
      sipi_logging('Insert new user:['.$fields['client']['name'].'] by user:['.$user->name.']','info');
      return $query;
    break;
    case 'update':
      $client=$fields['client'];
      $cid=intval($client['cid']);
      array_shift($client);
      $query=db_update('sipi_clients');
      $query->fields($client);
      $query->condition('cid',$cid,'=');
      $query->execute();
      drupal_set_message('User '.$fields['client']['name'].' updated.','status');
      sipi_logging('Update user:['.$fields['client']['name'].'] by user:['.$user->name.']','info');
      return true;
    break;
  }
}

function sipi_plans_clients_save_op($delta='insert',$fields,$cid){
  global $user;
  if(!isset($fields) && empty($fields)){
    return false;
  }
  switch($delta){
    case 'insert':
      $ids=array();
      foreach($fields['invent'] as $plan){
        if($plan['site']>0 && $plan['uid']>0 && $plan['pid']>0) {
          $plan['cid']=$cid;
          $query=db_insert('sipi_plans_clients');
          $query->fields($plan);
          $query->execute();
          $ids[]=$query;
          drupal_set_message('New plan for user: '.$fields['client']['name'],'status');
          sipi_logging('Insert new plan plan for: '.$fields['client']['name'].' by user:['.$user->name.']','info');
        }
      }
      return $ids;
    break;
    case 'update':
      //First delete if exist on DB but not in the form
      sipi_plans_clients_delete_op($cid,$fields['invent']);

      //Search every plan an update
      if(count($fields['invent'])>0){
        $ids=array();
        //Parse plans array from form
        foreach($fields['invent'] as $plan){
          if($plan['site']>0 && $plan['uid']>0 && $plan['pid']>0) {
            $field=array(
              'pid'        => $plan['pid'],
              'uid'        => $plan['uid'],
              'cid'        => $cid,
              'status'     => $plan['status'],
              'site'       => $plan['site'],
              'start_date' => $plan['start_date'],
              'end_date'   => $plan['end_date'],
            );

            if(intval($plan['mid'])>0){
              //Update plan if mid exists
              $query=db_update('sipi_plans_clients');
              $query->fields($field);
              $query->condition('cid',$cid,'=');
              $query->condition('mid',$plan['mid'],'=');
              $query->execute();
              //drupal_set_message('Update user-plan for '.$fields['client']['name'].'.','status');
              sipi_logging('Update user-plan of '.$fields['client']['name'].' by user:['.$user->name.']','info');
            }else{
              //Insert plan
              $query=db_insert('sipi_plans_clients');
              $query->fields($field);
              $query->execute();
              $ids[] = $query;
              drupal_set_message('New user-plan for '.$fields['client']['name'].'.','status');
              sipi_logging('Insert new user-plan for '.$fields['client']['name'].' by user:['.$user->name.']','info');
            }
          }
        }
        return $ids;
      }else{
        return false;
      }
      /*
      $fields['cid']=$result;
      $query=db_update('sipi_clients')->fields($fields)->execute();
      $query->condition('cid',$fields['cid'],'=');
      drupal_set_message('Plans updated.','status');
      sipi_logging('Plans updated by user:['.$user->name.']','info');
      return true;
      */
    break;
  }
}


function sipi_plans_clients_delete_op($cid,$plans){
  global $user;
  if(!isset($plans) || empty($plans))
    return null;

  $mids=array();
  foreach($plans as $plan){
    if($plan['mid']>0){
      $mids[]=$plan['mid'];
    }
  }
  if(count($mids)>0){
    $query=db_select('sipi_plans_clients','pc');
    $query->fields('pc',array('mid'));
    $query->condition('pc.cid',$cid,'=');
    $query->condition('pc.mid',$mids,'NOT IN');
    $result=$query->execute();
    if($result){
      //Delete every record founded
      foreach($result as $row){
        $query_delete=db_delete('sipi_plans_clients');
        $query_delete->condition('mid', $row->mid);
        $result_delete=$query_delete->execute();
        if($result_delete){
          drupal_set_message('Deleted user-plan.','status');
          sipi_logging('Deleted user-plan by user:['.$user->name.']','info');
        }
      }
    }else{
      return null;
    }
  }
}

function get_sipi_client_manager($roles=array('sipi_executive')){
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
function get_tids_sites($mode='array'){
  global $sipi_variables;
  $items=array();
  foreach($sipi_variables['sites'] as $key => $value){
    if(isset($value) && !empty($value)){
      $items[]=intval($value);
    }
  }
  if($mode=='string'){
    return implode(',',$items);
  }
  if($mode=='object'){
    return (object)$items;
  }
  return $items;
}

function get_sipi_sites(){
  $sites=get_tids_sites('string');

  $query="select td.tid, td.name
          from taxonomy_term_data td
          where td.vid=1 and td.tid in ($sites)
          order by td.weight ASC";
  $result=db_query($query);
  /**
  $query=db_select('taxonomy_term_data','td');
  $query->fields('td', array('tid','name'));
  $query->condition('td.vid',1,'=');
  $query->orderBy('td.vid','ASC');
  $result=$query->execute();
  */
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

function sipi_client_list(){
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
  /**
   * select
  c.cid, c.name as client, u.name as manager, td.name as site, p.name as plan,
  pc.status
  from sipi_clients c
  inner join sipi_plans_clients pc on pc.cid=c.cid
  inner join sipi_plans p on p.pid=pc.pid
  inner join users u on u.uid=pc.uid
  inner join taxonomy_term_data td on td.tid=pc.site;
   */
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

  $query=$query->extend('TableSort')->orderByHeader($header);
  $result=$query->execute();
  $rows=array();
  foreach ($result as $row) {

    $contents_published=sipi_client_get_nodes_published($row->cid, $row->idsite);
    $rows[] = array(
      $row->cid,
      l($row->name, "codiga/client/$row->cid/view/".$row->idsite,array('query'=>array('destination'=>'codiga/client'))),
      $row->manager,
      $row->site,
      $row->plan,
      ($row->status==0 ? t('Disabled') : ($row->status==1 ? t('Enabled') : 'N/D')),
      (isset($contents_published) && !empty($contents_published) ? (count($contents_published)>0 ? count($contents_published) : 0) : 0),
      (isset($contents_published) && !empty($contents_published) ? $row->contents_limit-count($contents_published) : 0),
      date('Y-m-d',$row->start_date),
      date('Y-m-d',$row->end_date),
      l(t('Details'),"codiga/client/$row->cid/view/".$row->idsite  ,array('query'=>array('destination'=>'codiga/client'))) .' <br> '.
      l(t('Edit')   ,"codiga/client/$row->cid/edit"  ,array('query'=>array('destination'=>'codiga/client'))),
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
  );
  return $build;

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

function sipi_client_get_nodes_published($cid, $tid){

  /**
   * SELECT count(c.cid) as nodes_published, iu.uid, c.cid, c.name, c.company, c.mail, iu.uid, iu.sitename, iu.pageviews
  FROM sipi_clients_invent_contents ic
  INNER JOIN sipi_clients_invent_users iu on iu.uid=ic.uid
  INNER JOIN sipi_clients c on c.cid=ic.cid
  WHERE c.cid=2 AND iu.uid=112113
  GROUP BY iu.cid, iu.uid, iu.sitename;
   */
  $query = db_select('sipi_clients_invent_contents', 'ic');
  $query->join('sipi_clients_invent_users','iu','iu.uid=ic.uid');
  $query->join('sipi_clients','c','c.cid=ic.cid');
  $query->fields('c',array('cid','name','mail','company'));
  $query->addField('iu','uid','uid');
  $query->addField('iu','sitename','sitename');
  $query->addField('iu','pageviews','pageviews');
  $query->condition('c.cid',$cid,'=');
  $query->condition('iu.cid',$cid,'=');
  $query->condition('ic.tid',$tid,'=');
  $result=$query->execute();

  #print $query;
  #die();

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

function sipi_client_delete_confirm($form, &$form_state, $plans=NULL) {
  $form['#plans'] = $plans;
  // Always provide entity id in the same form key as in the entity edit form.
  $form['pid'] = array('#type' => 'value', '#value' => $plans['pid']);
  return confirm_form($form,
    t('Are you sure you want to delete %title?', array('%title' => $plans['name'])),
    'codiga/plans/'.$plans['pid'],
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

function sipi_client_delete_confirm_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {
    db_delete('sipi_clients')
      ->condition('pid', $form_state['values']['pid'])
      ->execute();
  }
  $form_state['redirect'] = 'codiga/plans';
  $form_state['rebuild'] = TRUE;
}

function sipi_client_list_items(){
  $query=db_select('sipi_clients', 'c');
  $query->fields('c', array('cid','name','mail','pass','cellphone','phone','web','logo','description','created','changed','access','login'));
  $result=$query->execute();
  if($result){
    $items=array();
    foreach($result as $row){
      $items[]=$row;
    }
    return $items;
  }
  return null;
}

function sipi_client_list_plans_items($cid=0){
  if(!isset($cid) || empty($cid))
    return false;
  $query = db_select('sipi_clients', 'c');
  $query->join('sipi_plans_clients','pc','pc.cid=c.cid');
  $query->join('taxonomy_term_data','td','td.tid=pc.site');
  $query->join('field_data_field_api_container','ac','ac.entity_id=td.tid');
  $query->fields('c',array('cid','name','mail','pass'));
  $query->addField('pc','site','idsite');
  $query->addField('td','name','site');
  $query->addField('ac','field_api_container_value','apirepo');
  $query->condition('c.cid',$cid,'=');
  $result=$query->execute();
  if($result->rowCount()>0){
    $plans=array();
    foreach ($result as $row) {
      $plans[]=$row;
    }
    return $plans;
  }
  return false;
}

/**
 * Managed multiple forms. Add or remove dinamycally with Ajax
 */
function sipi_client_add_more($form, $form_state){
  return $form['sipi_client']['invent'];
}
function sipi_client_add_more_add_one($form, &$form_state) {
  $form_state['sipi_client']['invent']['items']++;
  $form_state['rebuild'] = TRUE;
}
function sipi_client_remove_one($form, &$form_state) {
  if ($form_state['sipi_client']['invent']['items'] > 1) {
    $form_state['sipi_client']['invent']['items']--;
  }
  $form_state['rebuild'] = TRUE;
}
/**
 * Managed files upload for Logo
 */
/**
 * Implements hook_file_element_process().
 */
function sipi_client_file_element_process($element, &$form_state, $form) {
  $element = file_managed_file_process($element, $form_state, $form);
  if ($element['#file']) {
    $element["logo_preview"] = array(
      '#type' => 'markup',
      '#markup' => '<p><img src="'.get_image_style( $element['#file']->uri, "thumbnail" ).'" style="margin-right:20px;"/></p>',
      '#weight' => -15,
    );
    $element['remove_button'] = array(
      '#name' => 'logo_remove_button',
      '#type' => 'submit',
      '#value' => t('Remove'),
      '#validate' => array(),
      '#submit' => array('ajax_image_update_callback'),
      '#limit_validation_errors' => array($element['#parents']),
      '#ajax' => array(
        'callback' => 'ajax_image_update_callback',
        'wrapper' => $element['upload_button']['#ajax']['wrapper'],
      ),
      '#weight' => -5,
    );
  }
  return $element;
}
/**
 * Implements ajax_image_update_callback().
 */
function ajax_image_update_callback($form, &$form_state){
  if (!empty($form['sipi_client']['client']["logo"]["#value"])) {
    $form['sipi_client']['client']["logo"]["#value"]=null;
    $form['sipi_client']['client']["logo"]['logo_preview']=null;
    $form['sipi_client']['client']["logo"]["filename"]=null;
  }
  return $form['sipi_client']['client']["logo"];
}


/**
 * Implements get_image_style()
 */
function get_image_style( $image_url = null, $image_style = null, $alternative = null, $title = null, $attributes = array() ) {
  if ( !$image_url || !$image_style ) {
    return null;
  }
  return image_style_url( $image_style, $image_url );
}
/**
 * Implements helpers for pass generator from client name
 */
function sipi_client_generate_name_pass($clientName){
  if(!isset($clientName) || empty($clientName)){
    return false;
  }
  //First convert everything in lowers
  $clientName=sipi_client_convert_to_lowers($clientName);
  //Convert vocals to numbers
  $clientName=sipi_client_convert_to_numbers($clientName);
  //Transliterate
  $clientName=sipi_client_transliteration($clientName);

  //Generate random number
  $randomNumber=rand(0,(intval(date('Y'))*1024));
  return '$'.ucfirst($clientName).'@'.sipi_client_convert_to_letters($randomNumber).'$';
}
function sipi_client_generate_random_pass(){
  $alphabet="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789*-+#$%&.,:;_";
  $pass = array();
  $alphaLength = strlen($alphabet) - 1;
  for($i=0;$i<16;$i++){
    $char=rand(0,$alphaLength);
    $pass[]=$alphabet[$char];
  }
  return implode($pass);
}
function sipi_client_convert_to_lowers($string){
  $search  = array('á', 'é', 'í', 'ó', 'ú', 'Á', 'É', 'Í', 'Ó', 'Ú', 'ñ' ,'Ñ', '');
  $replace = array('a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U', 'ni' ,'NI', '-');
  $string  = str_replace($search, $replace, $string);
  return strtolower($string);
}
function sipi_client_convert_to_numbers($string){
  $search  = array('a', 'e', 'i', 'o', 'u');
  $replace = array('4', '3', '1', '0', 'y');
  return str_replace($search, $replace, $string);
}
function sipi_client_convert_to_letters($string){
  $search  = array('0', '1', '2', '3', '4', '5', '6', '7', '8', '9');
  $replace = array('o', 'i', 'z', 'e', 'a', 's', 'g', 't', 'h', 'g');
  return str_replace($search, $replace, $string);
}
function sipi_client_transliteration($string){
  $search  = array('.', ',', ' ');
  $replace = array('-', '-', '-');
  return $string;
}

/**
 * Implements generic helpers
 */

function _get_timestmap_from_date($date){
  if(!isset($date) || empty($date))
    $date=date('Y-m-d');

  $date=explode('-',$date);
  return mktime(0,0,0,$date['1'],$date['2'],$date['0']);
}

/**
#sipi_clients_form_submit
#values
array(6) {
["sipi_client"]=>
array(3) {
["cid"]=>
int(0)
["client"]=>
array(19) {
["name"]=>
string(4) "Luis Contreras"
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
string(15) "sipi_clients_form"
["op"]=>
string(4) "Save"
 */

function sipi_client_detail($client=null){
  if(!isset($client) || empty($client))
    return false;

  $header = array(
    array(
      'data' => t('Cliente'),
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

  $query = db_select('sipi_clients', 'c')->extend('PagerDefault');
  $query->join('sipi_plans_clients','pc','pc.cid=c.cid');
  $query->join('sipi_plans','p','p.pid=pc.pid');
  $query->join('users','u','u.uid=pc.uid');
  $query->join('taxonomy_term_data','td','td.tid=pc.site');
  $query->limit(20);
  $query->fields('c', array('cid','name'));
  $query->addField('pc', 'status','status');
  $query->addField('pc', 'start_date','start_date');
  $query->addField('pc', 'end_date','end_date');
  $query->addField('p', 'name','plan');
  $query->addField('u', 'name','manager');
  $query->addField('td', 'name', 'site');
  $query->addField('td', 'tid', 'idsite');
  $query->condition('pc.cid',$client,'=');

  if(isset($idsite) && !empty($idsite)){
    $query->condition('td.tid',$idsite,'=');
  }

  $query=$query->extend('TableSort')->orderByHeader($header);
  $result=$query->execute();
  $rows=array();
  foreach ($result as $row) {
    $rows[] = array(
      $row->cid,
      l($row->name, "codiga/client/$row->cid/view",array('query'=>array('destination'=>'codiga/client'))),
      $row->manager,
      $row->site,
      $row->plan,
      ($row->status==0 ? t('Disabled') : ($row->status==1 ? t('Enabled') : 'N/D')),
      'contents published',
      'remain contents',
      date('Y-m-d',$row->start_date),
      date('Y-m-d',$row->end_date),
      l(t('Details'),"codiga/client/$row->cid/view"  ,array('query'=>array('destination'=>'codiga/client'))) .' <br> '.
      l(t('Edit')   ,"codiga/client/$row->cid/edit"  ,array('query'=>array('destination'=>'codiga/client'))),
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
  );
  return $build;

}

function sipi_client_contents_list_header(){
  return array(
    array(
      'data' => t('Contenidos'),
      'field' => 'title',
    ),
    array(
      'data' => t('Estatus'),
      'field' => 'status',
    ),
    array(
      'data' => t('Fecha de publicación'),
      'field' => 'created',
    ),
    array(
      'data' => t('Visitas'),
      'field' => 'sessions'
    ),
    array(
      'data' => t('Páginas vistas'),
      'field' => 'pageviews'
    ),
    array(
      'data' => t('Páginas únicas'),
      'field' => 'uniquePageviews'
    ),
    array(
      'data' => t('Tiempo promedio'),
      'field' => 'avgTimeOnPage'
    ),
    array(
      'data' => t('Rebote'),
      'field' => 'bounceRate'
    ),
    array(
      'data' => t('FB Shares'),
      'field' => 'fbshares'
    ),
    array(
      'data' => t('Tweets'),
      'field' => 'tweets'
    ),
    array(
      'data' => t('Google+'),
      'field' => 'gpshares'
    ),
  );
}
function sipi_client_contents_list_query($cid,$idsite,$limit=20){
  if(!isset($cid))
    return null;

  $query = db_select('sipi_clients_invent_contents', 'iu')->extend('PagerDefault');
  $query->join('sipi_clients','c','c.cid=iu.cid');
  $query->limit($limit);
  $query->fields('iu', array('title','path','status','created','sessions', 'pageviews', 'uniquePageviews', 'avgTimeOnPage', 'bounceRate', 'fbshares','tweets','gpshares'));
  $query->addField('c','name','client');
  $query->condition('iu.cid',$cid,'=');

  if(isset($idsite) && !empty($idsite)){
    $query->condition('iu.tid',$idsite,'=');
  }

  return $query;
}

function sipi_client_contents_list_metrics(){
  return array(
    'sessions'   => 0,
    'visits'     => 0,
    'uniques'    => 0,
    'avgtime'    => 0,
    'bouncerate' => 0,
    'fbshares'   => 0,
    'tweets'     => 0,
    'googleplus' => 0,
  );
}

function sipi_client_contents_list($client=null){
  if(!isset($client) || empty($client))
    return false;

  $args=arg();
  $idsite=isset($args[4]) && !empty($args[4]) ? $args[4] : null;

  $header  = sipi_client_contents_list_header();
  $metrics = sipi_client_contents_list_metrics();
  $query   = sipi_client_contents_list_query($client,$idsite);

  $query=$query->extend('TableSort')->orderByHeader($header);
  $result=$query->execute();
  $rows=array();
  $numItems=0;
  foreach ($result as $row) {
    //Recalculate metrics.
    $metrics['sessions']+=$row->sessions;
    $metrics['visits']+=$row->pageviews;
    $metrics['uniques']+=$row->uniquePageviews;
    $metrics['avgtime']+=$row->avgTimeOnPage;
    $metrics['bouncerate']+=$row->bounceRate;
    $metrics['fbshares']+=$row->fbshares;
    $metrics['tweets']+=$row->tweets;
    $metrics['googleplus']+=$row->gpshares;

    $rows[] = array(
      l($row->title, $row->path, array('attributes'=>array('target'=>'_blank'))),
      ($row->status==0 ? t('Unpublished') : ($row->status==1 ? t('Published') : 'N/D')),
      ($row->created ? date('Y-m-d',$row->created) : 'N/D'),
      ($row->sessions>0 ? $row->sessions : '-'),
      ($row->pageviews>0 ? $row->pageviews : '-'),
      ($row->uniquePageviews>0 ? $row->uniquePageviews : '-'),
      ($row->avgTimeOnPage>0 ? conversorSegundosHoras($row->avgTimeOnPage) : '-'),
      ($row->bounceRate>0 ? round($row->bounceRate,2) : '-'),
      ($row->fbshares>0 ? $row->fbshares : '-'),
      ($row->tweets>0 ? $row->tweets : '-'),
      ($row->gpshares>0 ? $row->gpshares : '-'),
    );
    $numItems++;
  }

  if (count($rows)>1){
    #Sumas
    $rows[] = array(
      array(
        'data' => '<strong>Totales</strong>',
        'colspan' => 3,
      ),
      $metrics['sessions'] ? $metrics['sessions'] : '-',
      $metrics['visits'] ? $metrics['visits'] : '-',
      $metrics['uniques'] ? $metrics['uniques'] : '-',
      conversorSegundosHoras($metrics['avgtime']/$numItems),
      $metrics['bouncerate'] ? $metrics['bouncerate']=round($metrics['bouncerate']/$numItems,2) : '-',
      $metrics['fbshares'] ? $metrics['fbshares'] : '-',
      $metrics['tweets'] ? $metrics['tweets'] : '-',
      ($metrics['googleplus'] ? $metrics['googleplus'] : '-')
    );
  }


  if (count($rows) && ($pager = theme('pager'))) {
    $rows[] = array(
      array(
        'data' => $pager,
        'colspan' => 9,
      ),
    );
  }
  $build['sipi_client_contents_list'] = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
    '#empty' => 'No se encontraron contenidos para mostrar',
    '#caption' => 'Contenidos publicados',
  );
  return $build;
}

function sipi_client_contents_list_header_report(){
  return array(
    array(
      'data' => t('Título'),
    ),
    array(
      'data' => t('Fecha de publicación'),
    ),
    array(
      'data' => t('Tiempo promedio de estancia'),
    ),
    array(
      'data' => t('Visitas'),
    ),
    array(
      'data' => t('Páginas vistas'),
    ),
    array(
      'data' => t('Rebote'),
    ),
    array(
      'data' => t('Compartido en Twitter'),
    ),
    array(
      'data' => t('Compartido en Facebook'),
    ),
  );
}

function sipi_client_contents_list_report($client=null,$idsite=null){
  if(!isset($client) || empty($client))
    return false;

  $args=arg();

  $header  = sipi_client_contents_list_header_report();
  $metrics = sipi_client_contents_list_metrics();
  $query   = sipi_client_contents_list_query($client,$idsite,100);

  $query=$query->extend('TableSort')->orderByHeader($header);
  $result=$query->execute();
  $rows=array();
  $numItems=0;
  $pageBreak=1;
  foreach ($result as $row) {
    //Recalculate metrics.
    $metrics['sessions']+=$row->sessions;
    $metrics['visits']+=$row->pageviews;
    $metrics['uniques']+=$row->uniquePageviews;
    $metrics['avgtime']+=$row->avgTimeOnPage;
    $metrics['bouncerate']+=$row->bounceRate;
    $metrics['fbshares']+=$row->fbshares;
    $metrics['tweets']+=$row->tweets;
    $classPageBreak='';
    if($pageBreak==11){
      $pageBreak=1;
      $classPageBreak='pagebreak';
    }
    $pageBreak++;

    $rows[] = array(
      'data' => array(
        array('data' => l($row->title, $row->path, array('attributes'=>array('target'=>'_blank'))), 'class' => 'link'),
        ($row->created ? date('Y-m-d',$row->created) : 'N/D'),
        ($row->avgTimeOnPage>0 ? conversorSegundosHoras($row->avgTimeOnPage) : '-'),
        ($row->sessions>0 ? $row->sessions : '-'),
        ($row->pageviews>0 ? $row->pageviews : '-'),
        ($row->bounceRate>0 ? round($row->bounceRate,2)  : '-'),
        ($row->tweets>0 ? $row->tweets : '-'),
        ($row->fbshares>0 ? $row->fbshares : '-'),
      ),
      'class' => array($classPageBreak),
    );
    $numItems++;
  }

  if (count($rows) && ($pager = theme('pager'))) {
    $rows[] = array(
      array(
        'data' => $pager,
        'colspan' => 7,
      ),
    );
  }
  $build['sipi_client_contents_list'] = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
    '#empty' => 'No se encontraron contenidos para mostrar',
    '#caption' => '<h4>REPORTE</h4>',
  );
  return $build;
}


/**
 * Send email
 */
function sipi_clients_save_send_email($cid) {
  $client=sipi_client_load($cid);
  //Basic settings
  $settings=array(
    'module'  => 'sipi',
    'delta'   => __FUNCTION__,
    'from'    => 'Webmaster Codiga <webmaster@inventmx.com>',
    'to'      => 'pablo.escobedo@inventmx.com,belem@inventmx.com',
    'params'  => array(
      'text'    => array(),
      'subject' => 'Registro de cliente CODIGA - '.$client->name,
      'headers' => array(
        'From'    => 'Webmaster Codiga <webmaster@inventmx.com>',
        'Reply-To'=> 'webmaster@inventmx.com>',
        'Cc'      => 'belem@inventmx.com',
        'Bcc'     => 'webmaster@inventmx.com',
      ),
    ),
  );

  //Attachment
  $file=file_load($client->logo);
  if($file){
    $settings['params']['files'][] = $file;
  }

  //Sites information
  $sites=array();
  foreach($client->plans as $plan){
    $term=taxonomy_term_load($plan->site);
    $sites[]=$term->name;
  }
  unset($term);
  $sites=implode(' | ', $sites);

  //Data client
  $dataClient=array();
  $dataClientHTML='';
  foreach($client as $key => $value){
    if(isset($value) && !empty($value)){
      if(!in_array($key,array('cid','logo','created','changed','access','login','plans'))){
        $dataClientHTML=$dataClientHTML.'<tr><td><strong>'.ucfirst(sipi_fields_translate($key)).'</strong>:</td><td><em>'.$value.'</em></td></tr>';
      }
    }
  }

  //Message email
  $settings['params']['text']=array(
    '<p>Datos del registro</p>',
    '<h3>'.$client->name.'</h3>',
    '<img src="'.file_create_url($file->uri).'" />',
    '<p>Sitios: '.$sites.'</p>',
    '<p>Datos para registro (<strong>Deben ser iguales en todos los sitios</strong>)</p>',
    '<p><table>'.$dataClientHTML.'</table></p>',
  );

  // Send message.
  $result=drupal_mail($settings['module'], $settings['delta'], $settings['to'], language_default(), $settings['params'], $settings['from']);
  if($result['send']){
    drupal_set_message('Correo electrónico de registro de cliente enviado a: '.$settings['to'],'status');
  }
  return $result['send'];
}


function conversorSegundosHoras($tiempo_en_segundos) {
  if ($tiempo_en_segundos == 0)
    return '0s';
  $tiempo_en_segundos = intval($tiempo_en_segundos);
  $horas = floor($tiempo_en_segundos / 3600);
  $minutos = floor(($tiempo_en_segundos - ($horas * 3600)) / 60);
  $segundos = $tiempo_en_segundos - ($horas * 3600) - ($minutos * 60);

  $hora_texto = "";
  if ($horas > 0 ) {
    $hora_texto .= $horas . "h ";
    #$hora_texto .= $horas . ":";
  }

  if ($minutos > 0 ) {
    $hora_texto .= $minutos . "m ";
    #$hora_texto .= $minutos . ":";
  }

  if ($segundos > 0 ) {
    $hora_texto .= $segundos . "s";
    #$hora_texto .= $segundos . "";
  }
  /*if ($tiempo_en_segundos <= 60) {
      $hora_texto .= "s";
  }*/

  return $hora_texto;
}
