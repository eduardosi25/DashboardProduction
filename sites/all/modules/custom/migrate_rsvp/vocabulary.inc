<?php
class VocabularyMigration extends Migration {
  public function __construct() {
    parent::__construct();
    $this->description = t('Migrate RSVP taxonomy terms vocabulary main');

    $source_fields = array(
      'tid' => t('Taxonomy ID'),
    );

    $query = db_select(MIGRATE_RSVP_DATABASE_NAME .'.term_data', 'td')
      ->fields('td', array('tid', 'vid', 'name', 'description', 'weight'))
      ->condition('td.vid', 2, '=');

    $this->source = new MigrateSourceSQL($query, $source_fields);
    $term_options = MigrateDestinationTerm::options(LANGUAGE_NONE, 'filtered_html');
    $this->destination = new MigrateDestinationTerm('tags', $term_options);

    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'tid' => array(
          'type' => 'int',
          'unsigned' => TRUE,
          'not null' => TRUE,
          'description' => 'D6 Unique Taxonomy Term ID',
          'alias' => 'td',
        )
      ),
      MigrateDestinationTerm::getKeySchema()
    );
    
    //Mapping fields
    $this->addFieldMapping('name', 'name');
    $this->addFieldMapping('description', 'description');
    $this->addFieldMapping('weight', 'weight');
    $this->addFieldMapping('format')->defaultValue('filtered_html');
    $this->addFieldMapping('parent')->defaultValue('0');
    $this->addFieldMapping('parent_name')->defaultValue('');
    $this->addFieldMapping('path')->issueGroup(t('DNM'));
    $this->addFieldMapping('pathauto_perform_alias')->defaultValue('1');
  }
  
  public function prepareRow($current_row) {
    return TRUE;
  }
}
