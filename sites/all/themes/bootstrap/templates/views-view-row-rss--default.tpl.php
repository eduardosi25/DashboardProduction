<?php

/**
 * @file
 * Default view template to display a item in an RSS feed.
 *
 * @ingroup views_templates
 */
$node=node_load($row->elements[1]['value']);
$channel=taxonomy_term_load($node->field_channel['und'][0]['tid']);
$channel_name=$channel->name;
$channel_url=isset($channel->field_content['und'][0]['value']) && !empty($channel->field_content['und'][0]['value']) ? $channel->field_content['und'][0]['value'] : '';
unset($channel);
$site=taxonomy_term_load($node->field_site['und'][0]['tid']);
$siteName=$site->name;
unset($channel,$site);
$item_elements=array();
foreach($row->elements as $element){
  if($element['key']=='dc:creator'){
    $element['value']=$siteName;
  }elseif($element['key']=='guid'){
    $element['value']=$node->nid;
  }elseif($element['key']=='pubDate'){
    $element['value']=date('c',$node->created);
  }
  $item_elements[]=$element;
}
$thumbnail=isset($node->field_cover['und'][0]['uri']) && !empty($node->field_cover['und'][0]['uri']) ? image_style_url('large',$node->field_cover['und'][0]['uri']) : 'empty';
$link=preg_replace('/https/','http',$link);
$link_video=preg_replace('/https/','http',$node->field_content['und'][0]['value']);
$video_duration=isset($node->field_video_duration['und'][0]['value']) && !empty($node->field_video_duration['und'][0]['value']) ? $node->field_video_duration['und'][0]['value'] : 300;
//Add other elements
$item_elements[]=array('key'=>'title'         , 'value'=>$title);
$item_elements[]=array('key'=>'description'   , 'value' => $description);
$item_elements[]=array('key'=>'author'        , 'value' => $siteName);
$item_elements[]=array('key'=>'lastBuildDate' , 'value' => date('c',$node->changed));
$item_elements[]=array('key'=>'expirationDate', 'value' => "");
$item_elements[]=array('key'=>'dcterms:valid' , 'value' => date('c',time()+(3*60*60)));
$item_elements[]=array('key'=>'media:keywords', 'value' => $channel_name);
$item_elements[]=array('key'=>'link', 'value' => $link);
$item_elements=empty($item_elements) ? '' : format_xml_elements($item_elements);
?>
  <item>
    <?php print $item_elements; ?>
    <media:content url="<?php print($link_video);?>" duration="<?php print($video_duration);?>" type="video/mp4" lang="es">
      <media:title><?php print($title);?></media:title>
      <media:category scheme="<?php print $channel_url;?>"><?php print $channel_name; ?></media:category>
      <media:text><![CDATA[<?php print $description; ?>]]></media:text>
      <media:thumbnail url="<?php print $thumbnail;?>"/>
    </media:content>
  </item>
