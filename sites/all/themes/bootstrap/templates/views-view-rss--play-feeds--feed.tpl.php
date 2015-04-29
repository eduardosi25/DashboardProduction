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
<rss version="2.0" xmlns:media="http://search.yahoo.com/mrss/" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:ext="http://ooyala.com/syndication/ext/" xmlns:mediasl="http://www.slide.com/funspace/developer/" xmlns:itunes="http://www.itunes.com/dtds/podcast-1.0.dtd" xmlns:boxee="http://boxee.tv/spec/rss/">
  <channel>
    <title><?php print $channel->name; ?></title>
    <link><?php print $channel->field_content['und'][0]['value']; ?></link>
    <description><?php print strip_tags($channel->description); ?></description>
    <language>es</language>
    <?php print $channel_elements; ?>
    <?php print $items; ?>
  </channel>
</rss>
