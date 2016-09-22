$(function() {
    var AppRoutes = Backbone.Router.extend({
        routes: {
            "": "home",
            "/": "home",
            "la-red-imagen": "home",
            "caso-de-exito": "home",
            "contacto": "contacto",
            "casos-de-exito": "home",
            "codiga": "codiga",
            "bridgestone": "bridgestone",
            "oikos": "oikos",
            "raidmax": "raidmax",
            //"blogs": "blogs",
            //"blogs/:blogsUrl": "blogsNota",
            "content-marketing": "servicios",
            "media-happenings": "servicios",
            "network-ads": "networkAds",
            "aviso-de-privacidad": "avisoPrivacidad",
            "politica-ambiental": "politicaAmbiental",
            "terminos-y-condiciones-de-uso": "terminosCondiciones",
            //"afiliate": "afiliate",
            //"anunciate": "anunciate",
            ":site": "perfilSitio",
            ":perfil": "perfilTalento",
            /*":casoexito": "casoExito"*/
        },
        initialize: function(){
            $('header').scrollToFixed();
        },
        home: function() {
            inventMx.view.pgHome = new inventMx.view.home();
        },
        networkAds: function() {
            inventMx.view.pgNetworkAds = new inventMx.view.networkAds();
        },
        redInvent: function() {
            inventMx.pglaRedInvent = new inventMx.view.redInvent();
        },
        servicios: function(name_section) {
            inventMx.pgServicios = new inventMx.view.servicios(name_section);
        },
        /*blogs: function() {
            inventMx.pgBlogs = new inventMx.view.blogs();
        },
        blogsNota: function(blogsUrl) {
            inventMx.pgBlogsNota = new inventMx.view.blogsNota(blogsUrl);
            
        },*/
        perfilSitio: function(site) {
            inventMx.pgPerfilSitio = new inventMx.view.perfilSitio(site);
        },
        perfilTalento: function(perfil) {
            inventMx.pgPerfilTalento = new inventMx.view.perfilTalento(perfil);
        },
        contacto: function() {
            inventMx.pgContacto = new inventMx.view.contacto();
        },
        codiga: function() {
            inventMx.pgCodiga = new inventMx.view.codiga();
        },
        bridgestone: function() {
            inventMx.pgBridgestone = new inventMx.view.bridgestone();
        },
        raidmax: function() {
            inventMx.pgRaidmax = new inventMx.view.raidmax();
        },
        oikos: function() {
            inventMx.pgOikos = new inventMx.view.oikos();
        },
        casoExito: function(casoexito) {
            inventMx.pgcasoExito = new inventMx.view.casoExito(casoexito);
        },
        avisoPrivacidad: function() {
            inventMx.pgAvisoPrivacidad = new inventMx.view.avisoPrivacidad();
        },        
        politicaAmbiental: function() {
            inventMx.pgPoliticAmbiental = new inventMx.view.politicAmbiental();
        },
        terminosCondiciones: function() {
            inventMx.pgTerminosCondiciones = new inventMx.view.terminosCondiciones();
        },
        afiliate: function() {
            inventMx.pgHomeAfiliate = new inventMx.thome.homeAfiliate();
        },
        anunciate: function() {
            inventMx.pgHomeAnunciate = new inventMx.thome.homeAnunciate();
        }
    });
    
    router = new AppRoutes();
    Backbone.history.start();

});