$(function() {
    var AppRoutes = Backbone.Router.extend({
        routes: {
            "": "home",
            "/": "home",
            "la-red-invent": "laRedInvent",
            "content": "content",
            "media-happenings": "mediaHappenings",
            "network-ads": "networkAds",
            "blogs": "blogs",
            "contacto": "contacto",
            
            "aviso-de-privacidad": "avisoPrivacidad",
            "politica-ambiental": "politicaAmbiental",
            "afiliate": "afiliate",
            "anunciate": "anunciate",
        },
        home: function() {
            inventMx.home.vista = new inventMx.home.Home();
        },
        laRedInvent: function() {
            console.log("laRedInvent");
        },
        content: function() {
            console.log("content");
        },
        mediaHappenings: function() {
            console.log("mediaHappenings");
        },
        networkAds: function() {
            console.log("networkAds");
        },
        blogs: function() {
            console.log("blogs");
        },
        contacto: function() {
            inventMx.home.pHomes = new inventMx.home.pHomes();
        },
        
        afiliate: function() {
            inventMx.home.pgAfiliate = new inventMx.home.homeAfiliate();
        },
        anunciate: function() {
            inventMx.home.pgAnunciate = new inventMx.home.homeAnunciate();
        },    
        avisoPrivacidad: function() {
            inventMx.home.pgAvisoPrivacidad = new inventMx.home.avisoPrivacidad();
        },        
        politicaAmbiental: function() {
            inventMx.home.pgPoliticaAmbiental = new inventMx.home.politicAmbiental();
        }
    });
    
    router = new AppRoutes();
    Backbone.history.start();

});