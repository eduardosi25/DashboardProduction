<?php
class GalleriesMigration extends Migration {
  public function __construct() {
    parent::__construct();
    
    $this->description = t('Migrate RSVP galleries');
    
    $source_fields = array(
      'nid' => t('The node ID of the page'),
      'term_node' => t('Taxonomy terms for node'),
    );
    
    $query = db_select(MIGRATE_RSVP_DATABASE_NAME .'.node', 'n')
      ->fields('n', array('nid', 'vid', 'type', 'language', 'title', 'uid', 'status', 'created', 'changed', 'comment', 'promote', 'moderate', 'sticky', 'tnid', 'translate'))
      ->condition('n.type', 'gallerie', '=');
    $query->join(MIGRATE_RSVP_DATABASE_NAME .'.node_revisions', 'nr', 'n.vid = nr.vid');
    $query->addField('nr', 'body');
    $query->addField('nr', 'teaser');
    $query->join(MIGRATE_RSVP_DATABASE_NAME .'.users', 'u', 'n.uid = u.uid');
    $query->addField('u', 'name');
    //Carrusel
    $query->join(MIGRATE_RSVP_DATABASE_NAME .'.content_field_title_carrusel', 'ftc', 'ftc.nid=n.nid');
    $query->addField('ftc', 'field_title_carrusel_value');
    $query->join(MIGRATE_RSVP_DATABASE_NAME .'.content_field_sinopsis_carrusel', 'fsc', 'fsc.nid=n.nid');
    $query->addField('fsc', 'field_sinopsis_carrusel_value');
    //Autoria
    $query->join(MIGRATE_RSVP_DATABASE_NAME .'.content_field_author_content', 'fac', 'fac.nid=n.nid');
    $query->addField('fac', 'field_author_content_value');
    $query->join(MIGRATE_RSVP_DATABASE_NAME .'.content_field_author_image', 'fai', 'fai.nid=n.nid');
    $query->addField('fai', 'field_author_image_value');
        
    
    
    $query->orderBy('n.nid');
    
    $this->highwaterField = array(
      'name' => 'changed', // Column to be used as highwater mark
      'alias' => 'n',      // Table alias containing that column
    );
    
    $this->source = new MigrateSourceSQL($query, $source_fields);
    $this->destination = new MigrateDestinationNode('gallerie');
    
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
    //Body
    $body_arguments = MigrateTextFieldHandler::arguments(NULL, filter_default_format());
    $this->addFieldMapping('body', 'body')->arguments($body_arguments);
    $body_arguments = MigrateTextFieldHandler::arguments(NULL, filter_default_format());
    $this->addFieldMapping('body:summary', 'teaser')->arguments($body_arguments);
    
    $this->addFieldMapping(NULL, 'name');
    $this->addFieldMapping(NULL, 'vid');
    $this->addFieldMapping(NULL, 'type');
    $this->addFieldMapping(NULL, 'language');
    $this->addFieldMapping(NULL, 'moderate');
    $this->addFieldMapping(NULL, 'tnid');
    $this->addFieldMapping(NULL, 'translate');
        
    //Statistics
    if (module_exists('statistics')) {
      $query->join(MIGRATE_RSVP_DATABASE_NAME .'.node_counter', 'nc', 'nc.nid = n.nid');
      $query->addField('nc', 'totalcount');
      $query->addField('nc', 'daycount');
      $query->addField('nc', 'timestamp');
      //Add fields
      $this->addFieldMapping('totalcount', 'totalcount');
      $this->addFieldMapping('daycount', 'daycount');
      $this->addFieldMapping('timestamp', 'timestamp')->default;
    }

    $arguments = MigrateTextFieldHandler::arguments(NULL, filter_default_format());
    //Carrusel
    $this->addFieldMapping('field_title_carrusel', 'field_title_carrusel_value')->arguments($arguments);
    $this->addFieldMapping('field_sinopsis_carrusel', 'field_sinopsis_carrusel_value')->arguments($arguments);
    //Autoria
    $this->addFieldMapping('field_author_content', 'field_author_content_value')->arguments($arguments);
    $this->addFieldMapping('field_author_image', 'field_author_image_value')->arguments($arguments);
   
    // We conditionally DNM these fields, so your field mappings will be clean
    // whether or not you have path and or pathauto enabled
    if (module_exists('path')) {
      $this->addFieldMapping('path')->issueGroup(t('DNM'));
      if (module_exists('pathauto')) {
        $this->addFieldMapping('pathauto')->issueGroup(t('DNM'));
      }
    }
    
    //Field tags
    $this->addFieldMapping('field_tags', 'term_node')->defaultValue('tid');
  }
  
  public function prepareRow($row) {
    
    return TRUE;
  }
}
