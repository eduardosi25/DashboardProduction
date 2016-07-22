<?php
function get_cms_access(){
  global $user;
  if($user->uid || get_cms_admin_paths()){
    return true;
  }
  return false;
}
function get_cms_admin_paths(){
  //Admin paths
  $paths=array(
    'files',
    'files/*',
    'admin',
    'admin/*',
    'node/add',
    'node/*/*',
    'user',
    'user/*',
    'login',
    '*/ajax/*',
    'system',
    'system/*',
    '*/ahah/*',
    'batch',
    'batch*',
    'codiga',
    'play/feeds/*',
    'jedi',
    'feeds',
    'colabora-con-nosotros',
    'colabora-con-nosotros/*',
    'dashboard',
    'dashboard/*',
  );
  $paths=implode("\n",$paths);
  return drupal_match_path($_GET["q"],$paths);
}
function get_frontend_paths(){
  if(drupal_is_front_page()){
    return true;
  }else{
    $paths=array(
      'web',
      'web/*',
    );
    $paths=implode("\n",$paths);
    return drupal_match_path($_GET["q"],$paths);
  }
  return false;
}
