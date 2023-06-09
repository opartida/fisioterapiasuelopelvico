CONTENTS OF THIS FILE
---------------------

 * Introduction
 * Requirements
 * Other Module Integrations
 * Installation
 * Quick Start
 * Troubleshooting
 * FAQ
 * Maintainers


INTRODUCTION
------------

The EU Cookie Compliance Extras module is a toolbox aimed to help system
administrators and developers comply with the European General Data Protection
Regulation (GDPR). It complements the EU Cookie Compliance module by providing
a highly performant consent storage plugin along with integration with popular
modules which set third-party cookies to the user (e.g. Google Analytics and
Adsense). Furthermore, it gives users the option to selectively disable cookies,
providing functionality similar to some very popular Wordpress plugins (like
"GDPR Cookie Compliance") in Drupal.

For a full description of the project visit the project page:
https://www.drupal.org/project/euccx

To submit bug reports and feature suggestions, or to track changes:
https://www.drupal.org/project/issues/euccx


REQUIREMENTS
------------

 * Ctools ( https://www.drupal.org/project/ctools )
   Recommended version: >= 1.14

 * EU Cookie Compliance ( https://www.drupal.org/project/eu_cookie_compliance )
   Required version: > 1.24

 * Jquery Update ( https://www.drupal.org/project/jquery_update )
   Recommended version: >= 2.7



OTHER MODULE INTEGRATIONS
-------------------------

 * Adsense ( https://www.drupal.org/project/adsense )

 * Google Analytics ( https://www.drupal.org/project/google_analytics )


INSTALLATION
------------

Install as you would normally install a contributed Drupal. See:
https://www.drupal.org/documentation/install/modules-themes/modules-7 for
further information.


CONFIGURATION
-------------

 1. Download, install and enable module dependencies.

 2. Download, install and enable the module.

 3. You should be able to select a new consent storage plugin in the
    admin/config/system/eu-cookie-compliance page of your site.

 4. Go to admin/config/system/eu-cookie-compliance/extras in order to setup
    additional options for the plugin.

For more detailed setup instructions please visit the project's page and follow
the Documentation link.


TROUBLESHOOTING
---------------

 * If you have any issues during the installation or use of this module, please
   make sure that the EU Cookie Compliance module's version is **1.25** or
   higher.

 * If the correct version of EU Cookie Compliance module is installed and you
   are still having issues, please create an issue here:
   https://www.drupal.org/project/issues/euccx


TRANSLATIONS
------------

We use the exact same system that the EU Cookie Compliance module uses so its
README section for Translations *should* work. Pasting it below for
completeness' sake:

> To translate the message in the banners, enable the "i18n_variable" submodule
> in the i18n project.
> https://www.drupal.org/project/i18n
> After enabling
"EU Cookie Compliance Extras"
> at admin/config/regional/i18n/variable,
> you will be able to set your translations on the settings page for this
> module.
> Using Domain Access? Instead of using the "domain_settings" module, you
> need to use the "domain_variable_i18n" sub-module from the domain_variable
> project, or you won't be able to translate the module settings.
> https://www.drupal.org/project/domain_variable


FAQ
---

 Q: Why not submit the code to the EU Cookie Compliance module?

 A: Well, the short answer is: "because I don't have enough time to create a D8
    version of my changes". If/when I do find time to make a D8 version of this
    module and there is enough interest, I would consider merging it with the
    EU Cookie Compliance module.

 -

 Q: Have you considered making a D8 version of the module?

 A: There is already an issue on the queue. I always have it in the back of my
    head to start working on that, but since I have to make ends meet, I keep
    pushing it back in favor of paid work. If you would like to sponsor the
    development of the D8 version of this module, please contact me via a pm
    in Drupal.org.

 -

 Q: Have you considered removing the dependencies of this module?

 A: Yes. But instead of re-inventing the wheel to make stuff adhere to modern
    development standards, I decided to just add the "extra" things that I
    needed for my use-case on top of the existing EU Cookie Compliance
    solution.

 -

 Q: Why do you not have separate permissions?

 A: Since this module completely depends on EU Cookie Compliance, we piggyback
    on the permissions too.

 -

 Q: Why not use the Data Privacy Link setting from EU Cookie Compliance instead
    of loading our own node?

 A: The 2 settings are different. The main purpose of the EU Cookie Compliance's
    setting is to create a link to the Privacy Policy page. The main purpose of
    our own setting on the other hand is to provide the administrator with a
    flexible way of adding a node to the euccx's block, themed properly.
    For a more detailed explanation you can read the comment in the issue queue:
    https://www.drupal.org/project/euccx/issues/3130016#comment-13567739


MAINTAINERS
-----------

Current maintainers:
 * Thomas Minitsios (tmin) - https://www.drupal.org/user/2970281

This project has been sponsored by:
 * Lawspot
   Lawspot's mission is to provide openness and transparency to the law, to
   all citizens. Lawspot is Greece's No.1 online hub for all things legal,
   transforming legislation, case law and legal opinions into a dynamic,
   tool-based, searchable dataset. Visit https://www.lawspot.gr for more
   information.
