<?php

/**
 * @file
 * Syslog consent storage.
 */

/**
 * Define your plugin as an associative array.
 *
 * Recognized keys:
 * 'title': The title of the consent storage plugin
 * 'description': A short description for the storage plugin
 * 'consent_storage_callback': A callback function that accepts $type (the
 *  consent type like banner or form id) as a parameter and the
 *  extra options that your storage plugin may require. This is where you
 *  specify the logic of your consent storage plugin.
 * 'module_dependencies': An array of machine-readable module names that this
 *  storage plugin requires in order to function.
 *  If one or more of the plugins defined in this array are not enabled, the
 *  storage plugin will be greyed out in the list.
 *  'consent_storage_extra_options_callback': A callback function that should
 *  return a form array with the elements that need to be added to the
 *  settings' form.
 */
$plugin = array(
  'title' => t('Store in Syslog'),
  'description' => t('Uses the system log for consent storage. See <a href="http://drupal.org/documentation/modules/syslog" target="_blank">the documentation of the core syslog module</a> and PHP\'s <a href="http://www.php.net/manual/function.openlog.php" target="_blank">openlog</a> and <a href="http://www.php.net/manual/function.syslog.php" target="_blank">syslog</a> functions for more information.'),
  'consent_storage_callback' => 'euccx_store_consent_syslog',
  'module_dependencies' => array('syslog'),
  'consent_storage_extra_options_callback' => 'euccx_store_consent_extra_options_syslog',
);

/**
 * Store record of consent in the syslog.
 *
 * @param string $type
 *   The consent type (for example banner or form ID).
 *
 * @return bool
 *   Returns TRUE on storage success.
 *
 * @throws \Exception
 */
function euccx_store_consent_syslog($type) {
  global $user;
  global $base_url;

  $revision_id = _eu_cookie_compliance_get_current_policy_node_revision();
  $timestamp = time();
  $ip_address = ip_address();
  $uid = $user->uid;

  // Get the default values for our form elements first.
  $config_options = _euccx_store_consent_syslog_get_stored_options();

  $message = strtr($config_options['syslog_format'], array(
    '!base_url'    => $base_url,
    '!timestamp'   => $timestamp,
    '!type'        => $type,
    '!ip'          => $ip_address,
    '!uid'         => $uid,
    '!rid'         => $revision_id,
  ));

  openlog(
    $config_options['syslog_identity'],
    LOG_NDELAY,
    $config_options['syslog_facility']
  );
  // Priority is always info;
  // no other priority makes sense for storing consent data.
  syslog(WATCHDOG_INFO, $message);

  return TRUE;
}

/**
 * Generate the extra form options for the syslog consent storage plugin.
 *
 * The specific part pretty much copies the options that you can find in the
 * Syslog core module.
 * The only thing that changes are the descriptions and the titles along with
 * the variables names that we are using.
 */
function euccx_store_consent_extra_options_syslog() {

  if (!module_exists('syslog')) {
    return array();
  }
  // Get the default values for our form elements first.
  $config_options = _euccx_store_consent_syslog_get_stored_options();

  // Now build the form elements that we want to show if our storage plugin is
  // selected.
  $form = array();

  $form['eu_cookie_compliance_syslog_identity'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Syslog identity'),
    '#default_value' => $config_options['syslog_identity'],
    '#description'   => t('A string that will be prepended to every consent entry logged to Syslog. If you have multiple sites logging to the same Syslog log file, a unique identity per site makes it easy to tell the log entries apart.'),
  );

  if (defined('LOG_LOCAL0')) {
    $form['eu_cookie_compliance_syslog_facility'] = array(
      '#type'          => 'select',
      '#title'         => t('Syslog facility'),
      '#default_value' => $config_options['syslog_facility'],
      '#options'       => syslog_facility_list(),
      '#description'   => t('Depending on the system configuration, Syslog and other logging tools use this code to identify or filter messages from within the entire system log.'),
    );
  }

  $form['eu_cookie_compliance_syslog_format'] = array(
    '#type'          => 'textarea',
    '#title'         => t('Log message format'),
    '#default_value' => $config_options['syslog_format'],
    '#description'   => t('Specify the format of the syslog entry. Available variables are: <dl><dt><code>!base_url</code></dt><dd>Base URL of the site.</dd><dt><code>!timestamp</code></dt><dd>Unix timestamp of the log entry.</dd><dt><code>!type</code></dt><dd>The type of the consent (e.g. banner or form id).</dd><dt><code>!ip</code></dt><dd>IP address of the user giving the consent.</dd><dt><code>!uid</code></dt><dd>User ID.</dd><dt><code>!rid</code></dt><dd>The revision id of the Terms page.</dd></dl>'),
  );

  return $form;
}

/**
 * Helper function.
 *
 * Retrieves the stored options from the configuration form and sets up
 * sane defaults if the form has not been saved.
 */
function _euccx_store_consent_syslog_get_stored_options() {
  $output = array();

  $eucc = variable_get('eu_cookie_compliance', array());
  $output['syslog_identity'] = !empty($eucc['syslog']['eu_cookie_compliance_syslog_identity']) ? $eucc['syslog']['eu_cookie_compliance_syslog_identity'] : 'drupal_eucc';
  $output['syslog_facility'] = !empty($eucc['syslog']['eu_cookie_compliance_syslog_facility']) ? $eucc['syslog']['eu_cookie_compliance_syslog_facility'] : LOG_LOCAL0;
  $output['syslog_format'] = !empty($eucc['syslog']['eu_cookie_compliance_syslog_format']) ? $eucc['syslog']['eu_cookie_compliance_syslog_format'] : '!base_url|!timestamp|!type|!ip|!uid|!rid';

  return $output;
}
