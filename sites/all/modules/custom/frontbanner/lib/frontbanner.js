var sTime = new Date().getTime();
var countDown = 10;

function closePrehome(){
  var expireCookie=calculate_time_expiring_cookies('1m');
  if(typeof(jQuery.cookie)!=='undefined'){
    jQuery.cookie("prehome",'{"status":"1","expire":"'+expireCookie+'"}',{"path":"/"});
  }else{
    var strCookie='"prehome={"status":"1","expire":"1411406743"}; "path"="/"';
    document.cookie=encodeURI(strCookie);
  }
  jQuery('#frontbanner-page').hide();
}

function UpdateTime() {
  var cTime = new Date().getTime();
  var diff = cTime - sTime;
  var seconds = countDown - Math.floor(diff / 1000);
  if (seconds >= 0) {
    jQuery("#seconds").text(seconds);
  } else {
    jQuery("#prehome-close").click();
    clearInterval(counter);
  }
}

function calculate_time_expiring_cookies(expire){
  if(!expire)
    return 0;

  //Valores posibles (segundos, minutos, horas, dias)
  //usando la primer letra de cada palabra para el cálculo
  //s = secs :: m = mins :: h = hours :: d = days
  var timestamp=Math.round(new Date().getTime()/1000);
  var regExpFull=/[0-9]+(s|m|h|d)/;
  var regExpNumber=/[0-9]+/;
  var regExpPeriod=/[smhd]/;
  if(expire.match(regExpFull)){
    var number=expire.match(regExpNumber);
    var period=expire.match(regExpPeriod);
    if(period=='s'){
      timestamp=timestamp+parseInt(number);
    }
    if(period=='m'){
      timestamp=timestamp+parseInt(number)*60;
    }
    if(period=='h'){
      timestamp=timestamp+parseInt(number)*60*60;
    }
    if(period=='d'){
      timestamp=timestamp+parseInt(number)*60*60*24;
    }
  }
  return timestamp;
}