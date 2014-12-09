jQuery(document).ready(function(){

   jQuery( "#id-img-open-online-transmision" ).click( function (){
       jQuery( "#id-transmision-online-home-video" ).stop(true, true).hide().fadeIn();

          	var html = "";

   	        jQuery( "#embed-transmisition-online-home-video-responsive" ).html ( jQuery( "#id_hidden_embed_transmition_play_vivo" ).val() );
   	        jQuery( "#embed-transmisition-online-pause-home-video-responsive" ).html ( "");
       
        //window.location.href="/tv";
    });   

});

function close_full_responsive_transmition(){      

       jQuery( "#embed-transmisition-online-home-video-responsive" ).html ( "" );
       jQuery( "#id-transmision-online-home-video" ).fadeOut(); 
       jQuery( "#embed-transmisition-online-pause-home-video-responsive" ).html ( jQuery( "#id_hidden_embed_transmition_pause_vivo" ).val() );
       
   }//close_full_responsive_transmition
