jQuery(document).ready(function($) {
    // Create send to backpack buttons for all unlocked achievements.
  jQuery('div.achievement-unlocked').each(function (index) {
    var body = jQuery(this).children('div.achievement-body');
    var image = jQuery(this).children('div.achievement-image');
    var i = image.find('img');
    var ext = i.attr('src').split('.').pop().toLowerCase();
    // Only create a link for the badge if the badge image is in .png format.
    if (ext == 'png') {
      var bpButton = '<input alt="Send to Mozilla Open Badge Backpack" title="Send to Mozilla Open Badge Backpack" type="backpack" class="achievement-openbadges-backpack-button">';
      image.append(bpButton);
    }
  });
  // Bind send buttons to the OpenBadges function.
  jQuery('.achievement-openbadges-backpack-button').bind('click', function() {
   // alert('hi');
    // Build the url for the assertion and call the OpenBadges function to issue the assertion.
    var title = jQuery(this).parent('div.achievement-image').parent('div.achievement').children('div.achievement-body').children('div.achievement-title').text();
    var url = Drupal.settings.baseRoot + Drupal.settings.basePath + 'amobb/assertions/' + encodeURIComponent(title) + '/' + Drupal.settings.uid;
    OpenBadges.issue([url], function(errors, successes) {
      // For logging errors.
      // alert(errors[0]['url']+errors[0]['reason']);
    });
  });
});
