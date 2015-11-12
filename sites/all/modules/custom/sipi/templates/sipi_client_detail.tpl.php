<?php
$file=file_load($data->logo);
$image=isset($file) && !empty($file) ? get_image_style($file->uri,'thumbnail') : url(drupal_get_path('module','sipi').'/img/codiga_white_150px.png',array('absolute'=>true));
unset($file);
$args=arg();
$idsite=isset($args[4]) && !empty($args[4]) ? $args[4] : null;
?>
<section class="sipi-client">
<div class="left">
  <img src="<?php print $image;?>"/>
</div>
<div class="right" style="width: 85%">
  <ul id="client-detail" class="nav">
    <li class="name">
      <?php print $data->name; ?>
    </li>
    <li class="description">
      <?php print $data->description; ?>
    </li>
    <li class="company">
      <strong>Company:</strong> <?php print $data->company; ?>
    </li>
    <li class="cellphone">
      <strong>Cellphone:</strong> <?php print $data->cellphone; ?>
    </li>
    <li class="phone">
      <strong>Phone:</strong> <?php print $data->phone.' - '.$data->extention; ?>
    </li>
    <li class="web">
      <a href="http://<?php print(preg_replace('/(http|https)\:\/\//','',$data->web)); ?>" target="_blank">Website</a>
    </li>
    <li class="actions">
      <a href="<?php print '/codiga/client/'.$data->cid.'/edit?destination=codiga/client/'.$data->cid.'/view';?>" style="width:50%;float:left;">Edit</a>
      <a href="<?php print '/codiga/client/'.$data->cid.'/cancel';?>" style="width:50%;float:left;">Cancel</a>
    </li>
  </ul>
</div>
<div class="right" style="width: 85%">
  <ul id="client-detail" class="nav">
    <li class="actions" style="text-align: center;background-color:#f5f5f5;padding:5px;border:1px solid #4c4c4c;"><strong>REPORTS</strong></li>
    <li class="actions" style="text-align: center;">
      <a href="<?php print '/codiga/client/'.$data->cid.'/report/'.$idsite;?>" style="width:20%;float:left;">View</a>
      <a href="javascript:window.print();" style="width:20%;float:left;">Print</a>
      <a href="<?php print '/codiga/client/'.$data->cid.'/pdf/'.$idsite;?>" target="_blank" style="width:20%;float:left;">Download as PDF</a>
      <a href="javascript:alert('Not available... yet! :)')" style="width:20%;float:left;">Download as XLS</a>
      <a href="javascript:alert('Not available... yet! :)')" style="width:20%;float:left;">Send to client email</a>
    </li>
  </ul>
</div>
</section>
<section class="sipi-client-contents-list">
<?php
$list=isset($data->cid) && !empty($data->cid) ? sipi_client_contents_list($data->cid) : NULL;
if(isset($list) && !empty($list) && count($list)>0){
  print drupal_render($list);
}
?>
</section>