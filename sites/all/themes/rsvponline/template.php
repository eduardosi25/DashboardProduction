<?php
/**
 * Implements hook_html_head_alter().
 * This will overwrite the default meta character type tag with HTML5 version.
 */
function rsvponline_html_head_alter(&$head_elements) {
  $head_elements['system_meta_content_type']['#attributes'] = array(
    'charset' => 'utf-8'
  );
}

/**
 * Insert themed breadcrumb page navigation at top of the node content.
 */
function rsvponline_breadcrumb($variables) {
  $breadcrumb = $variables['breadcrumb'];
  if (!empty($breadcrumb)) {
    // Use CSS to hide titile .element-invisible.
    $output = '<h2 class="element-invisible">' . t('You are here') . '</h2>';
    // comment below line to hide current page to breadcrumb
	$breadcrumb[] = drupal_get_title();
    $output .= '<nav class="breadcrumb">' . implode(' » ', $breadcrumb) . '</nav>';
    return $output;
  }
}

/**
 * Override or insert variables into the html template.
 */
function rsvponline_process_html(&$vars) {
  // Hook into color.module
  if (module_exists('color')) {
    _color_html_alter($vars);
  }
}

/**
 * Override or insert variables into the page template.
 */
function rsvponline_process_page(&$variables) {
  // Hook into color.module.
  if (module_exists('color')) {
    _color_page_alter($variables);
  }
 
}

/**
 * Override or insert variables into the html template.
 */
function rsvponline_preprocess_html(&$vars) {
  if(isset($vars['page']['body_scripts'])){
    $vars['body_scripts']=drupal_render($vars['page']['body_scripts']);
    if($vars['body_scripts']){
      $clearJS=strip_tags($vars['body_scripts'],'<script>');
      $clearJS=trim($clearJS);
      $clearJS=str_replace("\n", '', $clearJS);
      $vars['body_scripts']=$clearJS."\n";
    }
  }else{
    $vars['body_scripts']=FALSE;
  }

}

/**
 * Override or insert variables into the page template.
 */
function rsvponline_preprocess_page(&$vars) {
    if (isset($vars['main_menu'])) {
    $vars['main_menu'] = theme('links__system_main_menu', array(
      'links' => $vars['main_menu'],
      'attributes' => array(
        'class' => array('links', 'main-menu', 'clearfix'),
      ),
      'heading' => array(
        'text' => t('Main menu'),
        'level' => 'h2',
        'class' => array('element-invisible'),
      )
    ));
  }
  else {
    $vars['main_menu'] = FALSE;
  }
  if (isset($vars['secondary_menu'])) {
    $vars['secondary_menu'] = theme('links__system_secondary_menu', array(
      'links' => $vars['secondary_menu'],
      'attributes' => array(
        'class' => array('links', 'secondary-menu', 'clearfix'),
      ),
      'heading' => array(
        'text' => t('Secondary menu'),
        'level' => 'h2',
        'class' => array('element-invisible'),
      )
    ));
  }
  else {
    $vars['secondary_menu'] = FALSE;
  }
}

/**
 * Duplicate of theme_menu_local_tasks() but adds clearfix to tabs.
 */
function rsvponline_menu_local_tasks(&$variables) {
  $output = '';

  if (!empty($variables['primary'])) {
    $variables['primary']['#prefix'] = '<h2 class="element-invisible">' . t('Primary tabs') . '</h2>';
    $variables['primary']['#prefix'] .= '<ul class="tabs primary clearfix">';
    $variables['primary']['#suffix'] = '</ul>';
    $output .= drupal_render($variables['primary']);
  }
  if (!empty($variables['secondary'])) {
    $variables['secondary']['#prefix'] = '<h2 class="element-invisible">' . t('Secondary tabs') . '</h2>';
    $variables['secondary']['#prefix'] .= '<ul class="tabs secondary clearfix">';
    $variables['secondary']['#suffix'] = '</ul>';
    $output .= drupal_render($variables['secondary']);
  }
  return $output;
}

/**
 * Override or insert variables into the node template.
 */
function rsvponline_preprocess_node(&$variables) {
  $node = $variables['node'];
  if ($variables['view_mode'] == 'full' && node_is_page($variables['node'])) {
    $variables['classes_array'][] = 'node-full';
  }
}

function rsvponline_page_alter($page) {
  // <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1"/>
  /*
  $viewport = array(
    '#type' => 'html_tag',
    '#tag' => 'meta',
    '#attributes' => array(
    'name' =>  'viewport',
    'content' =>  'width=device-width, initial-scale=1, maximum-scale=1'
    )
  );
  */
  $metas=array(
    'MobileOptimized'  => array(
      '#type' => 'html_tag',
      '#tag' => 'meta',
      '#attributes' => array(
        'name' =>  'MobileOptimized',
        'content' =>  'width'
      ),
    ),
    'HandheldFriendly' => array(
      '#type' => 'html_tag',
      '#tag' => 'meta',
      '#attributes' => array(
        'name' =>  'HandheldFriendly',
        'content' =>  'true'
      ),
    ),
    'viewport'         => array(
      '#type' => 'html_tag',
      '#tag' => 'meta',
      '#attributes' => array(
        'name' =>  'viewport',
        'content' =>  'width=1024, initial-scale=1, maximum-scale=1'
      ),
    ),
  );
  
  foreach($metas as $key => $value){
    drupal_add_html_head($value, $key);
  }
}

/**
 * Add javascript files for front-page jquery slideshow.
 */
if (drupal_is_front_page()) {
  drupal_add_js(drupal_get_path('theme', 'rsvponline') . '/js/jquery.flexslider-min.js');
  drupal_add_js(drupal_get_path('theme', 'rsvponline') . '/js/slide.js');
}

function rsvponline_image_style($variables){
  // Determine the dimensions of the styled image. Responsive 100%
  $dimensions = array(
    'width' => $variables['width'],
    'height' => $variables['height'],
  );

  image_style_transform_dimensions($variables['style_name'], $dimensions);

  $variables['width'] = '100%';
  $variables['height'] = '100%';

  // Determine the URL for the styled image.
  $variables['path'] = image_style_url($variables['style_name'], $variables['path']);
  return theme('image', $variables);
}

function rsvponline_image($variables) {
  $attributes = $variables['attributes'];
  $fileUrl=file_create_url($variables['path']);

  //Lazy load images exceptions for some images styles
  $pattern="/(thumbnail|small)/i";
  if(preg_match($pattern,$fileUrl)){
    $attributes['src'] = $fileUrl;
  }else if(arg(0)=='rss.xml'){
    $attributes['src'] = $fileUrl;
  }else{
    $attributes['class'] = 'lazy';
    $attributes['data-original'] = $fileUrl;
  }

  foreach (array('width', 'height', 'alt', 'title') as $key) {
    if (isset($variables[$key])) {
      $attributes[$key] = $variables[$key];
    }
  }

  return '<img' . drupal_attributes($attributes) . ' />';
}
