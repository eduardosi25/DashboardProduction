$(function() {
    var AppRoutes = Backbone.Router.extend({
        routes: {
            "": "home",
            "/": "home",
            "/:section": "home",
            "contacto": "contacto",
            "condiga": "codiga",
            "blogs": "blogs",
            "blogs/:blogsUrl": "blogsNota",
            "la-red-invent": "redInvent",
            "servicios": "servicios",
            "servicios/:name_section": "servicios",
            ":site": "perfilSitio",
            ":perfil": "perfilTalento",
            ":casoexito": "casoExito", 
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
        servicios: function(name_section) {
            inventMx.pgServicios = new inventMx.view.servicios(name_section);
        },
        blogs: function() {
            inventMx.pgBlogs = new inventMx.view.blogs();
        },
        blogsNota: function(blogsUrl) {
            inventMx.pgBlogsNota = new inventMx.view.blogsNota(blogsUrl);
        },
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
        casoExito: function(casoexito) {
            inventMx.pgcasoExito = new inventMx.view.casoExito(casoexito);
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