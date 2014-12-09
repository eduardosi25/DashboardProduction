<div id="cxense-rels-widget" class="mb2">
	<!-- cxense -->
	<script id="cxense_rels" type="text/html">
	<div class="spritePlecas-sidebar widget-title">
	    te puede interesar
	</div>
	<ul id="cxense-rels-list">
	{{#items}}
	    <li class="cxense-rels-list-item">
	        <a class="cxense-rels-list-item-link title-hover" href="{{click_url}}">
	            <img class="cxense-rels-list-item-image mr1" src="{{imx-img-grande200px}}" alt="{{title}}">
	            <span class="cxense-rels-list-item-title">{{title}}</span>
	        </a>
	    </li>
	{{/items}}
	</ul>
	</script>

	<script>

	jQuery( document ).ready(function( $ ) {
			var url = 'http://api.cxense.com/public/widget/data?json=%7B%22widgetId%22%3A%22cb9b2b601feb7e5d0335823f35456982b0f1d91c%22%7D&callback=?';
			$.ajax({
			   type: 'GET',
			    url: url,
			    async: false,
			    jsonpCallback: 'bloqueRelsCallback',
			    contentType: "application/json",
			    dataType: 'jsonp',
			    success: function(json) {
			    	$.each(json.response.items,function(){
			    		if(/^http:\/\/(www\.)excelsior\.com\.mx\/\.*/.test(this["imx-img-grande200px"]))
			    			this["imx-img-grande200px"]	= 'http://8d5306c18b850ea7e0ac-65b9b7a2fa68b3c92f951010bb26a4de.r54.cf2.rackcdn.com/grande200px_default.jpg';
			    	});
			      $('#cxense-rels-container').html(ich.cxense_rels(json.response, true));
			    },
			    error: function(e) {
			       //console.log(e.message);
			    }
			});
	});

	</script>
	<div id="cxense-rels-container"></div>

	<!-- /cxense -->
	<div class="clear"></div>
</div>