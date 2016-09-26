<?php
require_once '/var/www/html/invent/mx/web/app/inventmx/global/swiftmailer-master/lib/swift_required.php';

$nombre   = $_REQUEST['nombre'] ? $_REQUEST['nombre'] : NULL;
$apellido = $_REQUEST['apellido'] ? $_REQUEST['apellido'] : NULL;
$correo   = $_REQUEST['email'] ? $_REQUEST['email'] : NULL;
@$canal   = $_REQUEST['chanel'] ? $_REQUEST['chanel'] : NULL;
$type     = $_REQUEST['type'] ? $_REQUEST['type'] : NULL;
$description     = $_REQUEST['description'] ? $_REQUEST['description'] : NULL;
$source   = $type;

$referer=isset($_REQUEST['text-referrer']) ? " Vía ".$_REQUEST['text-referrer'] : '';


if ($type == "afiliate") {
  $type = "Afíliate";  
  //$to = array('pedro@inventmx.com');
  $to = array('pedro@imagendigital.com','erika.aupart@imagendigital.com','red@imagendigital.com','webmaster@imagendigital.com','heberto@imagendigital.com', 'carine@imagendigital.com');
  //$to = array('jose.cruz@invent.mx','jorge@invent.mx','luis@invent.mx');
} else {
  $type = "Anúnciate";  
  //$to = array('pedro@inventmx.com');
  //$to = array('jose.cruz@invent.mx','jorge@invent.mx','luis@invent.mx');
  $to = array('pedro@imagendigital.com','webmaster@imagendigital.com','heberto@imagendigital.com','eduardo@imagendigital.com','carlos.jimenez@imagendigital.com');
}

$subject = 'Nos han contactado en ImagenDigital.com - ' . $type." ".$referer;
$body = 'Han usuado el formulario de contacto de Imagen Digital, estos son los datos: <br /><br />';
$body .= 'Nombre: '. $nombre .' '.$apellido.'<br /><br />';
$body .= 'Correo: '. $correo . '<br /><br />';
$body .= 'Producto: '. $description . '<br /><br />';

if($canal){
    $body .= 'Youtube Channel: '. $canal . '<br /><br />';
}

// Create the Transport
$transport = Swift_SmtpTransport::newInstance('localhost', 25);
// Create the Mailer using your created Transport
$mailer = Swift_Mailer::newInstance($transport);
$message = Swift_Message::newInstance($subject)
  ->setFrom(array('webmaster@imagendigital.com' => 'ImagenDigital.com'))
  ->setTo($to)
  ->setContentType('text/html')
  ->setBody($body)
  ;
// Send the message
$result = $mailer->send($message);
$result=true;
if( $result ){
  $respond = array(
    'respond' => true,
    'text' => 'El correo se ha enviado satisfactoriamente.'
  );

  //Save data
  $data=new apiFile($source.'_'.date('Ymd').'.csv','/var/www/html/invent/mx/files');
  $data->_write(implode(",",$_REQUEST)."\n");

  print json_encode( $respond );
} else{
    $respond = array(
        'respond' => false,
        'text' => 'Ha ocurrido un error al enviar el mail, recargue la p&aacute;gina e intente de nuevo por favor.'
    );
    print json_encode( $respond );
}

function sanitaze_string($str = ''){
    $str = strip_tags($str);
    $str = addslashes($str);
    $str = htmlentities($str);

    return $str;
}


class apiFile{
  /**
   * @var string Recipe for filename
   * @see __construct in that place this variable start it.
   */
  var $filename='';
  /**
   * @var int Write mode
   */
  var $mode=0;
  /**
   * @var int Write mode
   * @see http://php.net/manual/es/function.file-put-contents.php
   */
  var $append=FILE_APPEND;
  /**
   * @var int Write mode
   * @see http://php.net/manual/es/function.file-put-contents.php
   */
  var $lock=LOCK_EX;

  function __construct($name='anunciate.csv',$where='/tmp'){
    $this->filename=$where.'/'.$name;
  }
  /**
   * Write a line into a file
   * @param $content
   * @return bool
   */
  public function _write($content){
    if(!$content)
      return false;
    //First search
    if($this->_search()){
      $this->mode=$this->append;
    }else{
      $this->mode=$this->lock;
    }
    return file_put_contents($this->filename,$content,$this->mode);
  }
  /**
   * Search for a file
   * @return bool
   */
  public function _search(){
    if(file_exists($this->filename)){
      return true;
    }
    return false;
  }

  function __destruct(){

  }
}
