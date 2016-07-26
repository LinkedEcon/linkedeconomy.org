// Drupal Settings
(function ($) {
  
  $(document).ready(function() {
    
    $(".switcher .link").click(function() {

    	if ($(".switcher").css("left") === "-240px") {
    		$(".switcher").animate({ left: "0px" }); 
    	} else {
    		$(".switcher").animate({ left: "-240px" });
    	}
    	
    })
    
    // Theme color
    $('.themeColors li a').click(function() {
      var themeColor = $(this).attr('class');
      
      $('#themeColor').remove();
      $('body').append('<link rel="stylesheet" href="/sites/all/themes/specialone/css/colors/' + themeColor + '.css" id="themeColor">');
      $('.logo').attr('src', '/sites/default/files/specialonelogo' + themeColor + '.png');
    });
    
    // Set the layout version
    $('.layout-style').change(function() {
      if($(this).val() == "boxed") {
        $('#main-wrapper').addClass('boxed-version');
        $('body').addClass('bg-pattern-billie_holiday');
      }
      else {
        $('#main-wrapper').removeClass('boxed-version');
      }
    });
    
    // Background Patterns
    $(".backgroundSwitcher li a").click(function() {
      var bgPattern = $(this).css("background");
      
    	$(this).parent().parent().find("a").removeClass("active");
    	$(this).addClass("active");

    	$('body').css('background', bgPattern);
    });
    
  });

})(jQuery);