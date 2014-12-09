jQuery(document).ready(function() {
	jQuery('#main-menu ul.menu').mobileMenu();

  /* Navigation */
	jQuery('#main-menu ul.menu').superfish({ 
		delay:       500,								// 0.1 second delay on mouseout 
		animation:   {opacity:'show',height:'show'},	// fade-in and slide-down animation 
		dropShadows: true								// disable drop shadows 
	});

  /* Lazy load */
  jQuery(function() {
    jQuery("img.lazy").lazyload({
      threshold      : 500,
      effect         : "fadeIn",
      //failure_limit  : 10,
      skip_invisible : false
    });
  });
});

function poptastic(url) {
  left = (jQuery(window).width() / 2) - (626 / 2);
  top = (jQuery(window).height() / 2) - (436 / 2);
  newwindow = window.open(url, 'Compartir', "width=626, height=436, top=" + top + ", left=" + left);
  if (window.focus) {
    newwindow.focus();
  }
}

function isValidUrl(url) {
  var pattern = /^(http|https|ftp)\:\/\/[a-z0-9\.-]+\.[a-z]{2,4}/gi;
  if (url.match(pattern)) {
    return true;
  } else {
    return false;
  }
}

(function(jQuery) {
  jQuery.fn.IMxImageShare = function(options) {
    var defaults = {
        share_text: jQuery('meta[property="og:title"]').attr("content"),
        share_via: 'InventMx'
      },
      settings = jQuery.extend({}, defaults, options);
    main_content = jQuery(this);
    images = jQuery(this).find("img");
    var protocol = document.location.protocol;
    var domain = document.domain;
    var link =  protocol+'//'+domain;

    jQuery.each(images, function() {
      var source_image = jQuery(this).attr('src') ? jQuery(this).attr('src') : jQuery(this).attr('data-original');
      var url = '';
      if (isValidUrl(source_image) == true){
        url = source_image;
      } else {
        url = link + source_image;
      }
      tw_url = "http://www.twitter.com/share?url=" + url + "&text=" + settings.share_text;
      fb_url = "http://www.facebook.com/sharer.php?u=" + url + "&t=" + settings.share_text;
      gp_url = "https://plus.google.com/share?url=" + url;
      pt_url = "http://pinterest.com/pin/create/button/?url=" + url + "&media=" + url + "&description=" + settings.share_text;

      jQuery(this).wrap("<div class='img_share'></div>");

      share_tw = '<div class="img_share_item"> <span class="tw_item" onClick="poptastic(\'' + tw_url + '\');" ></span> </div>';
      share_fb = '<div class="img_share_item"> <span class="fb_item" onClick="poptastic(\'' + fb_url + '\');" ></span> </div>';
      share_go = '<div class="img_share_item"> <span class="gp_item" onClick="poptastic(\'' + gp_url + '\');" ></span> </div>';
      share_pt = '<div class="img_share_item"> <span class="pt_item" onClick="poptastic(\'' + pt_url + '\');" ></span> </div>';
      close_btn = '<span class="closeBtn cursor-pointer">x</span>';

      jQuery(this).parent().prepend("<span class='img_share_arrow'></span>");
      jQuery(this).parent().prepend("<div class='img_share_box'></div>");
      jQuery(this).parent().find(".img_share_box").prepend(share_pt);
      jQuery(this).parent().find(".img_share_box").prepend(share_go);
      jQuery(this).parent().find(".img_share_box").prepend(share_tw);
      jQuery(this).parent().find(".img_share_box").prepend(share_fb);
      jQuery(this).parent().find(".img_share_box").prepend(close_btn);

      jQuery('.img_share').each(function() {
        jQuery(".img_share_arrow", this).click(function() {
          jQuery(this).parent().find(".img_share_box").animate({
            "left": "-50px",
            "opacity": 1
          }, 500);
        });

        jQuery(".img_share_box .closeBtn", this).click(function() {
          jQuery(this).parent().parent().find(".img_share_box").animate({
            "left": "0",
            "opacity": 0
          }, 300);
        });
      });
    });

  };
})(jQuery);

jQuery(document).ready(function() {
  jQuery(".field-name-body").IMxImageShare();
  jQuery('.field-name-body').find('iframe, .img_share').parent().css({'width':'90%','text-align':'right'});
});
