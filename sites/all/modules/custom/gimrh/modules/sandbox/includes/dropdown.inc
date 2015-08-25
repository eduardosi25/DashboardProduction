<?php
/**
 * Function for generating form
 */
function sandbox_ajax_dropdown($form, &$form_state) {
  // Province dropdown list
  $form['sandbox_ajax_dropdown']['province'] = array(
    '#title' => t('Province'),
    '#type' => 'select',
    '#options' => _load_province(),
    '#ajax' => array(
      'event'=>'change',
      'callback' =>'sandbox_ajax_dropdown_city',
      'wrapper' => 'city-wrapper',
    ),
  );

  // Wrapper for city dropdown list
  $form['sandbox_ajax_dropdown']['wrapper'] = array(
    '#prefix' => '<div id="city-wrapper">',
    '#suffix' => '</div>',
  );

  // Options for city dropdown list
  $options = array('- Select city -');
  if (isset($form_state['values']['province'])) {
    // Pre-populate options for city dropdown list if province id is set
    $options = _load_city($form_state['values']['province']);
  }

  // Province dropdown list
  $form['sandbox_ajax_dropdown']['wrapper']['city'] = array(
    '#title' => t('City'),
    '#type' => 'select',
    '#options' => $options,
  );

  // Form submit button
  $form["sandbox_ajax_dropdown"]["submit"] = array(
    "#value"  => t("Submit"),
    "#type"   => "submit",
    "#submit" => array("sandbox_ajax_dropdown_submit"),
  );

  return $form;
}

/**
 * Function for handling form submission
 */
function sandbox_ajax_dropdown_submit($form, &$form_state) {
  $replacement = array(
    '@province_id' => $form_state['values']['province'],
    '@city_id' => $form_state['values']['city'],
  );

  drupal_set_message(t('Submitted data: Province ID = @province_id, City ID = @city_id.', $replacement));
}

/**
 * Function for handling ajax request
 */
function sandbox_ajax_dropdown_city($form, $form_state) {
  // Return the dropdown list including the wrapper
  var_dump($form['sandbox_ajax_dropdown']['wrapper']);
  die(__FUNCTION__);
  return $form['sandbox_ajax_dropdown']['wrapper'];
}

/**
 * Function for populating province
 */
function _load_province() {
  $province = array('- Select province -');

  // Select table
  $query = db_select("sandbox_province", "a");
  // Selected fields
  $query->fields("a", array('id', 'name'));
  // Filter the active ones only
  $query->condition("a.status", 1);
  // Order by name
  $query->orderBy("a.name");
  // Execute query
  $result = $query->execute();

  while($row = $result->fetchObject()){
    // Key-value pair for dropdown options
    $province[$row->id] = $row->name;
  }

  return $province;
}

/**
 * Function for populating city
 */
function _load_city($province_id) {
  $city = array('- Select city -');

  // Select table
  $query = db_select("sandbox_city", "a");
  // Selected fields
  $query->fields("a", array('id', 'name'));
  // Filter the active ones only
  $query->condition("a.status", 1);
  // Filter based province id
  $query->condition("a.province_id", $province_id);
  // Order by name
  $query->orderBy("a.name");
  // Execute query
  $result = $query->execute();

  while($row = $result->fetchObject()){
    // Key-value pair for dropdown options
    $city[$row->id] = $row->name;
  }

  return $city;
}
