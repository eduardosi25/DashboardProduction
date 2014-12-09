<?php

/**
 * @file
 * Administrative page callbacks for the imx_ads module.
 */

/**
 * Implements hook_admin_settings() for module settings configuration.
 */
function imx_gcms_filter_form($form, &$form_state, $no_js_use = FALSE)
{


    $cid=false;
    $type=false;
    if(isset($_SESSION["imx_gcms"][arg(5)]["filters"])){
        $filter=$_SESSION["imx_gcms"][arg(5)]["filters"];
        if($filter["categories"]){
            $cid=$filter["categories"];
        }
        if($filter["types"]){
            $type=$filter["types"];
        }
        if($filter["search"]){
            $search=$filter["search"];
        }
    }
    $form["gmc_data_source"] = array(
        '#type' => 'select',
        '#title' => t("Fuente de contenidos:"),
        '#options' => array(1 => "Sitios InventMX", 2 => "Temáticas"),
        '#default_value' => array(1)
    );

    $form["gmc_site"] = array(
        '#type' => 'select',
        '#required' => false,
        '#options' => getAPISites(TRUE),
        '#attributes' => array(
            'class' => array('container-inline'), // change to just 'text' for Drupal 6
        ),
        '#ajax' => array(
            'event' => 'change',
            'callback' => 'ajax_get_category_site_callback',
            'wrapper' => 'sites-wrapper',
        ),
        "#default_value" => ($form_state['values']["gmc_site"]) ? $form_state['values']["gmc_site"] : arg(5),
        '#title' => t("Sitios de InventMX"),
    );

    $form["gmc_categories"] = array(
        '#type' => 'select',
        '#attributes' => array(
            'class' => array('container-inline'), // change to just 'text' for Drupal 6
        ),
        '#prefix' => '<div id="sites-wrapper">',
        '#suffix' => '</div>',
        '#options' => _load_categories( ($form_state['values']["gmc_site"]) ? $form_state['values']["gmc_site"] : arg(5)),
        "#default_value" => ($cid) ? $cid : "Todas",
        '#title' => t("Categorias"),
    );

    $form["gmc_types"] = array(
        '#type' => 'select',
        '#attributes' => array(
            'class' => array('container-inline'), // change to just 'text' for Drupal 6
        ),
        '#required' => false,
        '#options' => array("Todos"=>"Todos","article" => "Articulos", "video" => "Videogalerías", "gallerie" => "Fotogalerías"),
        '#title' => t("Tipos de contenidos"),
        "#default_value" => ($type) ? $type : "Todas",
    );

    $form["gmc_search"] = array(
        '#type' => 'textfield',
        '#size' => 60,
        '#attributes' => array(
            'class' => array('container-inline'), // change to just 'text' for Drupal 6
        ),
        '#required' => false,
        '#title' => t("Buscar:"),
        "#default_value" => $search,

    );

    $form["submit"] = array(
        '#type' => "submit",
        '#attributes' => array(
            'class' => array('container-inline'), // change to just 'text' for Drupal 6
        ),
        "#value" => "Filtrar contenidos"
    );

    $path = drupal_get_path('module', 'imx_gcms');
// Attach the CSS and JS to the form
    $form['#attached'] = array
    (
        'css' => array
        (
            'type' => 'file',
            'data' => $path . '/form_style.css',
        ),
        'js' => array
        (
            'type' => 'file',
            'data' => $path . '/imx_gcms.js',
        ),
    );


    return $form;
}

function imx_gcms_filter_form_submit($form, &$form_state)
{
    $filters=array();
    $cid=$form_state["values"]["gmc_categories"];
    $site=$form_state["values"]["gmc_site"];
    $type=$form_state["values"]["gmc_types"];
    $search=$form_state["values"]["gmc_search"];

    if($cid){
        if($cid!="Todas"){
            $filters["categories"]=$cid;
        }
    }
    if($site){
        $filters["site"]=$site;
    }
    if($type){
        if($type!="Todos"){
            $filters["types"]=$type;
        }
    }
    if($search){
        $filters["search"]=$search;
    }

    if(count($filters)){
        $_SESSION["imx_gcms"][$site]["filters"]=$filters;
    }
    drupal_goto("admin/config/imx_gcms/sites/repo/{$site}/nodes");


}

function ajax_get_category_site_callback($form, $form_state)
{
    return $form["gmc_categories"];
}

function _load_categories($site)
{
    $json_path="/categories.json/";
    $categories = array("Todas"=>"Todas");
    if($site=="hub"){
        $json_path="/repos.json/";
    }

    $url = IMX_API_BASE_URL . $site .$json_path. IMX_API_TOKEN;
    $data = file_get_contents($url);
    $data = json_decode($data, true);
    if (count($data["data"])) {
        foreach ($data["data"] as $category) {
            if($site!="hub"){
                $categories[$category["id"]] = $category["name"];
            }else{
                if($category["reponame"] !="node"){
                    $categories[$category["reponame"]] = $category["name"];
                }
            }

        }
    }
    return $categories;
}