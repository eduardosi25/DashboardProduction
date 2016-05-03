<?php
function gimrh_colabora_form_submit($form, &$form_state){
  switch ($form_state['stage']) {
    case 'splash':
      if($form_state['values']['splash']['trabajo']['legal']==1){
        $form_state['new_stage']='trabajo';
        $form_state['privacy']=$form_state['values']['splash']['trabajo']['legal'];
        $form_state['condifential']=0;
      }
      if($form_state['values']['splash']['becario']['legal']==1){
        $form_state['new_stage']='becario';
        $form_state['privacy']=0;
        $form_state['condifential']=$form_state['values']['splash']['trabajo']['legal'];
      }
    break;
    case 'trabajo':
      $form_state['multistep_values'][$form_state['stage']] = $form_state['values'];
      if ($form_state['triggering_element']['#value'] != 'Back') {
        gimrh_trabajo_form_submit($form, $form_state);
        $form_state['complete'] = TRUE;
      }
      break;
    case 'becario':
      $form_state['multistep_values'][$form_state['stage']] = $form_state['values'];
      if ($form_state['triggering_element']['#value'] != 'Back') {
        gimrh_becario_form_submit($form, $form_state);
        $form_state['complete'] = TRUE;
      }
      break;
    default:
      $form_state['multistep_values'][$form_state['stage']] = $form_state['values'];
      $form_state['new_stage'] = 'splash';
      break;
  }

  if (isset($form_state['complete'])) drupal_goto('colabora-con-nosotros/complete');

  if ($form_state['triggering_element']['#value'] == 'Back') {
    $form_state['new_stage'] = 'splash';
  }

  if (isset($form_state['multistep_values']['form_build_id'])) {
    $form_state['values']['form_build_id'] = $form_state['multistep_values']['form_build_id'];
  }
  $form_state['multistep_values']['form_build_id'] = $form_state['values']['form_build_id'];
  $form_state['stage'] = $form_state['new_stage'];
  $form_state['rebuild'] = TRUE;

  $form_state['stage'] = $form_state['new_stage'];
  $form_state['rebuild'] = TRUE;
}

function gimrh_trabajo_form_submit($form, &$form_state){

  var_dump($form_state);

  $personal=$form_state['values']['gimrh']['personal'];
  $academics=$form_state['values']['gimrh']['academics'];
  $experience=$form_state['values']['gimrh']['experience']['0']['value'];
  $experience_format=$form_state['values']['gimrh']['experience']['0']['format'];
  $interest=$form_state['values']['gimrh']['interest'];
  //$cv=$form_state['values']['gimrh']['cv'];
  $privacy=1;

  //Save data
  $fields=array(
      'name'        => check_plain($personal['name']),
      'plname'      => check_plain($personal['plname']),
      'mlname'      => check_plain($personal['mlname']),
      'mail'        => check_plain($personal['email']),
      'gender'      => check_plain($personal['gender']),
      'birthdate'   => check_plain($personal['birthdate']),
      'phone'       => check_plain($personal['phone']),
      'state'       => check_plain($personal['state']),
      'city'        => check_plain($personal['city']['cityname']),
      'degree'      => check_plain($academics['degree']),
      'name_degree' => check_plain($academics['degreename']),
      'experience'  => check_markup($experience),
      'experience_format'  => check_plain($experience_format),
      'interest'    => gimrh_data_interest($interest),
      //'attached'    => check_plain($cv['file']),
      'privacy'     => check_plain($privacy),
      'created'     => time(),
      'site'        => $_SERVER['HTTP_HOST'],
  );
  #var_dump($form_state['values']['gimrh']['experience']);
  #die();
  $result=drupal_write_record('gimrh',$fields);
  if(!$result){
    drupal_set_message('Error al registrar los datos, inténtalo de nuevo por favor.', 'error');
  }else{
    drupal_set_message('Tus datos fueron enviados correctamente, gracias por tu interés.', 'status');
    #$form_state['redirect'] = 'bolsa-de-trabajo/datos-enviados';
  }
}

function gimrh_becario_form_submit($form, &$form_state){
  $personal=$form_state['values']['gimrh']['personal'];
  $academics=$form_state['values']['gimrh']['academics'];
  $interest=$form_state['values']['gimrh']['interest'];
  $privacy=1;

  //Save data
  $fields=array(
      'name'        => check_plain($personal['name']),
      'plname'      => check_plain($personal['plname']),
      'mlname'      => check_plain($personal['mlname']),
      'mail'        => check_plain($personal['email']),
      'gender'      => check_plain($personal['gender']),
      'birthdate'   => check_plain($personal['birthdate']),
      'phone'       => check_plain($personal['phone']),
      'state'       => check_plain($personal['state']),
      'city'        => check_plain($personal['city']['cityname']),
      'degree'      => check_plain($academics['degree']),
      'name_degree' => check_plain($academics['degreename']),
      'institution' => check_plain($academics['institution']),
      'languages'   => check_plain($academics['languages']),
      'software'    => check_plain($academics['software']),
      'interest'    => gimrh_data_interest($interest),
      'privacy'     => check_plain($privacy),
      'created'     => time(),
      'site'        => $_SERVER['HTTP_HOST'],
  );
  #var_dump($form_state['values']['gimrh']['experience']);
  #die();
  $result=drupal_write_record('gimrh',$fields);
  if(!$result){
    drupal_set_message('Error al registrar los datos, inténtalo de nuevo por favor.', 'error');
  }else{
    drupal_set_message('Tus datos fueron enviados correctamente, gracias por tu interés.', 'status');
    #$form_state['redirect'] = 'bolsa-de-trabajo/datos-enviados';
  }
}
