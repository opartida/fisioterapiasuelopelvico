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
/**
 * @file
 * JavaScript functions for the Client-side adaptive image module.
 */

(function ($) {
  Drupal.behaviors.csAdaptiveImage = {
    attach: function(context, settings) {
      /**
       * Retrieves an adapted image based element's data attributes
       * and the current client width.
       */
      var getAdaptedImage = function(element, excluded_breakpoint) {
        var selected_breakpoint = 'max';
        var breakpoints = $(element).attr('data-adaptive-image-breakpoints');
        if (breakpoints) {
          // Find applicable target resolution.
          $.each(breakpoints.split(' '), function(key, breakpoint) {
            if (document.documentElement.clientWidth <= Number(breakpoint) && (selected_breakpoint == 'max' || Number(breakpoint) < Number(selected_breakpoint))) {
              selected_breakpoint = breakpoint;
            }
          });
        }
        if (selected_breakpoint != excluded_breakpoint) {
          return $(element).attr('data-adaptive-image-' + selected_breakpoint + '-img');
        }
        else {
          return false;
        }
      };

      // Insert adapted images.
      $('noscript.adaptive-image', context).once('adaptive-image', function() {
        var img = getAdaptedImage(this);
        $(this).after(img);
        Drupal.attachBehaviors(img);
      });

      // Replace adapted images on window resize.
      $(window).resize(function() {
        $('noscript.adaptive-image-processed').each(function() {
          // Replace image if it does not match the same breakpoint.
          var excluded_breakpoint = $(this).next('img.adaptive-image').attr('data-adaptive-image-breakpoint');
          var img = getAdaptedImage(this, excluded_breakpoint);
          if (img) {
            $(this).next('img.adaptive-image').replaceWith(img);
            Drupal.attachBehaviors(img);
          }
        });
      });
    }
  };
})(jQuery);;
