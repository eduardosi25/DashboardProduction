$(function() {
    /* modelos */
    inventMx.home.Models = Backbone.Model.extend({});
    /* colecciones */
    inventMx.home.Collections = Backbone.Collection.extend({
        model: inventMx.home.Models,
        url: "/",
    });


    /* home */
    inventMx.home.Home = Backbone.View.extend({
        el: inventMx.page.wrapper_site,
        initialize: function () {
            $(this.el).unbind();
            _.bindAll(this, 'render');
            this.loadPage();
        },
        render: function (data) {            
            //this.loadPage();
        },
        loadPage: function () {            
            var url = "/web/data/home/home.json";
            var params = "";
            
            /* params accordion */
            var id_container = "#home-accordion";
            var tagHeader = "h2";
            var topOffset = true;
            
            var id_section1 = "#section-home-talento";
            var id_section2 = "#section-home-contactos";
            
            /* render handlebars */
            inventMx.page.wrapper_site.css("margin-right", "-3000px");
            inventMx.page.wrapper_site.hide().load("/web/app/inventmx/home/home.html", function () {
                inventMx.ajax.getAjax(url, params, function(resp) {
                    if (resp){                        
                        data = resp.data.sections[0].items;
                        dataVideos = data.slice(0, 15);
                        var redVideos = $("#template-home-red-videos").html();
                        var tpl_redVideos = Handlebars.compile(redVideos);
                        var view_redVideos = tpl_redVideos(dataVideos);
                        $("#home-red-videos").html(view_redVideos);                        
                    } else {
                        inventMx.utilities.loaderHide();
                        $("#home-red-videos").append("<p>No hay datos para mostrar</p>");
                    }
                    
                    if ($("img.lazy").length) {
                        $("img.lazy").lazyload({
                            effect: "fadeIn"
                        });
                    }
                    
                    inventMx.utilities.loaderHide();
                    setTimeout(inventMx.utilities.loaderHide, 7000);
                });
                                
                inventMx.utilities.validateAcordeon(id_container,tagHeader,topOffset);
                inventMx.utilities.homeAddRemoveSections(id_section1,id_section2);
                
                $(window).resize(function (e) {
                    //console.log(e);
                    e.stopPropagation();
                    deviceWidthWindow = inventMx.utilities.deviceWidthWindow();
                    if(inventMx.utilities.accordionStatus != "active" || deviceWidthWindow >= 701 && inventMx.utilities.accordionStatus == "active"){
                        inventMx.utilities.validateAcordeon(id_container,tagHeader,topOffset);
                    }                    
                    inventMx.utilities.homeAddRemoveSections(id_section1,id_section2);
                });
                                
                inventMx.page.wrapper_site.show();
                inventMx.page.wrapper_site.animate({
                    "margin-right": "+=3000px"
                }, "slow");
                return this;
            });
            
        },        
        acordeon: function(e) {
            e.preventDefault();
            
            var id_container = "#home-accordion";            
            inventMx.utilities.validateAcordeonOffsetStatus = true;
            inventMx.utilities.validateAcordeonOffset(id_container);
            
            $(window).resize(function () {               
                if(inventMx.utilities.validateAcordeonOffsetStatus){
                    inventMx.utilities.validateAcordeonOffset(id_container);
                }                
            });                        
        },
        events: {
            "click #home-accordion h2": "acordeon",
        },
        
    }),
    
    inventMx.home.homeCasoExito = Backbone.View.extend({
        el: inventMx.page.wrapper_site,
        initialize: function () {
            $(this.el).unbind();
            _.bindAll(this, 'render');
            this.render();            
        },
        render:function(){
            //inventMx.utilities.loaderHide();
            inventMx.page.wrapper_site.css("margin-right", "-3000px");
            inventMx.page.wrapper_site.load("/web/app/inventmx/caso-de-exito/home.html", function () {
                
                inventMx.utilities.loaderHide();
                setTimeout(inventMx.utilities.loaderHide, 7000);
                
                inventMx.page.wrapper_site.show();
                inventMx.page.wrapper_site.animate({
                    "margin-right": "+=3000px"
                }, "slow");
                return this;
            });            
        },        
    }),
    inventMx.home.homeAfiliate = Backbone.View.extend({
        el: inventMx.page.wrapper_site,
        initialize: function () {
            $(this.el).unbind();
            _.bindAll(this, 'render');
            this.render();            
        },
        render:function(){
            //inventMx.utilities.loaderHide();
            inventMx.page.wrapper_site.css("margin-right", "-3000px");
            inventMx.page.wrapper_site.load("/web/app/inventmx/afiliate/home.html", function () {
                inventMx.utilities.loaderHide();
                setTimeout(inventMx.utilities.loaderHide, 7000);
                
                inventMx.page.wrapper_site.show();
                inventMx.page.wrapper_site.animate({
                    "margin-right": "+=3000px"
                }, "slow");
                return this;
            });
        },
    }),
    
    inventMx.pageDefault.default404 = Backbone.View.extend({        
        initialize: function () {            
            this.render();            
        },
        render:function(){
            inventMx.utilities.loaderHide();
            
            inventMx.page.wrapper_site.css("margin-right", "-3000px");
            inventMx.page.wrapper_site.load("/web/app/inventmx/PageDefault/404.html", function () {
                setTimeout(inventMx.utilities.loaderHide, 7000);
                
                inventMx.page.wrapper_site.show();
                inventMx.page.wrapper_site.animate({
                    "margin-right": "+=3000px"
                }, "slow");
                return this;
            });            
        },        
    });
    

});