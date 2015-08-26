<?php
$privacy=arg(1);
$privacy=isset($privacy) && !empty($privacy) && $privacy=='aviso-de-privacidad' ? TRUE : FALSE;
?>
<?php if($privacy):?>
<header id="navbar" role="banner" class="<?php print $navbar_classes; ?> text-center">
  <?php if ($logo): ?>
  <img src="<?php print url(drupal_get_path('module','gimrh').'/css/top-bolsa-de-trabajo.jpg',array('absolute'=>true)); ?>" alt="Red Invent.mx - Grupo Imagen Multimedia" />
  <?php endif; ?>
</header>
<?php endif;?>

<div class="main-container container">
  <div class="row">
    <section<?php print $content_column_class; ?>>

      <?php print render($title_prefix); ?>
      <?php if (!empty($title)): ?>
        <h1 class="page-header"><?php print $title; ?></h1>
      <?php endif; ?>
      <?php print render($title_suffix); ?>

      <?php print $messages; ?>

      <?php print render($page['content']); ?>
    </section>
  </div>
</div>
