jQuery(function(){
  jQuery("#carousel-taxonomy").slidesjs({
    width: 664,
    height: 360,
    start : 1,
    navigation : {
      active : false,
      effect : "fade"
    },
    pagination : {
      active : false,
      effect : "fade"
    },
    effect: {
      fade: {
        speed: 900,
        crossfade: true
      }
    },
  }).css({'text-align':'center'});
});
