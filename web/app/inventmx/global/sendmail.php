<?php
require_once '/var/www/html/invent/mx/web/app/inventmx/global/swiftmailer-master/lib/swift_required.php';

$nombre   = $_REQUEST['nombre'];
$apellido = $_REQUEST['apellido'];
$correo   = $_REQUEST['email'];
@$canal    = $_REQUEST['chanel'];
$type     = $_REQUEST['type'];

$referer=isset($_REQUEST['text-referrer']) ? " Vía ".$_REQUEST['text-referrer'] : '';
//if( $nombre === '' || $correo === ''  || strlen($nombre) <= 3 || strlen($correo) <= 3  ){
//    $valid = false;
//    return 0;
//} else{
    //$nombre = sanitaze_string($nombre);
    //$correo = sanitaze_string($correo);
    //$asunto = sanitaze_string($asunto);
    //$phone  = sanitaze_string($phone);

    #$to = 'luis@inventmx.com, kenneth@inventmx.com, informesventas@inventmx.com';
if ($type == "afiliate") {
    $type = "Afíliate";

    $to = "sergio@inventmx.com,jose.cruz@inventmx.com,luis@inventmx.com";
    //$to="webmaster@inventmx.com,luis@inventmx.com,pedro@inventmx.com, sara@inventmx.com,heberto@inventmx.com";
} else {
    $type = "Anúnciate";

    $to = "sergio@inventmx.com,jose.cruz@inventmx.com,luis@inventmx.com";
    //$to="webmaster@inventmx.com,luis@inventmx.com,pedro@inventmx.com,heberto@inventmx.com,kenneth@inventmx.com";
}

$subject = 'Nos han contactado en Invent.mx - ' . $type." ".$referer;
$body = 'Han usuado el formulario de contacto de Invent, estos son los datos: <br /><br />';
$body .= 'Nombre: '. $nombre .' '.$apellido.'<br /><br />';
$body .= 'Correo: '. $correo . '<br /><br />';

if($canal){
    $body .= 'Youtube Channel: '. $canal . '<br /><br />';
}

// Create the Transport
$transport = Swift_SmtpTransport::newInstance('localhost', 25);
// Create the Mailer using your created Transport
$mailer = Swift_Mailer::newInstance($transport);
$message = Swift_Message::newInstance($subject)
  ->setFrom(array('webmaster@inventmx.com' => 'Invent.mx'))
  ->setTo(array($to))
  //->setTo(array('receiver@domain.org', 'other@domain.org' => 'A name'))
  ->setBody("$body")
  ;
// Send the message
$result = $mailer->send($message);

//$correo = filter_var( $correo, FILTER_SANITIZE_EMAIL);
//    $valid = true;
//}

//$headers   = array();
//$headers[] = "Content-type: text/html";
//$headers[] = "From: Invent.mx <webmaster@inventmx.com>";
//ini_set('sendmail_from', 'example@YourDomain.com');
//$cabeceras = implode("\n", $headers);
   

//mail($to, $subject, $message, $cabeceras);

/*if( $valid ){
    $respond = array(
        'respond' => true,
        'text' => 'El correo se ha enviado satisfactoriamente.'
    );
    print json_encode( $respond );
} else{
    $respond = array(
        'respond' => false,
        'text' => 'Ha ocurrido un error al enviar el mail, recargue la p&aacute;gina e intente de nuevo por favor.'
    );
    print json_encode( $respond );
}*/

function sanitaze_string($str = ''){
    $str = strip_tags($str);
    $str = addslashes($str);
    $str = htmlentities($str);

    return $str;
}

?>
