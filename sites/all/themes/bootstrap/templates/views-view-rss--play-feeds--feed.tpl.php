<?php
/**
 * @file views-view-rss.tpl.php
 * invent.PLAY Feeds view template.
 *
 * Variables available:
 * - $header: The view header
 * - $footer: The view footer
 * - $rows: The results of the view query, if any
 * - $feed_icon: Feed icon to display, if any
 * @ingroup views_templates
 */
$channel=taxonomy_term_load(arg(2));
?>
<?php print "<?xml"; ?> version="1.0" encoding="utf-8" <?php print "?>\n"; ?>
<rss version="2.0" xmlns:media="http://search.yahoo.com/mrss/" xmlns:dc="http://purl.org/dc/elements/1.1/" xmlns:content="http://purl.org/rss/1.0/modules/content/" xmlns:foaf="http://xmlns.com/foaf/0.1/" xmlns:og="http://ogp.me/ns#" xmlns:rdfs="http://www.w3.org/2000/01/rdf-schema#" xmlns:sioc="http://rdfs.org/sioc/ns#" xmlns:sioct="http://rdfs.org/sioc/types#" xmlns:skos="http://www.w3.org/2004/02/skos/core#" xmlns:xsd="http://www.w3.org/2001/XMLSchema#">
  <channel>
    <title><?php print $channel->name; ?></title>
    <link><?php print isset($channel->field_link['und'][0]['value']) && !empty($channel->field_link['und'][0]['value']) ? $channel->field_link['und'][0]['value'] : ''; ?></link>
    <description><?php print strip_tags($channel->description); ?></description>
    <language>es</language>
    <?php print $channel_elements; ?>
    <?php print $items; ?>
  </channel>
</rss>
