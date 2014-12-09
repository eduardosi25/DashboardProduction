<?php
function hf_wide_profile($item=null){
  $html='
<div class="'.str_replace('_', '-', $item['style_wide']).' left blackColor titilliumWeb content">
  <div class="spriteIcons voidSeparator"></div>
  <div class="'.str_replace('_', '-', $item['style_wide']).'-content relative">
    <a href="'.url($item['path'], array('absolute'=>true)).'">
      <span class="wrapImg">
        <img class="lazy" data-original="'.file_create_url($item['image']['uri']).'" alt="'.$item['image']['alt'].'" />
      </span>
    </a>
    <div class="spriteIcons bgPaperRight right centertext">
      <p class="colorLink heraBig">'.$item['canal'].'</p>
      <p class="titleItem">
        <a href="'.url($item['path'], array('absolute'=>true)).'">'.$item['title'].'</a>
      </p>
      <p class="teaserItem tinos italic">'.$item['summary'].'</p>
    </div>
  </div>
</div>
<div class="clear"></div>
';
  return $html;
}
function hf_wide_background($item=null){
  $html='
<div class="'.str_replace('_', '-', $item['style_wide']).'">
  <div class="spriteIcons voidSeparator"></div>
  <div class="sectionBlockLarge left relative">
    <a href="'.url($item['path'], array('absolute'=>true)).'">
      <span class="dblock wrapImg left">
        <img class="lazy" data-original="'.file_create_url($item['image']['uri']).'" alt="'.$item['image']['alt'].'" />
      </span>
    </a>
    <div class="spriteIcons bgPaperRight centertext right absolute">
      <div class="bgPaperContent">
        <a href="'.url($item['path'], array('absolute'=>true)).'">
          <span class="titleItem blackColor titilliumWeb centertext">'.$item['title'].'</span>
          <div class="clear"></div>
          <br />
          <span class="teaserItem tinos centertext italic blackColor">'.$item['summary'].'</span>
        </a>
      </div>
    </div>
  </div>
</div>
<div class="clear"></div>
';
  return $html;
}
/**********************************************************************************************************/
/**********************************************************************************************************/
/**********************************************************************************************************/
function rsvp_grid_iwant($items=null){
  $html='
<div class="rsvp-grid-iwant" class="clear">

  <div id="loQuieroLeft" class="left centertext">';
   
  $count=1;
  foreach($items as $item){
    if($count==1){
      $html.='
    <div class="colorLink heraBig">'.$item['canal'].'</div>
    <div class="sectionBlockLarge centertext">
      <a href="'.url($item['path'], array('absolute'=>true)).'">
        <span class="titleItem blackColor titilliumWeb centertext">'.$item['title'].'</span>
        <span class="dblock wrapImg">
          <img class="lazy" data-original="'.file_create_url($item['image']['uri']).'" alt="'.$item['image']['alt'].'" />
        </span>
        <span class="teaserItem tinos centertext italic blackColor">'.$item['summary'].'</span>
      </a>
    </div>
  </div>
  <div id="loQuieroRight" class="right">
    <ul id="loQuieroListRight">';
    }else{
      $html.='
      <li class="itemList left">
        <div class="itemContent">
          <a href="'.url($item['path'], array('absolute'=>true)).'">
            <span class="dblock wrapImg">
              <img class="lazy" data-original="'.file_create_url($item['image']['uri']).'" alt="'.$item['image']['alt'].'" />
            </span>
            <span class="titleItem titilliumWeb blackColor centertext">'.$item['title'].'</span>
          </a>
        </div>
      </li>
      ';
    }
    $count++;
  }
  $html.='
    </ul>
  </div>
</div>
<div class="clear"></div>
  ';

  return $html; 
}
function rsvp_grid_profile($items=null){
  $html='
<div class="rsvp-grid-profile">
  <div class="spriteIcons voidSeparator"></div>
  <div class="sectionBlockLarge centertext">';
  $count=1;
  foreach($items as $item){
    if($count==1){
      $html.='
    <div class="colorLink heraBig section">'.$item['canal'].'</div>
    <a href="'.url($item['path'], array('absolute'=>true)).'">
        <span class="titleItem blackColor titilliumWeb centertext">'.$item['title'].'</span>
    </a>
    <ul class="listImgs">';
    }else{
      $html.='
      <li class="itemList">
      <a href="'.url($item['path'], array('absolute'=>true)).'">
          <span class="dblock wrapImg">
            <img class="lazy" data-original="'.file_create_url($item['image']['uri']).'" alt="'.$item['image']['alt'].'" />
          </span>
          <span class="titleItem titilliumWeb blackColor centertext">'.$item['title'].'</span>
        </a>
      </li>
      ';
    }
    $count++;
  }
  $html.='
    </ul>
  </div>
</div>
<div class="clear"></div>
  ';
  
  return $html;
}
function rsvp_grid_special($items=null){
  $html='
  <div class="rsvp-grid-special" class="clear">
    <div class="spriteIcons voidSeparator"></div>
  ';
  $count=1;
  foreach($items as $item){
    if($count==1){
      $html.='
    <div class="sectionBlockLarge">
      <a href="'.url($item['path'], array('absolute'=>true)).'">
          <span class="mainImageBlock dblock wrapImg">
              <img class="lazy" data-original="'.file_create_url($item['image']['uri']).'" alt="'.$item['image']['alt'].'" />
          </span>
      </a>
      <div class="columnRight right centertext">
          <div class="colorLink heraBig">'.$item['canal'].'</div>
          <span class="titleItem blackColor titilliumWeb centertext">'.$item['title'].'</span>
          <ul class="listColumnRight">
      ';
    }else{
      $html.='
          <li class="itemList left relative">
              <a href="'.url($item['path'], array('absolute'=>true)).'">
                  <span class="dblock wrapImg">
                      <img class="lazy" data-original="'.file_create_url($item['image']['uri']).'" alt="'.$item['image']['alt'].'" />
                  </span>
                  <span class="titleWrapp spriteIcons listonBg dblock absolute">
                      <span class="titleItem titilliumWeb whiteColor dblock ">'.$item['title'].'</span>
                      <span class="cornerTop"></span>
                      <span class="cornerBottom"></span>
                  </span>
              </a>
          </li>';
    }
    $count++;
  }
  $html.='
          </ul>
      </div>
  </div>
</div>
<div class="clear"></div>
';
  return $html;
}
function rsvp_grid_columns($items=null){
  $html='
<div class="rsvp-grid-columns" class="columnRight right centertext">';
  
  $count=1;
  foreach($items as $item){
    if($count==1){
      $html.='
    <div class="colorLink heraBig">'.$item['canal'].'</div>
    <a href="'.url($item['path'], array('absolute'=>true)).'">
      <span class="titleItem blackColor titilliumWeb centertext">'.$item['title'].'</span>
    </a>
    <ul class="listColumnRight">
      ';
    }else{
      $html.='
      <li class="itemList left relative">
        <a href="'.url($item['path'], array('absolute'=>true)).'">
            <span class="dblock wrapImg">
                <img class="lazy" data-original="'.file_create_url($item['image']['uri']).'" alt="'.$item['image']['alt'].'" />
            </span>
            <span class="titleWrapp spriteIcons listonBg dblock absolute">
                <span class="titleItem titilliumWeb whiteColor dblock ">'.$item['title'].'</span>
                <span class="cornerTop"></span>
                <span class="cornerBottom"></span>
            </span>
        </a>
      </li>';
    }
    $count++;
  }
  $html.='
  </ul>
</div>
<div class="clear"></div>
  ';
  return $html;
}
/*----------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------*/
function hf_small_default($item=null){
  $html='
<div class="'.str_replace('_', '-', $item['style_small']).' left centertext blackColor titilliumWeb content">
  <p class="heraBig colorLink">'.$item['canal'].'</p>
  <p class="titleItem">
    <a href="'.url($item['path'], array('absolute'=>true)).'">'.$item['title'].'</a>
  </p>
  <p class="wrapImg">
    <a href="'.url($item['path'], array('absolute'=>true)).'">
      <img class="lazy" data-original="'.file_create_url($item['image']['uri']).'" alt="'.$item['image']['alt'].'" />
    </a>
  </p>
  <p class="teaserItem tinos italic">'.$item['summary'].'</p>
</div>
<div class="clear"></div>
';
  return $html;
}
function hf_wide_default($item=null){
  $html='
<div class="'.str_replace('_', '-', $item['style_wide']).'-separator">
  <div class="spriteIcons voidSeparator"></div>
</div>
<div class="'.str_replace('_', '-', $item['style_wide']).' left centertext blackColor titilliumWeb content">
  <p class="heraBig colorLink">'.$item['canal'].'</p>
  <p class="titleItem">
    <a href="'.url($item['path'], array('absolute'=>true)).'">'.$item['title'].'</a>
  </p>
  <p class="wrapImg">
    <a href="'.url($item['path'], array('absolute'=>true)).'">
      <img class="lazy" data-original="'.file_create_url($item['image']['uri']).'" alt="'.$item['image']['alt'].'" />
    </a>
  </p>
  <p class="teaserItem tinos italic">'.$item['summary'].'</p>
</div>
<div class="clear"></div>
';
  return $html;
}
/*----------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------*/
function hf_small_ribbon_boda($item=null){
  $html='
<div class="'.str_replace('_', '-', $item['style_small']).' left centertext blackColor titilliumWeb">
  <div class="borderSeparator center-elem">
    <div class="spriteIcons bodaIcon center-elem">&nbsp;</div>
  </div>
  <div class="content">
    <p class="titleItem">
      <a href="'.url($item['path'], array('absolute'=>true)).'">'.$item['title'].'</a>
    </p>
    <p class="wrapImg">
      <a href="'.url($item['path'], array('absolute'=>true)).'">
        <img class="lazy" data-original="'.file_create_url($item['image']['uri']).'" alt="'.$item['image']['alt'].'" />
      </a>
    </p>
    <p class="teaserItem tinos italic">'.$item['summary'].'</p>
  </div>
</div>
<div class="clear"></div>
';
  return $html;
}
function hf_wide_ribbon_boda($item=null){
  $html='
<div class="'.str_replace('_', '-', $item['style_wide']).' left centertext blackColor titilliumWeb">
  <div class="borderSeparator center-elem">
    <div class="spriteIcons bodaIcon center-elem">&nbsp;</div>
  </div>
  <div class="content">
    <p class="titleItem">
      <a href="'.url($item['path'], array('absolute'=>true)).'">'.$item['title'].'</a>
    </p>
    <p class="wrapImg">
      <a href="'.url($item['path'], array('absolute'=>true)).'">
        <img class="lazy" data-original="'.file_create_url($item['image']['uri']).'" alt="'.$item['image']['alt'].'" />
      </a>
    </p>
    <p class="teaserItem tinos italic">'.$item['summary'].'</p>
  </div>
</div>
<div class="clear"></div>
';
  return $html;
}
function hf_wide_ribbon_loquiero($item=null){
  $html='
<div class="'.str_replace('_', '-', $item['style_wide']).'">
  <div class="spriteIcons blackSeparator"></div>
  <div class="spriteIcons loquieroHeader">&nbsp;</div>
  <div class="'.str_replace('_', '-', $item['style_wide']).'-content">
    <div class="arrowNext spriteIcons right cursor-pointer"></div>
    <div class="arrowPrev spriteIcons left cursor-pointer"></div>
    <div class="itemCarrusel centertext">
      <a href="'.url($item['path'], array('absolute'=>true)).'">
        <span class="dblock wrapImg">
            <img class="lazy" data-original="'.file_create_url($item['image']['uri']).'" alt="'.$item['image']['alt'].'" />
        </span>
        <span class="titleItem blackColor titilliumWeb centertext">'.$item['title'].'</span>
        <br />
        <span class="teaserItem tinos centertext italic blackColor">'.$item['summary'].'</span>
      </a>
    </div>
  </div>
</div>
<div class="clear"></div>
';
  return $html;
}
function hf_wide_ribbon_bombon($item=null){
  $html='
<div class="'.str_replace('_', '-', $item['style_wide']).'">
  <div class="spriteIcons blackSeparator"></div>
  <div class="spriteIcons bombonHeader"></div>
  <div class="sectionBlockLarge left relative">
    <a href="'.url($item['path'], array('absolute'=>true)).'">
      <span class="dblock wrapImg left">
        <img class="lazy" data-original="'.file_create_url($item['image']['uri']).'" alt="'.$item['image']['alt'].'" />
      </span>
    </a>
    <div class="spriteIcons bgPaperRight centertext right absolute">
      <div class="bgPaperContent">
        <a href="'.url($item['path'], array('absolute'=>true)).'">
          <span class="titleItem blackColor titilliumWeb centertext">'.$item['title'].'</span>
          <div class="clear"></div>
          <br />
          <span class="teaserItem tinos centertext italic blackColor">'.$item['summary'].'</span>
        </a>
      </div>
    </div>
  </div>
</div>
<div class="clear"></div>
';
  return $html;
}
function hf_wide_ribbon_socialspot($item=null){
  $html='
<div class="'.str_replace('_', '-', $item['style_wide']).' left centertext blackColor titilliumWeb content">
  <div class="spriteIcons voidSeparator"></div>
  <div class="bgSiteAux"><div class="spriteIcons socialSpotHeader"></div></div>
  <p class="titleItem">
    <a href="'.url($item['path'], array('absolute'=>true)).'">'.$item['title'].'</a>
  </p>
  <p class="wrapImg center-elem">
    <a href="'.url($item['path'], array('absolute'=>true)).'">
      <img class="lazy" data-original="'.file_create_url($item['image']['uri']).'" alt="'.$item['image']['alt'].'" />
    </a>
  </p>
  <p class="teaserItem tinos italic">'.$item['summary'].'</p>
</div>
<div class="clear"></div>
';
  return $html;
}
/*----------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------*/
function _get_html_rsvp_phrase(){
  $item=_get_item_phrase();
  
  $html='
  <div class="hf_phrase">
    <div class="spriteIcons voidSeparator"></div>
    <div class="spriteIcons phraseContent">
        <p class="phraseText titilliumWeb blackColor">'.$item['body'].'</p>
        <p class="phraseName"><a class="colorLink" href="'.str_replace('@', 'http://www.twitter.com/', $item['title']).'" target="_blank" rel="nofollow">'.$item['title'].'</a></p>
    </div>
  </div>
  <div class="clear"></div>
  ';
  
  return $html;
}
function _get_item_phrase(){
  $item = &drupal_static(__FUNCTION__);
  if (!isset($item)){
    if ($cache = cache_get('last_item_phrase')) {
      $item = $cache->data;
    }else{
      $query="select n.nid, n.title, b.body_value as body 
              from {node} n 
              inner join {field_data_body} b on b.entity_id=n.nid
              where n.type='phrase'
              order by n.created desc
              limit 1";
      $result=db_query($query);
      $item=array();
      foreach ($result as $node) {
        $item=array(
          'nid'   => $node->nid,
          'title' => $node->title,
          'body'  => strip_tags($node->body),  
        );
      }
      cache_set('last_item_phrase', $item, 'cache');
    }
  }
  return $item;
}
