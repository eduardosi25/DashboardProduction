jQuery(document).ready(function(){
  jQuery('#main-menu > ul > li.last > a').removeAttr('href');
  jQuery('#main-menu > ul > li.last').append('<span class="proximamente" style="font-size: 8px; padding: 0px; margin: 0px; position: absolute; top: 30px; right: 30px;">Próximamente</span></li>');
  jQuery('.ibimage').parent('p').css({'text-align':'center'});
  jQuery('.node-full .field-name-body iframe').parent('p').css({'text-align':'center'});
  jQuery('.node-full .field-name-body img').parent('p').css({'text-align':'center'});
  jQuery('.view-taxonomy-term .field-name-field-image > .field-items').addClass('float-shadow').css({'width':'320px'});
  jQuery('ul.pager').parent('div.item-list').css({"display":"table", "margin":"0 auto", "clear":"both"});
  jQuery('ul.pager').css({"display":"table-cell"});
});
