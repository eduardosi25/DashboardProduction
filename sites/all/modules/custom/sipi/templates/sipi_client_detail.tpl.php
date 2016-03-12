<?php
$file=file_load($data->logo);
$image=isset($file) && !empty($file) ? get_image_style($file->uri,'thumbnail') : 'http://local.invent.mx/sites/all/themes/bootstrap/logo.png';
unset($file);
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
      <a href="<?php print '/sipi/client/'.$data->cid.'/edit?destination=sipi/client/'.$data->cid.'/view';?>" style="width:50%;float:left;">Edit</a>
      <a href="<?php print '/sipi/client/'.$data->cid.'/cancel';?>" style="width:50%;float:left;">Cancel</a>
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