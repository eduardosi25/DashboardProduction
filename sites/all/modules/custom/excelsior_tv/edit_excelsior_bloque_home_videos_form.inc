<?php
function edit_excelsior_bloque_home_videos ( $form, &$form_state ){


      $form = array (); 
      $data = array ();
      $file = CONFIG_JSON_RUTA_TV . "video-galeria-home.json";
      
      if ( file_exists( $file ) ){
           $data = json_decode( file_get_contents( $file ), TRUE );
        }

	     $form [ "top-block-videos" ][ 'submit' ] = array(
			                                         '#type' => 'submit',
			                                         '#value' => t( 'Guardar' ),
			                                         "#attributes" =>  array( 'class' => array( 'btn-save-preview-generate-template' ), 'id' => array( 'btn-Save-submit-top-embed' )  )  
	                                               );

	    $form [ "top-block-videos" ][ 'Editar' ] = array(
			                                        '#type' => 'button',
			                                        '#value' => t( 'Editar'),
			                                        "#attributes" =>  array( 'class' => array( 'btn-save-preview-generate-template' ), 'id' => array( 'btn-edit-botton-top-embed' )  )  
	                                      );  

	    $form [ "top-block-videos" ][ 'Cancel' ] = array(
			                                        '#type' => 'button',
			                                        '#value' => t( 'Cancelar' ),
			                                        "#attributes" =>  array( 'class' => array( 'btn-save-preview-generate-template' ), 'id' => array( 'btn-cancel-botton-top-embed' )  )  
	                                      ); 


	   $form[ "block-videos-home_1" ] = array(
	                                       '#type' => 'fieldset', 
	                                       '#title' => t( "Video - 1" ), 
	                                       '#weight' => 325, 
	                                       '#collapsible' => false, 
	                                       '#collapsed' => true,
	                                      );

       
        $change = ( array_key_exists( "change" , $data ) ) ? date ( "Y-m-d H:i:s", $data[ "change" ] ) : "none";

		$form[ "block-videos-home_change" ][ 'change_time' ] = array(
					                                                '#type' => 'markup',                                     
					                                                '#prefix' => '<div class = "sub-title-change-video-home" > Última modificación: <strong>' . $change . "</strong>",
					                                                '#suffix' => '</div>'           
	                                                             );

     // Videos

	   $lista = range( 1,4 );

	   foreach ( $lista as $key => $value ){

	   		   $form[ "block-videos-home_" . $value ] = array(
				                                       '#type' => 'fieldset', 
				                                       '#title' => t( "Video - " . $value ), 
				                                       '#weight' => 325, 
				                                       '#collapsible' => false, 
				                                       '#collapsed' => true,
	                                                 );

				      $form [ "block-videos-home_" . $value ][ "title_video_home_" . $value ] = array (
							                                                                 "#type" => "textfield",
							                                                                 "#id"=> "title_video_home_" . $value ,
							                                                                 "#title" => t( " Titulo :" ),
							                                                                 "#size" => 120,
							                                                                 "#maxlength" => 255,
							                                                                 "#default_value" => ( array_key_exists( "title" , $data[ "data" ][ $key ]  ) ) ? $data[ "data" ][ $key ][ "title" ] : "" ,
							                                                                 "#description" => t( "Escribe el titulo del video."  ),  
							                                                                 "#attributes" =>  array( 'class' => array( 'transmision-textarea-embed-disabled' ) ),
							                                                                 '#required' => true
				                                                                           ); 

				       $form [ "block-videos-home_" . $value ][ "url_video_home_" . $value ] = array (
							                                                                 "#type" => "textfield",
							                                                                 "#id"=> "url_video_home_" . $value,
							                                                                 "#title" => t( "Url :" ),
							                                                                 "#size" => 120,
							                                                                 "#maxlength" => 255,
							                                                                 "#default_value" => ( array_key_exists( "url" , $data[ "data" ][ $key ]  ) ) ? $data[ "data" ][ $key ][ "uri" ] : "" ,
							                                                                 "#description" => t( "Escribe el URL del Video, recuerda debe de ser de Youtube."  ),  
							                                                                 "#attributes" =>  array( 'class' => array( 'transmision-textarea-embed-disabled' ) ),
							                                                                 '#required' => true
				                                                                            );                                                                  
                     
                           $img = ( array_key_exists( "images" , $data[ "data" ][ $key ]  ) ) ? $data[ "data" ][ $key ][ "images" ][ "thumb" ] : "";
                        $images = ( $img != "" ) ? '<a href = "'. $data[ "data" ][ $key ][ "url" ] .'" target = "_black" > <img src = "'. $img .'" /> </a>' : '';

						$form[ "block-videos-home_" . $value ][ 'image_video_home_' . $value ] = array(
												                                                '#type' => 'markup',                                     
												                                                '#prefix' => '<div class = "images-thumb-video-home" >' . $images ,
												                                                '#suffix' => '</div>'           
						                                                                      );

		   }// foreach
	                                                    
      // end Videos

	  $form [ "bottom-block-videos" ][ 'submit' ] = array(
			                                         '#type' => 'submit',
			                                         '#value' => t( 'Guardar' ),
			                                         "#attributes" =>  array( 'class' => array( 'btn-save-preview-generate-template' ), 'id' => array( 'btn-Save-submit-top-embed' )  )  
	                                               );

	  $form [ "bottom-block-videos" ][ 'Editar' ] = array(
			                                        '#type' => 'button',
			                                        '#value' => t( 'Editar'),
			                                        "#attributes" =>  array( 'class' => array( 'btn-save-preview-generate-template' ), 'id' => array( 'btn-edit-botton-top-embed' )  )  
	                                      );  

	  $form [ "bottom-block-videos" ][ 'Cancel' ] = array(
			                                        '#type' => 'button',
			                                        '#value' => t( 'Cancelar' ),
			                                        "#attributes" =>  array( 'class' => array( 'btn-save-preview-generate-template' ), 'id' => array( 'btn-cancel-botton-top-embed' )  )  
	                                      );	   

        $form[ '#theme' ] = 'edit_excelsior_bloque_home_videos';

       return $form; 
     }


function edit_excelsior_bloque_home_videos_validate ( $form, &$form_state ){
       
         $lista = range( 1,4 );

          foreach ( $lista as $key => $value ){

                $title = $form_state[ 'values' ][ 'title_video_home_' . $value ];
                  $url = $form_state[ 'values' ][ 'url_video_home_' . $value ];
                 
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

  function edit_excelsior_bloque_home_videos_submit( $form, &$form_state ){

            $lista = range( 1,4 );
            $content = array ();
            $data = array ();

            $file = CONFIG_JSON_RUTA_TV . "video-galeria-home.json";

	          foreach ( $lista as $key => $value ){

	                $embed = get_id_youtube_embed ( $form_state[ 'values' ][ 'url_video_home_' . $value ] );

	                 $rand = rand( 1,4 );
	             $name_img = ( $rand == 4 ) ? "default.jpg" : $rand . ".jpg"; 

	                $content [] = array(
	                                  "title" => $form_state[ 'values' ][ 'title_video_home_' . $value ],
	                                  "vid" => $embed[ 1 ],
	                                  "images" => array (
	                                  	                "thumb" => 'http://img.youtube.com/vi/'. $embed[ 1 ] .'/'. $name_img,  
	                                                    "medium" => 'http://img.youtube.com/vi/'. $embed[ 1 ] .'/hqdefault.jpg',
	                                                    "mqdefault" => 'http://i1.ytimg.com/vi/'. $embed[ 1 ] .'/mqdefault.jpg'
	                                                ),     
	                                  "uri" => $form_state[ 'values' ][ 'url_video_home_' . $value ],
	                                  "url" => "http://www.youtube.com/watch?v=" . $embed[ 1 ]	                                  
	               	                );
	              }// foreach
	         
	           $data[ "data" ] = $content;
	         $data[ "change" ] = time ();

       file_put_contents( $file, json_encode( $data ) );
       
       drupal_set_message ( ' Se guardo correctamente la VideoGalería Bloque Home. ', 'status' ); 
       unset ( $file, $lista, $content, $data, $rand, $name_img, $embed );
     }//edit_excelsior_bloque_home_videos_submit    

 function get_id_youtube_embed ( $embed ){
	 	
        //$pattern = '{([^"]+)(youtube.com/v/|youtube.com/embed/|youtube-nocookie.com/v/|youtube-nocookie.com/embed/|youtu.be/)([^"\?]+)}';
 	      $pattern = "/([^=.:\/\?\&]{10,12})(&feature=player_embedded)*$/";
         $matchs = array();
           $text = preg_match( $pattern, $embed, $matchs );		
		
		  return $matchs;
      }     