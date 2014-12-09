<?php
/************************************************************************************************/
/* Require Zend Gdata Class
 * Only for use in this procedure
 */
$classPath=DRUPAL_ROOT.'/../class/zend/lib/'. PATH_SEPARATOR . get_include_path();
set_include_path($classPath);
require_once 'Zend/Loader.php';
/************************************************************************************************/

function zendGData($config=array()){
  
  if(!isset($config) || empty($config) || count($config)<=0){
    return null;
  }
  
  if(!isset($config['page']) || empty($config['page'])){
    $config['page']=1;
  }
  
  Zend_Loader::loadClass('Zend_Gdata_AuthSub');
  Zend_Loader::loadClass('Zend_Gdata_ClientLogin');
  Zend_Loader::loadClass('Zend_Http_Client');
  Zend_Loader::loadClass('Zend_Gdata_Spreadsheets');
  $service = Zend_Gdata_Spreadsheets::AUTH_SERVICE_NAME;
  try{
    $client = Zend_Gdata_ClientLogin::getHttpClient($config['user'], $config['pass'], $service);
  }catch( Zend_Gdata_App_Exception $ex){
    die($ex->getMessage());
  }catch(Zend_Gdata_App_HttpException $httpEx){
    die($httpEx->getMessage);
  }
  $spreadSheet = new Zend_Gdata_Spreadsheets($client);
  $dataSheet = new Zend_Gdata_Spreadsheets_ListQuery();
  $dataSheet->setSpreadsheetKey($config['shared']["key"]);
  $dataSheet->setWorksheetId($config['page']);
  $listFeed = $spreadSheet->getListFeed($dataSheet);
  
  //Start collect items
  $cells = array();
  $index=0;
  foreach ($listFeed->entries as $listEntry){
    $rowEntry=$listEntry->getCustom();
    foreach($rowEntry as $colEntry){
      $cells[$index][$colEntry->getColumnName()]=$colEntry->getText();  
    }
    $index++;
  }
  unset($spreadSheet, $dataSheet, $listFeed);
  return $cells;
}
