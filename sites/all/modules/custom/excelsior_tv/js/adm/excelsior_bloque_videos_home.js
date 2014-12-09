jQuery( document ).ready( function () {


   jQuery( "#btn-edit-botton-top-embed" ).click( function (){
         getEditTransmisionOnlineTv();

         return false;
     });   

   jQuery( "#btn-edit-submit-bottom-embed" ).click( function (){
         getEditTransmisionOnlineTv();

         return false;
     });

   jQuery( "#btn-cancel-botton-top-embed" ).click( function (){

       getCancelTransmisionOnlineTv();

       return false;
   });

   jQuery( "#btn-cancel-submit-bottom-embed" ).click( function (){

      getCancelTransmisionOnlineTv();

      return false;
    });

    /* ---------------------------------------------- */

      for ( I =1; I < 5; I++ ){
          jQuery( "#title_video_home_" + I ).attr( "disabled", "disabled" );
          jQuery( "#url_video_home_" + I ).attr( "disabled", "disabled" );
       }
    
    /* ---------------------------------------------- */

});


function getEditTransmisionOnlineTv (){

      for ( I =1; I < 5; I++ ){

           jQuery( "#title_video_home_" + I ).removeClass ( "transmision-textarea-embed-disabled" );
           jQuery( "#title_video_home_" + I ).addClass ( "transmision-textarea-embed-enabled" );

           jQuery( "#url_video_home_" + I ).removeClass ( "transmision-textarea-embed-disabled" );
           jQuery( "#url_video_home_" + I ).addClass ( "transmision-textarea-embed-enabled" );

           jQuery( "#title_video_home_" + I ).removeAttr( "disabled", "disabled" );
           jQuery( "#url_video_home_" + I ).removeAttr( "disabled", "disabled" );   
       }

      return false;
  }  

function getCancelTransmisionOnlineTv(){

       for ( I =1; I < 5; I++ ){
           jQuery( "#title_video_home_" + I ).addClass ( "transmision-textarea-embed-disabled" );
           jQuery( "#title_video_home_" + I ).removeClass ( "transmision-textarea-embed-enabled" );

           jQuery( "#url_video_home_" + I ).addClass ( "transmision-textarea-embed-disabled" );
           jQuery( "#url_video_home_" + I ).removeClass ( "transmision-textarea-embed-enabled" );

           jQuery( "#title_video_home_" + I ).attr( "disabled", "disabled" );
           jQuery( "#url_video_home_" + I ).attr( "disabled", "disabled" );
        }                  

      return false;
 }     