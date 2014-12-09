<div class="topicos-banner spriteFull"></div>
<div class="clear topicos-listado-container">
	<div class="topicos-listado-columna">
<?php
$previous_letter = "";
$i = 1;
$partir_en = floor(count($variables['excelsior_topicos_page_lista'])/2);
foreach($variables['excelsior_topicos_page_lista'] as $topico): 
	$current_letter = _transliterate_string(strtoupper(mb_substr($topico->title,0,1)));
	if($current_letter != $previous_letter):

		// Columnas
		if($i >= $partir_en): ?>
	</div>
	<div class="topicos-listado-columna">
		<?php $partir_en = count($variables['excelsior_topicos_page_lista'])+1;
		endif; ?>
<?php echo ($i>1)?"</ul>":""; ?>
<h4 class="topicos-listado-header"><?php print($current_letter); ?></h4>
<ul class="topicos-listado">
		<?php	
		$previous_letter = $current_letter;
	endif; ?>

	<li class="topicos-listado-list-item"><a class="topicos-listado-list-item-link" href="<?php print($topico->url); ?>"><?php print($topico->title); ?></a></li>
	<?php
	$i++;
endforeach; ?>
</ul>
</div>
</div>