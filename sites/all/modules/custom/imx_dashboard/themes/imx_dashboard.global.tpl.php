<!DOCTYPE html>
<html>
<head>
<title>Usuarios Activos - Red Imagen Digital</title>
<!-- Step 1: Load the Embed API library. -->
<script>
  (function(w,d,s,g,js,fjs){
    g=w.gapi||(w.gapi={});g.analytics={q:[],ready:function(cb){this.q.push(cb)}};
    js=d.createElement(s);fjs=d.getElementsByTagName(s)[0];
    js.src='https://apis.google.com/js/platform.js';
    fjs.parentNode.insertBefore(js,fjs);js.onload=function(){g.load('analytics')};
  }(window,document,'script'));
</script>
<script src="//ajax.googleapis.com/ajax/libs/jquery/2.2.4/jquery.min.js"></script>
<!-- Step 2: Load the components and their dependencies. -->
<script src="/sites/all/modules/custom/imx_dashboard/js/active-users.min.js"></script>
<!-- Include the CSS that styles the charts. -->
<link rel="stylesheet" href="/sites/all/modules/custom/imx_dashboard/css/imx_dashboard.css">
<meta http-equiv="refresh" content="300">
</head>
<body>
  <!-- Step 3: Add HTML containers to host the dashboard components.. -->
  <div id="embed-api-auth-container" class="invent"></div>
  <?php
  $index=1;
  foreach($data['views'] as $sitename => $view):
  ?>
  <div class="column">
    <div id="view-<?php print($sitename);?>" class="<?php print($sitename);?> logo"></div>
    <div id="active-users-<?php print($sitename);?>"></div>
  </div>
  <?php
  $index++;
  endforeach;
  ?>


<!-- Step 4: Write the dashboard code. -->
<script>
gapi.analytics.ready(function() {
  gapi.analytics.auth.authorize({
    userInfoLabel : 'Google Analytics con la cuenta de: ',
    container: 'embed-api-auth-container',
    clientid: '393479470712-nhtkfs438r5u6tcprkd9bmlppr75b5a4.apps.googleusercontent.com'
  });

  <?php
  $index=1;
  foreach($data['views'] as $sitename => $view):
  ?>
  var activeUsers_<?php print($sitename);?> = new gapi.analytics.ext.ActiveUsers({
    container: 'active-users-<?php print($sitename);?>',
    pollingInterval: <?php print(rand(15,30));?>
  });
  activeUsers_<?php print($sitename);?>.set({ids:'<?php print($view);?>'});
  activeUsers_<?php print($sitename);?>.once('success', function() {
    var element = this.container.firstChild;
    var timeout;
    this.on('change', function(data) {
      var element = this.container.firstChild;
      var animationClass = data.delta > 0 ? 'is-increasing' : 'is-decreasing';
      element.className += (' ' + animationClass);
      clearTimeout(timeout);
      timeout = setTimeout(function() {
        element.className =
          element.className.replace(/ is-(increasing|decreasing)/g, '');
      }, 3000);
    });
  });
  <?php
  if($index>5 && $index<10){
  ?>
  window.setTimeout(function(){
    activeUsers_<?php print($sitename);?>.execute();
  },'1000');
  <?php
  }else if($index>10){
  ?>
  window.setTimeout(function(){
    activeUsers_<?php print($sitename);?>.execute();
  },'2000');
  <?php
  }else{
  ?>
  activeUsers_<?php print($sitename);?>.execute();
  <?php
  }
  ?>
  <?php
  $index++;
  endforeach;
  ?>
});
</script>
</body>
</html>