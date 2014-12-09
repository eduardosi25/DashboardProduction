<?php
/*
@Developer : J. Enrique Montiel P.
Class : Obtiene Videos de Youtube sobre un canal
*/

class VideoGaleriaYoutube {

  public $node = "";
  public $type = "";
  public $pag = "";
  public $ruta = "";
  public $data = array();
  public $error = array ();
  public $ruta_lista = "";
  public $base_url = "";
  public $NumeroPaginas = 16;
  public $TotalVideos = 50;
  public $KeyDataVideos = array ();
          
     public function __construct( $node, $type, $pag, $ruta, $rutalist, $base_url ){
        
             $this-> node = trim ( $node );             
             
             $this-> type = ( $type > 0 ) ? $type : 1;                          
             $this-> pag = ( $pag > 0 ) ? $pag : 1;
            
             $this-> ruta = $ruta;
             $this-> ruta_lista = $rutalist;
             $this-> base_url = $base_url;
             
             $this-> data =  $this-> getData();//json config.json
                                                
      }//Constructor
      
    public function VideosYoutubeLista (){
         
         $data = $this-> getIdListaYoutube ();
         $this-> KeyDataVideos = $data;
        
            if ( !empty ( $this-> node ) ){

                if ( $this-> node != "none" ){                                     
                    
                    $KeyLista = $this-> getKeyYoutubeOrdernado ( $data, trim( $this-> node ) , "id" );
                    
                        $data = $this->getPaginarKeysYoutube( $data, $this-> NumeroPaginas, $this-> pag, $KeyLista );           
                                                                                                             
                  }else{
                        $data = $this->getPaginarKeysYoutube( $data, $this-> NumeroPaginas, $this-> pag, array ( ) );                            
                    }
                  
              }//node
            else{
              $data  = $this->getPaginarKeysYoutube( $data, $this-> NumeroPaginas, $this-> pag, array ( ) );         
             }  
                  
         return ( $data );
              
      }//VideosYoutubeLista  

    public function PaginacionListaYoutube (){
      
           return ( $this->getPaginadoListado( $this-> KeyDataVideos, $this-> NumeroPaginas, $this-> pag, $this-> node ) );
        
       }//PaginacionListaYoutube  
       
       
    /* --------------------------------------------------------------------- */
   
    private function getKeyYoutubeOrdernado( $KeyYoutubes, $Id_Search, $Campo ) {

        $KeysYoutube = $KeyYoutubes;
            $IdVideo = $Id_Search;

            $TempArray = array ();
            
            $Key =  $this-> Search_Key ( $KeysYoutube, $Campo, trim ( $IdVideo ) );
              
           if ( strlen ( $Key ) > 0 ){

                $TempArray = array( "id" => $KeysYoutube [ $Key ] [ 'id' ],
                                    "titulo" => $KeysYoutube [ $Key ] [ 'titulo' ],
                                    "descripcion" => $KeysYoutube [ $Key ] [ 'descripcion' ],
                                    "thumb" => $KeysYoutube [ $Key ] [ 'thumb' ], 
                                    "url" => $this-> base_url. "?w=" . $KeysYoutube [ $Key ] [ 'id' ]. "&type=" . $this-> type  
                                    //?w=2092&pag=101&type=1                
                                );

            }//key > 0

        return ( $TempArray );
    }//getKeyYoutubeOrdernado 
    
    private function Search_Key ( $array, $key, $value ) {

     $Posi = NULL;
    
         foreach ($array as $k=>$subarray){  

             if ( isset ( $subarray[ $key ] ) && $subarray[ $key ] == $value ) {
                    $Posi = $k;
                    break;
               }
               ////if 
            }//foreach
      return ( $Posi );      
  }//  Busqueda de Key y Values      
       
    private function getPaginarKeysYoutube ( $Data, $Num, $Pagina, $KeyIndice ) {

            $KeyData = array();
             $Inicio = ( $Pagina - 1 ) * $Num;
             
            if ( count ( $KeyIndice ) > 0 ){            

                   $Final = $Pagina * $Num ;                                    
                    $Data = array_slice( $Data, $Inicio, $Final ); 
                   array_unshift( $Data, $KeyIndice );
                    
                    $Data = array_map( "unserialize", array_unique( array_map ( "serialize", $Data ) ) );
                                                   
              }else{
                   $Final = $Pagina * $Num ;
                    $Data = array_slice( $Data, $Inicio, $Final );                                                            
                }//else
                
              $Data = array_merge ( array (), $Data );

                    $K = 0;                            
                    $i = 0;
                $Final = $Num;

                while ( $i < $Final  ){

                    if ( isset ( $Data [ $i ] [ "id" ] ) ) {
                                    $KeyData [ $K ][ "id" ] = $Data [ $i ] [ "id" ];
                                    $KeyData [ $K ][ "titulo" ] = $Data [ $i ] [ "titulo" ];
                                    $KeyData [ $K ][ "descripcion" ] = $Data [ $i ] [ "descripcion" ];
                                    $KeyData [ $K ][ "thumb" ] = $Data [ $i ] [ "thumb" ];
                                    $KeyData [ $K ][ "url" ] = $this-> base_url. "?w=" . $Data [ $i ] [ "id" ]. "&type=" . $this-> type;  
                            $K++;
                        }                                                                         
                    $i++;
                    }//while                
                                                                                                                                                
        return ( $KeyData );
     }//getPaginarKeysYoutube

    private function getPaginadoListado ( $Data, $Num, $Pagina, $IdVideo ) {

            $Paginador = "";
              $Paginas = ceil ( count( $Data ) / $Num );

           if ( empty( $IdVideo ) ) {
                    $IdVideo = "none";
                }//

              $Paginador = '<div id="paginas" class="ajax-pag">';

               if ( $Pagina > 1 )
                    $Paginador .= '<div class="ajax-pag-prev"><a href="' . $this-> base_url . "?w=none&type=".$this-> type."&pag=" . ($Pagina - 1 ) . '"></a></div>';

               for ( $I = 1; $I <= $Paginas; $I++ ) {
                    if ($I == $Pagina) {
                          $Paginador .= "<strong> " . $I . " </strong>";
                      } else {
                          $Paginador .= '<a href="' . $this-> base_url . "?w=none&type=".$this-> type."&pag=" . $I . '">' . $I . '</a>&nbsp;';
                        }
                }//for

                if ( $Pagina < $Paginas ) {
                     $Paginador .= '<div class="ajax-pag-next"><a href="' . $this-> base_url . "?w=none&type=". $this-> type. "&pag=" . ( $Pagina + 1 ) . '"></a></div>';
                  }//

                $Paginador .= '</div>';

        return ( $Paginador );
        
      }//getPaginadoListado
       
    /* --------------------------------------------------------------------- */   
            
    private function getIdListaYoutube (){
        
            $data = array ();
          $Videos = array ();
        
            if ( count ( $this-> data[ "data" ] ) > 0 ){

                $Key = $this-> Search_Key ( $this-> data[ "data" ], "type", $this-> type );

                    if ( is_numeric( $Key ) ){

                          $data = $this-> data[ "data" ] [ $Key ];
                          
                          if ( $data[ "estado" ] == "activar" ){                          
                               $Videos = $this-> getListaData( $this-> ruta_lista. $data [ "file" ] );
                               $this-> NumeroPaginas = ( $data [ "NoListando" ] > 0 ) ? $data [ "NoListando" ] : 16;
                            }//estado de activación  
                                                   
                       }//is_numeric 
                       
                }//count data
           return ( $Videos );     
       }//private getIdListaYoutube 
                                                          
    private function getListaData ( $ruta ){
        
              $data = array ();
              $Complemento = array ();

              if ( file_exists( $ruta ) ){                 
                    $data = json_decode( file_get_contents( $ruta ), true );     
                 }
                                   
              if ( count ( $data ) > 0 ){

                 $I = 0;

                  foreach ( $data[ 'data' ] ['items'] as  $Key ){

                        $Complemento[] = array (     "id" => $Key[ 'video' ] [ 'id' ], 
                                                 "titulo" => $Key [ 'video' ] [ 'title' ], 
                                            "descripcion" => $Key [ 'video' ] [ 'description' ],
                                                  "thumb" => $Key [ 'video' ] [ 'thumbnail' ] [ 'sqDefault' ],
                                                "thumbHD" => $Key [ 'video' ] [ 'thumbnail' ] [ 'hqDefault' ],
                                                "thumbHD" => $Key [ 'video' ] [ 'thumbnail' ] [ 'hqDefault' ],
                                              "duraccion" =>  $Key[ 'video' ] [ 'duration' ],
                                         "reproducciones" =>  $Key[ 'video' ] [ 'viewCount' ]
                                            );   
                        $I++;

                    }//foreach
                                                       
                 }//data > 0
                   
            return ( ( count ( $Complemento ) > 0 ) ? $Complemento : array () );
             
        }// getListaData 
        
      private function getData(){       
             return ( json_decode( file_get_contents( $this-> ruta ), true ) );       
        }//getData  config.Json         
      
      
                         
  }//class


?>