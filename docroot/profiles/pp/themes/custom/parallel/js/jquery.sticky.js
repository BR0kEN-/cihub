(function($, cssClass) {
  'use strict';

  $.fn.sticky = function() {
    return this.each(function() {
      var $element = $(this);
      var offsetTop = $element.offset().top;
      var sticky = false;
      var allow = (document.body.scrollHeight - offsetTop) >= window.outerHeight;

      $(window).on('scroll', function() {
        if (this.scrollY > offsetTop && allow) {
          if (!sticky) {
            sticky = !sticky;
            $element.addClass(cssClass);
          }
        }
        else {
          if (sticky) {
            sticky = !sticky;
            $element.removeClass(cssClass);
          }
        }
      });
    });
  };
})(jQuery, 'sticky');
