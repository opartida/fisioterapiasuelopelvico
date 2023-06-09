<?php

/**
 * @file
 * Matomo integration.
 */

$plugin = array(
  'title' => 'Matomo',
  'description' => 'Handle cookies related to Matomo (former Piwik)',
  'module_dependencies' => array('matomo'),
  'blacklist' => array('/matomo/'),
  'opt_in_category' => 'analytics',
);
