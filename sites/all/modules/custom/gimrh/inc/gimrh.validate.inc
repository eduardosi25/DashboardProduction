<?php
function gimrh_colabora_form_validate($form, &$form_state){
  if ($form_state['triggering_element']['#value'] == 'Back') {
    return;
  }

  switch ($form_state['stage']) {
    case 'splash':
      return gimrh_splash_form_validate($form, $form_state);
    break;
    case 'trabajo':
      return gimrh_trabajo_form_validate($form, $form_state);
    break;
    case 'becario':
      return gimrh_becario_form_validate($form, $form_state);
    break;
  }
}
function gimrh_splash_form_validate($form, &$form_state){
  if($form_state['clicked_button']['#name']=='trabajo' && $form_state['values']['splash']['trabajo']['legal']<1){
    form_set_error('splash][trabajo][legal','Necesitas aceptar el <strong>Aviso de Privacidad</strong> para poder continuar');
  }else if($form_state['clicked_button']['#name']=='becario' && $form_state['values']['splash']['becario']['legal']<1){
    form_set_error('splash][becario][legal','Necesitas aceptar la <strong>Carta de Confidencialidad</strong> para poder continuar');
  }
}
function gimrh_trabajo_form_validate($form, &$form_state){
  $personal=$form_state['values']['gimrh']['personal'];
  $academics=$form_state['values']['gimrh']['academics'];
  $experience=$form_state['values']['gimrh']['experience']['0']['value'];
  $interest=$form_state['values']['gimrh']['interest'];
  //$cv=$form_state['values']['gimrh']['cv'];
  if(preg_match('/[0-9]+/',$personal['name'])){
    form_set_error($form_state['values']['gimrh']['personal']['name'],'Tu nombre no puede contener números.');
  }
  if(preg_match('/[0-9]+/',$personal['plname'])){
    form_set_error($form_state['values']['gimrh']['personal']['plname'],'Tu apellido paterno no puede contener números.');
  }
  if(preg_match('/[0-9]+/',$personal['mlname'])){
    form_set_error($form_state['values']['gimrh']['personal']['mlname'],'Tu apellido materno no puede contener números.');
  }
  if(!valid_email_address($personal['email'])){
    form_set_error($form_state['values']['gimrh']['personal']['email'],'Debes indicar un correo electrónico válido.');
  }
  if(strlen(strip_tags($experience))>2000){
    form_set_error($experience,'Te pasaste del límite de 2000 letras. Revisa de nuevo por favor.');
  }
}
function gimrh_becario_form_validate($form, &$form_state){
  $personal=$form_state['values']['gimrh']['personal'];
  $academics=$form_state['values']['gimrh']['academics'];
  $interest=$form_state['values']['gimrh']['interest'];
  if(preg_match('/[0-9]+/',$personal['name'])){
    form_set_error($form_state['values']['gimrh']['personal']['name'],'Tu nombre no puede contener números.');
  }
  if(preg_match('/[0-9]+/',$personal['plname'])){
    form_set_error($form_state['values']['gimrh']['personal']['plname'],'Tu apellido paterno no puede contener números.');
  }
  if(preg_match('/[0-9]+/',$personal['mlname'])){
    form_set_error($form_state['values']['gimrh']['personal']['mlname'],'Tu apellido materno no puede contener números.');
  }
  if(!valid_email_address($personal['email'])){
    form_set_error($form_state['values']['gimrh']['personal']['email'],'Debes indicar un correo electrónico válido.');
  }
}
