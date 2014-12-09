<?php

class RedcatNewMigrationFilesMigration extends RedCatNewMigrationMigrations {

  /**
   * Overrides default constructor.
   */
  public function __construct(array $arguments) {
    $this->arguments = $arguments;
    parent::__construct();
    $this->description = t('Import All Files');

    $source_fields = array(
      'fid' => t('The File ID.'),
    );

    $connection = $this->getDatabaseConnection();
    $query = $connection->select('file_managed', 'fm');
    $query->fields('fm');

    $this->source = new MigrateSourceSQL($query, $source_fields, NULL, array('map_joinable' => FALSE));
    $this->destination = new MigrateDestinationFile('file');

    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'fid' => array(
          'type' => 'int',
          'unsigned' => TRUE,
          'not null' => TRUE,
          'alias' => 'fm',
        )
      ),
      MigrateDestinationFile::getKeySchema()
    );
    
    $this->addFieldMapping('uid')->defaultValue(1);
    $this->addFieldMapping('source_dir')->defaultValue($this->getFilesDirectory());
    $this->addFieldMapping('timestamp', 'timestamp');
    $this->addFieldMapping('value', 'uri');
    $this->addFieldMapping('destination_file', 'uri');
    $this->addFieldMapping('file_replace')->defaultValue('FILE_EXISTS_REUSE');
    $this->addFieldMapping('preserve_files')->defaultValue(TRUE);
    $this->addUnmigratedSources(array('uid', 'filename', 'filemime', 'filesize', 'status', 'type'));
  }
  
  public function prepareRow($current_row) {
    if (strpos($current_row->uri, 'public://') !== FALSE) {
      $current_row->uri = str_replace('public://', '', $current_row->uri);
    }
    else {
      return FALSE;
    }
  }
}
