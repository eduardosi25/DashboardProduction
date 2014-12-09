<?php
/************************************************
Start coding
 ************************************************/
# Constant values for Script config Execution
const REDIRECT_URL  = 'http://www.rsvponline.mx';
const CLIENT_ID     = '768389817374-brv4emp5b3dehs0k2tn7ltdb20d5es71.apps.googleusercontent.com';
const CLIENT_EMAIL  = '768389817374-brv4emp5b3dehs0k2tn7ltdb20d5es71@developer.gserviceaccount.com';
const CLIENT_SECRET = 'notasecret';
const PUBLIC_KEY    = 'ba902fccb95e1e4dee1ebabdcd8eb48faefc7688';
const API_KEY       = 'AIzaSyCJUNiSCQ0JG2ageSG5P6wq3aOigcitZU8';
const APP_NAME      = 'Test';
const KEY_FILE      = './GA-IMX-USERS-ANALYTICS-ba902fccb95e.p12';
const GA_SCOPE_FULL = 'https://www.googleapis.com/auth/analytics';
const GA_SCOPE_READ = 'https://www.googleapis.com/auth/analytics.readonly';
# The file name of this page. Used to create various query parameters to control script execution.
const THIS_PAGE     = 'index.php';
const OFFLINE_ACCESS = 'offline_access';

if (!CLIENT_ID || !CLIENT_EMAIL || !KEY_FILE) {
  echo missingServiceAccountDetailsWarning();
}
/************************************************
Make a simple API request using a key. In this
example we're not making a request as a
specific user, but simply indicating that the
request comes from our application, and hence
should use our quota, which is higher than the
anonymous quota (which is limited per IP).
 ************************************************/
set_include_path("google-api-php/vendor/google/apiclient/src/" . PATH_SEPARATOR . get_include_path());
require_once 'Google/Client.php';
require_once 'Google/Service/Analytics.php';

# Load all libraries required
#require("google-api-php/vendor/autoload.php");

/************************************************
We create the client and set the simple API
access key. If you comment out the call to
setDeveloperKey, the request may still succeed
using the anonymous quota.
 ************************************************/
$client = new Google_Client();
$client->setApplicationName(APP_NAME);
$client->setClientId(CLIENT_ID);
$client->setClientSecret(CLIENT_SECRET);
$client->setRedirectUri(THIS_PAGE);
$client->setAccessType(OFFLINE_ACCESS);
#$client->setDeveloperKey(API_KEY);
$client->addScope(GA_SCOPE_FULL);
$client->addScope(GA_SCOPE_READ);

/************************************************
If we have an access token, we can carry on.
Otherwise, we'll get one with the help of an
assertion credential. In other examples the list
of scopes was managed by the Client, but here
we have to list them manually. We also supply
the service account
 ************************************************/
if (isset($_SESSION['service_token'])) {
  $client->setAccessToken($_SESSION['service_token']);
}
# Credentials
$privateKey=file_get_contents(KEY_FILE);
$credentials=new Google_Auth_AssertionCredentials(
  CLIENT_EMAIL,
  array(GA_SCOPE_READ),
  $privateKey
);
$client->setAssertionCredentials($credentials);
$client->getAuth()->refreshTokenWithAssertion($credentials);
if($client->getAuth()->isAccessTokenExpired()) {
  $client->getAuth()->refreshTokenWithAssertion($credentials);
}
$_SESSION['service_token'] = $client->getAccessToken();

# Do service
$service = new Google_Service_Analytics($client);
$config=array(
  'ids'       => 'ga:54331725',
  'startDate' => date('Y-m-d', strtotime('-1 month')),
  'endDate'   => date('Y-m-d', strtotime('-1 day')),
  //'metrics'   => 'ga:pageviews,ga:pageviewsPerSession,ga:uniquePageviews,ga:avgTimeOnPage,ga:sessions,ga:avgSessionDuration',
  'metrics'   => 'ga:sessions,ga:pageviews,ga:uniquePageviews,ga:timeOnPage,ga:sessionDuration,ga:exits,ga:avgSessionDuration,ga:pageviewsPerSession,ga:avgTimeOnPage',
  'optParams' => array(
    'dimensions'  => 'ga:pagePath',
    'filters'     => 'ga:pagePath=~^/must/10-disfraces-ingeniosos-para-halloween',
    'start-index' => 1,
    'max-results' => 100,
  ),
);

# Do query
try {
  var_dump($config);
  $results = $service->data_ga->get($config['ids'], $config['startDate'], $config['endDate'], $config['metrics'],$config['optParams']);
  var_dump($results);
} catch(Exception $e) {
  echo 'There was an error : - ' . $e->getMessage();
}

die();

echo pageFooter(__FILE__);
