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

// Same as error_reporting(E_ALL);
#error_reporting(E_ALL);
#ini_set("display_errors", 1);


/**
 * Root directory of Drupal installation.
 */
define('DRUPAL_ROOT', getcwd());
require_once DRUPAL_ROOT . '/includes/bootstrap.inc';
require_once DRUPAL_ROOT . '/invent.mx.config.inc';
#Load a bootstrap
drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);
#Check config
if(get_frontend_paths()){
  require_once(DRUPAL_ROOT.'/web/index.php');
}else if(get_cms_access()){
  menu_execute_active_handler();
}else{
  drupal_access_denied();
}
