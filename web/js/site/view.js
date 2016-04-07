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
    
    /* colecciones */
    var collectionsMain = Backbone.Collection.extend({
        //model: modelMain,
        //url: "/",
        initialize: function() {},
        template: function(idTemplate, appendTo, data,callback) {
            console.log(idTemplate,appendTo);
            if ($(idTemplate).length && $(appendTo).length && data.length) {
                var tpl = $(idTemplate).html();
                var section = Handlebars.compile(tpl);
                var items = section(data);
                $(appendTo).html(items);
                if(typeof callback == "function"){
                    callback();
                }
            }else {
                console.log("Es posible que no exista algún parametro enviado, los datos recibidos para el template son:");
                console.log("template: "+idTemplate);
                console.log("append: "+ appendTo);
                console.log("data:");
                console.log(data);
            }
        },
        assembleUrl: function(idTemplate, appendTo,renderTemplate,callback) {
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
            this.getAjax(idTemplate,appendTo,renderTemplate,url,params,callback);
        },
        getAjax: function(idTemplate,appendTo,renderTemplate,url,params,callback) {
            Backbone.ajax({
                //dataType: "jsonp",
                url: url,
                data: params,
                dataType: 'json',
                type: 'GET',
                contentType: "application/json; charset=utf-8",
                async: true,
                success: function(nodes) {
                    /*var Model = Backbone.Model.extend({});
                    var Collection = Backbone.Collection.extend({
                        model: Model
                    });
                    collection = new Collection(val);*/
                    //callback(collection);
                    
                    if(nodes.response.status == "200" && nodes.data.length){
                        if(typeof renderTemplate == "function"){
                            var data = nodes.data;
  
                            
                            
                            renderTemplate(idTemplate, appendTo, data,callback)
                        }
                    }else if(nodes.response.status == "200" && !nodes.data.length){
                        return console.log("datos vacio");
                    }else {
                        return console.log("Status: " +nodes.response.status);
                    }
                    //return console.log(nodes);
                },
                error: function(request, status, error) {
                    alert("Hubo un error inesperado, intenta nuevamente por favor");
                }
            });
        },
        hideSections: function(section){
            $("#wrapper-page div[id^='page-main-invent-']").each(function(){
                $(this).hide();
                $("#wrapper-page #page-main-invent-"+section).show();
            });
        }
    });
    
    var collectionMain = new collectionsMain();
    collectionMain.add({
        baseUrl: "http://api.inventmx.com/v1/inventmx",
        apiKey: "3a5877fc16b6fcbf8eedbe55d091938a",
        repositorio: "sites.json"
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
        firtsIdContent:"#page-main-invent-",
    });
    
    //collectionMain.assembleUrl(collectionMain.template);
    
    inventMx.models = {};
    inventMx.view = {};
    /* modelos */
    //inventMx.models.home = Backbone.Model.extend({
    var modelsHome = Backbone.Model.extend({
        initialize: function() {
            console.log("1");
        },
        section:function(){
            console.log("2");
        }
    });
    
    /* home */
    inventMx.view.home = Backbone.View.extend({
        //el: inventMx.page.wrapper_site,
        template: collectionMain.get("c3").attributes.pathTemplate,
        idContent: collectionMain.get("c3").attributes.firtsIdContent,
        model: modelsHome,
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
            //console.log(this.model);
            var idContent = this.idContent;
            var section = "home";
            $.get(this.template+'home/home.html', function(data) {
                //console.log(data);
                //console.log("home");
                if($(idContent+"home").children("div").length == 0){
                    $(idContent+"home").html(data);
                }else {
                    console.log("cache");
                }
                collectionMain.hideSections(section);
                
                
                repositorio = collectionMain.get("c1");
                repositorio.set({repositorio: "sites.json"});
                
                params = collectionMain.get("c2");
                /* se pasan los campos del API */
                params.set({fields: "id|title|url|summary|images"});
                params.set({limit: "30"});
                
                /* renderTemplate: render generico, esto se puede copiar modificar nada */
                var renderTemplate = collectionMain.template;
                
                /* idTemplate: id del Template de javascript */
                var idTemplate = "#template-sections-sites";
                /* appendTo: lugar donde se pondra el template ya rendereado */
                var appendTo = "#sections-sites";
                /* callback: debe ser una función para poder ejecutarse */
                var callback = function(){
                    params.set({fields: null});
                     
                       $('.flexslider_marcas').flexslider({
                        animation: "slide",
                        animationLoop: true,
                        slideshowSpeed: 4000, 
                        animationSpeed: 2000,
                        controlNav: false,               
                        directionNav: true, 

                      });
                }; 
                
                /* Se hace la petición y  se pasan lo parámetros antes nombrados */
                collectionMain.assembleUrl(idTemplate, appendTo,renderTemplate,callback);
                
                repositorio.set({repositorio: "vloger.json"});
                
                params.set({fields: "id|title|url|audience|images|followers"});
                params.set({limit: "90"});
                 var idTemplate = "#template-sections-vloggers";
                /* appendTo: lugar donde se pondra el template ya rendereado */
                var appendTo = "#sections-vloggers";
                /* callback: debe ser una función para poder ejecutarse */
                var callback = function(){
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
                    
              
                     
                       
                }; 
                /* Se hace la petición y  se pasan lo parámetros antes nombrados */
                collectionMain.assembleUrl(idTemplate, appendTo,renderTemplate,callback);
                
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
                    onStep: function (from, to, percent) {
                        $(this.element).find('.pie-value').text(Math.round(percent*10)/10 + '%');
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
                            onStep: function (from, to, percent) {
                                $(this.element).find('.pie-value').text(Math.round(percent*10)/10 + '%');
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
                            onStep: function (from, to, percent) {
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
                            onStep: function (from, to, percent) {
                                $(this.element).find('.pie-value').text(Math.round(percent*10)/10 + '%');
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
                            onStep: function (from, to, percent) {
                                $(this.element).find('.pie-value').text(Math.round(percent*10)/10 + '%');
                            }
                        });
                $('#demo-pie-6').pieChart({
                            barColor: '#17d9b4',
                            trackColor: '#a03d73',
                            lineCap: 'square',
                            lineWidth: 24,
                            size: 158,
                            rotate: -110,

                            onStep: function (from, to, percent) {
                                $(this.element).find('.pie-value').text(Math.round(percent*10)/10 + '%');
                            }
                        });
                $('#demo-pie-7').pieChart({
                            barColor: '#17d9b4',
                            trackColor: '#a03d73',
                            lineCap: 'square',
                            lineWidth: 24,
                            size: 158,
                            rotate: -110,

                            onStep: function (from, to, percent) {
                                $(this.element).find('.pie-value').text(Math.round(percent*10)/10 + '%');
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
                            onStep: function (from, to, percent) {
                                $(this.element).find('.pie-value').text(Math.round(percent*10)/10 + '%');
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
                            onStep: function (from, to, percent) {
                                $(this.element).find('.pie-value').text(Math.round(percent*10)/10 + '%');
                            }
                        });
                    $("#audiencias .wrapper .content-audiencias > div").on({

                        mouseenter: function (e) {
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
                        mouseleave: function (e) {
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
                    
               
                
            }, 'html');
            
            return this;
            /*repo = "sites.json";
                url = null;
                return this;*/
            
            
        },        
        acordeon: function(e) {
            e.preventDefault();                   
        },
        events: {
            "click #home-accordion h2": "acordeon",
        },
    }),
    
    inventMx.view.redInvent = Backbone.View.extend({
        template: collectionMain.get("c3").attributes.pathTemplate,
        idContent: collectionMain.get("c3").attributes.firtsIdContent,
        initialize: function () {
            $(this.el).unbind();
            _.bindAll(this, 'render');
            this.render();
        },
        render: function () {
            var idContent = this.idContent;
            var  section = "redInvent";
            $.get(this.template+'redInvent/redInvent.html', function(data) {
                if($(idContent+"redInvent").children("div").length == 0){
                    $(idContent+"redInvent").html(data);
                }
                collectionMain.hideSections(section);
            }, 'html');
            return this;
        }
    }),
    inventMx.view.servicios = Backbone.View.extend({
        template: collectionMain.get("c3").attributes.pathTemplate,
        idContent: collectionMain.get("c3").attributes.firtsIdContent,
        initialize: function () {
            $(this.el).unbind();
            _.bindAll(this, 'render');
            this.render();
        },
        render: function () {
            var idContent = this.idContent;
            var  section = "servicios";
            $.get(this.template+'servicios/servicios.html', function(data) {
                if($(idContent+"servicios").children("div").length == 0){
                    $(idContent+"servicios").html(data);
                }
                     var urlHash = window.location.href.split("#")[1];
                    if (urlHash &&  $('#' + urlHash).length )
                          $('html,body').animate({
                              scrollTop: $('#' + urlHash).offset().top
                          }, 1500);
                
                collectionMain.hideSections(section);
            }, 'html');
            return this;
        }
    }),
    inventMx.view.blogs = Backbone.View.extend({
        template: collectionMain.get("c3").attributes.pathTemplate,
        idContent: collectionMain.get("c3").attributes.firtsIdContent,
        initialize: function () {
            $(this.el).unbind();
            _.bindAll(this, 'render');
            this.render();
        },
        render: function () {
            var idContent = this.idContent;
            var  section = "blogs";
            $.get(this.template+'blogs/blogs.html', function(data) {
                if($(idContent+"blogs").children("div").length == 0){
                    $(idContent+"blogs").html(data);
                }
                collectionMain.hideSections(section);
            }, 'html');
            return this;
        }
    }),
    inventMx.view.blogsNota = Backbone.View.extend({
        template: collectionMain.get("c3").attributes.pathTemplate,
        idContent: collectionMain.get("c3").attributes.firtsIdContent,
        initialize: function () {
            $(this.el).unbind();
            _.bindAll(this, 'render');
            this.render();
        },
        render: function () {
            var idContent = this.idContent;
            var  section = "blogsNota";
            $.get(this.template+'blogs/blogsNota.html', function(data) {
                $(idContent+"blogsNota").html(data);
                collectionMain.hideSections(section);
            }, 'html');
            return this;
        }
    }),
    inventMx.view.perfilSitio = Backbone.View.extend({
        template: collectionMain.get("c3").attributes.pathTemplate,
        idContent: collectionMain.get("c3").attributes.firtsIdContent,
        initialize: function () {
            $(this.el).unbind();
            _.bindAll(this, 'render');
            this.render();
        },
        render: function () {
            var idContent = this.idContent;
            var  section = "perfilSitio";
            $.get(this.template+'perfilSitio/perfilSitio.html', function(data) {
                $(idContent+"perfilSitio").html(data);
                collectionMain.hideSections(section);
            }, 'html');
            return this;
        }
    }),
    inventMx.view.perfilTalento = Backbone.View.extend({
        template: collectionMain.get("c3").attributes.pathTemplate,
        idContent: collectionMain.get("c3").attributes.firtsIdContent,
        initialize: function () {
            $(this.el).unbind();
            _.bindAll(this, 'render');
            this.render();
        },
        render: function () {
            var idContent = this.idContent;
            var  section = "perfilTalento";
            $.get(this.template+'perfilTalento/perfilTalento.html', function(data) {
                $(idContent+"perfilTalento").html(data);
                collectionMain.hideSections(section);
            }, 'html');
            return this;
        }
    }),
    inventMx.view.contacto = Backbone.View.extend({
        template: collectionMain.get("c3").attributes.pathTemplate,
        idContent: collectionMain.get("c3").attributes.firtsIdContent,
        initialize: function () {
            $(this.el).unbind();
            _.bindAll(this, 'render');
            this.render();
        },
        render: function () {
            var idContent = this.idContent;
            var  section = "contacto";
            $.get(this.template+'contacto/contacto.html', function(data) {
                 if($(idContent+"contacto").children("div").length == 0){
                    $(idContent+"contacto").html(data);
                    collectionMain.hideSections(section);
                }
            }, 'html');
            return this;
        }
    }),
    inventMx.view.codiga = Backbone.View.extend({
        template: collectionMain.get("c3").attributes.pathTemplate,
        idContent: collectionMain.get("c3").attributes.firtsIdContent,
        initialize: function () {
            $(this.el).unbind();
            _.bindAll(this, 'render');
            this.render();
        },
        render: function () {
            var idContent = this.idContent;
            var  section = "codiga";
            $.get(this.template+'codiga/codiga.html', function(data) {
                 if($(idContent+"codiga").children("div").length == 0){
                    $(idContent+"codiga").html(data);
                    collectionMain.hideSections(section);
                }
            }, 'html');
            return this;
        }
    }),
    inventMx.view.casoExito = Backbone.View.extend({
        template: collectionMain.get("c3").attributes.pathTemplate,
        idContent: collectionMain.get("c3").attributes.firtsIdContent,
        initialize: function () {
            $(this.el).unbind();
            _.bindAll(this, 'render');
            this.render();
        },
        render: function () {
            var idContent = this.idContent;
            var  section = "casoExito";
            $.get(this.template+'caso-de-exito/caso-de-exito.html', function(data) {
                 if($(idContent+"casoExito").children("div").length == 0){
                    $(idContent+"casoExito").html(data);
                    collectionMain.hideSections(section);
                }
            }, 'html');
            return this;
        }
    }),
    
    
    
    inventMx.thome = {};
    inventMx.thome.homeAfiliate = Backbone.View.extend({
        //el: inventMx.page.wrapper_site,
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
            inventMx.page.wrapper_site.load("/web/app/inventmx/afiliate/home.html", function () {
                
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
            });
        }
    }),
    inventMx.thome.homeAnunciate = Backbone.View.extend({
        //el: inventMx.page.wrapper_site,
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
            $(this.el).unbind();
            _.bindAll(this, 'render');
            this.render();            
        },
        render:function(){
            inventMx.page.wrapper_site.load("/web/app/inventmx/anunciate/home.html", function () {
                
                jQuery("#form-anunciate").validationEngine('attach', {
                    promptPosition: "bottomLeft"
                });
                
                $(document).on("submit","#form-anunciate",function(e){
                    e.preventDefault();
                    data = $(this).serializeArray();
                    inventMx_events.trigger('Inventform','#form-anunciate',data);
                });
                
                return this;
            });
            
        },
    }),
    
    
    inventMx.thome.avisoPrivacidad = Backbone.View.extend({
        initialize: function () {
            this.render();
        },
        render:function(){
            $("").load("/web/app/inventmx/politicas/aviso-de-privacidad.php", function () {
                    
                return this;
            });
            return this;
        },
    });
    
    inventMx.thome.politicAmbiental = Backbone.View.extend({
        initialize: function () {
            this.render();
        },
        render:function(){
            $("").load("/web/app/inventmx/politicas/politica-ambiental.php", function () {
                return this;
            });
        },
    });
    
});