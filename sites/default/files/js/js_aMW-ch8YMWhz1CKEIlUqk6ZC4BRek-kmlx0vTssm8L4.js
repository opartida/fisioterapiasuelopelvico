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
 * The RRSSB Drupal Behavior to configure settings.
 */

(function ($) {
    Drupal.behaviors.rrssb = {
      attach: function(context, settings) {
        rrssbConfigAll(settings.rrssb);
      }
    };
})(jQuery);;
+function(i,t,e){"use strict";var s={size:{min:.1,max:10,"default":1},shrink:{min:.2,max:1,"default":.8},regrow:{min:.2,max:1,"default":.8},minRows:{min:1,max:99,"default":1},maxRows:{min:1,max:99,"default":2},prefixReserve:{min:0,max:.8,"default":.3},prefixHide:{min:.1,max:10,"default":2},alignRight:{type:"boolean","default":!1}},n=function(){var i=t.fn.jquery.split(".");return 1==i[0]&&i[1]<8}();i.rrssbConfigAll=function(i){t(".rrssb").each(function(){t(this).rrssbConfig(i)})},t.fn.rrssbConfig=function(i){if(!t(this).data("settings")||i){var e={};for(var n in s)e[n]=s[n].default,i&&("boolean"==s[n].type?e[n]=Boolean(i[n]):isNaN(parseFloat(i[n]))||(e[n]=Math.min(s[n].max,Math.max(s[n].min,i[n]))));t(this).data("settings",e),o.call(this)}};var r,a=function(){var i=t(".rrssb-prefix",this),e=i.length?i.clone().css({visibility:"hidden","white-space":"nowrap",display:"inline"}).appendTo(this):null;t("ul").contents().filter(function(){return this.nodeType===Node.TEXT_NODE}).remove();var s={width:0,buttons:0,height:t("li",this).innerHeight(),fontSize:parseFloat(t(this).css("font-size")),prefixWidth:e?e.innerWidth():0};return t("li",this).each(function(){s.width=Math.max(s.width,t(this).innerWidth()),s.buttons++}),t(this).data("orig",s),e&&e.remove(),s},h=function(){t(".rrssb").each(o)},o=function(){var i=t(this).data("orig");i||(i=a.call(this));var e=t(this).data("settings"),s=i.width*e.size,r=i.buttons,h=t(this).innerWidth()-1,o=h<s*e.shrink?"":s;n?t("li",this).width(o):t("li",this).innerWidth(o);var l=h/e.shrink,c=i.prefixWidth*e.size;c>l*e.prefixHide?(c=0,t(".rrssb-prefix",this).css("display","none")):t(".rrssb-prefix",this).css("display","");var f=c<=h*e.prefixReserve?l-c:l,d=Math.floor(f/s);d*e.maxRows<r?(t(this).addClass("no-label"),s=i.height*e.size,d=Math.max(1,Math.floor(f/s))):t(this).removeClass("no-label");var u=e.minRows>1?Math.max(1,Math.ceil(r/(e.minRows-1))-1):r;d=Math.min(d,u),d=Math.ceil(r/Math.ceil(r/d)),u=Math.ceil(r/Math.ceil(r/u));var m=Math.floor(1e4/d)/100;t("li",this).css("max-width",m+"%");var p=s*d+c;p>l&&(p-=c,c=0);var g=u>d?e.regrow:1,b=Math.min(g,.95*h/p),x=i.fontSize*e.size*b;if(t(this).css("font-size",x+"px"),c){var v=Math.floor(1e4*c/p)/100;t(".rrssb-buttons",this).css("padding-left",v+"%"),t(".rrssb-prefix",this).css("position","absolute");var w=Math.ceil(r/d),M=w*i.height/i.fontSize;t(".rrssb-prefix",this).css("line-height",M+"em")}else t(".rrssb-buttons",this).css("padding-left",""),t(".rrssb-prefix",this).css("position",""),t(".rrssb-prefix",this).css("line-height","");var y=e.alignRight?"padding-left":"padding-right";if(b>=.999*g){var z=Math.floor(1e4*(h-p*b*1.02)/h)/100;t(this).css(y,z+"%")}else t(this).css(y,"")},l=function(t,s,n,r){var a=i.screenLeft!==e?i.screenLeft:screen.left,h=i.screenTop!==e?i.screenTop:screen.top,o=i.innerWidth?i.innerWidth:document.documentElement.clientWidth?document.documentElement.clientWidth:screen.width,l=i.innerHeight?i.innerHeight:document.documentElement.clientHeight?document.documentElement.clientHeight:screen.height,c=o/2-n/2+a,f=l/3-r/3+h,d=i.open(t,s,"scrollbars=yes, width="+n+", height="+r+", top="+f+", left="+c);d&&d.focus&&d.focus()},c=function(i){r&&clearTimeout(r),r=setTimeout(h,i?i:200)};t(document).ready(function(){t(".rrssb-buttons a.popup").click(function(i){l(t(this).attr("href"),t(this).find(".rrssb-text").html(),580,470),i.preventDefault()}),t(i).resize(c),t(document).ready(function(){rrssbConfigAll()})})}(window,jQuery);;
