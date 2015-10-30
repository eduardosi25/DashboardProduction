jQuery(document).ready(function(){
  jQuery('#edit-gimrh-personal-birthdate').mask("99/99/9999",{placeholder:"dd/mm/aaaa"});
  jQuery('#edit-gimrh-personal-phone').mask("99-99999999",{placeholder:"xx-xxxxxxxx"});
  jQuery('#edit-gimrh-experience-0-format').remove();
  if(top!=window){
    var eventMethod = window.addEventListener ? "addEventListener" : "attachEvent";
    var eventer = window[eventMethod];
    var messageEvent = eventMethod == "attachEvent" ? "onmessage" : "message";
    // Listen to message from the parent window
    eventer(messageEvent,function(e) {
      console.log("children.postMessage.received:", e.data);
      if(e.origin == "http://local.rsvponline.mx"){
        if(e.data=="hide_alert"){
          window.scrollTo(0,0);
          setTimeout(e.data+"()", 3000);
          console.log("Children received message: ", e.data);
        }
      }
    },false);

    //We are on iframe
    jQuery('#edit-submit').bind('click',function(){
      var data = {
        action : 'submit',
        height : jQuery('body').outerHeight(),
      };
      parent.postMessage(data,'*');
      console.log('parent.postMessage.sent');
    });
  }
});




function hide_alert(){
  jQuery('.alert').hide();
}

var validate_fields={
  _nKeypress : window.Event ? true : false,
  entero : function(evt){
    var key = this._nKeypress ? evt.which : evt.keyCode;
    return (key <= 13 || (key >= 48 && key <= 57));
  },
  flotante : function(evt){
    var key = this._nKeypress ? evt.which : evt.keyCode;
    return (key <= 13 || (key >= 48 && key <= 57) || key == 46);
  },
  first_name:function(evt){
    var key = this._nKeypress ? evt.which : evt.keyCode;
    return (key <= 13 ||(key >= 65 && key <= 90) || (key >= 97 && key <= 122) || (key ==32));
  },
  alfanumerico : function(evt){
    var key = this._nKeypress ? evt.which : evt.keyCode;
    return (key <= 12 || (key >= 48 && key <= 57) || ((key >= 65 && key <= 90) || (key >= 97 && key <= 122)) || (key==193 || key==201 || key==205 || key==209 || key==211 || key==218 || key==225 || key==233 || key==237 || key==241 || key==243 || key==250 || key==95 || key==45));
  },
  string_email : function(evt){
    var key = this._nKeypress ? evt.which : evt.keyCode;
    return (key <= 13 || (key >= 48 && key <= 57) || (key >= 65 && key <= 90) || (key >= 97 && key <= 122) || (key==64 || key==46 || key==45 || key==95));
  },
  nickname : function(evt){
    var key = this._nKeypress ? evt.which : evt.keyCode;
    return (key <= 13 || (key >= 48 && key <= 57) || (key >= 65 && key <= 90) || (key >= 97 && key <= 122) || (key==64 || key==46 || key==45));
  },
  alfanumericosignos : function(evt){
    var key = this._nKeypress ? evt.which : evt.keyCode;
    return (key <= 13 || (key >= 48 && key <= 57) || (key >= 65 && key <= 90) || (key >= 97 && key <= 122) || (key >= 40 && key <= 47) || (key==32 || key==36 || key==38 || key==58 || key==59 || key==64 || key==91 || key==92 || key==93 || key==95));
  },
  password : function(evt){
    var key = this._nKeypress ? evt.which : evt.keyCode;
    return (key <= 13 || (key >= 48 && key <= 57) || (key >= 65 && key <= 90) || (key >= 97 && key <= 122) || (key >= 40 && key <= 47) || (key==32 || key==36 || key==38 || key==58 || key==59 || key==64 || key==91 || key==92 || key==93 || key==95 || key==36 || key==33 || key==126|| key==35 || key==37 || key==94  || key==61 || key==123 || key==125 || key==124 || key==63 || key==164));
  },
  alfanumericosignos_sinenter: function(evt){
    var key = this._nKeypress ? evt.which : evt.keyCode;
    return (key <= 13 || (key >= 48 && key <= 57) || (key >= 65 && key <= 90) || (key >= 97 && key <= 122) || (key >= 40 && key <= 47) || (key==32 || key==36 || key==38 || key==58 || key==59 || key==64 || key==91 || key==92 || key==93 || key==95));
  },
  email : function(str_email){
    var filtrar=/^\w+([\.-]?\w+)*@\w+([\.-]?\w+)*(\.\w{2,3})$/;
    if (filtrar.test(str_email)){
      return true;
    }else{
      return false;
    }
  }
};
