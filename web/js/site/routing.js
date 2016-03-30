$(function() {

    var AppRoutes = Backbone.Router.extend({
        routes: {
            "": "home",
            "/": "home",
            "aviso-de-privacidad": "avisoPrivacidad",
            "politica-ambiental": "politicaAmbiental",
            "audiencias-y-contenidos": "audienciasContenidos",
            "audiencias-y-contenidos/:idSection": "audienciasContenidos",
            "marketers": "marketers",
            "marketers/:idSection": "marketers",
            "red-de-video": "redeVideo",
            "casos-de-exito": "casoExito",
            "afiliate": "afiliate",
            "anunciate": "anunciate",
            ":nameTalento": "perfilTalento",
            ":nameSite": "perfilSitio"
        },
        home: function() {
            inventMx.home.vista = new inventMx.home.Home();
        },
        audienciasContenidos: function(idSection) {
            inventMx.home.pgAudienciasContenidos = new inventMx.home.HomeAudienciasContenidos(idSection);
        },
        marketers: function(idSection) {
            
            inventMx.home.pgMarketers = new inventMx.home.homeMarketers(idSection);
        },
        redeVideo: function() {       
            inventMx.home.pgRedeVideo = new inventMx.home.homeRedeVideo();
        },
        casoExito: function() {           
            inventMx.home.pgCasoExito = new inventMx.home.homeCasoExito();
        },
        afiliate: function() { 
            inventMx.home.pgAfiliate = new inventMx.home.homeAfiliate();
        },
        anunciate: function() {
            inventMx.home.pgAnunciate = new inventMx.home.homeAnunciate();
        },
        perfilTalento: function(nameTalento) {  
            inventMx.home.pgPerfilTalento = new inventMx.home.homePerfilTalento(nameTalento);
        },
        perfilSitio: function(nameSite) {
            inventMx.home.pgPerfilSitio = new inventMx.home.homePerfilSitio(nameSite);
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