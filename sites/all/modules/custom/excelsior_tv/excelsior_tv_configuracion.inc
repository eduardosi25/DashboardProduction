<?php
function excelsior_tv_configuracion( $form, &$form_state, $no_js_use = FALSE ) {

  $vars_excelsior = variable_get( 'excelsior_tv_vars', array());

    
  $form[ 'description' ] = array(
                              '#markup' => '<div>' . t( 'Ingresa los datos correspondientes: </div>' )
                          );
 
  $form[ '#tree' ] = TRUE;
  
  $form[ 'alias_url' ] = array(
                             '#type' => 'textfield',
                             '#title' => t( 'Alias URL : '),
                             '#default_value' => ( array_key_exists( 'alias_url', $vars_excelsior ) ) ? $vars_excelsior[ 'alias_url' ] : "tv",
                            );

  $form[ 'ruta_jsons' ] = array(
                             '#type' => 'textfield',
                             '#title' => t( 'Consumer Secret : '),
                             '#default_value' => ( array_key_exists( 'ruta_jsons', $vars_excelsior ) ) ? $vars_excelsior[ 'ruta_jsons' ] : "/var/srv/data/files/json/tv/",
                            );

  $form[ 'ruta_embed' ] = array(
                             '#type' => 'textfield',
                             '#title' => t( 'Access Token  : '),
                             '#default_value' => ( array_key_exists( 'ruta_embed', $vars_excelsior ) ) ? $vars_excelsior[ 'ruta_embed' ] : "/var/srv/data/files/excelsior/embed/",
                            );

  $form[ 'set_title' ] = array(
                             '#type' => 'textfield',
                             '#title' => t( 'Set Title  : '),
                             '#default_value' => ( array_key_exists( 'set_title', $vars_excelsior ) ) ? $vars_excelsior[ 'set_title' ] : "Excélsior TV | ",
                            );

   /* Para SEO */
  $form[ 'facebook_share_image' ] = array(
		                             '#type' => 'textfield',
		                             '#title' => t( 'Share image  : '),
		                             '#default_value' => ( array_key_exists( 'facebook_share_image', $vars_excelsior ) ) ? $vars_excelsior[ 'facebook_share_image' ] 
		                                              : "http://8d5306c18b850ea7e0ac-65b9b7a2fa68b3c92f951010bb26a4de.r54.cf2.rackcdn.com/excelsior-tv-redes.png",
		                             '#maxlength' => 256                 
                                    );


  $form[ 'facebook_share_tv_title' ] = array(
			                             '#type' => 'textfield',
			                             '#title' => t( 'Share title  : '),
			                             '#default_value' => ( array_key_exists( 'facebook_share_tv_title', $vars_excelsior ) ) ? $vars_excelsior[ 'facebook_share_tv_title' ] 
			                                              : "Excélsior TV | Excélsior.com.mx",
                                       );


  $form[ 'facebook_share_tv_desc' ] = array(
			                             '#type' => 'textfield',
			                             '#title' => t( 'Share description  : '),
			                             '#default_value' => ( array_key_exists( 'facebook_share_tv_desc', $vars_excelsior ) ) ? $vars_excelsior[ 'facebook_share_tv_desc' ] 
			                                              : "El portal de noticias líder en México con toda la información nacional y del mundo, con las noticas de mayor impacto en tiempo real, ahora en Televisión.",
                                         '#maxlength' => 256			                                              
                                       );

  $form[ 'facebook_share_tv_type' ] = array(
			                             '#type' => 'textfield',
			                             '#title' => t( 'Share type  : '),
			                             '#default_value' => ( array_key_exists( 'facebook_share_tv_type', $vars_excelsior ) ) ? $vars_excelsior[ 'facebook_share_tv_type' ] 
			                                              : "page",
                                       );

  $form[ 'metatag_og_site_name' ] = array(
			                             '#type' => 'textfield',
			                             '#title' => t( 'Meta site name : '),
			                             '#default_value' => ( array_key_exists( 'metatag_og_site_name', $vars_excelsior ) ) ? $vars_excelsior[ 'metatag_og_site_name' ] 
			                                              : "Excélsior",
                                       ); 

  $form[ 'news_keywords' ] = array(
	                             '#type' => 'textfield',
	                             '#title' => t( 'Keywords  : '),
	                             '#default_value' => ( array_key_exists( 'news_keywords', $vars_excelsior ) ) ? $vars_excelsior[ 'news_keywords' ] 
	                                               : "excelsior.com.mx, excélsior TV, excélsior televisión, grupo imagen multimedia, noticias, dineroenimagen, función, adrenalina, comunidad, mesa y opinión, entrevistas, entretenimiento, titulares de la tarde",
	                             '#maxlength' => 256	
                               );
   $form['count_related'] = array(
     '#type' => 'select',
     '#title' => t('Número de videos Recomendados'),
     '#options' => array(
        5 => 5,
        6 => 6,
        7 => 7,
        8 => 8,
        9 => 9,
        10 => 10,
        11 => 11,
        12 => 12,
        13 => 13,
        14 => 14,
      ),
     '#default_value' => isset($vars_excelsior['count_related'])?$vars_excelsior['count_related']:14,
     '#description' => t('Selecciones el número de videos a mostrar para Recomendados(Lo más leido).'),
   );
   $form['logs'] = array(
    '#type' => 'checkbox', 
    '#title' => t('Activar logs de actualización'),
    '#default_value' => variable_get('excelsior_tv_log', false),
    '#description' => 'Active esta casilla para registrar logs de actualización en '.CONFIG_JSON_RUTA_TV . 'multimedia_update.log',
   );

  $form['submit'] = array(
                       '#type' => 'submit',
                       '#value' => t('Submit'),
                     );

     return $form;
}

/**
 * Final submit handler.
 *
 * Reports what values were finally set.
 */
function excelsior_tv_configuracion_submit( $form, &$form_state ) {
    
    $data = array ();
    
    if ( !empty( $_POST ) && form_get_errors() ) {
          drupal_set_message(t('Ha ocurrido un error!!, datos invalidos'), 'error');
      } else {          
		     form_state_values_clean( $form_state );
        	

           $data = array (
                           "alias_url" => trim ( $form_state[ 'values' ] [ 'alias_url' ] ),
                          "ruta_jsons" => trim ( $form_state[ 'values' ] [ 'ruta_jsons' ] ),
                          "ruta_embed" => trim ( $form_state[ 'values' ] [ 'ruta_embed' ] ),
                           "set_title" => trim ( $form_state[ 'values' ] [ 'set_title' ] ),

                           "facebook_share_image" => trim ( $form_state[ 'values' ] [ 'facebook_share_image' ] ),
                           "facebook_share_tv_title" => trim ( $form_state[ 'values' ] [ 'facebook_share_tv_title' ] ),
                           "facebook_share_tv_desc" => trim ( $form_state[ 'values' ] [ 'facebook_share_tv_desc' ] ),
                           "facebook_share_tv_type" => trim ( $form_state[ 'values' ] [ 'facebook_share_tv_type' ] ),
                           "metatag_og_site_name" => trim ( $form_state[ 'values' ] [ 'metatag_og_site_name' ] ),
                           "news_keywords" => trim ( $form_state[ 'values' ] [ 'news_keywords' ] ),
                           "count_related" => $form_state['values']['count_related'],
                     );

         variable_set( "excelsior_tv_vars", $data );
         variable_set("excelsior_tv_log", $form_state['values']['logs']);

         drupal_set_message( t( 'La configuración ha sido guardada satisfactoriamente.' ) );

        }//else 

   } //excelsior_twitter_administrator_submit