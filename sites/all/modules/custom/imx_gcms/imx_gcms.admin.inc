<?php

/**
 * @file
 * Administrative page callbacks for the imx_ads module.
 */

/**
 * Implements hook_admin_settings() for module settings configuration.
 */
function imx_gcms_admin_settings_form($form, &$form_state, $no_js_use = FALSE) {

    $form['description'] = array(
        '#markup' => '<div>' . t('Configuracion de IMX GCMS</div>')
    );

    $form['#tree'] = TRUE;
    $form["#rebuild"] = TRUE;
    $form_state['no_cache'] = true;


    $form['general'] = array(
        '#type' => 'fieldset',
        // Set up the wrapper so that AJAX will be able to replace the fieldset.
        '#prefix' => '<div id="block_info">',
        '#title' => 'Configuración general',
        '#suffix' => '</div>',
    );

    $form['general']["imx_api_base_url"] = array(
        '#type' => 'textfield',
        '#required' => true,
        '#title' => t("URL base de InventMx API:"),
        "#size"=>100,
        '#default_value' => variable_get("imx_gcms_api_base_url","http://api.inventmx.com/v1/")
    );

    $form['general']["imx_api_base_token"] = array(
        '#type' => 'textfield',
        '#required' => true,
        '#title' => t("Access Token de InventMx API:"),
        "#size"=>100,
        '#default_value' => variable_get("imx_gcms_api_token","")
    );

    $form['general']["imx_api_site_defaut"] = array(
        '#type' => 'select',
        '#required' => false,
        '#options' => getAPISites(),
        '#title' => t("Sitio por default"),
        '#default_value' => variable_get("imx_gcms_api_site_default","")
    );


    $form['general']["imx_api_site_relateds"] = array(
        '#type' => 'checkboxes',
        '#required' => false,
        '#options' => getAPISites(),
        '#title' => t("Sitios relacionados"),
        '#default_value' => json_decode(variable_get("imx_api_site_relateds",array()),true)
    );


    $form['general']["imx_api_max_recs"] = array(
        '#type' => 'select',
        '#required' => false,
        '#options' => range(0,20),
        '#title' => t("Recomendaciones por día:"),
        '#default_value' => variable_get("imx_api_max_recs",10)-1
    );


    $form['general']["imx_api_queue_dns"] = array(
        '#type' => 'textfield',
        '#required' => true,
        '#title' => t("DNS de BeansTalk API InventMX:"),
        "#size"=>100,
        '#default_value' => variable_get("imx_api_queue_dns","api.inventmx.com")
    );

    $form['general']["imx_api_queue_port"] = array(
        '#type' => 'textfield',
        '#required' => true,
        '#title' => t("Puerto de BeansTalk API InventMX:"),
        "#size"=>100,
        '#default_value' => variable_get("imx_api_queue_port","11300")
    );

    $form['data_fields'] = array(
        '#type' => 'fieldset',
        // Set up the wrapper so that AJAX will be able to replace the fieldset.
        '#prefix' => '<div id="block_info">',
        '#title' => 'Mapeo de campos',
        '#suffix' => '</div>',
    );



    $form['data_fields']["tags_field"] = array(
        '#type' => 'checkboxes',
        '#options' => array(1 => t('Sí')),
        '#title' => t('¿Importar tags?'),
        '#default_value' => array(variable_get("imx_gcms_field_tags",0))
    );

    $form['data_fields']["v_tags"] = array(
        '#type' => 'select',
        '#title' => t("Vocabulario de Tags"),
        '#options' => getVocabulary_tags(),
        '#default_value' => variable_get("imx_gcms_field_v_tags",0)
    );

    $form['data_fields']["image_field"] = array(
        '#type' => 'textfield',
        '#required' => true,
        '#title' => t("Nombre del campo de Imagen principal:"),
        "#size"=>100,
        '#default_value' => variable_get("imx_gcms_field_image",false)
    );


    $form['data_fields']["images_field"] = array(
        '#type' => 'textfield',
        '#required' => true,
        '#title' => t("Nombre del campo de Fotogalería (NA para ninguno):"),
        "#size"=>100,
        '#default_value' => variable_get("imx_gcms_field_images",false)
    );

    $form['data_fields']["video_field"] = array(
        '#type' => 'textfield',
        '#required' => true,
        '#title' => t("Nombre del fieldCollection de videos (NA para ninguno):"),
        "#size"=>100,
        '#default_value' => variable_get("imx_gcms_field_video",false)
    );

    $form['data_fields']["video_url_field"] = array(
        '#type' => 'textfield',
        '#required' => true,
        '#title' => t("Nombre del campo de url de videos (NA para ninguno):"),
        "#size"=>100,
        '#default_value' => variable_get("imx_gcms_field_video_url",false)
    );

    $form['data_fields']["video_desc_field"] = array(
        '#type' => 'textfield',
        '#required' => true,
        '#title' => t("Nombre del campo de descripción video (NA para ninguno):"),
        "#size"=>100,
        '#default_value' => variable_get("imx_gcms_field_video_desc",false)
    );

    $form['data_fields']["autor_field"] = array(
        '#type' => 'textfield',
        '#required' => true,
        '#title' => t("Nombre del campo para autor:"),
        "#size"=>100,
        '#default_value' => variable_get("imx_gcms_field_autor",false)
    );

    $form['data_fields']["relateds_field"] = array(
        '#type' => 'textfield',
        '#required' => true,
        '#title' => t("Nombre del fieldCollection de contenidos relacionados (NA para ninguno):"),
        "#size"=>100,
        '#default_value' => variable_get("imx_gcms_field_relateds",false)
    );


    $form['data_fields']["relateds_url_field"] = array(
        '#type' => 'textfield',
        '#required' => true,
        '#title' => t("Nombre del campo de url de contenidos relacionados:"),
        "#size"=>100,
        '#default_value' => variable_get("imx_gcms_field_relateds_url",false)
    );

    $form['data_fields']["relateds_title_field"] = array(
        '#type' => 'textfield',
        '#required' => true,
        '#title' => t("Nombre del campo de titulo de contenidos relacionados(NA para ninguno):"),
        "#size"=>100,
        '#default_value' => variable_get("imx_gcms_field_relateds_title",false)
    );




    $form['content_types'] = array(
        '#type' => 'fieldset',
        // Set up the wrapper so that AJAX will be able to replace the fieldset.
        '#prefix' => '<div id="block_info">',
        '#title' => 'Mapeo de tipos de contenido',
        '#suffix' => '</div>',
    );

    $form['content_types']["content_article"] = array(
        '#type' => 'textfield',
        '#required' => true,
        '#title' => t("Tipo de contenido para Article:"),
        "#size"=>100,
        '#default_value' => variable_get("imx_gcms_content_article",false)
    );

    $form['content_types']["content_gallerie"] = array(
        '#type' => 'textfield',
        '#required' => true,
        '#title' => t("Tipo de contenido para Gallerie:"),
        "#size"=>100,
        '#default_value' => variable_get("imx_gcms_content_gallerie",false)
    );

    $form['content_types']["content_video"] = array(
        '#type' => 'textfield',
        '#required' => true,
        '#title' => t("Tipo de contenido para Video:"),
        "#size"=>100,
        '#default_value' => variable_get("imx_gcms_content_video",false)
    );

    $form["submit"] = array(
        '#type' => "submit",
        "#value" => "Guardar configuración"
    );


    return $form;
}

function imx_gcms_admin_settings_form_submit($form, &$form_state) {
    $base_url=$form_state["values"]['general']["imx_api_base_url"];
    $access_token=$form_state["values"]['general']["imx_api_base_token"];
    $site=$form_state["values"]['general']["imx_api_site_defaut"];
    $site_rel=$form_state["values"]['general']["imx_api_site_relateds"];
    $dns=$form_state["values"]['general']["imx_api_queue_dns"];
    $port=$form_state["values"]['general']["imx_api_queue_port"];
    $max_recs=$form_state["values"]['general']["imx_api_max_recs"]+1;



    $field_tags=$form_state["values"]['data_fields']["tags_field"][1];
    $v_tags=$form_state["values"]['data_fields']["v_tags"];

    $field_image=$form_state["values"]['data_fields']["image_field"];
    $field_images=$form_state["values"]['data_fields']["images_field"];
    $field_video=$form_state["values"]['data_fields']["video_field"];
    $field_video_url=$form_state["values"]['data_fields']["video_url_field"];
    $field_video_desc=$form_state["values"]['data_fields']["video_desc_field"];
    $field_autor=$form_state["values"]['data_fields']["autor_field"];


    $field_relateds=$form_state["values"]['data_fields']["relateds_field"];
    $field_relateds_url=$form_state["values"]['data_fields']["relateds_url_field"];
    $field_relateds_title=$form_state["values"]['data_fields']["relateds_title_field"];



    $content_article=$form_state["values"]['content_types']["content_article"];
    $content_gallerie=$form_state["values"]['content_types']["content_gallerie"];
    $content_video=$form_state["values"]['content_types']["content_video"];

    variable_set("imx_gcms_api_base_url",$base_url);
    variable_set("imx_gcms_api_token",$access_token);
    variable_set("imx_gcms_api_site_default",$site);
    variable_set("imx_api_site_relateds",json_encode($site_rel));
    variable_set("imx_api_queue_dns",$dns);
    variable_set("imx_api_queue_port",$port);
    variable_set("imx_api_max_recs",$max_recs);


    variable_set("imx_gcms_field_tags",$field_tags);
    variable_set("imx_gcms_field_v_tags",$v_tags);

    variable_set("imx_gcms_field_image",$field_image);
    variable_set("imx_gcms_field_images",$field_images);

    variable_set("imx_gcms_field_video",$field_video);
    variable_set("imx_gcms_field_video_url",$field_video_url);
    variable_set("imx_gcms_field_video_desc",$field_video_desc);
    variable_set("imx_gcms_field_autor",$field_autor);

    variable_set("imx_gcms_field_relateds",$field_relateds);
    variable_set("imx_gcms_field_relateds_url",$field_relateds_url);
    variable_set("imx_gcms_field_relateds_title",$field_relateds_title);



    variable_set("imx_gcms_content_article",$content_article);
    variable_set("imx_gcms_content_gallerie",$content_gallerie);
    variable_set("imx_gcms_content_video",$content_video);

    variable_set("imx_gcms_config",true);
    drupal_set_message("Configuración guardada con éxito");
}


function imx_gcms_recs_history_list(){
    $header = array(
        array(
            'data' => t('Title'),
            'field' => 'n.title',
        ),
        array(
            'data' => t('Site DST'),
            'field' => 'nh.site_dst',
        ),
        array(
            'data' => t('User sended'),
            'field' => 'nh.uid',
        ),
        array(
            'data' => t('Date'),
            'field' => 'n.created',
        ),
    );

    // Default ordering
    if (!isset($_GET['order']) && !isset($_GET['sort'])) {
        $_GET['order'] = t('Sended');
        $_GET['sort'] = 'DESC';
    }

    $query = db_select('imx_gcms_recs_history', 'nh')->extend('PagerDefault');
    $query->limit(20);
    $query->join('node', 'n', 'n.nid = nh.nid');
    $query->join('users', 'u', 'u.uid = nh.uid');
    $query->fields('nh', array('nid','site_dst', 'created'));
    $query->fields('n', array('title'));
    $query->fields('u', array('name'));
    $query->orderBy("created","DESC");
    $query = $query
        ->extend('TableSort')
        ->orderByHeader($header);
    $result = $query->execute();

    $rows = array();

    foreach ($result as $node) {
        $rows[] = array(
            l($node->title, "node/$node->nid"),
            ucfirst($node->site_dst),
            theme('username', array('account' => $node)),
            ($node->created ? format_date($node->created,'custom','d/m/y h:i') : '&nbsp;'),
        );
    }
    if (count($rows) && ($pager = theme('pager'))) {
        $rows[] = array(
            array(
                'data' => $pager,
                'colspan' => 6,
            ),
        );
    }
    $build['imx_gcms_recs_history'] = array(
        '#theme' => 'table',
        '#header' => $header,
        '#rows' => $rows,
        '#empty' => t('There are no IMx GCMS Recs info nodes.'),
    );
    return $build;

}

function imx_gcms_imports_history_list(){
    $header = array(
        array(
            'data' => t('Title SRC'),
            'field' => 'n.title',
        ),
        array(
            'data' => t('Sitio SRC'),
            'field' => 'nh.site_src',
        ),
        array(
            'data' => t('Titulo'),
            'field' => 'nh.uid',
        ),
        array(
            'data' => t('Importador'),
            'field' => 'nh.uid',
        ),
        array(
            'data' => t('Date'),
            'field' => 'n.created',
        ),

    );

    // Default ordering
    if (!isset($_GET['order']) && !isset($_GET['sort'])) {
        $_GET['order'] = t('Sended');
        $_GET['sort'] = 'DESC';
    }

    $query = db_select('imx_gcms_imports_history', 'nh')->extend('PagerDefault');
    $query->limit(20);
    $query->join('node', 'n', 'n.nid = nh.id_dst');
    $query->join('field_data_field_gcms_title_source', 'fts', 'n.nid = fts.entity_id');
    $query->join('users', 'u', 'u.uid = nh.uid');
    $query->fields('nh', array('id_dst','site_src', 'created'));
    $query->fields('n', array('title'));
    $query->fields('u', array('name'));
    $query->fields('fts',array('field_gcms_title_source_value'));
    $query->orderBy("created","DESC");
    $query = $query
        ->extend('TableSort')
        ->orderByHeader($header);
    $result = $query->execute();

    $rows = array();

    foreach ($result as $node) {
        $rows[] = array(
            $node->field_gcms_title_source_value,
            ucfirst($node->site_src),
            l($node->title, "node/$node->id_dst"),
            theme('username', array('account' => $node)),
            ($node->created ? format_date($node->created,'custom','d/m/y h:i') : '&nbsp;'),
        );
    }
    if (count($rows) && ($pager = theme('pager'))) {
        $rows[] = array(
            array(
                'data' => $pager,
                'colspan' => 6,
            ),
        );
    }
    $build['imx_gcms_recs_history'] = array(
        '#theme' => 'table',
        '#header' => $header,
        '#rows' => $rows,
        '#empty' => t('There are no IMx GCMS Recs info nodes.'),
    );
    return $build;

}

function imx_gcms_reject_list(){
    $header = array(
        array(
            'data' => t('Title SRC'),
            'field' => 'nh.title_source',
        ),
        array(
            'data' => t('Sitio SRC'),
            'field' => 'nh.site_src',
        ),
        array(
            'data' => t('Date'),
            'field' => 'nh.created',
        ),

    );

    // Default ordering
    if (!isset($_GET['order']) && !isset($_GET['sort'])) {
        $_GET['order'] = t('Sended');
        $_GET['sort'] = 'DESC';
    }

    $query = db_select('imx_gcms_reject_history', 'nh')->extend('PagerDefault');
    $query->limit(20);
    $query->fields('nh', array('site_src', 'created',"title_source","url_source"));
    $query->orderBy("created","DESC");
    $query = $query
        ->extend('TableSort')
        ->orderByHeader($header);
    $result = $query->execute();

    $rows = array();

    foreach ($result as $node) {
        $rows[] = array(
            l($node->title_source, "$node->url_source"),
            ucfirst($node->site_src),
            ($node->created ? format_date($node->created,'custom','d/m/y h:i') : '&nbsp;'),
        );
    }
    if (count($rows) && ($pager = theme('pager'))) {
        $rows[] = array(
            array(
                'data' => $pager,
                'colspan' => 6,
            ),
        );
    }
    $build['imx_gcms_rejects_history'] = array(
        '#theme' => 'table',
        '#header' => $header,
        '#rows' => $rows,
        '#empty' => t('There are no IMx GCMS Rejects info nodes.'),
    );
    return $build;

}

function getVocabulary_tags() {
    $v = array();
    $query = db_select("taxonomy_vocabulary", "tv");
    $query->fields('tv', array("vid", "name"));
    $result = $query->execute()->fetchAll();
    foreach ($result as $item) {
        $v[$item->vid] = $item->name;
    }
    return $v;
}