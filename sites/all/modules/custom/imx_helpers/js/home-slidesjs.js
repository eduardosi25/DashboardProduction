jQuery(function(){
  jQuery("#carousel-home").slidesjs({
    width: 1024,
    height: 460,
    start : 1,
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
        speed: 900,
        crossfade: true
      }
    },
    play : {
      active : false,
      effect : "fade",
      auto : true,
      interval : 8000,
      swap : true,
      pauseOnHover : true,
      restartDelay : 3000
    }
  }).css({'text-align':'center'});
});
