/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

$(function() {

    var AppRoutes = Backbone.Router.extend({
        routes: {
            "": "home",
            "/": "home",
            "audiencias-y-contenidos": "audienciasContenidos",
            "audiencias-y-contenidos/:idSection": "audienciasContenidos",
            "marketers": "marketers",
            "marketers/:idSection": "marketers",
            "red-de-video": "redeVideo",
            "caso-de-exito": "casoExito",
            "afiliate": "afiliate",
            "anunciate": "anunciate",
            //"perfil/:id": "perfilTalento",
            //"perfil/:name": "perfilTalento",
            ":nameTalento": "perfilTalento",
            //"site/:id": "perfilSitio",
            ":nameSite": "perfilSitio",
            //"site/excelsior": "perfilSitio",
            "*default": "default",
            "*notFound": "notFound"
        },
        initialize: function() {            
            
            /*var that = this;
            $(function () {
                //var baseFolder = window.location.pathname.replace('/', '').split('/')[0];
                Backbone.history.start({
                    root: '/',
                    //root: '/'+baseFolder+"/",                    
                    pushState: true,
                    hashChange: false
                });

                // Trap links
                $('body').delegate('a[href]:not([href^=#])', 'click', function (e) {
                    e.preventDefault();
                    that.navigate($(this).attr('href'), {trigger: true});
                });

                // Block anchors for hash-based history
                if (!Backbone.history._hasPushState) {
                    $('body').delegate('a[href^=#]', 'click', function (e) {
                        e.preventDefault();
                    });
                }
             }); */
            
            //Backbone.history.start({pushState: true});
            //Backbone.history.start();
        },
        home: function() {
            //iMxWebapp.taxonomy.name = {canal: "home"},
            //inventMx.page.wrapper_site.hide("slow");
            inventMx.utilities.loaderShow();
            inventMx.utilities.section = "home";
            inventMx.utilities.topOffset(0);
            inventMx.home.vista = new inventMx.home.Home();
            
            $("footer").css("margin-bottom","41px");
            $("header ul li a").removeClass("active");
        },
        audienciasContenidos: function(idSection) {
            //inventMx.page.wrapper_site.hide("slow");
            valueSection = inventMx.utilities.isObject(idSection);
            inventMx.utilities.section = "audiencias-y-contenidos";
            //idSection = (idSection)? idSection : null;
            inventMx.utilities.loaderShow();            
            inventMx.main.activeHover();
            
            idSection = (valueSection === true)? valueSection : idSection;
            (valueSection === false) ? inventMx.utilities.topOffset(0) : "";
            $("footer").css("margin-bottom","41px");
            inventMx.home.pgAudienciasContenidos = new inventMx.home.HomeAudienciasContenidos(idSection);
        },
        marketers: function(idSection) {
            
            valueSection = inventMx.utilities.isObject(idSection);           
            //console.log(valueSection);
            //inventMx.page.wrapper_site.hide("slow");
            inventMx.utilities.section = "marketers";            
            inventMx.utilities.loaderShow();
            inventMx.main.activeHover();
            
            idSection = (valueSection == true)? valueSection : idSection;
            (valueSection == true) ? inventMx.utilities.topOffset(0) : "";
            //inventMx.home.pgMarketers = new inventMx.home.homeMarketers();
            
            $("footer").css("margin-bottom","41px");
            inventMx.home.pgMarketers = new inventMx.home.homeMarketers(idSection);
        },
        redeVideo: function() {
            //inventMx.page.wrapper_site.hide("slow");
            inventMx.utilities.section = "red-de-video";
            inventMx.utilities.loaderShow();            
            inventMx.main.activeHover();
            
            inventMx.utilities.topOffset(0);
            $("footer").css("margin-bottom","41px");
            inventMx.home.pgRedeVideo = new inventMx.home.homeRedeVideo();
        },
        casoExito: function() {            
            //inventMx.page.wrapper_site.hide("slow");
            inventMx.utilities.section = "caso-de-exito";
            inventMx.main.activeHover();
            inventMx.utilities.loaderShow();            
            
            inventMx.utilities.topOffset(0);
            $("footer").css("margin-bottom","41px");
            inventMx.home.pgCasoExito = new inventMx.home.homeCasoExito();
        },
        afiliate: function() {            
            //inventMx.page.wrapper_site.hide("slow");
            inventMx.utilities.section = "afiliate";
            inventMx.utilities.loaderShow();
            inventMx.main.activeHover();
            
            $("footer").css("margin-bottom","0px");
            inventMx.utilities.topOffset(0);
            inventMx.home.pgAfiliate = new inventMx.home.homeAfiliate();
        },
        anunciate: function() {
            //inventMx.page.wrapper_site.hide("slow");
            inventMx.utilities.section = "anunciate";
            inventMx.utilities.loaderShow();            
            inventMx.main.activeHover();
            
            $("footer").css("margin-bottom","0px");
            inventMx.utilities.topOffset(0);
            inventMx.home.pgAnunciate = new inventMx.home.homeAnunciate();
        },
        perfilTalento: function(nameTalento) {
            //inventMx.page.wrapper_site.hide("slow");
            inventMx.utilities.section = "perfil-talento";
            inventMx.utilities.nametalento = nameTalento;
            inventMx.utilities.loaderShow();
            inventMx.main.activeHover();
            
            $("footer").css("margin-bottom","41px");
            inventMx.utilities.topOffset(0);
            inventMx.home.pgPerfilTalento = new inventMx.home.homePerfilTalento(nameTalento);
        },
        perfilSitio: function(nameSite) {
            //inventMx.page.wrapper_site.hide("slow");
            inventMx.utilities.section = "perfil-sitio";
            inventMx.utilities.loaderShow();            
            inventMx.main.activeHover();
            
            $("footer").css("margin-bottom","41px");
            inventMx.utilities.topOffset(0);
            inventMx.home.pgPerfilSitio = new inventMx.home.homePerfilSitio(nameSite);
        },
        default: function() {
            //inventMx.page.wrapper_site.hide("slow");
            inventMx.utilities.section = "404";
            inventMx.utilities.loaderShow();
            inventMx.main.activeHover();
            
            $("footer").css("margin-bottom","0px");
            inventMx.home.vista404 = new inventMx.home.default404();
        },
        notFound: function() {
            alert("page no encontrada admin");
        }
    });

    /*var baseFolder = window.location.pathname.replace('/', '').split('/')[0];
    router = new AppRoutes();
    Backbone.history.start({
        pushState: true,
        hashChange: true,
        root: baseFolder
    });*/

    router = new AppRoutes();
    Backbone.history.start();
    //Backbone.history.start({pushState: true});

});