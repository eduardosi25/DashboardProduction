<?php

function sipi_login(){
  global $user;
  if(!$user->uid){
    module_load_include('module','user');
    return drupal_get_form('user_login');
  }else{
    return 'Admin SIPI';
  }
}

function sipi_dashboard(){
  return t('Dashboard');
}

function sipi_client(){
  return t('Clients');
}

function sipi_client_registration(){
  return t('Client registration');
}

function sipi_client_edit(){
  return t('Client edit');
}

function sipi_client_suspend(){
  return t('Client suspend');
}

function sipi_client_detail(){
  return t('Client detail');
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
