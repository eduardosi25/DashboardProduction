<?php

function sipi_login(){
  global $user;
  if(!$user->uid){
    module_load_include('module','user');
    return drupal_get_form('user_login');
  }else{
    return 'Administrador SIPI';
  }
}

function sipi_dashboard(){
  return t('Dashboard');
}
