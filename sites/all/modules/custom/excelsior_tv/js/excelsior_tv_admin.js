jQuery(document).ready(function(){


  jQuery ( "#lista-return-edit-delete" ).click( function (){

       window.location.href = "http://"+ document.domain +"/admin/config/excelsior/tv-config/list";

       return false;
 
    });

});

function actualizarReproduccionTv ( key, capa, URL, Index ){

       get_ajax_push( key, capa, URL, Index );


    }//actualizarReproduccionTv

 function get_ajax_push( KEY, CAPA, URL, Index ){

            var patch_url = "http://"+ document.domain + URL;

 			jQuery.ajax({
		                    url: patch_url,
		                  async: false,

		                   data: { id: KEY, index: Index },              
		               dataType: "json",
		            contentType: 'application/x-www-form-urlencoded; charset=UTF-8',
		                  error: function( objeto, quepaso, otroobj ){
		                           
		                         },
		                 cache: false,                         
		                global: true,
		            ifModified: false,
		           processData: true,
		                  type: "GET",          
		            beforeSend: function (  jqXHR,  settings ){
		                            var html = '<img src =  "http://07efd3b603a03e969c0d-475551f34d0bc0bfb73a67cd556cc73c.r32.cf2.rackcdn.com/ajax-loader-adm.gif" style = "width:16px;height:16px;" /> Actualizando...';  
		                                jQuery( CAPA ).html ( html );
		                          },
		              complete: function( data, status ){ 
		                            var html = "";

                                          
		                            var responses = jQuery.parseJSON( data.responseText );
		                            

		                                 if ( parseInt( data.status ) == 200 ){
		                                    if ( parseInt(  responses.response.status ) == 200 ){
		                                            
		                                            html = '<div class="messages status">';
													  html +='<h2 class="element-invisible">Mensaje de estado</h2>';
													    html += responses.data.message;
													html += '</div>'; 		                                           
		                                      }//1
		                                    else{                                  
		                                          html = '<div class="messages error"> ';
		                                         html += '<h2 class="element-invisible">Mensaje de error</h2>';
		                                             html += responses.data.message;
		                                         html += '</div>';  
		                                      }

		                                    jQuery( CAPA ).html ( "" );
		                                    jQuery( CAPA ).html ( html ).stop(true, true).hide().fadeIn();
		                                      
		                                  }//200 
		                          },                              
		            });
    } //get_ajax_push  