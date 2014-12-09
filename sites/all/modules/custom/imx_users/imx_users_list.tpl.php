<div class="imx-users-dinero">
	<div class="imx-users-line">
		<?php if (intval($total_traffic)): ?>
			<table id="imx-users-traffic-table">
				<tr id="imx-users-traffic-rows">
					<td id="imx-user-title">Datos generales</td>
					<td class="imx-table-cell"><span>Visto <?php echo $total_traffic['totalUniqueUsers'] ?></span></td>
					<td class="imx-table-cell"><span>Pageviews <?php echo $total_traffic['totalEvents'] ?></span></td>
					<td class="imx-table-cell"><span>Tiempo promedio <?php echo conversorSegundosHoras($total_traffic['averageActiveTime']) ?></span></td>
				</tr>
			</table>
		<?php endif ?>
	</div>
	<ul id="imx-users-item">
		<?php foreach ($data as $key => $value): ?>
				<?php #echo '<pre>'; print_r($value); echo '</pre>'; ?>
			<li class=" imx-users-dinero-content prelative ">
				<div class="imx-users-dinero-content-text left">
					<a href="/<?php echo $value['url']  ?>">
						<h3 class="imx-users-dinero-title-nota dblock family-droid-serif"><?php echo $value['title']  ?> </h3>
						<p class="imx-users-dinero-sumary dblock">
							<span class="dblock sprite-new-home imx-cuadro-users-azul"></span>
							<span class="imx-date-nota-users family-droid-sans "><?php echo $value['date']; ?></span>
							<span class="imx-users-summary"><?php echo $value['summary'] ?></span>
						</p>
					</a>
				</div>
				<div id="addthis-shares">
	                <!-- AddThis Button BEGIN -->
	                <div class="addthis_toolbox addthis_default_style">
	                        <a class="addthis_button_facebook_share" fb:share:layout="button_count" fb:addthis:url="<?php print $value['social_url'] ?>"></a>
	                        <a class="addthis_button_tweet" tw:count="horizontal"  tw:addthis:url="<?php echo $value['social_url'] ?>" addthis:title="<?php echo $value['title'] ?>" tw:via="<?php echo $value['twitter_via'] ?>"></a>
	                        <a class="addthis_button_google_plusone"  g:plusone:size="medium"></a>
							<a class="button-que-opinas prelative">
				                <span class="globe-a-text-queopinas" id="imx_share_s" >Comentarios</span>
								<span class="globe-a-cont"><fb:comments-count href="<?php print $value['full_url'] ; ?>"></fb:comments-count></span>
								<span class="pleca-comments dblock"><s></s><i></i></span>
				            </a>
	                </div>
	                <!-- AddThis Button END -->
	            </div>
	            <?php if (isset($value['traffic']['data']['activeTime'])): ?>
	            <div class="imx-users-metrica-content">
	            	<spam class="imx-metrica-view">
	            		<span class="imx-text-view">Visto: <span class="imx-tex-pik-gre"></span></span>
	            		<span class="imx-time-text"><?php echo $value['traffic']['data']['uniqueUsers']?></span>
	            	</spam>
	            	<spam class="imx-full-time">
	            		<span class="imx-text-view">Tiempo promedio:<span class="imx-tex-pik-gre"></span></span>
	            		<span class="imx-time-text"><?php echo conversorSegundosHoras($value['traffic']['data']['activeTime'])?></span>
	            	</spam>
	            </div>
	            <?php endif ?>
			</li>
		<?php endforeach ?>
	</ul>
</div>
<!-- AddThis Smart Layers BEGIN -->
<script type="text/javascript">
var addthis_share = addthis_share || {}
addthis_share = {
        passthrough : {
                twitter: {
                        via: "<?php echo $value['twitter_via'] ?>"
                }
        }
}
</script>
<!-- AddThis Smart Layers END -->