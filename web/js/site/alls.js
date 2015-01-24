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
            tag_url: null,
            created_start: null,
            created_finish: null,
            callback: null,
            not_ids: null,
            columnista_ids: null,
            sub_category_url: null
        }
    };
    
    inventMx.page.wrapper_site = $("#wrapper-page-site");
    inventMx.utilities.loaderShow = function () {
        $("#wrapper-loading-layout").css("display", "block");
    },
    inventMx.utilities.loaderHide = function () {
        $("#wrapper-loading-layout").css("display", "none");
    },
    inventMx.render.tplHomeTalentos = function(resp){
        if (resp) {
            dataVideos = resp.data;
            //dataVideos = data.slice(0, 15);
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
    },
    inventMx.render.tplPerfilTalentos = function(resp){
        if (resp.response.status == 200) {
            
            dataPerfil = resp.data[0];
            var perfilTalentos = $("#template-perfil-talento").html();
            var tpl_perfilTalentos = Handlebars.compile(perfilTalentos);
            var view_perfilTalentos = tpl_perfilTalentos(dataPerfil);
            $("#perfil-talento").html(view_perfilTalentos);
            
            if(resp.data.length){
                
                repo = "vloger.json";
                inventMx.dataSource.params.url = null;
                inventMx.dataSource.params.limit = "100"; 
                talentos = new inventMx.home.listPerfilTalentos(repo);
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
            console.log(dataSite);
            
            if(dataSite){
                var perfilSite = $("#template-perfil-site").html();
                var tpl_perfilSite = Handlebars.compile(perfilSite);
                var view_perfilSite = tpl_perfilSite(dataSite);
                $("#perfil-site").html(view_perfilSite);
                console.log(view_perfilSite)
            }else {
                error404 = new inventMx.home.default404();
            }
            
        }else {
            error404 = new inventMx.home.default404();
        }
        
        inventMx.utilities.loaderHide();
        setTimeout(inventMx.utilities.loaderHide, 7000);
        
    },
    inventMx.render.tplSites = function(resp){
        data = resp.data;
        
        if(data){
            var site = $("#template-sections-sites").html();
            var tpl_site = Handlebars.compile(site);
            var view_site = tpl_site(data);
            $("#sections-sites").html(view_site);
            
            /*if ($("img.lazy").length) {
                    $("img.lazy").lazyload({
                    effect: "fadeIn"
                });
            }*/
            var sites = "#sections-sites li.sections-sites";
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
                
            }else {
                $("#template-sections-case-exito").append("<p> Ha ocurrido un  error al cargar esta sección</p>")
            }
            
        }else{
            error404 = new inventMx.home.default404();
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
    inventMx.dataSource.load = function(repo,callback) {
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
        inventMx.dataSource.getAjax(url_ajax, params,callback);
        
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
        alert(data.text);
        idform = options.idform;
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
        transition = (transition) ? transition : 100;
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
        
        $("header .main-center").click(function(){
            if (devicewidth < 701) {
                $("header ul").slideToggle("fast");
            }else{
                $("header ul").css("display", "block");
            }
        });
        
        $(document).on("click",".ico-sumary-active",function(){
            $(this).parent().toggleClass("active");
        });
        
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
        
    });

})(window.inventMx = window.inventMx || {});