jQuery(document).ready(function(){

   
});

function close_full_responsive_transmition_online(){      

	  var html = '<div onclick = "play_full_responsive_transmition_online();" class = "spriteFullTv onclick_tv_vivo_stop" id = "id_onclick_tv_vivo_play_stop" >&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</div>';
      
       jQuery( "#id-embed-transmision-in-live" ).html ( "" );
       //jQuery( "#id-transmision-online-home-video" ).fadeOut(); 
       jQuery( "#id-embed-transmision-in-live" ).html ( jQuery( "#id-transmision-tv-online-pause" ).val() );

       jQuery( "#stop-play-transmision-click" ).html (  html );
       
   }//close_full_responsive_transmition

function play_full_responsive_transmition_online(){      
      
        var html = '<div onclick = "close_full_responsive_transmition_online();" class = "spriteFullTv onclick_tv_vivo_play" id = "id_onclick_tv_vivo_play_stop" >&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </div>';

       jQuery( "#id-embed-transmision-in-live" ).html ( "" );
       //jQuery( "#id-transmision-online-home-video" ).fadeOut(); 
       jQuery( "#id-embed-transmision-in-live" ).html ( jQuery( "#id-transmision-tv-online-play" ).val() );

       jQuery( "#stop-play-transmision-click" ).html (  html );
       
   }//close_full_responsive_transmition   