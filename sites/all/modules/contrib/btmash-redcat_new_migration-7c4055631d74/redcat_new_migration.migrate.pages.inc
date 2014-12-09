<?php

class RedcatNewMigrationPagesMigration extends RedCatNewMigrationMigrations {

  /**
   * Overrides default constructor.
   */
  public function __construct(array $arguments) {
    $this->arguments = $arguments;
    parent::__construct();
    $this->description = t('Import basic REDCAT pages.');

    $source_fields = array(
      'nid' => t('The node ID of the source REDCAT page.'),
      'redcat_new_migration_associated_images_filename' => t('Associated Images File Names'),
      'redcat_new_migration_associated_images_destination_dir' => t('Destination directory'),
      'redcat_new_migration_associated_images_alt' => t('Associated Images Alt. Text'),
      'redcat_new_migration_associated_images_title' => t('Associated Images Title Text'),
      'redcat_new_migration_linked_files_filename' => t('Linked Files File Names'),
      'redcat_new_migration_linked_files_destination_dir' => t('Linked Files Destination directory'),
      'redcat_new_migration_linked_files_description' => t('Linked Files Description'),
      'redcat_new_migration_linked_files_display' => t('Linked Files Display Option'),
    );

    $connection = $this->getDatabaseConnection();
    $query = $connection->select('node', 'n');
    $query->innerJoin('node_revision', 'nr', 'n.vid = nr.vid');
    $query->innerJoin('field_data_field_content_teaser', 'fdfct', 'n.vid = fdfct.revision_id');
    $query->innerJoin('field_data_field_content_body', 'fdfcb', 'n.vid = fdfcb.revision_id');
    $query->fields('n', array('nid', 'vid', 'language', 'title', 'status', 'created', 'changed', 'promote', 'sticky'));
    $query->fields('fdfct', array('field_content_teaser_value'));
    $query->fields('fdfcb', array('field_content_body_value'));
    $query->condition('n.type', 'redcat_general');
    $query->orderBy('n.changed');

    $this->highwaterField = array(
      'name' => 'changed', // Column to be used as highwater mark
      'alias' => 'n', // Table alias containing that column
    );

    $this->source = new MigrateSourceSQL($query, $source_fields, NULL, array('map_joinable' => FALSE));
    $this->destination = new MigrateDestinationNode('redcat_general');

    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'nid' => array(
          'type' => 'int',
          'unsigned' => TRUE,
          'not null' => TRUE,
          'alias' => 'n',
        )
      ),
      MigrateDestinationNode::getKeySchema()
    );

    // Simple Field Mappings.
    $this->addSimpleMappings(array('language', 'title', 'status', 'created', 'changed', 'promote', 'sticky'));

    // Default Mappings.
    $this->addFieldMapping('uid')->defaultValue(1);
    $this->addFieldMapping('revision_uid')->defaultValue(1);
    $this->addFieldMapping('revision')->defaultValue(1);
    $this->addFieldMapping('is_new')->defaultValue(TRUE);

    // Teaser Mapping.
    $this->addFieldMapping('field_content_teaser', 'field_content_teaser_value');
    $this->addFieldMapping('field_content_teaser:format')->defaultValue('filtered_html');

    // Body Field Mapping.
    $this->addFieldMapping('field_content_body', 'field_content_body_value');
    $this->addFieldMapping('field_content_body:format')->defaultValue('full_html');

    // Associated Images Mapping.
    $this->addFieldMapping('field_content_associated_images', 'redcat_new_migration_associated_images_filename');
    $this->addFieldMapping('field_content_associated_images:file_class')->defaultValue('MigrateFileUri');
    $this->addFieldMapping('field_content_associated_images:file_replace')->defaultValue(FILE_EXISTS_RENAME);
    $this->addFieldMapping('field_content_associated_images:preserve_files')->defaultValue(FALSE);
    $this->addFieldMapping('field_content_associated_images:source_dir')->defaultValue($this->getFilesDirectory());
    $this->addFieldMapping('field_content_associated_images:destination_dir', 'redcat_new_migration_associated_images_destination_dir');
    $this->addFieldMapping('field_content_associated_images:alt', 'redcat_new_migration_associated_images_alt');
    $this->addFieldMapping('field_content_associated_images:title', 'redcat_new_migration_associated_images_title');

    // Linked Files Mapping.
    $this->addFieldMapping('field_content_linked_files', 'redcat_new_migration_linked_files_filename');
    $this->addFieldMapping('field_content_linked_files:file_class')->defaultValue('MigrateFileUri');
    $this->addFieldMapping('field_content_linked_files:file_replace')->defaultValue(FILE_EXISTS_RENAME);
    $this->addFieldMapping('field_content_linked_files:preserve_files')->defaultValue(FALSE);
    $this->addFieldMapping('field_content_linked_files:source_dir')->defaultValue($this->getFilesDirectory());
    $this->addFieldMapping('field_content_linked_files:destination_dir', 'redcat_new_migration_linked_files_destination_dir');
    $this->addFieldMapping('field_content_linked_files:description', 'redcat_new_migration_linked_files_description');
    $this->addFieldMapping('field_content_linked_files:display', 'redcat_new_migration_linked_files_display');

    // Unmigrated Mappings.
    $this->addUnmigratedSources(array('vid'));
    $this->addUnmigratedDestinations(array('comment', 'log', 'path', 'tnid', 'field_content_teaser:language', 'field_content_body:language', 'field_content_associated_images:destination_file', 'field_content_linked_files:language', 'field_content_associated_images:language', 'field_content_linked_files:destination_file'));
  }
  
  public function prepareRow($row) {
    $this->prepareAssociatedImagesFileMapping($row);
    $this->prepareLinkedFilesFileMapping($row);
  }
}