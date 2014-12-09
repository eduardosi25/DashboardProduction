<?php
/**
 * @file
 * Default theme implementation to display a single Drupal page.
 *
 * Available variables:
 *
 * General utility variables:
 * - $base_path: The base URL path of the Drupal installation. At the very
 *   least, this will always default to /.
 * - $directory: The directory the template is located in, e.g. modules/system
 *   or themes/garland.
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
 * - $page['content']: The main content of the current page.
 * - $page['sidebar_first']: Items for the first sidebar.
 * - $page['sidebar_second']: Items for the second sidebar.
 * - $page['header']: Items for the header region.
 * - $page['footer']: Items for the footer region.
 *
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see template_process()
 */
?>
<?php if ($page['prehome'] && count($page['prehome'])>0): ?>
  <div id="prehome" class="sixteen columns">
    <?php print render($page['prehome']); ?>
  </div>
<?php endif; ?>

<?php if ($page['skin_absolute']): ?>
<div id="skin_absolute" class="sixteen columns">
<?php print render($page['skin_absolute']); ?>
</div>
<div class="clear"></div>
<?php endif; ?>

<?php if ($page['aperture']): ?>
<div id="aperture" class="sixteen columns">
<?php print render($page['aperture']); ?>
</div>
<?php endif; ?>

<div class="container" id="content-head">

  <header id="head" role="banner">
  <hgroup class="four columns alpha">
    <div id="logo">
    <?php if ($logo): ?><a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>"><img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>"/></a><?php endif; ?>
    <?php if ($site_slogan): ?><div class="site-slogan"><?php print $site_slogan; ?></div><!--site slogan--><?php endif; ?>
    </div>
  </hgroup>
    
  <div class="twelve columns omega" id="headright">
    
    <?php if ($page['searching']): ?>
    <div id="search" class="five columns">
    <?php print render($page['searching']); ?>
    </div>
    <?php endif; ?>
    
    <?php if (theme_get_setting('socialicon_display', 'rsvponline')): ?>
    <?php 
    $twitter_url = check_plain(theme_get_setting('twitter_url', 'rsvponline')); 
    $facebook_url = check_plain(theme_get_setting('facebook_url', 'rsvponline')); 
    $googleplus_url = check_plain(theme_get_setting('googleplus_url', 'rsvponline')); 
    $youtube_url = check_plain(theme_get_setting('youtube_url', 'rsvponline'));
    $instagram_url = check_plain(theme_get_setting('instagram_url', 'rsvponline'));
    $theme_path_social = base_path() . drupal_get_path('theme', 'rsvponline');
    ?>
    <div id="socialbar">
      <ul class="social">
    <?php if ($facebook_url): ?><li> <a href="<?php print $facebook_url; ?>" target="_blank"> <span class="social-button-facebook"> </span> </a> </li> <?php endif; ?>
    <?php if ($twitter_url): ?><li> <a href="<?php print $twitter_url; ?>" target="_blank"> <span class="social-button-twitter"> </span> </a> </li> <?php endif; ?>
    <?php if ($googleplus_url): ?><li> <a href="<?php print $googleplus_url; ?>" target="_blank"> <span class="social-button-googleplus"> </span> </a> </li> <?php endif; ?>
    <?php if ($youtube_url): ?><li> <a href="<?php print $youtube_url; ?>" target="_blank"> <span class="social-button-youtube"> </span> </a> </li> <?php endif; ?>
    <?php if ($instagram_url): ?><li> <a href="<?php print $instagram_url; ?>" target="_blank"> <span class="social-button-instagram"> </span> </a> </li> <?php endif; ?>
    <?php /*<li> <a href="<?php print $front_page; ?>rss.xml"> <span class="social-button-rss"> </span> </a> </li>*/?>
      </ul>
    </div>
    <?php endif; ?>

   </div>
  </header>
  
  <div id="container-navigation" class="sixteen columns">
    <nav id="navigation" role="navigation">
      <div id="main-menu">
        <?php 
          if (module_exists('i18n')) {
            $main_menu_tree = i18n_menu_translated_tree(variable_get('menu_main_links_source', 'main-menu'));
          } else {
            $main_menu_tree = menu_tree(variable_get('menu_main_links_source', 'main-menu'));
          }
          print drupal_render($main_menu_tree);
        ?>
       </div>
    </nav><!-- end main-menu -->
  </div>

</div>

<?php if ($page['skin_fixed']): ?>
<div id="skin_fixed" class="sixteen columns">
<?php print render($page['skin_fixed']); ?>
</div>
<div class="clear"></div>
<?php endif; ?>

  
<div class="container" id="content-contain">

  <?php if ($is_front): ?>
  <div class="container">
    <?php if ($page['front_welcome']): ?>
    <div id="front-welcome"> <?php print render($page['front_welcome']); ?></div>
    <?php endif; ?>
  </div>
  <?php endif; ?>
  
  <?php if ($page['header']): ?>
  <div id="header" class="sixteen columns">
  <?php print render($page['header']); ?>
  </div>
  <div class="clear"></div>
  <?php endif; ?>
  
  <?php if ($page['help']): ?>
  <div id="help" class="sixteen columns">
  <?php print render($page['help']); ?>
  </div>
  <div class="clear"></div>
  <?php endif; ?>
  
  <?php if($page['sidebar_first']) { $contentwid= "eleven"; } else { $contentwid= "sixteen"; } ?>
  <div id="breadcrumbs" class="sixteen columns"><?php if (theme_get_setting('breadcrumbs', 'rsvponline')): ?><?php if ($breadcrumb): print $breadcrumb; endif;?><?php endif; ?></div>
    
  <div id="content" name="content" class="<?php print $contentwid; ?> columns">
    <section id="post-content" role="main">
    <?php print $messages; ?>
    <?php if ($page['content_top']): ?><div id="content_top"><?php print render($page['content_top']); ?></div><?php endif; ?>
    <?php if (!empty($tabs['#primary'])): ?><div class="tabs-wrapper"><?php print render($tabs); ?></div><?php endif; ?>
    <?php if ($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>
    <?php print render($page['content']); ?>
    <?php print render($page['content_bottom']); ?>
    </section> <!-- /#main -->
  </div>

  <?php if ($page['sidebar_first_top'] || $page['sidebar_first']): ?>
  <div id="sidebar" class="sidebar five columns">
    <?php if ($page['sidebar_first_top']): ?>
    <div id="sidebar-first-top" role="complementary" class="sidebar">
    <?php print render($page['sidebar_first_top']); ?>
    </div>  <!-- /#sidebar-first -->
    <?php endif; ?>
    <?php $class=arg(0)=='node' ? 'sticky' : ''; ?>
    <?php if ($page['sidebar_first']): ?>
    <div id="sidebar-first" role="complementary" class="sidebar">
      <div id="sidebar-first-sticky" class="<?php print $class;?>">
        <?php print render($page['sidebar_first']); ?>
      </div>
    </div>  <!-- /#sidebar-first -->
    <?php endif; ?>
  </div>
  <div class="clear"></div>
  <?php endif; ?>
  
  
  <?php if($page['sidebar_second']) { $contentwid= "eleven"; } else { $contentwid= "sixteen"; } ?>
  
  <?php if (count($page['sidebar_second'])>1): ?>
  <aside id="sidebar-second" role="complementary" class="sidebar five columns">
  <?php print render($page['sidebar_second']); ?>
  </aside>  <!-- /#sidebar-second -->
  <?php endif; ?>

  <?php if (count($page['stack_top'])>1 || count($page['stack'])>1 || count($page['stack_bottom'])>1 ): ?>
  <div id="stack" class="<?php print $contentwid; ?> columns">
    <section id="stack-content" role="complementary">
    <?php if ($page['stack_top']): ?><div id="stack_top"><?php print render($page['stack_top']); ?></div><?php endif; ?>
    <?php if ($page['stack']): ?><div id="stack"><?php print render($page['stack']); ?></div><?php endif; ?>
    <?php if ($page['stack_bottom']): ?><div id="stack_bottom"><?php print render($page['stack_bottom']); ?></div><?php endif; ?>
    </section> <!-- /#stack -->
  </div>
  <?php endif; ?>
  
  <div class="clear"></div>  

  <?php if (count($page['footer_top'])>1): ?>
  <div id="footer_top" class="sixteen columns">
  <?php print render($page['footer_top']) ?>
  </div>
  <?php endif; ?>

  <?php if (count($page['footer'])>1): ?>
  <div id="footer" class="sixteen columns">
  <?php print render($page['footer']) ?>
  </div>
  <?php endif; ?>

  <?php if (count($page['footer_bottom'])>1): ?>
  <div id="footer_bottom" class="sixteen columns">
  <?php print render($page['footer_bottom']) ?>
  </div>
  <?php endif; ?>
  
</div>
 
<?php if (count($page['footer_first'])>1 || count($page['footer_second'])>1 || count($page['footer_third'])>1 || count($page['footer_fourth'])>1 ): ?>
  <div id="bottom" class="container">
  <?php $botomwid = "four"; $bottom = ((bool) $page['footer_first'] + (bool) $page['footer_second'] + (bool) $page['footer_third'] + (bool) $page['footer_fourth']);
    switch ($bottom) { 
      case 1: $botomwid = "sixteen"; break; case 2: $botomwid = "eight"; break;
      case 3: $botomwid = "five"; break; case 4: $botomwid = "four";
    } ?>
    <?php if ($page['footer_first']): ?>
    <div class="<?php print $botomwid; ?> columns botblck"><?php print render($page['footer_first']); ?></div>
    <?php endif; ?>
    <?php if ($page['footer_second']): ?>
    <div class="<?php print $botomwid; ?> columns botblck"><?php print render($page['footer_second']); ?></div>
    <?php endif; ?>
    <?php if ($page['footer_third']): ?>
    <div class="<?php print $botomwid; ?> columns botblck"><?php print render($page['footer_third']); ?></div>
    <?php endif; ?>
    <?php if ($page['footer_fourth']): ?>
    <div class="<?php print $botomwid; ?> columns botblck"><?php print render($page['footer_fourth']); ?></div>
    <?php endif; ?>
    </div>
<?php endif; ?>
  
<?php if (count($page['closure'])>1): ?>
<div id="closure" class="sixteen columns">
<?php print render($page['closure']); ?>
</div>
<div class="clear"></div>
<?php endif; ?>