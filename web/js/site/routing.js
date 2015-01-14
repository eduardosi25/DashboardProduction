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
            "caso-de-exito": "casoExito",
            "afiliate": "afiliate",
            "*default": "default",
            "*notFound": "notFound"
        },
        initialize: function() {
            
        },
        home: function() {
            //iMxWebapp.taxonomy.name = {canal: "home"},
            inventMx.home.vista = new inventMx.home.Home();
        },
        casoExito: function() {
            inventMx.home.homeCasoExito= new inventMx.home.homeCasoExito();
        },
        afiliate: function() {
            inventMx.home.homeAfiliate = new inventMx.home.homeAfiliate();
        },
        default: function() {                            
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
