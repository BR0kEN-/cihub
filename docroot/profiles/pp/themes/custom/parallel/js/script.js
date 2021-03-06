(function($) {
  'use strict';

  // Do not care about DOM ready.
  Theme.has('html', function($body, settings) {

  });

  Theme.has('node-type-article', function($body, settings) {

  });

  // Simple "resize" event. Callback (not "resize" event) will be executed
  // after page load.
  Breakpoint.set(function(height, width) {

  });

  // The value of "tablet" breakpoint is 980px (see $breakpoints variable in
  // scss/_variables.scss). Callback will be executed when window width will
  // be equal or less than 980px.
  Breakpoint.set({to: 'tablet'}, function(width, height, value, name) {
    console.log(arguments);
  });
})(jQuery);
