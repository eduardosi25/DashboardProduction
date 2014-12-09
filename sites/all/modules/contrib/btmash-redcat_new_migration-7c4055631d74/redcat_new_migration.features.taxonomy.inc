<?php
/**
 * @file
 * redcat_new_migration.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function redcat_new_migration_taxonomy_default_vocabularies() {
  return array(
    'tags' => array(
      'name' => 'REDCAT Event Type',
      'machine_name' => 'tags',
      'description' => 'Select the types of events that this event belongs to.',
      'hierarchy' => '0',
      'module' => 'taxonomy',
      'weight' => '0',
      'rdf_mapping' => array(
        'rdftype' => array(
          0 => 'skos:ConceptScheme',
        ),
        'name' => array(
          'predicates' => array(
            0 => 'dc:title',
          ),
        ),
        'description' => array(
          'predicates' => array(
            0 => 'rdfs:comment',
          ),
        ),
      ),
    ),
  );
}
