jQuery(document).ready(function(){
  jQuery('.slidesjs-slide').trackingClicksGA({
    domElementAttribute:'slidesjs-index'
  });
});

/**
 * Seteo de variable compatible para recuperar el UserAgent
 */
jQuery.browser = {};
(function () {
  jQuery.browser.msie = false;
  jQuery.browser.version = 0;
  if (navigator.userAgent.match(/MSIE ([0-9]+)\./)) {
    jQuery.browser.msie = true;
    jQuery.browser.version = RegExp.$1;
  }
})();
/**
 * Setea un div fixed de top y bottom autoajustable al
 * tamaño de la ventana dentro de otro div.
 * Se requieren de dos selectores para hacerlo funcionar:
 * {sticky} = el selector DOM donde se detendrá el scroll
 * {head}   = el selector DOM contener del elemento sticky
 */
(function(jQuery){
  jQuery.fn.elastic = function(options) {
    var defaults = {
      parent  : '#sidebar',
      head    : '#sidebar-bottom',
      sticky  : '.sticky',
      content : '#contents-popular'
    },
    settings = jQuery.extend({}, defaults, options);
    var topPadding = jQuery(settings.head).offset().top;
    jQuery(settings.sticky).css('top', topPadding);
    jQuery(window).scroll(function(event){
      event.preventDefault();
      var windowWidth=jQuery(window).height();
      jQuery(settings.sticky).css('top', topPadding - scroll);
      var scroll = jQuery(window).scrollTop();
      if (!jQuery("#sas_crea_1").is(":visible") || jQuery("#sas_crea_1").length == 0) {
        if (scroll >= topPadding) {
          jQuery(settings.sticky).css({
            'position' : 'fixed',
            'bottom' : '0',
            'top' : '0'
          });
          contentHeight=windowWidth-jQuery(settings.content).position().top-100;
          jQuery(settings.content).css({
            'height' : contentHeight
          });
          /*
          jQuery(settings.parent).css({
            'float'    : 'left',
            'margin-left' : '-10px'
          });
          */
        } else {
          jQuery(settings.sticky).css({
            'position' : 'static',
            'float' : 'none',
            'top' : topPadding - scroll
          });
          jQuery(settings.content).css({
            'height' : '100%'
          });
          /*
          jQuery(settings.parent).css({
            'float'    : 'none'
          });
          */
        }
      } else {
        jQuery(settings.sticky).css('position', 'static');
        /*
        jQuery(settings.parent).css({
          'float'    : 'none'
        });
        */
      }
    });
  };
})(jQuery);
//Track clicks to Google Analytics
//This function needs GA Tracking code properly configure
(function($) {
  $.fn.trackingClicksGA = function(options) {
    var settings = $.extend({},{
      domElementAttribute: 'href'
    }, options);
    return this.each(function() {
      var element=$(this);
      if ($.isFunction(_gaq.push)) {
        element.click(onClick);
      }
    });

    function onClick(){
      console.log($(this).attr(settings.domElementAttribute));
      var attribute=$(this).attr(settings.domElementAttribute);
      if(typeof attribute=='string' || typeof attribute=='number'){
        var value=attribute.replace('#','');
        value=location.pathname+'/#'+value;
        _gaq.push(['_trackPageview', value]);
      }
      return false;
    }
  };
})(jQuery);
function uid_call(a, b){
  ui_c2 = 7672322;
  ui_ns_site = 'rsvponline';
  window.b_ui_event = window.c_ui_event != null ? window.c_ui_event:"",window.c_ui_event = a;
  var ui_pixel_url = 'http://b.scorecardresearch.com/p?c1=2&c2='+ui_c2+'&ns_site='+ui_ns_site+'&name='+a+b;
  var b="comScore=",c=document,d=c.cookie,e="",f="indexOf",g="substring",h="length",i=2048,j,k="&ns_",l="&",m,n,o,p,q=window,r=q.encodeURIComponent||escape;if(d[f](b)+1)for(o=0,n=d.split(";"),p=n[h];o<p;o++)m=n[o][f](b),m+1&&(e=l+unescape(n[o][g](m+b[h])));ui_pixel_url+=k+"_t="+ +(new Date)+k+"c="+(c.characterSet||c.defaultCharset||"")+"&c8="+r(c.title)+e+"&c7="+r(c.URL)+"&c9="+r(c.referrer)+"&b_ui_event="+b_ui_event+"&c_ui_event="+c_ui_event,ui_pixel_url[h]>i&&ui_pixel_url[f](l)>0&&(j=ui_pixel_url[g](0,i-8).lastIndexOf(l),ui_pixel_url=(ui_pixel_url[g](0,j)+k+"cut="+r(ui_pixel_url[g](j+1)))[g](0,i)),c.images?(m=new Image,q.ns_p||(ns_p=m),m.src=ui_pixel_url):c.write("<p><img src='",ui_pixel_url,"' height='1' width='1' alt='*'></p>");
}
var newwindow;
function poptastic(url){
  left  = (jQuery(window).width()/2)-(626/2);
  top   = (jQuery(window).height()/2)-(436/2);
  newwindow = window.open(url,'Compartir', "width=626, height=436, top="+top+", left="+left);
  if (window.focus) {
    newwindow.focus()
  }
}
function OpenWindow(url){
  ventana = window.open (url, "popup", "width=626, height=436, top="+top+", left="+left);
  return ventana;
}
function fbs_click() {
  u=location.href;
  t=document.title;
  window.open('http://www.facebook.com/sharer.php?u='+encodeURIComponent(u)+'&t='+encodeURIComponent(t),'sharer','toolbar=0,status=0,width=626,height=436');
  return false;
}
function tws_click() {
  u=location.href;
  t=document.title;
  window.open('http://twitter.com/share?url='+encodeURIComponent(u)+'&text='+encodeURIComponent(t),'sharer','toolbar=0,status=0,width=626,height=436');
  return false;
}
