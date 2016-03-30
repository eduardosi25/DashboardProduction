<?php
function sipi_plans(){
  return sipi_plans_list();
}
function sipi_plans_add(){
  return drupal_get_form('sipi_plans_form');
}

function sipi_plans_edit($plan){
  return drupal_get_form('sipi_plans_form',$plan);
}

function sipi_plans_delete($plan){
  return drupal_get_form('sipi_plans_delete_confirm',$plan);
}

function sipi_plans_form($form, &$form_state, $plans=NULL){
  $admin = user_access('sipi admin plans');
  // If we aren't admin but already logged on, go to the dashboard
  if (!$admin) {
    drupal_goto('sipi');
  }
  $form=array();
  $form['sipi_plans'] = array(
    '#type'  => 'fieldset',
    '#title' => !isset($plans) || empty($plans) ? t('Add a plan') : t('Edit a plan'),
  );
  $form['sipi_plans']['pid']  = array(
    '#type' => 'hidden',
    '#value' => isset($plans['pid']) && !empty($plans['pid']) ? $plans['pid'] : 0,
  );
  $form['sipi_plans']['name'] = array(
    '#title'         => t('Name'),
    '#type'          => 'textfield',
    '#size'          => 30,
    '#maxlength'     => 60,
    '#default_value' => isset($plans['name']) && !empty($plans['name']) ? $plans['name'] : '',
    '#description'   => t('Plan name'),
    '#required'      => TRUE,
  );
  $form['sipi_plans']['contents'] = array(
    '#title'         => t('Contents number'),
    '#type'          => 'textfield',
    '#size'          => 10,
    '#maxlength'     => 4,
    '#default_value' => isset($plans['contents']) && !empty($plans['contents']) ? $plans['contents'] : 0,
    '#description'   => t('Contents number'),
    '#required'      => TRUE,
  );
  $form['sipi_plans']['posts'] = array(
    '#title'         => t('Social posts'),
    '#type'          => 'textfield',
    '#size'          => 10,
    '#maxlength'     => 4,
    '#default_value' => isset($plans['posts']) && !empty($plans['posts']) ? $plans['posts'] : 0,
    '#description'   => t('Social posts'),
  );
  $form['sipi_plans']['duration'] = array(
    '#title'         => t('Duration'),
    '#type'          => 'textfield',
    '#size'          => 5,
    '#maxlength'     => 3,
    '#default_value' => isset($plans['duration']) && !empty($plans['duration']) ? $plans['duration'] : 0,
    '#description'   => t('Duration in months for this plan (In months)'),
    '#required'      => TRUE,
  );
  $form['sipi_plans']['price'] = array(
    '#title'         => t('Price'),
    '#type'          => 'textfield',
    '#size'          => 10,
    '#maxlength'     => 10,
    '#default_value' => isset($plans['price']) && !empty($plans['price']) ? $plans['price'] : 0,
    '#description'   => t('Price or investment amount (Pesos MXN)'),
    '#required'      => TRUE,
  );
  $form['sipi_plans']['cancel'] = array(
    '#markup' => l(t('Cancel'), 'sipi/plans', array('attributes' => array('style'=>'display:inline-block;float:left;padding:8px;'))),
  );
  $form['sipi_plans']['submit'] = array(
    '#type'   => 'submit',
    '#value'  => t('Save'),
  );

  return $form;
}

function sipi_plans_form_validate($form, &$form_state){
  //Cancel
  if($form_state['values']['op']==='Cancel'){
    $errors=form_get_errors();
    if($errors) {
      sipi_plans_form_unset_error('name');
    }
    drupal_set_message('Canceled Add Plan','warning');
    drupal_goto('sipi/plans');
  } else {
    if( !isset($form_state['values']['name']) || !isset($form_state['values']['contents']) || !isset($form_state['values']['duration']) || !isset($form_state['values']['price']) ){
      form_set_error('cancel','All fields are required');
    }
    if( !isset($form_state['values']['name']) || empty($form_state['values']['name']) ){
      form_set_error('name','Name is required');
    }
    if( !isset($form_state['values']['contents']) || empty($form_state['values']['contents']) ){
      form_set_error('contents','Contents is required');
    }
    if( !isset($form_state['values']['duration']) || empty($form_state['values']['duration']) ){
      form_set_error('duration','Duration is required');
    }
    if( !isset($form_state['values']['price']) || empty($form_state['values']['price']) ){
      form_set_error('price','Price is required');
    }
  }
}
function sipi_plans_form_submit($form, &$form_state) {
  //Registrar datos.
  sipi_plans_save($form_state['values']);
}
function sipi_plans_form_unset_error($name) {
  $errors = &drupal_static('form_set_error', array());
  $removed_messages = array();
  if (isset($errors[$name])) {
    $removed_messages[] = $errors[$name];
    unset($errors[$name]);
  }
  $_SESSION['messages']['error'] = array_diff($_SESSION['messages']['error'], $removed_messages);
}

function sipi_plans_save($values){
  $pid=isset($values['pid']) && !empty($values['pid']) ? $values['pid'] : 0;
  $data=array(
    'name'     => $values['name'],
    'contents' => $values['contents'],
    'posts'    => $values['posts'],
    'duration' => $values['duration'],
    'price'    => $values['price'],
  );

  //Search
  $query=db_select('sipi_plans','sp');
  $query->fields('sp', array('pid','name','contents','posts','duration','price'));
  $query->condition('sp.pid',$pid,'=');
  $result=$query->execute()->fetchAssoc();
  if($result){
    sipi_plans_save_op('update',$data,$result);
  }else{
    sipi_plans_save_op('insert',$data,$result);
  }
}

/**
 *
 * @param array $field Fields array for insert or update values
 * @return boolean
 */
function sipi_plans_save_op($delta='insert',$fields,$result){
  global $user;
  switch($delta){
    case 'insert':
      $query=db_insert('sipi_plans');
      drupal_set_message('Plan inserted.','status');
      sipi_logging('Insert new plan:['.$fields['name'].'] by user:['.$user->name.']','info');
      break;
    case 'update':
      $fields['pid']=$result['pid'];
      $query=db_update('sipi_plans');
      $query->condition('pid',$result['pid'],'=');
      drupal_set_message('Plan updated.','status');
      sipi_logging('Update plan:['.$fields['name'].'] by user:['.$user->name.']','info');
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

function sipi_plans_list(){
  $header = array(
    array(
      'data' => t('PID'),
      'field' => 'p.pid',
    ),
    array(
      'data' => t('Name'),
      'field' => 'p.name',
    ),
    array(
      'data' => t('Contents'),
    ),
    array(
      'data' => t('Social Posts'),
    ),
    array(
      'data' => t('Duration'),
    ),
    array(
      'data' => t('Price'),
    ),
    array(
      'data' => t('Actions'),
    ),
  );

  // Default ordering
  if (!isset($_GET['order']) && !isset($_GET['sort'])) {
    $_GET['order'] = t('PID');
    $_GET['sort'] = 'ASC';
  }

  $query = db_select('sipi_plans', 'p')->extend('PagerDefault');
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
  $build['sipi_plans_list'] = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
    '#empty' => t('There are no plans.'),
  );
  return $build;

}

function sipi_plans_delete_confirm($form, &$form_state, $plans=NULL) {
  $form['#plans'] = $plans;
  // Always provide entity id in the same form key as in the entity edit form.
  $form['pid'] = array('#type' => 'value', '#value' => $plans['pid']);
  return confirm_form($form,
    t('Are you sure you want to delete %title?', array('%title' => $plans['name'])),
    'sipi/plans/'.$plans['pid'],
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

function sipi_plans_delete_confirm_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {
    db_delete('sipi_plans')
      ->condition('pid', $form_state['values']['pid'])
      ->execute();
  }
  $form_state['redirect'] = 'sipi/plans';
}

function sipi_plans_list_items(){
  $query=db_select('sipi_plans', 'p');
  $query->fields('p', array('pid','name','contents','posts','duration','price'));
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
