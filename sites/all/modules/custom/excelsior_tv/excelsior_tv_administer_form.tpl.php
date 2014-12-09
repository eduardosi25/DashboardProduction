<?php

print drupal_render( $form[ 'form_youtube_tv_top' ]['submit'] );

print drupal_render( $form[ 'form_youtube_tv' ] );

print drupal_render( $form[ 'form_youtube_tv' ][ 'name' ] );  
print drupal_render( $form[ 'form_youtube_tv' ][ 'lista' ] );
print drupal_render( $form[ 'form_youtube_tv' ][ 'num_mostrar' ] );
print drupal_render( $form[ 'form_youtube_tv' ][ 'estatus' ] );
print drupal_render( $form[ 'form_youtube_tv' ][ 'placa' ] );

print drupal_render( $form[ 'form_youtube_tv_bottom' ]['submit'] );
print drupal_render( $form[ 'form_youtube_tv_top' ]['bottom-return'] );



?>

<?php
print drupal_render_children( $form );
?>