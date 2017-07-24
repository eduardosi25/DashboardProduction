
<!DOCTYPE html>
<html>
<head>
  <title>Embed API Demo</title>
  <!-- This demo uses the Chart.js graphing library and Moment.js to do date
       formatting and manipulation. -->
  <script src="https://cdnjs.cloudflare.com/ajax/libs/Chart.js/1.0.2/Chart.min.js"></script>
  <script src="https://cdnjs.cloudflare.com/ajax/libs/moment.js/2.10.2/moment.min.js"></script>
  <script src="https://code.jquery.com/jquery-2.1.4.min.js"></script>
  <style>

    body {
      font-family: 'Open Sans', sans-serif;
    }

    .reportContainer {
      float: left;
      margin-bottom: 20px;
      margin-right: 20px;
    }

    .chartContainer {
      width: 500px;
      height: 200px;
    }

    .chartTitleContainer {
      width: 500px;
      text-align: center;
      font-weight: bold;
      font-size: 1.5em;
    }

    .up {
      color: green;
    }
    .down {
      color: red;
    }
  </style>
</head>
<body>


<!-- Step 1: Create the containing elements. -->

<section id="auth-button"></section>
<section id="timeline"></section>

<!-- Step 2: Load the Embed API library. -->
<script>
  (function(w,d,s,g,js,fjs){
    g=w.gapi||(w.gapi={});g.analytics={q:[],ready:function(cb){this.q.push(cb)}};
    js=d.createElement(s);fjs=d.getElementsByTagName(s)[0];
    js.src='https://apis.google.com/js/platform.js';
    fjs.parentNode.insertBefore(js,fjs);js.onload=function(){g.load('analytics')};
  }(window,document,'script'));
</script>

<script>
  var profiles;
  var curProfile = 0;

  function getProfiles(cb) {
    //do we have a cached version?
    if(sessionStorage["gaProfiles"]) {
      console.log("profiles fetched from cache");
      cb(JSON.parse(sessionStorage["gaProfiles"]));
      return;
    }

    gapi.client.analytics.management.accounts.list().then(function(res) {
      var accountId = res.result.items[0].id;
      var profiles = [];
      gapi.client.analytics.management.webproperties.list({'accountId': accountId}).then(function(res) {

        res.result.items.forEach(function(item) {
          if(item.defaultProfileId) profiles.push({id:"ga:"+item.defaultProfileId,name:item.name});
        });
        sessionStorage["gaProfiles"] = JSON.stringify(profiles);
        cb(profiles);
      });
    });
  }

  //Credit: https://ga-dev-tools.appspot.com/embed-api/third-party-visualizations/
  function query(params) {
    return new Promise(function(resolve, reject) {
      var data = new gapi.analytics.report.Data({query: params});
      data.once('success', function(response) { resolve(response); })
        .once('error', function(response) { reject(response); })
        .execute();
    });
  }

  function makeCanvas(id) {
    var container = document.getElementById(id);
    var canvas = document.createElement('canvas');
    var ctx = canvas.getContext('2d');

    container.innerHTML = '';
    canvas.width = container.offsetWidth;
    canvas.height = container.offsetHeight;
    container.appendChild(canvas);

    return ctx;
  }

  function processProfiles() {
    console.log("working on profile "+profiles[curProfile].name);

    var now = moment();
    console.log('this week',moment(now).subtract(1, 'day').day(0).format('YYYY-MM-DD'),moment(now).format('YYYY-MM-DD') );
    console.log('this week',moment(now).subtract(8, 'day').format('YYYY-MM-DD'),moment(now).subtract(1,'day').format('YYYY-MM-DD') );
    console.log('last week',moment(now).subtract(15, 'day').format('YYYY-MM-DD'),moment(now).subtract(8,'day').format('YYYY-MM-DD') );
    //console.log('last week',moment(now).subtract(1, 'day').day(0).subtract(1, 'week').format('YYYY-MM-DD'),moment(now).subtract(1, 'day').day(6).subtract(1, 'week').format('YYYY-MM-DD') )

    var id = profiles[curProfile].id;

    var thisWeek = query({
      'ids': id,
      'dimensions': 'ga:date,ga:nthDay',
      'metrics': 'ga:pageviews',
      'start-date': moment(now).subtract(8, 'day').format('YYYY-MM-DD'),
      'end-date': moment(now).subtract(1,'day').format('YYYY-MM-DD')
    });

    var lastWeek = query({
      'ids': id,
      'dimensions': 'ga:date,ga:nthDay',
      'metrics': 'ga:pageviews',
      'start-date': moment(now).subtract(15, 'day').subtract(1, 'week')
        .format('YYYY-MM-DD'),
      'end-date': moment(now).subtract(8, 'day').subtract(1, 'week')
        .format('YYYY-MM-DD')
    });


    Promise.all([thisWeek, lastWeek]).then(function(results) {
      console.log("Promise.all");console.dir(results);

      var data1 = results[0].rows.map(function(row) { return +row[2]; });
      var data2 = results[1].rows.map(function(row) { return +row[2]; });
      var labels = results[1].rows.map(function(row) { return +row[0]; });

      var totalThisWeek = results[0].totalsForAllResults["ga:pageviews"];
      var totalLastWeek = results[1].totalsForAllResults["ga:pageviews"];
      var percChange = (((totalThisWeek - totalLastWeek) / totalLastWeek) * 100).toFixed(2);
      console.log(totalLastWeek, totalThisWeek, percChange);

      labels = labels.map(function(label) {
        return moment(label, 'YYYYMMDD').format('ddd');
      });

      var data = {
        labels : labels,
        datasets : [
          {
            label: 'Last Week',
            fillColor : 'rgba(220,220,220,0.5)',
            strokeColor : 'rgba(220,220,220,1)',
            pointColor : 'rgba(220,220,220,1)',
            pointStrokeColor : '#fff',
            data : data2
          },
          {
            label: 'This Week',
            fillColor : 'rgba(151,187,205,0.5)',
            strokeColor : 'rgba(151,187,205,1)',
            pointColor : 'rgba(151,187,205,1)',
            pointStrokeColor : '#fff',
            data : data1
          }
        ]
      };

      var titleStr = profiles[curProfile].name + " ";
      if(totalLastWeek > 0 && totalThisWeek > 0) {
        if(percChange < 0) {
          titleStr += "<span class='down'>(Down "+Math.abs(percChange) + "%)</span>";
        } else {
          titleStr += "<span class='up'>(Up "+percChange + "%)</span>";
        }
      }

      $("body").append("<div class='reportContainer'><div class='chartTitleContainer'>"+titleStr+"</div><div class='chartContainer' id='chart-"+curProfile+"-container'></div></div>");

      new Chart(makeCanvas('chart-'+curProfile+'-container')).Line(data);

      if(curProfile+1 < profiles.length) {
        curProfile++;
        //settimeout to try to avoid GA rate limits
        setTimeout(processProfiles,200);
      }
    });
  }

  gapi.analytics.ready(function() {

    var CLIENT_ID = '393479470712-nhtkfs438r5u6tcprkd9bmlppr75b5a4.apps.googleusercontent.com';

    gapi.analytics.auth.authorize({
      container: 'auth-button',
      clientid: CLIENT_ID,
      userInfoLabel:""
    });

    gapi.analytics.auth.on('success', function(response) {
      //hide the auth-button
      document.querySelector("#auth-button").style.display='none';
      console.log("get profiles");
      getProfiles(function(profs) {
        window.profiles = profs;
        processProfiles();
      });

    });

    Chart.defaults.global.animationSteps = 60;
    Chart.defaults.global.animationEasing = 'easeInOutQuart';
    Chart.defaults.global.responsive = true;
    Chart.defaults.global.maintainAspectRatio = false;

  });
</script>

<!-- Include the ViewSelector2 component script. -->
<script src="/sites/all/modules/custom/imx_dashboard/js/view-selector2.js"></script>
<!-- Include the DateRangeSelector component script. -->
<script src="/sites/all/modules/custom/imx_dashboard/js/date-range-selector.js"></script>
<!-- Include the ActiveUsers component script. -->
<script src="/sites/all/modules/custom/imx_dashboard/js/active-users.js"></script>
<!-- Include the CSS that styles the charts. -->
<link rel="stylesheet" href="/sites/all/modules/custom/imx_dashboard/css/chartjs-visualizations.css">

</body>
</html>
