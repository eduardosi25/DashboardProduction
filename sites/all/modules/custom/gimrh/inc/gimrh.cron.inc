<?php
set_include_path(DRUPAL_ROOT.'/sites/all/libraries/google-api-php/vendor/google/apiclient/src/' . PATH_SEPARATOR . get_include_path());
require_once 'Google/Client.php';
require_once 'Google/Service/Drive.php';


function gimrh_cronlt(){
  global $gimrh_variables;
  if($gimrh_variables['debug']){
    writeSheet();
    return 'Done!';
  }else{
    return 'Debug mode not enabled. Nothing to do!';
  }
}


function writeSheet(){
  /**
   * API KEY: AIzaSyDNhzxvnpREp_mxkOKhd7UPQUqOvN-nhfo
   */

  # Load all libraries required
  #require_once("google-api-php/vendor/autoload.php");

  $client_id = '10099820695-rmhqt14o3sbnv7q5agpc0i4dqe06jsu2.apps.googleusercontent.com';
  $service_account_name = '10099820695-lu2j6rag865i9nd66dh7uc9rv884eht0@developer.gserviceaccount.com';
  $key_file_location = drupal_get_path('module','gimrh').'/inc/gim-rh-inventmx-key.p12';
  echo 'Access';
  if (strpos($client_id, "googleusercontent") == false
    || !strlen($service_account_name)
    || !strlen($key_file_location)) {
    echo 'Fail';
    exit;
  }
  $client = new Google_Client();
  $client->setApplicationName("Sheets API Testing");
  $service = new Google_Service_Drive($client);
  $key = file_get_contents($key_file_location);
  $cred = new Google_Auth_AssertionCredentials(
    $service_account_name,
    array('https://www.googleapis.com/auth/drive','https://spreadsheets.google.com/feeds'),
    $key
  );
  $client->setAssertionCredentials($cred);
  if ($client->getAuth()->isAccessTokenExpired()) {
    $client->getAuth()->refreshTokenWithAssertion($cred);
  }
  // Get access token for spreadsheets API calls
  $resultArray = json_decode($client->getAccessToken());
  $accessToken = $resultArray->access_token;
  // The file ID was copied from a URL while editing the sheet in Chrome
  $fileId = '1MfjoDkwzd7x3CWZV4OpHiT61WGGxqFDN0nJNc1eG460';
// Section 1: Uncomment to get file metadata with the drive service
// This is also the service that would be used to create a new spreadsheet file
//  $results = $service->files->get($fileId);
//  var_dump($results);
// Section 2: Uncomment to get list of worksheets
// $url = "https://spreadsheets.google.com/feeds/worksheets/$fileId/private/full";
// $method = 'GET';
// $headers = ["Authorization" => "Bearer $accessToken"];
// $req = new Google_Http_Request($url, $method, $headers);
// $curl = new Google_IO_Curl($client);
// $results = $curl->executeRequest($req);
// echo "$results[2]\n\n";
// echo "$results[0]\n";
// Section 3: Uncomment to get the table data
  $url = "https://spreadsheets.google.com/feeds/list/$fileId/od6/private/full";
  $method = 'GET';
  $headers = ["Authorization" => "Bearer $accessToken", "GData-Version" => "3.0"];
  $req = new Google_Http_Request($url, $method, $headers);
  $curl = new Google_IO_Curl($client);
  $results = $curl->executeRequest($req);

  var_dump($results);


  // Section 4: Uncomment to add a row to the sheet
  $url = "https://spreadsheets.google.com/feeds/list/$fileId/od6/private/full";
  $method = 'POST';
  $headers = ["Authorization" => "Bearer $accessToken", 'Content-Type' => 'application/atom+xml'];
  $postBody = '<entry xmlns="http://www.w3.org/2005/Atom" xmlns:gsx="http://schemas.google.com/spreadsheets/2006/extended"><gsx:gear>more gear</gsx:gear><gsx:quantity>99</gsx:quantity></entry>';
  $req = new Google_Http_Request($url, $method, $headers, $postBody);
  $curl = new Google_IO_Curl($client);
  $results = $curl->executeRequest($req);

  var_dump($results);

  die(__FUNCTION__);
}

