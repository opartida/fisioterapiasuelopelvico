<?php

/**
 * @file
 * Google Adsense integration.
 */

/**
 * Plugin definition.
 */
$plugin = array(
  'title' => 'Google Adsense',
  'description' => 'Handle cookies related to the Google Adsense service',
  'module_dependencies' => array('adsense', 'adsense_managed'),
  'module_block_overrides' => array(
    'adsense_managed' => array(
      // This setting will usually be the key of the renderable array that you
      // created in the cookie_consent_extra_options callback.
      'setting' => 'adsense_block_content',
      // The jquery selector of the container where the content will be
      // injected.
      // @todo: Maybe at some point allow for different operations in addition
      // to the "replace" that we're using right now?
      'selector' => '.adsense',
    ),
  ),
  'cookie_consent_extra_options' => 'euccx_cookies_gadsense',
  'blacklist' => array('/googlesyndication\.com/'),
  'opt_in_category' => 'marketing',
);

/**
 * Callback function that creates the extra options for our admin form.
 */
function euccx_cookies_gadsense() {
  $default_filter_format = filter_default_format();

  if ($default_filter_format == 'filtered_html' &&
    filter_format_load('full_html')) {
    $default_filter_format = 'full_html';
  }

  $item = array();
  $item['adsense_block_content'] = array(
    '#type' => 'text_format',
    '#title' => t('Markup to display if user did not enable ads'),
    '#description' => t('If the user did not accept the ads (yet), your input
     below will replace the blocks with the ads'),
    '#default_value' => _euccx_settings(
      'adsense_block_content',
      '',
      'value',
      'gadsense'
    ),
    '#format' => _euccx_settings(
      'adsense_block_content',
      $default_filter_format,
      'format',
      'gadsense'
    ),
  );

  return $item;
}
