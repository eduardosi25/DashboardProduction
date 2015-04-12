(function($, Drupal)
{
  Drupal.behaviors.autoFocus = {
    attach:function()
    {
      $(".form-text:first").focus();
    }
  };
}(jQuery, Drupal));
