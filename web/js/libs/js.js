
jQuery(document).ready(function ($) {
      $(".navicon-button").click(function(){
        $(this).toggleClass("open");
        $('.menu').slideToggle();
      });
      /*$(".menu a").click(function(){
          $('.menu a').removeClass('active');
          $(this).addClass('active');
      }); */
      
      $w=$(window).width();
     if($w <= 727){
           $(document).on("click",".mobilemenu li a, .menu li a",function (e) {
            //e.preventDefault();
            $('.navicon-button').toggleClass("open");
            $('.menu').slideUp();
        });
           
            
          $('#header .wrapper .menu').addClass('mobilemenu');  
        
        $('#header .wrapper .menu').css({'display':'none'});
            
        function flexdestroy(selector) {

            var $els = $(selector);

            $els.each(function() {
                var $el = $(this);
                var $elClean = $el.clone();

                $elClean.find('.flex-viewport').children().unwrap();
                $elClean
                  .removeClass('flexslider')
                  .find('.clone, .flex-direction-nav, .flex-control-nav')
                    .remove()
                    .end()
                  .find('*').removeAttr('style').removeClass(function (index, css) {
                    // If element is SVG css has an Object inside (?)
                    if (typeof css === 'string') {
                      return (css.match(/\bflex\S+/g) || []).join(' ');
                    }
                  });

                $elClean.insertBefore($el);
                $el.remove();
            }); 

        }

           flexdestroy('.flexslider_marcas');


        }
        
        else{
             $('#header .wrapper .menu').removeClass('mobilemenu');  
            $('#header .wrapper .menu').css({'display':'inline-block'});
        }

    $( window ).resize(function() {
        
        $w=$(window).width();
        if($w <= 727){
            //console.log('si');
            
            
          $('#header .wrapper .menu').addClass('mobile_menu');  
        
        $('#header .wrapper .menu').css({'display':'none'});
        $(document).on("click",".mobile_menu li a",function (e) {
                //e.preventDefault();
                $('.navicon-button').toggleClass("open");
                $('.menu').slideUp();
            });
            
        function flexdestroy(selector) {

            var $els = $(selector);

            $els.each(function() {
                var $el = $(this);
                var $elClean = $el.clone();

                $elClean.find('.flex-viewport').children().unwrap();
                $elClean
                  .removeClass('flexslider')
                  .find('.clone, .flex-direction-nav, .flex-control-nav')
                    .remove()
                    .end()
                  .find('*').removeAttr('style').removeClass(function (index, css) {
                    // If element is SVG css has an Object inside (?)
                    if (typeof css === 'string') {
                      return (css.match(/\bflex\S+/g) || []).join(' ');
                    }
                  });

                $elClean.insertBefore($el);
                $el.remove();
            }); 

        }

           flexdestroy('.flexslider_marcas');


        }
        else{
             $('.flexslider_marcas').flexslider({
                        animation: "slide",
                        animationLoop: true,
                        slideshowSpeed: 4000, 
                        animationSpeed: 2000,
                        controlNav: false,               
                        directionNav: true, 

                      });
             $('#header .wrapper .menu').removeClass('mobilemenu');  
            $('#header .wrapper .menu').css({'display':'inline-block'});
        }
    });
             
});
