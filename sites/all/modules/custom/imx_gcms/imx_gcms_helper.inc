<?php

require_once('php-ga/src/autoload.php');
use UnitedPrototype\GoogleAnalytics;

/**
 * Función que regresa un array con todos los sitios en el API
 * $return array
 */

function getAPISites($filter = FALSE)
{
    //Filtramos los sitios de la configuración del módulo únicamente
    if ($filter) {
        $data_sitios         = variable_get("imx_api_site_relateds", FALSE);
        $sitios_relacionados = ($data_sitios) ? json_decode($data_sitios, TRUE) : FALSE;
        $sites_default       = array();
        if ($sitios_relacionados) {
            foreach ($sitios_relacionados as $site_rel) {
                if ($site_rel) {
                    $sites_default[] = trim($site_rel);
                }
            }
        }
    } else {
        $sites_default = array();
    }

    $custom_sites = (count($sites_default)) ? TRUE : FALSE;
    $sites        = array();
    $url          = IMX_API_BASE_URL . "/user/sites.json/" . IMX_API_TOKEN;
    $data         = @file_get_contents($url);
    $api_info     = json_decode($data, TRUE);
    if (count($api_info["data"])) {
        foreach ($api_info["data"] as $site) {
            if ($custom_sites) {
                $site["name"] = ($site["name"] == "Hub-InventMx") ? $site["name"] = "hub" : $site["name"];
                if (array_key_exists(strtolower($site["name"]), array_flip($sites_default))) {
                    if ($site["name"] == "hub") {
                        $sites["hub"] = "Hub-InventMx";
                    } else {
                        $sites[strtolower($site["name"])] = $site["name"];
                    }
                }
            } else {
                if ($site["name"] == "Hub-InventMx") {
                    $sites["hub"] = $site["name"];
                } else {
                    $sites[strtolower($site["name"])] = $site["name"];
                }
            }
        }
    }

    if (!count($sites)) {
        $message = t('No se puede cargar la información del API en este momento, intenta nuevamente en unos minutos.');
        drupal_set_message($message, "warning");
        //drupal_goto("admin/config/imx_gcms");
    }
    return $sites;

}

function getAPISiteRepos($site)
{
    $repos    = array();
    $url      = IMX_API_BASE_URL . "{$site}/repos.json/" . IMX_API_TOKEN;
    $data     = @file_get_contents($url);
    $api_info = json_decode($data, TRUE);
    if (count($api_info["data"])) {
        foreach ($api_info["data"] as $site) {
            if ($site["reponame"] != "node" && $site["reponame"] != "home" && $site["reponame"] != "tags") {
                $repos[] = array("reponame" => $site["reponame"], "title" => $site["title"], "description" => $site["description"], "update" => date("h:i:s d-m-Y", $site["update"]));
            }
        }
    }
    if (!count($repos)) {
        $message = t('No se puede cargar la información del API en este momento, intenta nuevamente en unos minutos.');
        drupal_set_message($message, "warning");
        drupal_goto("admin/config/imx_gcms");
    }
    return $repos;
}

function getAPISiteRepoContents($site, $repo, $filter = FALSE, $page = 1)
{
    $contents              = array();
    $query_string          = array();
    $query                 = "";
    $query_string["limit"] = 20;

    if ($page >= 1) {
        $page = $page - 1;
    }
    $offset                 = $page * $query_string["limit"];
    $query_string["offset"] = $offset;
    $query_string["fields"] = "id|title|url|type|taxonomy|created|changed|submitted|rec_source|hub_id";
    $query_string["type"]   = "article|gallerie|video|story|galery|videogallerie|galery|videos|blog|catalogo|videogalery";


    if ($site == "hub") {
        $repo = $filter["categories"];
    }

    if ($filter) {
        if ($filter["types"] && $filter["types"] != "Todos") {
            $query_string["type"] = $filter["types"];
        }
        if ($filter["categories"] && $filter["types"] != "Todas" && $site != "hub") {
            $query_string["category_ids"] = $filter["categories"];
        }
        if ($filter["site"]) {
            $site = $filter["site"];
        }
        if ($filter["search"]) {
            $query_string["query"] = $filter["search"];
            $repo                  = "search";
        }
    }

    $query = drupal_http_build_query($query_string);

    $url      = IMX_API_BASE_URL . "{$site}/{$repo}.json/" . IMX_API_TOKEN . "?" . $query;
    $data     = @file_get_contents($url);
    $api_info = json_decode($data, TRUE);
    if (count($api_info["data"])) {
        foreach ($api_info["data"] as $node) {
            $contents[] = $node;
        }
    }
    if (!count($contents)) {
        $message = t('No se encontrarón datos que mostrar con los parámetros seleccionados.');
        drupal_set_message($message, "warning");
        //drupal_goto("admin/config/imx_gcms");
    }
    return $contents;
}

function getAPISiteContent($site, $id, $format = "json")
{
    $param = "id=";
    if ($site == "hub") {
        $param = "hub_id=";
    }
    $limit    = 20;
    $contents = array();
    $url      = IMX_API_BASE_URL . "{$site}/node.{$format}/" . IMX_API_TOKEN . '?' . $param . $id;
    $data     = @file_get_contents($url);
    $api_info = json_decode($data, TRUE);
    if (count($api_info["data"])) {
        foreach ($api_info["data"] as $node) {
            $contents[] = $node;
        }
    }

    if (!count($contents)) {
        $message = t('No se puede cargar la información del API en este momento, intenta nuevamente en unos minutos.');
        drupal_set_message($message, "warning");
        drupal_goto("admin/config/imx_gcms");
    }
    return $contents[0];
}

function getAPISiteContentURL($site, $id, $format = "json")
{
    $contents = array();
    $param    = "id=";
    if ($site == "hub") {
        $param = "hub_id=";
    }
    $url = IMX_API_BASE_URL . "{$site}/node.{$format}/" . IMX_API_TOKEN . '?' . $param . $id;
    return $url;
}

function transfer_image_remote($image)
{
    $url      = $image["url"];
    $ch       = curl_init($url);
    $realpath = FALSE;
    $uri      = NULL;
    $file     = NULL;
    $filename = basename($url);
    if ($wrapper = file_stream_wrapper_get_instance_by_uri('public://')) {
        $realpath = $wrapper->realpath();
    }
    $realpath = drupal_realpath(file_default_scheme() . '://') . "/";
    if ($realpath) {
        $fp = fopen($realpath . $filename, 'wb');
        curl_setopt($ch, CURLOPT_FILE, $fp);
        curl_setopt($ch, CURLOPT_HEADER, 0);
        curl_setopt($ch, CURLOPT_FOLLOWLOCATION, TRUE);
        curl_exec($ch);
        curl_close($ch);
        fclose($fp);

        $uri         = "public://" . $filename;
        $handle      = fopen($realpath . $filename, 'r');
        $file        = file_save_data($handle, $uri, FILE_EXISTS_RENAME);
        $file->statu = 0;
        file_save($file);
        fclose($handle);
    }

    return $file;
}

function getNodeAPIType($node)
{
    if ($node["type"] == "story" || $node["type"] == "blog" || $node["type"] == "catalogo") {
        $type = "article";
    } elseif ($node["type"] == "gallery" || $node["type"] == "galery" || $node["type"] == "gallerie") {
        $type = "gallerie";
    } elseif ($node["type"] == "videogallery" || $node["type"] == "videogalery" || $node["type"] == "video" || $node["type"] == "videogallerie" || $node["type"] == "videos") {
        $type = "video";
    } else {
        $type = "article";
    }

    switch ($type) {
        case "article" :
            $type = IMX_GCMS_CONTENT_ARTICLE;
            break;
        case "gallerie" :
            $type = IMX_GCMS_CONTENT_GALLERIE;
            break;
        case "video" :
            $type = IMX_GCMS_CONTENT_VIDEO;
            break;
    }

    return $type;
}

function imx_gcms_insert_history_share($field = array())
{
    //Buscar NID previo si existe actualizar campos, sino insertar
    $result = db_select('imx_gcms_recs_history', 'n')
        ->fields('n')
        ->condition('nid', $field['nid'], '=')
        ->condition('site_dst', $field['site_dst'], '=')
        ->execute()
        ->fetchAssoc();
    if (!$result) {
        $result = db_insert('imx_gcms_recs_history')
            ->fields(array(
                'nid'      => $field['nid'],
                'uid'      => $field['uid'],
                'site_dst' => $field['site_dst'],
                'created'  => $field['created'],
            ))
            ->execute();
    } else {
        $result = db_update('imx_gcms_recs_history')
            ->fields(array(
                'nid'      => $field['nid'],
                'uid'      => $field['uid'],
                'site_dst' => $field['site_dst'],
                'created'  => $field['created'],
            ))
            ->condition('nid', $field['nid'], '=')
            ->condition('site_dst', $field['site_dst'], '=')
            ->execute();
    }

    if (!$result)
        return FALSE;

    return TRUE;
}

function imx_gcms_insert_history_import($field = array())
{
    //Buscar NID previo si existe actualizar campos, sino insertar
    $result = db_select('imx_gcms_imports_history', 'n')
        ->fields('n')
        ->condition('id_source', $field['id_source'], '=')
        ->condition('site_src', $field['site_src'], '=')
        ->execute()
        ->fetchAssoc();
    if (!$result) {
        $result = db_insert('imx_gcms_imports_history')
            ->fields(array(
                'id_source' => $field['id_source'],
                'id_dst'    => $field['id_dst'],
                'uid'       => $field['uid'],
                'site_src'  => $field['site_src'],
                'created'   => $field['created'],
            ))
            ->execute();
    }

    if (!$result)
        return FALSE;

    return TRUE;
}

function imx_gcms_insert_history_reject($field = array())
{
    //Buscar NID previo si existe actualizar campos, sino insertar
    $result = db_select('imx_gcms_reject_history', 'n')
        ->fields('n')
        ->condition('id_source', $field['id_source'], '=')
        ->condition('site_src', $field['site_src'], '=')
        ->execute()
        ->fetchAssoc();
    if (!$result) {
        $result = db_insert('imx_gcms_reject_history')
            ->fields(array(
                'id_source'    => $field['id_source'],
                'title_src' => $field['title_source'],
                'url_src'   => $field['url_source'],
                'uid'          => $field['uid'],
                'site_src'     => $field['site_src'],
                'created'      => $field['created'],
                'code'         => $field['code'],
            ))
            ->execute();
    }

    if (!$result)
        return FALSE;

    return TRUE;
}

function imx_gcms_check_item_import($id_source, $site_src)
{
    //Buscar NID previo si existe actualizar campos, sino insertar
    $result = db_select('imx_gcms_imports_history', 'n')
        ->fields('n')
        ->condition('id_source', $id_source, '=')
        ->condition('site_src', $site_src, '=')
        ->execute()
        ->fetchAssoc();
    if (!$result) {
        return FALSE;
    } else {
        return $result["id_dst"];
    }
}

function imx_gcms_check_item_reject($id_source, $site_src)
{
    //Buscar NID previo si existe actualizar campos, sino insertar
    $result = db_select('imx_gcms_reject_history', 'n')
        ->fields('n')
        ->condition('id_source', $id_source, '=')
        ->condition('site_src', $site_src, '=')
        ->execute()
        ->fetchAssoc();
    if (!$result) {
        return FALSE;
    } else {
        return TRUE;
    }
}

function imx_gcms_count_imports_today()
{
    //Buscar NID previo si existe actualizar campos, sino insertar
    $result = db_select('imx_gcms_imports_history', 'n')
        ->fields('n', array("id_source"))
        ->where("FROM_UNIXTIME(created,'%y%m%d')=:date", array(':date' => date("Y-m-d", time())))
        ->execute();
    if (!$result) {
        return 0;
    } else {
        return $result->rowCount();
    }
}

function imx_gcms_register_ga_event($category, $action, $label, $value, $site_dst = FALSE)
{
    //Variable generada por el modulo de GA
    $ga_account       = variable_get("googleanalytics_account", FALSE);
    $ga_account_extra = FALSE;
    if ($ga_account && $category != "CNI:Recs Published" && $category != "CNI:Recs-Nids Published") {
        //Registro de la analitica del API
        $tracker = new GoogleAnalytics\Tracker($ga_account, $_SERVER['HTTP_HOST']);
        $visitor = new GoogleAnalytics\Visitor();
        $visitor->fromServerVar($_SERVER);
        $session = new GoogleAnalytics\Session();
        $event   = new GoogleAnalytics\Event($category, $action, $label, $value);
        $tracker->trackEvent($event, $session, $visitor);
    }


    //Registramos en INVENTMX Domain
    switch ($category) {
        case "CNI:Contents Imports":
            //Cuenta InventMX
            $ga_account_extra = array("account" => "UA-15985397-3", "domain" => "inventmx.com");
            break;

        case "CNI:Contents-Nids Imports":
            //Cuenta InventMX
            $ga_account_extra = array("account" => "UA-15985397-3", "domain" => "inventmx.com");
            break;

        case "CNI:Contents Shared":
            //Cuenta InventMX
            $ga_account_extra = array("account" => "UA-15985397-3", "domain" => "inventmx.com");
            break;

        case "CNI:Recs Published":
            if ($site_dst) {
                $ga_account_extra = getAccountGA($site_dst);
            }
            break;

        case "CNI:Recs-Nids Published":
            if ($site_dst) {
                $ga_account_extra = getAccountGA($site_dst);
            }
            break;
    }

    if ($ga_account_extra) {
        $tracker = new GoogleAnalytics\Tracker($ga_account_extra["account"], $ga_account_extra["domain"]);
        $visitor = new GoogleAnalytics\Visitor();
        $visitor->fromServerVar($_SERVER);
        $session = new GoogleAnalytics\Session();
        $event   = new GoogleAnalytics\Event($category, $action, $label, $value);
        $tracker->trackEvent($event, $session, $visitor);
    }
}

function getAccountGA($site)
{
    $site = str_replace("www.", "", $site);
    $site = str_replace(".com", "", $site);
    $site = str_replace(".mx", "", $site);

    $ga = FALSE;

    $ga_accounts = array(
        "actitudfem"     => array("account" => "UA-15985397-4", "domain" => "actitudfem.com"),
        "salud180"       => array("account" => "UA-15985397-2", "domain" => "salud180.com"),
        "dineroenimagen" => array("account" => "UA-15985397-15", "domain" => "dineroenimagen.com"),
        "excelsior"      => array("account" => "UA-3403383-1", "domain" => "excelsior.com.mx"),
        "imagen"         => array("account" => "UA-5000378-1", "domain" => "imagen.com.mx"),
        "reporte"        => array("account" => "UA-3403383-2", "domain" => "reporte.mx"),
        "melodijolola"   => array("account" => "UA-15985397-16", "domain" => "melodijolola.com"),
        "rsvponline"     => array("account" => "UA-15985397-10", "domain" => "rsvponline.mx"),
        "garuyo"         => array("account" => "UA-15985397-9", "domain" => "garuyo.com"),
        "swagger"        => array("account" => "UA-15985397-17", "domain" => "swagger.mx"),
        "atraccion360"   => array("account" => "UA-15985397-12", "domaun" => "atraccion360.com"),
        "gamedots"       => array("account" => "UA-15985397-11", "domain" => "gamedots.mx"),
    );

    if (array_key_exists($site, $ga_accounts)) {
        $ga = $ga_accounts[$site];
    }

    return $ga;
}

function getGCMSRelateds()
{
    $nodes                   = FALSE;
    $node                    = menu_get_object();
    $relacionados_sindicados = FALSE;

    if (variable_get("imx_gcms_field_relateds", FALSE)) {
        if (field_info_instance('node', variable_get("imx_gcms_field_relateds"), $node->type)) {
            $relacionados_sindicados = field_get_items('node', $node, variable_get("imx_gcms_field_relateds"));
        }
    }

    if ($relacionados_sindicados) {
        $nodes = array();
        foreach ($relacionados_sindicados as $item) {
            $title_field = variable_get("imx_gcms_field_relateds_title", FALSE);
            $url_field   = variable_get("imx_gcms_field_relateds_url", FALSE);
            $fc          = field_collection_item_load($item["value"]);
            if ($title_field && $url_field) {
                if (isset($fc->{$title_field}["und"][0]["value"]) && isset($fc->{$url_field}["und"][0]["value"])) {
                    $nodes[] = array(
                        'nid'       => FALSE,
                        'title'     => $fc->{$title_field}["und"][0]["value"],
                        'type'      => FALSE,
                        'url'       => $fc->{$url_field}["und"][0]["value"],
                        'image_uri' => FALSE,
                        'gcms'      => TRUE,
                    );
                }
            }
        }
    }

    return $nodes;
}