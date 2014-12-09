<?php
$data = $variables[ 'excelsior_tv_view_adm_list' ];

$HTML = "";

  if ( count( $data ) > 0 ){


  $HTML .= '<div class = "" style = "float:left; height:58px; text-align: center; width: 99%;" id = "update-respuesta-ajax" >   </div>';

  $HTML .= '<table style = "float:left;" >';

  $HTML .= '<tr>';
  $HTML .= '<th style= "text-align: center; font-weight: bold; width: 1%;" > # </th>';
  $HTML .= '<th style= "text-align: center; font-weight: bold; width: 12%;" > Nombre de la lista </th>';
  $HTML .= '<th style= "text-align: center; font-weight: bold; width: 32%;" > URL - Lista </th>';
  $HTML .= '<th style= "text-align: center; font-weight: bold; width: 1%;" > Videos mostrados</th>';
  $HTML .= '<th style= "text-align: center; font-weight: bold; width: 5%;" > Estatus </th>';
  $HTML .= '<th style= "text-align: center; font-weight: bold; width: 10%;" > Fecha de creación </th>';
  #$HTML .= '<th style= "text-align: center; font-weight: bold; width: 12%;" > Ultima actualización PlayList </th>';
  $HTML .= '<th style= "text-align: center; font-weight: bold; width: 22%;" > Acciones</th>';

  $HTML .= '</tr>';

    $I = 1;
    foreach ( $data as $index => $key ){


        $acciones_editar = '<a href = "/admin/config/excelsior/tv-config/edit?id='. $key[ "id" ] .'" alt = "Editar lista" > Editar </a>';
        $acciones_delete = '<a href = "/admin/config/excelsior/tv-config/delete?id='. $key[ "id" ] .'" alt = "Eliminar lista" > Eliminar</a>';

        $onclick = "actualizarReproduccionTv('". $key[ "id" ] ."', '#update-respuesta-ajax', '/admin/config/excelsior/tv-config/ajax-update-list', '". $index ."' )";

        $acciones_push = '<a onclick = "'. $onclick .'" alt = "Actualizar lista de reproducción." title = "Actualizar lista de reproducción." style = "cursor: pointer;" > Actualizar(Push) </a>';

        $estado = ( $key[ "estado" ] == "activar" ) ? "Activado" : "Desactivado";

        $HTML .= '<tr>';

           $HTML .= '<td> '. $I .' </td>';
           $HTML .= '<td> '. $key[ "nombre" ] .' </td>';
           $HTML .= '<td> '. $key[ "url_lista" ] .' </td>';
           $HTML .= '<td align = "center"> '. $key[ "NoListando" ] .' </td>';
           $HTML .= '<td align = "center" style = "color:#990000;" > '. $estado .' </td>';
           $HTML .= '<td align = "center" > '. date ( "Y-m-d H:i:s", $key[ "created" ] ) .' </td>';
           #$HTML .= '<td align = "center" style = "color:#990000;" > <strong>'. date ( "Y-m-d H:i:s", $key[ "update" ] ) .'</strong> </td>';
           $HTML .= '<td align = "center" > '.$acciones_editar.' | '.$acciones_delete./*' | '. $acciones_push .*/' </td>';

        $HTML .= '</tr>';

        $I ++;

       } // foreach

   $HTML .= '</table';    

    }else {
    	 $HTML = '<div class="messages error"> <h2 class="element-invisible">Mensaje de error</h2> Error, por el momento no hay registros. </div>';
    }

echo $HTML;
