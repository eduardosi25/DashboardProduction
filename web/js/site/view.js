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
        options = {idform:idform};
        if(validate) {
            inventMx.utilities.loaderShow();
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
            
            inventMx.metas.configure = {
                title: "Home | InventMx",
                canonical: "http://www.inventmx.com",
                description: "Inventmx es la comunidad de sitios mas grande de mexico, acercamos personas con perfiles similares mediante el uso natural del Internet",
                og_site_name: "InventMX",
                og_title: "InventMX",
                og_description: "Inventmx es la comunidad de sitios mas grande de mexico, acercamos personas con perfiles similares mediante el uso natural del Internet",
                og_url: "http://www.inventmx.com",
                og_type: "website",
                og_image: "/web/img/favicons/mstile-150x150.png",
            };
            inventMx.metas.compile();
            
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
                Options_sites = {
                    section: "#sections-sites",
                    template: "#template-sections-sites",
                    idSitesUl: "#sections-sites li.sections-sites",
                }
                inventMx.dataSource.params.url = null;
                inventMx.dataSource.params.limit = "30";
                inventMx.dataSource.params.sort = "id:ASC";
                inventMx.dataSource.load(repo,inventMx.render.tplSites,Options_sites);                
                
                repo = "vloger.json";
                inventMx.dataSource.params.sort = null;
                inventMx.dataSource.params.url = null;
                inventMx.dataSource.params.limit = "100";
                listTalentos = new inventMx.home.listPerfilTalentos(repo);
                
                inventMx.utilities.validateAcordeon(id_container,tagHeader,topOffset);
                inventMx.utilities.homeAddRemoveSections(id_section1,id_section2);
                
                // Un objeto puede disparar un evento en el momento que desee
                // utilizando la función trigger
                /*inventMx_events.trigger('NoData','Home');*/ 
                
                $("#slide-home article").owlCarousel({
                    singleItem: true,
                    autoPlay: true,
                    lazyLoad: false,
                    pagination: true,
                    navigation: true,
                    navigationText: [
                        "<i class='nex_prev block'></i>",
                        "<i class='nex_next block'></i>"
                    ],
                    autoHeight: true,
                });
                
                
                
                
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
            
            inventMx.metas.configure = {
                title: "Audiencias y Contenidos | InventMx",
                canonical: "http://www.inventmx.com/#audiencias-y-contenidos",
                description: "Inventmx es la comunidad de sitios mas grande de mexico, acercamos personas con perfiles similares mediante el uso natural del Internet",
                og_site_name: "InventMX",
                og_title: "InventMX",
                og_description: "Inventmx es la comunidad de sitios mas grande de mexico, acercamos personas con perfiles similares mediante el uso natural del Internet",
                og_url: "http://www.inventmx.com/#audiencias-y-contenidos",
                og_type: "website",
                og_image: "/web/img/favicons/mstile-150x150.png",
            };
            inventMx.metas.compile();
            
            idAncla =  idSection;
            this.render(idAncla);
        },
        render:function(idAncla){
            var id_section1 = "#section-home-contactos";
            var noticias = "#site-noticias-deportes li.sections-sites";
            var Msaludable = "#mundo-saludable li.sections-sites";
            var Mfemenino = "#mundo-femenino li.sections-sites";
            var lifeStyle = "#life-style li.sections-sites";
                    
            var widthDevice = inventMx.utilities.deviceWidthWindow();
                        
            inventMx.page.wrapper_site.load("/web/app/inventmx/audiencias-y-contenidos/home.html", function () {
                                
                inventMx.dataSource.params.limit = "100";
                
                /* NOTICIAS, NEGOCIOS */
                repo = "audience.json";
                Options_noticias = {
                    section: "#noticias-negocios",
                    template: "#template-audiencias-contenidos",
                }
                inventMx.dataSource.params.url = "noticias-y-negocios";
                inventMx.dataSource.params.audience_url = null;
                inventMx.dataSource.load(repo,inventMx.render.tplAudienciasContenidos,Options_noticias);
                
                /* sites de noticias y negocios */
                repo = "sites.json";
                Options_site_noticias = {
                    section: "#site-noticias-deportes",
                    template: "#template-sections-sites",
                    idSitesUl: "#site-noticias-deportes li.sections-sites",
                }  
                inventMx.dataSource.params.url = null;
                inventMx.dataSource.params.sort = "id:ASC";
                inventMx.dataSource.params.audience_url = "noticias-y-negocios";
                inventMx.dataSource.load(repo,inventMx.render.tplSites,Options_site_noticias);
                
                
                /* MUNDO SALUDABLE */
                repo = "audience.json";
                Options_saludable = {
                    section: "#mundo-saludable",
                    template: "#template-audiencias-contenidos",
                }
                inventMx.dataSource.params.url = "mundo-saludable";
                inventMx.dataSource.params.audience_url = null;
                inventMx.dataSource.load(repo,inventMx.render.tplAudienciasContenidos,Options_saludable);
                
                /* sites de mundo saludable */
                repo = "sites.json";
                Options_site_saludable = {
                    section: "#site-mundo-saludable",
                    template: "#template-sections-sites",
                    idSitesUl: "#site-mundo-saludable li.sections-sites",
                }
                inventMx.dataSource.params.url = null;
                inventMx.dataSource.params.sort = "id:ASC";
                inventMx.dataSource.params.audience_url = "mundo-saludable";
                inventMx.dataSource.load(repo,inventMx.render.tplSites,Options_site_saludable);
                
                
                /* MUNDO FEMENINO */
                repo = "audience.json";
                Options_Mfemenino = {
                    section: "#mundo-femenino",
                    template: "#template-audiencias-contenidos",
                }
                inventMx.dataSource.params.url = "mundo-femenino";
                inventMx.dataSource.params.audience_url = null;
                inventMx.dataSource.load(repo,inventMx.render.tplAudienciasContenidos,Options_Mfemenino);
                
                /* sites de mundo femenino */
                repo = "sites.json";
                Options_site_Mfemenino = {
                    section: "#site-mundo-femenino",
                    template: "#template-sections-sites",
                    idSitesUl: "#site-mundo-femenino li.sections-sites",
                }
                inventMx.dataSource.params.url = null;
                inventMx.dataSource.params.sort = "id:ASC";
                inventMx.dataSource.params.audience_url = "mundo-femenino";
                inventMx.dataSource.load(repo,inventMx.render.tplSites,Options_site_Mfemenino);
                
                /* MUNDO LIFE & STYLE */
                repo = "audience.json";
                Options_lifestye = {
                    section: "#lifestye",
                    template: "#template-audiencias-contenidos",
                }
                inventMx.dataSource.params.url = "life-style";
                inventMx.dataSource.params.audience_url = null;
                inventMx.dataSource.load(repo,inventMx.render.tplAudienciasContenidos,Options_lifestye);
                
                /* sites de life-style */
                repo = "sites.json";
                Options_site_lifestye = {
                    section: "#site-lifestye",
                    template: "#template-sections-sites",
                    idSitesUl: "#site-lifestye li.sections-sites",
                }
                inventMx.dataSource.params.url = null;
                inventMx.dataSource.params.sort = "id:ASC";
                inventMx.dataSource.params.audience_url = "life-style";
                inventMx.dataSource.load(repo,inventMx.render.tplSites,Options_site_lifestye);
                
                
                inventMx.dataSource.params.url = null;
                inventMx.dataSource.params.sort = null;
                inventMx.dataSource.params.audience_url = null;
                
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
                                    
                    setTimeout(inventMx.utilities.loaderHide, 7000);
                    
                    if(idAncla !== true){
                        if($("#"+idAncla).length){
                            function top(){
                                offset1 = $("#"+idAncla).offset();
                                var offset = offset1.top;
                                inventMx.utilities.topOffset(offset,0);
                            }
                            
                            setTimeout(top, 1000);
                            
                        }else {
                            var ficha = new inventMx.home.default404();
                        }
                    }
                    
                    
                    $(window).resize(function () {
                        //e.stopPropagation();
                        inventMx.utilities.oneAddRemoveSections(id_section1);
                        widthDevice = inventMx.utilities.deviceWidthWindow();

                        if(widthDevice >= 701){
                            
                            /* recalcular alto  de los sitios */
                            idHeightNoticias = Options_site_noticias.idSitesUl;
                            $(idHeightNoticias).css("height","auto");
                            finalNoticias = inventMx.utilities.calculateheightItem(idHeightNoticias);
                            $(idHeightNoticias).height(finalNoticias);

                            idHeightSaludable = Options_site_saludable.idSitesUl;
                            $(idHeightSaludable).css("height","auto");
                            finalSaludable = inventMx.utilities.calculateheightItem(idHeightSaludable);
                            $(idHeightSaludable).height(finalSaludable);

                            idHeightFemenino = Options_site_Mfemenino.idSitesUl;
                            $(idHeightFemenino).css("height","auto");
                            finalFemenino = inventMx.utilities.calculateheightItem(idHeightFemenino);
                            $(idHeightFemenino).height(finalFemenino);                    

                            idHeightLifestye = Options_site_lifestye.idSitesUl;
                            $(idHeightLifestye).css("height","auto");
                            finalLifestye = inventMx.utilities.calculateheightItem(idHeightLifestye);
                            $(idHeightLifestye).height(finalLifestye);
                            
                            /*$(sites).css("height","auto");
                            finalSites = inventMx.utilities.calculateheightItem(options.idSitesUl);
                            $(sites).height(finalSites);*/

                            $(noticias).css("height","auto");
                            finalNumbers = inventMx.utilities.calculateheightItem(noticias);
                            $(noticias).height(finalNumbers);

                            $(Msaludable).css("height","auto");
                            finalNumbers1 = inventMx.utilities.calculateheightItem(Msaludable);
                            $(Msaludable).height(finalNumbers1);

                            $(Mfemenino).css("height","auto");
                            finalNumbers2 = inventMx.utilities.calculateheightItem(Mfemenino);
                            $(Mfemenino).height(finalNumbers2);

                            $(lifeStyle).css("height","auto");
                            finalNumbers3 = inventMx.utilities.calculateheightItem(lifeStyle);
                            $(lifeStyle).height(finalNumbers3);
                        }

                    });
                    
                });
                
                return this;
        },        
    }),
    
    
    inventMx.home.homeMarketers = Backbone.View.extend({
        el: inventMx.page.wrapper_site,
        initialize: function (idSection) {
            
            inventMx.metas.configure = {
                title: "Marketers | InventMx",
                canonical: "http://www.inventmx.com/#marketers",
                description: "Inventmx es la comunidad de sitios mas grande de mexico, acercamos personas con perfiles similares mediante el uso natural del Internet",
                og_site_name: "InventMX",
                og_title: "InventMX",
                og_description: "Inventmx es la comunidad de sitios mas grande de mexico, acercamos personas con perfiles similares mediante el uso natural del Internet",
                og_url: "http://www.inventmx.com/#marketers",
                og_type: "website",
                og_image: "/web/img/favicons/mstile-150x150.png",
            };
            inventMx.metas.compile();
            
            
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
                        
            inventMx.page.wrapper_site.load("/web/app/inventmx/marketers/home.html", function () {
                    
                repo = "sites.json";
                Options_sites = {
                    section: "#sites-socials",
                    template: "#template-sites-socials",
                    idSitesUl: "#sites-socials li.sections-sites",
                }
                inventMx.dataSource.params.url = null;
                inventMx.dataSource.params.limit = "100";
                inventMx.dataSource.params.sort = "id:ASC";
                inventMx.dataSource.params.audience_url = null;
                inventMx.dataSource.load(repo,inventMx.render.tplSites,Options_sites);
                inventMx.dataSource.params.sort = null;
                //inventMx.dataSource.load(repo,inventMx.render.tplAudienciasContenidos,Options_Mfemenino);
                
                    
                finalNumbers = inventMx.utilities.calculateheightItem(rich1);
                $(rich1).height(finalNumbers);
                finalNumbers = inventMx.utilities.calculateheightItem(rich2);
                $(rich2).height(finalNumbers);
                finalNumbers = inventMx.utilities.calculateheightItem(mobile);
                $(mobile).height(finalNumbers);
                    
                inventMx.utilities.loaderHide();
                setTimeout(inventMx.utilities.loaderHide, 7000);
                
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
                
                $(rich1).css("height","auto");
                finalNumbers = inventMx.utilities.calculateheightItem(rich1);
                $(rich1).height(finalNumbers);
                
                $(rich2).css("height","auto");
                finalNumbers = inventMx.utilities.calculateheightItem(rich2);
                $(rich2).height(finalNumbers);
                
                $(mobile).css("height","auto");
                finalNumbers = inventMx.utilities.calculateheightItem(mobile);
                $(mobile).height(finalNumbers);
                
                idSitesUl = "#sites-socials li.sections-sites";
                $(idSitesUl).css("height","auto");
                finalNumbers = inventMx.utilities.calculateheightItem(idSitesUl);
                $(idSitesUl).height(finalNumbers);
                //finalNumbers = inventMx.utilities.calculateheightItem(rich2);
                //$(rich2).height(finalNumbers);
                //inventMx.utilities.changeResolitionsImg(id_image_firts);
            });
            
        },
    }),
    
    inventMx.home.homeRedeVideo = Backbone.View.extend({
        el: inventMx.page.wrapper_site,
        initialize: function () {
            
            inventMx.metas.configure = {
                title: "Red de Video | InventMx",
                canonical: "http://www.inventmx.com/#red-de-video",
                description: "Inventmx es la comunidad de sitios mas grande de mexico, acercamos personas con perfiles similares mediante el uso natural del Internet",
                og_site_name: "InventMX",
                og_title: "InventMX",
                og_description: "Inventmx es la comunidad de sitios mas grande de mexico, acercamos personas con perfiles similares mediante el uso natural del Internet",
                og_url: "http://www.inventmx.com/#red-de-video",
                og_type: "website",
                og_image: "/web/img/favicons/mstile-150x150.png",
            };
            inventMx.metas.compile();
            
            $(this.el).unbind();
            _.bindAll(this, 'render');
            this.render();            
        },
        render:function(){
            //var url = "/web/data/home/home.json";
            //var params = "";
            var id_section1 = "#section-home-contactos";
            
            inventMx.page.wrapper_site.load("/web/app/inventmx/redVideo/home.html", function () {
                
                var repo = "vloger.json";
                inventMx.dataSource.params.limit = "100";
                
                /* NOTICIAS, NEGOCIOS */
                Options_noticias = {
                    section: "#red-videos-noticias",
                    template: "#template-red-videos-noticias",
                }
                inventMx.dataSource.params.audience_url = "noticias-y-negocios";
                inventMx.dataSource.load(repo,inventMx.render.tplRedVideos,Options_noticias);
                
                /* MUNDO SALUDABLE */
                Options_Msaludable = {
                    section: "#red-videos-mundo-saludable",
                    template: "#template-red-videos-mundo-saludable",
                }
                inventMx.dataSource.params.audience_url = "mundo-saludable";
                inventMx.dataSource.load(repo,inventMx.render.tplRedVideos,Options_Msaludable);
                
                /* MUNDO FEMENINO */
                Options_Mfemenino = {
                    section: "#red-videos-mundo-femenino",
                    template: "#template-red-videos-mundo-femenino",
                }
                inventMx.dataSource.params.audience_url = "mundo-femenino";
                inventMx.dataSource.load(repo,inventMx.render.tplRedVideos,Options_Mfemenino);
                
                /* LIFE & STYLE */
                Options_lifeStyle = {
                    section: "#red-videos-lifeStyle",
                    template: "#template-red-videos-lifeStyle",
                }
                inventMx.dataSource.params.audience_url = "life-style";
                inventMx.dataSource.load(repo,inventMx.render.tplRedVideos,Options_lifeStyle);
                
                inventMx.utilities.oneAddRemoveSections(id_section1);
                                
                //inventMx.page.wrapper_site.show("slow");
                //inventMx.page.wrapper_site.animate({ "left": "-=2000px" }, "slow",function(){
                inventMx.dataSource.params.audience_url = null;
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
            
            inventMx.metas.configure = {
                title: "Casos de Éxito | InventMx",
                canonical: "http://www.inventmx.com/#casos-de-exito",
                description: "Inventmx es la comunidad de sitios mas grande de mexico, acercamos personas con perfiles similares mediante el uso natural del Internet",
                og_site_name: "InventMX",
                og_title: "InventMX",
                og_description: "Inventmx es la comunidad de sitios mas grande de mexico, acercamos personas con perfiles similares mediante el uso natural del Internet",
                og_url: "http://www.inventmx.com/#casos-de-exito",
                og_type: "website",
                og_image: "/web/img/favicons/mstile-150x150.png",
            };
            inventMx.metas.compile();
            
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
            
            inventMx.metas.configure = {
                title: "Afíliate | InventMx",
                canonical: "http://www.inventmx.com/#afiliate",
                description: "Inventmx es la comunidad de sitios mas grande de mexico, acercamos personas con perfiles similares mediante el uso natural del Internet",
                og_site_name: "InventMX",
                og_title: "InventMX",
                og_description: "Inventmx es la comunidad de sitios mas grande de mexico, acercamos personas con perfiles similares mediante el uso natural del Internet",
                og_url: "http://www.inventmx.com/#afiliate",
                og_type: "website",
                og_image: "/web/img/favicons/mstile-150x150.png",
            };
            inventMx.metas.compile();
            
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
                    inventMx.utilities.loaderShow();
                    console.log("cargando");
                    data = $(this).serializeArray();
                    inventMx_events.trigger('Inventform','#form-afiliate',data);
                    return false;
                });
                //return this;
            });
            
            $(window).resize(function (e) {
                e.stopPropagation();
                inventMx.utilities.changeResolitionsImg(id_image_firts);
            });
            
        }
    }),
    inventMx.home.homeAnunciate = Backbone.View.extend({
        el: inventMx.page.wrapper_site,
        initialize: function () {
            
            inventMx.metas.configure = {
                title: "Anúnciate | InventMx",
                canonical: "http://www.inventmx.com/#anunciate",
                description: "Inventmx es la comunidad de sitios mas grande de mexico, acercamos personas con perfiles similares mediante el uso natural del Internet",
                og_site_name: "InventMX",
                og_title: "InventMX",
                og_description: "Inventmx es la comunidad de sitios mas grande de mexico, acercamos personas con perfiles similares mediante el uso natural del Internet",
                og_url: "http://www.inventmx.com/#anunciate",
                og_type: "website",
                og_image: "/web/img/favicons/mstile-150x150.png",
            };
            inventMx.metas.compile();
            
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