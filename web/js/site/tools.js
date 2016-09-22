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
        website: 'http://www.imagendigital.com/',
        websiteUrl: 'http://www.imagendigital.com/',
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
        title: "Home | Imagen Digital",
        canonical: "http://www.imagendigital.com",
        description: "Imagen Digital es la comunidad de sitios mas grande de mexico, acercamos personas con perfiles similares mediante el uso natural del Internet",
        og_site_name: "Imagen Digital",
        og_title: "Imagen Digital",
        og_description: "Imagen Digital es la comunidad de sitios mas grande de mexico, acercamos personas con perfiles similares mediante el uso natural del Internet",
        og_url: "http://www.imagendigital.com",
        og_type: "website",
        og_image: "/web/img/favicons/mstile-150x150.png",
    };
    
    inventMx.metas.compile = function() {
        
        var head = $("#metas").html();
        var tpl_head = Handlebars.compile(head);
        var view_head = tpl_head(inventMx.metas.configure);
        //var metas;
        $("head meta, head link[rel='canonical']").each(function () {
            $(this).remove();
        });
        $("title").remove();
        $("head").prepend(view_head);
    },
    inventMx.render.tplPerfilSites = function(resp){
        if (resp.response.status == 200) {
            dataSite = resp.data[0];
            if(dataSite){
                inventMx.metas.configure = {
                    title: dataSite.title +" | ImagenDigital",
                    canonical: url,
                    description: dataSite.summary,
                    og_site_name: "ImagenDigital",
                    og_title: "ImagenDigital",
                    og_description: dataSite.summary,
                    og_url: url,
                    og_type: "website",
                    og_image: dataSite.images.logo[0].url,
                };
                inventMx.metas.compile();
                

            }
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
        
    }
    inventMx.utilities.calculateheightItem = function(items){
        var numbers = [];
        $(items).each(function(i,j){            
            numbers[i] = $(this).height();
        });
        return inventMx.utilities.searchNumbersMayor(numbers);
    },
    inventMx.utilities.searchNumbersMayor = function(number){
        //function mayor(m){
        var numbers=[].slice.call(number);
        return numbers.sort(function(a,b){return a-b;}).pop();
    }
    

})(window.inventMx = window.inventMx || {});
/* end alls */