<?php
/**
 * @file
 * redcat_new_migration.features.inc
 */

/**
 * Implements hook_node_info().
 */
function redcat_new_migration_node_info() {
  $items = array(
    'gallery_exhibition' => array(
      'name' => t('Gallery Exhibition'),
      'base' => 'node_content',
      'description' => t('Create a gallery exhibition that will be at REDCAT'),
      'has_title' => '1',
      'title_label' => t('Page Name'),
      'help' => '',
    ),
    'press_release' => array(
      'name' => t('Press Release'),
      'base' => 'node_content',
      'description' => t('This would show up in the press releases section of the web site.'),
      'has_title' => '1',
      'title_label' => t('Page Name (admin + page title use only)'),
      'help' => '',
    ),
    'publication' => array(
      'name' => t('Publication'),
      'base' => 'node_content',
      'description' => t('This would be a particular book publication.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'redcat_audio' => array(
      'name' => t('REDCAT Audio'),
      'base' => 'node_content',
      'description' => t('Add audio to be associated with various types of content.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'redcat_event' => array(
      'name' => t('REDCAT Event'),
      'base' => 'node_content',
      'description' => t('Create an event to be shown at REDCAT.'),
      'has_title' => '1',
      'title_label' => t('Page Name'),
      'help' => '',
    ),
    'redcat_festival' => array(
      'name' => t('Festival'),
      'base' => 'node_content',
      'description' => t('Festivals are content that consist of multiple content from within the site (such as pages and REDCAT events). An example of a Festival would be RADAR LA where you would create the corresponding content and tie it together to be shown fully on a festival page. The referenced pages would then get a link showing the user to get back to the festival page.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'redcat_general' => array(
      'name' => t('General Page'),
      'base' => 'node_content',
      'description' => t('Use <em>basic pages</em> for your static content, such as an \'About us\' page.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'redcat_media' => array(
      'name' => t('REDCAT Media'),
      'base' => 'node_content',
      'description' => t('Add Media to be associated with various types of content.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'redcat_video' => array(
      'name' => t('REDCAT Video'),
      'base' => 'node_content',
      'description' => t('Add video to be associated with various types of content.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
