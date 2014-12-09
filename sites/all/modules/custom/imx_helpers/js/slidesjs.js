/**
var indexPage=null;
var hashPage=location.hash;
if(typeof hashPage !== 'undefined' && typeof hashPage === 'string'){
  indexPage=parseInt(hashPage.replace("#image",""));
}
jQuery(function(){
  jQuery(".field-name-field-images div.field-items").slidesjs({
    width: 680,
    height: 510,
    start : (indexPage) ? indexPage : 1,
    effect : "fade",
    navigation : {
      active : false,
      effect : "fade"
    },
    pagination : {
      active: false,
      effect : "fade"
    },
    effect: {
      fade: {
        speed: 500,
        crossfade: true
      }
    },
    callback: {
      loaded: function(current) {
        var indexSlideJS=parseInt(current)-1;
        var captionSlideJS=jQuery('.slidesjs-slide[slidesjs-index="'+indexSlideJS+'"]').find('img').attr('title');
        if(typeof captionSlideJS=="undefined" || captionSlideJS=="null"){
          captionSlideJS=jQuery('.slidesjs-slide[slidesjs-index="'+indexSlideJS+'"]').find('img').attr('alt');
        }
        jQuery('#slidesjs-current-caption').animate({
          bottom:0
        },200).text(captionSlideJS);
        if (window.console && console.log) {
          //console.log('Loaded on current:'+current+' - Caption: '+captionSlideJS);
        };
      },
      start: function(current) {
        jQuery('#slidesjs-current-caption').animate({
          bottom:-75
        },100);
        if (window.console && console.log) {
          //console.log('Start on current: '+current);
        };
      },
      complete: function(current) {
        var indexSlideJS=parseInt(current)-1;
        var captionSlideJS=jQuery('.slidesjs-slide[slidesjs-index="'+indexSlideJS+'"]').find('img').attr('alt');
        var titleSlideJS=jQuery('.slidesjs-slide[slidesjs-index="'+indexSlideJS+'"]').find('img').attr('title');
        if(typeof captionSlideJS=="undefined" || captionSlideJS=="null"){
          captionSlideJS=jQuery('.slidesjs-slide[slidesjs-index="'+indexSlideJS+'"]').find('img').attr('title');
        }elseif(typeof titleSlideJS=="undefined" || titleSlideJS=="null"){{
          captionSlideJS=captionSlideJS+' | '+titleSlideJS;
        }
        jQuery('#slidesjs-current-caption').animate({
          bottom:0
        },200).text(captionSlideJS);
        //console.log('Complete on current:'+current+' - Caption: '+captionSlideJS);
        //Tracking pageview Google Analytics
        if (jQuery.isFunction(_gaq.push)) {
          valueHash='image'+current;
          pathLocation=location.pathname+'#'+valueHash;
          _gaq.push(['_trackPageview', pathLocation]);
          if (typeof window.history.pushState === 'function') {
            window.history.pushState({}, '', pathLocation);
          } else {
            window.location.hash = '#!' + path;
          }
          //window.history.pushState({}, '', value);
          //console.log('Send GA pageview:'+value);
        }
      }
    }
  }).css({'text-align':'center'});
});
*/