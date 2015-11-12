<?php
/**
 * @file
 * Default theme implementation to display a single Drupal page.
 *
 * The doctype, html, head and body tags are not in this template. Instead they
 * can be found in the html.tpl.php template in this directory.
 *
 * Available variables:
 *
 * General utility variables:
 * - $base_path: The base URL path of the Drupal installation. At the very
 *   least, this will always default to /.
 * - $directory: The directory the template is located in, e.g. modules/system
 *   or themes/bartik.
 * - $is_front: TRUE if the current page is the front page.
 * - $logged_in: TRUE if the user is registered and signed in.
 * - $is_admin: TRUE if the user has permission to access administration pages.
 *
 * Site identity:
 * - $front_page: The URL of the front page. Use this instead of $base_path,
 *   when linking to the front page. This includes the language domain or
 *   prefix.
 * - $logo: The path to the logo image, as defined in theme configuration.
 * - $site_name: The name of the site, empty when display has been disabled
 *   in theme settings.
 * - $site_slogan: The slogan of the site, empty when display has been disabled
 *   in theme settings.
 *
 * Navigation:
 * - $main_menu (array): An array containing the Main menu links for the
 *   site, if they have been configured.
 * - $secondary_menu (array): An array containing the Secondary menu links for
 *   the site, if they have been configured.
 * - $breadcrumb: The breadcrumb trail for the current page.
 *
 * Page content (in order of occurrence in the default page.tpl.php):
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title: The page title, for use in the actual HTML content.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 * - $messages: HTML for status and error messages. Should be displayed
 *   prominently.
 * - $tabs (array): Tabs linking to any sub-pages beneath the current page
 *   (e.g., the view and edit tabs when displaying a node).
 * - $action_links (array): Actions local to the page, such as 'Add menu' on the
 *   menu administration interface.
 * - $feed_icons: A string of all feed icons for the current page.
 * - $node: The node object, if there is an automatically-loaded node
 *   associated with the page, and the node ID is the second argument
 *   in the page's path (e.g. node/12345 and node/12345/revisions, but not
 *   comment/reply/12345).
 *
 * Regions:
 * - $page['help']: Dynamic help text, mostly for admin pages.
 * - $page['highlighted']: Items for the highlighted content region.
 * - $page['content']: The main content of the current page.
 * - $page['sidebar_first']: Items for the first sidebar.
 * - $page['sidebar_second']: Items for the second sidebar.
 * - $page['header']: Items for the header region.
 * - $page['footer']: Items for the footer region.
 *
 * @see bootstrap_preprocess_page()
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see bootstrap_process_page()
 * @see template_process()
 * @see html.tpl.php
 *
 * @ingroup themeable
 */
if(arg(0)==='sipi' || arg(0)==='codiga'){
  $front_page='codiga';
  $logo="data:image/png;base64,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";
}
?>
<header id="navbar" role="banner" class="<?php print $navbar_classes; ?>">
  <div class="container">
    <div class="navbar-header">
      <?php if ($logo): ?>
      <a class="logo navbar-btn pull-left" href="/<?php print $front_page; ?>" title="<?php print t('Home'); ?>">
        <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
      </a>
      <?php endif; ?>

      <?php if (!empty($site_name)): ?>
      <a class="name navbar-brand" href="/<?php print $front_page; ?>" title="<?php print t('Home'); ?>"><?php print $site_name; ?></a>
      <?php endif; ?>

      <!-- .btn-navbar is used as the toggle for collapsed navbar content -->
      <button type="button" class="navbar-toggle" data-toggle="collapse" data-target=".navbar-collapse">
        <span class="sr-only">Toggle navigation</span>
        <span class="icon-bar"></span>
        <span class="icon-bar"></span>
        <span class="icon-bar"></span>
      </button>
    </div>

    <?php if (!empty($primary_nav) || !empty($secondary_nav) || !empty($page['navigation'])): ?>
      <div class="navbar-collapse collapse">
        <nav role="navigation">
          <?php if (!empty($primary_nav)): ?>
            <?php print render($primary_nav); ?>
          <?php endif; ?>
          <?php if (!empty($secondary_nav)): ?>
            <?php print render($secondary_nav); ?>
          <?php endif; ?>
          <?php if (!empty($page['navigation'])): ?>
            <?php print render($page['navigation']); ?>
          <?php endif; ?>
        </nav>
      </div>
    <?php endif; ?>
  </div>
</header>

<div class="main-container container">

  <header role="banner" id="page-header">
    <?php if (!empty($site_slogan)): ?>
      <p class="lead"><?php print $site_slogan; ?></p>
    <?php endif; ?>

    <?php print render($page['header']); ?>
  </header> <!-- /#page-header -->

  <div class="row">

    <?php if (!empty($page['sidebar_first'])): ?>
      <aside class="col-sm-3" role="complementary">
        <?php print render($page['sidebar_first']); ?>
      </aside>  <!-- /#sidebar-first -->
    <?php endif; ?>

    <section<?php print $content_column_class; ?>>
      <?php if (!empty($page['highlighted'])): ?>
        <div class="highlighted jumbotron"><?php print render($page['highlighted']); ?></div>
      <?php endif; ?>
      <?php if (!empty($breadcrumb)): print $breadcrumb; endif;?>
      <a id="main-content"></a>
      <?php print render($title_prefix); ?>
      <?php if (!empty($title)): ?>
        <h1 class="page-header"><?php print $title; ?></h1>
      <?php endif; ?>
      <?php print render($title_suffix); ?>
      <?php print $messages; ?>
      <?php if (!empty($tabs)): ?>
        <?php print render($tabs); ?>
      <?php endif; ?>
      <?php if (!empty($page['help'])): ?>
        <?php print render($page['help']); ?>
      <?php endif; ?>
      <?php if (!empty($action_links)): ?>
        <ul class="action-links"><?php print render($action_links); ?></ul>
      <?php endif; ?>
      <?php print render($page['content']); ?>
    </section>

    <?php if (!empty($page['sidebar_second'])): ?>
      <aside class="col-sm-3" role="complementary">
        <?php print render($page['sidebar_second']); ?>
      </aside>  <!-- /#sidebar-second -->
    <?php endif; ?>

  </div>
</div>
<footer class="footer container">
  <?php print render($page['footer']); ?>
</footer>
