<?php

define( 'DRUPAL_ROOT', '/var/www/html/rsvpd7' ); #root del proyecto

$_SERVER['HTTP_HOST'] = 'local.rsvponline.mx'; #alias del host
$_SERVER['SCRIPT_NAME'] = '/'.'multimedia_update.php';
$_SERVER['REMOTE_ADDR'] = '127.0.0.1';
$_SERVER['SERVER_SOFTWARE'] = NULL;
$_SERVER['REQUEST_METHOD']  = 'GET';
$_SERVER['QUERY_STRING']    = '';
$_SERVER['PHP_SELF']        = $_SERVER['REQUEST_URI'] = '/';
$_SERVER['HTTP_USER_AGENT'] = 'console';

require_once DRUPAL_ROOT . '/includes/bootstrap.inc';
drupal_bootstrap( DRUPAL_BOOTSTRAP_FULL );

excelsior_tv_update_gdata();
excelsior_tv_feed();
