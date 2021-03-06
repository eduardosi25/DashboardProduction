<?php
function gimrh_legal($type='privacy'){
  $xframe_metas = array(
    '#tag' => 'meta',
    '#attributes' => array(
      'http-equiv' => 'X-Frame-Options',
      'content'    => '*.excelsior.com.mx *.imagen.com.mx *.reporte.com.mx *.cadenatres.com.mx *.salud180.com *.actitudfem.com *.dineroenimagen.com *.swagger.mx *.atraccion360.com *.gamedots.mx *.garuyo.com *.melodijolola.com',
    ),
  );
  drupal_add_html_head($xframe_metas,'meta-xframe-gimrh');

  $xframe_metas = array(
    '#tag' => 'meta',
    '#attributes' => array(
      'http-equiv' => 'Content-Security-Policy',
      'content'    => '*.excelsior.com.mx *.imagen.com.mx *.reporte.com.mx *.cadenatres.com.mx *.salud180.com *.actitudfem.com *.dineroenimagen.com *.swagger.mx *.atraccion360.com *.gamedots.mx *.garuyo.com *.melodijolola.com',
    ),
  );
  drupal_add_html_head($xframe_metas,'meta-csp-gimrh');

  $settings=gimrh_get_variables();

  $html=$type=='privacy' ? $settings['privacy']['value'] : ($type=='confidential' ? $settings['confidential']['value'] : '');

  return $html;
}

function gimrh_data_send(){
  return '<p>Tus datos fueron enviados a nuestro equipo de Reclutamiento y Selección.</p><p>Gracias por tu interés</p>';
}

function gimrh_ajax_sector_area($form, $form_state){
  return $form['gimrh']['interest'];
}

function gimrh_list_form($form, &$form_state){
  $form=array();
  $form['gimrh_filter'] = array(
    '#type' => 'fieldset',
    '#title' => 'Filtros',
  );

  $gimrh_filter=isset($_SESSION['gimrh_filters']) ? $_SESSION['gimrh_filters'] : array();

  if(isset($form_state['filters'])){
    $gimrh_filter=array(
      'type'     => isset($form_state['filters']['type']) && !empty($form_state['filters']['type']) ? $form_state['filters']['type'] : null,
      'sector'   => isset($form_state['filters']['sector']) && !empty($form_state['filters']['sector']) ? $form_state['filters']['sector'] : null,
      'interest' => isset($form_state['filters']['interest']) && !empty($form_state['filters']['interest']) ? $form_state['filters']['interest'] : null,
      'degree'   => isset($form_state['filters']['degree']) && !empty($form_state['filters']['degree']) ? $form_state['filters']['degree'] : null,
      'state'    => isset($form_state['filters']['state']) && !empty($form_state['filters']['state']) ? $form_state['filters']['state'] : null,
      'city'     => isset($form_state['filters']['city']) && !empty($form_state['filters']['city']) ? $form_state['filters']['city'] : null,
      'gender'   => isset($form_state['filters']['gender']) && !empty($form_state['filters']['gender']) ? $form_state['filters']['gender'] : null,
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
    ),
    array(
      'data' => 'Celular',
    ),
    array(
      'data' => 'Edad',
    ),
    array(
      'data' => 'Estudios',
    ),
    array(
      'data' => 'Fecha de Registro',
      'field' => 'g.created',
    ),
  );

  // Default ordering
  if (!isset($_GET['order']) && !isset($_GET['sort'])) {
    $_GET['order'] = 'Nombre';
    $_GET['sort'] = 'ASC';
  }

  $args=arg();
  $type=isset($args[3]) && !empty($args[3]) ? $args[3] : 'work';
  if($type=='internship'){
    $query = db_select('gimrh_becario', 'g')->extend('PagerDefault');
    $query->join('locations','l','l.lid=g.city');
    $query->join('locations','l2','l2.lid=g.state');
    $query->limit(20);
    $query->fields('g',array('name','plname','mlname','mail','gender','birthdate','phone','cellphone','state','city','degree','name_degree','sector','interest','created','site'));
    $query->addField('l','name','city');
    $query->addField('l2','name','state');
  }else{
    $query = db_select('gimrh', 'g')->extend('PagerDefault');
    $query->join('locations','l','l.lid=g.city');
    $query->join('locations','l2','l2.lid=g.state');
    $query->limit(20);
    $query->fields('g',array('name','plname','mlname','mail','gender','birthdate','phone','cellphone','state','city','degree','name_degree','sector','interest','attached','created','site'));
    $query->addField('l','name','city');
    $query->addField('l2','name','state');
  }

  #Filters
  if(isset($gimrh_filter) && !empty($gimrh_filter) && count($gimrh_filter)>0){
    if($gimrh_filter['sector']!=='select' && $gimrh_filter['sector']!=='all' && $gimrh_filter['sector']!=='seleccionar'){
      $queryFilter='%'.$gimrh_filter['sector'].'%';
      $query->condition('g.sector',$queryFilter,'LIKE');
    }
    if($gimrh_filter['interest']!=='select' && $gimrh_filter['interest']!=='all' && $gimrh_filter['interest']!=='seleccionar'){
      $queryFilter='%'.$gimrh_filter['interest'].'%';
      $query->condition('g.interest',$queryFilter,'LIKE');
    }
    if($gimrh_filter['degree']!=='select' && $gimrh_filter['degree']!=='all' && $gimrh_filter['degree']!=='seleccionar'){
      $queryFilter=$gimrh_filter['degree'];
      $query->condition('g.degree',$queryFilter,'=');
    }
    if($gimrh_filter['state']!=='select' && $gimrh_filter['state']!=='all' && $gimrh_filter['state']!=='seleccionar'){
      $queryFilter=$gimrh_filter['state'];
      $query->condition('g.state',$queryFilter,'=');
    }
    if($gimrh_filter['city']!=='select' && $gimrh_filter['city']!=='all' && $gimrh_filter['city']!=='seleccionar' && $gimrh_filter['city']!==''){
      $queryFilter=$gimrh_filter['city'];
      $query->condition('g.city',$queryFilter,'=');
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
    /**
    $file=file_load($row->attached);
    if($file){
      $fileUrl=file_create_url($file->uri);
    }
    */
    $rows[] = array(
      $row->name.' '.$row->plname.' '.$row->mlname,
      $row->mail,
      $row->phone,
      $row->cellphone,
      $row->birthday,
      $row->degree.'|'.$row->name_degree,
      format_date($row->created,'long'),
      //l('CV',$fileUrl,array('absolute'=>true,'attributes'=> array('target'=>'_blank'))),
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

  $form['gimrh_filter']['sector'] = array(
    '#title'         => 'Sector',
    '#type'          => 'select',
    '#options'       => gimrh_getSector(),
    '#ajax'          => array(
      'event'    => 'change',
      'callback' => 'gimrh_filter_ajax_sector_area',
      'wrapper'  => 'sector-area',
    ),
    '#default_value' => isset($gimrh_filter['sector']) && !empty($gimrh_filter['sector']) ? $gimrh_filter['sector'] : 'seleccionar',
  );
  $options=array();
  if (isset($form_state['values']['sector']) && !empty($form_state['values']['sector'])) {
    $options = gimrh_getInterest($form_state['values']['sector']);
  }
  $form['gimrh_filter']['interest'] = array(
    '#title'         => 'Área',
    '#type'          => 'select',
    '#options'       => $options,
    '#default_value' => isset($gimrh_filter['interest']) && !empty($gimrh_filter['interest']) ? $gimrh_filter['interest'] : 'seleccionar',
    '#prefix'        => '<div id="sector-area">',
    '#suffix'        => '</div>',
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
      'maestria'    => 'Maestría',
      'posgrado'    => 'Posgrado',
    ),
    '#default_value' => isset($gimrh_filter['degree']) && !empty($gimrh_filter['degree']) ? $gimrh_filter['degree'] : 'seleccionar',
  );

  $form['gimrh_filter']['state'] = array(
    '#title'         => 'Estado',
    '#type'          => 'select',
    '#options'       => gimrh_getLocation(1,0),
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
  if (isset($form_state['values']['state']) && intval($form_state['values']['state'])>1) {
    $options = gimrh_getLocation($form_state['values']['state'],0);
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

  $form['gimrh_filter']['save_continue'] = array(
    '#value' => t('Apply'),
    '#type'  => 'submit',
  );
  $form['gimrh_filter']['reset_continue'] = array(
    '#value' => t('Reset'),
    '#type'  => 'submit',
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
  if($form_state['values']['op']=='reset' ||  $form_state['values']['op']=='Reiniciar'){
    //Filters a form
    $form_state['filters']=array(
      'sector'   => 'seleccionar',
      'interest' => 'seleccionar',
      'degree'   => 'seleccionar',
      'state'    => 'seleccionar',
      'city'     => 'seleccionar',
      'gender'   => 'seleccionar',
    );
    $_SESSION['gimrh_filters']=$form_state['filters'];
    #var_dump($_SESSION);
    #die(__FUNCTION__);
  }else{
    //Session filters
    $values=$form_state['values'];
    //Filters
    $sector   = isset($values['sector']) ? $values['sector'] : null;
    $interest = isset($values['interest']) ? $values['interest'] : null;
    $degree   = isset($values['degree']) ? $values['degree'] : null;
    $state    = isset($values['state']) ? $values['state'] : null;
    $city     = isset($values['cityname']) ? $values['cityname'] : null;
    $gender   = isset($values['gender']) ? $values['gender'] : null;
    $age      = isset($values['age']) ? $values['age'] : null;
    //Filters a form
    $form_state['filters']=array(
      'sector'   => $sector,
      'interest' => $interest,
      'degree'   => $degree,
      'state'    => $state,
      'city'     => $city,
      'gender'   => $gender,
    );
    $_SESSION['gimrh_filters']=$form_state['filters'];
  }
  $form_state['rebuild']=TRUE;
}
function gimrh_filter_ajax_locations_city($form, $form_state) {
  return $form['gimrh_filter']['city'];
}
function gimrh_filter_ajax_sector_area($form, $form_state) {
  return $form['gimrh_filter']['interest'];
}
function gimrh_get_sector($sector){
  return $sector;
}
function gimrh_get_interest($interest){
  return $interest;
}

function gimrh_get_degree($degree){
  return $degree;
}

function gimrh_send_email($data){
  $texto[]='Sr(a). '.$data['name'].' '.$data['apellidop'].' '.$data['apellidom'];
  $texto[]='P r e s e n t e .';
  $texto[]='Estimado Sr(a). '.$data['apellidop'].':';
  $texto[]='Hemos recibido su Curriculum Vitae donde nos muestra su interés por integrarse a nuestra Compañía, tenga la seguridad que consideraremos su preparación y experiencia en nuestras futuras vacantes.';
  $texto[]='Como usted sabe, este ramo de la industria es muy dinámico y se enfrenta a constantes cambios, por lo que incluiremos su información en nuestra base de datos y en caso de surgir alguna oportunidad nos pondremos en contacto con usted.';
  $texto[]='Sin mas de momento, agradecemos su interés en nuestra Compañía y aprovechamos la ocasión para desearle éxito en la búsqueda de nuevas experiencias profesionales.';
  $texto[]='Atentamente';
  $texto[]='Reclutamiento y Selección';
}