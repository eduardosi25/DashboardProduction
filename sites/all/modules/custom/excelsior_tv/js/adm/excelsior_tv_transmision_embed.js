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

      jQuery( "#id-transmision-embed" ).attr( "disabled", "disabled" );
      jQuery( "#id-textfield-title" ).attr( "disabled", "disabled" );

      jQuery( "#id-transmision-embed-home" ).attr( "disabled", "disabled" );
      jQuery( "#id-textfield-title-home" ).attr( "disabled", "disabled" ); 

      jQuery ( "#id-key-ooyala" ).attr( 'disabled', 'disabled' );     

    /* ---------------------------------------------- */

});


function getEditTransmisionOnlineTv (){

       jQuery( "#id-transmision-embed" ).removeClass ( "transmision-textarea-embed-disabled" );
       jQuery( "#id-transmision-embed" ).addClass ( "transmision-textarea-embed-enabled" );

       jQuery( "#id-textfield-title" ).removeClass ( "transmision-textarea-embed-disabled" );
       jQuery( "#id-textfield-title" ).addClass ( "transmision-textarea-embed-enabled" );

       jQuery( "#id-transmision-embed" ).removeAttr( "disabled", "disabled" );
       jQuery( "#id-textfield-title" ).removeAttr( "disabled", "disabled" );


       jQuery( "#id-transmision-embed-home" ).removeClass ( "transmision-textarea-embed-disabled" );
       jQuery( "#id-transmision-embed-home" ).addClass ( "transmision-textarea-embed-enabled" );

       jQuery( "#id-textfield-title-home" ).removeClass ( "transmision-textarea-embed-disabled" );
       jQuery( "#id-textfield-title-home" ).addClass ( "transmision-textarea-embed-enabled" );

       jQuery( "#id-transmision-embed-home" ).removeAttr( "disabled", "disabled" );
       jQuery( "#id-textfield-title-home" ).removeAttr( "disabled", "disabled" );   

      jQuery( "#id-key-ooyala" ).removeClass ( "transmision-textarea-embed-disabled" );
      jQuery( "#id-key-ooyala" ).addClass ( "transmision-textarea-embed-enabled" );
      
      jQuery ( "#id-key-ooyala" ).removeAttr('disabled', 'disabled' );       

      return false;
  }  

function getCancelTransmisionOnlineTv(){

       jQuery( "#id-transmision-embed" ).addClass ( "transmision-textarea-embed-disabled" );
       jQuery( "#id-transmision-embed" ).removeClass ( "transmision-textarea-embed-enabled" );

       jQuery( "#id-textfield-title" ).addClass ( "transmision-textarea-embed-disabled" );
       jQuery( "#id-textfield-title" ).removeClass ( "transmision-textarea-embed-enabled" );

        jQuery( "#id-transmision-embed" ).attr( "disabled", "disabled" );
        jQuery( "#id-textfield-title" ).attr( "disabled", "disabled" );

       jQuery( "#id-transmision-embed-home" ).addClass ( "transmision-textarea-embed-disabled" );
       jQuery( "#id-transmision-embed-home" ).removeClass ( "transmision-textarea-embed-enabled" );

       jQuery( "#id-textfield-title-home" ).addClass ( "transmision-textarea-embed-disabled" );
       jQuery( "#id-textfield-title-home" ).removeClass ( "transmision-textarea-embed-enabled" );

        jQuery( "#id-transmision-embed-home" ).attr( "disabled", "disabled" );
        jQuery( "#id-textfield-title-home" ).attr( "disabled", "disabled" ); 

        
      jQuery( "#id-key-ooyala" ).removeClass ( "transmision-textarea-embed-enabled" );
      jQuery( "#id-key-ooyala" ).addClass ( "transmision-textarea-embed-disabled" );
      
      jQuery ( "#id-key-ooyala" ).attr( "disabled", "disabled" );         

      return false;
 }     