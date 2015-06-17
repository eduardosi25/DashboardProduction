<?php
/**
 *
 * @param string $command Herramienta a utilizar
 * @param integer $nid NID del contenido
 * @return object
 */
function imx_tools_action($command=NULL, $nid=NULL){
  if(!$command || !$nid)
    return NULL;

  $nid=(int)$nid;

  //Load node content
  $node=node_load($nid);

  switch($node->type){
    case 'article':
    //case 'gallerie':
    //case 'video':
      //Render content node
      $imx_autor = implode(' | ', node_get_autor($node) );
      $html=call_user_func('imx_tools_html_'.$node->type, $command, $imx_autor);
    break;
    default:
      exit;
    break;
  }


//print_r($html); die();

  //Replace tokens
  $html=token_replace($html, array('node'=>$node));

  switch($command){
    case 'print':
      echo $html;
    break;
    case 'pdf':
      imx_tools_createpdf($html,$nid);
    break;
  }
  exit;
}


function imx_tools_createpdf($html=NULL,$nid=NULL){
  if(!$html)
    return $html;

  //Sanitize html
  $html=strip_tags($html,'<html><head><meta><title><link><style><body><p><a><img><br><div><table><tr><td><span><strong><h1><h2><h3><h4><h5><h6><em><audio><video><canvas><hr>');
  $site=$_SERVER['HTTP_HOST'];
  $site=explode('.',$site);
  $site=$site[1];

  //Start buffer
  ob_start();

  //Put content in tmp file
  $time=time();
  $tmpfile='/tmp/'.$site.'_'.$nid.'.html';

  if(!file_exists($tmpfile))
    $handler=@file_put_contents($tmpfile, $html);
  else
    $handler=file_get_contents($tmpfile);

  if(!$handler)
    return null;

  //Create PDF
  $filename='/tmp/'.$site.'_'.$nid.'.pdf';
  $cmd="/usr/local/bin/wkhtmltopdf {$tmpfile} {$filename}";

  if(!file_exists($filename))
    $handler=exec($cmd);
  else
    $handler=true;

  //Regresa el pdf
  ob_start();
  $pdf=file_get_contents($filename);
  $length=filesize($filename);
  header('Content-Type: application/pdf');
  header('Cache-Control: public, must-revalidate, max-age=0'); // HTTP/1.1
  header('Pragma: public');
  header('Expires: Sat, 26 Jul 1997 05:00:00 GMT'); // Date in the past
  header('Last-Modified: '.gmdate('D, d M Y H:i:s').' GMT');
  header('Content-Length: '.$length);
  header('Content-Disposition: inline; filename="'.basename($filename).'";');
  ob_clean();
  flush();
  echo $pdf;

  unset($handler);
}
