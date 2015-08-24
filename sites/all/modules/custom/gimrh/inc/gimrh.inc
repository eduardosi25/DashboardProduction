<?php
function gimrh_privacy(){
  $settings=gimrh_get_variables();
  return $settings['privacy']['value'];
}
function gimrh_data_send(){
  return '<p>Tus datos fueron enviados a nuestro equipo de Reclutamiento y Selección.</p><p>Gracias por tu interés</p>';
}
function gimrh_list_form($form, &$form_state){
  $form=array();
  $form['gimrh_filter'] = array(
    '#type' => 'fieldset',
    '#title' => 'Filtros',
  );

  $gimrh_filter=isset($_SESSION['gimrh_filters']) ? $_SESSION['gimrh_filters'] : array();

  if(isset($form_state['filters'])){
    #var_dump($form_state);
    #die();

    $gimrh_filter=array(
      'interest' => $form_state['filters']['interest'],
      'degree'   => $form_state['filters']['degree'],
      'state'    => $form_state['filters']['state'],
      'city'     => $form_state['filters']['city'],
      'gender'   => $form_state['filters']['gender'],
      'age'      => $form_state['filters']['age'],
    );
  }

  $header = array(
    array(
      'data' => 'Nombre',
      'field' => 'g.name',
    ),
    array(
      'data' => 'Correo Electrónico',
      'field' => 'g.mail',
    ),
    array(
      'data' => 'Teléfono',
      'field' => 'g.phone',
    ),
    array(
      'data' => 'Licenciatura',
      'field' => 'g.name_degree',
    ),
    array(
      'data' => t('Descargar CV'),
    ),
  );

  // Default ordering
  if (!isset($_GET['order']) && !isset($_GET['sort'])) {
    $_GET['order'] = 'Nombre';
    $_GET['sort'] = 'ASC';
  }

  $query = db_select('gimrh', 'g')->extend('PagerDefault');
  $query->join('locations','l','l.lid=g.city');
  $query->join('locations','l2','l2.lid=g.state');
  $query->limit(20);
  $query->fields('g',array('name','plname','mlname','mail','gender','birthdate','phone','state','city','degree','name_degree','interest','attached','created','site'));
  $query->addField('l','name','city');
  $query->addField('l2','name','state');

  //var_dump($gimrh_filter);

  if(isset($gimrh_filter) && !empty($gimrh_filter) && count($gimrh_filter)>0){

    if($gimrh_filter['interest']!=='select' && $gimrh_filter['interest']!=='all' && $gimrh_filter['interest']!=='seleccionar'){
      $queryFilter='%'.$gimrh_filter['interest'].'%';
      $query->condition('g.interest',$queryFilter,'LIKE');
    }

    if($gimrh_filter['degree']!=='select' && $gimrh_filter['degree']!=='all' && $gimrh_filter['degree']!=='seleccionar'){
      $queryFilter=$gimrh_filter['degree'];
      $query->condition('g.degree',$queryFilter,'=');
    }

    if($gimrh_filter['gender']!=='select' && $gimrh_filter['gender']!=='all' && $gimrh_filter['gender']!=='seleccionar'){
      $queryFilter=$gimrh_filter['gender'];
      $query->condition('g.gender',$queryFilter,'=');
    }
  }

  $query=$query->extend('TableSort')->orderByHeader($header);
  $result=$query->execute();
  $rows=array();
  foreach ($result as $row) {
    $file=file_load($row->attached);
    if($file){
      $fileUrl=file_create_url($file->uri);
    }
    $rows[] = array(
      $row->name,
      $row->mail,
      $row->phone,
      $row->name_degree,
      l('CV',$fileUrl,array('absolute'=>true,'attributes'=> array('target'=>'_blank'))),
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

  $form['gimrh_filter']['interest'] = array(
    '#title'         => 'Áreas de interés',
    '#type'          => 'select',
    '#options'       => gimrh_getInterest(),
    '#default_value' => isset($gimrh_filter['interest']) && !empty($gimrh_filter['interest']) ? $gimrh_filter['interest'] : 'seleccionar',
  );

  $form['gimrh_filter']['degree'] = array(
    '#title'         => 'Nivel de estudios',
    '#type'          => 'select',
    '#options'       => array(
      'seleccionar' => '- Seleccionar -',
      'all'         => 'Todas',
      'basica'      => 'Básica',
      'media'       => 'Media Superior',
      'superior'    => 'Superior',
      'posgrado'    => 'Posgrado',
    ),
    '#default_value' => isset($gimrh_filter['degree']) && !empty($gimrh_filter['degree']) ? $gimrh_filter['degree'] : 'seleccionar',
  );

  $form['gimrh_filter']['state'] = array(
    '#title'         => 'Estado',
    '#type'          => 'select',
    '#options'       => gimrh_getLocation(1),
    '#ajax'          => array(
      'event'    => 'change',
      'callback' => 'gimrh_filter_ajax_locations_city',
      'wrapper'  => 'location-city',
    ),
    '#default_value' => NULL,
  );

  // Wrapper for city dropdown list
  $form['gimrh_filter']['city'] = array(
    '#prefix' => '<div id="location-city">',
    '#suffix' => '</div>',
  );
  $options=array();
  if (isset($form_state['values']['gimrh_filter']['state']) && intval($form_state['values']['gimrh_filter']['state'])>1) {
    $options = gimrh_getLocation($form_state['values']['state']);
  }
  $form['gimrh_filter']['city']['cityname'] = array(
    '#title'         => 'Delegación/Municipio',
    '#type'          => 'select',
    '#options'       => $options,
  );

  $form['gimrh_filter']['gender'] = array(
    '#title'         => 'Sexo',
    '#type'          => 'select',
    '#options'       => array(
      'seleccionar' => '- Seleccionar -',
      'masculino'   => 'Masculino',
      'femenino'    => 'Femenino',
    ),
    '#default_value' => isset($gimrh_filter['gender']) && !empty($gimrh_filter['gender']) ? $gimrh_filter['gender'] : 'seleccionar',
  );

  $form['gimrh_filter']['gimrh_filter_submit'] = array(
    '#value' => t('Filter'),
    '#type'  => 'submit',
    '#attributes' => array('class' => array('left')),
  );

  $form['table'] = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
    '#empty' => 'No se encontraron registros.',
    '#caption' => 'Registro de interesados en Bolsa de Trabajo | GIM RH',
  );

  return $form;
}

function gimrh_list_form_submit($form, &$form_state){
  //Session filters
  $values=$form_state['values'];
  //Filters
  $interest = isset($values['interest']) ? $values['interest'] : null;
  $degree   = isset($values['degree']) ? $values['degree'] : null;
  $state    = isset($values['state']) ? $values['state'] : null;
  $city     = isset($values['city']) ? $values['city'] : null;
  $gender   = isset($values['gender']) ? $values['gender'] : null;
  $age      = isset($values['age']) ? $values['age'] : null;
  //Filters a form
  $form_state['filters']=array(
    'interest' => $interest,
    'degree'   => $degree,
    'state'    => $state,
    'city'     => $city,
    'gender'   => $gender,
    'age'      => $age,
  );
  $_SESSION['gimrh_filters']=$form_state['filters'];
  $form_state['rebuild']=TRUE;
}
function gimrh_filter_ajax_locations_city($form, $form_state) {
  #var_dump($form['gimrh_filter']);
  #die();
  return $form['gimrh_filter']['city'];
}
function gimrh_get_interest($interest){
  return $interest;
}

function gimrh_get_degree($degree){
  return $degree;
}