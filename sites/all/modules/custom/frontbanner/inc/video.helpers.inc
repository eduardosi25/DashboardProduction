<?php
//Helpers
/**
* cURL to URL crawling
* @param string $url
* @param string $ref_url
* @param boolean $convert
* @param string $format
* @return string
*/
function load_url($url=null, $ref_url=null, $convert=FALSE, $format='utf-8', $bot=FALSE, $method='get', $options=array()){
  if(!$url)
    return $url;

  //Capture everything on buffers
  ob_start();

  //Start cURL resource
  $cURL = @curl_init();

  if($method=='get'){
    @curl_setopt($cURL,CURLOPT_HTTPGET,1);
    $cadena=null;
    if(count($options)>0){
      $cadena=array();
      foreach($options as $var => $value){
        $cadena[]=$var.'='.$value;
      }
      $cadena=implode('&',$cadena);
    }
    $url=$url.'?'.$cadena;
  }else{
    @curl_setopt($cURL,CURLOPT_POST,1);
    if(count($options)>0)
      @curl_setopt($cURL,CURLOPT_POSTFIELDS,$options);
  }

  //Define basic options
  @curl_setopt($cURL, CURLOPT_URL, $url);

  //Validating custom bot
  if($bot){
    @curl_setopt($cURL, CURLOPT_USERAGENT, 'Googlebot/2.1 (+http://www.google.com/bot.html)');
    @curl_setopt($cURL, CURLOPT_REFERER, 'http://www.google.com');
    @curl_setopt($cURL, CURLOPT_AUTOREFERER, TRUE);
  }else{
    @curl_setopt($cURL, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.8.1.1) Gecko/20061204 Firefox/2.0.0.1");
    if($ref_url)
      @curl_setopt($cURL, CURLOPT_REFERER, $ref_url);
    else
      @curl_setopt($cURL, CURLOPT_AUTOREFERER, TRUE);
  }


  //Headers & other options
  @curl_setopt($cURL, CURLOPT_HTTPHEADER, shadow_headers());
  @curl_setopt($cURL, CURLOPT_RETURNTRANSFER, TRUE);
  @curl_setopt($cURL, CURLOPT_ENCODING, 'text/html; charset=utf-8');
  @curl_setopt($cURL, CURLOPT_FOLLOWLOCATION, TRUE);
  @curl_setopt($cURL, CURLOPT_CONNECTTIMEOUT, 120);
  @curl_setopt($cURL, CURLOPT_TIMEOUT, 120);
  @curl_setopt($cURL, CURLOPT_MAXREDIRS, 10);
  $HTTP_RESPONSE = @curl_exec($cURL);
  $cURL_ERRNO = @curl_errno($cURL);
  $cURL_ERROR = @curl_error($cURL);
  $header=curl_getinfo($cURL);

  //Error handling
  if($cURL_ERROR)
    return $cURL_ERRNO.' | '.$cURL_ERROR;

  //Read URL
  if($convert)
    $HTTP_RESPONSE=utf8_encode($HTTP_RESPONSE);

  return $HTTP_RESPONSE;

  //Free buffers
  ab_end_clean();
  curl_close();
  unset($cURL);

}

/**
* Return shadow headers for cURL transactions
* @param void 
* @return array Array with options headers for customize cURL transactions
*/
function shadow_headers(){
  $header=array();
  $header[0]  = "Accept: text/xml,application/xml,application/xhtml+xml,";
  $header[0] .= "text/html;q=0.9,text/plain;q=0.8,image/png,*/*;q=0.5";
  $header[] = "Cache-Control: max-age=0";
  $header[] = "Connection: keep-alive";
  $header[] = "Keep-Alive: 300";
  $header[] = "Accept-Charset: ISO-8859-1,utf-8;q=0.7,*;q=0.7";
  $header[] = "Accept-Language: en-us,en;q=0.5";
  $header[] = "Pragma: "; // browsers keep this blank.
  return $header;
}

/**
* Transliterate text plain in htmlentities secure
* @param string $string
* @param string $format Options: utf-8, iso-8869-1 & other formats
* @return string String encoding with htmlentities, even quotes
*/
function qp_htmlentities($string=NULL, $format=NULL){
  if(!$string)
    return $string;
  
  $output=trim($string);

  if($format)
    return htmlentities($output, ENT_QUOTES | ENT_IGNORE, $format);

  return htmlentities($output, ENT_QUOTES);
}

/**
* Return a string cleaning & transliterated into a secure string
* @staticvar array $translations Turn on var Array if file i18n-ascii.txt found it
* @param string $string The string where we want cleaning & transliterated
* @return string The result of cleaning & transliterated string
*/
function qp_cleanstring($string=null){
  $output = $string;

  // Remove accents and transliterate
  static $translations;

  if (!isset($translations)) {
    $translations = FALSE;
    $file=ROOT_PATH.'/inc/i18n-ascii.txt';
    if ($file){
      $translations = parse_ini_file($file);
    }
  }
  
  if (!empty($translations)) {
    $output = strtr($output, $translations);
  }

  // Replace or drop punctuation based on user settings
  $separator = '-';
  $punctuation = qp_punctuation_chars();
  foreach ($punctuation as $name => $details) {
    // Slightly tricky inline if which either replaces with the separator
    $output = str_replace($details['value'], $separator, $output);
  }

  // Reduce strings to letters and numbers
  $pattern = '/[^a-zA-Z0-9\/]+/';
  $output = preg_replace($pattern, $separator, $output);

  // Always replace whitespace with the separator.
  $output = preg_replace('/\s+/', $separator, $output);

  // Trim duplicates and remove trailing and leading separators.
  $output = _qp_clean_separators($output);

  // Convert to lower case.
  $output = strtolower($output);

  return $output;
}

function qp_db_string_safe($string=NULL){
  if(!$string)
    return $string;

  $file=CRAWL_PATH.'/inc/db_string_safe.txt';
  if ($file){
    $translations = parse_ini_file($file);
  }
  if (!empty($translations)) {
    $string = strtr($string, $translations);
  }
  $punctuation = qp_db_punctuation_chars();

  foreach ($punctuation as $name => $details) {
    $string = str_replace($details['search'],$details['replace'],$string);
  }
  return $string;
}

function qp_db_punctuation_chars() {
  $replaces=array();
  $replaces[]=array('search'=>'"','replace'=>htmlspecialchars('"'));
  $replaces[]=array('search'=>"'",'replace'=>htmlspecialchars("'",ENT_QUOTES));
  $replaces[]=array('search'=>'&','replace'=>htmlspecialchars('&'));
  $replaces[]=array('search'=>'<','replace'=>htmlspecialchars('<'));
  $replaces[]=array('search'=>'>','replace'=>htmlspecialchars('>'));
  $replaces[]=array('search'=>'|','replace'=>'-');
  $replaces[]=array('search'=>'`','replace'=>'');
  $replaces[]=array('search'=>'*','replace'=>'*');
  $replaces[]=array('search'=>'%','replace'=>'%');
  $replaces[]=array('search'=>'^','replace'=>'^');
  $replaces[]=array('search'=>'$','replace'=>'$');
  $replaces[]=array('search'=>'#','replace'=>'#');
  $replaces[]=array('search'=>'@','replace'=>'@');
  $replaces[]=array('search'=>'!','replace'=>'!');
  $replaces[]=array('search'=>"\n",'replace'=>'<br />');
  $replaces[]=array('search'=>"\r",'replace'=>'<br />');
  $replaces[]=array('search'=>"\n\r",'replace'=>'<br />');
  $replaces[]=array('search'=>"\r\n",'replace'=>'<br />');
  return $replaces;
}


/**
* Cleaning & replacing doubles-separators
* @param string $string The string to be cleaning
* @param string $separator The char that use as separator
* @return string The string result of cleaning
*/
function _qp_clean_separators($string, $separator = NULL) {
  $output = $string;

  if (!isset($separator)) {
    $separator = '-';
  }

  // Clean duplicate or trailing separators.
  if (strlen($separator)) {
    // Escape the separator.
    $seppattern = preg_quote($separator, '/');

    // Trim any leading or trailing separators.
    $output = preg_replace("/^$seppattern+|$seppattern+$/", '', $output);

    // Replace trailing separators around slashes.
    if ($separator !== '/') {
    $output = preg_replace("/$seppattern+\/|\/$seppattern+/", "/", $output);
    }

    // Replace multiple separators with a single one.
    $output = preg_replace("/$seppattern+/", $separator, $output);
  }

  return $output;
}

/**
* Return an Array with some other chars to be used in cleaning string
* @staticvar array $punctuation A var to turn on Array with some values chars to be used on cleaning & transliteration
* @return array The array with additional chars to transliteration & cleaning
*/
function qp_punctuation_chars() {
  static $punctuation;
  if (!isset($punctuation)) {
    $punctuation = array();
    $punctuation['double_quotes']      = array('value' => '"', 'name' => 'Double quotes "');
    $punctuation['quotes']             = array('value' => "'", 'name' => "Single quotes (apostrophe) '");
    $punctuation['backtick']           = array('value' => '`', 'name' => 'Back tick `');
    $punctuation['comma']              = array('value' => ',', 'name' => 'Comma ,');
    $punctuation['period']             = array('value' => '.', 'name' => 'Period .');
    $punctuation['hyphen']             = array('value' => '-', 'name' => 'Hyphen -');
    $punctuation['underscore']         = array('value' => '_', 'name' => 'Underscore _');
    $punctuation['colon']              = array('value' => ':', 'name' => 'Colon :');
    $punctuation['semicolon']          = array('value' => ';', 'name' => 'Semicolon ;');
    $punctuation['pipe']               = array('value' => '|', 'name' => 'Pipe |');
    $punctuation['left_curly']         = array('value' => '{', 'name' => 'Left curly bracket {');
    $punctuation['left_square']        = array('value' => '[', 'name' => 'Left square bracket [');
    $punctuation['right_curly']        = array('value' => '}', 'name' => 'Right curly bracket }');
    $punctuation['right_square']       = array('value' => ']', 'name' => 'Right square bracket ]');
    $punctuation['plus']               = array('value' => '+', 'name' => 'Plus +');
    $punctuation['equal']              = array('value' => '=', 'name' => 'Equal =');
    $punctuation['asterisk']           = array('value' => '*', 'name' => 'Asterisk *');
    $punctuation['ampersand']          = array('value' => '&', 'name' => 'Ampersand &');
    $punctuation['percent']            = array('value' => '%', 'name' => 'Percent %');
    $punctuation['caret']              = array('value' => '^', 'name' => 'Caret ^');
    $punctuation['dollar']             = array('value' => '$', 'name' => 'Dollar $');
    $punctuation['hash']               = array('value' => '#', 'name' => 'Hash #');
    $punctuation['at']                 = array('value' => '@', 'name' => 'At @');
    $punctuation['exclamation']        = array('value' => '!', 'name' => 'Exclamation !');
    $punctuation['tilde']              = array('value' => '~', 'name' => 'Tilde ~');
    $punctuation['left_parenthesis']   = array('value' => '(', 'name' => 'Left parenthesis (');
    $punctuation['right_parenthesis']  = array('value' => ')', 'name' => 'Right parenthesis )');
    $punctuation['question_mark']      = array('value' => '?', 'name' => 'Question mark ?');
    $punctuation['less_than']          = array('value' => '<', 'name' => 'Less than <');
    $punctuation['greater_than']       = array('value' => '>', 'name' => 'Greater than >');
    $punctuation['slash']              = array('value' => '/', 'name' => 'Slash /');
    $punctuation['back_slash']         = array('value' => '\\', 'name' => 'Backslash \\');
  }
  return $punctuation;
}

function fn_date2timestamp($fecha=NULL,$formato="dd/mm/yyyy",$separador='/'){
  $fecha=explode($separador,$fecha);
  $formato=explode($separador,$formato);
  $date=array();
  foreach($formato as $key => $value){
    $date[$value]=$fecha[$key];
  }
  $fecha=mktime(0,0,0,$date['mm'],$date['dd'],$date['yyyy']);
  return $fecha;
}

function fn_pipe2array($string=NULL,$format=NULL){
  if(!$string)
    return string;
  $array=explode('|',$string);
  $items=array();
  foreach($array as $item){
    $items[]=trim($item);
  }
  if($format==='json')
    return json_encode($items);
  return $items;
}

function arguments($args ) {
  $ret = array(
    'exec'      => '',
    'options'   => array(),
    'flags'     => array(),
    'arguments' => array(),
  );

  $ret['exec'] = array_shift( $args );

  while (($arg = array_shift($args)) != NULL) {
    // Is it a option? (prefixed with --)
    if ( substr($arg, 0, 2) === '--' ) {
      $option = substr($arg, 2);
      // is it the syntax '--option=argument'?
      if (strpos($option,'=') !== FALSE)
      array_push( $ret['options'], explode('=', $option, 2) );
      else
      array_push( $ret['options'], $option );
      continue;
    }
    // Is it a flag or a serial of flags? (prefixed with -)
    if ( substr( $arg, 0, 1 ) === '-' ) {
      for ($i = 1; isset($arg[$i]) ; $i++){
        $ret['flags'][] = $arg[$i];
      }
      continue;
    }
    // finally, it is not option, nor flag
    $ret['arguments'][] = $arg;
    continue;
  }
  return $ret;
}

/**
 * Devuelve arreglo de fechas a procesar, normal devuelve fecha en formato dd/mm/aaaa, timestamp un timestamp basado en unix
 * @param type $startdate
 * @param type $days
 * @param type $type
 * @return type 
 */
function fn_retrieve_dates($startdate=NULL,$days=7,$type='normal',$format='Ymd'){
  if(!$startdate)
    return $startdate;
  
  $startdate=explode('/',$startdate);
  $items=array();
  for($i=0;$i<$days;$i++){
    switch($type){
      case 'normal':
        $items[]=date($format,mktime(0,0,0,$startdate[1],$startdate[0]+$i,$startdate[2]));
      break;
      case 'timestamp':
        $items[]=mktime(0,0,0,$startdate[1],$startdate[0]+$i,$startdate[2]);
      break;
    }
  }
  
  return $items;
}


function check_cache(){
  //get the last-modified-date of this very file
  $lastModified=filemtime($_SERVER['SCRIPT_FILENAME']);
  //get a unique hash of this file (etag)
  $etagFile = md5_file($_SERVER['SCRIPT_FILENAME']);
  //get the HTTP_IF_MODIFIED_SINCE header if set
  $ifModifiedSince=(isset($_SERVER['HTTP_IF_MODIFIED_SINCE']) ? $_SERVER['HTTP_IF_MODIFIED_SINCE'] : false);
  //get the HTTP_IF_NONE_MATCH header if set (etag: unique file hash)
  $etagHeader=(isset($_SERVER['HTTP_IF_NONE_MATCH']) ? trim($_SERVER['HTTP_IF_NONE_MATCH']) : false);
  //set last-modified header
  header("Last-Modified: ".gmdate("D, d M Y H:i:s", $lastModified)." GMT");
  //set etag-header
  header("Etag: $etagFile");
  //make sure caching is turned on
  header('Cache-Control: public');
  //check if page has changed. If not, send 304 and exit
  if (@strtotime($_SERVER['HTTP_IF_MODIFIED_SINCE'])==$lastModified || $etagHeader == $etagFile){
    header("HTTP/1.1 304 Not Modified");
    exit;
  }
}

function is_bot(){
  $bots = array(
    'Googlebot', 
    'Baiduspider', 
    'ia_archiver',
    'R6_FeedFetcher', 
    'NetcraftSurveyAgent', 
    'Sogou web spider',
    'bingbot', 
    'Yahoo! Slurp',
    'facebookexternalhit',
    'PrintfulBot',
    'msnbot',
    'Twitterbot',
    'UnwindFetchor',
    'urlresolver',
    'Butterfly',
    'TweetmemeBot'
  );
  $bots_flat = implode('|', $bots);

  if(preg_match('/'.$bots_flat.'/',$_SERVER['HTTP_USER_AGENT'])){
    return true;
  }
  return false;
}

function getcookie($name,$onlyvalue=false){
  $matches=array();
  $COOKIE=$_SERVER['HTTP_COOKIE'].';';
  $regex='{'.$name.'=[a-zA-Z0-9]+;}';
  $result=preg_match($regex, $COOKIE, $matches);
  if(count($matches)>0){
    if($onlyvalue){
      $COOKIE=explode('=',$matches[0]);
      return str_replace(';', '', $COOKIE[1]);
    }
    return $matches[0];
  }
  return false;
}

function calculate_time_expiring_cookies($expire=null){
  if(!$expire)
    return $expire;
    
  //Valores posibles (segundos, minutos, horas, dias)
  //usando la primer letra de cada palabra para el cálculo
  //s = secs :: m = mins :: h = hours :: d = days
  
  //Primero buscar las coincidencias 
  
  $matches=array();
  if(preg_match('{[0-9]+(s|m|h|d)}', $expire, $matches)){
    preg_match('{[0-9]+}',$expire,$matches);
    $number=(int)$matches[0];
    preg_match('{(s|m|h|d)}',$expire,$matches);
    $period=(string)$matches[0];
    
    switch($period){
      case 's':
        return time()+$number;
      break;
      case 'm':
        return time()+60*$number;
      break;
      case 'h':
        return time()+60*60*$number;
      break;
      case 'd':
        return time()+60*60*24*$number;
      break;
    }
  }
  return null;
}


function get_video_config(){
  $name=$_SERVER['HTTP_HOST'];
  if($_SERVER['HTTP_HOST']!=='localhost'){
    $name=explode('.',$name);
    $name=$name[1];
  }
  if(isset($name) && !empty($name)){
    $filename=__DIR__.'/'.$name.'.json';
    $result=file_get_contents($filename);
    return json_decode($result);
  }
  return false;
}

function get_expire_cookie_time($expire){
  if(!$expire){
    return $expire;
  }
  if($expire<time()){
    return true;
  }
  return false;
}

function show_videopo2(){
  global $prehomeConfig, $prehomeCookie; 
  $prehomeConfig=get_video_config();
  $timeExpire=calculate_time_expiring_cookies($prehomeConfig->expire);
  $defaultCookie=json_encode(array('status' => '0','expire' => $timeExpire));
  $prehomeCookie=isset($_COOKIE['prehome']) && !empty($_COOKIE['prehome']) ? json_decode($_COOKIE['prehome']) : json_decode($defaultCookie);
  
  //Match path
  $path = drupal_get_path_alias($_GET['q']);
  // Compare with the internal and path alias (if any).
  $patterns=explode('|',$prehomeConfig->match);
  $patterns=implode("\n",$patterns);
  $page_match = drupal_match_path($path, $patterns);
  if ($path != $_GET['q']) {
    $page_match = $page_match || drupal_match_path($_GET['q'], $patterns);
  }
  
  if($prehomeCookie->status==0 && $page_match){
    //Set cookie
    setcookie('prehome', json_encode($prehomeCookie), $prehomeCookie->expire, '/');
    return true;
  }else if($prehomeCookie->status==1){
    //Evaluate expire time
    $expiredCookie=get_expire_cookie_time($prehomeCookie->expire);
    if($expiredCookie){
      $prehomeConfig->expire=$timeExpire;
      $prehomeCookie->status=0;
    }
    setcookie('prehome', json_encode($prehomeCookie), $prehomeCookie->expire, '/');
    return false;
  }
}
