<?php
function gimrh_colabora_form($form, &$form_state){
  drupal_add_css(drupal_get_path('module','gimrh').'/css/gimrh.css');
  drupal_add_js(drupal_get_path('module','gimrh').'/js/jquery.maskedinput.min.js', 'file');
  drupal_add_js(drupal_get_path('module','gimrh').'/js/gimrh.js', 'file');

  if(!isset($form_state['stage'])){
    $form_state['stage']='splash';
    drupal_set_title('Colabora con nosotros');
  }

  $form=array();
  switch($form_state['stage']){
    case 'splash':
      return gimrh_splash_form($form, $form_state);
    break;
    case 'trabajo':
      drupal_set_title('Bolsa de trabajo');
      return gimrh_trabajo_form($form, $form_state);
    break;
    case 'becario':
      drupal_set_title('Prácticas profesionales');
      return gimrh_becario_form($form, $form_state);
    break;
    default:
      return gimrh_splash_form($form, $form_state);
    break;
  }

  return $form;
}

function gimrh_splash_form($form, &$form_state){
  $values = isset($form_state['multistep_values']['splash']) ? $form_state['multistep_values']['splash'] : array();

  $form['splash'] = array(
    '#type'  => 'fieldset',
    '#tree'  => TRUE,
  );

  //Bolsa de trabajo - Form
  $form['splash']['trabajo'] = array(
      '#type'  => 'fieldset',
      '#tree'  => TRUE,
  );
  $form['splash']['trabajo']['option'] = array(
      '#markup' => '<div id="bolsa-de-trabajo">
                    <div clas="center"><div class="candidato-image"></div></div>
                    <div class="candidato-text">
                      <p>En Grupo Imagen Multimedia queremos contar con gente con talento, deseos de crecimiento, enfoque a resultados y amplio sentido de responsabilidad que desee formar parte de la Multimedia más grande de México.<br><br></p>                    </div>
                  </div>',
  );
  $form['splash']['trabajo']['submit'] = array(
      '#type'   => 'submit',
      '#value'  => 'Bolsa de Trabajo',
      '#name'   => 'trabajo',
      '#prefix' => '<div id="work-submit-preffix">',
      '#suffix' => '</div>',
  );
  $form['splash']['trabajo']['legal'] = array(
    '#title' => 'Acepto <a href="/colabora-con-nosotros/aviso-de-privacidad" target="_blank">Aviso de privacidad</a>',
    '#type'  => 'checkbox',
    '#default_value' => isset($values['trabajo']['legal']) && !empty($values['trabajo']['legal']) ? $values['trabajo']['legal'] : 0,
  );

  //Becarios - Form
  $form['splash']['becario'] = array(
      '#type'  => 'fieldset',
      '#tree'  => TRUE,
  );
  $form['splash']['becario']['option'] = array(
      '#markup' => '<div id="becarios">
                    <div class="center"><div class="becarios-image"></div></div>
                    <div class="becarios-text">
                      <p>Gracias al vínculo que se ha establecido con Instituciones Educativas podemos ofrecerte la oportunidad de formar parte del Programa de Prácticas Profesionales y Servicio Social permitiéndonos descubrir y desarrollar el talento de las nuevas generaciones.</p>
                    </div>
                  </div>',
  );
  $form['splash']['becario']['submit'] = array(
      '#type'   => 'submit',
      '#value'  => 'Prácticas Profesionales y Servicio Social',
      '#name'   => 'becario',
      '#prefix' => '<div id="intern-submit-preffix">',
      '#suffix' => '</div>',
  );
  $form['splash']['becario']['legal'] = array(
    '#title' => 'Acepto <a href="/colabora-con-nosotros/carta-de-confidencialidad" target="_blank">Carta de confidencialidad</a>',
    '#type'  => 'checkbox',
    '#default_value' => isset($values['becario']['legal']) && !empty($values['becario']['legal']) ? $values['becario']['legal'] : 0,
  );

  return $form;
}

function gimrh_trabajo_form($form, &$form_state){
  $values = isset($form_state['multistep_values']['trabajo']) ? $form_state['multistep_values']['trabajo'] : array();
  $privacy=isset($form_state['privacy']) && !empty($form_state['privacy']) ? $form_state['privacy'] : 1;

  $form=array();
  $form['#tree'] = TRUE;
  $form['gimrh'] = array(
    '#title' => 'Antes de iniciar lee las siguientes instrucciones:',
    '#type'  => 'fieldset',
  );
  $form['gimrh']['instructions'] = array(
    '#markup' => '<ol>
                <li>Es necesario llenar todos los campos del registro.</li>
                </ol>',
  );
  $form['gimrh']['personal'] = array(
    '#type'  => 'fieldset',
    '#title' => 'Datos Personales',
    '#tree'  => TRUE,
  );
  $form['gimrh']['personal']['name'] = array(
    '#title'         => 'Nombre',
    '#type'          => 'textfield',
    '#size'          => 30,
    '#maxlength'     => 100,
    '#required'      => TRUE,
    '#default_name'  => isset($values['gimrh']['personal']['name']) && !empty($values['gimrh']['personal']['name']) ? $values['gimrh']['personal']['name'] : '',
  );
  $form['gimrh']['personal']['plname'] = array(
    '#title'         => 'Apellido Paterno',
    '#type'          => 'textfield',
    '#size'          => 30,
    '#maxlength'     => 100,
    '#required'      => TRUE,
  );
  $form['gimrh']['personal']['mlname'] = array(
    '#title'         => 'Apellido Materno',
    '#type'          => 'textfield',
    '#size'          => 30,
    '#maxlength'     => 100,
    '#required'      => TRUE,
  );
  $form['gimrh']['personal']['email'] = array(
    '#title'         => 'Correo electrónico',
    '#type'          => 'textfield',
    '#size'          => 60,
    '#maxlength'     => 150,
    '#required'      => TRUE,
  );
  $form['gimrh']['personal']['gender'] = array(
    '#title' => 'Sexo',
    '#type' => 'radios',
    '#options' => array(
        'masculino' => 'Masculino',
        'femenino'  => 'Femenino'
    ),
    '#required' => TRUE,
  );

  $date_format = 'd/m/Y';
  $form['gimrh']['personal']['birthdate'] = array(
    '#title' => 'Fecha de nacimiento',
    '#type' => 'textfield',
    '#size'          => 30,
    '#maxlength'     => 12,
    '#required' => TRUE,
  );
  $form['gimrh']['personal']['phone'] = array(
    '#title'         => 'Teléfono de casa',
    '#type'          => 'textfield',
    '#size'          => 30,
    '#maxlength'     => 60,
    '#required'      => TRUE,
  );
  $form['gimrh']['personal']['cellphone'] = array(
    '#title'         => 'Teléfono celular',
    '#type'          => 'textfield',
    '#size'          => 30,
    '#maxlength'     => 60,
    '#required'      => TRUE,
  );
  $form['gimrh']['personal']['state'] = array(
    '#title'         => 'Estado de residencia',
    '#type'          => 'select',
    '#options'       => gimrh_getLocation(1),
    '#ajax'          => array(
        'event'    => 'change',
        'callback' => 'gimrh_ajax_locations_city',
        'wrapper'  => 'location-city',
    ),
    '#default_value' => NULL,
    '#required'      => TRUE,
  );

  // Wrapper for city dropdown list
  $form['gimrh']['personal']['city'] = array(
      '#prefix' => '<div id="location-city">',
      '#suffix' => '</div>',
  );
  $options=array();
  if (isset($form_state['values']['gimrh']['personal']['state']) && intval($form_state['values']['gimrh']['personal']['state'])>1) {
    $options = gimrh_getLocation($form_state['values']['gimrh']['personal']['state']);
  }
  $form['gimrh']['personal']['city']['cityname'] = array(
      '#title'         => 'Delegación o Municipio',
      '#type'          => 'select',
      '#options'       => $options,
      '#required'      => TRUE,
  );
  $form['gimrh']['academics'] = array(
      '#type'  => 'fieldset',
      '#title' => 'Datos Académicos',
      '#tree'  => TRUE,
  );
  $form['gimrh']['academics']['degree'] = array(
      '#title'         => 'Nivel de estudios',
      '#type'          => 'select',
      '#options'       => gimrh_getDegree(1),
      '#default_value' => NULL,
      '#required'      => TRUE,
  );
  $form['gimrh']['academics']['degreename'] = array(
      '#title'         => 'Menciona la licenciatura o Posgrado',
      '#type'          => 'textfield',
      '#size'          => 60,
      '#maxlength'     => 150,
      '#required'      => TRUE,
  );
  $form['gimrh']['experience']=array(
      '#type'  => 'fieldset',
      '#title' => 'Experiencia laboral',
      '#tree'  => TRUE,
  );
  $form['gimrh']['experience'][0] = array(
      '#title'         => 'Última experiencia laboral',
      '#type'          => 'text_format',
      '#default_value' => NULL,
      '#format'        => 'lite',
      '#description'   => 'Tienes un límite de 2000 letras.'
  );
  $form['gimrh']['sector'] = array(
    '#title'         => 'Sector',
    '#type'          => 'select',
    '#options'       => gimrh_getSector(1),
    '#default_value' => NULL,
    '#required'      => TRUE,
  );
  $form['gimrh']['interest'] = array(
      '#title'         => 'Área de interés',
      '#description'   => 'Sólo puedes elegir una opción.',
      '#type'          => 'select',
      '#options'       => gimrh_getInterest(1),
      '#default_value' => NULL,
      '#required'      => TRUE,
  );
  /**
  $form['gimrh']['cv']=array(
      '#type'  => 'fieldset',
      '#title' => 'Agrega tu Currículum Vitae',
      '#tree'  => TRUE,
  );
  $form['gimrh']['cv']['file']= array(
      '#title'             => 'Archivo',
      '#type'              => 'managed_file',
      '#description'       => 'Aceptamos archivos en formato Word (.doc y .docx) y Adobe Acrobat Reader (.pdf).<br>El peso máximo de tu archivo debe ser de 1MB.',
      '#upload_validators' => array(
          'file_validate_extensions' => array('doc docx pdf'),
          'file_validate_size'       => array(2*1024*1024),
      ),
      '#upload_location'   => 'public://gimrh_uploads/',
      '#process'           => array('gimrh_file_element_process'),
  );
   */
  $form['submit'] = array(
      '#type'   => 'submit',
      '#value'  => 'Enviar datos',
  );
  return $form;
}
function gimrh_ajax_locations_city($form, $form_state) {
  return $form['gimrh']['personal']['city'];
}
function gimrh_ajax_sector_area($form, $form_state){
  return $form['gimrh']['area'];
}

/**
 * Implements hook_file_element_process().
 */
function gimrh_file_element_process($element, &$form_state, $form) {
  $element = file_managed_file_process($element, $form_state, $form);
  if ($element['#file']) {
    $element['remove_button'] = array(
        '#name' => 'logo_remove_button',
        '#type' => 'submit',
        '#value' => 'Eliminar',
        '#validate' => array(),
        '#submit' => array('ajax_file_update_callback'),
        '#limit_validation_errors' => array($element['#parents']),
        '#ajax' => array(
            'callback' => 'ajax_file_update_callback',
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
function ajax_file_update_callback($form, &$form_state){
  if (!empty($form['gimrh']['cv']["file"]["#value"])) {
    $form['gimrh']['cv']["file"]["#value"]=null;
    $form['gimrh']['cv']["file"]["filename"]=null;
  }
  return $form['gimrh']['cv']["file"];
}


function gimrh_becario_form($form, &$form_state){
  $values = isset($form_state['multistep_values']['becario']) ? $form_state['multistep_values']['becario'] : array();
  $confidential=isset($form_state['privacy']) && !empty($form_state['privacy']) ? $form_state['privacy'] : 1;
  $form=array();
  $form['#tree'] = TRUE;
  $form['gimrh'] = array(
      '#title' => 'Antes de iniciar lee las siguientes instrucciones:',
      '#type'  => 'fieldset',
  );
  $form['gimrh']['instructions'] = array(
      '#markup' => '<ol>
                  <li>Los campos marcados con un asterisco (*) son obligatorios.</li>
                  </ol>',
  );
  $form['gimrh']['personal'] = array(
      '#type'  => 'fieldset',
      '#title' => 'Datos Personales',
      '#tree'  => TRUE,
  );
  $form['gimrh']['personal']['name'] = array(
      '#title'         => 'Nombre',
      '#type'          => 'textfield',
      '#size'          => 30,
      '#maxlength'     => 100,
      '#required'      => TRUE,
  );
  $form['gimrh']['personal']['plname'] = array(
      '#title'         => 'Apellido Paterno',
      '#type'          => 'textfield',
      '#size'          => 30,
      '#maxlength'     => 100,
      '#required'      => TRUE,
  );
  $form['gimrh']['personal']['mlname'] = array(
      '#title'         => 'Apellido Materno',
      '#type'          => 'textfield',
      '#size'          => 30,
      '#maxlength'     => 100,
      '#required'      => TRUE,
  );
  $form['gimrh']['personal']['email'] = array(
      '#title'         => 'Correo electrónico',
      '#type'          => 'textfield',
      '#size'          => 60,
      '#maxlength'     => 150,
      '#required'      => TRUE,
  );
  $form['gimrh']['personal']['gender'] = array(
      '#title' => 'Sexo',
      '#type' => 'radios',
      '#options' => array(
          'masculino' => 'Masculino',
          'femenino'  => 'Femenino'
      ),
      '#required' => TRUE,
  );

  $date_format = 'd/m/Y';
  $form['gimrh']['personal']['birthdate'] = array(
      '#title' => 'Fecha de nacimiento',
      '#type' => 'textfield',
      '#size'          => 30,
      '#maxlength'     => 12,
      '#required' => TRUE,
  );
  $form['gimrh']['personal']['phone'] = array(
    '#title'         => 'Teléfono de casa',
    '#type'          => 'textfield',
    '#size'          => 30,
    '#maxlength'     => 60,
    '#required'      => TRUE,
  );
  $form['gimrh']['personal']['cellphone'] = array(
      '#title'         => 'Teléfono celular',
      '#type'          => 'textfield',
      '#size'          => 30,
      '#maxlength'     => 60,
      '#required'      => TRUE,
  );
  $form['gimrh']['personal']['state'] = array(
      '#title'         => 'Estado de residencia',
      '#type'          => 'select',
      '#options'       => gimrh_getLocation(1),
      '#ajax'          => array(
          'event'    => 'change',
          'callback' => 'gimrh_ajax_locations_city',
          'wrapper'  => 'location-city',
      ),
      '#default_value' => NULL,
      '#required'      => TRUE,
  );

  // Wrapper for city dropdown list
  $form['gimrh']['personal']['city'] = array(
      '#prefix' => '<div id="location-city">',
      '#suffix' => '</div>',
  );
  $options=array();
  if (isset($form_state['values']['gimrh']['personal']['state']) && intval($form_state['values']['gimrh']['personal']['state'])>1) {
    $options = gimrh_getLocation($form_state['values']['gimrh']['personal']['state']);
  }
  $form['gimrh']['personal']['city']['cityname'] = array(
      '#title'         => 'Delegación o Municipio',
      '#type'          => 'select',
      '#options'       => $options,
      '#required'      => TRUE,
  );
  $form['gimrh']['academics'] = array(
      '#type'  => 'fieldset',
      '#title' => 'Institución educativa',
      '#tree'  => TRUE,
  );
  $form['gimrh']['academics']['degree'] = array(
      '#title'         => 'Carrera',
      '#type'          => 'select',
      '#options'       => gimrh_getDegree(1),
      '#default_value' => NULL,
      '#required'      => TRUE,
  );
  $form['gimrh']['academics']['degreename'] = array(
      '#title'         => 'Menciona la licenciatura o Posgrado',
      '#type'          => 'textfield',
      '#size'          => 60,
      '#maxlength'     => 150,
      '#required'      => TRUE,
  );
  $form['gimrh']['academics']['institution'] = array(
      '#title'         => 'Instituto o Universidad',
      '#type'          => 'textfield',
      '#size'          => 60,
      '#maxlength'     => 150,
      '#required'      => TRUE,
  );
  $form['gimrh']['academics']['credits'] = array(
    '#title'         => 'Créditos',
    '#type'          => 'textfield',
    '#size'          => 60,
    '#maxlength'     => 150,
    '#required'      => TRUE,
  );

  $form['gimrh']['academics']['languages'] = array(
    '#title'         => 'Idiomas',
    '#type'          => 'textfield',
    '#size'          => 20,
    '#maxlength'     => 150,
  );
  $form['gimrh']['academics']['languages_domain'] = array(
    '#title'         => 'Porcentaje',
    '#type'          => 'textfield',
    '#size'          => 10,
    '#maxlength'     => 5,
  );
  $form['gimrh']['academics']['software'] = array(
    '#title'         => 'Software de computadora',
    '#type'          => 'textfield',
    '#size'          => 60,
    '#maxlength'     => 150,
  );
  $form['gimrh']['academics']['software_domain'] = array(
      '#title'         => 'Porcentaje',
      '#type'          => 'textfield',
      '#size'          => 10,
      '#maxlength'     => 5,
  );
  $form['gimrh']['sector'] = array(
    '#title'         => 'Sector',
    '#type'          => 'select',
    '#options'       => gimrh_getSector(1),
    '#ajax'          => array(
      'event'    => 'change',
      'callback' => 'gimrh_ajax_sector_area',
      'wrapper'  => 'sector-area',
    ),
    '#default_value' => NULL,
    '#required'      => TRUE,
  );
  // Wrapper for area dropdown list
  $form['gimrh']['area'] = array(
    '#prefix' => '<div id="sector-area">',
    '#suffix' => '</div>',
  );
  $options=array();
  if (isset($form_state['values']['gimrh']['sector']) && intval($form_state['values']['gimrh']['sector'])>1) {
    $options = gimrh_getInterest($form_state['values']['gimrh']['sector']);
  }
  $form['gimrh']['area']['interest'] = array(
    '#title'         => 'Área de interés',
    '#description'   => 'Sólo puedes elegir una opción.',
    '#type'          => 'select',
    '#options'       => $options,
    '#default_value' => NULL,
    '#required'      => TRUE,
  );
  $form['submit'] = array(
      '#type'   => 'submit',
      '#value'  => 'Enviar datos',
  );
  return $form;
}
