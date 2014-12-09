/**
 * Ejecucion de script On Window Load
 */
jQuery(window).load(function(){
  //Sidebar Sticky
  jQuery(".sticky").elastic({
    parent  : '#sidebar',
    head    : '#sidebar-first-sticky',
    sticky  : '.sticky',
    content : '.view-popular'
  });
  imx_doresize();
});

function imx_doresize(){
  var settings = {
    domFlag        : 'imx-resizeable',
    domLeft        : '#content',
    domRight       : '#sidebar',
    domSticky      : '#sidebar-first-sticky',
    selectorSearch : '#sidebar-first .block-imx-ads',
    patternSearch  : "div[id^='sas_']",
    curClassLeft   : 'eleven',
    curClassRight  : 'five',
    doClassLeft    : 'nine',
    doClassRight   : 'seven',
    fieldBody      : '.field-name-body'
  };

  var doResize = document.getElementById(settings.domFlag) ? document.getElementById(settings.domFlag).getAttributeNode("class").value : false;
  if (doResize == "doresize") {
    jQuery(settings.selectorSearch).find(settings.patternSearch).each(function(){
      var banner=jQuery(this).html();
      if(banner.length>1){
        var img = jQuery(this).find("img").width();
        var objeto = jQuery(this).find("object").width();
        var iframe = jQuery(this).find("iframe").width();
        var adWidth = (objeto) ? objeto : (img) ? img : (iframe) ? iframe : 0;
        if(parseInt(adWidth) > 300){
          if(jQuery(settings.domRight).hasClass(settings.curClassRight)){
            jQuery(settings.domRight).removeClass(settings.curClassRight);
            jQuery(settings.domRight).addClass(settings.doClassRight);
            jQuery(settings.domSticky).css({'width':'428px'});
            jQuery(settings.domSticky+' div.content').css({'width':'100%'});
            jQuery(settings.fieldBody+' img').css({'width':'100%','height':'100%'});
            jQuery('div.slidesjs-container, div.slidesjs-control').width('100%').height('418px');
          }
          if(jQuery(settings.domLeft).hasClass(settings.curClassLeft)){
            jQuery(settings.domLeft).removeClass(settings.curClassLeft);
            jQuery(settings.domLeft).addClass(settings.doClassLeft);
          }
        }else{
          if(jQuery(settings.domRight).hasClass(settings.doClassRight)){
            jQuery(settings.domRight).removeClass(settings.doClassRight);
            jQuery(settings.domRight).addClass(settings.curClassRight);
            jQuery(settings.domSticky).css({'width':'300px'});
            jQuery(settings.domSticky+' div.content').css({'width':'300px'});
            jQuery('div.slidesjs-container, div.slidesjs-control').width('684px').height('513px');
          }
          if(jQuery(settings.domLeft).hasClass(settings.doClassLeft)){
            jQuery(settings.domLeft).removeClass(settings.doClassLeft);
            jQuery(settings.domLeft).addClass(settings.curClassLeft);
          }
        }
      }
    });
  }
}