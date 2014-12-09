<?php
echo '<div style = "float:left; width:99%;" > ';
	print drupal_render( $form [ "top-block-videos-canal" ][ 'submit' ] );
	print drupal_render( $form [ "top-block-videos-canal" ][ 'Editar' ] );
	print drupal_render( $form [ "top-block-videos-canal" ][ 'Cancel' ] );
echo '</div>';

    print drupal_render( $form [ "block-videos-canal_change" ][ 'change_time' ] );
    print drupal_render( $form [ "block-video-canal-bandera" ][ "apagar-encender-bloque-canal" ] );

   $data = range( 1,14 );


   foreach ( $data as $index => $value ){

    print drupal_render( $form [ "block-videos-canal_" . $value ] );
       print drupal_render( $form [ "block-videos-canal_". $value  ][ 'image_video_canal_'. $value ] );
       print drupal_render( $form [ "block-videos-canal_". $value ][ "title_video_canal_". $value ] );
       print drupal_render( $form [ "block-videos-canal_". $value ][ "url_video_canal_". $value ] );
       print drupal_render( $form [ "block-videos-canal_". $value ][ "peso_video_canal_". $value ] );
     }

/*    print drupal_render( $form [ "block-videos-home_2" ] );
       print drupal_render( $form [ "block-videos-home_2" ][ 'image_video_home_2' ] );
       print drupal_render( $form [ "block-videos-home_2" ][ "title_video_home_2" ] );
       print drupal_render( $form [ "block-videos-home_2" ][ "url_video_home_2" ] );       

    print drupal_render( $form [ "block-videos-home_3" ] );
       print drupal_render( $form [ "block-videos-home_3" ][ 'image_video_home_3' ] );
       print drupal_render( $form [ "block-videos-home_3" ][ "title_video_home_3" ] );
       print drupal_render( $form [ "block-videos-home_3" ][ "url_video_home_3" ] );        

    print drupal_render( $form [ "block-videos-home_4" ] );
       print drupal_render( $form [ "block-videos-home_4" ][ 'image_video_home_4' ] );
       print drupal_render( $form [ "block-videos-home_4" ][ "title_video_home_4" ] );
       print drupal_render( $form [ "block-videos-home_4" ][ "url_video_home_4" ] );       
 */ 

echo '<div style = "float:left; width:99%;" > ';
	print drupal_render( $form [ "bottom-block-videos-canal" ][ 'submit' ] );
	print drupal_render( $form [ "bottom-block-videos-canal" ][ 'Editar' ] );
	print drupal_render( $form [ "bottom-block-videos-canal" ][ 'Cancel' ] );
echo '</div>';	

	print drupal_render_children( $form );	