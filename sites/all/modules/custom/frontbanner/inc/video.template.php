<!DOCTYPE html>
<html lang="es">
<head>
<meta content="text/html; charset=UTF-8">
<meta charset="UTF-8">
<title><?php print($prehomeConfig->title);?></title>
<?php
if($prehomeConfig->og){
  foreach($prehomeConfig->og as $name => $value){
    ?>
    <meta property="og:<?php print($name);?>" content="<?php print($value);?>"/>
    <?php
  }
}
?>
<script type="text/javascript" src="/videopo2/videolib.min.js"></script>
<script type="text/javascript">jQuery.noConflict();</script>
<script src="http://jwpsrv.com/library/k9UL2AnnEeOvMRIxOUCPzg.js"></script>
<link rel="stylesheet" type="text/css" href="/videopo2/video.styles.css" />
<style>
.logo-site{background-image: url("<?php print($prehomeConfig->logo);?>")}
.close{background-image: url("<?php print($prehomeConfig->bgimage);?>")}
</style>
</head>
<body>
<div id="fb-root"></div>
<section id="body-recomendacion">
  <article id="wrapper-recomendacion">
  <div class="header">
    <div id="site-actitudfem" class="logo-site left"></div>
    <div id="close-pop" class="close rigth"></div>
    <div class="clear"></div>
  </div>
  <div class="wrapper-info"><?php print($prehomeConfig->legend);?></div>
  <div class="wrapper-video">
    <div id='idlocal'></div>
    <script type='text/javascript'>
    jwplayer('idlocal').setup({
      file: '<?php print($prehomeConfig->movie);?>',
      image: '<?php print($prehomeConfig->poster);?>',
      title: '<?php print($prehomeConfig->movie_title);?>',
      width: '<?php print($prehomeConfig->size->width);?>',
      aspectratio: '16:9'
    });
    </script>
  </div>
  </article>
  <div class="wrapper-shares">
    <div class="left text-share"><?php print($prehomeConfig->subtitle);?></div>
    <div class="left wrapper-botones">
      <div class="boton-shares left">
        <div class="<?php print($prehomeConfig->shares->facebook->share->css);?>" data-href="<?php print($prehomeConfig->shares->facebook->share->url);?>" data-type="<?php print($prehomeConfig->shares->facebook->share->layout);?>"></div>
      </div>
      <div class="boton-shares left">
        <div class="<?php print($prehomeConfig->shares->facebook->like->css);?>" data-href="<?php print($prehomeConfig->shares->facebook->like->url);?>" data-layout="<?php print($prehomeConfig->shares->facebook->like->layout);?>" data-action="<?php print($prehomeConfig->shares->facebook->like->action);?>" data-show-faces="<?php print($prehomeConfig->shares->facebook->like->faces);?>" data-share="<?php print($prehomeConfig->shares->facebook->like->shares);?>"></div>
      </div>
      <div class="boton-shares left">
        <a href="https://twitter.com/share" data-count="<?php print($prehomeConfig->shares->twitter->layout);?>" class="<?php print($prehomeConfig->shares->twitter->css);?>" data-url="<?php print($prehomeConfig->shares->twitter->url);?>" data-via="<?php print($prehomeConfig->shares->twitter->via);?>" data-dnt="true">Tweet</a>
      </div>
      <div class="boton-shares google left">
        <g:plusone size="<?php print($prehomeConfig->shares->googleplus->layout);?>" href="<?php print($prehomeConfig->shares->googleplus->url);?>" ></g:plusone>                            
      </div>
      <div class="clear"></div>
    </div>
    <div class="clear"></div>
  </div>
</section>
<script>(function(d, s, id) {
var js, fjs = d.getElementsByTagName(s)[0];
if (d.getElementById(id))
  return;
js = d.createElement(s);
js.id = id;
js.src = "//connect.facebook.net/es_LA/all.js#xfbml=1";
fjs.parentNode.insertBefore(js, fjs);
}(document, 'script', 'facebook-jssdk'));</script>
<script>!function(d, s, id) {
var js, fjs = d.getElementsByTagName(s)[0], p = /^http:/.test(d.location) ? 'http' : 'https';
if (!d.getElementById(id)) {
js = d.createElement(s);
js.id = id;
js.src = p + '://platform.twitter.com/widgets.js';
fjs.parentNode.insertBefore(js, fjs);
}
}(document, 'script', 'twitter-wjs');</script>
<script type="text/javascript" src="https://apis.google.com/js/platform.js">{lang: 'es'}</script>
<script type="text/javascript">
jQuery('.close').click(function(){
  var expireCookie=calculate_time_expiring_cookies('<?php print($prehomeConfig->expire);?>');
  jQuery.cookie('prehome', '{"status":"1","expire" : "'+expireCookie+'"}', {path: '/'});
  location.reload();
});
function getCookie(cname){
  var name = cname + "=";
  var ca = document.cookie.split(';');
  for(var i=0; i<ca.length; i++){
    var c = ca[i].trim();
    if (c.indexOf(name)==0)
      return c.substring(name.length,c.length);
  }
  return "";
} 
function setCookie(cname,cvalue,exdays){
  var d = new Date();
  d.setTime(d.getTime()+(exdays*24*60*60*1000));
  var expires = "expires="+d.toGMTString();
  document.cookie = cname + "=" + cvalue + "; " + expires;
}
function checkCookie(){
  var username=getCookie("username");
  if (username!=""){
    alert("Welcome again " + username);
  }else{
    username = prompt("Please enter your name:","");
    if (username!="" && username!=null){
      setCookie("username",username,365);
    }
  }
}
function getJSONObjectfromCookie(text){
  var myData = JSON.parse(text, function (key, value) {
    var type;
    if (value && typeof value === 'object') {
      type = value.type;
      if(typeof type === 'string' && typeof window[type] === 'function'){
        return new (window[type])(value);
      }
    }
    return value;
  });
}
function calculate_time_expiring_cookies(expire){
  if(!expire)
    return 0;
    
  //Valores posibles (segundos, minutos, horas, dias)
  //usando la primer letra de cada palabra para el cálculo
  //s = secs :: m = mins :: h = hours :: d = days
  var timestamp=Math.round(new Date().getTime()/1000);
  var regExpFull=/[0-9]+(s|m|h|d)/;
  var regExpNumber=/[0-9]+/;
  var regExpPeriod=/[smhd]/;
  if(expire.match(regExpFull)){
    var number=expire.match(regExpNumber);
    var period=expire.match(regExpPeriod);
    if(period=='s'){
      timestamp=timestamp+parseInt(number);
    }
    if(period=='m'){
      timestamp=timestamp+parseInt(number)*60;
    }
    if(period=='h'){
      timestamp=timestamp+parseInt(number)*60*60;
    }
    if(period=='d'){
      timestamp=timestamp+parseInt(number)*60*60*24;
    }
  }
  return timestamp;
}
</script>
</body>
</html>
