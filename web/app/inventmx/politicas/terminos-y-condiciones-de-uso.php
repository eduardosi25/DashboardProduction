<?php

$politica_ambiental = file_get_contents("http://737aebe7d69c81121b98-469d1938c942b4c8df1c08ee87f4d1a1.r21.cf1.rackcdn.com/terminos-y-condiciones-de-uso-imagen.html");
$bodyhtml = str_replace("|*SITENAME*|", "Imagen Digital", $politica_ambiental);
print $bodyhtml;