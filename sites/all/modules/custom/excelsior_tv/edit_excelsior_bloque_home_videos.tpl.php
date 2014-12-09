<?php
echo '<div style = "float:left; width:99%;" > ';
	print drupal_render( $form [ "top-block-videos" ][ 'submit' ] );
	print drupal_render( $form [ "top-block-videos" ][ 'Editar' ] );
	print drupal_render( $form [ "top-block-videos" ][ 'Cancel' ] );
echo '</div>';

    print drupal_render( $form [ "block-videos-home_change" ][ 'change_time' ] );

    print drupal_render( $form [ "block-videos-home_1" ] );
       print drupal_render( $form [ "block-videos-home_1" ][ 'image_video_home_1' ] );
       print drupal_render( $form [ "block-videos-home_1" ][ "title_video_home_1" ] );
       print drupal_render( $form [ "block-videos-home_1" ][ "url_video_home_1" ] );

    print drupal_render( $form [ "block-videos-home_2" ] );
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
     
echo '<div style = "float:left; width:99%;" > ';
	print drupal_render( $form [ "bottom-block-videos" ][ 'submit' ] );
	print drupal_render( $form [ "bottom-block-videos" ][ 'Editar' ] );
	print drupal_render( $form [ "bottom-block-videos" ][ 'Cancel' ] );
echo '</div>';	

	print drupal_render_children( $form );	