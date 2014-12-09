/**
 * @author Sergio Castillo
 */

jQuery(document).ready(function () {
    //Activado dinamico de los subcanales
    jQuery("#edit-gmc-data-source").change(function () {
        mode = jQuery(this).val();
        if (mode == 2) {
            jQuery("#edit-gmc-site").val("hub").change();
        }
    });
});