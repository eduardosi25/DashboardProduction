$(function() {
    /* modelos */
    inventMx.home.Models = Backbone.Model.extend({});
    /* colecciones */
    inventMx.home.Collections = Backbone.Collection.extend({
        model: inventMx.home.Models,
        url: "/",
    });


    /* home */
    inventMx.home.viewHome = Backbone.View.extend({
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
            inventMx.page.wrapper_site.hide().load("/web/app/inventmx/home/home.html", function () {
                inventMx.ajax.getAjax(url, params, function(resp) {
                    if (resp){
                        //$("#page").fadeIn(2000);
                        data = resp.data.sections[0].items;
                        dataVideos = data.slice(0, 15);
                        var redVideos = $("#template-home-red-videos").html();
                        var tpl_redVideos = Handlebars.compile(redVideos);
                        var view_redVideos = tpl_redVideos(dataVideos);
                        $("#home-red-videos").html(view_redVideos);
                        //inventMx.utilities.loaderHide();
                    } else {
                        inventMx.utilities.loaderHide();
                        $("#home-red-videos").append("<p>No hay datos para mostrar</p>");
                    }
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
                
                inventMx.page.wrapper_site.show("fast");
                return this;
            });
            
        },        
        acordeon: function(e) {
            e.preventDefault();
            
            var id_container = "#home-accordion";
            //section = $("#home-accordion").attr("id");
            inventMx.utilities.validateAcordeonOffsetStatus = true;
            inventMx.utilities.validateAcordeonOffset(id_container);
            
            $(window).resize(function () {
                //console.log("vt");
                //console.log(inventMx.utilities.validateAcordeonOffsetStatus);
                if(inventMx.utilities.validateAcordeonOffsetStatus){
                    inventMx.utilities.validateAcordeonOffset(id_container);
                }                
            });
            
            /*deviceWidthWindow = inventMx.utilities.deviceWidthWindow();
            if (deviceWidthWindow <= 700) {
                offset1 = $("#home-accordion").offset();
                var offset = offset1.top;
                inventMx.utilities.topOffset(offset);
            }*/
        },
        events: {
            "click #home-accordion h2": "acordeon",
        },
        
    });

});