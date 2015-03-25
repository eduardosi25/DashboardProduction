<?php
/**
 * @file
 * invent-accordion.func.php
 * @todo replace this with invent_panel?
 */

/**
 * Implements theme_invent_bare().
 */
function invent_invent_accordion($variables) {
  $elements = $variables['elements'];

  if (empty($variables['id'])) {
    $accordion_id = 'accordion-' . md5($elements);
  }
  else {
    $accordion_id = check_plain($variables['id']);
  }
  $output = '<div class="accordion" id="' . $accordion_id . '">';
  foreach ($elements as $id => $item) {
    $output .= '<div class="accordion-group"><div class="accordion-heading">';
    $output .= '<a class="accordion-toggle" data-toggle="collapse" data-parent="#' . $accordion_id . '" href="#' . $id . '">' . check_plain($item['header']) . '</a></div>';
    $output .= '<div id="' . $id . '" class="accordion-body collapse in"><div class="accordion-inner">';
    $output .= render($item['content']);
    $output .= '</div></div></div>';
  }
  $output .= '</div>';
  return $output;
}
