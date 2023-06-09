<?php

/**
 * @file
 * Default theme implementation for the toggle buttons in EUCCX block's tabs.
 *
 * Available variables:
 * - $title: the text next to the Toggle Switch
 * - $toggle_id: an id for the specific toggle based on who created it. This can
 *   be used to theme the switches separately from each other.
 * - $has_input: variable to determine whether an input button should be
 *   included. Useful for the case of Required Cookies where the user is not
 *   given the option to disable them.
 *
 *   Important Note: The inputs are identified by their name in the javascript
 *   code of this module. If you change the _name=""_ part of this template,
 *   stuff WILL break and puppies MAY cry.
 */
?>

<div class="euccx-toggle-wrapper euccx-toggle-wrapper-<?php print($toggle_id); ?>">
  <div class="euccx-label euccx-label-<?php print($toggle_id); ?>">
    <h3><?php print($title); ?></h3>
  </div>
  <div class="euccx-switch-wrapper euccx-switch-wrapper-<?php print($toggle_id);?>">
    <label class="euccx-switch euccx-switch-<?php print($toggle_id); ?>">
      <?php if ($has_input): ?>
      <input class="euccx-input" id="euccx-input-<?php print($toggle_id); ?>" name="euccx-input-<?php print($toggle_id); ?>" type="checkbox">
      <?php endif; ?>
      <span class="euccx-slider euccx-round euccx-slider-<?php print($toggle_id); ?>"></span>
    </label>
  </div>
</div>
