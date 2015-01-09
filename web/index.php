<!DOCTYPE html>
<html lang="es">
    <meta name="charset" content="utf-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1, minimum-scale=1, user-scalable=no" />
    <meta name="language" content="es" />
    <meta name="robots" content="index,follow,noarchive" />        

    <title>Home | InventMx</title>

    <link rel="stylesheet" type="text/css" href="/css/globals_style.css">

</head>
<body>
    <header>
        <div class="wrapper-header">
            <div class="wrapper-site-logo left">
                <a href="/">
                    <span class="site-invent block"></span>
                </a>                    
                <h1 class="none">Inventmx</h1>
            </div>
            <ul class="left">
                <li class="left inline-block">
                    <a class="none-decoration" href="/">AUDIENCIAS Y CONTENIDOS</a>
                </li>
                <li class="left inline-block">
                    <a class="none-decoration" href="/">MARKETERS</a>
                </li>
                <li class="left inline-block">
                    <a class="none-decoration" href="/">RED DE VIDEO</a>
                </li>
                <li class="left inline-block">
                    <a class="none-decoration" href="/">CASO DE ÉXITO</a>
                </li>
                <li class="left inline-block">
                    <a class="none-decoration" href="/">AFILIATE</a>
                </li>
                <li class="left inline-block">
                    <a class="none-decoration" href="/">ANUNCIATE</a>
                </li>
                <span class="clear block"></span>
            </ul>                
            <div class="clear"></div>
        </div>
    </header>

    <div id="wrapper-page-site"></div>

    <footer>
        <div class="footer-content-site-invent">
            <div class="footer-site-invent"></div>
        </div>
        <p class="center">
            Bucareli No. 1 Col. Centro, delegación Cuauhtémoc, C.P. 06000, México
        </p>

    </footer>    
    
    <script type="text/javascript" src="js/libs/inventmx_libs.min.js"></script>
    <script type="text/javascript" src="js/site/alls.js"></script>
    <script type="text/javascript" src="js/site/view.js"></script>
    <script type="text/javascript" src="js/site/routing.js"></script>
</body>
</html>

<?php
 /*$rutafisica = "data/home/home.json";

  $data_center = array();

  $data_center["data"]["sections"]["0"]["name"] = "RED DE VIDEOS";
  $data_center["data"]["sections"]["0"]["items"]["0"]["image"] = "/img/home/global/Talento.png"; 
  $data_center["data"]["sections"]["0"]["items"]["0"]["name_editor"] = "Ana Dominguez";
  $data_center["data"]["sections"]["0"]["items"]["0"]["title"] = "Tips de Belleza";  
  $data_center["data"]["sections"]["0"]["items"]["0"]["url"] = "/";  
  $data_center["data"]["sections"]["0"]["items"]["1"]["image"] = "/img/home/global/Talento.png"; 
  $data_center["data"]["sections"]["0"]["items"]["1"]["name_editor"] = "Ana Dominguez";
  $data_center["data"]["sections"]["0"]["items"]["1"]["title"] = "Tips de Belleza";
  $data_center["data"]["sections"]["0"]["items"]["1"]["url"] = "/";  
  $data_center["data"]["sections"]["0"]["items"]["2"]["image"] = "/img/home/global/Talento.png"; 
  $data_center["data"]["sections"]["0"]["items"]["2"]["name_editor"] = "Ana Dominguez";
  $data_center["data"]["sections"]["0"]["items"]["2"]["title"] = "Tips de Belleza";  
  $data_center["data"]["sections"]["0"]["items"]["2"]["url"] = "/";  
  $data_center["data"]["sections"]["0"]["items"]["3"]["image"] = "/img/home/global/Talento.png"; 
  $data_center["data"]["sections"]["0"]["items"]["3"]["name_editor"] = "Ana Dominguez";
  $data_center["data"]["sections"]["0"]["items"]["3"]["title"] = "Tips de Belleza";
  
  $data_center["data"]["sections"]["0"]["items"]["4"]["image"] = "/img/home/global/Talento.png"; 
  $data_center["data"]["sections"]["0"]["items"]["4"]["name_editor"] = "Ana Dominguez";
  $data_center["data"]["sections"]["0"]["items"]["4"]["title"] = "Tips de Belleza";  
  $data_center["data"]["sections"]["0"]["items"]["4"]["url"] = "/";  
  $data_center["data"]["sections"]["0"]["items"]["5"]["image"] = "/img/home/global/Talento.png"; 
  $data_center["data"]["sections"]["0"]["items"]["5"]["name_editor"] = "Ana Dominguez";
  $data_center["data"]["sections"]["0"]["items"]["5"]["title"] = "Tips de Belleza";  
  $data_center["data"]["sections"]["0"]["items"]["5"]["url"] = "/";  
  $data_center["data"]["sections"]["0"]["items"]["6"]["image"] = "/img/home/global/Talento.png"; 
  $data_center["data"]["sections"]["0"]["items"]["6"]["name_editor"] = "Ana Dominguez";
  $data_center["data"]["sections"]["0"]["items"]["6"]["title"] = "Tips de Belleza";  
  $data_center["data"]["sections"]["0"]["items"]["6"]["url"] = "/";  
  $data_center["data"]["sections"]["0"]["items"]["7"]["image"] = "/img/home/global/Talento.png"; 
  $data_center["data"]["sections"]["0"]["items"]["7"]["name_editor"] = "Ana Dominguez";
  $data_center["data"]["sections"]["0"]["items"]["7"]["title"] = "Tips de Belleza";  
  $data_center["data"]["sections"]["0"]["items"]["7"]["url"] = "/";  
  
  $data_center["data"]["sections"]["0"]["items"]["8"]["image"] = "/img/home/global/Talento.png"; 
  $data_center["data"]["sections"]["0"]["items"]["8"]["name_editor"] = "Ana Dominguez";
  $data_center["data"]["sections"]["0"]["items"]["8"]["title"] = "Tips de Belleza";  
  $data_center["data"]["sections"]["0"]["items"]["8"]["url"] = "/";  
  $data_center["data"]["sections"]["0"]["items"]["9"]["image"] = "/img/home/global/Talento.png"; 
  $data_center["data"]["sections"]["0"]["items"]["9"]["name_editor"] = "Ana Dominguez";
  $data_center["data"]["sections"]["0"]["items"]["9"]["title"] = "Tips de Belleza";  
  $data_center["data"]["sections"]["0"]["items"]["9"]["url"] = "/";  
  $data_center["data"]["sections"]["0"]["items"]["10"]["image"] = "/img/home/global/Talento.png"; 
  $data_center["data"]["sections"]["0"]["items"]["10"]["name_editor"] = "Ana Dominguez";
  $data_center["data"]["sections"]["0"]["items"]["10"]["title"] = "Tips de Belleza";  
  $data_center["data"]["sections"]["0"]["items"]["10"]["url"] = "/";  
  $data_center["data"]["sections"]["0"]["items"]["11"]["image"] = "/img/home/global/Talento.png"; 
  $data_center["data"]["sections"]["0"]["items"]["11"]["name_editor"] = "Ana Dominguez";
  $data_center["data"]["sections"]["0"]["items"]["11"]["title"] = "Tips de Belleza";  
  $data_center["data"]["sections"]["0"]["items"]["11"]["url"] = "/";  
  
  $data_center["data"]["sections"]["1"]["name"] = "LA RED INVENT";
  $data_center["data"]["sections"]["1"]["items"]["0"]["image"] = "/";  
  $data_center["data"]["sections"]["1"]["items"]["0"]["site"] = "Excelsior";  
  $data_center["data"]["sections"]["1"]["items"]["0"]["sumary"] = "Portal de noticias líder en México con toda la información nacional y del mundo. Entérate en tiempo real de la vida pública, política de espectáculos, deportes, videos y más…"; 
  $data_center["data"]["sections"]["1"]["items"]["1"]["image"] = "/";  
  $data_center["data"]["sections"]["1"]["items"]["1"]["site"] = "Imagen Radio";  
  $data_center["data"]["sections"]["1"]["items"]["1"]["sumary"] = "Sitio web de la estación número 1 de la radio hablada en México. Sitio de noticias, finanza, negocios, deportes, vida, música y curiosidades.";  
  

  file_put_contents($rutafisica, json_encode($data_center)); */
?>

