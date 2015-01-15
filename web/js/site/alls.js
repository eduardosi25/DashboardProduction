(function (inventMx, undefined) {
    inventMx.ajax = {},
    inventMx.header = {},
    inventMx.utilities = {},
    inventMx.home = {},
    inventMx.pageDefault = {},
    inventMx.page = {},
    inventMx.header.main = function () {
    },    
    inventMx.page.wrapper_site = $("#wrapper-page-site"),
    inventMx.utilities.loaderShow = function () {
        $("#wrapper-loading-layout").css("display", "block");
    },
    inventMx.utilities.loaderHide = function () {
        $("#wrapper-loading-layout").css("display", "none");
    },
    inventMx.ajax.params = function() {
        params = iMxWebapp.dataSource.params;
        finshparams = {};
        $.each(params, function(i, x) {
            if (x) {
                finshparams[i] = x;
            }
        });
        return finshparams;
    },
    inventMx.ajax.getAjax = function(url, params, callback) {
        jQuery.ajax({
            url: url,
            data: params,
            dataType: 'json',
            type: 'GET',
            timeout: 100000,
            contentType: "application/json; charset=utf-8",
            async: false,
            success: function(data) {
                if (data.data.sections) {                    
                    callback(data);
                } else {
                    alert("Hubo un error inesperado, intenta nuevamente por favor");
                }
            },
            error: function(request, status, error) {
                alert("Hubo un error inesperado, intenta nuevamente por favor");
            }
        });
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
    inventMx.utilities.topOffset = function(position) {
        $('body,html').delay(position).animate({
            scrollTop: position
        }, 300,function(){
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
    }
    
    $(document).ready(function(){
       /*$("header ul li a").click(function(){
           inventMx.utilities.loaderShow();
       });*/
    });

})(window.inventMx = window.inventMx || {});

/*define({        
 apen : function(){
 $("body").append("<div>Hola mundo</div>");
 }
 });*/

/*define(function () {
 //Do setup work here
 return {        
 color: "negro claro",
 size: function(){
 alert("entre");
 },
 }
 });*/