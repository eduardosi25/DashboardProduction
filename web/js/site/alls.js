(function (inventMx, undefined) {
    inventMx.ajax = {},
    inventMx.header = {},
    inventMx.utilities = {},
    inventMx.home = {},    
    inventMx.main = {},
    inventMx.pageDefault = {},
    inventMx.page = {},
    inventMx.email = {},
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
    inventMx.ajax.getAjax = function(url, params,callback,options) {
        jQuery.ajax({
            url: url,
            data: params,
            dataType: 'json',
            type: 'GET',
            timeout: 100000,
            contentType: "application/json; charset=utf-8",
            async: false,
            success: function(data) {
                console.log(data);
                if (data) {
                    callback(data,options);
                } else {
                    inventMx.utilities.loaderHide();
                    alert("Hubo un error inesperado, intenta nuevamente por favor");
                }
            },
            error: function(request, status, error) {
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
        
        /*ActveMain = inventMx.utilities.section;
        $("header ul li a#"+ActveMain).addClass("active");
        console.log("header ul li a#"+ActveMain);*/
        
        
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