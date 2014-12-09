/**
* Clase cXense search para la ejecución de un index schema sobre un site id 
* ver https://wiki.cxense.com/display/cust/cX%3A%3Asearch+-+Getting+Started
*
* @class Search
* @constructor
* @execute
* @param {String} siteId
*/

function cxSearch(siteId){

	this.queryType = 'search'; // search o recs
	this.siteId = siteId || '9222288259132208948'; // siteId de excélsior
	
	this.matchingMode = undefined; //para recs

	this.queryString = undefined;
	
	this.p_aq = 'query(kw-entity:"excelsior") and query(imx-nodetype:"article")';
	this.p_sm = 'publishtime:desc';
	this.p_c = '20';
	this.callback = 'jsonpCallback';

	this.fetchResults = function(){

		this.buildQuery();

		jQuery.ajax({
			type: 'GET',
			url: this.queryString,
			async: false,
			jsonp: 'p_callback',
			jsonpCallback:  this.callback,
			contentType: "application/json",
			dataType: 'jsonp',
			error: function(e) {
				// console.log(e.message);
			},
			success: function(data){

			}
		});

		this.queryString = undefined;
	}

	this.buildQuery = function(){
		if(typeof(this.queryString) === 'undefined'){
			var queryArray = [];
			for(var queryProperty in this){
				if(typeof(this[queryProperty]) !== 'undefined' && typeof(this[queryProperty]) !== 'function' && queryProperty != 'queryString' && queryProperty != 'siteId' && queryProperty != 'matchingMode' && queryProperty != 'queryType' && queryProperty != 'callback')
					queryArray.push(queryProperty + '=' + this[queryProperty]);
			}
			
			var queryArrayClean = [];
			for(var key in queryArray){
				queryArrayClean.push( encodeURI(queryArray[key]) );
			}
			
			if(this.queryType == 'recs')
				this.queryString = 'http://recs.cxense.com/api/recommendation/' + this.siteId + '?' + 'matching_mode=' + this.matchingMode + '&';
			else if(this.queryType == 'search')
				this.queryString = 'http://sitesearch.cxense.com/api/search/' + this.siteId + '?';
			
			this.queryString += queryArrayClean.join('&');

			this.queryString += '&media=json';
		}
		// Para debuggear el query (URL, devuelve JSON)
		// console.log(this.queryString);
	}

}