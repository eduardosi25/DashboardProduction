<section id="imx-users-profile">
  <?php if ($data['login']): ?>
    <span class="sesion-user"><a href="/user/logout">Cerrar Sesión</a></span>
  <?php endif ?>
  <div id="imx-users-profile-image">
    <img src="<?php echo $data['image']?>" width="170" height="170">
  </div>
  <aside id="imx-users-profile-data">
    <h1 class="imx-users-title-name"><?php echo $data['name']?></h1>
    <p class="imx-users-description"><?php echo $data['signature']?></p>
    <p class="imx-page-web-user"><a href=""></a></p>
    <div class="imx-social-users-profile">
      <div class="addthis_toolbox addthis_default_style addthis_32x32_style">
        <?php if(!is_null($data['twitter'])): ?>
          <a href="https://twitter.com/<?php print $data['twitter']; ?>" class="twitter-follow-button left" data-show-count="false">Seguir a @<?php echo $data['twitter'];?></a>
        <?php else: ?>
          <a class="twitter-follow-button" style="text-aling:center;" href="https://twitter.com/Dinero_Exc"  data-show-count="false" data-lang="es"  data-show-screen-name="false">Seguir a @Dinero_Exc</a>
        <?php endif; ?>
        <?php if(!is_null($data['facebook'])): ?>
          <div class="fb-follow" data-href="https://www.facebook.com/<?php echo $data['facebook'];?>" data-colorscheme="light" data-layout="button" data-show-faces="true"></div>
        <?php else: ?>
          <div class="fb-follow" data-href="https://www.facebook.com/DineroEnImagen" data-colorscheme="light" data-layout="button" data-show-faces="true"></div>
        <?php endif; ?>
        <a class="addthis_button_google_plusone" g:plusone:annotation="bubble"></a>
      </div>
    </div>
  </aside>
</section>
<?php if (isset($data['background'])): ?>
  <script type="text/javascript">
    (function($){
      $(document).ready(function(){
        var background_url  = "<?php echo $data['background']; ?>";
        if ( background_url != '') {
          jQuery('body').css( "background","url('"+ background_url +"' ) no-repeat fixed center 0" );
          jQuery('#page-wrapper').css('background','none');
        };
      });  //Termina ready
    })(jQuery);
  </script>
<?php endif ?>
