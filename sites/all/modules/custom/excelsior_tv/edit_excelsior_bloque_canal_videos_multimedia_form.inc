<?php
function edit_excelsior_bloque_canal_videos_multimedia ( $form, &$form_state ){


      $form = array (); 
      $data = array ();
      $file = CONFIG_JSON_RUTA_TV . "multimedia-portada.json";
      $conf = variable_get( "excelsior_tv_vars", array());
      
      if ( file_exists( $file ) ){
           $data = json_decode( file_get_contents( $file ), TRUE );
        }

	     $form [ "top-block-videos-canal" ][ 'submit' ] = array(
			                                         '#type' => 'submit',
			                                         '#value' => t( 'Guardar' ),
			                                         "#attributes" =>  array( 'class' => array( 'btn-save-preview-generate-template' ), 'id' => array( 'btn-Save-submit-top-embed' )  )  
	                                               );

	    $form [ "top-block-videos-canal" ][ 'Editar' ] = array(
			                                        '#type' => 'button',
			                                        '#value' => t( 'Editar'),
			                                        "#attributes" =>  array( 'class' => array( 'btn-save-preview-generate-template' ), 'id' => array( 'btn-edit-botton-top-embed' )  )  
	                                      );  

	    $form [ "top-block-videos-canal" ][ 'Cancel' ] = array(
			                                        '#type' => 'button',
			                                        '#value' => t( 'Cancelar' ),
			                                        "#attributes" =>  array( 'class' => array( 'btn-save-preview-generate-template' ), 'id' => array( 'btn-cancel-botton-top-embed' )  )  
	                                      ); 


	   $form[ "block-videos-canal_1" ] = array(
	                                       '#type' => 'fieldset', 
	                                       '#title' => t( "Video - 1" ), 
	                                       '#weight' => 325, 
	                                       '#collapsible' => false, 
	                                       '#collapsed' => true,
	                                      );

       
        $change = ( array_key_exists( "change" , $data ) ) ? date ( "Y-m-d H:i:s", $data[ "change" ] ) : "none";
        $estado = ( array_key_exists( "estado" , $data ) ) ? $data[ "estado" ]  : "0";

		$form[ "block-videos-canal_change" ][ 'change_time' ] = array(
					                                                '#type' => 'markup',                                     
					                                                '#prefix' => '<div class = "sub-title-change-video-home" > Última modificación: <strong>' . $change . "</strong>",
					                                                '#suffix' => '</div>'           
	                                                             );
		$form[ "block-video-canal-bandera" ][ "apagar-encender-bloque-canal" ] = array(
									                                            '#type' => 'select',
									                                            '#title' => t( 'Estado del bloque:' ),
									                                            '#default_value' => $estado,
									                                            '#options' => array(							                                                             
									                                                             '0' => t( 'Ocultar' ),                                                                 
									                                                             '1' => t( 'Visible' ),  
									                                                           ),                
									                                            '#description' => t( 'Selecciona el peso del video.' ),
									                                            '#id' => 'id-apagar-encender',
									                                            "#attributes" =>  array( 'class' => array( 'estado-bloque-canal' ) ),
			                                                                  );

     // Videos
	   $end = isset($conf['count_related'])?$conf['count_related']:14;
	   $lista = range( 1, $end);

	   foreach ( $lista as $key => $value ){

	   		   $form[ "block-videos-canal_" . $value ] = array(
				                                       '#type' => 'fieldset', 
				                                       '#title' => t( "Video - " . $value ), 
				                                       '#weight' => 325, 
				                                       '#collapsible' => false, 
				                                       '#collapsed' => true,
	                                                 );

		      $form [ "block-videos-canal_" . $value ][ "title_video_canal_" . $value ] = array (
					                                                                 "#type" => "textfield",
					                                                                 "#id"=> "title_video_canal_" . $value ,
					                                                                 "#title" => t( " Titulo :" ),
					                                                                 "#size" => 120,
					                                                                 "#maxlength" => 255,
					                                                                 "#default_value" => ( array_key_exists( "title" , $data[ "data" ][ $key ]  ) ) ? $data[ "data" ][ $key ][ "title" ] : "" ,
					                                                                 "#description" => t( "Escribe el titulo del video."  ),  
					                                                                 "#attributes" =>  array( 'class' => array( 'transmision-textarea-embed-disabled' ) ),
					                                                                 '#required' => true
		                                                                           ); 

		       $form [ "block-videos-canal_" . $value ][ "url_video_canal_" . $value ] = array (
					                                                                 "#type" => "textfield",
					                                                                 "#id"=> "url_video_canal_" . $value,
					                                                                 "#title" => t( "Url :" ),
					                                                                 "#size" => 120,
					                                                                 "#maxlength" => 255,
					                                                                 "#default_value" => ( array_key_exists( "url" , $data[ "data" ][ $key ]  ) ) ? $data[ "data" ][ $key ][ "uri" ] : "" ,
					                                                                 "#description" => t( "Escribe el URL del Video, recuerda debe de ser de Youtube."  ),  
					                                                                 "#attributes" =>  array( 'class' => array( 'transmision-textarea-embed-disabled' ) ),
					                                                                 '#required' => true
		                                                                            ); 

			   $form [ "block-videos-canal_" . $value ][ "peso_video_canal_" . $value ] = array(
											                                            '#type' => 'select',
											                                            '#title' => t( 'Peso del video:' ),
											                                            '#default_value' => ( array_key_exists( "peso" , $data[ "data" ][ $key ]  ) ) ? $data[ "data" ][ $key ][ "peso" ] : "",
											                                            '#options' => array(                                             
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
											                                                             '14' => t( '14' ) 


											                                                           ),                
											                                            '#description' => t( 'Selecciona el peso del video.' ),
											                                            '#id' => 'peso_video_canal_' . $value,
											                                            "#attributes" =>  array( 'class' => array( 'transmision-textarea-embed-disabled' ) ),
											                                       );             


                   $img = ( array_key_exists( "images" , $data[ "data" ][ $key ]  ) ) ? $data[ "data" ][ $key ][ "images" ][ "thumb" ] : "";
                $images = ( $img != "" ) ? '<a href = "'. $data[ "data" ][ $key ][ "url" ] .'" target = "_black" > <img src = "'. $img .'" /> </a>' : '';

				$form[ "block-videos-canal_" . $value ][ 'image_video_canal_' . $value ] = array(
										                                                '#type' => 'markup',                                     
										                                                '#prefix' => '<div class = "images-thumb-video-home" >' . $images ,
										                                                '#suffix' => '</div>'           
				                                                                      );

		   }// foreach
	                                                    
      // end Videos

	  $form [ "bottom-block-videos-canal" ][ 'submit' ] = array(
			                                         '#type' => 'submit',
			                                         '#value' => t( 'Guardar' ),
			                                         "#attributes" =>  array( 'class' => array( 'btn-save-preview-generate-template' ), 'id' => array( 'btn-Save-submit-top-embed' )  )  
	                                               );

	  $form [ "bottom-block-videos-canal" ][ 'Editar' ] = array(
			                                        '#type' => 'button',
			                                        '#value' => t( 'Editar'),
			                                        "#attributes" =>  array( 'class' => array( 'btn-save-preview-generate-template' ), 'id' => array( 'btn-edit-botton-top-embed' )  )  
	                                      );  

	  $form [ "bottom-block-videos-canal" ][ 'Cancel' ] = array(
			                                        '#type' => 'button',
			                                        '#value' => t( 'Cancelar' ),
			                                        "#attributes" =>  array( 'class' => array( 'btn-save-preview-generate-template' ), 'id' => array( 'btn-cancel-botton-top-embed' )  )  
	                                      );	   

        $form[ '#theme' ] = 'edit_excelsior_bloque_canal_videos';

       return $form; 
       //print_r('esto es una prueba '.$form);
     }


function edit_excelsior_bloque_canal_videos_tv_validate ( $form, &$form_state ){
		$conf = variable_get( "excelsior_tv_vars", array());
		$end = isset($conf['count_related'])?$conf['count_related']:14;
       
         $lista = range( 1, $end);

          foreach ( $lista as $key => $value ){

                $title = $form_state[ 'values' ][ 'title_video_canal_' . $value ];
                  $url = $form_state[ 'values' ][ 'url_video_canal_' . $value ];
                 
		         if( empty( $title ) ){
			         form_set_error( 'El titulo del video [ ' . $value . ' ], no debe estar vacio.');
			       }

			      $embed = get_id_youtube_embed ( $url );

			     if ( ( count ( $embed ) < 2 ) ){
                       form_set_error( 'El url del video es incorrecto [ ' . $value . ' ], el video debe ser de youtube P/E: <strong> http://www.youtube.com/watch?v=VrpNhl9G4vQ </strong> | <strong> http://youtu.be/whwcxYEU-rA </strong>.');
			        }		                     
            } // foreach

         unset ( $lista, $title, $url, $embed );              
      }


function edit_excelsior_bloque_canal_videos_multimedia_submit( $form, &$form_state ){
	$conf = variable_get( "excelsior_tv_vars", array());
	$end = isset($conf['count_related'])?$conf['count_related']:14;

	$content = array ();
	$data = array ();

	$file = CONFIG_JSON_RUTA_TV . "multimedia-portada.json";

	$lista = range( 1, $end);

	/** Salvando en esquema*/
	$playlist_title = 'Recomendados';
    excelsior_tv_delete_list($playlist_title);
	/** Salvando en esquema*/
	
	foreach ( $lista as $key => $value ){
		$embed = _get_youtubeid( $form_state[ 'values' ][ 'url_video_canal_' . $value ] );
		$url_video = get_url_videos( $form_state[ 'values' ][ 'url_video_canal_' . $value ], $embed );

		$rand = rand( 1,4 );
		$name_img = ( $rand == 4 ) ? "default.jpg" : $rand . ".jpg"; 

		$str_curl = CurlLinkXVideo( $embed );
		$content [] = array(
		                  "title" => $form_state[ 'values' ][ 'title_video_canal_' . $value ],
		                  "vid" => $embed,
		                  "images" => array (
		                  	                "thumb" => 'http://img.youtube.com/vi/'. $embed .'/'. $name_img,  
		                                    "medium"=> 'http://img.youtube.com/vi/'. $embed .'/hqdefault.jpg',
		                                    "mqdefault"=> 'http://i1.ytimg.com/vi/'. $embed .'/mqdefault.jpg'
		                                 ), 
		                  "url_video" => $url_video,
		                  "uri" => $form_state[ 'values' ][ 'url_video_canal_' . $value ],
		                  "url" => "http://www.youtube.com/watch?v=" . $embed,
		                  "peso" => $form_state[ 'values' ][ 'peso_video_canal_' . $value ],
						  "reproduccion" => get_reproducciones_cout( $str_curl ),
		);
		/** Salvando en esquema*/
		$video = excelsior_tv_get_retrieve_gdata($str_curl);
		if ( count($video) > 0) {
			$video['video']['title'] = $form_state[ 'values' ][ 'title_video_canal_' . $value ];
			$video['position'] = $value;
			excelsior_tv_save_gdata($video, $playlist_title);
		}
		/** Salvando en esquema*/
	}// foreach
	         
	$data[ "data" ] = $content;
	$data[ "estado" ] = $form_state[ "values" ][ "apagar-encender-bloque-canal" ];
	$data[ "change" ] = time ();

	file_put_contents( $file, json_encode( $data ) );

	curl_clear_cache_varnish_varnishadm ( "/tv" );
	curl_clear_cache_varnish_x_refresh ( "/tv" );       

	excelsior_tv_feed();
	drupal_set_message ( ' Se guardo correctamente la lista Bloque Canal TV. ', 'status' ); 
	unset ( $file, $lista, $content, $data, $rand, $name_img, $embed );
}//edit_excelsior_bloque_home_videos_submit    

 function get_id_youtube_embed ( $embed ){
	 	
        //$pattern = '{([^"]+)(youtube.com/v/|youtube.com/embed/|youtube-nocookie.com/v/|youtube-nocookie.com/embed/|youtu.be/)([^"\?]+)}';
 	     $pattern = "/([^=.:\/\?\&]{10,12})(&feature=player_embedded)*$/";
        	$matchs = array();
         $text = preg_match( $pattern, $embed, $matchs );		
		
		  return $matchs;
     }

  function get_reproducciones_cout ( $data ){

       $data = json_decode( $data, TRUE );
       $total = 0;

        if ( array_key_exists(  "data",  $data ) ){

           $total = $data[ "data" ][ "viewCount" ];
        }

      return $total; 
    }     