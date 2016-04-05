$(function() {
    var AppRoutes = Backbone.Router.extend({
        routes: {
            "": "home",
            "/": "home",
            "la-red-invent": "redInvent",
            "content": "content",
            "content/:name_section": "content",
            "media-happenings": "mediaHappenings",
            "network-ads": "networkAds",
            "blogs": "blogs",
            ":site": "perfilSitio",
            ":perfil": "perfilTalento",
            "contacto": "contacto",
            
            "aviso-de-privacidad": "avisoPrivacidad",
            "politica-ambiental": "politicaAmbiental",
            "afiliate": "afiliate",
            "anunciate": "anunciate",
        },
        home: function() {
            inventMx.view.pgHome = new inventMx.view.home();
        },
        redInvent: function() {
            inventMx.pglaRedInvent = new inventMx.view.redInvent();
        },
        content: function() {
            inventMx.pgContent = new inventMx.view.content();
        },
        mediaHappenings: function() {
            inventMx.pgMediaHappenings = new inventMx.view.mediaHappenings();
        },
        networkAds: function() {
            inventMx.pgNetworkAds = new inventMx.view.networkAds();
        },
        blogs: function() {
            inventMx.pgBlogs = new inventMx.view.blogs();
        },
        perfilSitio: function() {
            inventMx.pgPerfilSitio = new inventMx.view.perfilSitio();
        },
        perfilTalento: function() {
            inventMx.pgPerfilTalento = new inventMx.view.perfilTalento();
        },
        contacto: function() {
            inventMx.pgContacto = new inventMx.view.contacto();
        },
        
        
        afiliate: function() {
            inventMx.pgHomeAfiliate = new inventMx.thome.homeAfiliate();
        },
        anunciate: function() {
            inventMx.pgHomeAnunciate = new inventMx.thome.homeAnunciate();
        },    
        avisoPrivacidad: function() {
            inventMx.pgAvisoPrivacidad = new inventMx.thome.avisoPrivacidad();
        },        
        politicaAmbiental: function() {
            inventMx.pgPoliticAmbiental = new inventMx.thome.politicAmbiental();
        }
    });
    
    router = new AppRoutes();
    Backbone.history.start();

});