<?php
/**
 * You must implement hook_migrate_api(), setting the API level to 2, for
 * your migration classes to be recognized by the Migrate module.
 */
function migrate_rsvp_migrate_api() {
  $api = array(
    'api' => 2,
    'groups' => array(
      'rsvp' => array(
        'title' => t('RSVP Migrations'),
      ),
    ),
    'migrations' => array(
      'User' => array(
        'class_name' => 'UserMigration',
        'group_name' => 'rsvp',
      ),
      'Pages'    => array(
        'class_name' => 'PagesMigration',
        'group_name' => 'rsvp',
      ),
      'Articles'    => array(
        'class_name' => 'ArticlesMigration',
        'group_name' => 'rsvp',
      ),
      'Galleries'    => array(
        'class_name' => 'GalleriesMigration',
        'group_name' => 'rsvp',
      ),
      'Taxonomy'    => array(
        'class_name' => 'TaxonomyMigration',
        'group_name' => 'rsvp',
      ),
      'Vocabulary'    => array(
        'class_name' => 'VocabularyMigration',
        'group_name' => 'rsvp',
      ),
    ),
  );
  
  return $api;
}

