<?php

function get_facebook_data_href($nid){
  return null;
}
print render( $node_top ); 
$wrapper = entity_metadata_wrapper( 'node', $node ); 
$cx_site_id = $variables['excelsior_topicos_vars']['cx_site_id'];

if(module_exists('excelsior_topicos')): ?><!-- if module_exists -->
<!-- variables tópicos -->
<script type="text/javascript">
    /**
     * El main query se compone de los keywords que el editor seleccionó al agregar el tópico
     */    
    <?php 
    $p_aq = array();    
    foreach ( $wrapper->field_terminos_relacionados->value() as $keyword ){
        $keyword_array = array();
        preg_match("/(.*)--(.*)$/", $keyword, $keyword_array);
        $p_aq[] = 'query(' . $keyword_array[1] . ':"' . $keyword_array[2] . '")';
    }
    print "var main_query = '(" . implode(' or ', $p_aq) . ")';\n";
    ?>

    jQuery(document).ready(function () {

        /**
         * Callback para llenar los campos vía Javascript
         */
        noTePierdasCallback = function(data){

            data.dateFormat = function () {
                return function(date, render){
                    var parts = render(date).match(/\d+/g);
                    dateObj = new Date(parts[0], parts[1] - 1, parts[2], parts[3], parts[4], parts[5]);
                    dateObj.setHours( dateObj.getHours() - (dateObj.getTimezoneOffset() / 60) );
                    return dateObj.getFullYear() + '-' + ('0' + (dateObj.getMonth()+1)).slice(-2) + '-' + ('0' + dateObj.getDate()).slice(-2) + ' ' + ('0' + dateObj.getHours()).slice(-2) + ':' + ('0' + dateObj.getMinutes()).slice(-2);
                }
                
            }
            data.truncateDescription = function () {
                return function(description, render){
                    if(render(description).length > 150)
                        return jQuery.trim(render(description)).substring(0, 150).split(" ").slice(0, -1).join(" ") + "...";
                    else
                        return render(description)
                }
            }

            jQuery('#topicos-no-te-pierdas').html(ich.no_te_pierdas(data, true));
        }

        /**
         * Llenamos los atributos del objeto que hará el query
         * y después ejecutamos la búsqueda con fetchResults()
         */
        var cxsNoTePierdas = new cxSearch('<?php print($cx_site_id); ?>');
        cxsNoTePierdas.queryType = 'recs';
        cxsNoTePierdas.p_aq = main_query + ' and (query(imx-nodetype:"article") or query(imx-nodetype:"galery")) and query(url:"www.excelsior.com.mx")';
        cxsNoTePierdas.p_sm = 'recs-publishtime:desc';
        cxsNoTePierdas.callback = 'noTePierdasCallback';
        cxsNoTePierdas.matchingMode = 'contextual^75,behavioral^25';
        cxsNoTePierdas.p_dr='title';
        cxsNoTePierdas.p_c = '9';
        cxsNoTePierdas.p_rs = 'fl:[url,title,recs-publishtime]';
        cxsNoTePierdas.fetchResults();

    });

</script>

<!-- mustache template resto recientes -->
<script id="no_te_pierdas" type="text/html">
<h3 class="topicos-modulos-titulo spriteFull">No te pierdas</h3>
{{#matches}}
<a href="{{document.fields.url}}" class="topicos-nota-no-te-pierdas">
    <p class="topicos-fecha">{{#dateFormat}} {{document.fields.recs-publishtime}} {{/dateFormat}}</p>
    <h4 class="topicos-titulo title-hover">{{document.fields.title}}</h4>
</a>
{{/matches}}
</script>
<?php endif; ?><!-- /if module_exists -->

<article class="cXenseParse mb3 node-<?php print $node->nid; ?> <?php print $classes; ?> clearfix"<?php print $attributes; ?>>
    <header>
        <?php if ( $unpublished ): ?>
            <p class="unpublished"><?php print t( 'Unpublished' ); ?></p>
        <?php endif; ?>
        
        <!-- imagen -->
        <?php if ( !empty( $node->field_image_portada ) ) : ?>
        <div class="topicos-banner spriteFull">
            <a class="topicos-banner-link" href="/topicos"></a>
            <span class="topicos-banner-leyenda">Encuentra aquí toda la información de:</span>
        </div>
        <img class="topicos-banner-image" src="<?php print get_image_style( $node->field_image_portada[LANGUAGE_NONE][0]['uri'], 'portada' ); ?>" alt="<?php print $title; ?>" title="<?php print $title; ?>" />
        <?php endif; ?>

    </header>
    
    <div id="contenido" class="mb2 clear">

        <div class="topicos-left-column cXenseParse">
            <!-- title -->
            <h1 class="topicos-banner-title" <?php print $title_attributes; ?>><?php print strip_tags( $node->title, '<i><em>' ); ?></h1>
            <!-- social -->
            <div id="topico-redes-sociales" class="mb2 clear">
                <div id="addthis-shares">
                    <!-- AddThis Button BEGIN -->
                    <div class="addthis_toolbox addthis_default_style addthis_32x32_style">
                        <a class="addthis_button_facebook_like" fb:like:href="<?php print(get_facebook_data_href($node->nid)); ?>"></a>
                        <a class="addthis_button_google_plusone" g:plusone:annotation="bubble"></a>
                    </div>
                    <!-- AddThis Button END -->
                </div>
            </div>
            <!-- bio -->
            <div class="topicos-bio">
                <ul>
                    <?php 
                    $i = 1;
                    foreach ( $wrapper->field_campos_bio as $campo ): ?>
                    <li class="topicos-bio-item<?php echo ($i%2 == 0)?" topicos-bio-item-even":" topicos-bio-item-odd"; ?>">
                        <h4 class="topicos-bio-titulo"><?php print( $campo->field_titulo_campo->value()); ?></h4>
                        <p class="topicos-bio-contenido"><?php print( $campo->field_contenido_campo->value() ); ?></p>
                    </li>
                    <?php 
                    $i++;
                    endforeach;?>
                </ul>
            </div>
        </div>

        <!-- body -->
        <div class="topicos-body cXenseParse">
            <?php print preg_replace("/^(<p>&nbsp;<\/p>)/", "", $wrapper->body->value->value( array( 'sanitize' => TRUE) ) ); ?>
        </div>
        
        <div class="clear topicos-top-ruler mb2"></div>

        <?php if(module_exists('excelsior_topicos')): ?><!-- if module_exists -->
        <!-- variables tópicos -->
        <?php 
        $p_aq = array();    
        foreach ( $wrapper->field_terminos_relacionados->value() as $keyword ){
            $keyword_array = array();
            preg_match("/(.*)--(.*)$/", $keyword, $keyword_array);
            $p_aq[] = 'query(' . $keyword_array[1] . ':"' . $keyword_array[2] . '")';
        }
        $main_query = "(" . implode(' or ', $p_aq) . ")"; ?>

        <!-- placeholder lo mas reciente -->
        <div class="mr2" id="topicos-tres-recientes">
            <?php
            $cxsTresRecientes = new cxSearch($cx_site_id);
            $cxsTresRecientes->p_aq = $main_query . ' and (query(imx-nodetype:"article") or query(imx-nodetype:"galery")) and query(url:"www.excelsior.com.mx")';
            $cxsTresRecientes->p_sm = 'recs-publishtime:desc';
            $cxsTresRecientes->callback = 'tresRecientesCallback';
            $cxsTresRecientes->p_c = '3';
            $cxsTresRecientes->p_dr='title';
            $cxrTresRecientes = $cxsTresRecientes->fetchResults($decoded = true);
            if(count($cxrTresRecientes->matches) > 0): ?>
            <h3 class="topicos-modulos-titulo spriteFull">Lo más reciente</h3>
            <div class="tfa-left">
                <ul>
            <?php foreach($cxrTresRecientes->matches as $match): ?>
                    <li class="top-front-artices-items">
                        <a class="" href="<?php print($match->document->fields->url); ?>">
                            <span class="image-block">
                                <img class="mb1" src="<?php print($match->document->fields->{'imx-img-portada'}); ?>" alt="<?php print($match->document->fields->title); ?>">
                                <span class="spriteIconos"></span>
                                <span class="spriteFull topicos-taxonomy-badge-<?php print($match->document->fields->{'kw-taxonomy'}); ?>"</span>
                            </span>
                            <span class="ntitle"><?php print($match->document->fields->title); ?></span>
                            <span>
                                <span class="ntime"><?php print(date('Y-m-d H:i',strtotime($match->document->fields->{'recs-publishtime'}))); ?></span>
                                <span class="ndescription"><?php print( truncate_utf8( (strlen($match->document->fields->{'og-description'}) > 0)?$match->document->fields->{'og-description'}:$match->document->fields->description ,150,TRUE,TRUE, 4)); ?></span>
                            </span>
                        </a>
                    </li>
            <?php endforeach; 
            endif; ?>
                </ul>
            </div>

        </div>

        <!-- placeholder no te pierdas -->
        <div class="" id="topicos-no-te-pierdas"></div>

        <div class="clear"></div>
        
        <!-- placeholder videos recientes -->
        <div class="" id="topicos-videos-recientes">
            <?php
            $cxsVideosRecientes = new cxSearch($cx_site_id);
            $cxsVideosRecientes->queryType = 'recs';
            $cxsVideosRecientes->matchingMode = 'trend';
            $cxsVideosRecientes->p_aq = $main_query . ' and query(imx-nodetype:"videogalery") and query(url:"www.excelsior.com.mx")';
            $cxsVideosRecientes->p_sm = 'recs-publishtime:desc';
            $cxsVideosRecientes->p_c = '4';
            $cxsVideosRecientes->p_dr='title';
            $cxrVideosRecientes = $cxsVideosRecientes->fetchResults(TRUE);
            ?>
            <?php if(count($cxrVideosRecientes->matches) > 0): ?>
            <h3 class="topicos-modulos-titulo spriteFull">Videos</h3>
            <?php foreach($cxrVideosRecientes->matches as $match): ?>
            <div class="topicos-nota-video mb2">
                <div class="topicos-nota-video-left spriteFull"></div>
                <iframe class="topicos-nota-video-iframe" width="296" height="222" wmode="opaque" src="https://www.youtube.com/embed/<?php print($match->document->fields->{'imx-vid-youtubeid'}); ?>" frameborder="0" allowfullscreen></iframe>
                <a href="<?php print($match->document->fields->url); ?>" class="topicos-nota-video-titulo"><?php print($match->document->fields->title); ?></a>
                <div class="topicos-nota-video-bottom spriteFull"></div>
            </div>
            <?php endforeach;
            endif; ?>
        </div>

        <!-- placeholder resto recientes -->
        <div class="" id="topicos-resto-recientes">
            <?php 
            $cxsRestoRecientes = new cxSearch($cx_site_id);
            $cxsRestoRecientes->p_aq = $main_query . ' and (query(imx-nodetype:"article") or query(imx-nodetype:"galery")) and query(url:"www.excelsior.com.mx")';
            $cxsRestoRecientes->p_sm = 'recs-publishtime:desc';
            $cxsRestoRecientes->p_dr='title';
            $cxsRestoRecientes->p_s = '3';
            $cxsRestoRecientes->p_c = '7';
            $cxrRestoRecientes = $cxsRestoRecientes->fetchResults(TRUE);   
            if(count($cxrRestoRecientes->matches) > 0):?>
            <h3 class="topicos-modulos-titulo spriteFull">Cronología</h3>
            <ul class="topicos-resto-recientes-list">
            <?php foreach($cxrRestoRecientes->matches as $match): ?>
                <li class="topicos-resto-recientes-list-item">
                    <a class="topicos-resto-recientes-list-item-link mb1" href="<?php print($match->document->fields->url); ?>">
                        <span class="topicos-resto-recientes-list-item-image">
                            <img class="mr1 mb1" src="<?php print($match->document->fields->{'imx-img-portada'}); ?>" alt="<?php print($match->document->fields->title); ?>">
                            <span class="spriteIconos"></span>
                            <span class="spriteFull topicos-taxonomy-badge-<?php print($match->document->fields->{'kw-taxonomy'}); ?>"></span>                    
                        </span>
                        <span class="topicos-resto-recientes-list-item-title"><?php print($match->document->fields->title); ?></span>
                        <span class="topicos-resto-recientes-list-item-time"><?php print(date('Y-m-d H:i',strtotime($match->document->fields->{'recs-publishtime'}))); ?></span>
                        <span class="topicos-resto-recientes-list-item-description"><?php print( truncate_utf8( (strlen($match->document->fields->{'og-description'}) > 0)?$match->document->fields->{'og-description'}:$match->document->fields->description ,150,TRUE,TRUE, 4)); ?></span>
                    </a>
                </li>
            <?php endforeach; 
            endif; ?>
            </ul>
        </div>
        <?php endif; ?><!-- /if module_exists -->
        <div class="clear"></div>
    </div>
</article><!-- /.node -->
<?php print render( $node_bottom );