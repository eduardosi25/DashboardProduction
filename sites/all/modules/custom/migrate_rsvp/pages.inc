<?php
class PagesMigration extends Migration {
  public function __construct() {
    parent::__construct();
    
    $this->description = t('Migrate RSVP pages');
    
    $source_fields = array(
      'nid' => t('The node ID of the page'),
    );
    
    $query = db_select(MIGRATE_RSVP_DATABASE_NAME .'.node', 'n')
      ->fields('n', array('nid', 'vid', 'type', 'language', 'title', 'uid', 'status', 'created', 'changed', 'comment', 'promote', 'moderate', 'sticky', 'tnid', 'translate'))
      ->condition('n.type', 'page', '=');
    $query->join(MIGRATE_RSVP_DATABASE_NAME .'.node_revisions', 'nr', 'n.vid = nr.vid');
    $query->addField('nr', 'body');
    $query->addField('nr', 'teaser');
    $query->join(MIGRATE_RSVP_DATABASE_NAME .'.users', 'u', 'n.uid = u.uid');
    $query->addField('u', 'name');
    $query->orderBy('n.changed');
    
    $this->highwaterField = array(
      'name' => 'changed', // Column to be used as highwater mark
      'alias' => 'n',      // Table alias containing that column
    );
    
    $this->source = new MigrateSourceSQL($query, $source_fields);
    $this->destination = new MigrateDestinationNode('redcat_general');
    
    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'nid' => array(
          'type' => 'int',
          'unsigned' => TRUE,
          'not null' => TRUE,
          'description' => 'D6 Unique Node ID',
          'alias' => 'n',
        )
      ),
      MigrateDestinationNode::getKeySchema()
    );
    
    // Make the mappings
    $this->addFieldMapping('title', 'title');
    $this->addFieldMapping('is_new')->defaultValue(TRUE);
    $this->addFieldMapping('uid', 'uid');
    $this->addFieldMapping('revision')->defaultValue(TRUE);
    $this->addFieldMapping('revision_uid', 'uid');
    $this->addFieldMapping('created', 'created');
    $this->addFieldMapping('changed', 'changed');
    $this->addFieldMapping('status', 'status');
    $this->addFieldMapping('promote', 'promote');
    $this->addFieldMapping('sticky', 'sticky');
    $this->addFieldMapping('comment', 'comment');
    $this->addFieldMapping('language')->defaultValue('und');

    $body_arguments = MigrateTextFieldHandler::arguments(NULL, filter_default_format());
    $this->addFieldMapping('field_content_body', 'body')->arguments($body_arguments);

    $body_arguments = MigrateTextFieldHandler::arguments(NULL, filter_default_format());
    $this->addFieldMapping('field_content_teaser', 'teaser')->arguments($body_arguments);

    $this->addFieldMapping(NULL, 'name');
    $this->addFieldMapping(NULL, 'vid');
    $this->addFieldMapping(NULL, 'type');
    $this->addFieldMapping(NULL, 'language');
    $this->addFieldMapping(NULL, 'moderate');
    $this->addFieldMapping(NULL, 'tnid');
    $this->addFieldMapping(NULL, 'translate');
    
    // We conditionally DNM these fields, so your field mappings will be clean
    // whether or not you have path and or pathauto enabled
    if (module_exists('path')) {
      $this->addFieldMapping('path')->issueGroup(t('DNM'));
      if (module_exists('pathauto')) {
        $this->addFieldMapping('pathauto')->issueGroup(t('DNM'));
      }
    }
  }
  
  public function prepareRow($current_row) {
    return TRUE;
  }
}
