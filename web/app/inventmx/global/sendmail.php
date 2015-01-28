<?php

$nombre   = $_REQUEST['nombre'];
$apellido = $_REQUEST['apellido'];
$correo   = $_REQUEST['email'];
$canal    = $_REQUEST['chanel'];
$type     = $_REQUEST['type'];

$referer=isset($_REQUEST['text-referrer']) ? " Vía ".$_REQUEST['text-referrer'] : '';


//if( $nombre === '' || $correo === ''  || strlen($nombre) <= 3 || strlen($correo) <= 3  ){
//    $valid = false;
//    return 0;
//} else{

    $nombre = sanitaze_string($nombre);
    $correo = sanitaze_string($correo);
    //$asunto = sanitaze_string($asunto);
    //$phone  = sanitaze_string($phone);

    $correo = filter_var( $correo, FILTER_SANITIZE_EMAIL);
    $valid = true;
//}

$to="sergio@inventmx.com,jose.cruz@inventmx.com,pedro@inventmx.com";
//$to="sergio@inventmx.com,jose.cruz@inventmx.com";
#$to = 'luis@inventmx.com, kenneth@inventmx.com, informesventas@inventmx.com';
    /*if($type == "afiliate") {
        $to="pedro@inventmx.com, sara@inventmx.com,heberto@inventmx.com";
    }else {
        $to="pedro@inventmx.com,heberto@inventmx.com,kenneth@inventmx.com";
    }*/

$cabeceras = "Content-type: text/html";

$subject = 'InventMX - Nos han contactado! - ' . $type." ".$referer;
$message = 'Han usuado el formulario de contacto de InventMX, estos son los datos: <br /><br />';
$message .= 'Nombre: '. $nombre .' '.$apellido.'<br /><br />';
$message .= 'Correo: '. $correo . '<br /><br />';
$message .= 'Youtube Channel: '. $canal . '<br /><br />';


mail($to, $subject, $message, $cabeceras);

if( $valid ){
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
}

function sanitaze_string($str = ''){
    $str = strip_tags($str);
    $str = addslashes($str);
    $str = htmlentities($str);

    return $str;
}

?>
