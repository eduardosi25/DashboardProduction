<?php
class sipiClientReport{
  var $client;
  var $siteName;

  function __construct(){
    $this->clearData();
    #echo '<pre>';
    #var_dump($this->client);
    #echo '<hr>';
    #var_dump($args);
    #echo '</pre>';
  }

  function getData($client,$args){
    $this->client=$client;
    $tid=isset($args[4]) && !empty($args[4]) ? $args[4] : 0;
    if($tid>0){
      $term=taxonomy_term_load($tid);
      $this->siteName=$term->name;
    }else{
      $this->siteName='Todos los sitios';
    }
  }

  function renderHTML(){
    $data=$this->client;
    $file=file_load($data->logo);
    $image=isset($file) && !empty($file) ? get_image_style($file->uri,'thumbnail') : url(drupal_get_path('module','sipi').'/img/codiga_white_150px.png',array('absolute'=>true));
    unset($file);
    $list=isset($data->cid) && !empty($data->cid) ? sipi_client_contents_list_report($data->cid) : NULL;
    if(isset($list) && !empty($list) && count($list)>0){
      $list=drupal_render($list);
    }

    //var_dump($this->client);

    $data=array(
      'longdate'   => format_date(time(),'custom','d \d\e F \d\e Y'),
      'clientName' => $this->client->name,
      'siteName'   => $this->siteName,
      'startDate'  => $this->client->created,
      'endDate'    => $this->client->finish,
      'periodDate' => $this->client->reportDate,
      'numItems'   => $this->client->numContents,
      'listItems'  => $list,
    );

    $content=file_get_contents(drupal_get_path('module','sipi').'/templates/codiga.pdf.html');
    foreach($data as $key => $value){
      $content=str_replace('{{'.$key.'}}',$value,$content);
    }

    print $content;

    die();

  }

  function renderPDF(){

  }

  function renderXLS(){

  }

  function renderCSV(){

  }

  function renderDrive(){

  }

  function clearData(){
    if($this->client){
      unset($this->client);
    }
  }

  function __destruct(){

  }
}