<!DOCTYPE html>
<head>
<?php print $head; ?>
<title><?php print $head_title; ?></title>
<?php print $styles; ?>
<?php print $scripts; ?>
<!--[if lt IE 9]><script src="http://html5shiv.googlecode.com/svn/trunk/html5.js"></script><![endif]-->
</head>
<body class="<?php print $classes; ?>"<?php print $attributes; ?>>
<script type="text/javascript">if(typeof smart_ads=='function'){smart_ads();}</script>
<?php $class=(arg(0)=='node' && !arg(2)) ? 'doresize' : 'noresize' ;?>
<div id="imx-resizeable" class="<?php print $class;?>"></div>
<?php if ($body_scripts): ?>
<?php print $body_scripts;?>
<?php endif; ?>
<?php print $page_top; ?>
<?php print $page; ?>
<?php print $page_bottom; ?>
</body>
</html>