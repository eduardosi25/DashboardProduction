<?php

/**
 * Returns a form for default dax
 * configuration settings
 *
 * @return array
 */
function dax_admin_settings_form() {
    $form['#attached']['js'] = array(
        'data' => drupal_get_path('module', 'dax') . '/js/dax.js',
    );

    $form['default'] = array(
        '#type' => 'fieldset',
        '#title' => t('Configuración Predeterminada'),
        '#collapsible' => TRUE,
        '#collapsed' => FALSE,
    );

//  $form['default']['dax_base_url'] = array(
//    '#type' => 'textfield',
//    '#title' => t('Base url'),
//    '#description' => t('The Digital Analytix base url.<br/> (<em>for example: <strong>b</strong>.scorecardresearch.com/p?</em>)'),
//    '#default_value' => variable_get('dax_base_url', ''),
//    '#required' => TRUE,
//  );
//  $form['default']['dax_country_code'] = array(
//    '#type' => 'textfield',
//    '#title' => t('Country Code'),
//    '#description' => t('The Digital Analytix Country Code.<br/> (<em>for example: <strong>mx</strong></em>)'),
//    '#default_value' => variable_get('dax_country_code', ''),
//    '#required' => TRUE,
//  );

    $form['default']['dax_client_name'] = array(
        '#type' => 'textfield',
        '#title' => t('Clave del Cliente C2'),
        '#description' => t('La clave de cliente Digital Analytix C2, brindada por su consultor comScore.<br/> (<em>por ejemplo: <strong>12345678</strong></em>)'),
        '#default_value' => variable_get('dax_client_name', ''),
        '#required' => TRUE,
    );

    $form['default']['dax_site_name'] = array(
        '#type' => 'textfield',
        '#title' => t('Identificador ns_site'),
        '#description' => t('El valor de identidad de sitio conocido como ns_site.<br/> (<em>por ejemplo: <strong>comscore-mx</strong></em>)'),
        '#default_value' => variable_get('dax_site_name', ''),
        '#required' => TRUE,
    );

    $form['countername'] = array(
        '#type' => 'fieldset',
        '#title' => t('Configuración name'),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
    );

    $form['countername']['dax_general_countername_generate_type'] = array(
        '#type' => 'radios',
        '#title' => t('Generación de name basado en:'),
        '#options' => array(
            'breadcrumbs' => t('Utilizando drupal breadcrumbs'),
//            'path' => t('Based on path url'),
//            'node_type_tokens' => t('Based on nodetype tokens')
        ),
        '#default_value' => variable_get('dax_general_countername_generate_type', 'breadcrumbs'),
    );

    if (variable_get('dax_general_countername_generate_type') !== 'breadcrumbs') {
        $form['countername']['node_type_tokens'] = array(
            '#type' => 'fieldset',
            '#collapsible' => FALSE,
            '#collapsed' => FALSE,
            '#prefix' => '<div id="dax-countername-node-type-settings">',
            '#suffix' => '</div>',
        );

        $form['countername']['node_type_tokens']['dax_node_types']['dax_general_node_type_settings'] = array(
            '#type' => 'textfield',
            '#title' => t('General countername settings'),
            '#description' => t('Assign a general countername for all content-types.  You can use tokens to make this more dynamic.'),
            '#default_value' => variable_get('dax_general_node_type_settings', ''),
            '#required' => FALSE,
        );

        $node_types = node_type_get_names();
        foreach ((array) $node_types as $key => $node_type) {
            $form['countername']['node_type_tokens']['dax_node_types']['dax_node_type_' . $key . '_settings'] = array(
                '#type' => 'textfield',
                '#title' => t('Countername settings !name', array('!name' => $node_type)),
                '#description' => t('Assign a countername to contenttype "<em>!content-type</em>".  You can use tokens.  If no countername is set fro this content-type, the general countername will be used.', array('!content-type' => $node_type)),
                '#default_value' => variable_get('dax_node_type_' . $key . '_settings', ''),
                '#required' => FALSE,
            );
        }

        $form['countername']['node_type_tokens']['tokens'] = array(
            '#theme' => 'token_tree',
            '#token_types' => array('node'),
        );


        $form['special_pages'] = array(
            '#type' => 'fieldset',
            '#title' => t('Special pages'),
            '#collapsible' => TRUE,
            '#collapsed' => TRUE,
        );
        $form['special_pages']['dax_frontpage_countername'] = array(
            '#type' => 'textfield',
            '#title' => t('Frontpage'),
            '#description' => t('Assign a countername for the frontpage.'),
            '#default_value' => variable_get('dax_frontpage_countername', ''),
            '#required' => FALSE,
        );

        $form['special_pages']['dax_error_403_settings'] = array(
            '#type' => 'textfield',
            '#title' => t('403 error'),
            '#description' => t('Assign a countername for all 403 pages.'),
            '#default_value' => variable_get('dax_error_403_settings', ''),
            '#required' => FALSE,
        );

        $form['special_pages']['dax_error_404_settings'] = array(
            '#type' => 'textfield',
            '#title' => t('404 error'),
            '#description' => t('Assign a countername for all 404 pages.'),
            '#default_value' => variable_get('dax_error_404_settings', ''),
            '#required' => FALSE,
        );

        $form['prefix_suffix'] = array(
            '#type' => 'fieldset',
            '#title' => t('Prefix & suffix'),
            '#collapsible' => TRUE,
            '#collapsed' => TRUE,
        );

        $form['prefix_suffix']['dax_prefix'] = array(
            '#type' => 'textfield',
            '#title' => t('Prefix'),
            '#description' => t('The prefix of each counter.<br/> (<em>for example: <strong>testcounter</strong></em>)'),
            '#default_value' => variable_get('dax_prefix', ''),
            '#required' => FALSE,
        );

        $form['prefix_suffix']['dax_suffix'] = array(
            '#type' => 'textfield',
            '#title' => t('Suffix'),
            '#description' => t('The suffix of each counter.<br/> (<em>for example: <strong>page</strong></em>)'),
            '#default_value' => variable_get('dax_suffix', ''),
            '#required' => FALSE,
        );


        $form['measurements'] = array(
            '#type' => 'fieldset',
            '#title' => t('Measurement types'),
            '#collapsible' => TRUE,
            '#collapsed' => TRUE,
        );

        $form['measurements']['normal']['dax_measurement_type_normal'] = array(
            '#type' => 'checkbox',
            '#title' => t('Normal'),
            '#description' => t('Select this measurement type for basic tracking'),
            '#default_value' => variable_get('dax_measurement_type_normal', 1),
            '#required' => FALSE,
        );

        $form['measurements']['technical'] = array(
            '#type' => 'fieldset',
            '#title' => '',
            '#collapsible' => FALSE,
            '#collapsed' => FALSE,
        );

        $form['measurements']['technical']['dax_measurement_type_technical'] = array(
            '#type' => 'checkbox',
            '#title' => t('Technical'),
            '#description' => t('Select this measurement type for technical tracking'),
            '#default_value' => variable_get('dax_measurement_type_technical', 1),
            '#required' => FALSE,
        );

        $form['measurements']['technical']['dax_measurement_type_technical_paths'] = array(
            '#type' => 'textarea',
            '#title' => t('Technical paths'),
            '#description' => t('Add all pages that should have technical tracking. Specify pages by using their paths. Each line represent a exclude. An * is permitted.'),
            '#default_value' => variable_get('dax_measurement_type_technical_paths', ''),
            '#required' => FALSE,
        );

        $form['measurements']['loading']['dax_measurement_type_loading'] = array(
            '#type' => 'checkbox',
            '#title' => t('Loading time'),
            '#description' => t('Select this measurement type for loading time tracking'),
            '#default_value' => variable_get('dax_measurement_type_loading', 0),
            '#required' => FALSE,
        );

        $form['measurements']['click_in']['dax_measurement_type_click_in'] = array(
            '#type' => 'checkbox',
            '#title' => t('Click in'),
            '#description' => t('Select this measurement type for click in tracking'),
            '#default_value' => variable_get('dax_measurement_type_click_in', 0),
            '#required' => FALSE,
        );

        $form['measurements']['click_out']['dax_measurement_type_click_out'] = array(
            '#type' => 'checkbox',
            '#title' => t('Click out'),
            '#description' => t('Select this measurement type for click out tracking'),
            '#default_value' => variable_get('dax_measurement_type_click_out', 0),
            '#required' => FALSE,
        );

        $form['measurements']['click_out']['dax_measurement_type_pdf'] = array(
            '#type' => 'checkbox',
            '#title' => t('Pdf documents'),
            '#description' => t('Select this measurement type for Pdf documents tracking'),
            '#default_value' => variable_get('dax_measurement_type_pdf', 0),
            '#required' => FALSE,
        );

        $form['measurements']['click_out']['dax_measurement_type_campaigns'] = array(
            '#type' => 'checkbox',
            '#title' => t('Campaigns'),
            '#description' => t('Select this measurement type for campaign tracking'),
            '#default_value' => variable_get('dax_measurement_type_campaigns', 0),
            '#required' => FALSE,
        );
    }
    return system_settings_form($form);
}