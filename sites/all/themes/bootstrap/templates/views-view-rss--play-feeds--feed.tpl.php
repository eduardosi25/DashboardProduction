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
<rss version="2.0">
  <channel>
    <title><?php print $channel->name; ?></title>
    <link><?php print isset($channel->field_link['und'][0]['value']) && !empty($channel->field_link['und'][0]['value']) ? $channel->field_link['und'][0]['value'] : ''; ?></link>
    <description><?php print strip_tags($channel->description); ?></description>
    <language>es</language>
    <?php print $channel_elements; ?>
    <?php print $items; ?>
  </channel>
</rss>
