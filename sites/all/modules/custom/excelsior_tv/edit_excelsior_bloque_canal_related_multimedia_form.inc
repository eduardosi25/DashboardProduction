<?php 
function edit_excelsior_bloque_canal_related_multimedia ( $form, &$form_state ){

    $form = array();
    $form['marco'] = array(
        '#type'=>'fieldset',
        '#prefix'=>'<div>',
        '#suffix'=>'</div>'
    );
    $form['marco']['description'] = array(
        '#type' => 'item',
        '#title' => t('Configuración de Videos Relacionados.'),
    );
    $form['marco']['title_video'] = array(
        '#type' => 'textfield',
        '#title' => t('Titulo del video principal'),
        '#required' => TRUE,
        '#default_value' => variable_get('imx_titulo_video', ''),
        '#description' => t('Ejemplo: NO te hagas bolas'),
    );
    $form['marco']['streaming_url'] = array(
        '#type' => 'textfield',
        '#title' => t('URL de video de YOUTUBE ó Play list '),
        '#required' => TRUE,
        '#default_value' => variable_get('imx_streaming_url', ''),
        '#description' => t('Ejemplo:https://www.youtube.com/watch?v=F1WaCjrf87o&list=TLtmnoVojDh37edhQEA9zvJS45RWo0Jw3E'),
    );
    $form['marco']['autoplay'] = array(
        '#type' => 'checkbox',
        '#title' => t('Activar autoplay'),
        '#default_value' => variable_get('multimedia_autoplay', 1),
        '#description' => t('Active esta casilla para que el video principal se reproduzca al cargar la página.'),
    );
    $form['marco']['buscador'] = array(
        '#type'=>'fieldset',
        '#prefix'=>'<div id="imx-buscador-multimedia">',
        '#suffix'=>'</div>'
    );
    $form['marco']['buscador']['description'] = array(
        '#type' => 'item',
        '#title' => t('Listado de Videos Relacionados.'),
    );
    $form['marco']['buscador']['chanel_youtube'] = array(
        '#type' => 'textfield',
        '#title' => t('Titulo del Canal'),
        '#required' => TRUE,
        '#default_value' => variable_get('imx_titulo_chanel', ''),
        '#description' => t('DineroEnImagen'),
    );
    $form['marco']['buscador']['search'] = array(
        '#title' => t('Search'),
        '#type' => 'textfield',
        '#size' => 60,
        '#maxlength' => 128,
        '#default_value' => '',
        '#description' => t('Enter para buscar'),
        '#ajax' => array(
          'event' => 'none',
          'callback' => 'ajax_search_token',
          'wrapper' => 'checkboxes-div',
          'method' => 'replace',
          'keypress' => true,
          'progress'=> array('type'=> 'bar', 'message' => t('Please wait...')),
          ),
    );
    
    /** videos seleccionados */
    $videos_checked = variable_get('imx_search_token_checked',array());
    $videos_titles = variable_get('imx_search_token_titles',array());

    if ( count($videos_checked) > 0 && count($videos_titles) > 0) {
        $video_related = _get_videos_related($videos_checked, $videos_titles);
    }
    /** videos seleccionados */

    $form['marco']['buscador']['checkboxes_fieldset'] = array(
        '#title' => isset($videos_titles)?t("Videos encontrados"):t(""),
        '#prefix' => '<div id="checkboxes-div">',
        '#suffix' => '</div>',
        '#type' => 'checkboxes',
        #'#description' => t('This is where we get automatically generated checkboxes'),
        '#default_value' =>  isset($video_related['default_value'])?$video_related['default_value']:array(),
        '#options' => isset($videos_titles)?$videos_titles:array(),
        #'#options' => variable_get('imx_check',array()),
    );

    if (isset($form_state['values']['search']) ) {
        $form['marco']['buscador']['checkboxes_fieldset']['#options'] = _search_token($form_state['values']['search'],$form_state['values']['chanel_youtube']);
        $form['marco']['buscador']['checkboxes_fieldset']['#title'] = t("Videos encontrados ( Debes seleccionar 3 videos )");
    }
    $form['marco']['resultados'] = array(
        '#type'=>'fieldset',
        '#prefix'=>'<div id="imx-resultados-multimedia">',
        '#suffix'=>'</div>'
    );
    
    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Save'),
    );

    return $form;
}

/**
 * Callback element needs only select the portion of the form to be updated.
 * Since #ajax['callback'] return can be HTML or a renderable array (or an
 * array of commands), we can just return a piece of the form.
 * See @link ajax_example_advanced.inc AJAX Advanced Commands for more details
 * on AJAX framework commands.
 *
 * @return renderable array (the checkboxes fieldset)
 */

function ajax_search_token(&$form, &$form_state) {
  return $form['marco']['buscador']['checkboxes_fieldset'];
}

function _defaul_values(){
    $data = array();
    $file =CONFIG_JSON_RUTA_TV . "multimedia-portada-relacionados.json";
    $data = json_decode( file_get_contents( $file ), TRUE );
     foreach ($data['data'] as $key => $value) {
            foreach ($value['relacionados'] as $key => $val) {
        
          $checbox[$val['id']] = $val['title'];
  }
}
    return $checbox;
}

function _search_token($search,$chanel) {
  $search = htmlentities(check_plain(preg_replace('(\s)','+',$search)));
  $url = "https://gdata.youtube.com/feeds/api/videos?author=$chanel&v=2&orderby=published&alt=jsonc&q=$search";
  $data = array();
  $videos = array();

  $ch = curl_init();
  curl_setopt($ch, CURLOPT_URL, $url);
  curl_setopt($ch, CURLOPT_HEADER, 0);
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
  curl_setopt($ch, CURLOPT_TIMEOUT, 10);
  curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);
  $output = curl_exec($ch);
  curl_close($ch);
 
  $data = json_decode($output,true);

  if (isset($data['data']['items'])) {
    foreach ($data['data']['items'] as $key => $value) {
      $videos[$value['id']] = $value['title'];
    }
    //guardando busqueda
    variable_set('imx_search_token_titles', $videos);
  }

  return $videos;
}

function edit_excelsior_bloque_canal_related_multimedia_validate($form, &$form_state) {
  $checked = array();
  foreach ($form_state['values']['checkboxes_fieldset'] as $youtube_id => $youtube_value) {
    if ($youtube_id === $youtube_value) {
        array_push($checked, $youtube_id);
    }
  }
  if (count($checked) < 3) {
    form_set_error('checkboxes_fieldset', 'Debes seleccionar 3 videos.');
  }  
}
function edit_excelsior_bloque_canal_related_multimedia_submit($form, &$form_state) {

    #drupal_set_message('<pre>'.dvm($form_state['values']).'</pre>');
    $content = array ();
    $data = array ();
    $file = CONFIG_JSON_RUTA_TV . "multimedia-portada-relacionados.json";
    $video_related = array();

    variable_set('imx_titulo_video', $form_state['values']['title_video']);
    variable_set('imx_streaming_url', $form_state['values']['streaming_url']);
    variable_set('imx_titulo_chanel', $form_state['values']['chanel_youtube']);
    variable_set('imx_search', $form_state['values']['search']);
    variable_set('imx_search_token_checked', $form_state['values']['checkboxes_fieldset']);
    variable_set('multimedia_autoplay', $form_state['values']['autoplay']);
    #variable_set('imx_relates',);

    /** videos seleccionados */
    $videos_checked = $form_state['values']['checkboxes_fieldset'];
    $videos_titles = variable_get('imx_search_token_titles',array());

    /** videos seleccionados */
    if ( count($videos_checked) > 0 && count($videos_titles) > 0) {
        $video_related = _get_videos_related($videos_checked, $videos_titles);
    }
    /** videos seleccionados */

    $embed = _get_youtubeid( $form_state[ 'values' ][ 'streaming_url'] );
    $video_url = $form_state[ 'values' ][ 'streaming_url'];
    if ($form_state['values']['autoplay']) {
        $video_url_parse = array();
        $video_url_parse = parse_url($video_url);
        if (is_array($video_url_parse) && isset($video_url_parse['query'])) {
            $video_url .= "&autoplay=1";
        }
    }

    $url_video = get_url_videos($video_url, $embed );

    $content[] =array(
        "title" => $form_state['values']['title_video'],
        "vid" => $embed,
        "url" => $url_video,
        "canal" => $form_state['values']['chanel_youtube'],
        "tags" => $form_state['values']['search'],
        "relacionados" => $video_related['related'],
    );
    $data["data" ] = $content;
    
    file_put_contents( $file, json_encode( $data ) );

    /** Salvando en esquema*/
    $playlist_title = 'Relacionados';
    excelsior_tv_delete_list($playlist_title);
    foreach ($video_related['related'] as $video_key => $video_title) {
        $str_curl = CurlLinkXVideo($video_key);
        $video = excelsior_tv_get_retrieve_gdata($str_curl, $playlist_title);
        if ( count($video) > 0) {
            #$video['video']['title'] = $video_title;
            excelsior_tv_save_gdata($video);
        }
    }
    /** Salvando en esquema*/
    excelsior_tv_feed();
    drupal_set_message ( ' Se guardo correctamente la lista Relacionados . ' ); 
}

function id_video_check( $dato1,$dato2){

 foreach ($dato1 as $key => $value) {
        $id_video[$key]= array ( 'id' => $value);  
    }
foreach ($dato2 as $key => $value) {
        $titulo[$key]= array ( 'title' => $value);  
    }

    $union =array_merge_recursive($id_video, $titulo  );
    return $union;
 }

/** videos seleccionados */
function _get_videos_related($videos_checked, $videos_titles) {
    $default_value = array();
    $related = array();

    if ( count($videos_checked) > 0 && count($videos_titles) > 0) {
        foreach ($videos_checked as $youtube_id => $youtube_title) {
            if ($youtube_id === $youtube_title) {
                array_push($default_value, $youtube_id);
                $videos_pre_insersect[$youtube_id] = $youtube_id;
            }
        }
        $related = array_intersect_key($videos_titles, $videos_pre_insersect);
    }

    return array('related' => $related, 'default_value' => $default_value);
}