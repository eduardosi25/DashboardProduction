jQuery(document).ready(function(){
  if(typeof Drupal.settings.videoOoyala.vid != 'undefined'){
    var htmlVideoOoyala="<div id='ooyalaplayer' style='width:100%;height:320px;margin-bottom:20px;'></div>";
    htmlVideoOoyala+="<script>OO.ready(function(){OO.Player.create('ooyalaplayer','"+Drupal.settings.videoOoyala.vid+"');});</script>";
    htmlVideoOoyala+="<noscript><div>Debes activar Javascript en tu navegador para ver este video</div></noscript>";
    jQuery("#note_body > h1").after(htmlVideoOoyala);
    jQuery('#note_body').find('iframe').each(function(){
      jQuery(this).hide();
    });
  }
});
