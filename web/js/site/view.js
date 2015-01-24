$(function() {
    /* eventos */
    var inventMx_events = {};
    IMxevents=_.extend(inventMx_events, Backbone.Events);
    
    // Con la funcion bind podemos enlazar un evento cualquiera con una
    // función callback que se ejecutará cuando este evento ocurra en este objeto
    inventMx_events.bind("NoData", function (msg) {
        alert('No hay  más dato en ' + msg);
    });
    
    inventMx_events.bind("Inventform", function (idform,data) {
        validate = $(idform).validationEngine('validate');        
        options = {idform:idform}
        if(validate) {
            url = "/web/app/inventmx/global/sendmail.php";
            inventMx.dataSource.getAjax(url, data,inventMx.email.data,options);
        }else {
            console.log("No validate");
        }
    });
    
    
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
        render: function () {            
            //this.loadPage();
        },
        loadPage: function () {
            
            /* params accordion */
            var id_container = "#home-accordion";
            var tagHeader = "h2";
            var topOffset = true;
            
            var id_section1 = "#section-home-talento";
            var id_section2 = "#section-home-contactos";
            
            inventMx.page.wrapper_site.load("/web/app/inventmx/home/home.html", function () {
                
                repo = "sites.json";
                inventMx.dataSource.params.url = null;
                inventMx.dataSource.params.limit = "30";
                inventMx.dataSource.load(repo,inventMx.render.tplSites);
                
                repo = "vloger.json";
                inventMx.dataSource.params.url = null;
                inventMx.dataSource.params.limit = "100";
                listTalentos = new inventMx.home.listPerfilTalentos(repo);
                
                inventMx.utilities.validateAcordeon(id_container,tagHeader,topOffset);
                inventMx.utilities.homeAddRemoveSections(id_section1,id_section2);
                
                // Un objeto puede disparar un evento en el momento que desee
                // utilizando la función trigger
                /*inventMx_events.trigger('NoData','Home');*/ 
                
                $(window).resize(function (e) {
                    e.stopPropagation();
                    var sites = "#sections-sites li.sections-sites";
                    $(sites).css("height","auto");
                    
                    deviceWidthWindow = inventMx.utilities.deviceWidthWindow();
                    if(inventMx.utilities.accordionStatus != "active" || deviceWidthWindow >= 701 && inventMx.utilities.accordionStatus == "active"){
                        inventMx.utilities.validateAcordeon(id_container,tagHeader,topOffset);
                    }
                    inventMx.utilities.homeAddRemoveSections(id_section1,id_section2);
                    
                    finalSites = inventMx.utilities.calculateheightItem(sites);
                    $(sites).height(Math.round(finalSites));
                    
                });
                
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
    
    inventMx.home.HomeAudienciasContenidos = Backbone.View.extend({
        el: inventMx.page.wrapper_site,
        initialize: function (idSection) {
            $(this.el).unbind();
            _.bindAll(this, 'render');
            //this.render();            
            idAncla =  idSection;
            this.render(idAncla);
        },
        render:function(idAncla){
                var id_section1 = "#section-home-contactos";
                var noticias = "#noticias-deportes li.sections-sites";
                var Msaludable = "#mundo-saludable li.sections-sites";
                var Mfemenino = "#mundo-femenino li.sections-sites";
                var lifeStyle = "#life-style li.sections-sites";
                    
            var widthDevice = inventMx.utilities.deviceWidthWindow();
            
            //inventMx.page.wrapper_site.animate({ "left": "+=2000px" }, "slow" );
            inventMx.page.wrapper_site.load("/web/app/inventmx/audiencias-y-contenidos/home.html", function () {
                
                //inventMx.page.wrapper_site.show("slow");
                //inventMx.page.wrapper_site.animate({ "left": "-=2000px" }, "slow",function(){
                
                
                inventMx.utilities.oneAddRemoveSections(id_section1);
                
                if(widthDevice >= 701){
                    finalNumbers = inventMx.utilities.calculateheightItem(noticias);
                    $(noticias).height(finalNumbers);
                    
                    finalNumbers1 = inventMx.utilities.calculateheightItem(Msaludable);
                    $(Msaludable).height(finalNumbers1);
                    
                    finalNumbers2 = inventMx.utilities.calculateheightItem(Mfemenino);
                    $(Mfemenino).height(finalNumbers2);
                    
                    finalNumbers3 = inventMx.utilities.calculateheightItem(lifeStyle);
                    $(lifeStyle).height(finalNumbers3);
                }
                
                    inventMx.utilities.loaderHide();
                    setTimeout(inventMx.utilities.loaderHide, 7000);
                    
                    if(idAncla !== true){
                        //console.log(idAncla);
                        if($("#"+idAncla).length){
                            offset1 = $("#"+idAncla).offset();
                            var offset = offset1.top;
                            inventMx.utilities.topOffset(offset,0);
                            //console.log("Si");
                        }else {
                            var ficha = new inventMx.home.default404();
                            //inventMx.home.default404();
                        }
                    }
                    
                });
                
                return this;
            //});                        
                                    
            $(window).resize(function (e) {
                e.stopPropagation();
                inventMx.utilities.oneAddRemoveSections(id_section1);
                
                if(widthDevice >= 701){                    
                    finalNumbers = inventMx.utilities.calculateheightItem(noticias);
                    $(noticias).height(finalNumbers);
                    
                    finalNumbers1 = inventMx.utilities.calculateheightItem(Msaludable);
                    $(Msaludable).height(finalNumbers1);
                    
                    finalNumbers2 = inventMx.utilities.calculateheightItem(Mfemenino);
                    $(Mfemenino).height(finalNumbers2);
                    
                    finalNumbers3 = inventMx.utilities.calculateheightItem(lifeStyle);
                    $(lifeStyle).height(finalNumbers3);
                }
                
            });
            
        },        
    }),
    
    
    inventMx.home.homeMarketers = Backbone.View.extend({
        el: inventMx.page.wrapper_site,
        initialize: function (idSection) {
            $(this.el).unbind();
            _.bindAll(this, 'render');
            idAncla =  idSection;
            this.render(idAncla);
            //this.render();
        },
        render:function(idAncla){
            var id_section1 = "#section-home-contactos";
            var rich1 = ".formats-rich-media .body-table-1 li.box-table";
            var rich2 = ".formats-rich-media .body-table-2 li.box-table";
            
            var mobile = ".formats-mobile .body-table li.box-table";
            
            //inventMx.page.wrapper_site.animate({ "left": "+=2000px" }, "slow" );
            inventMx.page.wrapper_site.load("/web/app/inventmx/marketers/home.html", function () {

                //inventMx.page.wrapper_site.show("slow");
                //inventMx.page.wrapper_site.animate({ "left": "-=2000px" }, "slow",function(){
                    
                    finalNumbers = inventMx.utilities.calculateheightItem(rich1);
                    $(rich1).height(finalNumbers);
                    finalNumbers = inventMx.utilities.calculateheightItem(rich2);
                    $(rich2).height(finalNumbers);
                    finalNumbers = inventMx.utilities.calculateheightItem(mobile);
                    $(mobile).height(finalNumbers);
                    
                    inventMx.utilities.loaderHide();
                    setTimeout(inventMx.utilities.loaderHide, 7000);
                //});
                inventMx.utilities.oneAddRemoveSections(id_section1);
                
                if(idAncla !== true){
                    //console.log(idAncla);
                    if($("#"+idAncla).length){
                        offset1 = $("#"+idAncla).offset();
                        var offset = offset1.top;                        
                        inventMx.utilities.topOffset(offset,0);
                        //console.log("Si");
                    }else {
                        var ficha = new inventMx.home.default404();
                        //inventMx.home.default404();
                    }
                }
                
                return this;
            });                        
                        
            //finalNumbers = inventMx.utilities.calculateheightItem(rich2);
            //$(rich2).height(finalNumbers);
            
            $(window).resize(function (e) {
                e.stopPropagation();
                inventMx.utilities.oneAddRemoveSections(id_section1);
                
                finalNumbers = inventMx.utilities.calculateheightItem(rich1);
                $(rich1).height(finalNumbers);                
                finalNumbers = inventMx.utilities.calculateheightItem(rich2);
                $(rich2).height(finalNumbers);
                finalNumbers = inventMx.utilities.calculateheightItem(mobile);
                $(mobile).height(finalNumbers);
                //finalNumbers = inventMx.utilities.calculateheightItem(rich2);
                //$(rich2).height(finalNumbers);
                //inventMx.utilities.changeResolitionsImg(id_image_firts);
            });
            
        },
    }),
    
    inventMx.home.homeRedeVideo = Backbone.View.extend({
        el: inventMx.page.wrapper_site,
        initialize: function () {
            $(this.el).unbind();
            _.bindAll(this, 'render');
            this.render();            
        },
        render:function(){
            var url = "/web/data/home/home.json";
            var params = "";
            var id_section1 = "#section-home-contactos";
            
            //inventMx.page.wrapper_site.animate({ "left": "+=2000px" }, "slow" );
            inventMx.page.wrapper_site.load("/web/app/inventmx/redVideo/home.html", function () {
                
                inventMx.dataSource.getAjax(url, params, function(resp) {
                    if (resp){                        
                        data = resp.data.sections[0].items;
                        dataVideos = data.slice(0, 15);
                        var redVideos = $("#template-red-videos-lifeStyle").html();
                        var redVideosCocina = $("#template-red-videos-cocina").html();
                        var redVideosNoticias = $("#template-red-videos-noticias").html();
                        var redVideosEntretenimiento = $("#template-red-videos-entretenimiento").html();
                        var tpl_redVideos = Handlebars.compile(redVideos);
                        var tpl_redVideosCocina = Handlebars.compile(redVideosCocina);
                        var tpl_redVideosNoticias = Handlebars.compile(redVideosNoticias);
                        var tpl_redVideosEntretenimiento = Handlebars.compile(redVideosEntretenimiento);
                        var view_redVideos = tpl_redVideos(dataVideos);
                        var view_redVideosCocina = tpl_redVideosCocina(dataVideos);
                        var view_redVideosNoticias = tpl_redVideosNoticias(dataVideos);
                        var view_redVideosEntretenimiento = tpl_redVideosEntretenimiento(dataVideos);
                        $("#red-videos-lifeStyle").html(view_redVideos);
                        $("#red-videos-cocina").html(view_redVideosCocina);
                        $("#red-videos-noticias").html(view_redVideosNoticias);
                        $("#red-videos-entretenimiento").html(view_redVideosEntretenimiento);
                    } else {
                        inventMx.utilities.loaderHide();
                        $("#red-videos-lifeStyle").append("<p>No hay datos para mostrar</p>");
                    }
                    
                    if ($("img.lazy").length) {
                        $("img.lazy").lazyload({
                            effect: "fadeIn"
                        });
                    }
                });
                
                
                inventMx.utilities.oneAddRemoveSections(id_section1);
                
                //inventMx.page.wrapper_site.show("slow");
                //inventMx.page.wrapper_site.animate({ "left": "-=2000px" }, "slow",function(){
                    inventMx.utilities.loaderHide();
                    setTimeout(inventMx.utilities.loaderHide, 7000);
                //});
                return this;
            });
                
            $(window).resize(function (e) {
                e.stopPropagation();
                inventMx.utilities.oneAddRemoveSections(id_section1);
            });
            
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
            var id_section1 = "#section-home-contactos";
            var id_section2 = "#section-table-case-exito";
            var li_items = ".wrapper-table-case-exito li.box-item";
            
            inventMx.page.wrapper_site.load("/web/app/inventmx/caso-de-exito/home.html", function () {
                
                repo = "case.json";
                inventMx.dataSource.params.url = null;
                inventMx.dataSource.params.limit = 20;
                inventMx.dataSource.load(repo,inventMx.render.tplcaseExito);
                
                inventMx.utilities.caseExitoAddRemoveSections(id_section1,id_section2);
                inventMx.utilities.loaderHide();
                setTimeout(inventMx.utilities.loaderHide, 7000);
               
                finalNumbers = inventMx.utilities.calculateheightItem(li_items);
                $(li_items).height(finalNumbers);
                return this;
            });
                
            $(window).resize(function (e) {
                e.stopPropagation();                
                inventMx.utilities.caseExitoAddRemoveSections(id_section1,id_section2);
                finalNumbers = inventMx.utilities.calculateheightItem(li_items);
                $(li_items).height(finalNumbers);
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
            id_image_firts = "#bg-firts-afiliate";
            
            //inventMx.page.wrapper_site.animate({ "left": "+=2000px" }, "slow" );
            inventMx.page.wrapper_site.load("/web/app/inventmx/afiliate/home.html", function () {
                
                inventMx.utilities.changeResolitionsImg(id_image_firts);
                //inventMx.page.wrapper_site.show("slow");
                //inventMx.page.wrapper_site.animate({ "left": "-=2000px" }, "slow",function(){
                    inventMx.utilities.loaderHide();
                    setTimeout(inventMx.utilities.loaderHide, 7000);
                //});
                
                jQuery("#form-afiliate").validationEngine('attach', {
                    promptPosition: "bottomLeft"
                });
                
                $(document).on("submit","#form-afiliate",function(e){
                    e.preventDefault();
                    data = $(this).serializeArray();                    
                    inventMx_events.trigger('Inventform','#form-afiliate',data);
                });
                
                return this;
            });
            
            $(window).resize(function (e) {
                e.stopPropagation();
                inventMx.utilities.changeResolitionsImg(id_image_firts);
            });
            
        },
    }),
    inventMx.home.homeAnunciate = Backbone.View.extend({
        el: inventMx.page.wrapper_site,
        initialize: function () {
            $(this.el).unbind();
            _.bindAll(this, 'render');
            this.render();            
        },
        render:function(){
            id_image_firts = "#bg-firts-afiliate";            
            //inventMx.page.wrapper_site.animate({ "left": "+=2000px" }, "slow" );
            inventMx.page.wrapper_site.load("/web/app/inventmx/anunciate/home.html", function () {
                
                inventMx.utilities.changeResolitionsImg(id_image_firts);   
                //inventMx.page.wrapper_site.show("slow");
                //inventMx.page.wrapper_site.animate({ "left": "-=2000px" }, "slow",function(){
                    inventMx.utilities.loaderHide();
                    setTimeout(inventMx.utilities.loaderHide, 2000);
                //});
                
                jQuery("#form-anunciate").validationEngine('attach', {
                    promptPosition: "bottomLeft"
                });
                
                $(document).on("submit","#form-anunciate",function(e){
                    e.preventDefault();
                    inventMx.utilities.loaderShow();
                    data = $(this).serializeArray();
                    inventMx_events.trigger('Inventform','#form-anunciate',data);
                });
                
                return this;
            });
            
            $(window).resize(function (e) {
                e.stopPropagation();
                inventMx.utilities.changeResolitionsImg(id_image_firts);
            });
            
        },
    }),
    
    inventMx.home.homePerfilTalento = Backbone.View.extend({
        initialize: function (nameTalento) {
            this.render(nameTalento);
        },
        render:function(nameTalento){
            var id_section1 = "#section-home-contactos";
            
            inventMx.page.wrapper_site.load("/web/app/inventmx/perfilTalento/home.html", function () {
                
                repo = "vloger.json";
                inventMx.dataSource.params.url = nameTalento;
                inventMx.dataSource.load(repo,inventMx.render.tplPerfilTalentos);
                
                inventMx.utilities.oneAddRemoveSections(id_section1);
                setTimeout(inventMx.utilities.loaderHide, 7000);
                //});
                return this;
            });
            
            
            $(window).resize(function (e) {
                e.stopPropagation();
                inventMx.utilities.oneAddRemoveSections(id_section1);
            });
            
        },
    });
    
    inventMx.home.homePerfilSitio = Backbone.View.extend({
        initialize: function (nameSite) {
            this.render(nameSite);
        },
        render:function(nameSite){
            var id_section1 = "#section-home-contactos";            
                        
            inventMx.page.wrapper_site.load("/web/app/inventmx/perfilSitio/home.html", function () {
                
                repo = "sites.json";
                inventMx.dataSource.params.url = nameSite;
                inventMx.dataSource.load(repo,inventMx.render.tplPerfilSites);
                
                inventMx.utilities.oneAddRemoveSections(id_section1);
                setTimeout(inventMx.utilities.loaderHide, 7000);
                
                return this;
            });
            
            
            $(window).resize(function (e) {
                e.stopPropagation();
                inventMx.utilities.oneAddRemoveSections(id_section1);
            });
            
        },
    });
    
    
    inventMx.home.listPerfilTalentos = Backbone.View.extend({
        initialize: function (repo) {
            this.render(repo);
        },
        render:function(repo){
            //repo = "vloger.json";
            //inventMx.dataSource.params.url = null;
            //inventMx.dataSource.params.limit = "100";
            inventMx.dataSource.load(repo, inventMx.render.tplHomeTalentos);
        }
        
    });
    
    inventMx.home.default404 = Backbone.View.extend({
        initialize: function () {
            this.render();
        },
        render:function(){
            //inventMx.page.wrapper_site.animate({ "left": "+=2000px" }, "slow" );
            inventMx.page.wrapper_site.load("/web/app/inventmx/PageDefault/404.html", function () {
                
                //inventMx.page.wrapper_site.show("slow");
                //inventMx.page.wrapper_site.animate({ "left": "-=2000px" }, "slow",function(){
                    inventMx.utilities.loaderHide();
                    setTimeout(inventMx.utilities.loaderHide, 7000);
                //});                                
                return this;
            });            
        },        
    });
    

});