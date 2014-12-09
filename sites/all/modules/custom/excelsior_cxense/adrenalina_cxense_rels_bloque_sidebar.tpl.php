<div id="adrenalina-cxense-rels-widget" class="mb2">
	<!-- cxense -->
	<script id="cxense_rels" type="text/html">
	<ul id="cxense-rels-list">
	{{#items}}
	    <li class="cxense-rels-list-item">
	        <a class="cxense-rels-list-item-link title-hover" href="{{click_url}}">
	            <img class="cxense-rels-list-item-image mr10" src="{{imx-img-grande200px}}" alt="{{title}}">
	            <span class="cxense-rels-list-item-title">{{title}}</span>
	        </a>
	    </li>
	{{/items}}
	</ul>
	</script>

	<script>

	jQuery( document ).ready(function( $ ) {
			var url = 'http://api.cxense.com/public/widget/data?json=%7B%22widgetId%22%3A%2236125c383f86d37fa90f13401600d0ada254dcfa%22%7D&callback=?';
			$.ajax({
			   type: 'GET',
			    url: url,
			    async: false,
			    jsonpCallback: 'jsonCallback',
			    contentType: "application/json",
			    dataType: 'jsonp',
			    success: function(json) {
			    	$.each(json.response.items,function(){
			    		if(/^http:\/\/(www\.)excelsior\.com\.mx\/\.*/.test(this["imx-img-grande200px"]))
			    			this["imx-img-grande200px"]	= 'http://a4abc406deb0a8793cfc-8f09eb7e0d12d12e8088bd883ec972c9.r81.cf2.rackcdn.com/imagendefault.jpg';
			    	});			    	
			      $('#cxense-rels-container').html(ich.cxense_rels(json.response, true));
			    },
			    error: function(e) {
			       //console.log(e.message);
			    }
			});
	});

	</script>
	<div class="widget-title">
	    Te puede interesar...
	</div>
	<div id="cxense-rels-container"></div>
	<a id="cxense-rels-ver-mas">Ver más...</a>

	<!-- /cxense -->
	<div class="clear"></div>
</div>