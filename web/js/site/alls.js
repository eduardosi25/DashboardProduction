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
    inventMx.animations = {},
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
    inventMx.utilities.validateImgStage = function(twidth, container, params) {
                if (twidth > 1024) {
                    //$("#wrapper-slider-home img.not-img")
                    container.each(function() {
                        var img = $(this);
                        var data_src = img.attr("data-src");
                        var newImg = params.r1920 + data_src;
                        img.attr("src", newImg);
                    });
                } else if (twidth >= 701 && twidth <= 1024) {
                    container.each(function() {
                        var img = $(this);
                        var data_src = img.attr("data-src");
                        var newImg = params.r1024 + data_src;
                        img.attr("src", newImg);
                    });
                } else if (twidth >= 401 && twidth <= 700) {
                    container.each(function() {
                        var img = $(this);
                        var data_src = img.attr("data-src");
                        var newImg = params.r700 + data_src;
                        img.attr("src", newImg);
                    });
                } else if (twidth <= 400) {
                    container.each(function() {
                        var img = $(this);
                        var data_src = img.attr("data-src");
                        var newImg = params.r400 + data_src;
                        img.attr("src", newImg);
                    });
                }
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
        
                /* init animation letter */
        //set animation timing
    var animationDelay = 2500,
        //loading bar effect
        barAnimationDelay = 3800,
        barWaiting = barAnimationDelay - 3000, //3000 is the duration of the transition on the loading bar - set in the scss/css file
        //letters effect
        lettersDelay = 50,
        //type effect
        typeLettersDelay = 150,
        selectionDuration = 500,
        typeAnimationDelay = selectionDuration + 800,
        //clip effect 
        revealDuration = 600,
        revealAnimationDelay = 1500;

    initHeadline();


    function initHeadline() {
        //insert <i> element for each letter of a changing word
        singleLetters($('.cd-headline.letters').find('b'));
        //initialise headline animation
        animateHeadline($('.cd-headline'));
    }

    function singleLetters($words) {
        $words.each(function () {
            var word = $(this),
                letters = word.text().split(''),
                selected = word.hasClass('is-visible');
            for (i in letters) {
                if (word.parents('.rotate-2').length > 0) letters[i] = '<em>' + letters[i] + '</em>';
                letters[i] = (selected) ? '<i class="in">' + letters[i] + '</i>' : '<i>' + letters[i] + '</i>';
            }
            var newLetters = letters.join('');
            word.html(newLetters);
        });
    }

    function animateHeadline($headlines) {
        var duration = animationDelay;
        $headlines.each(function () {
            var headline = $(this);

            if (headline.hasClass('loading-bar')) {
                duration = barAnimationDelay;
                setTimeout(function () {
                    headline.find('.cd-words-wrapper').addClass('is-loading')
                }, barWaiting);
            } else if (headline.hasClass('clip')) {
                var spanWrapper = headline.find('.cd-words-wrapper'),
                    newWidth = spanWrapper.width() + 10
                    spanWrapper.css('width', newWidth);
            } else if (!headline.hasClass('type')) {
                //assign to .cd-words-wrapper the width of its longest word
                var words = headline.find('.cd-words-wrapper b'),
                    width = 0;
                words.each(function () {
                    var wordWidth = $(this).width();
                    if (wordWidth > width) width = wordWidth;
                });
                headline.find('.cd-words-wrapper').css('width', width);
            };

            //trigger animation
            setTimeout(function () {
                hideWord(headline.find('.is-visible').eq(0))
            }, duration);
        });
    }

    function hideWord($word) {
        var nextWord = takeNext($word);

        if ($word.parents('.cd-headline').hasClass('type')) {
            var parentSpan = $word.parent('.cd-words-wrapper');
            parentSpan.addClass('selected').removeClass('waiting');
            setTimeout(function () {
                parentSpan.removeClass('selected');
                $word.removeClass('is-visible').addClass('is-hidden').children('i').removeClass('in').addClass('out');
            }, selectionDuration);
            setTimeout(function () {
                showWord(nextWord, typeLettersDelay)
            }, typeAnimationDelay);

        } else if ($word.parents('.cd-headline').hasClass('letters')) {
            var bool = ($word.children('i').length >= nextWord.children('i').length) ? true : false;
            hideLetter($word.find('i').eq(0), $word, bool, lettersDelay);
            showLetter(nextWord.find('i').eq(0), nextWord, bool, lettersDelay);

        } else if ($word.parents('.cd-headline').hasClass('clip')) {
            $word.parents('.cd-words-wrapper').animate({
                width: '2px'
            }, revealDuration, function () {
                switchWord($word, nextWord);
                showWord(nextWord);
            });

        } else if ($word.parents('.cd-headline').hasClass('loading-bar')) {
            $word.parents('.cd-words-wrapper').removeClass('is-loading');
            switchWord($word, nextWord);
            setTimeout(function () {
                hideWord(nextWord)
            }, barAnimationDelay);
            setTimeout(function () {
                $word.parents('.cd-words-wrapper').addClass('is-loading')
            }, barWaiting);

        } else {
            switchWord($word, nextWord);
            setTimeout(function () {
                hideWord(nextWord)
            }, animationDelay);
        }
    }

    function showWord($word, $duration) {
        if ($word.parents('.cd-headline').hasClass('type')) {
            showLetter($word.find('i').eq(0), $word, false, $duration);
            $word.addClass('is-visible').removeClass('is-hidden');

        } else if ($word.parents('.cd-headline').hasClass('clip')) {
            $word.parents('.cd-words-wrapper').animate({
                'width': $word.width() + 10
            }, revealDuration, function () {
                setTimeout(function () {
                    hideWord($word)
                }, revealAnimationDelay);
            });
        }
    }

    function hideLetter($letter, $word, $bool, $duration) {
        $letter.removeClass('in').addClass('out');

        if (!$letter.is(':last-child')) {
            setTimeout(function () {
                hideLetter($letter.next(), $word, $bool, $duration);
            }, $duration);
        } else if ($bool) {
            setTimeout(function () {
                hideWord(takeNext($word))
            }, animationDelay);
        }

        if ($letter.is(':last-child') && $('html').hasClass('no-csstransitions')) {
            var nextWord = takeNext($word);
            switchWord($word, nextWord);
        }
    }

    function showLetter($letter, $word, $bool, $duration) {
        $letter.addClass('in').removeClass('out');

        if (!$letter.is(':last-child')) {
            setTimeout(function () {
                showLetter($letter.next(), $word, $bool, $duration);
            }, $duration);
        } else {
            if ($word.parents('.cd-headline').hasClass('type')) {
                setTimeout(function () {
                    $word.parents('.cd-words-wrapper').addClass('waiting');
                }, 200);
            }
            if (!$bool) {
                setTimeout(function () {
                    hideWord($word)
                }, animationDelay)
            }
        }
    }

    function takeNext($word) {
        return (!$word.is(':last-child')) ? $word.next() : $word.parent().children().eq(0);
    }

    function takePrev($word) {
        return (!$word.is(':first-child')) ? $word.prev() : $word.parent().children().last();
    }

    function switchWord($oldWord, $newWord) {
        $oldWord.removeClass('is-visible').addClass('is-hidden');
        $newWord.removeClass('is-hidden').addClass('is-visible');
    }
        /* end animation letter */        
        
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
