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
        //model: config,
        //url: "/",
        defaults: {},
        initialize: function() {},
        configuration: {
            baseUrl: "http://api.inventmx.com/v1/inventmx",
            apiKey: "3a5877fc16b6fcbf8eedbe55d091938a",
            repositorio: "sites.json"
        },
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
        },
        template: function(id,append,data){
            
        },
        assembleUrl: function(callback) {
            var baseUrl = this.configuration.baseUrl;
            var apiKey = this.configuration.apiKey;
            var repositorio = this.configuration.repositorio;
            var mainParams = this.params;
            
            var params = {};
            $.each(mainParams, function(i, j) {
                if (j) {
                    params[i] = j;
                }
            });
            var url = baseUrl + "/" + repositorio + "/" + apiKey + "?callback=?";
            this.getAjax(callback,url,params);
        },
        getAjax: function(callback,url,params) {
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
                        return console.log(nodes.data);
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
    
    /*mana.add({'nombre': 'Anthony Machine' });
    mana.get('nombre');
    console.log( mana.toJSON() );*/
    //console.log(mana);
    //console.log(mana.__proto__.configuration);
    //console.log(mana.__proto__.params);
    //mana.assembleUrl();
    //mana.comparator("Angel");
    //mana.params.get("sort");
    
    /* modelos */
    inventMx.home.Models = Backbone.Model.extend({
        initialize: function() {
            this.assembleUrl();
        },
        hideSections: function(){
            
        }
    });
    
    /*Contactos = Backbone.Collection.extend({
        Model: contacto,
        url: "contactos"
    });*/
    
    var contacto = new Backbone.Model({
        nombre: "",
        telefono: "",
        initialize: function() {},
        allowedToEdit: function(account) {
            return true;
        }
        //Defaults {}
    });
    //console.log(contacto.get("nombre"));
    inventMx.home.pHomes = Backbone.View.extend({
        //el: inventMx.page.wrapper_site,
        template: "/app/templates/books/list.html",
        model: contacto,
        initialize: function() {
            $(this.el).unbind();
            _.bindAll(this, 'render');
            this.loadPage();
            this.render();
        },
        render: function() {
            console.log(this.model);
            $.get('templates/your-template-file.html', function(data) {
                console.log(data);
                template = _.template(data, {});
                this.$el.html(template);
            }, 'html');
            return this;
        },
        loadPage: function() {
            
        },
        acordeon: function(e) {},
        events: {},
    });

    /* home */
    inventMx.view = {};
    inventMx.view.home = Backbone.View.extend({
        //el: inventMx.page.wrapper_site,
        initialize: function () {
            $(this.el).unbind();
            _.bindAll(this, 'render');
            this.loadPage();
        },
        render: function () {            
            //this.loadPage();
        },
        loadPage: function () {
            $.get('/web/app/inventmx/home/home.html', function(data) {
                console.log(data);
                if(!$("#page-main-invent-home").children("div").length){
                    $("#page-main-invent-home").html(data);
                }else {
                    console.log("cache");
                }
                collectionMain.hideSections();
                
                //template = _.template(data, {});
                //this.$el.html(template);
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
        initialize: function () {
            $(this.el).unbind();
            _.bindAll(this, 'render');
            this.render();
        },
        render: function () {            
            $.get('/web/app/inventmx/redInvent/redInvent.html', function(data) {
                if(!$("#page-main-invent-redInvent").children("div")){
                    $("#page-main-invent-redInvent").html(data);
                }
                collectionMain.hideSections();
            }, 'html');
            return this;
        }
    }),
    inventMx.view.content = Backbone.View.extend({
        initialize: function () {
            $(this.el).unbind();
            _.bindAll(this, 'render');
            this.render();
        },
        render: function () {            
            $.get('/web/app/inventmx/content/content.html', function(data) {
                if(!$("#page-main-invent-content").children("div")){
                    $("#page-main-invent-content").html(data);
                }
            }, 'html');
            return this;
        }
    }),
    inventMx.view.mediaHappenings = Backbone.View.extend({
        initialize: function () {
            $(this.el).unbind();
            _.bindAll(this, 'render');
            this.render();
        },
        render: function () {            
            $.get('/web/app/inventmx/mediaHappenings/mediaHappenings.html', function(data) {
                 if(!$("#page-main-invent-mediaHappenings").children("div")){
                    $("#page-main-invent-mediaHappenings").html(data);
                }
            }, 'html');
            return this;
        }
    }),
    inventMx.view.networkAds = Backbone.View.extend({
        initialize: function () {
            $(this.el).unbind();
            _.bindAll(this, 'render');
            this.render();
        },
        render: function () {            
            $.get('/web/app/inventmx/networkAds/networkAds.html', function(data) {
                if(!$("#page-main-invent-networkAds").children("div")){
                    $("#page-main-invent-networkAds").html(data);
                }
            }, 'html');
            return this;
        }
    }),
    inventMx.view.blogs = Backbone.View.extend({
        initialize: function () {
            $(this.el).unbind();
            _.bindAll(this, 'render');
            this.render();
        },
        render: function () {            
            $.get('/web/app/inventmx/blogs/blogs.html', function(data) {
                if(!$("#page-main-invent-blogs").children("div")){
                    $("#page-main-invent-blogs").html(data);
                }
            }, 'html');
            return this;
        }
    }),
    inventMx.view.contacto = Backbone.View.extend({
        initialize: function () {
            $(this.el).unbind();
            _.bindAll(this, 'render');
            this.render();
        },
        render: function () {            
            $.get('/web/app/inventmx/contacto/contacto.html', function(data) {
                 if(!$("#page-main-invent-contacto").children("div")){
                    $("#page-main-invent-contacto").html(data);
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