    function onSuccess(googleUser) {
      console.log('Logged in as: ' + googleUser.getBasicProfile().getName());
    }

    function onFailure(error) {
      console.log(error);
    }

    function renderButton() {
      gapi.signin2.render('my-signin2', {
        'scope': 'profile email',
        'width': 219,
        'height': 37,
        'longtitle': false,
        'margin-top':'-7px',
        'theme': 'dark',
        'onsuccess': onSuccess,
        'onfailure': onFailure
      });
    }


    function handleClientLoad() {
      // Load the API's client and auth2 modules.
      // Call the initClient function after the modules load.
      gapi.load('client:auth2', {
  callback: function() {
    // Handle gapi.client initialization.
    initClient();
  },
  onerror: function() {
    // Handle loading error.
    alert('gapi.client failed to load!');
  },
  timeout: 5000, // 5 seconds.
  ontimeout: function() {
    // Handle timeout.
    alert('gapi.client could not load in a timely manner!');
  }
});
    }

    var GoogleAuth;
    var SCOPE = 'https://www.googleapis.com/auth/analytics.readonly';



    function initClient() {
      // Retrieve the discovery document for version 3 of Google Drive API.
      // In practice, your app can retrieve one or more discovery documents.
      var discoveryUrl = 'https://www.googleapis.com/discovery/v1/apis/drive/v3/rest';

      // Initialize the gapi.client object, which app uses to make API requests.
      // Get API key and client ID from API Console.
      // 'scope' field specifies space-delimited list of access scopes.
      gapi.client.init({
        'apiKey': 'AIzaSyAmWqkeieybT1T-qzBZNQ0ASxscmljeRVA',
        'discoveryDocs': [discoveryUrl],
        'clientId': '1005095317724-qq2702oohdhg1kiu50l7pa48or84mngb.apps.googleusercontent.com',
        'scope': SCOPE
      }).then(function() {
        GoogleAuth = gapi.auth2.getAuthInstance();
        // Listen for sign-in state changes.
        GoogleAuth.isSignedIn.listen(updateSigninStatus);
        gapi.auth2.getAuthInstance().isSignedIn.listen(updateSigninStatus);
        // Handle the initial sign-in state.
        updateSigninStatus(gapi.auth2.getAuthInstance().isSignedIn.get());
        // Handle initial sign-in state. (Determine if user is already signed in.)
        var user = GoogleAuth.currentUser.get();


        //console.log(user.Zi.access_token);
        //console.log(user)
        //var access_token = user.Zi.access_token;
        //getCall(access_token);
        setSigninStatus();

        // Call handleAuthClick function when user clicks on
        //      "Sign In/Authorize" button.
        $('#sign-in-or-out-button').click(function() {
          handleAuthClick();
        });
        $('#revoke-access-button').click(function() {
          revokeAccess();
        });

      });

    }


    function makeApiCall() {

      var ids = '';
      var searchRequest = function(ids) {
        return gapi.client.request({
          'path': 'https://www.googleapis.com/analytics/v3/data/realtime?fields=totalsForAllResults',
          'method': 'get',
          'params': {
            'ids': ids,
            'metrics': 'rt:activeUsers'
          },
        });

      };

      // Adding just the request
      var Excelsior = searchRequest('ga:6643838');
      var ExcelsiorAmp = searchRequest('ga:116432353');
      var Adrenalina = searchRequest('ga:112555539');
      var AdrenalinaAmp = searchRequest('ga:116455651');
      var Actitud = searchRequest('ga:46928050');
      var ActitudInst = searchRequest('ga:117360079');
      var ActitudAmp = searchRequest('ga:116429352');
      var Imagen = searchRequest('ga:130323869');
      var batch = gapi.client.newBatch();
      batch.add(Excelsior,{"id":"Excelsior"});
      batch.add(ExcelsiorAmp,{"id":"ExcelsiorAmp"});
      batch.add(Adrenalina,{"id":"Adrenalina"});
      batch.add(AdrenalinaAmp,{"id":"AdrenalinaAmp"});
      batch.add(Actitud,{"id":"Actitud"});
      batch.add(ActitudInst,{"id":"ActitudInst"});
      batch.add(ActitudAmp,{"id":"ActitudAmp"});
      batch.add(Imagen,{"id":"Imagen"});

      batch.then(function(response) {

        $.each(response.result, function(key, item) {
         console.log(key, item);
          $('#'+key).hide().html(item.result.totalsForAllResults["rt:activeUsers"]).fadeIn(1000).addClass('animated bounceIn');
          cookieactual = parseInt($.cookie(key));
          document.cookie = key+"="+item.result.totalsForAllResults["rt:activeUsers"];
          cookienueva= parseInt($.cookie(key));
          if (cookieactual > cookienueva){
          //  alert("la cookie nueva es menor");
            $(".cont"+ key ).animate({backgroundColor: "red"}, 100)
                            .animate({backgroundColor:'#2d2d2d'}, 10000);
          }else if (cookieactual < cookienueva){
            $(".cont"+ key).animate({backgroundColor: "green"}, 100)
                                    .animate({backgroundColor:'#2d2d2d'}, 10000);
          }else{
            $(".cont"+ key).animate({backgroundColor: "#3177bc"}, 100)
                                    .animate({backgroundColor:'#2d2d2d'}, 10000);
          }
        });
        //pinta total
        ExcelsiorTotal = parseInt($.cookie("Excelsior")) + parseInt($.cookie("ExcelsiorAmp"));
        $('#ExcelsiorTotal').hide().html(ExcelsiorTotal).fadeIn(1000).addClass('animated bounceIn');
        ExcelsiorTotalAnt = parseInt($.cookie("ExcelsiorTotal"));
        //alert(ExcelsiorTotalAnt);
        document.cookie = "ExcelsiorTotal="+parseInt(ExcelsiorTotal);
        //alert(ExcelsiorTotalNew);
        ExcelsiorTotalNew = parseInt($.cookie("ExcelsiorTotal"));
        if (ExcelsiorTotalAnt > ExcelsiorTotalNew){
          $(".contExcelsiorTotal").animate({backgroundColor: "red"}, 100)
                                  .animate({backgroundColor:'#2d2d2d'}, 10000);
        }else if (ExcelsiorTotalAnt < ExcelsiorTotalNew){
          $(".contExcelsiorTotal").animate({backgroundColor: "green"}, 100)
                                  .animate({backgroundColor:'#2d2d2d'}, 10000);
        }else{
          $(".contExcelsiorTotal").animate({backgroundColor: "#3177bc"}, 100)
                                  .animate({backgroundColor:'#2d2d2d'}, 10000);
        }
        //pinta total
        AdrenalinaTotal = parseInt($.cookie("Adrenalina")) + parseInt($.cookie("AdrenalinaAmp"));
        $('#AdrenalinaTotal').hide().html(AdrenalinaTotal).fadeIn(1000).addClass('animated bounceIn');
        AdrenalinaTotalAnt = parseInt($.cookie("AdrenalinaTotal"));
        //alert(AdrenalinaTotalAnt);
        document.cookie = "AdrenalinaTotal="+parseInt(AdrenalinaTotal);
        //alert(AdrenalinaTotalNew);
        AdrenalinaTotalNew = parseInt($.cookie("AdrenalinaTotal"));
        if (AdrenalinaTotalAnt > AdrenalinaTotalNew){
          $(".contAdrenalinaTotal").animate({backgroundColor: "red"}, 100)
                                   .animate({backgroundColor:'#2d2d2d'}, 10000);
        }else if (AdrenalinaTotalAnt < AdrenalinaTotalNew){
          $(".contAdrenalinaTotal").animate({backgroundColor: "green"}, 100)
                                   .animate({backgroundColor:'#2d2d2d'}, 10000);
        }else{
          $(".contAdrenalinaTotal").animate({backgroundColor: "#3177bc"}, 100)
                                   .animate({backgroundColor:'#2d2d2d'}, 10000);
        }


           //pinta total
            ActitudTotal = parseInt($.cookie("Actitud")) + parseInt($.cookie("ActitudAmp"))+ parseInt($.cookie("ActitudInst"));
            $('#ActitudTotal').hide().html(ActitudTotal).fadeIn(1000).addClass('animated bounceIn');
            ActitudTotalAnt = parseInt($.cookie("ActitudTotal"));
            //alert(ActitudTotalAnt);
            document.cookie = "ActitudTotal="+parseInt(ActitudTotal);
            //alert(ActitudTotalNew);
            ActitudTotalNew = parseInt($.cookie("ActitudTotal"));
            if (ActitudTotalAnt > ActitudTotalNew){
              $(".contActitudTotal").animate({backgroundColor: "red"}, 100)
                                    .animate({backgroundColor:'#2d2d2d'}, 10000);
            }else if (ActitudTotalAnt < ActitudTotalNew){
              $(".contActitudTotal").animate({backgroundColor: "green"}, 100)
                                    .animate({backgroundColor:'#2d2d2d'}, 10000);
            }else{
              $(".contActitudTotal").animate({backgroundColor: "#3177bc"}, 100)
                                    .animate({backgroundColor:'#2d2d2d'}, 10000);
            }

            ImagenTotal = parseInt($.cookie("Imagen"));
            $('#ImagenTotal').hide().html(ImagenTotal).fadeIn(1000).addClass('animated bounceIn');
            ImagenTotalAnt = parseInt($.cookie("ImagenTotal"));
            //alert(ImagenTotalAnt);
            document.cookie = "ImagenTotal="+parseInt(ImagenTotal);
            //alert(ImagenTotalNew);
            ImagenTotalNew = parseInt($.cookie("ImagenTotal"));
            if (ImagenTotalAnt > ImagenTotalNew){
              $(".contImagenTotal").animate({backgroundColor: "red"}, 100)
                                   .animate({backgroundColor:'#2d2d2d'}, 10000);
            }else if (ImagenTotalAnt < ImagenTotalNew){
              $(".contImagenTotal").animate({backgroundColor: "green"}, 100)
                                    .animate({backgroundColor:'#2d2d2d'}, 10000);
            }else{
              $(".contImagenTotal").animate({backgroundColor: "#3177bc"}, 100)
                                    .animate({backgroundColor:'#2d2d2d'}, 10000);
            }
      });

    }



    function makeApiCall2() {
      var ids = '';
      var searchRequest = function(ids) {
        return gapi.client.request({
          'path': 'https://www.googleapis.com/analytics/v3/data/realtime?fields=totalsForAllResults',
          'method': 'get',
          'params': {
            'ids': ids,
            'metrics': 'rt:activeUsers'
          },
        });

      };

      var Dinero = searchRequest('ga:62706709');
      var DineroInst = searchRequest('ga:153500502');
      var DineroAmp = searchRequest('ga:116486819');
      var Atraccion = searchRequest('ga:59849096');
      var AtraccionInst = searchRequest('ga:155445728');
      var AtraccionAmp = searchRequest('ga:141799432');
      var Gamedots = searchRequest('ga:59347434');
      var GamedotsInst = searchRequest('ga:155429790');
      var GamedotsAmp = searchRequest('ga:141746476');
      var batch = gapi.client.newBatch();
      batch.add(Dinero,{"id":"Dinero"});
      batch.add(DineroInst,{"id":"DineroInst"});
      batch.add(DineroAmp,{"id":"DineroAmp"});
      batch.add(Atraccion,{"id":"Atraccion"});
      batch.add(AtraccionInst,{"id":"AtraccionInst"});
      batch.add(AtraccionAmp,{"id":"AtraccionAmp"});
      batch.add(Gamedots,{"id":"Gamedots"});
      batch.add(GamedotsInst,{"id":"GamedotsInst"});
      batch.add(GamedotsAmp,{"id":"GamedotsAmp"});

      batch.then(function(response) {
          //console.log(response.result);

          $.each(response.result, function(key, item) {
             console.log(key, item);
            //$('#'+key).htmlTo(item.result.totalsForAllResults["rt:activeUsers"]).fadeIn(1000);
            $('#'+key).hide().html(item.result.totalsForAllResults["rt:activeUsers"]).fadeIn(1000).addClass('animated bounceIn');
            cookieactual = parseInt($.cookie(key));
            document.cookie = key+"="+item.result.totalsForAllResults["rt:activeUsers"];
            cookienueva= parseInt($.cookie(key));
            if (cookieactual > cookienueva){
            //  alert("la cookie nueva es menor");
              $(".cont"+ key ).animate({backgroundColor: "red"}, 100)
                              .animate({backgroundColor:'#2d2d2d'}, 10000);
            }else if (cookieactual < cookienueva){
              $(".cont"+ key).animate({backgroundColor: "green"}, 100)
                                      .animate({backgroundColor:'#2d2d2d'}, 10000);
            }else{
              $(".cont"+ key).animate({backgroundColor: "#3177bc"}, 100)
                                      .animate({backgroundColor:'#2d2d2d'}, 10000);
            }
          });

          DineroTotal = parseInt($.cookie("Dinero")) + parseInt($.cookie("DineroInst")) + parseInt($.cookie("DineroAmp"));
          //pinta total
           $('#DineroTotal').hide().html(DineroTotal).fadeIn(1000).addClass('animated bounceIn');
           DineroTotalAnt = parseInt($.cookie("DineroTotal"));
           //alert(DineroTotalAnt);
           document.cookie = "DineroTotal="+parseInt(DineroTotal);
           //alert(DineroTotalNew);
           DineroTotalNew = parseInt($.cookie("DineroTotal"));
           if (DineroTotalAnt > DineroTotalNew){
             $(".contDineroTotal").animate({backgroundColor: "red"}, 100)
                                  .animate({backgroundColor:'#2d2d2d'}, 10000);
           }else if (DineroTotalAnt < DineroTotalNew){
             $(".contDineroTotal").animate({backgroundColor: "green"}, 100)
                                      .animate({backgroundColor:'#2d2d2d'}, 10000);
           }else{
             $(".contDineroTotal").animate({backgroundColor: "#3177bc"}, 100)
                                      .animate({backgroundColor:'#2d2d2d'}, 10000);
           }

          AtraccionTotal = parseInt($.cookie("Atraccion")) + parseInt($.cookie("AtraccionInst")) + parseInt($.cookie("AtraccionAmp"));
          //pinta total
           $('#AtraccionTotal').hide().html(AtraccionTotal).fadeIn(1000).addClass('animated bounceIn');
           AtraccionTotalAnt = parseInt($.cookie("AtraccionTotal"));
           //alert(AtraccionTotalAnt);
           document.cookie = "AtraccionTotal="+parseInt(AtraccionTotal);
           //alert(AtraccionTotalNew);
           AtraccionTotalNew = parseInt($.cookie("AtraccionTotal"));
           if (AtraccionTotalAnt > AtraccionTotalNew){
             $(".contAtraccionTotal").animate({backgroundColor: "red"}, 100)
                                     .animate({backgroundColor:'#2d2d2d'}, 10000);
           }else if (AtraccionTotalAnt < AtraccionTotalNew){
             $(".contAtraccionTotal").animate({backgroundColor: "green"}, 100)
                                      .animate({backgroundColor:'#2d2d2d'}, 10000);
           }else{
             $(".contAtraccionTotal").animate({backgroundColor: "#3177bc"}, 100)
                                      .animate({backgroundColor:'#2d2d2d'}, 10000);
           }

          GamedotsTotal = parseInt($.cookie("Gamedots")) + parseInt($.cookie("GamedotsInst")) + parseInt($.cookie("GamedotsAmp"));
           $('#GamedotsTotal').hide().html(GamedotsTotal).fadeIn(1000).addClass('animated bounceIn');
           GamedotsTotalAnt = parseInt($.cookie("GamedotsTotal"));
           //alert(GamedotsTotalAnt);
           document.cookie = "GamedotsTotal="+parseInt(GamedotsTotal);
           //alert(GamedotsTotalNew);
           GamedotsTotalNew = parseInt($.cookie("GamedotsTotal"));
           if (GamedotsTotalAnt > GamedotsTotalNew){
             $(".contGamedotsTotal").animate({backgroundColor: "red"}, 100);
             $(".contGamedotsTotal").animate({backgroundColor:'#2d2d2d'}, 10000);
           }else if (GamedotsTotalAnt < GamedotsTotalNew){
             $(".contGamedotsTotal").animate({backgroundColor: "green"}, 100);
             $(".contGamedotsTotal").animate({backgroundColor:'#2d2d2d'}, 10000);
           }else{
             $(".contGamedotsTotal").animate({backgroundColor: "#3177bc"}, 100);
             $(".contGamedotsTotal").animate({backgroundColor:'#2d2d2d'}, 10000);
           }

      });
    }


    function makeApiCall3() {

      var ids = '';
      var searchRequest = function(ids) {
        return gapi.client.request({
          'path': 'https://www.googleapis.com/analytics/v3/data/realtime?fields=totalsForAllResults',
          'method': 'get',
          'params': {
            'ids': ids,
            'metrics': 'rt:activeUsers'
          },
        });

      };

      // Adding just the request
      var Dailytrend = searchRequest('ga:78887468');
      var DailytrendInst = searchRequest('ga:155439411');
      var DailytrendAmp = searchRequest('ga:116464754');
      var Rsvp = searchRequest('ga:54331725');
      var RsvpInst = searchRequest('ga:155396166');
      var RsvpAmp = searchRequest('ga:141799436');
      var Imagenradio = searchRequest('ga:10076419');
      var ImagenradioAmp = searchRequest('ga:141848103');
      var Rmx = searchRequest('ga:136699842');
      var RmxAmp = searchRequest('ga:141818215');
      var batch = gapi.client.newBatch();
      batch.add(Dailytrend,{"id":"Dailytrend"});
      batch.add(DailytrendInst,{"id":"DailytrendInst"});
      batch.add(DailytrendAmp,{"id":"DailytrendAmp"});
      batch.add(Rsvp,{"id":"Rsvp"});
      batch.add(RsvpInst,{"id":"RsvpInst"});
      batch.add(RsvpAmp,{"id":"RsvpAmp"});
      batch.add(Imagenradio,{"id":"Imagenradio"});
      batch.add(ImagenradioAmp,{"id":"ImagenradioAmp"});
      batch.add(Rmx,{"id":"Rmx"});
      batch.add(RmxAmp,{"id":"RmxAmp"});


      batch.then(function(response) {

        $.each(response.result, function(key, item) {
          console.log(key, item);
          //$('#'+key).htmlTo(item.result.totalsForAllResults["rt:activeUsers"]).fadeIn(1000);
          $('#'+key).hide().html(item.result.totalsForAllResults["rt:activeUsers"]).fadeIn(1000).addClass('animated bounceIn');
          cookieactual = parseInt($.cookie(key));
          document.cookie = key+"="+item.result.totalsForAllResults["rt:activeUsers"];
          cookienueva= parseInt($.cookie(key));
          if (cookieactual > cookienueva){
            //alert("la cookie nueva es menor");
            $(".cont"+ key ).animate({backgroundColor: "red"}, 100)
                            .animate({backgroundColor:'#2d2d2d'}, 10000);
          }else{
          //  alert("la cookie nueva es mayor");
          $(".cont"+ key ).animate({backgroundColor: "green"}, 100)
                          .animate({backgroundColor:'#2d2d2d'}, 10000);
          }
        });
        DailytrendTotal = parseInt($.cookie("Dailytrend")) + parseInt($.cookie("DailytrendInst")) + parseInt($.cookie("DailytrendAmp"));
        //pinta total
         $('#DailytrendTotal').hide().html(DailytrendTotal).fadeIn(1000).addClass('animated bounceIn');
         DailytrendTotalAnt = parseInt($.cookie("DailytrendTotal"));
         //alert(DailytrendTotalAnt);
         document.cookie = "DailytrendTotal="+parseInt(DailytrendTotal);
         //alert(DailytrendTotalNew);
         DailytrendTotalNew = parseInt($.cookie("DailytrendTotal"));
         if (DailytrendTotalAnt > DailytrendTotalNew){
           $(".contDailytrendTotal").animate({backgroundColor: "red"}, 100);
           $(".contDailytrendTotal").animate({backgroundColor:'#2d2d2d'}, 10000);
         }else if (DailytrendTotalAnt < DailytrendTotalNew){
           $(".contDailytrendTotal").animate({backgroundColor: "green"}, 100);
           $(".contDailytrendTotal").animate({backgroundColor:'#2d2d2d'}, 10000);
         }else{
           $(".contDailytrendTotal").animate({backgroundColor: "#3177bc"}, 100);
           $(".contDailytrendTotal").animate({backgroundColor:'#2d2d2d'}, 10000);
         }

         RsvpTotal = parseInt($.cookie("Rsvp")) + parseInt($.cookie("RsvpInst")) + parseInt($.cookie("RsvpAmp"));
         //pinta total
          $('#RsvpTotal').hide().html(RsvpTotal).fadeIn(1000).addClass('animated bounceIn');
          RsvpTotalAnt = parseInt($.cookie("RsvpTotal"));
          //alert(RsvpTotalAnt);
          document.cookie = "RsvpTotal="+parseInt(RsvpTotal);
          //alert(RsvpTotalNew);
          RsvpTotalNew = parseInt($.cookie("RsvpTotal"));
          if (RsvpTotalAnt > RsvpTotalNew){
            $(".contRsvpTotal").animate({backgroundColor: "red"}, 100);
            $(".contRsvpTotal").animate({backgroundColor:'#2d2d2d'}, 10000);
          }else if (RsvpTotalAnt < RsvpTotalNew){
            $(".contRsvpTotal").animate({backgroundColor: "green"}, 100);
            $(".contRsvpTotal").animate({backgroundColor:'#2d2d2d'}, 10000);
          }else{
            $(".contRsvpTotal").animate({backgroundColor: "#3177bc"}, 100);
            $(".contRsvpTotal").animate({backgroundColor:'#2d2d2d'}, 10000);
          }

          ImagenradioTotal = parseInt($.cookie("Imagenradio")) + parseInt($.cookie("ImagenradioAmp"));
          //pinta total
           $('#ImagenradioTotal').hide().html(ImagenradioTotal).fadeIn(1000).addClass('animated bounceIn');
           ImagenradioTotalAnt = parseInt($.cookie("ImagenradioTotal"));
           //alert(ImagenradioTotalAnt);
           document.cookie = "ImagenradioTotal="+parseInt(ImagenradioTotal);
           //alert(ImagenradioTotalNew);
           ImagenradioTotalNew = parseInt($.cookie("ImagenradioTotal"));
           if (ImagenradioTotalAnt > ImagenradioTotalNew){
             $(".contImagenradioTotal").animate({backgroundColor: "red"}, 100);
             $(".contImagenradioTotal").animate({backgroundColor:'#2d2d2d'}, 10000);
           }else if (ImagenTotalAnt < ImagenTotalNew){
             $(".contImagenradioTotal").animate({backgroundColor: "green"}, 100);
             $(".contImagenradioTotal").animate({backgroundColor:'#2d2d2d'}, 10000);
           }else{
             $(".contImagenradioTotal").animate({backgroundColor: "#3177bc"}, 100);
             $(".contImagenradioTotal").animate({backgroundColor:'#2d2d2d'}, 10000);
           }

           RmxTotal = parseInt($.cookie("Rmx")) + parseInt($.cookie("RmxAmp"));
           //pinta total
            $('#RmxTotal').hide().html(RmxTotal).fadeIn(1000).addClass('animated bounceIn');
            RmxTotalAnt = parseInt($.cookie("RmxTotal"));
            //alert(RmxTotalAnt);
            document.cookie = "RmxTotal="+parseInt(RmxTotal);
            //alert(RmxTotalNew);
            RmxTotalNew = parseInt($.cookie("RmxTotal"));
            if (RmxTotalAnt > RmxTotalNew){
              $(".contRmxTotal").animate({backgroundColor: "red"}, 100)
                              .animate({backgroundColor:'#2d2d2d'}, 10000);
            }else if (RmxTotalAnt < RmxTotalNew){
              $(".contRmxTotal").animate({backgroundColor: "green"}, 100)
                                       .animate({backgroundColor:'#2d2d2d'}, 10000);
            }else{
              $(".contRmxTotal").animate({backgroundColor: "#3177bc"}, 100)
                                       .animate({backgroundColor:'#2d2d2d'}, 10000);
            }
      });
    }

    function makeApiCall4() {

      var ids = '';
      var searchRequest = function(ids) {
        return gapi.client.request({
          'path': 'https://www.googleapis.com/analytics/v3/data/realtime?fields=totalsForAllResults',
          'method': 'get',
          'params': {
            'ids': ids,
            'metrics': 'rt:activeUsers'
          },
        });

      };

      // Adding just the request
      var Bienysaludable = searchRequest('ga:140322049');
      var BienysaludableInst = searchRequest('ga:155447690');
      var BienysaludableAmp = searchRequest('ga:141744668');
      var Cocina = searchRequest('ga:117144775');
      var CocinaInst = searchRequest('ga:153505343');
      var CocinaAmp = searchRequest('ga:141804313');
      var Melodijolola = searchRequest('ga:62818963');
      var MelodijololaInst = searchRequest('ga:155432772');
      var MelodijololaAmp = searchRequest('ga:141805523');
      var batch = gapi.client.newBatch();
      batch.add(Bienysaludable,{"id":"Bienysaludable"});
      batch.add(BienysaludableInst,{"id":"BienysaludableInst"});
      batch.add(BienysaludableAmp,{"id":"BienysaludableAmp"});
      batch.add(Cocina,{"id":"Cocina"});
      batch.add(CocinaInst,{"id":"CocinaInst"});
      batch.add(CocinaAmp,{"id":"CocinaAmp"});
      batch.add(Melodijolola,{"id":"Melodijolola"});
      batch.add(MelodijololaInst,{"id":"MelodijololaInst"});
      batch.add(MelodijololaAmp,{"id":"MelodijololaAmp"});

      batch.then(function(response) {

        $.each(response.result, function(key, item) {
        console.log(key, item);
          //$('#'+key).htmlTo(item.result.totalsForAllResults["rt:activeUsers"]).fadeIn(1000);
          $('#'+key).hide().html(item.result.totalsForAllResults["rt:activeUsers"]).fadeIn(1000).addClass('animated bounceIn');
          cookieactual = parseInt($.cookie(key));
          document.cookie = key+"="+item.result.totalsForAllResults["rt:activeUsers"];
          cookienueva= parseInt($.cookie(key));
          if (cookieactual > cookienueva){
          //  alert("la cookie nueva es menor");
            $(".cont"+ key ).animate({backgroundColor: "red"}, 100)
                            .animate({backgroundColor:'#2d2d2d'}, 10000);
          }else if (cookieactual < cookienueva){
            $(".cont"+ key).animate({backgroundColor: "green"}, 100)
                                    .animate({backgroundColor:'#2d2d2d'}, 10000);
          }else{
            $(".cont"+ key).animate({backgroundColor: "#3177bc"}, 100)
                                    .animate({backgroundColor:'#2d2d2d'}, 10000);
          }
        });

        BienysaludableTotal = parseInt($.cookie("Bienysaludable")) + parseInt($.cookie("BienysaludableInst")) + parseInt($.cookie("BienysaludableAmp"));
        //pinta total
         $('#BienysaludableTotal').hide().html(BienysaludableTotal).fadeIn(1000).addClass('animated bounceIn');
         BienysaludableTotalAnt = parseInt($.cookie("BienysaludableTotal"));
         //alert(BienysaludableTotalAnt);
         document.cookie = "BienysaludableTotal="+parseInt(BienysaludableTotal);
         //alert(BienysaludableTotalNew);
         BienysaludableTotalNew = parseInt($.cookie("BienysaludableTotal"));
         if (BienysaludableTotalAnt > BienysaludableTotalNew){
           $(".contBienysaludableTotal").animate({backgroundColor: "red"}, 100);
           $(".contBienysaludableTotal").animate({backgroundColor:'#2d2d2d'}, 10000);
         }else if (BienysaludableTotalAnt < BienysaludableTotalNew){
           $(".contBienysaludableTotal").animate({backgroundColor: "green"}, 100);
           $(".contBienysaludableTotal").animate({backgroundColor:'#2d2d2d'}, 10000);
         }else{
           $(".contBienysaludableTotal").animate({backgroundColor: "#3177bc"}, 100);
           $(".contBienysaludableTotal").animate({backgroundColor:'#2d2d2d'}, 10000);
         }

         CocinaTotal = parseInt($.cookie("Cocina")) + parseInt($.cookie("CocinaInst")) + parseInt($.cookie("CocinaAmp"));
         //pinta total
          $('#CocinaTotal').hide().html(CocinaTotal).fadeIn(1000).addClass('animated bounceIn');
          CocinaTotalAnt = parseInt($.cookie("CocinaTotal"));
          //alert(CocinaTotalAnt);
          document.cookie = "CocinaTotal="+parseInt(CocinaTotal);
          //alert(CocinaTotalNew);
          CocinaTotalNew = parseInt($.cookie("CocinaTotal"));
          if (CocinaTotalAnt > CocinaTotalNew){
            $(".contCocinaTotal").animate({backgroundColor: "red"}, 100);
            $(".contCocinaTotal").animate({backgroundColor:'#2d2d2d'}, 10000);
          }else if (CocinaTotalAnt < CocinaTotalNew){
            $(".contCocinaTotal").animate({backgroundColor: "green"}, 100);
            $(".contCocinaTotal").animate({backgroundColor:'#2d2d2d'}, 10000);
          }else{
            $(".contCocinaTotal").animate({backgroundColor: "#3177bc"}, 100);
            $(".contCocinaTotal").animate({backgroundColor:'#2d2d2d'}, 10000);
          }

          MelodijololaTotal = parseInt($.cookie("Melodijolola")) + parseInt($.cookie("MelodijololaInst")) + parseInt($.cookie("MelodijololaAmp"));
          //pinta total
           $('#MelodijololaTotal').hide().html(MelodijololaTotal).fadeIn(1000).addClass('animated bounceIn');
           MelodijololaTotalAnt = parseInt($.cookie("MelodijololaTotal"));
           //alert(MelodijololaTotalAnt);
           document.cookie = "MelodijololaTotal="+parseInt(MelodijololaTotal);
           //alert(MelodijololaTotalNew);
           MelodijololaTotalNew = parseInt($.cookie("MelodijololaTotal"));
           if (MelodijololaTotalAnt > MelodijololaTotalNew){
            $(".contMelodijololaTotal").animate({backgroundColor: "red"}, 100);
            $(".contMelodijololaTotal").animate({backgroundColor:'#2d2d2d'}, 10000);
           }else if (MelodijololaTotalAnt < MelodijololaTotalNew){
             $(".contMelodijololaTotal").animate({backgroundColor: "green"}, 100);
             $(".contMelodijololaTotal").animate({backgroundColor:'#2d2d2d'}, 10000);
           }else{
             $(".contMelodijololaTotal").animate({backgroundColor: "#3177bc"}, 100);
            $(".contMelodijololaTotal").animate({backgroundColor:'#2d2d2d'}, 10000);
           }
      });
    }

    function makeApiCall5() {

      var ids = '';
      var searchRequest = function(ids) {
        return gapi.client.request({
          'path': 'https://www.googleapis.com/analytics/v3/data/realtime?fields=totalsForAllResults',
          'method': 'get',
          'params': {
            'ids': ids,
            'metrics': 'rt:activeUsers'
          },
        });

      };

      // Adding just the request
      var Salud = searchRequest('ga:36901730');
      var SaludInst = searchRequest('ga:153449755');
      var SaludAmp = searchRequest('ga:116446177');
      var Huffpost = searchRequest('ga:129681372');
      var batch = gapi.client.newBatch();
      batch.add(Salud,{"id":"Salud"});
      batch.add(SaludInst,{"id":"SaludInst"});
      batch.add(SaludAmp,{"id":"SaludAmp"});
      batch.add(Huffpost,{"id":"Huffpost"});

      batch.then(function(response) {

        $.each(response.result, function(key, item) {
      console.log(key, item);
          //$('#'+key).htmlTo(item.result.totalsForAllResults["rt:activeUsers"]).fadeIn(1000);
          $('#'+key).hide().html(item.result.totalsForAllResults["rt:activeUsers"]).fadeIn(1000).addClass('animated bounceIn');
          cookieactual = parseInt($.cookie(key));
          document.cookie = key+"="+item.result.totalsForAllResults["rt:activeUsers"];
          cookienueva= parseInt($.cookie(key));
          if (cookieactual > cookienueva){
          //  alert("la cookie nueva es menor");
            $(".cont"+ key ).animate({backgroundColor: "red"}, 100)
                            .animate({backgroundColor:'#2d2d2d'}, 10000);
          }else if (cookieactual < cookienueva){
            $(".cont"+ key).animate({backgroundColor: "green"}, 100)
                                    .animate({backgroundColor:'#2d2d2d'}, 10000);
          }else{
            $(".cont"+ key).animate({backgroundColor: "#3177bc"}, 100)
                                    .animate({backgroundColor:'#2d2d2d'}, 10000);
          }
        });

        SaludTotal = parseInt($.cookie("Salud")) + parseInt($.cookie("SaludInst")) + parseInt($.cookie("SaludAmp"));
        //pinta total
         $('#SaludTotal').hide().html(SaludTotal).fadeIn(1000).addClass('animated bounceIn');
         SaludTotalAnt = parseInt($.cookie("SaludTotal"));
         //alert(SaludTotalAnt);
         document.cookie = "SaludTotal="+parseInt(SaludTotal);
         //alert(SaludTotalNew);
         SaludTotalNew = parseInt($.cookie("SaludTotal"));
         if (SaludTotalAnt > SaludTotalNew){
           $(".contSaludTotal").animate({backgroundColor: "red"}, 100);
           $(".contSaludTotal").animate({backgroundColor:'#2d2d2d'}, 10000);
         }else if (SaludTotalAnt < SaludTotalNew){
           $(".contSaludTotal").animate({backgroundColor: "green"}, 100);
           $(".contSaludTotal").animate({backgroundColor:'#2d2d2d'}, 10000);
         }else{
           $(".contSaludTotal").animate({backgroundColor: "#3177bc"}, 100);
           $(".contSaludTotal").animate({backgroundColor:'#2d2d2d'}, 10000);
         }

         HuffpostTotal = parseInt($.cookie("Huffpost"));
          $('#HuffpostTotal').hide().html(HuffpostTotal).fadeIn(1000).addClass('animated bounceIn');
          HuffpostTotalAnt = parseInt($.cookie("HuffpostTotal"));
          //alert(HuffpostTotalAnt);
          document.cookie = "HuffpostTotal="+parseInt(HuffpostTotal);
          //alert(HuffpostTotalNew);
          HuffpostTotalNew = parseInt($.cookie("HuffpostTotal"));
          if (HuffpostTotalAnt > HuffpostTotalNew){
            $(".contHuffpostTotal").animate({backgroundColor: "red"}, 100);
            $(".contHuffpostTotal").animate({backgroundColor:'#2d2d2d'}, 10000);
          }else if (HuffpostTotalAnt < HuffpostTotalNew){
            $(".contHuffpostTotal").animate({backgroundColor: "green"}, 100);
            $(".contHuffpostTotal").animate({backgroundColor:'#2d2d2d'}, 10000);
          }else{
            $(".contHuffpostTotal").animate({backgroundColor: "#3177bc"}, 100);
            $(".contHuffpostTotal").animate({backgroundColor:'#2d2d2d'}, 10000);
          }
      });
    }

    function handleAuthClick() {
      if (GoogleAuth.isSignedIn.get()) {
        // User is authorized and has clicked 'Sign out' button.
        GoogleAuth.signOut();
      } else {
        // User is not signed in. Start Google auth flow.
        GoogleAuth.signIn();
      }
    }

    function revokeAccess() {
      GoogleAuth.disconnect();
    }

    function setSigninStatus(isSignedIn) {
      var user = GoogleAuth.currentUser.get();
      var isAuthorized = user.hasGrantedScopes(SCOPE);
      if (isAuthorized) {
        $('#sign-in-or-out-button').html('Sign out');
        $('#revoke-access-button').css('display', 'inline-block');
        $('#auth-status').html('You are currently signed in and have granted ' +
          'access to this app.');
      } else {
        $('#sign-in-or-out-button').html('Sign In/Authorize');
        $('#revoke-access-button').css('display', 'none');
        $('#auth-status').html('You have not authorized this app or you are ' +
          'signed out.');
      }
    }

    function updateSigninStatus(isSignedIn) {
        setSigninStatus();
        if (isSignedIn) {
       callVisits();

        }
      }
      var Digital=new Date();
      var hours=Digital.getHours();
      //console.log("la hora es:"+hours);
    function callVisits(){
      makeApiCall();

      setTimeout(makeApiCall2, 2000);
      setTimeout(makeApiCall3, 4000);
      setTimeout(makeApiCall4, 6000);
      setTimeout(makeApiCall5, 8000);
      setInterval(function(hours){ if (hours > 8 && hours < 22){ //console.log("lo hizo");
      callVisitsSet();
        }
      }, 60000, hours);

    }



  function callVisitsSet(){
    makeApiCall();
    setTimeout(makeApiCall2, 15000);
    setTimeout(makeApiCall3, 25000);
    setTimeout(makeApiCall4, 35000);
    setTimeout(makeApiCall5, 45000);
  }

    function signOut() {
      var auth2 = gapi.auth2.getAuthInstance();
      auth2.signOut().then(function() {
        console.log('User signed out.');
      });
    }
