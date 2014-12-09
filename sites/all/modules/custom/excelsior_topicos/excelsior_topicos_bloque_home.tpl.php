<?php
$data = $variables[ 'excelsior_topicos_bloque_home' ];
?>
<ul class="spriteFull" id="topicos-home-list">
<?php foreach ( $data as $topico ): ?>
	<li class="topicos-home-list-item"><a class="topicos-home-list-item-link title-hover family-droid-serif" href="<?php echo $topico['url'] ?>"><?php echo $topico['title'] ?></a></li>
<?php endforeach; ?>
</ul>
<div class="topicos-home-ver-mas">
	<a class="family-titillium-web topicos-home-ver-mas-link" href="/topicos">Ver más</a>
</div>
