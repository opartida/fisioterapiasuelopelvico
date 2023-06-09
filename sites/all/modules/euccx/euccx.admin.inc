<?php

/**
 * @file
 * This file provides the administration form for the module.
 */

/**
 * Provides the admin form for euccx.
 *
 * @param array $form
 *   Form array.
 * @param array $form_state
 *   For state array.
 *
 * @return array
 *   Admin form render array.
 */
function euccx_admin_form(array $form, array $form_state) {
  ctools_include('plugins');

  // Setting the default filter format for any textareas that may need it.
  // For more info on why it's done this way see:
  // https://www.drupal.org/node/2969619
  $default_filter_format = filter_default_format();
  if ($default_filter_format == 'filtered_html' &&
    filter_format_load('full_html')) {
    $default_filter_format = 'full_html';
  }

  $form = array();

  $form['euccx'] = array(
    '#type' => 'item',
    '#tree' => TRUE,
  );

  $form['euccx']['info'] = array(
    '#markup' => '<p>' . t("<h2>EU Cookie Compliance Extras' Settings</h2>") .
    '</p>',
  );

  // When using "Opt-in with groups" option in eucc, this has huge implications
  // for us. Inform the user about the changes and hide unavailable form fields.
  $uses_categories = _euccx_uses_categories();
  drupal_set_message(t('You selected Opt-in with categories in
  EU Cookie Compliance settings. EUCCX currently only has limited compatibility
  with this option. For example toggle buttons can not be used. Instead the consent banner is
  used to change users opt-in group preferences.'), 'warning', FALSE);

  $form['euccx']['bar'] = array(
    '#type' => 'fieldset',
    '#title' => t('Bar Options'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => t('Settings that alter the default bar shown by EU Cookie
      Compliance module.'),
  );

  $form['euccx']['bar']['disable_all_button'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display a "Disable all cookies" button'),
    '#default_value' => _euccx_settings('disable_all_button', 0),
    '#description' => t('This is an option that allows the user to disable all
      cookies from the default EU Cookie Compliance bar. For more information
      about the legal rationale behind this option you can check the relevant
      issue <a href="https://www.drupal.org/project/euccx/issues/3126824">here
      </a>.<br>In order to use this option, you just have to create an element
      with the class "euccx-disable-all" anywhere in your page after enabling
      this option. It can be any element (e.g. a, span, div) and euccx will
      handle turning off the default behavior (e.g. in the case of an a).'),
  );

  $form['euccx']['block'] = array(
    '#type' => 'fieldset',
    '#title' => t('Block Options'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => t('The euccx module provides you with a block where all
      the custom integrations are being displayed and the user can opt-in or out
      from specific cookies being stored in their browser.'),
  );

  $form['euccx']['block']['unticked'] = array(
    '#type' => 'checkbox',
    '#title' => t('Extra cookies unticked by default'),
    '#default_value' => _euccx_settings('unticked', 0),
    '#description' => t('The European Court of Justice (ECJ) confirmed
      that the pre-ticked checkboxes for cookie consent are illegal. You can
      find more information in the relevant issue for the euccx module
      <a href="https://www.drupal.org/project/euccx/issues/3092522">here.</a>
      Even though it is pretty clear that the court\'s decision is very
      straightforward, in order to prevent breaking functionality in sites
      that are already using the module, the default value of this checkbox
      is set to "unchecked". However, if you want your website to be compliant,
      you should enable this option. If you do, the default option in all the
      "not-necessary" cookies\' switches (i.e. Google Analytics and Google
      Adsense) will be disabled by default and the user will have to enable
      them with an affirmative action'),
    '#disabled' => $uses_categories,
  );

  $form['euccx']['block']['include_bare_css'] = array(
    '#type' => 'checkbox',
    '#title' => t('Include minimal CSS'),
    '#default_value' => _euccx_settings('include_bare_css', 0),
    '#description' => t('The cookie consent block comes with several default
      design choices. If you want to theme it yourself in any css file loaded by
      your theme or custom module, you can check this option.'),
  );

  $form['euccx']['block']['save_button_text'] = array(
    '#type' => 'textfield',
    '#title' => t('Text for the save button of the block'),
    '#default_value' => _euccx_settings(
      'save_button_text',
      'Save my cookie preferences'
    ),
    '#description' => t('Provide the text of the button that will be used to
      store the user choices. This will be available in the template file as
      a variable.'),
    '#disabled' => $uses_categories,
  );

  $form['euccx']['block']['toggle_withdraw_banner_button_text'] = array(
    '#type' => 'textfield',
    '#title' => t('Text for the "Change my cookie preferences" button of the block'),
    '#default_value' => _euccx_settings(
      'toggle_withdraw_banner_button_text',
      'Change my cookie preferences'
    ),
    '#description' => t('Provide the text of the button that will be used to
      trigger the EU Cookie Compliance popup to change users cookie group
      preferences (when using EUCC "Opt-in with categories" consent method).'),
    '#disabled' => !$uses_categories,
  );

  $form['euccx']['block']['include_pp'] = array(
    '#type' => 'checkbox',
    '#title' => t('Include Privacy Policy page in tabs'),
    '#default_value' => _euccx_settings('include_pp', 0),
    '#description' => t('The block presents a list of vertical tabs with all the
      different categories of cookies that the users can interact with. Do you
      want a separate tab that will render the Privacy Policy page?'),
  );

  $form['euccx']['block']['extras_ipp'] = array(
    '#type' => 'fieldset',
    '#title' => t("Privacy Policy Settings"),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#states' => array(
      'visible' => array(
        "input[name='euccx[block][include_pp]']" => array(
          'checked' => TRUE,
        ),
      ),
    ),
  );

  $form['euccx']['block']['extras_ipp']['pptitle'] = array(
    '#type' => 'textfield',
    '#title' => t('Tab Title for the Privacy Policy tab'),
    '#default_value' => _euccx_settings('pptitle', 'Privacy Policy'),
    '#description' => t('Please provide the title that you would like the
      "Privacy Policy" tab to have.'),
  );

  $form['euccx']['block']['extras_ipp']['pplink'] = array(
    '#type' => 'textfield',
    '#title' => t('Path to the node that is the privacy link'),
    '#default_value' => _euccx_settings('pplink', ''),
    '#description' => t('Provide a link to the privacy page node. Currently only
      internal links are supported in the format "node/{nid}".<br>Please note
      that the purpose of this link is different than the purpose of the Data
      Privacy Link setting in EU Cookie Compliance module. You can use euccx\'s
      setting to load any node that you want and name it however you want. This
      option is more about flexibility in your block\'s presenation than
      anything else.<br>For more information please check the FAQ in euccx\'s
      <a href="/admin/help#euccx">README.txt</a> or the
      <a href="https://www.drupal.org/project/euccx/issues/3130016#comment-13567739">
      relevant comment</a> in the module\'s issue queue.'),
  );

  $form['euccx']['block']['include_required'] = array(
    '#type' => 'checkbox',
    '#title' => t('Include "Required Cookies" tab'),
    '#default_value' => _euccx_settings('include_required', 0),
    '#description' => t('The GDPR states that some cookies can be stored in the
      end user\'s browser if they are absolutely necessary for the proper
      function of the website. By selecting this option a new tab will be
      created where you can inform your user about those cookies.'),
  );

  $form['euccx']['block']['extras_ir'] = array(
    '#type' => 'fieldset',
    '#title' => t("Required Cookies' Settings"),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#states' => array(
      'visible' => array(
        "input[name='euccx[block][include_required]']" => array(
          'checked' => TRUE,
        ),
      ),
    ),
  );

  $form['euccx']['block']['extras_ir']['rctitle'] = array(
    '#type' => 'textfield',
    '#title' => t('Tab Title for the Required Cookies tab'),
    '#default_value' => _euccx_settings('rctitle', 'Required Cookies'),
    '#description' => t('Please provide the title that you would like the
      "Required Cookies" tab to have.'),
  );

  $form['euccx']['block']['extras_ir']['rctoggle'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show the toggle button for required cookies'),
    '#default_value' => _euccx_settings('rctoggle', 0),
    '#description' => t('It is common practice for sites to display a greyed-out
      toggle button so that the users understand that these cookies cannot be
      disabled. Check this option to display such a toggle switch.<br><em>Note:
      </em> This button is created through css using the markup found in the
      template file. If you choose to <em>"Include minimal CSS"</em>, you will
      most likely not see it. Take a look at the available variables and
      comments in the euccx.tpl.php file for more information.'),
    '#disabled' => $uses_categories,
  );

  $form['euccx']['block']['extras_ir']['rctext'] = array(
    '#type' => 'text_format',
    '#title' => t('Required cookies text'),
    '#description' => t('A text that will explain to the end user which cookies
      are absolutely necessary for the proper function of the website and cannot
      be disabled.'),
    '#default_value' => _euccx_settings('rctext', '', 'value'),
    '#format' => _euccx_settings('rctext', $default_filter_format, 'format'),
  );

  // PLUGINS.
  $cookie_consent_plugins = ctools_get_plugins('euccx', 'cookie_consent');

  // We only create the fieldset for the plugins if it's not empty.
  if (!empty($cookie_consent_plugins)) {
    $form['euccx']['plugins'] = array(
      '#type' => 'fieldset',
      '#title' => t('Available Plugins'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#description' => t('The euccx module ships with 2 plugins for google
        analytics and google adsense integration. If your installation meets the
        requirements, you may enable and configure them below'),
    );
  }

  // No need to include this in the previous !empty statement since if it's
  // empty this loop will not be executed at all and we save some indentation
  // space in the process.
  foreach ($cookie_consent_plugins as $ccp_key => $ccp_array) {
    // We'll use this to identify whether to show the settings for the current
    // plugin (only show settings if the plugin is enabled).
    $input_name = ':input[name="' . "euccx[plugins][$ccp_key][$ccp_key]" . '"]';

    $form['euccx']['plugins'][$ccp_key] = array(
      '#type' => 'item',
    );

    $form['euccx']['plugins'][$ccp_key][$ccp_key] = array(
      '#type' => 'checkbox',
      '#title' => $ccp_array['title'],
      '#description' => $ccp_array['description'],
      '#default_value' => _euccx_settings($ccp_key, '0', '', $ccp_key),
    );
    // Verify Module Dependencies
    // For a detailed explanation on what we're doing here check:
    // euccx_form_eu_cookie_compliance_admin_form_alter() in euccx.module file.
    if (!empty($ccp_array['module_dependencies'])) {
      $module_dependency_string = '';
      foreach ($ccp_array['module_dependencies'] as $module_dependency) {
        if (!module_exists($module_dependency)) {
          $module_dependency_string = empty($module_dependency_string) ?
            $module_dependency :
            "$module_dependency_string, $module_dependency";
          $form['euccx']['plugins'][$ccp_key]['#disabled'] = TRUE;
          $form['euccx']['plugins'][$ccp_key]['#description'] = t('You need to
            enable: <strong>%dependencies</strong> module(s) in order to use
            this plugin', array('%dependencies' => $module_dependency_string));
        }
      }
    }

    // Create a grouping item in order to show/hide our extra configuration
    // options at the same time.
    $group_name = $ccp_key . "_group";
    $form['euccx']['plugins'][$ccp_key][$group_name] = array(
      '#type' => 'fieldset',
      '#title' => t('Extra settings for the <strong>%plugin</strong> plugin',
      array('%plugin' => $ccp_array['title'])),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
      '#states' => array(
        'visible' => array($input_name => array('checked' => TRUE)),
      ),
    );

    $form['euccx']['plugins'][$ccp_key][$group_name]['title'] = array(
      '#type' => 'textfield',
      '#title' => t('Tab Title'),
      '#description' => t('The tab title for the plugin in the user block'),
      '#default_value' => _euccx_settings(
        'title',
        $ccp_array['title'],
        '',
        $ccp_key
      ),
    );

    $form['euccx']['plugins'][$ccp_key][$group_name]['content'] = array(
      '#type' => 'text_format',
      '#title' => t('Tab Contents'),
      '#description' => t('The tab contents for the plugin in the user block'),
      '#default_value' => _euccx_settings('content', '', 'value', $ccp_key),
      '#format' => _euccx_settings(
        'content',
        $default_filter_format,
        'format',
        $ccp_key
      ),
    );

    if ($uses_categories) {
      // eucc opt-in categories are used:

      $form['euccx']['plugins'][$ccp_key][$group_name]['opt_in_category'] = array(
        '#type' => 'select',
        '#title' => t('EUCC Cookie Opt-in category'),
        '#description' => t('The cookie category this plugin is associated with (when using EUCC "Opt-in with categories" consent method).'),
        '#options' => _euccx_get_categories_options(),
        '#default_value' => _euccx_settings(
          'opt_in_category',
          $ccp_array['opt_in_category'],
          '',
          $ccp_key
        ),
        '#required' => TRUE,
      );
    }

    // Generate the extra options that the plugin might have defined.
    if (!empty($ccp_array['cookie_consent_extra_options'])) {
      $extra_options = $ccp_array['cookie_consent_extra_options']();
      foreach ($extra_options as $key => $value) {
        $form['euccx']['plugins'][$ccp_key][$group_name][$key] = $value;
      }
    }
  }

  $form = system_settings_form($form);

  return $form;
}
