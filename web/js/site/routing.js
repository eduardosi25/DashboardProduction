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
            "casos-de-exito": "casoExito",
            "afiliate": "afiliate",
            "anunciate": "anunciate",
            ":nameTalento": "perfilTalento",
            ":nameSite": "perfilSitio",
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
             });*/
            
            //Backbone.history.start({pushState: true});
            //Backbone.history.start();
            
            //inventMx.metas.compile();
        },
        home: function() {            
            inventMx.utilities.loaderShow();
            inventMx.utilities.section = "home";
            inventMx.utilities.topOffset(0);
            inventMx.home.vista = new inventMx.home.Home();
            
            $("footer").css("margin-bottom","41px");
            $("header ul li a").removeClass("active");
        },
        audienciasContenidos: function(idSection) {            
            
            valueSection = inventMx.utilities.isObject(idSection);
            inventMx.utilities.section = "audiencias-y-contenidos";            
            inventMx.utilities.loaderShow();            
            inventMx.main.activeHover();
            
            idSection = (valueSection === true)? valueSection : idSection;
            (valueSection === false) ? inventMx.utilities.topOffset(0) : "";
            $("footer").css("margin-bottom","41px");
            inventMx.home.pgAudienciasContenidos = new inventMx.home.HomeAudienciasContenidos(idSection);
        },
        marketers: function(idSection) {
            
            valueSection = inventMx.utilities.isObject(idSection);                       
            inventMx.utilities.section = "marketers";            
            inventMx.utilities.loaderShow();
            inventMx.main.activeHover();
            
            idSection = (valueSection == true)? valueSection : idSection;
            (valueSection == true) ? inventMx.utilities.topOffset(0) : "";            
            
            $("footer").css("margin-bottom","41px");
            inventMx.home.pgMarketers = new inventMx.home.homeMarketers(idSection);
        },
        redeVideo: function() {            
            inventMx.utilities.section = "red-de-video";
            inventMx.utilities.loaderShow();            
            inventMx.main.activeHover();
            
            inventMx.utilities.topOffset(0);
            $("footer").css("margin-bottom","41px");
            inventMx.home.pgRedeVideo = new inventMx.home.homeRedeVideo();
        },
        casoExito: function() {                        
            inventMx.utilities.section = "caso-de-exito";
            inventMx.main.activeHover();
            inventMx.utilities.loaderShow();            
            
            inventMx.utilities.topOffset(0);
            $("footer").css("margin-bottom","41px");
            inventMx.home.pgCasoExito = new inventMx.home.homeCasoExito();
        },
        afiliate: function() {                        
            inventMx.utilities.section = "afiliate";
            inventMx.utilities.loaderShow();
            inventMx.main.activeHover();
            
            $("footer").css("margin-bottom","0px");
            inventMx.utilities.topOffset(0);
            inventMx.home.pgAfiliate = new inventMx.home.homeAfiliate();
        },
        anunciate: function() {            
            inventMx.utilities.section = "anunciate";
            inventMx.utilities.loaderShow();            
            inventMx.main.activeHover();
            
            $("footer").css("margin-bottom","0px");
            inventMx.utilities.topOffset(0);
            inventMx.home.pgAnunciate = new inventMx.home.homeAnunciate();
        },
        perfilTalento: function(nameTalento) {            
            inventMx.utilities.section = "perfil-talento";
            inventMx.utilities.nametalento = nameTalento;
            inventMx.utilities.loaderShow();
            inventMx.main.activeHover();
            
            $("footer").css("margin-bottom","41px");
            inventMx.utilities.topOffset(0);
            inventMx.home.pgPerfilTalento = new inventMx.home.homePerfilTalento(nameTalento);
        },
        perfilSitio: function(nameSite) {            
            inventMx.utilities.section = "perfil-sitio";
            inventMx.utilities.loaderShow();            
            inventMx.main.activeHover();
            
            $("footer").css("margin-bottom","41px");
            inventMx.utilities.topOffset(0);
            inventMx.home.pgPerfilSitio = new inventMx.home.homePerfilSitio(nameSite);
        },
        default: function() {            
            inventMx.utilities.section = "404";
            inventMx.utilities.loaderShow();
            inventMx.main.activeHover();
            
            $("footer").css("margin-bottom","0px");
            inventMx.home.vista404 = new inventMx.home.default404();
        },
        notFound: function() {
            inventMx.utilities.section = "404";
            inventMx.utilities.loaderShow();
            inventMx.main.activeHover();
            
            $("footer").css("margin-bottom","0px");
            inventMx.home.vista404 = new inventMx.home.default404();
        }
    });
    
    router = new AppRoutes();
    Backbone.history.start();

});