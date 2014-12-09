<?php

/**
 * @file
 * The PHP page that serves all page requests on a Drupal installation.
 *
 * The routines here dispatch control to the appropriate handler, which then
 * prints the appropriate page.
 *
 * All Drupal code is released under the GNU General Public License.
 * See COPYRIGHT.txt and LICENSE.txt.
 */

/**
 * Root directory of Drupal installation.
 */
define('DRUPAL_ROOT', getcwd());

require_once DRUPAL_ROOT . '/includes/bootstrap.inc';
drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);

//Admin paths
$paths=array(
  'admin/*',
  'node/*/*',
  'login',
  '*/ajax/*',
  '*/ahah/*',
);

if(drupal_match_path($_GET['q'],$paths)){
  menu_execute_active_handler();
}else{
  require_once(DRUPAL_ROOT.'/web/index.php');
}
