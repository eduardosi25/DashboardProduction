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

function sipi_package(){
  return t('Package');
}

function sipi_package_registration(){
  return t('Package registration');
}

function sipi_package_edit(){
  return t('Package edit');
}

function sipi_package_delete(){
  return t('Package delete');
}

function sipi_next_completions(){
  return t('Next completions');
}
