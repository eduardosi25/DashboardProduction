<?php
/*******************************************************************************************
Make a simple API request using a key. In this example we're not making a request as a
specific user, but simply indicating that the request comes from our application, and hence
should use our quota, which is higher than the anonymous quota (which is limited per IP).
 *******************************************************************************************/
set_include_path(DRUPAL_ROOT.'/'.drupal_get_path('module','node_analytics').'/'."google-api-php/vendor/google/apiclient/src/" . PATH_SEPARATOR . get_include_path());
require_once 'Google/Client.php';
require_once 'Google/Service/Analytics.php';
# Load all libraries required
#require("google-api-php/vendor/autoload.php");
/*******************************************************************************************
We create the client and set the simple API access key. If you comment out the call to
setDeveloperKey, the request may still succeed using the anonymous quota.
 *******************************************************************************************/
$googleClient = new Google_Client();
$googleClient->setApplicationName($node_analytics['api']['APP_NAME']);
$googleClient->setClientId($node_analytics['api']['CLIENT_ID']);
$googleClient->setClientSecret($node_analytics['constants']['secret']);
$googleClient->setRedirectUri($node_analytics['constants']['script']);
$googleClient->setAccessType($node_analytics['constants']['mode']);
#$googleClient->setDeveloperKey($node_analytics['api']['API_KEY']);
$googleClient->addScope($node_analytics['api']['GA_SCOPE_FULL']);
$googleClient->addScope($node_analytics['api']['GA_SCOPE_READ']);
/*******************************************************************************************
If we have an access token, we can carry on. Otherwise, we'll get one with the help of an
assertion credential. In other examples the list of scopes was managed by the Client, but here
we have to list them manually. We also supply the service account
 *******************************************************************************************/
if (isset($_SESSION['service_token'])) {
  $googleClient->setAccessToken($_SESSION['service_token']);
}
# Credentials
$privateKey=file_get_contents(DRUPAL_ROOT.'/'.drupal_get_path('module','node_analytics').'/keys/'.$node_analytics['api']['KEY_FILE']);
$googleCredentials=new Google_Auth_AssertionCredentials(
  $node_analytics['api']['CLIENT_EMAIL'],
  array($node_analytics['api']['GA_SCOPE_READ']),
  $privateKey
);
$googleClient->setAssertionCredentials($googleCredentials);
$googleClient->getAuth()->refreshTokenWithAssertion($googleCredentials);
if($googleClient->getAuth()->isAccessTokenExpired()) {
  $googleClient->getAuth()->refreshTokenWithAssertion($googleCredentials);
}
$_SESSION['service_token'] = $googleClient->getAccessToken();
/*******************************************************************************************
Do service
 *******************************************************************************************/
$googleServiceAnalytics = new Google_Service_Analytics($googleClient);
