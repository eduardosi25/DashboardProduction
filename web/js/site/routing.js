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
            "*default": "default",
            "*notFound": "notFound"
        },
        initialize: function() {
            
        },
        home: function() {            
            //iMxWebapp.taxonomy.name = {canal: "home"},
            inventMx.home.vista = new inventMx.home.viewHome();
        },        
        default: function() {            
                alert("page no encontrada admin");
        },
        notFound: function() {

            alert("page no encontrada admin");
        }
    });

    router = new AppRoutes();
    //Backbone.history.start({pushState: true});
    Backbone.history.start();

});
