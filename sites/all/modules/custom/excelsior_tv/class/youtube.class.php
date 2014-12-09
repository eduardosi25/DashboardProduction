<?php
/*
@Developer : J. Enrique Montiel P.
Class : Obtiene Videos de Youtube sobre un canal
*/


class configuracion_youtube{
    
  public $ruta = "";
  public $ruta_json = "";
  public $base_url = "";
  public $error = "";
  public $Max = 50;
       
    
  public function __construct( $ruta, $ruta_json, $base_url ){
        
         $this-> ruta = $ruta;
         $this-> ruta_json = $ruta_json;
         $this-> base_url = $base_url;
                  
         //$this-> SetCreateData (); 

      }//Constructor

   public function set_configuracion_youtube ( $ruta, $ruta_json, $base_url ){

         $this-> ruta = $ruta;
         $this-> ruta_json = $ruta_json;
         $this-> base_url = $base_url;                          
     }   
    
   public function SetCreateData( ){
      
            $data = array ();

            if ( $this->getExisteFile( $this-> ruta ) == 'data' ){

                $data = json_decode ( file_get_contents( $this-> ruta  ), TRUE );

                  if ( array_key_exists ( "data", $data ) ) {
                      if ( count ( $data[ "data" ] ) == 0 )  {
                           $this-> getCreateDataJsonYoutube( $this-> ruta ); 
                           $data = json_decode( file_get_contents( $this-> ruta ), true );   
                        } 
                    }//array key exists
               
                    if ( count ( $data ) == 0 )  {
                         $this-> getCreateDataJsonYoutube( $this-> ruta ); 
                         $data = json_decode( file_get_contents( $this-> ruta ), true );   
                      }                

                }//getExisteFile  
            else{
                    $this-> getCreateDataJsonYoutube( $this-> ruta ); 
                    $data = json_decode( file_get_contents( $this-> ruta ), true );  
                }  
 
            return ( $data );               
     }//  SetCreateData      

   public function validar_url_youtube ( $url, $max = 25 ){

        return $this-> CurlLinkExiste ( $this-> getInfoURLParametros ( $url ), $max );

      }   //validar_url_youtube     


  /*
   * @ Regresa el conjunto de datos deñ json 
   *
   */
        
   public function getData(){       
          return ( json_decode( file_get_contents( $this-> ruta ), true ) );       
      }//getData

  /*
   * @ Busca un ID dentro del Json
   */    

   public function search_id ( $id ){

         $data = $this-> getData ();      
         $posi = false;
            $K = 0;

          if ( count ( $data[ "data" ] ) > 0 ){

              foreach ( $data[ "data" ] as $Key ){

                  if ( $Key [ "id" ] == $id ){
                        $posi = $K;
                        break;
                    }
                 $K ++;
               }//foreach
            }//if   

          $result = ( is_numeric( $posi ) ) ? $data[ "data" ][ $posi ] : array();
          
        return $result;

      } // search _ id     
      
   public function setSaveNewData ( $id, $nombre, $UrlLista, $NoListando, $Estatus, $Peso, $Placa ){
       
                 $msg = "";
            $KeyLista = $this-> getInfoURLParametros ( $UrlLista );
                 
            if ( ! is_array( $KeyLista ) ){
                    
                       $data = $this-> CurlLinkExiste ( $KeyLista, $this-> Max );
                     
                       if (  $this-> ValidarCurlYoutube ( $data ) == false ){
                             $msg .= "<div>Error, ID de Youtube Invalido</div>";
                        }                  
              }//is_array
           else{
                 $msg .= "<div>Error, URL invalido.</div>";
              } 

            if (  $this-> validarCadena ( $nombre ) == 0 ){
                  $msg .= "<div>Error, nombre de la lista</div>";
              } 
                  
            if ( ctype_digit( $NoListando ) === false ){
                  $msg .= "<div>Error, en el número de videos a mostrar.</div>";
              }  
                  
            if ( strlen ( $msg ) == 0 ){              
                 return ( $this-> saveDataCamposJsonNew ( $id, $nombre, $KeyLista, $UrlLista, $NoListando, $Estatus, $Peso, $Placa ) );                
              }else{
                    return ( $msg );   
                 } 
              
       }//setSaveNewData   
       
   public function setSaveData( $id, $nombre, $UrlLista, $NoListando, $Estatus, $Peso, $Placa ){
         
                 $msg = "";
            $KeyLista = $this-> getInfoURLParametros ( $UrlLista );
                 
            if ( ! is_array( $KeyLista ) ){
                    
                   $data = $this-> CurlLinkExiste ( $KeyLista, $this-> Max );
                     
                     if (  $this-> ValidarCurlYoutube ( $data ) == false ){
                            $msg .= "<div>Error, ID de Youtube Invalido</div>";
                       }                  
              }//is_array
           else{
                $msg .= "<div>Error, URL invalido.</div>";
              } 
                  
            if (  $this-> validarCadena ( $nombre ) == 0 ){
                      $msg .= "<div>Error, nombre de la lista</div>";
              } 
                  
            if ( ctype_digit( $NoListando ) === false ){
                     $msg .= "<div>Error, en el número de videos a mostrar.</div>";
              }                    

            if ( strlen ( $msg ) == 0 ){              
                   return ( $this-> saveDataCamposJson ( $id, $nombre, $KeyLista, $UrlLista, $NoListando, $Estatus, $Peso, $Placa ) );                
              }else{
                    return ( $msg );   
                } 
              
      }//setSaveData  
      
   private function saveDataCamposJson ( $id, $nombre, $KeyLista, $UrlLista, $NoListando, $Estatus, $Peso, $Placa ){ //metodo donde se guardan los datos en el json
       
            $Data = $this-> getData();
            $Posi = null;          
               $K = 0;
            
            foreach ( $Data[ "data" ] as $Key ){
              
                   if ( $Key [ "id" ] == $id ){
                        $Posi = $K;
                        break;
                      }
                $K ++;
              }//foreach
       
            if ( ( is_numeric( $Posi ) ) ){
                
                $Data [ "data" ] [ $Posi ] [ "nombre" ] = $nombre;
                $Data [ "data" ] [ $Posi ] [ "url_lista" ] = $UrlLista;
                $Data [ "data" ] [ $Posi ] [ "lista" ] = $KeyLista;
                $Data [ "data" ] [ $Posi ] [ "estado" ] = $Estatus;
                $Data [ "data" ] [ $Posi ] [ "NoListando" ] = $NoListando;
                $Data [ "data" ] [ $Posi ] [ "peso" ] = $Peso;
                $Data [ "data" ] [ $Posi ] [ "placa" ] = $Placa;
                
              if ( is_numeric( $Peso ) ){                                                                     
                    $Data[ "data" ] = $this-> orderMultiDimensionalArray ( $Data[ "data" ], "time", $inverse = TRUE );
                    $Data[ "data" ] = $this-> orderMultiDimensionalArray ( $Data[ "data" ], "peso", $inverse = false );
                }
                
                $this-> getFileWriteJson ( $this-> ruta, $Data );//escribe el json con los nuevos datos
                
                $this->getFileWriteJsonFile( $this-> ruta_json. $Data [ "data" ] [ $Posi ] [ "id" ]."_lista.json", 
                                             $this-> CurlLinkExiste ( $KeyLista, $this-> Max ) ); //crear la lista de los videos
                
                return true;
                
              }else{
                return ( "Error, al guardar los datos en el json" );  
              }                                     
      }//saveDataCamposJson  
      
   private function saveDataCamposJsonNew ( $id, $nombre, $KeyLista, $UrlLista, $NoListando, $Estatus, $Peso, $Placa  ){ // Metodo para guardar nueva galeria
       
           $Data = $this-> getData(); //

           $Type = 0;
           
           if ( count ( $Data[ "data" ] ) > 0 ){
               
               $Ultimo = $Data[ "data" ] [ count ( $Data [ "data" ] ) - 1 ];
                 $Type = $Ultimo[ "type" ] + 1;
                 
                 $complemento =  array (
                                          "id" => $id,
                                         "type"=> $Type,
                                      "nombre" => $nombre,
                                   "url_lista" => $UrlLista,
                                       "lista" => $KeyLista,
                                      "estado" => $Estatus,
                                       "file"  => $id."_lista.json",
                                  "NoListando" => $NoListando,
                                        "peso" => $Peso,
                                      "update" => time(),
                                     "created" => time(),                                        
                                       "placa" => $Placa

                              );//
               
                 //array_unshift( $Data [ "data" ] , $complemento ); // al Inicio
                 array_push ( $Data [ "data" ], $complemento );

                                              
                 if ( is_numeric( $Peso ) ){                                                                     
                      $Data[ "data" ] = $this-> orderMultiDimensionalArray ( $Data[ "data" ], "time", $inverse = TRUE );
                      $Data[ "data" ] = $this-> orderMultiDimensionalArray ( $Data[ "data" ], "peso", $inverse = false );
                    }
                                                            
                 $this-> getFileWriteJson ( $this-> ruta, $Data );
                 
                 $this->getFileWriteJsonFile( $this-> ruta_json. $id."_lista.json" , $this-> CurlLinkExiste ( $KeyLista, $this-> Max ) );
                 
                return true;                                       
             }//if
            else{
               return ( "Error, json no creado" );   
             }           
     }//saveDataCamposJsonNew
     

   public function deleteListaData ( $id, $name_lista, $url_lista, $num_mostrar, $estatus ){

           $data = $this-> getData ();      
           $posi = false;
              $K = 0;
        $borrado = false;

       if ( count ( $data[ "data" ] ) > 0 ){

              foreach ( $data[ "data" ] as $Key ){

                  if ( $Key [ "id" ] == $id ){
                        $posi = $K;
                        break;
                    }
                 $K ++;
               }//foreach
            }//if   

        if ( is_numeric( $posi ) ){  

               if ( file_exists( CONFIG_JSON_RUTA_TV. $data[ "data" ][ $posi ][ "file" ]  ) ){

                    unlink( CONFIG_JSON_RUTA_TV. $data[ "data" ][ $posi ][ "file" ] );     

                    unset ( $data[ "data" ][ $posi ] );

                    $data[ "data" ] = array_merge( array(), $data[ "data" ] );

                    $this-> getFileWriteJson ( $this-> ruta, $data );//escribe el json con los nuevos datos

                    $borrado = true;
                }//file_existe
               else{
                    unset ( $data[ "data" ][ $posi ] );
                    $data[ "data" ] = array_merge( array(), $data[ "data" ] );
                    $this-> getFileWriteJson ( $this-> ruta, $data );//escribe el json con los nuevos datos
                    $borrado = true;
                 }                
          }//is_numeric              
        return $borrado;
      }//deleteListaData

   /* ------------------------------------------------------------------------- */

   private function getDataYoutubeFeeds ( $id, $max ){
       
         $data = $this-> CurlLinkExiste ( $id, $max );
       
         return ( $this-> ValidarCurlYoutube ( $data ) == true ? $data : array ( "error" => "404" ) );   
       
     }//getDataYoutubeFeeds  
     
      
   private function validarCadena ( $cadena ){
       
          //return preg_match( "#^ [a-z]  [\da-z_] {6,22} [a-z\d] \$#i", $cadena );
           //preg_match(‘/^[a-z\d_]{4,28}$/i’, $string
           //return ( preg_match('/^[a-z\d_]{4,28}$/i', $cadena ) );
           //preg_match( '/^[a-zñÑáéíóú\d_\s]{4,28}$/i', $cadena )
           //preg_match("/^[a-zA-ZñÑáéíóúÁÉÍÓÚ¡!¿?()\*\+\%\&\#\$\/\d_-\s\"]{4,200}$/i", $input_line, $output_array);
           #return ( preg_match ("/^[a-zA-ZñÑáéíóúÁÉÍÓÚ¡!¿?()\*\+\%\&\#\$\/\d_-\s\"]{4,200}$/i", $cadena ) );
           return true;
       
      }//validarCadena
      
   private function ValidarCurlYoutube ( $data ){
       
              $datas = json_decode( $data, TRUE );
               $band = true;

             if ( ( is_array( $datas ) ) && ( array_key_exists ( "error", $datas ) ) ) {

                    if ( $datas [ "error" ][ "code" ] == "404" ){
                            $band = false;
                       }//             
                }//is_array

          return ( $band );
       
     }//private Function    
      
   private function CurlLinkExiste ( $ID, $Max ){
       
           $URL = "http://gdata.youtube.com/feeds/api/playlists/".$ID."?v=2&alt=jsonc&max-results=".$Max."&orderby=published";
       
            if ( $URL == NULL ) return false;
           
            $ch = curl_init( $URL );
            
            curl_setopt( $ch, CURLOPT_TIMEOUT, 30 );
            curl_setopt( $ch, CURLOPT_CONNECTTIMEOUT, 60 );
            curl_setopt( $ch, CURLOPT_RETURNTRANSFER, true );
            
            $data = curl_exec($ch);
                                  
            curl_close($ch);
       
          return ( $data );  
                   
      }//validarLink   
                                  
   private function getExisteFile ( $ruta ){
      
          $data =  ( file_exists( $ruta ) ) ? "data" : "none";  
                           
        return $data; 
          
     }//private getExisteFile   
    
   private function getCreateDataJsonYoutube ( $ruta ){
            
            $id = md5 ( time() . microtime() );

          $data = array ( "data"=> array (
                                            array (
                                                     "id" => $id,
                                                   "type" => "1",
                                                 "nombre" => "test",
                                              "url_lista" => "",
                                                  "lista" => "",                                                  
                                                 "estado" => "desactivar",
                                                   "file" => $id."_lista.json",                                                   
                                             "NoListando" => "6",
                                                   "peso" => '_none',
                                                 "update" => time(),
                                                "created" => time(),
                                                  "placa" => '_none'
                                               )//
                                       )//data
                    );
            
          $this-> getFileWriteJson( $ruta, $data );

          if ( ! array_key_exists( "error", json_decode( $this-> validar_url_youtube ( $data[ "data" ][ 0 ][ "url_lista" ], 50 ), TRUE ) ) ){ 
                          
                 $this-> getFileWriteJsonFile( $this-> ruta_json. $id."_lista.json", 
                                               $this-> CurlLinkExiste ( $data[ "data" ][ 0 ][ "lista" ], $this-> Max ) 
                                            ); //crear la lista de los videos          
         
            } // array_key_exists 
         
     }//getCreateDataJsonYoutube  
     
   public function getFileWriteJson ( $Ruta_Json, $Datas ){
    
            $Band = false;

            while ( $Band == false ){

                    if ( file_exists( $Ruta_Json ) ){
                        
                          if ( is_writable( $Ruta_Json ) ) {           
                               $Band = true;                  
                               file_put_contents( $Ruta_Json , json_encode( $Datas ), LOCK_EX );            
                            }// is_writable           
                              
                       }//file_existe    
                    else{
                          file_put_contents( $Ruta_Json , json_encode( $Datas ), LOCK_EX ); 
                          $Band = true;   
                      }  
               }//while
        return $Band;
   }//getFileWrite Verifica que se pueda escribir en el Archivo    
   
   public function getFileWriteJsonFile ( $Ruta_Json, $Datas ){
       
           $Band = false;

            while ( $Band == false ){

                    if ( file_exists( $Ruta_Json ) ){
                        
                          if ( is_writable( $Ruta_Json ) ) {           
                               $Band = true;                  
                               file_put_contents( $Ruta_Json , $Datas, LOCK_EX );            
                            }// is_writable           
                              
                       }//file_existe    
                    else{
                          file_put_contents( $Ruta_Json , $Datas, LOCK_EX ); 
                          $Band = true;   
                      }  
               }//while
        return $Band;                     
     }//
      
   public function getFileWriteLog ( $Ruta_Error, $Datas ){
    
       $Band = false;
      
             while ( $Band == false ){

                  if ( file_exists( $Ruta_Error ) ){  

                       if ( is_writable( $Ruta_Error ) ) {           
                            $Band = true;              
                            file_put_contents( $Ruta_Error , $Datas, FILE_APPEND | LOCK_EX );            
                         }//

                    }else{
                        $Band = true;
                        file_put_contents( $Ruta_Error , $Datas, FILE_APPEND | LOCK_EX ); 
                     }
              }//while
         
      return $Band;
   }//getFileWriteLog Metodo para crear el archivo de Logs | Control de Errores   
   
   
   /* ------------------ Validar URL Youtube ---------------------------------- */
   
    private function getInfoURLParametros ( $Link ){

            $Data = array ();
            $Info = array ();
            
            $Data = parse_url( $Link );
           
            if ( array_key_exists( "query", $Data ) ){
                                
                $Info = ( count ( $this-> getQueryInfoParametros ( $Data [ 'query' ] ) ) > 0 ) ? 
                                  $this-> getQueryInfoParametros ( $Data [ 'query' ] ) : array ();
            
              }//array_key_exists
            
            if ( array_key_exists ( "list", $Info ) ){                     
                 return ( count ( $Info ) > 0 ? substr( $Info [ "list" ], 2, strlen ( $Info [ "list" ] )  ) : array ()  );                  
              }else{
                 return ( array () );  
                }   

        } //getInfoUrlOpinion
        
        
    private function getQueryInfoParametros ( $query ) {

             $params = array();

            if ( strlen ( $query ) > 0 ){
                    $Parts = explode ( '&', $query );

                    foreach ( $Parts AS $param ) {
                                $item = explode( '=', $param );
                                $params [ $item[ 0 ] ] = $item[ 1 ];
                        }//foreach

                }//if parametros
                  
            return $params; 
        }//getQueryInfoParametros 
   
   /* -------------------------------------------------------------------------- */  

  private function orderMultiDimensionalArray ($toOrderArray, $field, $inverse = false) {

          $position = array();
          $newRow = array();
        
         foreach ( $toOrderArray as $key => $row ) {
               $position[ $key ]  = $row[ $field ];
               $newRow[ $key ] = $row;
            } //

          if ( $inverse ) {
              arsort( $position );
           }
          else {
               asort( $position );
            }
          
         $returnArray = array();

          foreach ( $position as $key => $pos ) {     
              $returnArray[] = $newRow[ $key ];
            }

      return $returnArray;

    }//orderMultiDimensionalArray     
       
}//class configuracion_youtubeLista

?>