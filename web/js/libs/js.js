
jQuery(document).ready(function ($) {
    /*var controller = new ScrollMagic.Controller({
			globalSceneOptions: {
				triggerHook: 'onLeave'
			}
		});

		// get all slides
		var slides = document.querySelectorAll("div.panel");

		// create scene for every slide
		for (var i=0; i<slides.length; i++) {
			new ScrollMagic.Scene({
					triggerElement: slides[i]
				})
				.setPin(slides[i])
				.addIndicators() // add indicators (requires plugin)
				.addTo(controller)
                                .removeIndicators();
                        
		}
                            */    
                                
/*
          
$('#intro').parallax({
      axis: 'y',
      attr: 'top',
      speed: 0.001
    });

	*/				
             
           /*++++++++++++++++++++++++++++++++   jQuery(window).stellar();
            slide = $('.slide');
            button = $('.button');
            mywindow = $(window);
            htmlbody = $('html,body');

            slide.waypoint(function (event, direction) {
                    dataslide = $(this).attr('data-slide');
                    if (direction === 'down') {
                            $('.navigation li[data-slide="' + dataslide + '"]').addClass('active').prev().removeClass('active');
                    } else {
                            $('.navigation li[data-slide="' + dataslide + '"]').addClass('active').next().removeClass('active');
                    }
            });
            mywindow.scroll(function () {
                    if (mywindow.scrollTop() == 0) {
                            $('.navigation li[data-slide="1"]').addClass('active');
                            $('.navigation li[data-slide="2"]').removeClass('active');
                    }
            });
            function goToByScroll(dataslide) {
                    htmlbody.animate({
                            scrollTop: $('.slide[data-slide="' + dataslide + '"]').offset().top
                    }, 2000, 'easeInOutQuint');
            }*/
   

    $('.flexslider').flexslider({
        animation: "slide",
        animationLoop: true,
        slideshowSpeed: 4000, 
        animationSpeed: 2000,
        controlNav: true,               
        directionNav: false, 
        
      });
    $('.flexslider_marcas').flexslider({
            animation: "slide",
            animationLoop: true,
            slideshowSpeed: 4000, 
            animationSpeed: 2000,
            controlNav: false,               
            directionNav: true, 

          });
    $('.flexslider_bloger').flexslider({
            animation: "slide",
            animationLoop: true,
            slideshowSpeed: 4000, 
            animationSpeed: 2000,
            controlNav: false,               
            directionNav: true, 
            itemWidth: 305,
            itemMargin: 0,
            minItems: 2,
            maxItems: 3
          });
    //initialise Stellar.js
   
    //Cache some variables
   /* var links = $('.navigation').find('li');
    slide = $('.slide');
    button = $('.button');
    mywindow = $(window);
    htmlbody = $('html,body');*/


    //Setup waypoints plugin
   /* slide.waypoint(function (event, direction) {

        //cache the variable of the data-slide attribute associated with each slide
        dataslide = $(this).attr('data-slide');

        //If the user scrolls up change the navigation link that has the same data-slide attribute as the slide to active and 
        //remove the active class from the previous navigation link 
        if (direction === 'down') {
            $('.navigation li[data-slide="' + dataslide + '"]').addClass('active').prev().removeClass('active');
        }
        // else If the user scrolls down change the navigation link that has the same data-slide attribute as the slide to active and 
        //remove the active class from the next navigation link 
        else {
            $('.navigation li[data-slide="' + dataslide + '"]').addClass('active').next().removeClass('active');
        }

    });*/

    //waypoints doesnt detect the first slide when user scrolls back up to the top so we add this little bit of code, that removes the class 
    //from navigation link slide 2 and adds it to navigation link slide 1. 
    /*mywindow.scroll(function () {
        if (mywindow.scrollTop() == 0) {
            $('.navigation li[data-slide="1"]').addClass('active');
            $('.navigation li[data-slide="2"]').removeClass('active');
        }
    });*/

    //Create a function that will be passed a slide number and then will scroll to that slide using jquerys animate. The Jquery
    //easing plugin is also used, so we passed in the easing method of 'easeInOutQuint' which is available throught the plugin.
    



    //When the user clicks on the navigation links, get the data-slide attribute value of the link and pass that variable to the goToByScroll function
   /* links.click(function (e) {
        e.preventDefault();
        dataslide = $(this).attr('data-slide');
        goToByScroll(dataslide);
    });*/

    //When the user clicks on the button, get the get the data-slide attribute value of the button and pass that variable to the goToByScroll function
   /* button.click(function (e) {
        e.preventDefault();
        dataslide = $(this).attr('data-slide');
        goToByScroll(dataslide);

    });*/
    $('#demo-pie-1').pieChart({
                barColor: '#17d9b4',
                trackColor: '#a03d73',
                lineCap: 'square',
                lineWidth: 24,
                size: 158,
                rotate: -110,
                animate: {
                    duration: 3000,
                    enabled: true
                  },
                onStep: function (from, to, percent) {
                    $(this.element).find('.pie-value').text(Math.round(percent*10)/10 + '%');
                }
            });
    $('#demo-pie-2').pieChart({
                barColor: '#17d9b4',
                trackColor: '#a03d73',
                lineCap: 'square',
                lineWidth: 24,
                size: 158,
                rotate: -110,
                animate: {
                    duration: 3000,
                    enabled: true
                  },
                onStep: function (from, to, percent) {
                    $(this.element).find('.pie-value').text(Math.round(percent*10)/10 + '%');
                }
            });
    $('#demo-pie-3').pieChart({
                barColor: '#17d9b4',
                trackColor: '#a03d73',
                lineCap: 'square',
                lineWidth: 24,
                size: 158,
                rotate: -110,
                animate: {
                    duration: 2000,
                    enabled: true
                  },
                onStep: function (from, to, percent) {
                    $(this.element).find('.pie-value').text(Math.round(percent) + '%');
                }
            });
    $('#demo-pie-4').pieChart({
                barColor: '#17d9b4',
                trackColor: '#a03d73',
                lineCap: 'square',
                lineWidth: 24,
                size: 158,
                rotate: -110,
                animate: {
                    duration: 2000,
                    enabled: true
                  },
                onStep: function (from, to, percent) {
                    $(this.element).find('.pie-value').text(Math.round(percent*10)/10 + '%');
                }
            });
    $('#demo-pie-5').pieChart({
                barColor: '#17d9b4',
                trackColor: '#a03d73',
                lineCap: 'square',
                lineWidth: 24,
                size: 158,
                rotate: -110,
                animate: {
                    duration: 2000,
                    enabled: true
                  },
                onStep: function (from, to, percent) {
                    $(this.element).find('.pie-value').text(Math.round(percent*10)/10 + '%');
                }
            });
    $('#demo-pie-6').pieChart({
                barColor: '#17d9b4',
                trackColor: '#a03d73',
                lineCap: 'square',
                lineWidth: 24,
                size: 158,
                rotate: -110,
                
                onStep: function (from, to, percent) {
                    $(this.element).find('.pie-value').text(Math.round(percent*10)/10 + '%');
                }
            });
    $('#demo-pie-7').pieChart({
                barColor: '#17d9b4',
                trackColor: '#a03d73',
                lineCap: 'square',
                lineWidth: 24,
                size: 158,
                rotate: -110,
                
                onStep: function (from, to, percent) {
                    $(this.element).find('.pie-value').text(Math.round(percent*10)/10 + '%');
                }
            });
             $('#demo-pie-8').pieChart({
                barColor: '#17d9b4',
                trackColor: '#449cce',
                lineCap: 'square',
                lineWidth: 24,
                size: 158,
                rotate: -110,
                animate: {
                    duration: 3000,
                    enabled: true
                  },
                onStep: function (from, to, percent) {
                    $(this.element).find('.pie-value').text(Math.round(percent*10)/10 + '%');
                }
            });
    $('#demo-pie-9').pieChart({
                barColor: '#17d9b4',
                trackColor: '#449cce',
                lineCap: 'square',
                lineWidth: 24,
                size: 158,
                rotate: -110,
                animate: {
                    duration: 3000,
                    enabled: true
                  },
                onStep: function (from, to, percent) {
                    $(this.element).find('.pie-value').text(Math.round(percent*10)/10 + '%');
                }
            });
            
             
         /*

            (function(){
                var $el = $('.slide-window h2');
                $el.waypoint({
                    position: function(){
                        return $el.offset().top - $(window).height()/2;
                    },
                    down: function(){
                        $el.animate(
                            {'background-position-x': 270},
                            {
                                duration: 500,
                                
                        });
                    }
                });
            }());

            (function(){
                var $el = $('.slide-last h2');
                $el.tween({
                    start: function(){
                        return $el.offset().top - $(window).height()/2;
                    },
                    end: function(){
                        return $el.offsetParent().offset().top;
                    },
                    easing: 'Linear',
                    
                });

                $('.slide-last').parallax({
                  attr: 'background-position-y',
                  speed: 0.8
                });
            }());      */  
            
            
            



});