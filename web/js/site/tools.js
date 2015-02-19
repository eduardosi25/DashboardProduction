/* Init alls */

(function (inventMx, undefined) {
    //inventMx.ajax = {}, no use
    inventMx.utilities = {},
    inventMx.home = {},   
    //inventMx.pageDefault = {},  //no use
    inventMx.email = {},
    inventMx.main = {},
    inventMx.header = {}, //no use
    inventMx.header.main = function () {}, //no use
    inventMx.page = {},
    inventMx.render = {},
    inventMx.metas = {},
    inventMx.config = {
        website: 'http://www.inventmx.com/',
        websiteUrl: 'http://www.inventmx.com/',
        webAppBaseUrl: 'http://invent.jediteam.mx/',
        data_source: {
            baseUrl: "http://api.inventmx.com/v1/inventmx",
            apiKey: "3a5877fc16b6fcbf8eedbe55d091938a"
        }
    };
    inventMx.dataSource = {
        params: {
            sort: null,
            section_page: null,
            type: null,
            fields: null,
            limit: null,
            offset: null,
            audio: null,
            category_ids: null,
            tag_ids: null,
            category_url: null,
            audience_url: null,
            tag_url: null,
            created_start: null,
            created_finish: null,
            callback: null,
            not_ids: null,
            columnista_ids: null,
            sub_category_url: null
        }
    },
    inventMx.metas = {},
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
    
    inventMx.page.wrapper_site = $("#wrapper-page-site");
    inventMx.page.wrapper_bgMessageSendEmailShow = function(){
        $(".bg-messaje-send-form, .wrapper-messaje-form").show();
    },
    inventMx.page.wrapper_bgMessageSendEmailHide = function(){
        $(".bg-messaje-send-form, .wrapper-messaje-form").hide();
    },
    inventMx.utilities.loaderShow = function () {
        $("#wrapper-loading-layout").css("display", "block");
    },
    inventMx.utilities.loaderHide = function () {
        $("#wrapper-loading-layout").css("display", "none");
    },
    inventMx.metas.compile = function() {
        
        var head = $("#metas").html();
        var tpl_head = Handlebars.compile(head);
        var view_head = tpl_head(inventMx.metas.configure);
        //var metas;
        $("head meta, head link[rel='canonical']").each(function () {
            //metas += $(this).clone().wrap('<div>').parent().html();
            $(this).remove();
        });
        $("title").remove();
        $("head").prepend(view_head);
    },
    inventMx.render.tplHomeTalentos = function(resp){
        if (resp) {
            dataVideos = resp.data;
            //dataVideos = data.slice(0, 15);
            var redVideos = $("#template-home-red-videos").html();
            var tpl_redVideos = Handlebars.compile(redVideos);
            var view_redVideos = tpl_redVideos(dataVideos);
            $("#home-red-videos").html(view_redVideos);
            
            /*var perfil = "#home-red-videos ul li";
            finalPerfil = inventMx.utilities.calculateheightItem(perfil);
            $(perfil).height(finalPerfil);*/
            
        } else {
            inventMx.utilities.loaderHide();
            $("#home-red-videos").append("<p>No hay datos para mostrar</p>");
        }

        if ($("img.lazy").length) {
            $("img.lazy").lazyload({
                effect: "fadeIn",
                placeholder:'/web/img/global/default.png'
            });
        }                

        inventMx.utilities.loaderHide();
        setTimeout(inventMx.utilities.loaderHide, 7000);
    },
    inventMx.render.tplAudienciasContenidos = function(resp,options){
        
        if (resp.response.status == 200) {
            dataRedVideo = resp.data[0];
            
            if(dataRedVideo){
                var redVideos = $(options.template).html();
                var tpl_redVideos = Handlebars.compile(redVideos);
                var view_redVideos = tpl_redVideos(dataRedVideo);
                $(options.section).html(view_redVideos);
                inventMx.utilities.loaderHide();
                
            }else {
                $(options.section).append("<p> Ha ocurrido un  error al cargar esta sección</p>")
            }
            
        }else {
            error404 = new inventMx.home.default404();
        }
        
    },
    inventMx.render.tplPerfilTalentos = function(resp){
        if (resp.response.status == 200) {
            
            dataPerfil = resp.data[0];
            var url_taxonomy;
            
            if(resp.data.length){
                url_taxonomy = dataPerfil.audience[0].url;
                
            temp_url = $.url(dataPerfil.url);
            np_url = 'http://' + window.location.host + "#" + temp_url.attr('relative');
            url = np_url.replace('#/','#');
                
            inventMx.metas.configure = {
                title: dataPerfil.title +" | InventMx",
                canonical: url,
                description: dataPerfil.summary,
                og_site_name: "InventMX",
                og_title: "InventMX",
                og_description: dataPerfil.summary,
                og_url: url,
                og_type: "website",
                og_image: dataPerfil.images.picture[0].url,
            };
            inventMx.metas.compile();
                
                
            }
            var perfilTalentos = $("#template-perfil-talento").html();
            var tpl_perfilTalentos = Handlebars.compile(perfilTalentos);
            var view_perfilTalentos = tpl_perfilTalentos(dataPerfil);
            $("#perfil-talento").html(view_perfilTalentos);
            
            if(resp.data.length){
                
                temp_taxonomy = $.url(url_taxonomy);
                taxonomy_path = temp_taxonomy.attr('relative');
                
                repo = "vloger.json";
                inventMx.dataSource.params.url = null;
                inventMx.dataSource.params.audience_url = taxonomy_path;
                inventMx.dataSource.params.limit = "100"; 
                talentos = new inventMx.home.listPerfilTalentos(repo);
                inventMx.dataSource.params.audience_url = null;
            }else {
                url = window.location.href;
                temp_url = $.url(url);
                np_url = temp_url.attr('relative');
                url = np_url.replace('/#', '');
                
                perfilSitio = new inventMx.home.homePerfilSitio(url);
                //error404 = new inventMx.home.default404();
            }
            
        }else {
            error404 = new inventMx.home.default404();
        }

        inventMx.utilities.loaderHide();
        setTimeout(inventMx.utilities.loaderHide, 7000);
        
    },
    inventMx.render.tplPerfilSites = function(resp){
        if (resp.response.status == 200) {
            
            dataSite = resp.data[0];
            
            if(dataSite){
                
                temp_url = $.url(dataSite.url);
                np_url = 'http://' + window.location.host + "#" + temp_url.attr('relative');
                url = np_url.replace('#/','#');
                
                inventMx.metas.configure = {
                    title: dataSite.title +" | InventMx",
                    canonical: url,
                    description: dataSite.summary,
                    og_site_name: "InventMX",
                    og_title: "InventMX",
                    og_description: dataSite.summary,
                    og_url: url,
                    og_type: "website",
                    og_image: dataSite.images.logo[0].url,
                };
                inventMx.metas.compile();
                
                
                var perfilSite = $("#template-perfil-site").html();
                var tpl_perfilSite = Handlebars.compile(perfilSite);
                var view_perfilSite = tpl_perfilSite(dataSite);
                $("#perfil-site").html(view_perfilSite);

                itemsFolow = $(".wrapper-bars .content-visit").length;
                itemsFolow = parseInt(itemsFolow);
                //console.log(itemsFolow);
                if(itemsFolow == 5) {
                    $(".wrapper-bars .content-visit").css("padding-top","10px");
                    $(".wrapper-bars .content-visit").eq(4).addClass("itemUnit");
                    //$(".wrapper-bars .content-visit").eq(4).css({"max-width":"320px","width":"100%","margin":"0  auto"});
                }else if (itemsFolow == 4) {
                    $(".wrapper-bars .content-visit").css("padding-top","30px");
                }else if (itemsFolow == 3) {
                    $(".wrapper-bars .content-visit").css("padding-top","30px");
                    //$(".wrapper-bars .content-visit").eq(2).css({"max-width":"320px","width":"100%","margin":"0  auto"});
                    $(".wrapper-bars .content-visit").eq(2).addClass("itemUnit");
                }else if (itemsFolow == 2 || itemsFolow == 1) {
                    $(".wrapper-bars .content-visit").css("padding-top","60px");
                }

            }else {
                error404 = new inventMx.home.default404();
            }
            
        }else {
            error404 = new inventMx.home.default404();
        }
        
        inventMx.utilities.loaderHide();
        setTimeout(inventMx.utilities.loaderHide, 7000);
        
    },
    inventMx.render.tplSites = function(resp,options){
        data = resp.data;
        
        if(data){
            var site = $(options.template).html();
            var tpl_site = Handlebars.compile(site);
            var view_site = tpl_site(data);
            $(options.section).html(view_site);
                        
            $(sites).css("height","auto");
            var sites = options.idSitesUl;
            finalSites = inventMx.utilities.calculateheightItem(sites);
            $(sites).height(finalSites);
            
        }else {
            $("#template-sections-sites").append("<p> Ha ocurrido un  error al cargar esta sección</p>")
        }
        
    },
    inventMx.render.tplcaseExito = function(resp){
        
        if (resp.response.status == 200) {
            dataCase = resp.data;
            
            if(dataCase){
                var caseExit = $("#template-sections-case-exito").html();
                var tpl_case = Handlebars.compile(caseExit);
                var view_case = tpl_case(dataCase);
                $("#sections-case-exito").html(view_case);
                
                if ($("img.lazy").length) {
                    $("img.lazy").lazyload({
                        effect: "fadeIn"
                    });
                }
                
                inventMx.utilities.loaderHide();
                
            }else {
                $("#template-sections-case-exito").append("<p> Ha ocurrido un  error al cargar esta sección</p>")
            }
            
        }else{
            error404 = new inventMx.home.default404();
        }
    },
    inventMx.render.tplRedVideos = function(resp,options){
        if (resp.response.status == 200) {
            dataRedVideo = resp.data;
            
            if(dataRedVideo){
                
                var redVideos = $(options.template).html();
                var tpl_redVideos = Handlebars.compile(redVideos);
                var view_redVideos = tpl_redVideos(dataRedVideo);
                $(options.section).html(view_redVideos);
                
                if ($("img.lazy").length) {
                    $("img.lazy").lazyload({
                        effect: "fadeIn",
                        placeholder:'/web/img/global/default.png'
                    });
                }
                
            }else {
                $(options.section).append("<p> Ha ocurrido un  error al cargar esta sección</p>")
            }
            
            
        }else {
            error404 = new inventMx.home.default404();
        }
    },
    inventMx.render.tplGenereral = function(resp,options){
        data = resp.data;
        
        if(data){
            var site = $(options.template).html();
            var tpl_site = Handlebars.compile(site);
            var view_site = tpl_site(data);
            $(options.section).html(view_site);
            
        }else {
            $(options.section).append("<p> Ha ocurrido un  error al cargar esta sección</p>")
        }
        
    },
    inventMx.utilities.isArray = function (value) {
        //function isArray(value) {
        return (value === null || typeof value === 'array')? true : false;
            //return Object.prototype.toString.call(value) === "[object Array]";
        //}
    },
    inventMx.utilities.isObject = function (value) {
        //function isArray(value) {
        return (value === null || typeof value === 'object')? true : false;
            //return Object.prototype.toString.call(value) === "[object Object]";
        //}
    },
    inventMx.dataSource.load = function(repo,callback,options) {
        req_url = inventMx.config.data_source.baseUrl;
        req_api_key = inventMx.config.data_source.apiKey;

        //Dejamos unicamente los parametros que fueron asignados los que no se desechan
        data_params = inventMx.dataSource.params;
        params = {};
        $.each(data_params, function(i, j) {
            if (j) {
                params[i] = j;
            }

        });

        url_ajax = req_url + "/" + repo + "/" + req_api_key + "?callback=?";
        inventMx.dataSource.getAjax(url_ajax, params,callback,options);
        
    },
    inventMx.dataSource.getAjax = function(url, params,callback,options) {
        jQuery.ajax({
            url: url,
            data: params,
            dataType: 'json',
            type: 'GET',
            timeout: 100000,
            contentType: "application/json; charset=utf-8",
            async: false,
            success: function(data) {
                //console.log(data);
                if (data) {
                    callback(data,options);
                } else {
                    inventMx.utilities.loaderHide();
                    alert("Hubo un error inesperado, intenta nuevamente por favor");
                }
            },
            error: function(request, status, error) {
                inventMx.utilities.loaderHide();
                return alert("Hubo un error inesperado, intenta nuevamente por favor");
            }
        });
    },
    inventMx.email.data = function(data,options){
        //console.log(data);
        //console.log(options.idform);
        //alert(data.text);
        inventMx.page.wrapper_bgMessageSendEmailShow();
        idform = options.idform;
        //$(options.idform + " :input[type='submit']").html("Enviar");
        $(idform + " :input[type='text']").val("");
        inventMx.utilities.loaderHide();
        
    },
    inventMx.utilities.deviceWidthWindow = function(){
        return $(window).width();
    },
    inventMx.utilities.deviceWidthDocument = function(){
        return $(document).width();
    },
    inventMx.utilities.validateAcordeon = function(id_container, tagHeader, topOffset,e){
        var deviceWidthWindow = inventMx.utilities.deviceWidthWindow();
        
            if (deviceWidthWindow <= 700) {
                //console.log(deviceWidthWindow + " |");
                inventMx.utilities.accordionStatus = "active";
                inventMx.utilities.accordionInit(id_container, tagHeader, topOffset);
            }else {
                //console.log("|| "+deviceWidthWindow);
                ui_state_active = $(id_container + " " + tagHeader+".ui-state-active");
                if(ui_state_active.length){
                    //console.log("destroy");
                    inventMx.utilities.accordionDestroy(id_container);
                    inventMx.utilities.accordionStatus = "destroy";
                }
            }
        
    },
    inventMx.utilities.validateAcordeonOffsetStatus = false;
    inventMx.utilities.validateAcordeonOffset = function(id_container){
        var deviceWidthWindow = inventMx.utilities.deviceWidthWindow();
            if (deviceWidthWindow <= 700) {
                offset1 = $(id_container).offset();
                var offset = offset1.top;
                inventMx.utilities.topOffset(offset);
            }
    },
    inventMx.utilities.topOffset = function(position,transition) {
        transition = (transition) ? transition : 500;
        $('body,html').delay(position).animate({
            scrollTop: position
        }, transition,function(){
            inventMx.utilities.validateAcordeonOffsetStatus = false;
        });
    },
    inventMx.utilities.accordionStatus = "disabled",
    inventMx.utilities.accordionInit = function(id_container,tagHeader,topOffset) {
        $(id_container).accordion({
            'header': tagHeader,
            heightStyle: "content",
            collapsible: true,
            disabled: false,
            active: 0
        });
        
        inventMx.utilities.accordionStatus = "active";
        
        if(topOffset) {
            //section = $("#accordion").attr("id");
            offset1 = $(id_container).offset();
            var offset = offset1.top;
            //topAcorrdion(offset);            
            inventMx.utilities.topOffset(offset);
        }
    },
    inventMx.utilities.accordionDestroy = function(id_container) {
        $(id_container).accordion("destroy");        
        inventMx.utilities.accordionStatus = "destroy";
    },
    inventMx.utilities.homeAddRemoveSections = function(id_section1, id_section2){
        deviceWidthWindow = inventMx.utilities.deviceWidthWindow();
        if (deviceWidthWindow >= 701) {
            script_section1 = $(id_section1+"-1").html();
            $(id_section1).html(script_section1);
        
            script_section2 = $(id_section2+"-1").html();
            $(id_section2).html(script_section2);
        } else {
            $(id_section1).html("");
            $(id_section2).html("");
        }
    },    
    inventMx.utilities.caseExitoAddRemoveSections = function(id_section1,id_section2){
        deviceWidthWindow = inventMx.utilities.deviceWidthWindow();
        if (deviceWidthWindow >= 701) {
            script_section1 = $(id_section1+"-1").html();
            $(id_section1).html(script_section1);
            
            script_section2 = $(id_section2+"-1").html();
            $(id_section2).html(script_section2);
                    
        } else {
            $(id_section1).html("");
            $(id_section2).html("");
        }
    },
    inventMx.utilities.oneAddRemoveSections = function(id_section1){
        deviceWidthWindow = inventMx.utilities.deviceWidthWindow();
        if (deviceWidthWindow >= 701) {
            script_section1 = $(id_section1+"-1").html();
            $(id_section1).html(script_section1);
        } else {
            $(id_section1).html("");
        }
    },
    inventMx.utilities.calculateheightItem = function(items){
        var numbers = [];
        $(items).each(function(i,j){            
            numbers[i] = $(this).height();
        });
        return inventMx.utilities.searchNumbersMayor(numbers);
    }
    inventMx.utilities.searchNumbersMayor = function(number){
        //function mayor(m){
        var numbers=[].slice.call(number);
        return numbers.sort(function(a,b){return a-b;}).pop();
        //Math.round(2);
        
        //}
        //j = [101,2,3,14,5,55,205];
        //alert(mayor(j));
    },
    inventMx.main.activeHover = function(){
        $("header ul li a").removeClass("active");
        section =  inventMx.utilities.section;
        $("header ul li a."+section).addClass("active");
    },
    inventMx.utilities.changeResolitionsImg = function(id_image_firts){
        deviceWidthWindow = inventMx.utilities.deviceWidthWindow();
        //1366       1920x800.jpg
        active = false;
        src = $(id_image_firts).attr("data-src");
        w1920 = "1920x800.jpg";
        w1024 = "1024x800.jpg";
        w700  = "700x800.jpg";
        w400  = "400x800.jpg";
        
        if (deviceWidthWindow >= 1300 && !active) {
            active = true;
            src = src + w1920;
            $(id_image_firts).attr("src",src);
            active = false;
        } else if(deviceWidthWindow <= 1299 && deviceWidthWindow >= 701 && !active) {
            active = true;
            src = src + w1024;            
            $(id_image_firts).attr("src",src);            
            active = false;
        } else if(deviceWidthWindow <= 700 && deviceWidthWindow >= 400 && !active) {
            active = true;
            src = src + w700;
            $(id_image_firts).attr("src",src);
            active = false;
        }else if(deviceWidthWindow <= 400 && !active) {
            active = true;
            src = src + w400;
            $(id_image_firts).attr("src",src);
            active = false;
        }
    }
    
    $(document).ready(function(){
        devicewidth = inventMx.utilities.deviceWidthWindow();

        $(document).on("click",".wrapper-messaje-form-btn .btn-publish",function(e){
            e.preventDefault();
            inventMx.page.wrapper_bgMessageSendEmailHide();
        });

        $("header .main-center").click(function(){
            if (devicewidth < 701) {
                $("header ul").slideToggle("fast");
            }else{
                $("header ul").css("display", "block");
            }
        });

        $("header ul li").click(function(){
            if (devicewidth < 701) {
                $("header ul").css("display", "none");
            }else{
                $("header ul").css("display", "block");
            }
        });
        
        /*$(document).on("click",".red-invent-sections-sites .wrapper-ico-sumary",function(){
         $(this).parent().toggleClass("active");
         });*/                
        
    });
    
    
    $(window).resize(function () {
        devicewidth = inventMx.utilities.deviceWidthWindow();
        
        $("header .main-center").click(function(){
            if (devicewidth > 700) {                
                $("header ul").css("display","block");
            }
        });
        
        if (devicewidth > 700) {
            $("header ul").css("display", "block");
        }else {
            $("header ul").css("display", "none");
        }

        $("header ul li").click(function(){
            if (devicewidth < 701) {
                $("header ul").css("display", "none");
            }else{
                $("header ul").css("display", "block");
            }
        });

        
    });

})(window.inventMx = window.inventMx || {});
/* end alls */

/* init view */
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
                    autoPlay: 8000,
                    lazyLoad: false,
                    pagination: true,
                    navigation: true,
                    navigationText: [
                        "<i class='nex_prev block'></i>",
                        "<i class='nex_next block'></i>"
                    ],
                    autoHeight: true,
                });


                services = ".wrapper-our-services ul li.services-sites";
                $(services).css("height","auto");
                finalSites = inventMx.utilities.calculateheightItem(services);
                $(services).height(finalSites);
                
                
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


                    services = ".wrapper-our-services ul li.services-sites";
                    $(services).css("height","auto");
                    finalSites = inventMx.utilities.calculateheightItem(services);
                    $(services).height(finalSites);

                    
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
    
    inventMx.home.avisoPrivacidad = Backbone.View.extend({
        initialize: function () {
            this.render();
        },
        render:function(){
            inventMx.page.wrapper_site.append("<div id='aviso-politicas'><article><article></div>");
            $("#aviso-politicas article").load("/web/app/inventmx/politicas/aviso-de-privacidad.php", function () {
                    inventMx.utilities.loaderHide();
                    setTimeout(inventMx.utilities.loaderHide, 7000);
                return this;
            });
            return this;
        },
    });
    
    inventMx.home.politicAmbiental = Backbone.View.extend({
        initialize: function () {
            this.render();
        },
        render:function(){
            inventMx.page.wrapper_site.append("<div id='aviso-politicas'><article><article></div>");
            $("#aviso-politicas article").load("/web/app/inventmx/politicas/politica-ambiental.php", function () {
                    inventMx.utilities.loaderHide();
                    setTimeout(inventMx.utilities.loaderHide, 7000);
                return this;
            });
        },
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
/* end view */

/* init routing */

/* end routing */