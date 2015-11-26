<?php
class sipiClientReport{
  var $client;
  var $siteName;
  var $data;

  function __construct(){
    $this->clearData();
    #echo '<pre>';
    #var_dump($this->client);
    #echo '<hr>';
    #var_dump($args);
    #echo '</pre>';
  }

  function getData($client,$tid){
    $data=$this->client=$client;
    if($tid>0){
      $term=taxonomy_term_load($tid);
      $this->siteName=$term->name;
    }else{
      $this->siteName='Todos los sitios';
    }

    $file=file_load($data->logo);
    $image=isset($file) && !empty($file) ? get_image_style($file->uri,'thumbnail') : url(drupal_get_path('module','sipi').'/img/codiga_white_150px.png',array('absolute'=>true));
    unset($file);

    $list=isset($data->cid) && !empty($data->cid) ? sipi_client_contents_list_report($data->cid,$tid) : NULL;
    $this->client->numContents=count($list['sipi_client_contents_list']['#rows']);

    if(isset($list) && !empty($list) && count($list)>0){
      $list=drupal_render($list);
    }

    if(isset($this->client) && !empty($this->client)){
      $this->data=array(
        'longdate'   => format_date(time(),'custom','d \d\e F \d\e Y'),
        'shortdate'  => format_date(time(),'custom','d/m/Y'),
        'clientName' => $this->client->name,
        'siteName'   => $this->siteName,
        'startDate'  => format_date($this->client->created,'custom','d/m/Y'),
        'endDate'    => isset($this->client->finish) ? $this->client->finish : null,
        'periodDate' => isset($this->client->reportDate) ? $this->client->reportDate : null,
        'numItems'   => isset($this->client->numContents) ? $this->client->numContents : null,
        'listItems'  => $list,
        'imageLogo'  => $image,
      );
    }
  }

  function renderHTML(){
    print $this->getHTML();
    die();
  }

  function getHTML(){
    $data=$this->data;

    $content=file_get_contents(drupal_get_path('module','sipi').'/templates/codiga.pdf.html');
    foreach($data as $key => $value){
      $content=str_replace('{{'.$key.'}}',$value,$content);
    }

    return $content;
  }

  function renderPDF(){
    $data=$this->data;

    $content=file_get_contents(drupal_get_path('module','sipi').'/templates/codiga.pdf.html');
    foreach($data as $key => $value){
      $content=str_replace('{{'.$key.'}}',$value,$content);
    }

    $this->html2pdf_createpdf($content);

    die();

  }

  function renderXLS(){

  }

  function renderCSV(){

  }

  function renderDrive(){

  }

  function html2pdf_createpdf($html=NULL){
    if(!$html)
      return $html;

    //Sanitize html
    //$html=strip_tags($html,'<html><head><meta><title><link><style><body><p><a><img><br><div><table><caption><th><tr><td><span><strong><h1><h2><h3><h4><h5><h6><em><audio><video><canvas><hr>');

    //Start buffer
    ob_start();
    $nameFile=array(
      'codiga',
      $this->data['clientName'],
      $this->data['siteName'],
      date('Ymd'),
    );

    //Filename: codiga_amis_7_20151111_7.pdf
    $nameFile=implode('_',$nameFile);
    $nameFile=transliteration_clean_filename($nameFile,LANGUAGE_NONE);
    //Put content in tmp file
    $time=time();
    $tmpfile='/tmp/'.$nameFile.'.html';

    if(!file_exists($tmpfile))
      $handler=@file_put_contents($tmpfile, $html);
    else
      $handler=file_get_contents($tmpfile);

    if(!$handler)
      return null;

    //Create PDF
    $filename='/tmp/'.$nameFile.'.pdf';

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
    header('Content-Disposition: attachment; filename="'.basename($filename).'";');
    ob_clean();
    flush();
    echo $pdf;

    unset($handler);
  }

  function clearData(){
    if($this->client){
      unset($this->client);
    }
  }

  function __destruct(){

  }
}