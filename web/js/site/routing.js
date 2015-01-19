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
            "marketers": "marketers",
            "red-de-video": "redeVideo",
            "caso-de-exito": "casoExito",
            "afiliate": "afiliate",
            "anunciate": "anunciate",
            "*default": "default",
            "*notFound": "notFound"
        },
        initialize: function() {
            
        },
        home: function() {
            //iMxWebapp.taxonomy.name = {canal: "home"},
            inventMx.page.wrapper_site.hide("slow");
            inventMx.utilities.loaderShow();
            inventMx.home.vista = new inventMx.home.Home();
        },
        marketers: function() {
            inventMx.page.wrapper_site.hide("slow");
            inventMx.utilities.loaderShow();
            inventMx.home.pgMarketers = new inventMx.home.homeMarketers();
        },
        redeVideo: function() {
            inventMx.page.wrapper_site.hide("slow");
            inventMx.utilities.loaderShow();           
            inventMx.home.pgRedeVideo = new inventMx.home.homeRedeVideo();
        },
        casoExito: function() {            
            inventMx.page.wrapper_site.hide("slow");
            inventMx.utilities.loaderShow();
            inventMx.home.pgCasoExito = new inventMx.home.homeCasoExito();
        },
        afiliate: function() {            
            inventMx.page.wrapper_site.hide("slow");
            inventMx.utilities.loaderShow();
            inventMx.home.pgAfiliate = new inventMx.home.homeAfiliate();
        },
        anunciate: function() {
            inventMx.page.wrapper_site.hide("slow");
            inventMx.utilities.loaderShow();
            inventMx.home.pgAnunciate = new inventMx.home.homeAnunciate();
        },
        default: function() {
                inventMx.page.wrapper_site.hide("slow");
                inventMx.utilities.loaderShow();
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
