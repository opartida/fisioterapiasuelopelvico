<?php

/**
 * @file
 * Google Analytics' integration.
 */

/**
 * Define your plugin as an associative array.
 *
 * Recognized keys:
 * 'title': The title of your integration plugin.
 * 'description': A short description (for the administrative interface).
 * 'module_dependencies': An array of machine-readable module names that this
 *  plugin requires in order to function.
 * 'js_exclude': This behaves differently from the javascript file exclusion
 *  that happens in EU Cookie Compliance. This option should be an array with 2
 *  keys: name and data.
 *  In the "name" key you store an array of strings that should be excluded if
 *  they exist in a javascript file's path (e.g. array('googleanalytics.js')).
 *  In the "data" key you store an array of strings that should be excluded if
 *  they exist in the javascript's data (e.g. array('GoogleAnalyticsObject')).
 *  This plugin features the abovementioned examples in its definitino.
 * 'cookies_handled': An array of cookie names that your plugin interacts with.
 *  If you have just enabled euccx in your site and a user has, say, a google
 *  analytics cookie stored in their browser, the javascript may be disabled
 *  but the cookie will remain. This is a last line of defense which makes sure
 *  that the user's wishes will be respected.
 * 'module_block_overrides': An associative array with a module name as a key
 *  and the setting name that will used as the block content. Used for the
 *  adsense integration plugin to completely override the contents of the blocks
 *  it creates (so that you don't get the adsense javascript to run at all).
 *  Please check the gadsense plugin in order to understand how to structure
 *  this associative array and how to specify the selector that will be used by
 *  the javascript code in order to insert the content.
 *
 * @todo: Maybe in the future give the user an option to provide an empty
 *  string as "content" and remove the block completely from the registry with
 *  hook_block_info_alter().
 * 'cookie_consent_extra_options': A function that should return a renderable
 *  array for extra options to be presented to the plugin's admin form.
 */
$plugin = array(
  'title' => 'Google Analytics',
  'description' => 'Handle cookies related to the Google Analytics service',
  'module_dependencies' => array('googleanalytics'),
  'js_exclude' => array(
    'name' => array('googleanalytics.js'),
    'data' => array('GoogleAnalyticsObject'),
  ),
  'cookies_handled' => array('_ga', '_gat', '_gid'),
  'opt_in_category' => 'analytics',
);
