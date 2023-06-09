(function($) {
  Drupal.behaviors.stickynav = {
    breakpoint: 0,
    compensation: 0,
    originalPadding: 0,
    attach : function(context) {
      var selector = Drupal.settings.stickynav.selector;
      //only getting the first elmenet in the dom
      var $menu = $(selector).eq(0);
      if ($menu.length) {
        $menu.once('stickynav', function() {
          // Save original padding on top. 0 timeout to get correct padding.
          setTimeout(function() {
            Drupal.behaviors.stickynav.originalPadding = $('body').css('paddingTop');
          }, 0);
          Drupal.behaviors.stickynav.breakpoint = $menu.offset().top;
          //we need to compensate the element so that the content does not jump up.
          Drupal.behaviors.stickynav.compensation = $menu.outerHeight();
          $(window).scroll(function () {
            if ($(window).scrollTop() > Drupal.behaviors.stickynav.breakpoint) {
              $menu.addClass('stickynav-active');
              $('body').css('padding-top', Drupal.behaviors.stickynav.compensation);
            }
            else {
              $menu.removeClass('stickynav-active');
              $('body').css('padding-top', Drupal.behaviors.stickynav.originalPadding);
            }
          });
        });
      }
    }
  }
})(jQuery);
;
(function ($) {

  Drupal.behaviors.captcha = {
    attach: function (context) {

      // Turn off autocompletion for the CAPTCHA response field.
      // We do it here with JavaScript (instead of directly in the markup)
      // because this autocomplete attribute is not standard and
      // it would break (X)HTML compliance.
      $("#edit-captcha-response").attr("autocomplete", "off");

    }
  };

  Drupal.behaviors.captchaAdmin = {
    attach: function (context) {
      // Add onclick handler to checkbox for adding a CAPTCHA description
      // so that the textfields for the CAPTCHA description are hidden
      // when no description should be added.
      // @todo: div.form-item-captcha-description depends on theming, maybe
      // it's better to add our own wrapper with id (instead of a class).
      $("#edit-captcha-add-captcha-description").click(function() {
        if ($("#edit-captcha-add-captcha-description").is(":checked")) {
          // Show the CAPTCHA description textfield(s).
          $("div.form-item-captcha-description").show('slow');
        }
        else {
          // Hide the CAPTCHA description textfield(s).
          $("div.form-item-captcha-description").hide('slow');
        }
      });
      // Hide the CAPTCHA description textfields if option is disabled on page load.
      if (!$("#edit-captcha-add-captcha-description").is(":checked")) {
        $("div.form-item-captcha-description").hide();
      }
    }

  };

})(jQuery);
;
