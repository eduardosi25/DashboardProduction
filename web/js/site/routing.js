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
            "marketers": "marketers",
            "red-de-video": "redeVideo",
            "caso-de-exito": "casoExito",
            "afiliate": "afiliate",
            "anunciate": "anunciate",
            //"perfil/:id": "perfilTalento",
            //"perfil/:name": "perfilTalento",
            "perfil/ana-dominguez": "perfilTalento",
            //"site/:id": "perfilSitio",
            "site/:name": "perfilSitio",
            //"site/excelsior": "perfilSitio",
            "*default": "default",
            "*notFound": "notFound"
        },
        initialize: function() {
            
        },
        home: function() {
            //iMxWebapp.taxonomy.name = {canal: "home"},
            //inventMx.page.wrapper_site.hide("slow");
            inventMx.utilities.loaderShow();
            inventMx.utilities.section = "home";
            inventMx.home.vista = new inventMx.home.Home();
        },
        audienciasContenidos: function() {
            //inventMx.page.wrapper_site.hide("slow");
            inventMx.utilities.loaderShow();
            inventMx.utilities.section = "audiencias-y-contenidos";
            inventMx.home.pgAudienciasContenidos = new inventMx.home.HomeAudienciasContenidos();
        },
        marketers: function() {
            //inventMx.page.wrapper_site.hide("slow");
            inventMx.utilities.loaderShow();
            inventMx.utilities.section = "marketers";
            inventMx.home.pgMarketers = new inventMx.home.homeMarketers();
        },
        redeVideo: function() {
            //inventMx.page.wrapper_site.hide("slow");
            inventMx.utilities.loaderShow();
            inventMx.utilities.section = "red-de-video";
            inventMx.home.pgRedeVideo = new inventMx.home.homeRedeVideo();
        },
        casoExito: function() {            
            //inventMx.page.wrapper_site.hide("slow");
            inventMx.utilities.loaderShow();
            inventMx.utilities.section = "caso-de-exito";
            inventMx.home.pgCasoExito = new inventMx.home.homeCasoExito();
        },
        afiliate: function() {            
            //inventMx.page.wrapper_site.hide("slow");
            inventMx.utilities.loaderShow();
            inventMx.utilities.section = "afiliate";
            inventMx.home.pgAfiliate = new inventMx.home.homeAfiliate();
        },
        anunciate: function() {
            //inventMx.page.wrapper_site.hide("slow");
            inventMx.utilities.loaderShow();
            inventMx.utilities.section = "anunciate";
            inventMx.home.pgAnunciate = new inventMx.home.homeAnunciate();
        },
        perfilTalento: function() {
            //inventMx.page.wrapper_site.hide("slow");
            inventMx.utilities.loaderShow();
            inventMx.utilities.section = "perfil-talento";
            inventMx.home.pgPerfilTalento = new inventMx.home.homePerfilTalento();
        },
        perfilSitio: function(name) {
            //inventMx.page.wrapper_site.hide("slow");
            inventMx.utilities.loaderShow();
            inventMx.utilities.section = "perfil-sitio";
            inventMx.home.pgPerfilSitio = new inventMx.home.homePerfilSitio();
        },
        default: function() {
                //inventMx.page.wrapper_site.hide("slow");
                inventMx.utilities.loaderShow();
                inventMx.utilities.section = "404";
                inventMx.pageDefault.vista404 = new inventMx.pageDefault.default404();
        },
        notFound: function() {
            alert("page no encontrada admin");
        }
    });

    router = new AppRoutes();
    //Backbone.history.start({pushState: true});
    Backbone.history.start();

});
