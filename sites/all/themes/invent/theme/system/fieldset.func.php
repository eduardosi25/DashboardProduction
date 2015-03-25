<?php
/**
 * @file
 * fieldset.func.php
 */

/**
 * Overrides theme_fieldset().
 */
function invent_fieldset($variables) {
  return theme('invent_panel', $variables);
}
