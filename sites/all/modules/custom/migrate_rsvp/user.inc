<?php
class UserMigration extends Migration {
  public function __construct() {
    parent::__construct();
    $this->description = t('Migrate RSVP users');

    $source_fields = array(
      'uid' => t('User ID'),
      'roles' => t('The set of roles assigned to a user.'),
    );

    $query = db_select(MIGRATE_RSVP_DATABASE_NAME .'.users', 'u')
      ->fields('u', array('uid', 'name', 'pass', 'mail', 'created', 'access', 'login', 'status', 'init'))
      ->condition('u.name', array('admin', 'webmaster'), 'NOT IN')
      ->condition('u.uid', 0, '>');
    $query->join(MIGRATE_RSVP_DATABASE_NAME .'.users_roles', 'ur', 'ur.uid = u.uid');
    $query->distinct();
      
    $this->source = new MigrateSourceSQL($query, $source_fields);
    $this->destination = new MigrateDestinationUser();

    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'uid' => array(
          'type' => 'int',
          'unsigned' => TRUE,
          'not null' => TRUE,
          'description' => 'D6 Unique User ID',
          'alias' => 'u',
        )
      ),
      MigrateDestinationUser::getKeySchema()
    );

    // Make the mappings
    $this->addFieldMapping('name', 'name')->dedupe('users', 'name');
    $this->addFieldMapping('is_new')->defaultValue(TRUE);
    $this->addFieldMapping('pass', 'pass');
    $this->addFieldMapping('mail', 'mail')->dedupe('users', 'mail');
    $this->addFieldMapping('language')->defaultValue('');
    $this->addFieldMapping('theme')->defaultValue('');
    $this->addFieldMapping('signature')->defaultValue('');
    $this->addFieldMapping('signature_format')->defaultValue('filtered_html');
    $this->addFieldMapping('created', 'created');
    $this->addFieldMapping('access', 'access');
    $this->addFieldMapping('login', 'login');
    $this->addFieldMapping('status', 'status');
    $this->addFieldMapping('picture')->defaultValue(0);
    $this->addFieldMapping('init', 'init');
    $this->addFieldMapping('timezone')->defaultValue(NULL);
    $this->addFieldMapping('path')->issueGroup(t('DNM'));
    $this->addFieldMapping('pathauto_perform_alias')->defaultValue('1');
    $this->addFieldMapping('roles', 'roles');
  }
  
  public function prepareRow($current_row) {
    $source_id = $current_row->uid;
    $query = db_select(MIGRATE_RSVP_DATABASE_NAME .'.users_roles', 'r')
      ->fields('r', array('uid', 'rid'))
      ->condition('r.uid', $source_id, '=');
    $results = $query->execute();
    $roles = array('2' => '2');
    foreach ($results as $row) {
      $roles[$row->rid] = $row->rid;
    }
    $current_row->roles = $roles;
    return TRUE;
    // return FALSE if you wish to skip a particular row
  }
}
