<?php
/*
@Developer : J. Enrique Montiel P.
Class : Obtiene Videos de Youtube sobre una lista
*/

class getYoutubeLista{

  public $ruta = "";
  public $ruta_json = "";
  public $data = array();
  public $error = array ();
  public $ruta_lista = "";  
  public $TotalVideos = 50;
  
  public function __construct ( $ruta_json, $ruta, $base_url ){
  	 $this-> ruta = $ruta;
  	 $this-> ruta_json = $ruta_json;
   }


 public function getData( $ruta ){       
         return ( json_decode( file_get_contents( $ruta ), true ) );       
    }//getData


 public function get_lista ( $file, $key, $max ){

        return ( $this-> getListaData ( $this-> ruta . $file, $max ) );            
    }

 public function get_update_lista ( $file, $key_list, $max = 50 ){

    $Band = FALSE;

     if ( file_exists( $this-> ruta . $file ) ){

        $data = $this-> CurlLinkExiste ( $key_list, $max );

          if ( ! array_key_exists( "error", json_decode( $data, TRUE ) ) ){
                 $this-> getFileWriteFile ( $this-> ruta . $file, $data );
                 $Band = TRUE;
            } // error   
        } //if file_exist

       return $Band;
    } //get_update_lista 


  private function getListaData ( $ruta, $max ){
        
          $data = array ();
          $Complemento = array ();

          if ( file_exists( $ruta ) ){                 
                $data = json_decode( file_get_contents( $ruta ), true );     
             }
                                          
          if ( count ( $data ) > 0 ){

             $I = 1;

              foreach ( $data[ 'data' ] ['items'] as  $Key ){

                    $Complemento[] = array (     "id" => $Key[ 'video' ] [ 'id' ], 
                                              "title" => $Key [ 'video' ] [ 'title' ], 
                                        "description" => $Key [ 'video' ] [ 'description' ],
                                              "thumb" => $Key [ 'video' ] [ 'thumbnail' ] [ 'sqDefault' ],
                                            "thumbHD" => $Key [ 'video' ] [ 'thumbnail' ] [ 'hqDefault' ], 
                                            "thumbMq" => 'http://i1.ytimg.com/vi/'. $Key[ 'video' ] [ 'id' ] .'/mqdefault.jpg',
                                          "duraccion" => $Key[ 'video' ] [ 'duration' ],
                                     "reproducciones" => $Key[ 'video' ] [ 'viewCount' ]
                                        );   
                    if ( $I == $max ){
                         break;
                      }

                   $I++;

                }//foreach
                                                   
             }//data > 0
               
       return ( ( count ( $Complemento ) > 0 ) ? $Complemento : array () );
             
    }// getListaData 


   private function CurlLinkExiste ( $ID, $Max ){
       
           $URL = "http://gdata.youtube.com/feeds/api/playlists/".$ID."?v=2&alt=jsonc&max-results=".$Max."&orderby=published";
       
            if ( $URL == NULL ) return false;
          
            $ch = curl_init( $URL );
          
            curl_setopt( $ch, CURLOPT_TIMEOUT, 30 );//comentar
            curl_setopt( $ch, CURLOPT_CONNECTTIMEOUT, 60 ); ///comentadas
            curl_setopt( $ch, CURLOPT_RETURNTRANSFER, true );

            $data = curl_exec( $ch );

            curl_close($ch);

          return ( $data );  
                   
      }//validarLink   

  private function CurlLinkXVideo ( $ID ){

         $URL = "http://gdata.youtube.com/feeds/api/videos/". $ID ."?v=2&alt=jsonc";
     
          if ( $URL == NULL ) return false;
         
          $ch = curl_init( $URL );
          
          curl_setopt( $ch, CURLOPT_TIMEOUT, 30 );
          curl_setopt( $ch, CURLOPT_CONNECTTIMEOUT, 60 );
          curl_setopt( $ch, CURLOPT_RETURNTRANSFER, true );
          
          $data = curl_exec($ch);
                                
          curl_close($ch);
     
        return ( $data );      
    }        

  private function getFileWriteFile ( $Ruta_Json, $Datas ){
       
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


} //Class