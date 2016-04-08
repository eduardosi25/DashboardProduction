$(function() {
    var id_exclude;

    /* eventos */
    var inventMx_events = {};
    IMxevents = _.extend(inventMx_events, Backbone.Events);

    // Con la funcion bind podemos enlazar un evento cualquiera con una
    // función callback que se ejecutará cuando este evento ocurra en este objeto
    inventMx_events.bind("NoData", function(msg) {
        alert('No hay  más dato en ' + msg);
    });

    inventMx_events.bind("Inventform", function(idform, data) {
        validate = $(idform).validationEngine('validate');
        //options = {idform: idform};
        if (validate) {
            var url = "/web/app/inventmx/global/sendmail.php";
            Backbone.ajax({
                url: url,
                data: data,
                dataType: 'json',
                type: 'GET',
                contentType: "application/json; charset=utf-8",
                async: false,
                success: function(nodes) {
                    /*respond: true, text: "El correo se ha enviado satisfactoriamente."*/
                    if (nodes) {
                        alert(nodes.text);
                        $(idform + " :input[type='text'], " + idform + " :input[type='email'], " + idform + " textarea").val("");
                    } else {
                        console.log("Hubo un  error al procesar la petición");
                    }
                },
                error: function(request, status, error) {
                    alert("Hubo un error inesperado, intenta nuevamente por favor");
                }
            });
        } else {
            console.log("No validate");
        }
    });


    /* colecciones */
    var collectionsMain = Backbone.Collection.extend({
        //model: modelMain,
        //url: "/",
        initialize: function() {
        },
        animations: function(section) {
            $("#wrapper-page div[id^='page-main-invent-']").each(function() {
                $(this).hide().animate({'margin-left': "100%"});
                $(this).show().animate({'margin-left': "0"});
                ;
                //$("#wrapper-page #page-main-invent-" + section).show();
            });
        },
        template: function(idTemplate, appendTo, data, callback) {

            if ($(idTemplate).length && $(appendTo).length && data.length) {
                var tpl = $(idTemplate).html();
                var section = Handlebars.compile(tpl);
                var items = section(data);
                $(appendTo).html(items);
                if (typeof callback == "function") {
                    callback();
                }
            } else {
                console.log("Es posible que no exista algún parametro enviado, los datos recibidos para el template son:");
                console.log("template: " + idTemplate);
                console.log("append: " + appendTo);
                console.log("data:");
                console.log(data);
            }
        },
        assembleUrl: function(idTemplate, appendTo, renderTemplate, callback, forward, pathUrl) {
            var baseUrl = collectionMain.get("c1").attributes.baseUrl;
            var apiKey = collectionMain.get("c1").attributes.apiKey;
            var repositorio = collectionMain.get("c1").attributes.repositorio;
            var mainParams = collectionMain.get("c2").attributes;

            var params = {};
            $.each(mainParams, function(i, j) {
                if (j) {
                    params[i] = j;
                }
            });
            var url = baseUrl + "/" + repositorio + "/" + apiKey + "?callback=?";
            this.getAjax(idTemplate, appendTo, renderTemplate, url, params, callback, forward, pathUrl);
        },
        getAjax: function(idTemplate, appendTo, renderTemplate, url, params, callback, forward, pathUrl) {
            Backbone.ajax({
                //dataType: "jsonp",
                url: url,
                data: params,
                dataType: 'json',
                type: 'GET',
                contentType: "application/json; charset=utf-8",
                async: true,
                success: function(nodes) {
                    if (nodes.response.status == "200" && nodes.data.length) {
                        if (typeof renderTemplate == "function") {
                            var data = nodes.data;
                            renderTemplate(idTemplate, appendTo, data, callback)
                        }
                    } else if (nodes.response.status == "200" && !nodes.data.length) {
                        if (typeof forward == "function") {
                            new forward(pathUrl);
                        } else {
                            console.log("No hay datos.");
                        }

                    } else {
                        return console.log("Status: " + nodes.response.status);
                    }
                    //return console.log(nodes);
                },
                error: function(request, status, error) {
                    alert("Hubo un error inesperado, intenta nuevamente por favor");
                }
            });
        },
        topOffset: function(position, delay, transition, callback) {
            delay = (delay) ? delay : 0;
            transition = (transition) ? transition : 500;
            $('body,html').delay(delay).animate({
                scrollTop: position
            }, transition, function() {
                if (typeof callback == "function") {
                    callback();
                }
            });
        },
        loaderShow: function() {
            $("#wrapper-loading-layout").show();
        },
        loaderHide: function() {
            $("#wrapper-loading-layout").hide();
        },
        hideSections: function(section) {
            $("#wrapper-page div[id^='page-main-invent-']").each(function() {
                $(this).hide();
                $("#wrapper-page #page-main-invent-" + section).show();
            });
        }
    });

    var collectionMain = new collectionsMain();
    collectionMain.add({
        baseUrl: "http://api.inventmx.com/v1/inventmx",
        apiKey: "3a5877fc16b6fcbf8eedbe55d091938a",
        repositorio: "sites.json",
        section: "home"
    });
    collectionMain.add({
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
    });
    collectionMain.add({
        pathTemplate: "/web/app/inventmx/",
        firtsIdContent: "#page-main-invent-",
    });

    //collectionMain.assembleUrl(collectionMain.template);
    /* modelos */
    inventMx.models = {};
    //inventMx.models.forward = Backbone.Model.extend({
    modelsHome = Backbone.Model.extend({
        initialize: function(param) {
            this.section(param);
            console.log("1");
        },
        section: function(param) {
            console.log("2");
        }
    });

    inventMx.view = {};
    inventMx.render = {};
    /* home */
    inventMx.view.home = Backbone.View.extend({
        //el: inventMx.page.wrapper_site,
        template: collectionMain.get("c3").attributes.pathTemplate,
        //idContent: collectionMain.get("c3").attributes.firtsIdContent,
        Model: modelsHome,
        initialize: function() {
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
        render: function() {
            //this.loadPage();
        },
        el: collectionMain.get("c3").attributes.firtsIdContent + "home",
        loadPage: function() {
            //console.log(this.model);
            var $el = this.$el;
            //var idContent = this.idContent;
            var section = "home";

            $.get(this.template + 'home/home.html', function(data) {
                if ($el.children("div").length == 0) {
                    //$(idContent + "home").html(data);
                    $el.html(data);
                } else {
                    console.log("cache");
                }
                collectionMain.hideSections(section);

                /* la red invent */
                var idAncla = window.location.href.split("#")[1];
                if (idAncla) {
                    if ($("[data-section='" + idAncla + "']").length) {
                        collectionMain.loaderShow();
                        function top() {
                            var offset1 = $("[data-section='" + idAncla + "']").offset();
                            var offset = offset1.top;
                            var delay = 10;
                            //position,delay,transition,callback
                            collectionMain.topOffset(offset, delay, 0, collectionMain.loaderHide);
                        }
                        setTimeout(top, 1000);
                    } else {
                        console.log("no valido");
                    }
                }


                repositorio = collectionMain.get("c1");
                repositorio.set({repositorio: "sites.json", section: "home"});

                params = collectionMain.get("c2");
                /* se pasan los campos del API */
                params.set({fields: "id|title|url|summary|images"});
                params.set({limit: "30", not_ids: null});

                /* renderTemplate: render generico, esto se puede copiar modificar nada */
                var renderTemplate = collectionMain.template;

                /* idTemplate: id del Template de javascript */
                var idTemplate = "#template-sections-sites";
                /* appendTo: lugar donde se pondra el template ya rendereado */
                var appendTo = "#sections-sites";
                /* callback: debe ser una función para poder ejecutarse */
                var callback = function() {
                    params.set({fields: null});

                    $w = $(window).width();
                    if ($w >= 728) {
                        $('.flexslider_marcas').flexslider({
                            animation: "slide",
                            animationLoop: true,
                            slideshowSpeed: 4000,
                            animationSpeed: 2000,
                            controlNav: false,
                            directionNav: true,
                        });
                    }
                    else {

                    }
                    $('.slides li a').click(function() {
                        id_exclude = $(this).attr('data-id');
                    });
                    $(".btn-contacto .anunciate").click(function() {
                        $(this).addClass("active");
                        $(".contact_form").fadeOut();
                        $(".contact_form_anunciate").fadein();

                    });
                    $(".btn-contacto .anunciate").click(function() {
                        $(this).addClass("active");
                        $(".contact_form").fadeOut();
                        $(".contact_form_afilate").fadein();
                    });

                };

                /* forward: instancia de la vista a renderear*/
                var forward = null;

                /* Se hace la petición y  se pasan lo parámetros antes nombrados */
                collectionMain.assembleUrl(idTemplate, appendTo, renderTemplate, callback, forward);

                repositorio.set({repositorio: "vloger.json"});

                params.set({fields: "id|title|url|audience|images|followers"});
                params.set({limit: "90"});
                idTemplate = "#template-sections-vloggers";
                /* appendTo: lugar donde se pondra el template ya rendereado */
                appendTo = "#sections-vloggers";
                /* callback: debe ser una función para poder ejecutarse */
                callback = function() {
                    params.set({fields: null});

                    $('.center').slick({
                        dots: true,
                        infinite: true,
                        speed: 3000,
                        slidesToShow: 3,
                        slidesToScroll: 3,
                        responsive: [
                            {
                                breakpoint: 1024,
                                settings: {
                                    slidesToShow: 3,
                                    slidesToScroll: 3,
                                    infinite: true,
                                    dots: true
                                }
                            },
                            {
                                breakpoint: 600,
                                settings: {
                                    slidesToShow: 3,
                                    slidesToScroll: 3
                                }
                            },
                            {
                                breakpoint: 480,
                                settings: {
                                    slidesToShow: 2,
                                    slidesToScroll: 2
                                }
                            }
                            // You can unslick at a given breakpoint now by adding:
                            // settings: "unslick"
                            // instead of a settings object
                        ]
                    });
                    $('.slick-slide .content-blogger a').click(function() {
                        id_exclude = $(this).attr('data-id');

                    });


                };
                /* forward: instancia de la vista a renderear*/
                var forward = null;

                /* Se hace la petición y  se pasan lo parámetros antes nombrados */
                collectionMain.assembleUrl(idTemplate, appendTo, renderTemplate, callback, forward);

                $('.flexslider').flexslider({
                    animation: "slide",
                    animationLoop: true,
                    slideshowSpeed: 4000,
                    animationSpeed: 2000,
                    controlNav: true,
                    directionNav: false,
                });

                $('#demo-pie-1').pieChart({
                    barColor: '#17d9b4',
                    trackColor: '#a03d73',
                    lineCap: 'square',
                    lineWidth: 24,
                    size: 158,
                    rotate: -110,
                    animate: {
                        duration: 3000,
                        enabled: true
                    },
                    onStep: function(from, to, percent) {
                        $(this.element).find('.pie-value').text(Math.round(percent * 10) / 10 + '%');
                    }
                });
                $('#demo-pie-2').pieChart({
                    barColor: '#17d9b4',
                    trackColor: '#a03d73',
                    lineCap: 'square',
                    lineWidth: 24,
                    size: 158,
                    rotate: -110,
                    animate: {
                        duration: 3000,
                        enabled: true
                    },
                    onStep: function(from, to, percent) {
                        $(this.element).find('.pie-value').text(Math.round(percent * 10) / 10 + '%');
                    }
                });
                $('#demo-pie-3').pieChart({
                    barColor: '#17d9b4',
                    trackColor: '#a03d73',
                    lineCap: 'square',
                    lineWidth: 24,
                    size: 158,
                    rotate: -110,
                    animate: {
                        duration: 2000,
                        enabled: true
                    },
                    onStep: function(from, to, percent) {
                        $(this.element).find('.pie-value').text(Math.round(percent) + '%');
                    }
                });
                $('#demo-pie-4').pieChart({
                    barColor: '#17d9b4',
                    trackColor: '#a03d73',
                    lineCap: 'square',
                    lineWidth: 24,
                    size: 158,
                    rotate: -110,
                    animate: {
                        duration: 2000,
                        enabled: true
                    },
                    onStep: function(from, to, percent) {
                        $(this.element).find('.pie-value').text(Math.round(percent * 10) / 10 + '%');
                    }
                });
                $('#demo-pie-5').pieChart({
                    barColor: '#17d9b4',
                    trackColor: '#a03d73',
                    lineCap: 'square',
                    lineWidth: 24,
                    size: 158,
                    rotate: -110,
                    animate: {
                        duration: 2000,
                        enabled: true
                    },
                    onStep: function(from, to, percent) {
                        $(this.element).find('.pie-value').text(Math.round(percent * 10) / 10 + '%');
                    }
                });
                $('#demo-pie-6').pieChart({
                    barColor: '#17d9b4',
                    trackColor: '#a03d73',
                    lineCap: 'square',
                    lineWidth: 24,
                    size: 158,
                    rotate: -110,
                    onStep: function(from, to, percent) {
                        $(this.element).find('.pie-value').text(Math.round(percent * 10) / 10 + '%');
                    }
                });
                $('#demo-pie-7').pieChart({
                    barColor: '#17d9b4',
                    trackColor: '#a03d73',
                    lineCap: 'square',
                    lineWidth: 24,
                    size: 158,
                    rotate: -110,
                    onStep: function(from, to, percent) {
                        $(this.element).find('.pie-value').text(Math.round(percent * 10) / 10 + '%');
                    }
                });
                $('#demo-pie-8').pieChart({
                    barColor: '#17d9b4',
                    trackColor: '#449cce',
                    lineCap: 'square',
                    lineWidth: 24,
                    size: 158,
                    rotate: -110,
                    animate: {
                        duration: 3000,
                        enabled: true
                    },
                    onStep: function(from, to, percent) {
                        $(this.element).find('.pie-value').text(Math.round(percent * 10) / 10 + '%');
                    }
                });
                $('#demo-pie-9').pieChart({
                    barColor: '#17d9b4',
                    trackColor: '#449cce',
                    lineCap: 'square',
                    lineWidth: 24,
                    size: 158,
                    rotate: -110,
                    animate: {
                        duration: 3000,
                        enabled: true
                    },
                    onStep: function(from, to, percent) {
                        $(this.element).find('.pie-value').text(Math.round(percent * 10) / 10 + '%');
                    }
                });

                $("#audiencias .wrapper .content-audiencias > div").on({
                    mouseenter: function(e) {
                        //e.preventDefault();
                        e.stopPropagation();
                        //var href = $(this).attr("href");
                        $(this).addClass("gif-active");
                        var img = $(this).find("img");
                        var src = $(this).find("img").attr("src");
                        src = src.replace(/png/g, "gif");
                        img.attr("src", src);
                        //console.log("Mouse Over!");
                    },
                    mouseleave: function(e) {
                        //e.preventDefault();
                        e.stopPropagation();
                        //var href = $(this).attr("href");
                        $(this).removeClass("gif-active");
                        var img = $(this).find("img");
                        var src = $(this).find("img").attr("src");
                        src = src.replace(/gif/g, "png");
                        img.attr("src", src);
                        //console.log("Mouse Out!");
                    }
                });
                $('#marketing .wrapper').css({'opacity': "0", 'top': '200px'});
                $("html, body").animate({scrollTop: 0}, "slow");
                $('#marketing .wrapper').css({'opacity': "0", 'top': '200px'});
                $('.contact-form').css({'opacity': "0", 'top': '200px'});
                $(".btn-contacto .anunciate").click(function() {
                    $(".btn-contacto contcato").removeClass("active");
                    $(this).addClass("active");
                    $(".contact_form").fadeOut();
                    $(".contact_form.contact_form_anunciate").fadeIn();

                });
                $(".btn-contacto .afíliate").click(function() {
                    $(".btn-contacto contcato").removeClass("active");
                    $(this).addClass("active");
                    $(".contact_form").fadeOut();
                    $(".contact_form.contact_form_afilate").fadeIn();
                });

            }, 'html');

            return this;
        },
        acordeon: function(e) {
            e.preventDefault();
        },
        events: {
            "click #home-accordion h2": "acordeon",
        },
    }),
            /*inventMx.view.redInvent = Backbone.View.extend({
             template: collectionMain.get("c3").attributes.pathTemplate,
             idContent: collectionMain.get("c3").attributes.firtsIdContent,
             initialize: function() {
             $(this.el).unbind();
             _.bindAll(this, 'render');
             this.render();
             },
             render: function() {
             var idContent = this.idContent;
             var section = "redInvent";
             $.get(this.template + 'redInvent/redInvent.html', function(data) {
             var repositorio = collectionMain.get("c1");
             repositorio.set({section: section});
             
             if ($(idContent + "redInvent").children("div").length == 0) {
             $(idContent + "redInvent").html(data);
             }
             collectionMain.hideSections(section);
             $('#marketing .wrapper').css({'opacity': "0", 'top': '200px'});
             $('.contact-form').css({'opacity': "0", 'top': '200px'});
             }, 'html');
             return this;
             }
             }),*/
            inventMx.view.servicios = Backbone.View.extend({
                template: collectionMain.get("c3").attributes.pathTemplate,
                idContent: collectionMain.get("c3").attributes.firtsIdContent,
                initialize: function() {
                    $(this.el).unbind();
                    _.bindAll(this, 'render');
                    this.render();
                },
                render: function() {
                    var idContent = this.idContent;
                    var section = "servicios";
                    $.get(this.template + 'servicios/servicios.html', function(data) {
                        var repositorio = collectionMain.get("c1");
                        repositorio.set({section: section});

                        if ($(idContent + "servicios").children("div").length == 0) {
                            $(idContent + "servicios").html(data);
                        }
                        /*var urlHash = window.location.href.split("#")[1];
                         if (urlHash && $('#' + urlHash).length)
                         $('html,body').animate({
                         scrollTop: $('#' + urlHash).offset().top
                         }, 1500);*/

                        collectionMain.hideSections(section);

                        $("html, body").animate({scrollTop: 0}, "slow");
                        /* $('.content-marketing').swift({'type': 'dom', 'positionStart': 'bottom', 'length': '100'});*/
                        /*$('.content-marketing').swift({'type': 'dom', 'positionStart': 'right', 'length': '100', 'axis': 'right'});*/
                        $('#marketing .wrapper').css({'opacity': "1", 'top': '0'});
                        $('.contact-form').css({'opacity': "0", 'top': '200px'});

                        $('.content-codiga .item.right.i2').swift({'type': 'dom', 'positionStart': 'right', 'length': '700', 'axis': 'left', 'delay': '50'});
                        $('.content-codiga .item.i1').swift({'type': 'dom', 'positionStart': 'left', 'length': '700', 'axis': 'left', 'delay': '50'});
                        $('.content-codiga .item.i3').swift({'type': 'dom', 'positionStart': 'left', 'length': '1500', 'axis': 'left', 'delay': '50'});
                        $('.content-codiga .item.right.i4').swift({'type': 'dom', 'positionStart': 'right', 'length': '2000', 'axis': 'left', 'delay': '50'});

                        $('.content-ads .item').swift({'type': 'dom', 'positionStart': 'left', 'length': '3200', 'axis': 'left', 'delay': '50'});
                        $('.content-ads .item.right').swift({'type': 'dom', 'positionStart': 'right', 'length': '3600', 'axis': 'left', 'delay': '50'});
                        $('.content-ads .item.video').swift({'type': 'dom', 'positionStart': 'left', 'length': '3800', 'axis': 'left', 'delay': '50'});

                        /* servicios - content - netword-ads - media*/
                        var idAncla = window.location.href.split("#")[1];
                        if (idAncla) {
                            if ($("[data-section='" + idAncla + "']").length) {
                                collectionMain.loaderShow();
                                function top() {
                                    var offset1 = $("[data-section='" + idAncla + "']").offset();
                                    var offset = offset1.top;
                                    var delay = 10;
                                    //position,delay,transition,callback
                                    collectionMain.topOffset(offset, delay, 0, collectionMain.loaderHide);
                                }
                                setTimeout(top, 1000);
                            } else {
                                console.log("no valido");
                            }
                        }


                        $(".btn-contacto .anunciate").click(function() {
                            $(".btn-contacto contcato").removeClass("active");
                            $(this).addClass("active");
                            $(".contact_form").fadeOut();
                            $(".contact_form.contact_form_anunciate").fadeIn();

                        });
                        $(".btn-contacto .afíliate").click(function() {
                            $(".btn-contacto contcato").removeClass("active");
                            $(this).addClass("active");
                            $(".contact_form").fadeOut();
                            $(".contact_form.contact_form_afilate").fadeIn();
                        });


                        jQuery(".contact_form").validationEngine('attach', {
                            promptPosition: "bottomLeft"
                        });

                        $(document).on("submit", ".contact_form", function(e) {
                            e.preventDefault();
                            data = $(this).serializeArray();
                            inventMx_events.trigger('Inventform', '.contact_form', data);
                            return false;
                        });

                    }, 'html');
                    return this;
                }

            }),
            inventMx.view.perfilSitio = Backbone.View.extend({
                template: collectionMain.get("c3").attributes.pathTemplate,
                idContent: collectionMain.get("c3").attributes.firtsIdContent,
                initialize: function(site) {
                    $(this.el).unbind();
                    _.bindAll(this, 'render');
                    this.render(site);
                },
                render: function(site) {
                    var idContent = this.idContent;
                    var section = "perfilSitio";
                    $.get(this.template + 'perfilSitio/perfilSitio.html', function(data) {

                        $(idContent + "perfilSitio").html(data);
                        collectionMain.hideSections(section);

                        repositorio = collectionMain.get("c1");
                        repositorio.set({repositorio: "sites.json", section: section});

                        params = collectionMain.get("c2");
                        /* se pasan los campos del API */
                        params.set({url: site, limit: 1, not_ids: null});


                        /* renderTemplate: render generico, esto se puede copiar modificar nada */
                        var renderTemplate = collectionMain.template;

                        /* idTemplate: id del Template de javascript */
                        var idTemplate = "#template-sections-perfil";
                        /* appendTo: lugar donde se pondra el template ya rendereado */
                        var appendTo = "#sections-sites-perfil";
                        /* callback: debe ser una función para poder ejecutarse */
                        var callback = function() {

                            params.set({fields: null});

                            $('#demo-pie-12').pieChart({
                                barColor: '#17d9b4',
                                trackColor: '#a03d73',
                                lineCap: 'square',
                                lineWidth: 24,
                                size: 158,
                                rotate: -110,
                                animate: {
                                    duration: 3000,
                                    enabled: true
                                },
                                onStep: function(from, to, percent) {
                                    $(this.element).find('.pie-value').text(Math.round(percent * 10) / 10 + '%');
                                }
                            });
                            $('#demo-pie-13').pieChart({
                                barColor: '#17d9b4',
                                trackColor: '#a03d73',
                                lineCap: 'square',
                                lineWidth: 24,
                                size: 158,
                                rotate: -110,
                                animate: {
                                    duration: 3000,
                                    enabled: true
                                },
                                onStep: function(from, to, percent) {
                                    $(this.element).find('.pie-value').text(Math.round(percent * 10) / 10 + '%');
                                }
                            });




                        };

                        /* forward: instancia de la vista a renderear*/
                        var forward = inventMx.view.perfilTalento;
                        /* pathUrl: si se hace uso de un forward se debe de mandar la url en question
                         * en este caso site*/
                        var pathUrl = site;


                        /* Se hace la petición y  se pasan lo parámetros antes nombrados */
                        collectionMain.assembleUrl(idTemplate, appendTo, renderTemplate, callback, forward, pathUrl);


                        var callback2 = function() {
                            params.set({fields: null});
                            $('.center-sites').slick({
                                dots: true,
                                infinite: true,
                                speed: 3000,
                                slidesToShow: 3,
                                slidesToScroll: 3,
                                responsive: [
                                    {
                                        breakpoint: 1024,
                                        settings: {
                                            slidesToShow: 3,
                                            slidesToScroll: 3,
                                            infinite: true,
                                            dots: true
                                        }
                                    },
                                    {
                                        breakpoint: 600,
                                        settings: {
                                            slidesToShow: 3,
                                            slidesToScroll: 3
                                        }
                                    },
                                    {
                                        breakpoint: 480,
                                        settings: {
                                            slidesToShow: 2,
                                            slidesToScroll: 2
                                        }
                                    }
                                    // You can unslick at a given breakpoint now by adding:
                                    // settings: "unslick"
                                    // instead of a settings object
                                ]
                            });
                            $('.slick-slide > div a').click(function() {
                                id_exclude = $(this).attr('data-id');

                            });

                        };
                        repositorio = collectionMain.get("c1");
                        repositorio.set({repositorio: "sites.json"});
                        params = collectionMain.get("c2");
                        params.set({url: null, not_ids: id_exclude, limit: 50});
                        /* idTemplate: id del Template de javascript */
                        var idTemplate1 = "#template-sections-carousel-sites";
                        /* appendTo: lugar donde se pondra el template ya rendereado */
                        var appendTo1 = "#sections-carousel-sites";
                        collectionMain.assembleUrl(idTemplate1, appendTo1, renderTemplate, callback2, forward, pathUrl);
                        $("html, body").animate({scrollTop: 0}, "slow");
                        $('#marketing .wrapper').css({'opacity': "0", 'top': '200px'});
                        $('.contact-form').css({'opacity': "0", 'top': '200px'});
                        $(".btn-contacto .anunciate").click(function() {
                            $(".btn-contacto contcato").removeClass("active");
                            $(this).addClass("active");
                            $(".contact_form").fadeOut();
                            $(".contact_form.contact_form_anunciate").fadeIn();

                        });
                        $(".btn-contacto .afíliate").click(function() {
                            $(".btn-contacto contcato").removeClass("active");
                            $(this).addClass("active");
                            $(".contact_form").fadeOut();
                            $(".contact_form.contact_form_afilate").fadeIn();
                        });

                    }, 'html');
                    return this;
                }
            }),
            inventMx.view.perfilTalento = Backbone.View.extend({
                template: collectionMain.get("c3").attributes.pathTemplate,
                idContent: collectionMain.get("c3").attributes.firtsIdContent,
                initialize: function(perfil) {
                    $(this.el).unbind();
                    _.bindAll(this, 'render');
                    this.render(perfil);
                },
                render: function(perfil) {
                    var idContent = this.idContent;
                    var section = "perfilTalento";
                    $.get(this.template + 'perfilTalento/perfilTalento.html', function(data) {
                        $(idContent + "perfilTalento").html(data);
                        collectionMain.hideSections(section);

                        repositorio = collectionMain.get("c1");
                        repositorio.set({repositorio: "vloger.json", section: section});

                        params = collectionMain.get("c2");
                        /* se pasan los campos del API */
                        params.set({url: perfil, limit: 1, not_ids: null});

                        /* renderTemplate: render generico, esto se puede copiar modificar nada */
                        var renderTemplate = collectionMain.template;

                        /* idTemplate: id del Template de javascript */
                        var idTemplate = "#template-sections-vlogger";
                        /* appendTo: lugar donde se pondra el template ya rendereado */
                        var appendTo = "#sections-vlogger";
                        /* callback: debe ser una función para poder ejecutarse */
                        var callback = function() {
                            params.set({fields: null});

                            $('#demo-pie-8').pieChart({
                                barColor: '#17d9b4',
                                trackColor: '#449cce',
                                lineCap: 'square',
                                lineWidth: 24,
                                size: 158,
                                rotate: -110,
                                animate: {
                                    duration: 3000,
                                    enabled: true
                                },
                                onStep: function(from, to, percent) {
                                    $(this.element).find('.pie-value').text(Math.round(percent * 10) / 10 + '%');
                                }
                            });
                            $('#demo-pie-9').pieChart({
                                barColor: '#17d9b4',
                                trackColor: '#449cce',
                                lineCap: 'square',
                                lineWidth: 24,
                                size: 158,
                                rotate: -110,
                                animate: {
                                    duration: 3000,
                                    enabled: true
                                },
                                onStep: function(from, to, percent) {
                                    $(this.element).find('.pie-value').text(Math.round(percent * 10) / 10 + '%');
                                }
                            });

                            $('.slick-slide .content-blogger a').click(function() {
                                id_exclude = $(this).attr('data-id');

                            });



                        };
                        /* forward: instancia de la vista a renderear*/
                        var forward = inventMx.view.casoExito;
                        /* pathUrl: si se hace uso de un forward se debe de mandar la url en question
                         * en este caso perfil*/
                        var pathUrl = perfil;

                        /* Se hace la petición y  se pasan lo parámetros antes nombrados */
                        collectionMain.assembleUrl(idTemplate, appendTo, renderTemplate, callback, forward, pathUrl);
                        callback = function() {
                            params.set({fields: null});
                            $('.vlogger').slick({
                                dots: true,
                                infinite: true,
                                speed: 3000,
                                slidesToShow: 3,
                                slidesToScroll: 3,
                                responsive: [
                                    {
                                        breakpoint: 1024,
                                        settings: {
                                            slidesToShow: 3,
                                            slidesToScroll: 3,
                                            infinite: true,
                                            dots: true
                                        }
                                    },
                                    {
                                        breakpoint: 600,
                                        settings: {
                                            slidesToShow: 3,
                                            slidesToScroll: 3
                                        }
                                    },
                                    {
                                        breakpoint: 480,
                                        settings: {
                                            slidesToShow: 2,
                                            slidesToScroll: 2
                                        }
                                    }
                                    // You can unslick at a given breakpoint now by adding:
                                    // settings: "unslick"
                                    // instead of a settings object
                                ]
                            });

                        };
                        repositorio = collectionMain.get("c1");
                        repositorio.set({repositorio: "vloger.json"});
                        params = collectionMain.get("c2");
                        params.set({url: null, not_ids: id_exclude, limit: 50});
                        /* idTemplate: id del Template de javascript */
                        var idTemplate = "#template-carousel-sections-vloggers";
                        /* appendTo: lugar donde se pondra el template ya rendereado */
                        var appendTo = "#sections-carousel-influencers";
                        collectionMain.assembleUrl(idTemplate, appendTo, renderTemplate, callback, forward, pathUrl);

                        $("html, body").animate({scrollTop: 0}, "slow");
                        $('#marketing .wrapper').css({'opacity': "0", 'top': '200px'});
                        $('.contact-form').css({'opacity': "0", 'top': '200px'});

                        $(".btn-contacto .anunciate").click(function() {
                            $(".btn-contacto contcato").removeClass("active");
                            $(this).addClass("active");
                            $(".contact_form").fadeOut();
                            $(".contact_form.contact_form_anunciate").fadeIn();

                        });
                        $(".btn-contacto .afíliate").click(function() {
                            $(".btn-contacto contcato").removeClass("active");
                            $(this).addClass("active");
                            $(".contact_form").fadeOut();
                            $(".contact_form.contact_form_afilate").fadeIn();
                        });

                    }, 'html');
                    return this;
                }
            }),
            inventMx.view.casoExito = Backbone.View.extend({
                template: collectionMain.get("c3").attributes.pathTemplate,
                idContent: collectionMain.get("c3").attributes.firtsIdContent,
                initialize: function(casoexito) {
                    $(this.el).unbind();
                    _.bindAll(this, 'render');
                    this.render(casoexito);
                },
                render: function(casoexito) {
                    var idContent = this.idContent;
                    var section = "casoExito";
                    $.get(this.template + 'caso-de-exito/caso-de-exito.html', function(data) {
                        var animateSection = collectionMain.get("c1");
                        animateSection.set({section: section});

                        if ($(idContent + "casoExito").children("div").length == 0) {
                            $(idContent + "casoExito").html(data);
                            collectionMain.hideSections(section);

                            repositorio = collectionMain.get("c1");
                            repositorio.set({repositorio: "case.json"});

                            params = collectionMain.get("c2");
                            /* se pasan los campos del API */
                            params.set({url: casoexito, limit: 1});

                            /* renderTemplate: render generico, esto se puede copiar modificar nada */
                            var renderTemplate = collectionMain.template;

                            /* idTemplate: id del Template de javascript */
                            var idTemplate = "#template-sections-sites";
                            /* appendTo: lugar donde se pondra el template ya rendereado */
                            var appendTo = "#sections-sites";
                            /* callback: debe ser una función para poder ejecutarse */
                            var callback = null;
                            /* forward: instancia de la vista a renderear*/
                            var forward = inventMx.view.blogsNota;
                            /* pathUrl: si se hace uso de un forward se debe de mandar la url en question
                             * en este caso perfil*/
                            var pathUrl = casoexito;

                            /* Se hace la petición y  se pasan lo parámetros antes nombrados */
                            collectionMain.assembleUrl(idTemplate, appendTo, renderTemplate, callback, forward, pathUrl);


                        }

                        $("html, body").animate({scrollTop: 0}, "slow");
                        $('#marketing .wrapper').css({'opacity': "0", 'top': '200px'});
                        $('.contact-form').css({'opacity': "0", 'top': '200px'});
                        $(".btn-contacto .anunciate").click(function() {
                            $(".btn-contacto contcato").removeClass("active");
                            $(this).addClass("active");
                            $(".contact_form").fadeOut();
                            $(".contact_form.contact_form_anunciate").fadeIn();

                        });
                        $(".btn-contacto .afíliate").click(function() {
                            $(".btn-contacto contcato").removeClass("active");
                            $(this).addClass("active");
                            $(".contact_form").fadeOut();
                            $(".contact_form.contact_form_afilate").fadeIn();
                        });


                    }, 'html');
                    return this;
                }
            }),
            inventMx.view.blogs = Backbone.View.extend({
                template: collectionMain.get("c3").attributes.pathTemplate,
                idContent: collectionMain.get("c3").attributes.firtsIdContent,
                initialize: function() {
                    $(this.el).unbind();
                    _.bindAll(this, 'render');
                    this.render();
                },
                render: function() {
                    var idContent = this.idContent;
                    var section = "blogs";
                    $.get(this.template + 'blogs/blogs.html', function(data) {
                        var animateSection = collectionMain.get("c1");
                        animateSection.set({section: section});

                        if ($(idContent + "blogs").children("div").length == 0) {
                            $(idContent + "blogs").html(data);
                        }
                        $("html, body").animate({scrollTop: 0}, "slow");
                        $('#marketing .wrapper').css({'opacity': "0", 'top': '200px'});
                        $('.contact-form').css({'opacity': "0", 'top': '200px'});

                        collectionMain.hideSections(section);
                    }, 'html');
                    return this;
                }

            }),
            inventMx.view.blogsNota = Backbone.View.extend({
                template: collectionMain.get("c3").attributes.pathTemplate,
                idContent: collectionMain.get("c3").attributes.firtsIdContent,
                initialize: function(blogsUrl) {
                    $(this.el).unbind();
                    _.bindAll(this, 'render');
                    this.render(blogsUrl);
                },
                render: function(blogsUrl) {
                    var idContent = this.idContent;
                    var section = "blogsNota";
                    $.get(this.template + 'blogs/blogsNota.html', function(data) {
                        var animateSection = collectionMain.get("c1");
                        animateSection.set({section: section});

                        $(idContent + "blogsNota").html(data);
                        collectionMain.hideSections(section);

                        repositorio = collectionMain.get("c1");
                        repositorio.set({repositorio: "blogs.json"});

                        params = collectionMain.get("c2");
                        /* se pasan los campos del API */
                        params.set({url: blogsUrl, limit: 1});

                        /* renderTemplate: render generico, esto se puede copiar modificar nada */
                        var renderTemplate = collectionMain.template;

                        /* idTemplate: id del Template de javascript */
                        var idTemplate = "#template-sections-sites";
                        /* appendTo: lugar donde se pondra el template ya rendereado */
                        var appendTo = "#sections-sites";
                        /* callback: debe ser una función para poder ejecutarse */
                        var callback = null;
                        /* forward: instancia de la vista a renderear*/
                        var forward = inventMx.view.default404;
                        /* pathUrl: si se hace uso de un forward se debe de mandar la url en question
                         * en este caso perfil*/
                        var pathUrl = blogsUrl;

                        /* Se hace la petición y  se pasan lo parámetros antes nombrados */
                        collectionMain.assembleUrl(idTemplate, appendTo, renderTemplate, callback, forward, pathUrl);
                        $("html, body").animate({scrollTop: 0}, "slow");
                        $('#marketing .wrapper').css({'opacity': "0", 'top': '200px'});
                        $('.contact-form').css({'opacity': "0", 'top': '200px'});


                    }, 'html');
                    return this;
                }
            }),
            inventMx.view.contacto = Backbone.View.extend({
                template: collectionMain.get("c3").attributes.pathTemplate,
                idContent: collectionMain.get("c3").attributes.firtsIdContent,
                initialize: function() {
                    $(this.el).unbind();
                    _.bindAll(this, 'render');
                    this.render();
                },
                render: function() {
                    var idContent = this.idContent;
                    var section = "contacto";
                    $.get(this.template + 'contacto/contacto.html', function(data) {
                        var animateSection = collectionMain.get("c1");
                        animateSection.set({section: section});

                        if ($(idContent + "contacto").children("div").length == 0) {
                            $(idContent + "contacto").html(data);
                        }
                        collectionMain.hideSections(section);
                        $("html, body").animate({scrollTop: 0}, "slow");
                        $('#marketing .wrapper').css({'opacity': "0", 'top': '200px'});
                        $('.contact-form').css({'opacity': "1", 'top': '0'});


                        jQuery(".contact_form").validationEngine('attach', {
                            promptPosition: "bottomLeft"
                        });

                        $(document).on("submit", ".contact_form", function(e) {
                            e.preventDefault();
                            data = $(this).serializeArray();
                            inventMx_events.trigger('Inventform', '.contact_form', data);
                            return false;
                        });
                        $(".btn-contacto .anunciate").click(function() {
                            $(".btn-contacto contcato").removeClass("active");
                            $(this).addClass("active");
                            $(".contact_form").fadeOut();
                            $(".contact_form.contact_form_anunciate").fadeIn();

                        });
                        $(".btn-contacto .afíliate").click(function() {
                            $(".btn-contacto contcato").removeClass("active");
                            $(this).addClass("active");
                            $(".contact_form").fadeOut();
                            $(".contact_form.contact_form_afilate").fadeIn();
                        });


                    }, 'html');
                    return this;
                }

            }),
            inventMx.view.codiga = Backbone.View.extend({
                template: collectionMain.get("c3").attributes.pathTemplate,
                idContent: collectionMain.get("c3").attributes.firtsIdContent,
                initialize: function() {
                    $(this.el).unbind();
                    _.bindAll(this, 'render');
                    this.render();
                },
                render: function() {
                    var idContent = this.idContent;
                    var section = "codiga";
                    $.get(this.template + 'codiga/codiga.html', function(data) {
                        var animateSection = collectionMain.get("c1");
                        animateSection.set({section: section});

                        if ($(idContent + "codiga").children("div").length == 0) {
                            $(idContent + "codiga").html(data);
                        }

                        collectionMain.hideSections(section);

                        $("html, body").animate({scrollTop: 0}, "slow");
                        $('#marketing .wrapper').css({'opacity': "0", 'top': '200px'});
                        $('.contact-form').css({'opacity': "0", 'top': '200px'});
                        $(".btn-contacto .anunciate").click(function() {
                            $(".btn-contacto contcato").removeClass("active");
                            $(this).addClass("active");
                            $(".contact_form").fadeOut();
                            $(".contact_form.contact_form_anunciate").fadeIn();

                        });
                        $(".btn-contacto .afíliate").click(function() {
                            $(".btn-contacto contcato").removeClass("active");
                            $(this).addClass("active");
                            $(".contact_form").fadeOut();
                            $(".contact_form.contact_form_afilate").fadeIn();
                        });

                    }, 'html');
                    return this;
                }
            }),
            inventMx.view.avisoPrivacidad = Backbone.View.extend({
                template: collectionMain.get("c3").attributes.pathTemplate,
                idContent: collectionMain.get("c3").attributes.firtsIdContent,
                initialize: function() {
                    $(this.el).unbind();
                    _.bindAll(this, 'render');
                    this.render();
                },
                render: function() {
                    var idContent = this.idContent;
                    var section = "avisoPrivacidad";
                    $.get(this.template + 'politicas/aviso-de-privacidad.php', function(data) {
                        collectionMain.topOffset(0, 0, 0, null);
                        var animateSection = collectionMain.get("c1");
                        animateSection.set({section: section});

                        $(idContent + "avisoPrivacidad").html(data);
                        collectionMain.hideSections(section);
                    });
                    return this;
                },
            }),
    inventMx.view.politicAmbiental = Backbone.View.extend({
        template: collectionMain.get("c3").attributes.pathTemplate,
        idContent: collectionMain.get("c3").attributes.firtsIdContent,
        initialize: function() {
            $(this.el).unbind();
            _.bindAll(this, 'render');
            this.render();
        },
        render: function() {
            var idContent = this.idContent;
            var section = "politicaAmbiental";
            $.get(this.template + 'politicas/politica-ambiental.php', function(data) {
                collectionMain.topOffset(0, 0, 0, null);
                var animateSection = collectionMain.get("c1");
                animateSection.set({section: section});
                
                $(idContent + "politicaAmbiental").html(data);
                collectionMain.hideSections(section);
            });
            return this;
        },
    }),
    inventMx.view.terminosCondiciones = Backbone.View.extend({
        template: collectionMain.get("c3").attributes.pathTemplate,
        idContent: collectionMain.get("c3").attributes.firtsIdContent,
        initialize: function() {
            $(this.el).unbind();
            _.bindAll(this, 'render');
            this.render();
        },
        render: function() {
            var idContent = this.idContent;
            var section = "terminosCondiciones";
            $.get(this.template + 'politicas/terminos-y-condiciones-de-uso.php', function(data) {
                collectionMain.topOffset(0, 0, 0, null);
                var animateSection = collectionMain.get("c1");
                animateSection.set({section: section});
                
                $(idContent + "terminosCondiciones").html(data);
                collectionMain.hideSections(section);
            });
            return this;
        },
    }),
    inventMx.view.default404 = Backbone.View.extend({
        template: collectionMain.get("c3").attributes.pathTemplate,
        idContent: collectionMain.get("c3").attributes.firtsIdContent,
        initialize: function() {
            $(this.el).unbind();
            _.bindAll(this, 'render');
            this.render();
        },
        render: function() {
            var idContent = this.idContent;
            var section = "404";
            $.get(this.template + 'PageDefault/404.html', function(data) {
                collectionMain.topOffset(0, 0, 0, null);
                if ($(idContent + "404").children("div").length == 0) {
                    $(idContent + "404").html(data);
                    collectionMain.hideSections(section);
                }
            });
        }
    });



    inventMx.thome = {};
    inventMx.thome.homeAfiliate = Backbone.View.extend({
        //el: inventMx.page.wrapper_site,
        initialize: function() {

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
        render: function() {
            inventMx.page.wrapper_site.load("/web/app/inventmx/afiliate/home.html", function() {

                jQuery("#form-afiliate").validationEngine('attach', {
                    promptPosition: "bottomLeft"
                });

                $(document).on("submit", "#form-afiliate", function(e) {
                    e.preventDefault();
                    inventMx.utilities.loaderShow();
                    console.log("cargando");
                    data = $(this).serializeArray();
                    inventMx_events.trigger('Inventform', '#form-afiliate', data);
                    return false;
                });
            });
        }
    }),
            inventMx.thome.homeAnunciate = Backbone.View.extend({
                //el: inventMx.page.wrapper_site,
                initialize: function() {

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
                    $(this.el).unbind();
                    _.bindAll(this, 'render');
                    this.render();
                },
                render: function() {
                    inventMx.page.wrapper_site.load("/web/app/inventmx/anunciate/home.html", function() {

                        jQuery("#form-anunciate").validationEngine('attach', {
                            promptPosition: "bottomLeft"
                        });

                        $(document).on("submit", "#form-anunciate", function(e) {
                            e.preventDefault();
                            data = $(this).serializeArray();
                            inventMx_events.trigger('Inventform', '#form-anunciate', data);
                        });

                        return this;
                    });

                },
            })
});