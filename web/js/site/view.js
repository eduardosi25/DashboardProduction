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
            $(this.el).unbind();
            _.bindAll(this, 'render');
            this.loadPage();
        },
        render: function () {            
            //this.loadPage();
        },
        loadPage: function () {
            
            inventMx.page.wrapper_site.load("/web/app/inventmx/home/home.html", function () {
                
                repo = "sites.json";
                url = null;
                return this;
            });
            
        },        
        acordeon: function(e) {
            e.preventDefault();                   
        },
        events: {
            "click #home-accordion h2": "acordeon",
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
    
    
    inventMx.home.avisoPrivacidad = Backbone.View.extend({
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
    
    inventMx.home.politicAmbiental = Backbone.View.extend({
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