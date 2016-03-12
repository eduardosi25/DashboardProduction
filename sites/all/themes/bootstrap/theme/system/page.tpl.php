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
$width='';
if(arg(0)==='sipi' || arg(0)==='codiga'){
  $front_page='codiga';
  $logo="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAASwAAACWCAYAAABkW7XSAAAAGXRFWHRTb2Z0d2FyZQBBZG9iZSBJbWFnZVJlYWR5ccllPAAAAyZpVFh0WE1MOmNvbS5hZG9iZS54bXAAAAAAADw/eHBhY2tldCBiZWdpbj0i77u/IiBpZD0iVzVNME1wQ2VoaUh6cmVTek5UY3prYzlkIj8+IDx4OnhtcG1ldGEgeG1sbnM6eD0iYWRvYmU6bnM6bWV0YS8iIHg6eG1wdGs9IkFkb2JlIFhNUCBDb3JlIDUuNi1jMDY3IDc5LjE1Nzc0NywgMjAxNS8wMy8zMC0yMzo0MDo0MiAgICAgICAgIj4gPHJkZjpSREYgeG1sbnM6cmRmPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5LzAyLzIyLXJkZi1zeW50YXgtbnMjIj4gPHJkZjpEZXNjcmlwdGlvbiByZGY6YWJvdXQ9IiIgeG1sbnM6eG1wPSJodHRwOi8vbnMuYWRvYmUuY29tL3hhcC8xLjAvIiB4bWxuczp4bXBNTT0iaHR0cDovL25zLmFkb2JlLmNvbS94YXAvMS4wL21tLyIgeG1sbnM6c3RSZWY9Imh0dHA6Ly9ucy5hZG9iZS5jb20veGFwLzEuMC9zVHlwZS9SZXNvdXJjZVJlZiMiIHhtcDpDcmVhdG9yVG9vbD0iQWRvYmUgUGhvdG9zaG9wIENDIDIwMTUgKFdpbmRvd3MpIiB4bXBNTTpJbnN0YW5jZUlEPSJ4bXAuaWlkOkE2Qzc2RERDODhBODExRTVCMTc3RDQxRkQ4QTFDODA4IiB4bXBNTTpEb2N1bWVudElEPSJ4bXAuZGlkOkE2Qzc2REREODhBODExRTVCMTc3RDQxRkQ4QTFDODA4Ij4gPHhtcE1NOkRlcml2ZWRGcm9tIHN0UmVmOmluc3RhbmNlSUQ9InhtcC5paWQ6QTZDNzZEREE4OEE4MTFFNUIxNzdENDFGRDhBMUM4MDgiIHN0UmVmOmRvY3VtZW50SUQ9InhtcC5kaWQ6QTZDNzZEREI4OEE4MTFFNUIxNzdENDFGRDhBMUM4MDgiLz4gPC9yZGY6RGVzY3JpcHRpb24+IDwvcmRmOlJERj4gPC94OnhtcG1ldGE+IDw/eHBhY2tldCBlbmQ9InIiPz60YSrjAAAzgklEQVR42ux9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";
  $width=" width=200px; ";
}
?>
<header id="navbar" role="banner" class="<?php print $navbar_classes; ?>">
  <div class="container">
    <div class="navbar-header">
      <?php if ($logo): ?>
      <a class="logo navbar-btn pull-left" href="/<?php print $front_page; ?>" title="<?php print t('Home'); ?>">
        <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" <?php print $width;?>/>
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
