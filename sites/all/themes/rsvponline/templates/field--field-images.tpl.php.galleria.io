<?php

/**
 * @file field.tpl.php
 * Default template implementation to display the value of a field.
 *
 * This file is not used and is here as a starting point for customization only.
 * @see theme_field()
 *
 * Available variables:
 * - $items: An array of field values. Use render() to output them.
 * - $label: The item label.
 * - $label_hidden: Whether the label display is set to 'hidden'.
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default values can be one or more of the
 *   following:
 *   - field: The current template type, i.e., "theming hook".
 *   - field-name-[field_name]: The current field name. For example, if the
 *     field name is "field_description" it would result in
 *     "field-name-field-description".
 *   - field-type-[field_type]: The current field type. For example, if the
 *     field type is "text" it would result in "field-type-text".
 *   - field-label-[label_display]: The current label position. For example, if
 *     the label position is "above" it would result in "field-label-above".
 *
 * Other variables:
 * - $element['#object']: The entity to which the field is attached.
 * - $element['#view_mode']: View mode, e.g. 'full', 'teaser'...
 * - $element['#field_name']: The field name.
 * - $element['#field_type']: The field type.
 * - $element['#field_language']: The field language.
 * - $element['#field_translatable']: Whether the field is translatable or not.
 * - $element['#label_display']: Position of label display, inline, above, or
 *   hidden.
 * - $field_name_css: The css-compatible field name.
 * - $field_type_css: The css-compatible field type.
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 *
 * @see template_preprocess_field()
 * @see theme_field()
 *
 * @ingroup themeable
 */
?>
<div class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <div class="galleria field-items"<?php print $content_attributes; ?>>
    <?php
    $image=new stdClass();
    foreach ($items as $delta => $item){
      $image->large=image_style_url($item['#image_style'],$item['#item']['uri']);
      $image->thumb=image_style_url('thumbnail',$item['#item']['uri']);
      $image->big=file_create_url($item['#item']['uri']);
      $image->title=isset($item['#item']['title']) && !empty($item['#item']['title']) ? $item['#item']['title']: $item['#item']['alt'];
      $image->description=isset($item['#item']['alt']) && !empty($item['#item']['alt']) ? $item['#item']['alt']: $item['#item']['title'];
    ?>
      <a href="<?php print($image->large);?>">
        <img src="<?php print($image->thumb);?>" data-big="<?php print($image->big);?>" data-description="<?php print($image->description);?>" />
      </a>
    <?php
    }
    ?>
  </div>
</div>
<script type="text/javascript">
Galleria.loadTheme('/sites/all/themes/rsvponline/js/galleria/themes/classic/galleria.classic.min.js');
Galleria.run('.galleria',{
  responsive  : true,
  wait        : true,
  _justLanded : true,
  debug       : false,
  height      : 400,
  transition  : 'fade',
  trueFullscreen : true
});
</script>
