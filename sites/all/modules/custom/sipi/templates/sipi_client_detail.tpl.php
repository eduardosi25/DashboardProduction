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
  </ul>
</div>
</section>

<?php
echo render(sipi_client_contents_list($data->cid));
  //echo module_invoke('sipi', 'block_view', 'sipi_client_contents_list');
?>
