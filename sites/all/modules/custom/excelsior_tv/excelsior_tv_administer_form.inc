<?php

/*  */
/* Formulario para crear un lista de Galeria de videos a partir de Youtube */


function excelsior_tv_administer_form ( $form, &$form_state ){


	 $mensaje = '';
	 
	$val_error = variable_get ( "error_procces_lista_reproduccion_tv", "" );
	$name_error = variable_get ( "error_procces_lista_reproduccion_tv_name", "" );
	$lista_error = variable_get ( "error_procces_lista_reproduccion_tv_lista", "" );
	
     if ( strlen ( $val_error ) > 0 ){    	  
		 $mensaje = '<div class="messages error"> <h2 class="element-invisible">Mensaje de error</h2> Error, al guardar nueva lista de reproducción, verifica el URL de la lista. </div>';
		 variable_set ( "error_procces_lista_reproduccion_tv", null );	
		 variable_set ( "error_procces_lista_reproduccion_tv_name", null );
		 variable_set ( "error_procces_lista_reproduccion_tv_lista", null );
       }	

 
  $form[ 'form_youtube_tv' ] = array(
                                    '#type' => 'fieldset', 
                                    '#title' => t( "" ), 
                                    '#weight' => 350, 
                                    '#collapsible' => false, 
                                    '#collapsed' => false,
                               );

       $form[ "form_youtube_tv" ][ 'script_html_msg_error_super_ocho' ] = array(
								                                           '#type' => 'markup',    
								                                           '#prefix' => "<p>" . $mensaje,
								                                           '#suffix' => '</p>'           
                                                                          );   


		$form [ 'form_youtube_tv' ][ 'name' ] = array(
		                                            '#type' => 'textfield',
		                                            '#title' => t( 'Nombre de la lista:' ),
		                                            '#default_value' => $name_error,
		                                            '#maxlength' => 50,
		                                            '#size' => 50,
		                                            '#description' => t( 'Introduzca el nombre de la lista.' ),
		                                            '#id' => 'tv_name_lista',
		                                            '#required' => true
		                                    );

		$form [ 'form_youtube_tv' ][ 'lista' ] = array(
		                                            '#type' => 'textfield',
		                                            '#title' => t( 'URL de la Lista youtube:' ),
		                                            '#default_value' =>  $lista_error,
		                                            '#maxlength' => 150,
		                                            '#size' => 150,
		                                            '#description' => t( 'Introduzca el URL de la lista. P/E: http://www.youtube.com/playlist?list=PL206F54543088F3FD&feature=plcp' ),
		                                            '#id' => 'tv_url_lista',
		                                            '#required' => true
		                                    ); 

		$form [ 'form_youtube_tv' ][ 'num_mostrar' ] = array(
		                                            '#type' => 'textfield',
		                                            '#title' => t( 'No. de videos a mostrar:' ),
		                                            '#default_value' =>  "6",
		                                            '#maxlength' => 3,
		                                            '#size' => 3,
		                                            '#description' => t( 'Introduzca el Número de videos a mostrar en lista.' ),
		                                            '#id' => 'tv_num_mostrar',
		                                            '#required' => true
		                                       );

		$form [ 'form_youtube_tv' ][ 'estatus' ] = array(
		                                            '#type' => 'select',
		                                            '#title' => t( 'Estatus de la lista:' ),
		                                            '#default_value' => variable_get( 'form_new_status','desactivar'),
		                                            '#options' => array(
		                                                             'activar' => t( 'Activar' ), 
		                                                             'desactivar' => t( 'Desactivar' ),                                                                 
		                                                           ),                
		                                            '#description' => t( 'Seleccionar el estatus de la lista.' ),
		                                            '#id' => 'tv_estatus',                                                        
		                                       );            

		$form [ 'form_youtube_tv' ][ 'peso' ] = array(
		                                            '#type' => 'select',
		                                            '#title' => t( 'Peso de la lista:' ),
		                                            '#default_value' => '_none',
		                                            '#options' => array(
		                                                             '_none' => t( '- Ninguno -' ), 
		                                                             '0' => t( '0' ),                                                                 
		                                                             '1' => t( '1' ),  
		                                                             '2' => t( '2' ),  
		                                                             '3' => t( '3' ),  
		                                                             '4' => t( '4' ),  
		                                                             '5' => t( '5' ),  
		                                                             '6' => t( '6' ),  
		                                                             '7' => t( '7' ),  
		                                                             '8' => t( '8' ),  
		                                                             '9' => t( '9' ),  
		                                                             '10' => t( '10' ),  
		                                                             '11' => t( '11' ),  
		                                                             '12' => t( '12' ),  
		                                                             '13' => t( '13' ),  
		                                                             '14' => t( '14' ),  
		                                                             '15' => t( '15' ),  
		                                                             '16' => t( '16' ),  
		                                                             '17' => t( '17' ),
		                                                             '18' => t( '18' ),  
		                                                             '19' => t( '19' ),  
		                                                             '20' => t( '20' ),  
		                                                             '21' => t( '21' ),  		                                                             
		                                                             '22' => t( '22' ),  
		                                                             '23' => t( '23' ),  
		                                                             '24' => t( '24' ),  
		                                                             '25' => t( '25' ),  		                                                             
		                                                             '26' => t( '26' ),  
		                                                             '27' => t( '27' ),  
		                                                             '28' => t( '28' ),  
		                                                             '29' => t( '29' ),  		                                                             
		                                                             '30' => t( '30' ),  
		                                                             '31' => t( '31' ),  
		                                                             '32' => t( '32' ),  
		                                                             '33' => t( '33' ),  		                                                             
		                                                             '34' => t( '34' ),  
		                                                             '35' => t( '35' ),  
		                                                             '36' => t( '36' ),  
		                                                             '37' => t( '37' ),  
		                                                             '38' => t( '38' ),  
		                                                             '39' => t( '39' ),  
		                                                             '40' => t( '40' ),                                                               
		                                                           ),                
		                                            '#description' => t( 'Seleccionar el peso de la lista.' ),
		                                            '#id' => 'tv_peso',                                                        
		                                       );


		$form [ 'form_youtube_tv' ][ 'placa' ] = array(
		                                            '#type' => 'select',
		                                            '#title' => t( 'Seleccionar placar para la lista:' ),
		                                            '#default_value' => '_none',
		                                            '#options' => array(
		                                                                  '_none' => t( '_none' ), 	                                                                                            
		                                                               'nacional' => t( 'Nacional'),
                                                                      'comunidad' => t( 'Comunidad' ),
                                                                         'global' => t( 'Global' ),		
                                                                        'funcion' => t( 'Función' ),		
                                                                     'adrenalina' => t( 'Adrenalina' ),
                                                                         'dinero' => t( 'Dinero' ),
                                                                    'hackersBits' => t( 'Hackers y Bits' ),                                                         
                                                                          'salud' => t( 'Salud' )                                                         
		                                                           ),                
		                                            '#description' => t( 'Seleccionar placar para la lista.' ),
		                                            '#id' => 'tv_placa',                                                        
		                                       );

		$form[ 'form_youtube_tv' ][ 'identificador' ] = array(
		                                            '#type' => 'hidden',
		                                            '#id' => 'tv_identificador_id',
		                                            '#value' => md5 ( time() . microtime() )
		                            );                   


 
    
    $form[ 'form_youtube_tv_top' ]['submit'] = array( '#type' => 'submit', '#value' => t(' Guardar ') );
    $form[ 'form_youtube_tv_top' ]['bottom'] = array( '#type' => 'submit', '#value' => t(' Guardar ') );
        
    $form[ '#theme' ] = 'excelsior_tv_administer_form';

	return ( $form );
}


function excelsior_tv_administer_form_validate( &$form, &$form_state ){

	  $name_lista = $form_state[ "values" ][ "name" ];
	   $url_lista = $form_state [ "values" ][ "lista" ];
	   

       if ( get_validate_url_lista_reproduce ( $url_lista, 10 ) ){

     	   variable_set( 'error_procces_lista_reproduccion_tv', md5 ( microtime() ) );
     	   variable_set ( "error_procces_lista_reproduccion_tv_name", $name_lista );
		   variable_set ( "error_procces_lista_reproduccion_tv_lista", $url_lista );

     	   form_set_error( 'Error, verifica el URL de lista de reproduccion de Youtube [ '. $url_lista .' ] ' );
		   drupal_goto ( "admin/config/excelsior/tv-config/add" ); 	

        } // if de valida url de la lista de youtube

 
    } //excelsior_tv_administer_form_validate


function excelsior_tv_administer_form_submit( $form, &$form_state ){

	  $name_lista = $form_state[ "values" ][ "name" ];
	   $url_lista = $form_state [ "values" ][ "lista" ];
	 $num_mostrar = $form_state[ "values" ][ "num_mostrar" ];
	     $estatus = $form_state [ "values" ][ "estatus" ];
	          $id = $form_state[ "values" ][ "identificador" ];
	        $peso = $form_state [ "values" ] [ "peso" ];
	       $placa = $form_state [ "values" ] [ "placa" ];

           $Class = new configuracion_youtube ( CONFIG_JSON_NAME_TV, CONFIG_JSON_RUTA_TV, "" );
           $Class -> SetCreateData( ); // crea el Test cuando es primero

            $Resp = $Class-> setSaveNewData ( $id, $name_lista, $url_lista, $num_mostrar, $estatus, $peso, $placa );
          
        if ( strlen ( $Resp ) > 4 ){
             $HTML .= $Resp;
           }
       
        if ( strlen ( $HTML ) == 0 ){                    
		    /** salvando en esquema */
			if ($estatus == "activar") {
			    $lists[] = array(
					"nombre" => $name_lista,
					"url_lista" => $url_lista,
				);
			    excelsior_tv_update_gdata($lists);
			}    
		    /** salvando en esquema */
		    excelsior_tv_feed();
		    excelsior_play_list();
             drupal_set_message ( ' Se guardo correctamente la nueva lista para Excélsior - TV ', 'status' );   
           }else{
             drupal_set_message ( $HTML, "error" );  
            }             

       drupal_goto ( "admin/config/excelsior/tv-config/list" ); 
    }//excelsior_tv_administer_form_submit     

function get_validate_url_lista_reproduce ( $url_lista, $max = 50 ){

	     $class = new configuracion_youtube ( CONFIG_JSON_NAME_TV, CONFIG_JSON_RUTA_TV, "" );

	     $band = false;
	       
	    if ( array_key_exists( "error", json_decode( $class -> validar_url_youtube ( $url_lista, $max ), TRUE ) ) ){
	         $band = true;
	      }

	    return $band; 
    } //get_validate_url_lista_reproduce


 /* 
  *
  * Edicion de lista de reproduccion de Excélsior TV 
  *
  */

 function excelsior_administer_edit_lista ( $form, &$form_state ){

      $id = isset ( $_REQUEST[ "id" ] ) ? trim( $_REQUEST[ "id" ] ) : "";

      $Class = new configuracion_youtube ( CONFIG_JSON_NAME_TV, CONFIG_JSON_RUTA_TV, "" );

      $data = $Class-> search_id ( $id );

      if ( count ( $data ) > 0 ){

		$mensaje = '';
			 
			$val_error = variable_get ( "error_procces_lista_reproduccion_tv", "" );
			$name_error = variable_get ( "error_procces_lista_reproduccion_tv_name", "" );
			$lista_error = variable_get ( "error_procces_lista_reproduccion_tv_lista", "" );
			
		  if ( strlen ( $val_error ) > 0 ){    	  
		   	    $mensaje = '<div class="messages error"> <h2 class="element-invisible">Mensaje de error</h2> Error, al guardar nueva lista de reproducción, verifica el URL de la lista. </div>';
				variable_set ( "error_procces_lista_reproduccion_tv", null );	
				variable_set ( "error_procces_lista_reproduccion_tv_name", null );
				variable_set ( "error_procces_lista_reproduccion_tv_lista", null );
		    }	

		 
		  $form[ 'form_youtube_tv' ] = array(
		                                    '#type' => 'fieldset', 
		                                    '#title' => t( "" ), 
		                                    '#weight' => 350, 
		                                    '#collapsible' => false, 
		                                    '#collapsed' => false,
		                               );

		       $form[ "form_youtube_tv" ][ 'script_html_msg_error_super_ocho' ] = array(
										                                           '#type' => 'markup',                                     
										                                           '#prefix' => "<p>" . $mensaje,
										                                           '#suffix' => '</p>'           
		                                                                          );   


				$form [ 'form_youtube_tv' ][ 'name' ] = array(
				                                            '#type' => 'textfield',
				                                            '#title' => t( 'Nombre de la lista:' ),
				                                            '#default_value' => ( empty ( $name_error ) ) ? $data[ "nombre" ] : $name_error,
				                                            '#maxlength' => 50,
				                                            '#size' => 50,
				                                            '#description' => t( 'Introduzca el nombre de la lista.' ),
				                                            '#id' => 'tv_name_lista',
				                                            '#required' => true
				                                    );

				$form [ 'form_youtube_tv' ][ 'lista' ] = array(
				                                            '#type' => 'textfield',
				                                            '#title' => t( 'URL de la Lista youtube:' ),
				                                            '#default_value' =>  ( empty ( $lista_error ) ) ? $data[ "url_lista" ] : $lista_error,
				                                            '#maxlength' => 150,
				                                            '#size' => 150,
				                                            '#description' => t( 'Introduzca el URL de la lista. P/E: http://www.youtube.com/playlist?list=PL206F54543088F3FD&feature=plcp' ),
				                                            '#id' => 'tv_url_lista',
				                                            '#required' => true
				                                    ); 

				$form [ 'form_youtube_tv' ][ 'num_mostrar' ] = array(
				                                            '#type' => 'textfield',
				                                            '#title' => t( 'No. de videos a mostrar:' ),
				                                            '#default_value' =>  $data[ "NoListando" ],
				                                            '#maxlength' => 3,
				                                            '#size' => 3,
				                                            '#description' => t( 'Introduzca el Número de videos a mostrar en lista.' ),
				                                            '#id' => 'tv_num_mostrar',
				                                            '#required' => true
				                                       );

				$form [ 'form_youtube_tv' ][ 'estatus' ] = array(
				                                            '#type' => 'select',
				                                            '#title' => t( 'Estatus de la lista:' ),
				                                            '#default_value' => $data[ "estado" ],
				                                            '#options' => array(
				                                                             'activar' => t( 'Activar' ), 
				                                                             'desactivar' => t( 'Desactivar' ),                                                                 
				                                                           ),                
				                                            '#description' => t( 'Seleccionar el estatus de la lista.' ),
				                                            '#id' => 'tv_estatus',                                                        
				                                       );  

				$form [ 'form_youtube_tv' ][ 'peso' ] = array(
				                                            '#type' => 'select',
				                                            '#title' => t( 'Peso de la lista:' ),
				                                            '#default_value' => $data[ "peso" ],
				                                            '#options' => array(
				                                                             '_none' => t( '- Ninguno -' ), 
				                                                             '0' => t( '0' ),                                                                 
				                                                             '1' => t( '1' ),  
				                                                             '2' => t( '2' ),  
				                                                             '3' => t( '3' ),  
				                                                             '4' => t( '4' ),  
				                                                             '5' => t( '5' ),  
				                                                             '6' => t( '6' ),  
				                                                             '7' => t( '7' ),  
				                                                             '8' => t( '8' ),  
				                                                             '9' => t( '9' ),  
				                                                             '10' => t( '10' ),  
				                                                             '11' => t( '11' ),  
				                                                             '12' => t( '12' ),  
				                                                             '13' => t( '13' ),  
				                                                             '14' => t( '14' ),  
				                                                             '15' => t( '15' ),  
				                                                             '16' => t( '16' ),  
				                                                             '17' => t( '17' ),
				                                                             '18' => t( '18' ),  
				                                                             '19' => t( '19' ),  
				                                                             '20' => t( '20' ),  
				                                                             '21' => t( '21' ),  		                                                             
				                                                             '22' => t( '22' ),  
				                                                             '23' => t( '23' ),  
				                                                             '24' => t( '24' ),  
				                                                             '25' => t( '25' ),  		                                                             
				                                                             '26' => t( '26' ),  
				                                                             '27' => t( '27' ),  
				                                                             '28' => t( '28' ),  
				                                                             '29' => t( '29' ),  		                                                             
				                                                             '30' => t( '30' ),  
				                                                             '31' => t( '31' ),  
				                                                             '32' => t( '32' ),  
				                                                             '33' => t( '33' ),  		                                                             
				                                                             '34' => t( '34' ),  
				                                                             '35' => t( '35' ),  
				                                                             '36' => t( '36' ),  
				                                                             '37' => t( '37' ),  
				                                                             '38' => t( '38' ),  
				                                                             '39' => t( '39' ),  
				                                                             '40' => t( '40' ),  
		                                                             
				                                                           ),                
				                                            '#description' => t( 'Seleccionar el peso de la lista.' ),
				                                            '#id' => 'tv_peso',                                                        
				                                       );

				$form [ 'form_youtube_tv' ][ 'placa' ] = array(
				                                            '#type' => 'select',
				                                            '#title' => t( 'Seleccionar placar para la lista:' ),
				                                            '#default_value' => $data[ "placa" ],
				                                            '#options' => array(
			                                                                  '_none' => t( '_none' ), 	                                                                                            
			                                                               'nacional' => t( 'Nacional'),
	                                                                      'comunidad' => t( 'Comunidad' ),
	                                                                         'global' => t( 'Global' ),		
	                                                                        'funcion' => t( 'Función' ),		
	                                                                     'adrenalina' => t( 'Adrenalina' ),
	                                                                         'dinero' => t( 'Dinero' ),
	                                                                    'hackersBits' => t( 'Hackers y Bits' ),                                                         
	                                                                          'salud' => t( 'Salud' )                                                                     
				                                                           ),                
				                                            '#description' => t( 'Seleccionar placar para la lista.' ),
				                                            '#id' => 'tv_placa',                                                        
				                                       );

				$form[ 'form_youtube_tv' ][ 'identificador' ] = array(
				                                            '#type' => 'hidden',
				                                            '#id' => 'tv_identificador_id',
				                                            '#value' => $data[ "id" ]
				                            );                   
		 		 
		    $form[ 'form_youtube_tv_edit_top' ]['submit'] = array( '#type' => 'submit', '#value' => t(' Guardar ') );
		    $form[ 'form_youtube_tv_edit_bottom' ]['bottom'] = array( '#type' => 'submit', '#value' => t(' Guardar ') );
		    $form[ 'form_youtube_tv_edit_bottom' ]['bottom-return'] = array( '#type' => 'button', "#id" => 'lista-return-edit-delete' , '#value' => t('Regresar a la lista') );
		        
		    $form[ '#theme' ] = 'excelsior_tv_administer_form_edit';

		    return ( $form );

        } // if count > 0
      else{
      	 drupal_set_message ( "Lista no encontrada para editar [ <strong>". $id ." </strong> ]", "error" );  
      	 drupal_goto ( "admin/config/excelsior/tv-config/list" );
        }       
   } //excelsior_administer_edit_lista


function excelsior_administer_edit_lista_validate ( $form, &$form_state ){


		$name_lista = $form_state[ "values" ][ "name" ];
		$url_lista = $form_state [ "values" ][ "lista" ];
		   

	    if ( get_validate_url_lista_reproduce ( $url_lista, 10 ) ){

	         variable_set( 'error_procces_lista_reproduccion_tv', md5 ( microtime() ) );
	         variable_set ( "error_procces_lista_reproduccion_tv_name", $name_lista );
		     variable_set ( "error_procces_lista_reproduccion_tv_lista", $url_lista );

	         form_set_error( 'Error, verifica el URL de lista de reproduccion de Youtube [ '. $url_lista .' ] ' );
		     drupal_goto ( "admin/config/excelsior/tv-config/edit?id=" . $form_state [ "values" ][ "identificador'" ] ); 	

	    } // if de valida url de la lista de youtube

    } //excelsior_administer_edit_lista_validate 


function excelsior_administer_edit_lista_submit( $form, &$form_state ){

		  $name_lista = $form_state[ "values" ][ "name" ];
		   $url_lista = $form_state [ "values" ][ "lista" ];
		 $num_mostrar = $form_state[ "values" ][ "num_mostrar" ];
		     $estatus = $form_state [ "values" ][ "estatus" ];
		          $id = $form_state[ "values" ][ "identificador" ];
		        $peso = $form_state [ "values" ] [ "peso" ];
		       $placa = $form_state [ "values" ] [ "placa" ];

	           $Class = new configuracion_youtube ( CONFIG_JSON_NAME_TV, CONFIG_JSON_RUTA_TV, "" );

	            $Resp = $Class-> setSaveData ( $id, $name_lista, $url_lista, $num_mostrar, $estatus, $peso, $placa );
	          
	        if ( strlen ( $Resp ) > 4 ){
	             $HTML .= $Resp;
	           }
	       
	        if ( strlen ( $HTML ) == 0 ){
    		    /** salvando en esquema */
				if ($estatus == "activar") {
				    $lists[] = array(
						"nombre" => $name_lista,
						"url_lista" => $url_lista,
					);

				    excelsior_tv_update_gdata($lists);
				}
				else if($estatus == "desactivar") {
					excelsior_tv_delete_list($name_lista);
					
				}
				excelsior_tv_feed();
				excelsior_play_list();
			    /** salvando en esquema */
	             drupal_set_message ( ' Se guardo correctamente el cambio de la lista [ '. $name_lista .' ] ', 'status' );   
	           }else{
	             drupal_set_message ( $HTML, "error" );  
	            }             
	        
	    drupal_goto ( "admin/config/excelsior/tv-config/list" );

    }//excelsior_administer_edit_lista_submit       


 /* 
  *
  * Delete de lista de reproduccion de Excélsior TV 
  *
  */

 function excelsior_administer_delete_lista ( $form, &$form_state ){

      $id = isset ( $_REQUEST[ "id" ] ) ? trim( $_REQUEST[ "id" ] ) : "";

      $Class = new configuracion_youtube ( CONFIG_JSON_NAME_TV, CONFIG_JSON_RUTA_TV, "" );

      $data = $Class-> search_id ( $id );

      if ( count ( $data ) > 0 ){

		$mensaje = '';
			 
			$val_error = variable_get ( "error_procces_lista_reproduccion_tv", "" );
			$name_error = variable_get ( "error_procces_lista_reproduccion_tv_name", "" );
			$lista_error = variable_get ( "error_procces_lista_reproduccion_tv_lista", "" );
			
		  if ( strlen ( $val_error ) > 0 ){    	  
		   	    $mensaje = '<div class="messages error"> <h2 class="element-invisible">Mensaje de error</h2> Error, al eliminar la lista. </div>';
				variable_set ( "error_procces_lista_reproduccion_tv", null );	
				variable_set ( "error_procces_lista_reproduccion_tv_name", null );
				variable_set ( "error_procces_lista_reproduccion_tv_lista", null );
		    }	

		 
		  $form[ 'form_youtube_tv' ] = array(
		                                    '#type' => 'fieldset', 
		                                    '#title' => t( "" ), 
		                                    '#weight' => 350, 
		                                    '#collapsible' => false, 
		                                    '#collapsed' => false,
		                               );

		       $form[ "form_youtube_tv" ][ 'script_html_msg_error_super_ocho' ] = array(
										                                           '#type' => 'markup',                                     
										                                           '#prefix' => "<p>" . $mensaje,
										                                           '#suffix' => '</p>'           
		                                                                          );   


		       $form[ "form_youtube_tv" ][ 'msg_delete_lista' ] = array(
								                                     '#type' => 'markup',                                     
								                                     '#prefix' => "<p> Se borrara la lista [ <strong>". $data[ "nombre" ] ."</strong> ], si esta seguro da click en 
								                                                       el Botón Eliminar, en caso contrario da click en el Botón Regresar a la lista. </strong>",
								                                     '#suffix' => '</p>'           
                                                                    );

				$form [ 'form_youtube_tv' ][ 'name' ] = array(
				                                            '#type' => 'textfield',
				                                            '#title' => t( 'Nombre de la lista:' ),
				                                            '#default_value' => ( empty ( $name_error ) ) ? $data[ "nombre" ] : $name_error,
				                                            '#maxlength' => 50,
				                                            '#size' => 50,
				                                            '#description' => t( 'Introduzca el nombre de la lista.' ),
				                                            '#id' => 'tv_name_lista',
				                                            '#required' => true
				                                    );

				$form [ 'form_youtube_tv' ][ 'lista' ] = array(
				                                            '#type' => 'textfield',
				                                            '#title' => t( 'URL de la Lista youtube:' ),
				                                            '#default_value' =>  ( empty ( $lista_error ) ) ? $data[ "url_lista" ] : $lista_error,
				                                            '#maxlength' => 150,
				                                            '#size' => 150,
				                                            '#description' => t( 'Introduzca el URL de la lista. P/E: http://www.youtube.com/playlist?list=PL206F54543088F3FD&feature=plcp' ),
				                                            '#id' => 'tv_url_lista',
				                                            '#required' => true
				                                    ); 

				$form [ 'form_youtube_tv' ][ 'num_mostrar' ] = array(
				                                            '#type' => 'textfield',
				                                            '#title' => t( 'No. de videos a mostrar:' ),
				                                            '#default_value' =>  $data[ "NoListando" ],
				                                            '#maxlength' => 3,
				                                            '#size' => 3,
				                                            '#description' => t( 'Introduzca el Número de videos a mostrar en lista.' ),
				                                            '#id' => 'tv_num_mostrar',
				                                            '#required' => true
				                                       );

				$form [ 'form_youtube_tv' ][ 'estatus' ] = array(
				                                            '#type' => 'select',
				                                            '#title' => t( 'Estatus de la lista:' ),
				                                            '#default_value' => $data[ "estado" ],
				                                            '#options' => array(
				                                                             'activar' => t( 'Activar' ), 
				                                                             'desactivar' => t( 'Desactivar' ),                                                                 
				                                                           ),                
				                                            '#description' => t( 'Seleccionar el estatus de la lista.' ),
				                                            '#id' => 'tv_estatus',                                                        
				                                       ); 

				$form [ 'form_youtube_tv' ][ 'peso' ] = array(
				                                            '#type' => 'select',
				                                            '#title' => t( 'Peso de la lista:' ),
				                                            '#default_value' => $data[ "peso" ],
				                                            '#options' => array(
				                                                             '_none' => t( '- Ninguno -' ), 
				                                                             '0' => t( '0' ),                                                                 
				                                                             '1' => t( '1' ),  
				                                                             '2' => t( '2' ),  
				                                                             '3' => t( '3' ),  
				                                                             '4' => t( '4' ),  
				                                                             '5' => t( '5' ),  
				                                                             '6' => t( '6' ),  
				                                                             '7' => t( '7' ),  
				                                                             '8' => t( '8' ),  
				                                                             '9' => t( '9' ),  
				                                                             '10' => t( '10' ),  
				                                                             '11' => t( '11' ),  
				                                                             '12' => t( '12' ),  
				                                                             '13' => t( '13' ),  
				                                                             '14' => t( '14' ),  
				                                                             '15' => t( '15' ),  
				                                                             '16' => t( '16' ),  
				                                                             '17' => t( '17' ),
				                                                             '18' => t( '18' ),  
				                                                             '19' => t( '19' ),  
				                                                             '20' => t( '20' ),  
				                                                             '21' => t( '21' ),  		                                                             
				                                                             '22' => t( '22' ),  
				                                                             '23' => t( '23' ),  
				                                                             '24' => t( '24' ),  
				                                                             '25' => t( '25' ),  		                                                             
				                                                             '26' => t( '26' ),  
				                                                             '27' => t( '27' ),  
				                                                             '28' => t( '28' ),  
				                                                             '29' => t( '29' ),  		                                                             
				                                                             '30' => t( '30' ),  
				                                                             '31' => t( '31' ),  
				                                                             '32' => t( '32' ),  
				                                                             '33' => t( '33' ),  		                                                             
				                                                             '34' => t( '34' ),  
				                                                             '35' => t( '35' ),  
				                                                             '36' => t( '36' ),  
				                                                             '37' => t( '37' ),  
				                                                             '38' => t( '38' ),  
				                                                             '39' => t( '39' ),  
				                                                             '40' => t( '40' ),  
		                                                             
				                                                           ),                
				                                            '#description' => t( 'Seleccionar el peso de la lista.' ),
				                                            '#id' => 'tv_peso',                                                        
				                                       );

				$form [ 'form_youtube_tv' ][ 'placa' ] = array(
				                                            '#type' => 'select',
				                                            '#title' => t( 'Seleccionar placar para la lista:' ),
				                                            '#default_value' => $data[ "placa" ],
				                                            '#options' => array(
			                                                                  '_none' => t( '_none' ), 	                                                                                            
			                                                               'nacional' => t( 'Nacional'),
	                                                                      'comunidad' => t( 'Comunidad' ),
	                                                                         'global' => t( 'Global' ),		
	                                                                        'funcion' => t( 'Función' ),		
	                                                                     'adrenalina' => t( 'Adrenalina' ),
	                                                                         'dinero' => t( 'Dinero' ),
	                                                                    'hackersBits' => t( 'Hackers y Bits' ),                                                         
	                                                                          'salud' => t( 'Salud' )                                                                     
				                                                           ),                
				                                            '#description' => t( 'Seleccionar placar para la lista.' ),
				                                            '#id' => 'tv_placa',                                                        
				                                       );

				$form[ 'form_youtube_tv' ][ 'identificador' ] = array(
				                                            '#type' => 'hidden',
				                                            '#id' => 'tv_identificador_id',
				                                            '#value' => $data[ "id" ]
				                            );                   
		 		 
		    $form[ 'form_youtube_tv_delete_top' ]['submit'] = array( '#type' => 'submit', '#value' => t(' Eliminar ') );
		    $form[ 'form_youtube_tv_delete_bottom' ]['bottom'] = array( '#type' => 'submit', '#value' => t(' Eliminar ') );
		    $form[ 'form_youtube_tv_delete_bottom' ]['bottom-return'] = array( '#type' => 'button', "#id" => 'lista-return-edit-delete' , '#value' => t('Regresar a la lista') );
		        
		    $form[ '#theme' ] = 'excelsior_tv_administer_form_delete';

		    return ( $form );

        } // if count > 0
      else{
      	 drupal_set_message ( "Lista no encontrada para eliminar [ <strong>". $id ." </strong> ]", "error" );  
      	 drupal_goto ( "admin/config/excelsior/tv-config/list" );
        }       

    } //excelsior_administer_delete_lista


function excelsior_administer_delete_lista_validate ( $form, &$form_state ){


		$name_lista = $form_state[ "values" ][ "name" ];
		$url_lista = $form_state [ "values" ][ "lista" ];
		   

	    if ( get_validate_url_lista_reproduce ( $url_lista, 10 ) ){

	         variable_set( 'error_procces_lista_reproduccion_tv', md5 ( microtime() ) );
	         variable_set ( "error_procces_lista_reproduccion_tv_name", $name_lista );
		     variable_set ( "error_procces_lista_reproduccion_tv_lista", $url_lista );

	         form_set_error( 'Error, verifica el URL de lista de reproduccion de Youtube [ '. $url_lista .' ] ' );
		     drupal_goto ( "admin/config/excelsior/tv-config/edit?id=" . $form_state [ "values" ][ "identificador'" ] ); 	

	    } // if de valida url de la lista de youtube
 	
    } //excelsior_administer_edit_lista_validate 


function excelsior_administer_delete_lista_submit( $form, &$form_state ){

		  $name_lista = $form_state[ "values" ][ "name" ];
		   $url_lista = $form_state [ "values" ][ "lista" ];
		 $num_mostrar = $form_state[ "values" ][ "num_mostrar" ];
		     $estatus = $form_state [ "values" ][ "estatus" ];
		          $id = $form_state[ "values" ][ "identificador" ];

	           $Class = new configuracion_youtube ( CONFIG_JSON_NAME_TV, CONFIG_JSON_RUTA_TV, "" );

	            $Resp = $Class-> deleteListaData ( $id, $name_lista, $url_lista, $num_mostrar, $estatus );
	            $HTML = "";  

	        if ( $Resp == false ){
	             $HTML .= "Error, al eliminar la lista [ ". $name_lista ." ]";
	           }
	       
	        if ( strlen ( $HTML ) == 0 ){
	        	excelsior_tv_delete_list($name_lista);
	        	excelsior_tv_feed();
	        	excelsior_play_list();
	             drupal_set_message ( ' Se elimino correctamente la lista [ '. $name_lista .' ] ', 'status' );   
	           }else{
	             drupal_set_message ( $HTML, "error" );  
	            }             
	        
	    curl_clear_cache_varnish_varnishadm ( "/tv" );
        curl_clear_cache_varnish_x_refresh ( "/tv" );   
	    drupal_goto ( "admin/config/excelsior/tv-config/list" );

    }//excelsior_administer_edit_lista_submit        