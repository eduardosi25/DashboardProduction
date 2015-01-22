<!DOCTYPE html>
<html lang="es">
    <meta name="charset" content="utf-8" />    
        
    <link rel="canonical" href="http://www.inventmx.com" />
    
    <link rel="shortcut icon" href="/web/img/favicons/invent_16x16.ico" />
    <link rel="shortcut icon" href="/web/img/favicons/invent_32x32.ico" />
    <link rel="apple-touch-icon" sizes="57x57" href="/web/img/favicons/apple-touch-icon-57x57.png" />
    <link rel="apple-touch-icon" sizes="72x72" href="/web/img/favicons/apple-touch-icon-72x72.png" />
    <link rel="apple-touch-icon" sizes="114x114" href="/web/img/favicons/apple-touch-icon-114x114.png" />
    
    <meta name="description" content="Inventmx es la comunidad de sitios mas grande de mexico, acercamos personas con perfiles similares mediante el uso natural del Internet" />
    <!-- meta facebook -->
    <meta property="og:site_name" content="InventMX" />
    <meta property="og:title" content="InventMX" />
    <meta property="og:description" content="Inventmx es la comunidad de sitios mas grande de mexico, acercamos personas con perfiles similares mediante el uso natural del Internet"/>
    <meta property="og:url" content="http://www.inventmx.com" />
    <meta property="og:type" content="website" />
    <meta property="og:image" content="/web/img/favicons/mstile-150x150.png" />
        
    <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1, minimum-scale=1, user-scalable=no" />
    <meta name="language" content="es" />
    <meta name="robots" content="index,follow,noarchive" />        

    <title>Home | InventMx</title>

    <link rel="stylesheet" type="text/css" href="/web/css/globals_style.css">

</head>
<body class="relative">
    
    <div id="wrapper-loading-layout">
        <img class="gif" src="/web/img/ajax-loader.gif">
    </div>
    
    <header>
        <div class="wrapper-header relative">
            <div class="wrapper-site-logo left">
                <a href="/#">
                    <span class="site-invent block"></span>
                </a>                    
                <h1 class="none">Inventmx</h1>
            </div>
            
            <div class="wrapper-main right none">
                    <span class="main-center block"></span>
            </div>
            
            <ul class="left">
                <li class="left inline-block">
                    <a class="audiencias-y-contenidos none-decoration" href="/#audiencias-y-contenidos">AUDIENCIAS Y CONTENIDOS</a>
                </li>
                <li class="left inline-block">
                    <a class="marketers none-decoration" href="/#marketers">MARKETERS</a>
                </li>
                <li class="left inline-block">
                    <a class="red-de-video none-decoration" href="/#red-de-video">RED DE VIDEO</a>
                </li>
                <li class="left inline-block">
                    <a class="caso-de-exito none-decoration" href="/#caso-de-exito">CASO DE ÉXITO</a>
                </li>
                <li class="left inline-block">
                    <a class="afiliate none-decoration" href="/#afiliate">AFÍLIATE</a>
                </li>
                <li class="left inline-block">
                    <a class="anunciate none-decoration" href="/#anunciate">ANÚNCIATE</a>
                </li>
                <span class="clear block"></span>
            </ul>                
            <div class="clear"></div>
        </div>
    </header>
    
    <div id="global-page">
        <div id="wrapper-page-site" class="relative"></div>
    </div>    

    <footer>
        <div class="footer-content-site-invent">
            <div class="footer-site-invent"></div>
        </div>
        <p class="center">
            Bucareli No. 1 Col. Centro, Delegación Cuauhtémoc. C.P. 06600. México D.F
        </p>

    </footer>    
    
    <script type="text/javascript" src="/web/js/libs/inventmx_libs.min.js"></script>
    <script type="text/javascript" src="/web/js/site/alls.js"></script>
    <script type="text/javascript" src="/web/js/site/view.js"></script>
    <script type="text/javascript" src="/web/js/site/routing.js"></script>
</body>
</html>

<?php
 /*$rutafisica = "web/data/home/home.json";

  $data_center = array();

  $data_center["data"]["sections"]["0"]["name"] = "RED DE VIDEOS";
  $data_center["data"]["sections"]["0"]["items"]["0"]["image"] = "/web/img/home/global/Talento.png"; 
  $data_center["data"]["sections"]["0"]["items"]["0"]["name_editor"] = "Ana Dominguez";
  $data_center["data"]["sections"]["0"]["items"]["0"]["title"] = "Tips de Belleza";  
  $data_center["data"]["sections"]["0"]["items"]["0"]["url"] = "/#perfil/ana-dominguez";  
  $data_center["data"]["sections"]["0"]["items"]["1"]["image"] = "/web/img/home/global/Talento.png"; 
  $data_center["data"]["sections"]["0"]["items"]["1"]["name_editor"] = "Ana Dominguez";
  $data_center["data"]["sections"]["0"]["items"]["1"]["title"] = "Tips de Belleza";
  $data_center["data"]["sections"]["0"]["items"]["1"]["url"] = "/#perfil/ana-dominguez";  
  $data_center["data"]["sections"]["0"]["items"]["2"]["image"] = "/web/img/home/global/Talento.png"; 
  $data_center["data"]["sections"]["0"]["items"]["2"]["name_editor"] = "Ana Dominguez";
  $data_center["data"]["sections"]["0"]["items"]["2"]["title"] = "Tips de Belleza";  
  $data_center["data"]["sections"]["0"]["items"]["2"]["url"] = "/#perfil/ana-dominguez";  
  $data_center["data"]["sections"]["0"]["items"]["3"]["image"] = "/web/img/home/global/Talento.png"; 
  $data_center["data"]["sections"]["0"]["items"]["3"]["name_editor"] = "Ana Dominguez";
  $data_center["data"]["sections"]["0"]["items"]["3"]["title"] = "Tips de Belleza";
  $data_center["data"]["sections"]["0"]["items"]["3"]["url"] = "/#perfil/ana-dominguez";  
  
  $data_center["data"]["sections"]["0"]["items"]["4"]["image"] = "/web/img/home/global/Talento.png"; 
  $data_center["data"]["sections"]["0"]["items"]["4"]["name_editor"] = "Ana Dominguez";
  $data_center["data"]["sections"]["0"]["items"]["4"]["title"] = "Tips de Belleza";  
  $data_center["data"]["sections"]["0"]["items"]["4"]["url"] = "/#perfil/ana-dominguez";  
  $data_center["data"]["sections"]["0"]["items"]["5"]["image"] = "/web/img/home/global/Talento.png"; 
  $data_center["data"]["sections"]["0"]["items"]["5"]["name_editor"] = "Ana Dominguez";
  $data_center["data"]["sections"]["0"]["items"]["5"]["title"] = "Tips de Belleza";  
  $data_center["data"]["sections"]["0"]["items"]["5"]["url"] = "/#perfil/ana-dominguez";  
  $data_center["data"]["sections"]["0"]["items"]["6"]["image"] = "/web/img/home/global/Talento.png"; 
  $data_center["data"]["sections"]["0"]["items"]["6"]["name_editor"] = "Ana Dominguez";
  $data_center["data"]["sections"]["0"]["items"]["6"]["title"] = "Tips de Belleza";  
  $data_center["data"]["sections"]["0"]["items"]["6"]["url"] = "/#perfil/ana-dominguez";  
  $data_center["data"]["sections"]["0"]["items"]["7"]["image"] = "/web/img/home/global/Talento.png"; 
  $data_center["data"]["sections"]["0"]["items"]["7"]["name_editor"] = "Ana Dominguez";
  $data_center["data"]["sections"]["0"]["items"]["7"]["title"] = "Tips de Belleza";  
  $data_center["data"]["sections"]["0"]["items"]["7"]["url"] = "/#perfil/ana-dominguez";  
  
  $data_center["data"]["sections"]["0"]["items"]["8"]["image"] = "/web/img/home/global/Talento.png"; 
  $data_center["data"]["sections"]["0"]["items"]["8"]["name_editor"] = "Ana Dominguez";
  $data_center["data"]["sections"]["0"]["items"]["8"]["title"] = "Tips de Belleza";  
  $data_center["data"]["sections"]["0"]["items"]["8"]["url"] = "/#perfil/ana-dominguez";  
  $data_center["data"]["sections"]["0"]["items"]["9"]["image"] = "/web/img/home/global/Talento.png"; 
  $data_center["data"]["sections"]["0"]["items"]["9"]["name_editor"] = "Ana Dominguez";
  $data_center["data"]["sections"]["0"]["items"]["9"]["title"] = "Tips de Belleza";  
  $data_center["data"]["sections"]["0"]["items"]["9"]["url"] = "/#perfil/ana-dominguez";  
  $data_center["data"]["sections"]["0"]["items"]["10"]["image"] = "/web/img/home/global/Talento.png"; 
  $data_center["data"]["sections"]["0"]["items"]["10"]["name_editor"] = "Ana Dominguez";
  $data_center["data"]["sections"]["0"]["items"]["10"]["title"] = "Tips de Belleza";  
  $data_center["data"]["sections"]["0"]["items"]["10"]["url"] = "/#perfil/ana-dominguez";  
  $data_center["data"]["sections"]["0"]["items"]["11"]["image"] = "/web/img/home/global/Talento.png"; 
  $data_center["data"]["sections"]["0"]["items"]["11"]["name_editor"] = "Ana Dominguez";
  $data_center["data"]["sections"]["0"]["items"]["11"]["title"] = "Tips de Belleza";  
  $data_center["data"]["sections"]["0"]["items"]["11"]["url"] = "/#perfil/ana-dominguez";  
  
  $data_center["data"]["sections"]["1"]["name"] = "LA RED INVENT";
  $data_center["data"]["sections"]["1"]["items"]["0"]["image"] = "/";  
  $data_center["data"]["sections"]["1"]["items"]["0"]["site"] = "Excelsior";  
  $data_center["data"]["sections"]["1"]["items"]["0"]["sumary"] = "Portal de noticias líder en México con toda la información nacional y del mundo. Entérate en tiempo real de la vida pública, política de espectáculos, deportes, videos y más…"; 
  $data_center["data"]["sections"]["1"]["items"]["1"]["image"] = "/";  
  $data_center["data"]["sections"]["1"]["items"]["1"]["site"] = "Imagen Radio";  
  $data_center["data"]["sections"]["1"]["items"]["1"]["sumary"] = "Sitio web de la estación número 1 de la radio hablada en México. Sitio de noticias, finanza, negocios, deportes, vida, música y curiosidades.";    

  file_put_contents($rutafisica, json_encode($data_center)); */


/* caso  de exito */
/*  $rutafisica = "web/data/caso-de-exito/nodes.json";
  $data_center = array();

  $data_center["data"]["sections"]["0"]["name"] = "Casos de éxito";
  $data_center["data"]["sections"]["0"]["items"]["0"]["objetive_cliente"] = ""; 
  $data_center["data"]["sections"]["0"]["items"]["0"]["tender_invent"] = "";  
  $data_center["data"]["sections"]["0"]["items"]["0"]["url"] = "/";*/
  
  

  //file_put_contents($rutafisica, json_encode($data_center));


?>

