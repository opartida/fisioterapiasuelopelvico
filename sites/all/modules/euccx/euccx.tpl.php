<?php

/**
 * @file
 * Default theme implementation to display EUCCX's block.
 *
 * Available variables:
 * - $bare_css: whether the user selected to use minimal css. May seem redundant
 *   but a designer may choose to add or remove specific classes or markup based
 *   on what the administrator has chosen.
 * - $save: the button text for the save button
 * - $privacy_page: whether the privacy page is selected to be displayed
 * - $privacy_page_title: the tab title for the privacy page
 * - $privacy_page_contents: the contents of the privacy page
 * - $required_cookies: whether the required cookies part is enabled
 * - $required_cookies_title: the tab title for the required cookies
 * - $required_cookies_text: the text that the administrator submitted formatted
 *   properly.
 * - $plugins: the plugins in the system. You need to loop through them and use
 *   the "title" key to print the markup for the vertical tab title and the
 *   "content" key to print the makrup for the div container. See below for an
 *   example usage.
 *
 *   Important Note: The class of the save button is used to identify it with
 *   javascript. You should NOT change this class or things will probably break.
 *   If you want to theme it differently you can add an id to it (ids are
 *   prioritized over classes in css, remember?) or just copy and paste the
 *   rules from euccx.css in your theme and change them to suit your needs.
 */
?>

<div class="cookie-tab-container">
  <div id="cookie-tabs">
    <ul>
      <?php if ($privacy_page): ?>
      <li><a href="#cookie-tab-pp"><?php print $privacy_page_title; ?></a></li>
      <?php endif; ?>
      <?php if ($required_cookies): ?>
      <li><a href="#cookie-tab-rc"><?php print $required_cookies_title; ?></a></li>
      <?php endif; ?>
      <?php
        foreach ($plugins as $plugin) {
          print($plugin['title']);
        }
      ?>
    </ul>
    <?php if ($privacy_page): ?>
    <div id="cookie-tab-pp">
      <?php print $privacy_page_contents; ?>
    </div>
    <?php endif; ?>
    <?php if ($required_cookies): ?>
    <div id="cookie-tab-rc">
      <?php print $required_cookies_text; ?>
    </div>
    <?php endif; ?>
    <?php
      foreach ($plugins as $plugin) {
        print($plugin['content']);
      }
    ?>
  </div>
  <div class="cookie-tab-actions">
    <?php
      if ($uses_categories):
    ?>
      <button class="eucc-toggle-withdraw-banner" onclick="Drupal.eu_cookie_compliance.toggleWithdrawBanner(); return false;"><?php print $toggle_withdraw_banner_button_text; ?></button>
    <?php
      else:
    ?>
      <button class="cookie-settings-save"><?php print $save; ?></button>
    <?php
      endif;
    ?>
  </div>
</div>
