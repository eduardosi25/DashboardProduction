<?php
/**
 * @file
 * invent-search-form-wrapper.func.php
 */

/**
 * Theme function implementation for invent_search_form_wrapper.
 */
function invent_invent_search_form_wrapper($variables) {
  $output = '<div class="input-group">';
  $output .= $variables['element']['#children'];
  $output .= '<span class="input-group-btn">';
  $output .= '<button type="submit" class="btn btn-default">';
  // We can be sure that the font icons exist in CDN.
  if (theme_get_setting('invent_cdn')) {
    $output .= _invent_icon('search');
  }
  else {
    $output .= t('Search');
  }
  $output .= '</button>';
  $output .= '</span>';
  $output .= '</div>';
  return $output;
}
