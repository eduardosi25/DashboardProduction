jQuery(document).ready(function () {//Creeamos los tags script para las dependencias a utilizar
   //Carga del jCarruselListe
  (function(e){function t(t,n){return parseInt(e.css(t[0],n))||0}function n(e){return e[0].offsetWidth+t(e,"marginLeft")+t(e,"marginRight")}function r(e){return e[0].offsetHeight+t(e,"marginTop")+t(e,"marginBottom")}e.fn.jCarouselLite=function(t){t=e.extend({btnPrev:null,btnNext:null,btnGo:null,mouseWheel:false,auto:null,speed:200,easing:null,vertical:false,circular:true,visible:3,start:0,scroll:1,beforeStart:null,tiempo:8e3,afterEnd:null},t||{});return this.each(function(){function b(){return p.slice(v).slice(0,h)}function w(n){if(!i){if(t.beforeStart)t.beforeStart.call(this,b());if(t.circular){if(n<=t.start-h-1){f.css(s,-((d-h*2)*m)+"px");v=n==t.start-h-1?d-h*2-1:d-h*2-t.scroll}else if(n>=d-h+1){f.css(s,-(h*m)+"px");v=n==d-h+1?h+1:h+t.scroll}else v=n}else{if(n<0||n>d-h)return;else v=n}i=true;f.animate(s=="left"?{left:-(v*m)}:{top:-(v*m)},t.speed,t.easing,function(){if(t.afterEnd)t.afterEnd.call(this,b());i=false});if(!t.circular){e(t.btnPrev+","+t.btnNext).removeClass("disabled");e(v-t.scroll<0&&t.btnPrev||v+t.scroll>d-h&&t.btnNext||[]).addClass("disabled")}}return false}var i=false,s=t.vertical?"top":"left",u=t.vertical?"height":"width";var a=e(this),f=e("ul",a),l=e("li",f),c=l.size(),h=t.visible;if(t.circular){f.prepend(l.slice(c-h-1+1).clone()).append(l.slice(0,h).clone());t.start+=h}var p=e("li",f),d=p.size(),v=t.start;a.css("visibility","visible");p.css({overflow:"hidden","float":t.vertical?"none":"left"});f.css({margin:"0",padding:"0",position:"relative","list-style-type":"none","z-index":"1"});a.css({overflow:"hidden",position:"relative","z-index":"2",left:"0px"});var m=t.vertical?r(p):n(p);var g=m*d;var y=m*h;p.css({width:p.width(),height:p.height()});f.css(u,g+"px").css(s,-(v*m));a.css(u,y+"px");if(t.btnPrev)e(t.btnPrev).click(function(){return w(v-t.scroll)});if(t.btnNext)e(t.btnNext).click(function(){return w(v+t.scroll)});if(t.btnGo)e.each(t.btnGo,function(n,r){e(r).click(function(){clearInterval(t.tiempo);t.tiempo=setInterval(function(){w(v+t.scroll)},t.tiempo);return w(t.circular?t.visible+n:n)})});if(t.mouseWheel&&a.mousewheel)a.mousewheel(function(e,n){return n>0?w(v-t.scroll):w(v+t.scroll)});if(t.auto)t.tiempo=setInterval(function(){w(v+t.scroll)},t.tiempo);})};})(jQuery)
  jQuery('head').append('<link rel="stylesheet" href="http://776561ea720ed80d100a-d15d7e8f8f7f4ad15567639aa98ea820.r76.cf2.rackcdn.com/imx_bottom_v5.css"/>');
//  jQuery('head').append('<link rel="stylesheet" href="/sites/all/modules/custom/bottom/imx_bottom_v4.css"/>');
  loadBottom("bottom_feeds");
});

function loadBottom(name) {
    var items = false;
    if (!items) {
        jQuery.ajax({
            url: 'http://776561ea720ed80d100a-d15d7e8f8f7f4ad15567639aa98ea820.r76.cf2.rackcdn.com/imx_bottom_data.js',
            dataType: 'jsonp',
            cache: true,
            jsonpCallback: 'renderButtom',
            success: function (data) {
            }
        });
    }
    //renderButtom(items);
}
//Funcion que contruye los items del feed
function buildFeedItems(parent, feed) {
    //Generamos cada uno de los items recorriendo el json con el feed de cada sitio
    x = 1;
    item_html = '<span class="bottom-links-prev"></span>';
    item_html += '<span class="bottom-links-next"></span>';
    item_html += '<div class="bottom-links-notes">';
    item_html += '<ul>';
    jQuery.each(feed, function (i, a) {
        if (typeof a !== "undefined") {
            site = i;
            item = a;
            if (a.length) {
                site_domain = a[0].link.split("/", 3);
                if (site === "adrenalina") {
                    site_domain[2] = "adrenalina360.com.mx";
                }else if (site === "enforma.salud180" || site === "sexualidad.salud180" || site === "bienestar.salud180") {
                    site_domain[2] = "salud180";
                }
            }
            jQuery.each(this, function (i) {

                if (i == 0) {
                    image_item="http://776561ea720ed80d100a-d15d7e8f8f7f4ad15567639aa98ea820.r76.cf2.rackcdn.com/generica_invent.jpg";
                    if(typeof this.image !== "undefined"){
                        if(this.image){
                            image_item=this.image;
                        }
                    }
                    title = truncate_text(this.title, 80, "");
                    item_html += '<li>';
                    item_html += ' <span class="logo logo-' + site + '"></span>';
                    item_html += '   <a href="' + this.link + '">';
                    item_html += '    <span class="img-cutter">';
                    item_html += '      <img src="'+image_item+'" />';
                    item_html += '    </span>';
                    item_html += '    <span class="note-title">' + title + '</span>';
                    item_html += '   </a>';
                    item_html += '</li>';
                }
            });
            x++;
        }
    });
    if (typeof item_html  !== "undefined") {
        item_html += '</ul>';
        item_html += '</div>';
    }else{
        item_html="";
    }
    item_html += '<div class="bottom-links-footer"><a class="gotop" href="#">Ir arriba</a><a class="politica-ambiental" href="#">Política ambiental</a><a class="mapa-sitio" href="#">Mapa de sitio</a><a class="feed-rss" href="#">RSS</a></div>';
    item_html += '</div>';

    jQuery(parent).append(item_html);
}


//Funciona de pintado del bottom
function renderButtom(feedData) {
    feed = feedData;
    jQuery("#bottom-imx").html("");
    //Template Statico del bottom, se rellenara con cada unos de los items de los feeds
    bottomTemplate = '<div id="bottom-imx-fixed-wrapper" class="bottom-static">\n\
                        <div id="bottom-imx-fixed" class="bottom-js bottom-black">\n\
                            <div class="bottom-top prelative">\n\
                                <div class="bottom-top-links-wrapper">\n\
                                    <span class="logo-invent left"></span>\n\
                                    <div class="bottom-top-links">\n\
                                        <a class="terminos-condiciones" href="#">Términos y condiciones de uso</a>\n\
                                        <a class="politicas-privacidad" href="#">Aviso de privacidad</a>\n\
                                        <div class="bottom-trigger tacenter">\n\
                                            <span class="trigger">\n\
                                               <span class="arrow-up"></span>\n\
                                               </span>\n\
                                        </div>\n\
                                        <div class="clear"></div>\n\
                                    </div>\n\
                                    <span class="logo-gimm right"></span>\n\
                                </div>\n\
                                <span class="copy clear tacenter dblock">© 2014 InventMX. Todos los derechos reservados. Prohibida la reproducción total o parcial, incluyendo cualquier medio electrónico o magnético.</span>\n\
                            </div>\n\
                            <div class="bottom-links">\n\
                           </div>\n\
                        </div>\n\
                     </div>';
    //Agregamos el template al html
    jQuery("#imx_bottom_js").parent("div").prepend(bottomTemplate);
    buildFeedItems(jQuery(".bottom-links"), feed);

    //Corremos el carrusel
    runCarrusel();
    buildLinks();
    if (typeof imx_bottom_callback == 'function') {
        imx_bottom_callback();
    }
}

function getDocHeight() {
    var D = document;
    return Math.max(
        D.body.scrollHeight, D.documentElement.scrollHeight,
        D.body.offsetHeight, D.documentElement.offsetHeight,
        D.body.clientHeight, D.documentElement.clientHeight
    );
}

function runCarrusel(){
    if(jQuery('#bottom-imx-fixed').length > 0){
        if(jQuery('#bottom-imx-fixed-wrapper.bottom-static').length > 0){
            jQuery(window).scroll(function() {
                if (jQuery(window).scrollTop() + jQuery(window).height() > jQuery(document).height() - 20) {
                    jQuery("#show-more").css({
                        bottom: "55px"
                    });
                } else {
                    jQuery("#show-more").css({
                        bottom: "0"
                    });
                }
            });
        }
        
        if(jQuery('.trigger-bottom-fixed').length > 0){
            altoInicial = jQuery('body').height();
            scrollFlag = jQuery('.trigger-bottom-fixed').offset().top - 200;
//            console.log(scrollFlag);
            jQuery(window).scroll(function() {
                VarScroll = jQuery(window).scrollTop();
//                console.log(VarScroll);
                if (VarScroll > scrollFlag) {
                    jQuery('#bottom-imx-fixed-wrapper.bottom-static').removeClass('bottom-static').addClass('bottom-fixed');
                    jQuery("#show-more").css({
                        bottom: "55px"
                    });
                } else {
                    jQuery('#bottom-imx-fixed-wrapper.bottom-fixed').removeClass('bottom-fixed').addClass('bottom-static');
                    jQuery("#show-more").css({
                        bottom: "0"
                    });
                }
            });
        }
        
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
                jQuery("#bottom-imx-fixed .bottom-links").animate({
                    height: "234px"
                }, 1000);
                if(jQuery("#bottom-imx-fixed-wrapper.bottom-static").length > 0){
                    jQuery("html, body").animate({ scrollTop: jQuery(document).height() }, 1000);
                }
            } else {
                jQuery(this).children().removeClass('arrow-down').addClass('arrow-up');
                    jQuery("#bottom-imx-fixed .bottom-links").animate({
                        height: "1px"
                    }, 1000);
            }
        });

        jQuery('.gotop').click(function(e) {
            e.preventDefault();
            jQuery('html, body').stop().animate({
                'scrollTop': 0
            }, 900, 'swing');
        });

//        var Mobile = /iphone|ipad|ipod|android|blackberry|mini|windows\sce|palm/i.test(navigator.userAgent);
//        if(Mobile){
//            jQuery('#bottom-imx-fixed .bottom-top-links a.version-movil').css('visibility', 'visible');
//        }
    }
}


function buildLinks(){
    pp=jQuery("#politicasprivacidad").html();
    pa=jQuery("#politicaambiental").html();
    gm=jQuery("#gomobile").html();
    cu=jQuery("#condiciones-uso").html();
    sm=jQuery("#sitemap").html();
    gt=jQuery("#gotop").html();
    rss=jQuery("#rss").html();

    if(pp){
        jQuery(".politicas-privacidad").attr("href",pp);
    }
    if(pa){
        jQuery(".politica-ambiental").attr("href",pa);
    }
    if(gm){
        jQuery(".version-movil").attr("href",pp);
    }
    if(cu){
        jQuery(".terminos-condiciones").attr("href",cu);
    }
    if(sm){
        jQuery(".mapa-sitio").attr("href",sm);
    }
    if(rss){
        jQuery(".feed-rss").attr("href",rss);
    }
    if(gt){
        jQuery(".gotop").attr("href",gt);
    }
}
function truncate_text(str, maxLength, suffix) {
    if (str.length > maxLength) {
        str = str.substring(0, maxLength + 1);
        str = str.substring(0, Math.min(str.length, str.lastIndexOf(" ")));
        str = str + suffix;
    }
    return str;
}