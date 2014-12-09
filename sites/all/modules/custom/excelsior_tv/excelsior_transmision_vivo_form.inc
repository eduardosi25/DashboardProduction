<?php
  /* ------------------------------------------------------------------------------ */
  /* --------------------  Para la transmision en Vivo ---------------------------- */

 function edit_excelsior_transmision_vivo ( $form, &$form_state ){

     $form = array ();
     
      $data = array ();

      $file = CONFIG_JSON_RUTA_TV . "transmision_online.json";
      
      if ( file_exists( $file ) ){
           $data = json_decode( file_get_contents( $file ), TRUE );
        }
     
     $form [ "top-embed" ][ 'submit' ] = array(
                                         '#type' => 'submit',
                                         '#value' => t( 'Guardar' ),
                                         "#attributes" =>  array( 'class' => array( 'btn-save-preview-generate-template' ), 'id' => array( 'btn-Save-submit-top-embed' )  )  
                                    );

    $form [ "top-embed" ][ 'Editar' ] = array(
                                        '#type' => 'button',
                                        '#value' => t( 'Editar'),
                                        "#attributes" =>  array( 'class' => array( 'btn-save-preview-generate-template' ), 'id' => array( 'btn-edit-botton-top-embed' )  )  
                                      );  

    $form [ "top-embed" ][ 'Cancel' ] = array(
                                        '#type' => 'button',
                                        '#value' => t( 'Cancelar' ),
                                        "#attributes" =>  array( 'class' => array( 'btn-save-preview-generate-template' ), 'id' => array( 'btn-cancel-botton-top-embed' )  )  
                                      ); 


   $form[ "transmision_online" ] = array(
                                       '#type' => 'fieldset', 
                                       '#title' => t( "Transmisión en Vivo Canal" ), 
                                       '#weight' => 980, 
                                       '#collapsible' => false, 
                                       '#collapsed' => false,
                                      );



    $form [ "transmision_online" ][ "transmision_textfield_title" ] = array (
                                                                       "#type" => "textfield",
                                                                       "#id"=> "id-textfield-title",
                                                                       "#title" => t( " Titulo :" ),
                                                                       "#size" => 115,
                                                                       "#maxlength" => 255,
                                                                       "#default_value" => ( array_key_exists( "title" , $data[ "canal" ]  ) ) ? $data[ "canal" ][ "title" ] : "" ,
                                                                       "#description" => t( "Escribe el titulo de la transmisión del canal."  ),  
                                                                       "#attributes" =>  array( 'class' => array( 'transmision-textarea-embed-disabled' ) ),
                                                                       //'#required' => true
                                                                      );                      

   $embed_script =  ( array_key_exists( "script" , $data[ "canal" ]  ) ) ? $data[ "canal" ][ "script" ] : "";

    $embed_canal = ( strlen( $embed_script ) > 0 ) ? $embed_script : "";

    $embed_home_portada = ( array_key_exists( "embed" , $data[ "canal" ]  ) ) ? $data[ "canal" ][ "embed" ] : "";

    preg_match( "/player.ooyala.com/", $embed_canal, $output_array );
     
     if ( count ( $output_array ) == 0 ){
          $embed_canal = ( array_key_exists( "embed" , $data[ "canal" ]  ) ) ? $data[ "canal" ][ "embed" ] : "";          
      }else{
         $embed_home_portada = ( array_key_exists( "portada" , $data[ "canal" ]  ) ) ? $data[ "canal" ][ "portada" ] : "";     
        } 
  

  $Description = '<p> Medidas son : <strong> width = "980"   height = "670" </strong> </p>';
 $Description .= 'Escribe el Embed de la <strong> Transmisión en Auto-Play </strong>';
 $Description .= 'Para los siguientes casos : '; 
 $Description .= '<p> Youtube : <strong style = "color:#124D7A;""> http://www.youtube.com/embed/UlI0oD3BTTU</strong>';
 $Description .= '<strong style = "color:#880000;">?autoplay=1</strong> </p>';
 $Description .= '<p> Nota : Añade <strong style = "color:#880000;">?autoplay=1</strong> siempre y cuándo sea de <strong>Youtube</strong>. P/E: </p>';
 $Description .= '<textarea class="transmision-textarea-embed-disabled form-textarea required" id="transmision-embed-pe" name="transmision-embed-pe" cols="60" rows="3" disabled="">';
 $Description .= '<iframe type = "text/html" width = "980" height = "970" src="http://www.youtube.com/embed/UlI0oD3BTTU?autoplay=1&rel=0" frameborder="0" allowfullscreen></iframe>';
 $Description .= '</textarea>';
 
 $Description .= '<p><hr></p>';
 $Description .= '<p style = "font-size:16px;" > <strong style = "color:000;" > Copiar Embed </strong> para la portada <strong style = "font-size:16px" > Home del Excélsior </strong> : </p>';
 $Description .= '<textarea class="copy-embed-portada-home form-textarea required" id="transmision-embed-pe" name="transmision-embed-pe" cols="60" rows="3" disabled="">';
 $Description .= $embed_home_portada;
 $Description .= '</textarea>';
 
     $form[ "transmision_online" ][ "transmision_embed" ] = array (
                                                              "#type" => "textarea",
                                                              "#id" => 'id-transmision-embed',
                                                              "#title" => t( "Embed canal: " ),
                                                              "#cols" => 60,
                                                              "#resizable"=> false, 
                                                              "#rows" => 5,
                                                              "#default_value" => $embed_canal,
                                                              "#description" => t( $Description ), 
                                                              "#attributes" =>  array( 'class' => array( 'transmision-textarea-embed-disabled' ) ),
                                                              '#required' => true
                                                              );


   $form[ "transmision_online_home" ] = array(
                                       '#type' => 'fieldset', 
                                       '#title' => t( "Transmisión en Bloque del Home | VideoGalería" ), 
                                       '#weight' => 980, 
                                       '#collapsible' => false, 
                                       '#collapsed' => false,
                                      );



    $form [ "transmision_online_home" ][ "transmision_textfield_title_home" ] = array (
                                                                                 "#type" => "textfield",
                                                                                 "#id"=> "id-textfield-title-home",
                                                                                 "#title" => t( " Titulo :" ),
                                                                                 "#size" => 115,
                                                                                 "#maxlength" => 255,
                                                                                 "#default_value" => ( array_key_exists( "title" , $data[ "home" ]  ) ) ? $data[ "home" ][ "title" ] : "" ,
                                                                                 "#description" => t( "Escribe el titulo de la transmisión de Tv bloque home."  ),  
                                                                                 "#attributes" =>  array( 'class' => array( 'transmision-textarea-embed-disabled' ) ),
                                                                                 //'#required' => true
                                                                                );   

   $embed_script =  ( array_key_exists( "script" , $data[ "home" ]  ) ) ? $data[ "home" ][ "script" ] : "";

    $embed_canal = ( strlen( $embed_script ) > 0 ) ? $embed_script : "";

    preg_match( "/player.ooyala.com/", $embed_canal, $output_array );
     
     if ( count ( $output_array ) == 0 ){
          $embed_canal = ( array_key_exists( "embed" , $data[ "home" ]  ) ) ? $data[ "home" ][ "embed" ] : "";     
      }                                                                                                                        

  $Description = '<p>Medidas son : <strong> width = "650" height = "450" </strong></p>';
 $Description .= 'Escribe el Embed de la <strong> Transmisión en Pause </strong>';
 $Description .= 'Para los siguientes casos : '; 
 $Description .= '<p> Youtube : <strong style = "color:#124D7A;""> http://www.youtube.com/embed/UlI0oD3BTTU</strong></p>';
 $Description .= '<p> <textarea class="transmision-textarea-embed-disabled form-textarea required" id="transmision-embed-pe" name="transmision-embed-pe" cols="60" rows="3" disabled="">';
 $Description .= '<iframe type = "text/html" width = "650" height = "410" src="http://www.youtube.com/embed/UlI0oD3BTTU?rel=0" frameborder="0" allowfullscreen></iframe>';
 $Description .= '</textarea></p>';
 $Description .= '<p>"Ojo" Aqui no lleva <strong style = "color:#880000;"> autoplay=1 </strong </p>';

     $form[ "transmision_online_home" ][ "transmision_embed_home" ] = array (
                                                                        "#type" => "textarea",
                                                                        "#id" => 'id-transmision-embed-home',
                                                                        "#title" => t( "Embed [ Portada del Home - Excélsior ]: " ),
                                                                        "#cols" => 60,
                                                                        "#resizable"=> false, 
                                                                        "#rows" => 5,
                                                                        "#default_value" =>  $embed_canal,
                                                                        "#description" => t( $Description ), 
                                                                        "#attributes" =>  array( 'class' => array( 'transmision-textarea-embed-disabled' ) ),
                                                                        '#required' => true
                                                                      );

    $form[ "transmision_online_movil" ] = array(
                                           '#type' => 'fieldset', 
                                           '#title' => t( "Transmisión TV para movil con ooyala" ), 
                                           '#weight' => 980, 
                                           '#collapsible' => false, 
                                           '#collapsed' => false,
                                          );

    $Description = "<strong>OO.ready(function() { OO.Player.create('ooyalaplayer', '<strong style = 'color:#E82424;' >Bybmw5ZTqJgLywPM6677ozz9pV1vQIPb</strong>', {'autoplay':true}); })</strong>";  

    $form[ "transmision_online_movil" ][ "key_ooyala" ] =  array (
                                                             "#type" => "textfield",
                                                             "#id"=> "id-key-ooyala",
                                                             "#title" => t( "Key ooyala:" ),
                                                             "#size" => 115,
                                                             "#maxlength" => 255,
                                                             "#default_value" => ( array_key_exists( "key_ooyala" , $data[ "movil" ]  ) ) ? $data[ "movil" ][ "key_ooyala" ] : "" ,
                                                             "#description" => t( "Escribe el Key de la transmision de ooyala. P/E : " . $Description ),  
                                                             "#attributes" =>  array( 'class' => array( 'transmision-textarea-embed-disabled' ) ),
                                                             //'#required' => true
                                                            ); 


    $form [ "bottom-embed" ][ 'submit' ] = array(
                                              '#type' => 'submit',
                                              '#value' => t( 'Guardar'),
                                              "#attributes" =>  array( 'class' => array( 'btn-save-preview-generate-template' ), 'id' => array( 'btn-Save-submit-bottom-embed' ) )                              
                                            );

    $form [ "bottom-embed" ][ 'Editar' ] = array(
                                              '#type' => 'button',
                                              '#value' => t( 'Editar'),
                                              "#attributes" =>  array( 'class' => array( 'btn-save-preview-generate-template' ), 'id' => array( 'btn-edit-submit-bottom-embed' ) )                             
                                            );

    $form [ "bottom-embed" ][ 'Cancel' ] = array(
                                            '#type' => 'button',
                                            '#value' => t( 'Cancelar' ),
                                            "#attributes" =>  array( 'class' => array( 'btn-save-preview-generate-template' ), 'id' => array( 'btn-cancel-submit-bottom-embed' ) )                             
                                          );    

    $form[ '#theme' ] = 'excelsior_transmision_online_embed';

     return $form;
   }//edit_excelsior_transmision_vivo


function edit_excelsior_transmision_vivo_validate ( $form, &$form_state ){
        
        $Name = $form_state[ "values" ][ "transmision_textfield_title" ];
        $Embed = $form_state[ "values" ][ "transmision_embed" ];
       
        $Name_home = $form_state[ "values" ][ "transmision_textfield_title_home" ];
        $Embed_home = $form_state[ "values" ][ "transmision_embed_home" ];

         if ( $Embed === "" ){
              form_set_error( 'Error, verifica por favor el Embed de la Transmisión en Canal. ' );
           }  

         if ( $Embed_home === "" ){
              form_set_error( 'Error, verifica por favor el Embed de la Transmisión en Bloque Home | VideoGalería. ' );
           }             

    }//

function edit_excelsior_transmision_vivo_submit ( $form, &$form_state ){
    
       $file = CONFIG_JSON_RUTA_TV . "transmision_online.json";

       $html_iframe_auto_play = "";
       $html_iframe_pause_play = "";
       $html_iframe_portada_play = "";

       $script_auto_play = "";
       $script_pause_play = "";

        $Name = $form_state[ "values" ][ "transmision_textfield_title" ];
        $Embed = $form_state[ "values" ][ "transmision_embed" ];

        $Name_home = $form_state[ "values" ][ "transmision_textfield_title_home" ];
        $Embed_home = $form_state[ "values" ][ "transmision_embed_home" ];

        $key_ooyala = $form_state[ "values" ][ "key_ooyala" ];


        preg_match( "/player.ooyala.com/", $Embed, $output_array );
         
        /* Se verifica que exista script para ooyala */  

        if ( count ( $output_array ) > 0 ){

             $file_content_auto_play = get_iframe_file_ooyala ( $Embed ); //auto-play 
             $file_content_pause_play = get_iframe_file_ooyala ( $Embed_home ); //pause-play 

            $file_content_portada_play = str_replace( "width:980px", "width:664px", $Embed );
            $file_content_portada_play = str_replace( "height:670px", "height:350px", $file_content_portada_play ); //portada

             $file_content_portada_play = get_iframe_file_ooyala ( $file_content_portada_play, 310 ); // portada


             file_put_contents( CONFIG_JSON_FRAME_EMBED . "auto-play.html" , $file_content_auto_play, LOCK_EX );
             file_put_contents( CONFIG_JSON_FRAME_EMBED . "pause-play.html" , $file_content_pause_play, LOCK_EX );
             file_put_contents( CONFIG_JSON_FRAME_EMBED . "portada-play.html" , $file_content_portada_play, LOCK_EX );

        $html_iframe_auto_play = '<iframe type = "text/html" width = "980" height = "670" src="/media/embed/auto-play.html" frameborder="0" scrolling="no" allowfullscreen></iframe>';
        $html_iframe_pause_play = '<iframe type = "text/html" width = "650" height = "450" src="/media/embed/pause-play.html" frameborder="0" scrolling="no" allowfullscreen></iframe>';
        $html_iframe_portada_play = '<iframe type = "text/html" width = "100%" height = "350" src="/media/embed/portada-play.html?width=100&height=350" frameborder="0" scrolling="no" allowfullscreen></iframe>';

             $script_auto_play = $Embed;
             $script_pause_play = $Embed_home;
            
          }//count


       $data = array ( "canal" => array (
                                       "id" => microtime( time() . microtime() ),
                                    "title" => $Name,
                                    "embed" => (string) ( strlen( $html_iframe_auto_play ) > 0 ) ? $html_iframe_auto_play : $Embed, 
                                   "script" => (string) $script_auto_play,  
                                   "portada" => (string) ( strlen( $html_iframe_portada_play ) > 0 ) ? $html_iframe_portada_play : $Embed,                                
                                    "time"  => time()
                                    ),
                        "home" => array (
                                       "id" => microtime( time() . microtime() ),
                                    "title" => $Name_home,
                                    "embed" => (string) ( strlen( $html_iframe_pause_play ) > 0 ) ? $html_iframe_pause_play : $Embed_home, 
                                   "script" => (string) $script_pause_play,
                                   "portada" => (string) ( strlen( $html_iframe_portada_play ) > 0 ) ? $html_iframe_portada_play : $Embed_home,   
                                    "time"  => time()
                                    ),  

                        "movil" => array (
                                        "id" => microtime( time() . microtime() ),
                                        "key_ooyala" => trim( $key_ooyala )
                                     )

                 );
      
       file_put_contents( $file, json_encode( $data ) );
                   
       drupal_set_message ( ' Se guardo correctamente la transmisión. ', 'status' ); 
       unset ( $file, $Name, $data );
    } //edit_excelsior_transmision_vivo_submit

function get_iframe_file_ooyala( $script, $alto = 410 ){

    $html = '
              <!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
              <html xmlns="http://www.w3.org/1999/xhtml" lang="es" xml:lang="es">

              <head>
              <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
              <title>Transmisión en Vivo</title>
              </head>

              <style type = "text/css" >

              body{
                margin:0px auto;
                padding: 0px;
                background:#292929;
                height: '. $alto .'px;
                }

              </style>

              <script src = "http://code.jquery.com/jquery-2.0.2.min.js" ></script>

              <script type="text/javascript">

               function getQueryParams( qs ) {
                        qs = qs.split("+").join(" ");
                    var params = {}, tokens,
                        re = /[?&]?([^=]+)=([^&]*)/g;

                    while ( tokens = re.exec( qs ) ) {
                            params[ decodeURIComponent( tokens[ 1 ] ) ] = decodeURIComponent( tokens[ 2 ] );
                     }
                   return params;
                 }

              </script>

              <body>
              <!-- embed -->
                  '. $script .'
              <!-- end Embed -->

              <script type="text/javascript">

                   $(document).ready(function() {

                       var _GET = {};
                       var width = "980px";
                       var height = "410px";

                        _GET = getQueryParams( document.location.search );

                           if ( jQuery.isPlainObject ( _GET ) ){

                                  width_get = parseInt( _GET.width );
                                 height_get = parseInt( _GET.height );

                                 height = ( isNaN ( height_get ) ) ? ( height ) : ( height_get + "px" );

                                 if ( ! isNaN ( width_get ) ){
                                        width = ( width_get < 350 ) ? ( width_get + "%" ) : ( width_get + "px" );
                                    }                            
                             }

                          document.getElementById( "ooyalaplayer" ).style.height = height;
                          document.getElementById( "ooyalaplayer" ).style.width = width;

                     });
              </script>

              </body>
              </html>
     ';
     return $html;
   }//get_iframe_file_ooyala