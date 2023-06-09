;
;
;
;
;
;
;
;
;
;
;
;
var $ = jQuery.noConflict();
$(document).ready(function() {
  $('#carousel-bootstrap').carousel({ interval: 4000, cycle: true });
  
  $('a[data-slide="prev"]').click(function() {
  $('#carousel-bootstrap').carousel('prev');
});

$('a[data-slide="next"]').click(function() {
  $('#carousel-bootstrap').carousel('next');
});
}); ;
