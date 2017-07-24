/**
 * Draw the a chart.js line chart with data from the specified view that
 * overlays session data for the current week over session data for the
 * previous week.
 */
function renderWeekOverWeekChart(ids) {
  // Adjust `now` to experiment with different days, for testing only...
  var now = moment(); // .subtract(3, 'day');
  var thisWeek = query({
    'ids': ids,
    'dimensions': 'ga:date,ga:nthDay',
    'metrics': 'ga:sessions',
    'start-date': moment(now).subtract(1, 'day').day(0).format('YYYY-MM-DD'),
    'end-date': moment(now).format('YYYY-MM-DD')
  });
  var lastWeek = query({
    'ids': ids,
    'dimensions': 'ga:date,ga:nthDay',
    'metrics': 'ga:sessions',
    'start-date': moment(now).subtract(1, 'day').day(0).subtract(1, 'week')
      .format('YYYY-MM-DD'),
    'end-date': moment(now).subtract(1, 'day').day(6).subtract(1, 'week')
      .format('YYYY-MM-DD')
  });
  Promise.all([thisWeek, lastWeek]).then(function(results) {
    var data1 = results[0].rows.map(function(row) { return +row[2]; });
    var data2 = results[1].rows.map(function(row) { return +row[2]; });
    var labels = results[1].rows.map(function(row) { return +row[0]; });
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
    new Chart(makeCanvas('chart-1-container')).Line(data);
    generateLegend('legend-1-container', data.datasets);
  });
}
/**
 * Draw the a chart.js bar chart with data from the specified view that
 * overlays session data for the current year over session data for the
 * previous year, grouped by month.
 */
function renderYearOverYearChart(ids) {
  // Adjust `now` to experiment with different days, for testing only...
  var now = moment(); // .subtract(3, 'day');
  var thisYear = query({
    'ids': ids,
    'dimensions': 'ga:month,ga:nthMonth',
    'metrics': 'ga:users',
    'start-date': moment(now).date(1).month(0).format('YYYY-MM-DD'),
    'end-date': moment(now).format('YYYY-MM-DD')
  });
  var lastYear = query({
    'ids': ids,
    'dimensions': 'ga:month,ga:nthMonth',
    'metrics': 'ga:users',
    'start-date': moment(now).subtract(1, 'year').date(1).month(0)
      .format('YYYY-MM-DD'),
    'end-date': moment(now).date(1).month(0).subtract(1, 'day')
      .format('YYYY-MM-DD')
  });
  Promise.all([thisYear, lastYear]).then(function(results) {
    var data1 = results[0].rows.map(function(row) { return +row[2]; });
    var data2 = results[1].rows.map(function(row) { return +row[2]; });
    var labels = ['Jan','Feb','Mar','Apr','May','Jun','Jul','Aug','Sep','Oct','Nov','Dec'];
    // Ensure the data arrays are at least as long as the labels array.
    // Chart.js bar charts don't (yet) accept sparse datasets.
    for (var i = 0, len = labels.length; i < len; i++) {
      if (data1[i] === undefined) data1[i] = null;
      if (data2[i] === undefined) data2[i] = null;
    }
    var data = {
      labels : labels,
      datasets : [
        {
          label: 'Last Year',
          fillColor : 'rgba(220,220,220,0.5)',
          strokeColor : 'rgba(220,220,220,1)',
          data : data2
        },
        {
          label: 'This Year',
          fillColor : 'rgba(151,187,205,0.5)',
          strokeColor : 'rgba(151,187,205,1)',
          data : data1
        }
      ]
    };
    new Chart(makeCanvas('chart-2-container')).Bar(data);
    generateLegend('legend-2-container', data.datasets);
  })
    .catch(function(err) {
      console.error(err.stack);
    });
}
/** ################################################################# **/
/**
 * Extend the Embed APIs `gapi.analytics.report.Data` component to
 * return a promise the is fulfilled with the value returned by the API.
 * @param {Object} params The request parameters.
 * @return {Promise} A promise.
 */
function query(params) {
  return new Promise(function(resolve, reject) {
    var data = new gapi.analytics.report.Data({query: params});
    data.once('success', function(response) { resolve(response); })
      .once('error', function(response) { reject(response); })
      .execute();
  });
}
/**
 * Create a new canvas inside the specified element. Set it to be the width
 * and height of its container.
 * @param {string} id The id attribute of the element to host the canvas.
 * @return {RenderingContext} The 2D canvas context.
 */
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
/**
 * Create a visual legend inside the specified element based off of a
 * Chart.js dataset.
 * @param {string} id The id attribute of the element to host the legend.
 * @param {Array.<Object>} items A list of labels and colors for the legend.
 */
function generateLegend(id, items) {
  var legend = document.getElementById(id);
  legend.innerHTML = items.map(function(item) {
    var color = item.color || item.fillColor;
    var label = item.label;
    return '<li><i style="background:' + color + '"></i>' + label + '</li>';
  }).join('');
}
