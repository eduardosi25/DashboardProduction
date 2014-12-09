jQuery(document).ready(function() {
    if(jQuery('#bottom-imx-fixed').length > 0){
        jQuery("#bottom-imx-fixed .bottom-links-notes").jCarouselLite({
            btnNext: ".bottom-links-next",
            btnPrev: ".bottom-links-prev",
            speed: 700,
            circular: true,
            visible: 5,
            scroll: 1
        });
        jQuery("#bottom-imx-fixed .trigger").click(function(){
            if(jQuery(this).children().hasClass('arrow-up')){
                jQuery(this).children().removeClass('arrow-up').addClass('arrow-down');
                jQuery("#bottom-imx-fixed").animate({
                    bottom: 0
                }, 1000);
                jQuery("#show-more").animate({
                    bottom: "288px"
                }, 1000);
            } else {
                jQuery(this).children().removeClass('arrow-down').addClass('arrow-up');
                jQuery("#bottom-imx-fixed").animate({
                    bottom: "-234px"
                }, 1000);
                jQuery("#show-more").animate({
                    bottom: "55px"
                }, 1000);
            }
        });
        var Mobile = /iphone|ipad|ipod|android|blackberry|mini|windows\sce|palm/i.test(navigator.userAgent);
        if(Mobile){
            jQuery('#bottom-imx-fixed .bottom-top-links a.version-movil').css('visibility', 'visible');
        }
    }
});
