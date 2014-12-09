<?php
class ArticlesMigration extends Migration {
  /**
   * Class constructor, the one that initiates the process
   */
  public function __construct() {
    // Process initialization
    parent::__construct();
    
    // Give a description to this process
    $this->description = t('Migrate RSVP articles');
    
    $source_fields = array(
      'nid' => t('The node ID of the page'),
      'term_node' => t('Taxonomy terms for node'),
    );
    
    // Prepare the query that will retrieve the data from the source
    // tables. One iteration for each record retrieved.
    $query = db_select(MIGRATE_RSVP_DATABASE_NAME .'.node', 'n')
      ->fields('n', array('nid', 'vid', 'type', 'language', 'title', 'uid', 'status', 'created', 'changed', 'comment', 'promote', 'moderate', 'sticky', 'tnid', 'translate'))
      ->condition('n.type', 'story', '=');
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
    
    // Instance of the source data object, populated with
    // source data from the query above
    $this->source = new MigrateSourceSQL($query, $source_fields);
    
    // Instance for the destination data object
    $this->destination = new MigrateDestinationNode('article');
    
    // Map the field that uniquely identifies a row in the source
    // tables. This is necessary if you want to be able to rollback
    // and run the process for updating existing data
    // The data type of the unique field must be specified
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
    //Misc Fields
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
      $this->addFieldMapping('timestamp', 'timestamp');
    }

    $arguments = MigrateTextFieldHandler::arguments(NULL, filter_default_format());
    // Carousel
    $this->addFieldMapping('field_title_carrusel', 'field_title_carrusel_value')->arguments($arguments);
    $this->addFieldMapping('field_sinopsis_carrusel', 'field_sinopsis_carrusel_value')->arguments($arguments);
    // Authoring
    $this->addFieldMapping('field_author_content', 'field_author_content_value')->arguments($arguments);
    $this->addFieldMapping('field_author_image', 'field_author_image_value')->arguments($arguments);
   
    // We conditionally DNM these fields, so your field mappings will be clean
    // whether or not you have path and or path auto enabled
    if (module_exists('path')) {
      $this->addFieldMapping('path')->issueGroup(t('DNM'));
      if (module_exists('pathauto')) {
        $this->addFieldMapping('pathauto')->issueGroup(t('DNM'));
      }
    }
    
    //Field tags
    $this->addFieldMapping('field_tags', 'term_node')->defaultValue('tid');
  }

  /**
   * The function prepareRow can't be overwrited in order to do some custom
   * processing when the source data has been read. The $row object contains
   * the field values of the current row being processed.
   *
   * In our case we use it to process the special mappings for the cover, main
   * and galleries images. To achieve this we have defined a custom
   * that we call for each field of type image or file.
   */
  public function prepareRow($row) {
    
    $this->prepareTermNodes($row);
    
    return true;
  }
  
  /***
   * 
   */
  private function prepareTermNodes($row){
    $row->field_tags=array();
    
    $query = db_select(MIGRATE_RSVP_DATABASE_NAME .'.term_node', 'tn');
    $query->join(MIGRATE_RSVP_DATABASE_NAME .'.node', 'n', 'n.nid = tn.nid');
    $query->join(MIGRATE_RSVP_DATABASE_NAME .'.term_data', 'td', 'td.tid = tn.tid');
    $query->condition('n.status', 1, '=');
    $query->condition('tn.nid', $row->nid, '=');
    $query->condition('td.vid', 3, '=');
    
    $query->addField('tn', 'tid');
    $query->addField('td', 'name');
    $results=$query->execute();
    foreach($results as $result){
      $row->field_tags[]=$result->name;  
    }
  }
}
