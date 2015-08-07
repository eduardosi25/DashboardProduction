<?php
/**
 * @file flag_lists_handler_filter_list.inc
 * Filter by flag lists
 *
 * https://api.drupal.org/api/examples/ajax_example!ajax_example_autocomplete.inc/7
 */
class flag_lists_handler_filter_list extends views_handler_filter_string {

function value_form(&$form, &$form_state) {
  parent::value_form($form, $form_state);

  if ( $form['value']['#type'] == 'textfield') {
    $form['value']['#autocomplete_path'] = 
      'flag-lists/autocomplete_list_callback';
  }

}

}
