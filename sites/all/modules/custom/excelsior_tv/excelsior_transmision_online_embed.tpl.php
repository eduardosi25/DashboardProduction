<?php

	print drupal_render( $form [ "top-embed" ][ 'submit' ] );
	print drupal_render( $form [ "top-embed" ][ 'Editar' ] );
	print drupal_render( $form [ "top-embed" ][ 'Cancel' ] );

    print drupal_render( $form [ "transmision_online" ] );
    print drupal_render( $form [ "transmision_online" ][ "transmision_textfield_title" ] );
	print drupal_render( $form [ "transmision_online" ][ "transmision_embed" ] );

	print drupal_render( $form [ "transmision_online_home" ] );
    print drupal_render( $form [ "transmision_online_home" ][ "transmision_textfield_title_home" ] );
	print drupal_render( $form [ "transmision_online_home" ][ "transmision_embed_home" ] );

	print drupal_render( $form [ "transmision_online_movil" ] );
    print drupal_render( $form [ "transmision_online_movil" ][ "key_ooyala" ] );
	
	print drupal_render( $form [ "bottom-embed" ][ 'submit' ] );
	print drupal_render( $form [ "bottom-embed" ][ 'Editar' ] );
	print drupal_render( $form [ "bottom-embed" ][ 'Cancel' ] );

	print drupal_render_children( $form );	
?>