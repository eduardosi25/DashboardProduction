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
$channel_url=$channel->field_content['und'][0]['value'];
unset($channel);
$site=taxonomy_term_load($node->field_site['und'][0]['tid']);
$siteName=$site->name;
unset($channel,$site);
$item_elements=array();
foreach($row->elements as $element){
  if($element['key']=='dc:creator'){
    $element['key']='author';
    $element['value']=$siteName;
  }elseif($element['key']=='guid'){
    $element['value']=md5($siteName.'|'.$element['value']);
  }
  $item_elements[]=$element;
}
$item_elements=empty($item_elements) ? '' : format_xml_elements($item_elements);
$thumbnail=isset($node->field_cover['und'][0]['uri']) && !empty($node->field_cover['und'][0]['uri']) ? image_style_url('large',$node->field_cover['und'][0]['uri']) : 'empty';
?>
  <item>
    <title><?php print $title; ?></title>
    <link><?php print $link; ?></link>
    <description><![CDATA[<?php print $description; ?>]]></description>
    <?php print $item_elements; ?>
    <media:title><?php print($node->title);?></media:title>
    <media:category scheme="<?php print $channel_url;?>"><?php print $channel_name; ?></media:category>
    <media:content url="<?php print($node->field_content['und'][0]['value']);?>" medium="video" expression="full" lang="es">
      <media:thumbnail url="<?php print $thumbnail;?>"/>
    </media:content>
  </item>
