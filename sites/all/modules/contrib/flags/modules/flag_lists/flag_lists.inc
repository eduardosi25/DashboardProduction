<?php
/**
 * @file
 * Implements flag lists.
 */

class flag_lists extends flag_flag {

function save(&$flag) {
  krumo('here');
  $flag->flag_lists_save($flag);
}

  /**
   * Saves a flag to the database. It is a wrapper around update($flag) and insert($flag).
   */
  function flag_lists_save(&$flag) {
    if (isset($flag->fid)) {
      flag_lists_update($flag);
      $flag->is_new = FALSE;
    }
    else {
      flag_lists_insert($flag);
      $flag->is_new = TRUE;
    }
    // Clear the page cache for anonymous users.
//    cache_clear_all('*', 'cache_page', TRUE);
  }

  /**
   * Saves an existing flag to the database. Better use save($flag).
   */
  function flag_lists_update($flag) {
    db_query("UPDATE {flag_lists_flags} SET title = '%s', name = '%s' WHERE fid = %d", $flag->title, $flag->name, $flag->fid);
  }

  /**
   * Saves a new flag to the database. Better use save($flag).
   */
  function flag_lists_insert($flag) {
    db_query("INSERT INTO {flag_lists_flags} (pfid, uid, content_type, name, title, options) VALUES (%d, %d, '%s', '%s', '%s', '%s')",             $flag->pfid, $flag->uid, $flag->content_type, $flag->name, $flag->title, $flag->get_serialized_options($flag));
    $flag->fid = db_last_insert_id('flags', 'fid');
    $flag->name = 'flag_lists_'. $flag->uid .'_'. $flag->fid;
    $flag->flag_lists_update($flag);

    foreach ($flag->types as $type) {
      db_query("INSERT INTO {flag_types} (fid, type) VALUES (%d, '%s')", $flag->fid, $type);
    }
  }
}