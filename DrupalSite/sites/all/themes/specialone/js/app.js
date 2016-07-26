// Drupal Settings
(function ($) {
  
  $(document).ready(function() {
    
    // Set the layout version
    var layout_version = Drupal.settings['settings']['layout_version'];
    
    if (layout_version == "boxed") {
      var use_bPattern = Drupal.settings['settings']['use_bPattern'];
      
      if (use_bPattern == "1") {
        // if the user chooses the background pattern
        var boxed_bPattern = Drupal.settings['settings']['boxed_bPattern'];
        
        $('body').addClass(boxed_bPattern);
      } else {
        // if the user chooses not to use a background pattern it will apply a solid background color
        var boxed_bColor = Drupal.settings['settings']['boxed_bColor'];
        
        $('body').addClass(boxed_bColor);
      }
      
      $('#main-wrapper').addClass('boxed-version');
    }
    
    // Set the background color for the regions
    var header_bColor        = Drupal.settings['settings']['header_bColor'];
    var top_content_bColor   = Drupal.settings['settings']['top_content_bColor'];
    var featured_bColor      = Drupal.settings['settings']['featured_bColor'];
    var wide1_use_bImg       = Drupal.settings['settings']['wide1_use_bImg']; // This region allows background images
    var wide2_bColor         = Drupal.settings['settings']['wide2_bColor'];
    var wide3_use_bImg       = Drupal.settings['settings']['wide3_use_bImg']; // This region allows background images
    var wide4_bColor         = Drupal.settings['settings']['wide4_bColor'];
    var before_footer_bColor = Drupal.settings['settings']['before_footer_bColor'];
    var footer_four_bColor   = Drupal.settings['settings']['footer_four_bColor'];
    var footer_bColor        = Drupal.settings['settings']['footer_bColor'];
    
    $('#header-region').addClass(header_bColor);
    $('#top-content-region').addClass(top_content_bColor);
    $('#featured-region').addClass(featured_bColor);
    
    // Check if the user wants a background image
    if (wide1_use_bImg == "1") {
      // if the user chooses the background image
      var wide1_bImg = Drupal.settings['settings']['wide1_bImg'];
      
      $('#content-wide1-region').addClass(wide1_bImg);
    } else {
      // if the user chooses not to use a background image it will apply a solid background color
      var wide1_bColor = Drupal.settings['settings']['wide1_bColor'];
      
      $('#content-wide1-region').addClass(wide1_bColor);
    }
    
    $('#content-wide2-region').addClass(wide2_bColor);
    
    // Check if the user wants a background image
    if (wide3_use_bImg == "1") {
      // if the user chooses the background image
      var wide3_bImg = Drupal.settings['settings']['wide3_bImg'];
      
      $('#content-wide3-region').addClass(wide3_bImg);
    } else {
      // if the user chooses not to use a background image it will apply a solid background color
      var wide3_bColor = Drupal.settings['settings']['wide3_bColor'];
      
      $('#content-wide3-region').addClass(wide3_bColor);
    }
    
    $('#content-wide4-region').addClass(wide4_bColor);
    $('#before-footer-region').addClass(before_footer_bColor);
    $('#footer-four-columns').addClass(footer_four_bColor);
    $('footer').addClass(footer_bColor);
    
    // Set the text color for the regions
    var header_tColor        = Drupal.settings['settings']['header_tColor'];
    var top_content_tColor   = Drupal.settings['settings']['top_content_tColor'];
    var featured_tColor      = Drupal.settings['settings']['featured_tColor'];
    var wide1_tColor         = Drupal.settings['settings']['wide1_tColor'];
    var wide2_tColor         = Drupal.settings['settings']['wide2_tColor'];
    var wide3_tColor         = Drupal.settings['settings']['wide3_tColor'];
    var wide4_tColor         = Drupal.settings['settings']['wide4_tColor'];
    var before_footer_tColor = Drupal.settings['settings']['before_footer_tColor'];
    var footer_four_tColor   = Drupal.settings['settings']['footer_four_tColor'];
    var footer_tColor        = Drupal.settings['settings']['footer_tColor'];
    
    $('#header-region').addClass(header_tColor);
    $('#top-content-region').addClass(top_content_tColor);
    $('#featured-region').addClass(featured_tColor);
    $('#content-wide1-region').addClass(wide1_tColor);
    $('#content-wide2-region').addClass(wide2_tColor);
    $('#content-wide3-region').addClass(wide3_tColor);
    $('#content-wide4-region').addClass(wide4_tColor);
    $('#before-footer-region').addClass(before_footer_tColor);
    $('#footer-four-columns').addClass(footer_four_tColor);
    $('footer').addClass(footer_tColor);
    
    // Set the Title color for the regions
    var header_tiColor        = Drupal.settings['settings']['header_tiColor'];
    var top_content_tiColor   = Drupal.settings['settings']['top_content_tiColor'];
    var featured_tiColor      = Drupal.settings['settings']['featured_tiColor'];
    var wide1_tiColor         = Drupal.settings['settings']['wide1_tiColor'];
    var wide2_tiColor         = Drupal.settings['settings']['wide2_tiColor'];
    var wide3_tiColor         = Drupal.settings['settings']['wide3_tiColor'];
    var wide4_tiColor         = Drupal.settings['settings']['wide4_tiColor'];
    var before_footer_tiColor = Drupal.settings['settings']['before_footer_tiColor'];
    var footer_four_tiColor   = Drupal.settings['settings']['footer_four_tiColor'];
    var footer_tiColor        = Drupal.settings['settings']['footer_tiColor'];
    
    $('#header-region h1').addClass(header_tiColor);
    $('#header-region h2').addClass(header_tiColor);
    $('#header-region h3').addClass(header_tiColor);
    $('#header-region h4').addClass(header_tiColor);
    $('#header-region h5').addClass(header_tiColor);
    $('#header-region h6').addClass(header_tiColor);
    $('#header-region .block-title').addClass(header_tiColor);
    
    $('#top-content-region h1').addClass(top_content_tiColor);
    $('#top-content-region h2').addClass(top_content_tiColor);
    $('#top-content-region h3').addClass(top_content_tiColor);
    $('#top-content-region h4').addClass(top_content_tiColor);
    $('#top-content-region h5').addClass(top_content_tiColor);
    $('#top-content-region h6').addClass(top_content_tiColor);
    $('#top-content-region .block-title').addClass(top_content_tiColor);
    
    $('#featured-region h1').addClass(featured_tiColor);
    $('#featured-region h2').addClass(featured_tiColor);
    $('#featured-region h3').addClass(featured_tiColor);
    $('#featured-region h4').addClass(featured_tiColor);
    $('#featured-region h5').addClass(featured_tiColor);
    $('#featured-region h6').addClass(featured_tiColor);
    $('#featured-region .block-title').addClass(featured_tiColor);
    
    $('#content-wide1-region h1').addClass(wide1_tiColor);
    $('#content-wide1-region h2').addClass(wide1_tiColor);
    $('#content-wide1-region h3').addClass(wide1_tiColor);
    $('#content-wide1-region h4').addClass(wide1_tiColor);
    $('#content-wide1-region h5').addClass(wide1_tiColor);
    $('#content-wide1-region h6').addClass(wide1_tiColor);
    $('#content-wide1-region .block-title').addClass(wide1_tiColor);
    
    $('#content-wide2-region h1').addClass(wide2_tiColor);
    $('#content-wide2-region h2').addClass(wide2_tiColor);
    $('#content-wide2-region h3').addClass(wide2_tiColor);
    $('#content-wide2-region h4').addClass(wide2_tiColor);
    $('#content-wide2-region h5').addClass(wide2_tiColor);
    $('#content-wide2-region h6').addClass(wide2_tiColor);
    $('#content-wide2-region .block-title').addClass(wide2_tiColor);
    
    $('#content-wide3-region h1').addClass(wide3_tiColor);
    $('#content-wide3-region h2').addClass(wide3_tiColor);
    $('#content-wide3-region h3').addClass(wide3_tiColor);
    $('#content-wide3-region h4').addClass(wide3_tiColor);
    $('#content-wide3-region h5').addClass(wide3_tiColor);
    $('#content-wide3-region h6').addClass(wide3_tiColor);
    $('#content-wide3-region .block-title').addClass(wide3_tiColor);
    
    $('#content-wide4-region h1').addClass(wide4_tiColor);
    $('#content-wide4-region h2').addClass(wide4_tiColor);
    $('#content-wide4-region h3').addClass(wide4_tiColor);
    $('#content-wide4-region h4').addClass(wide4_tiColor);
    $('#content-wide4-region h5').addClass(wide4_tiColor);
    $('#content-wide4-region h6').addClass(wide4_tiColor);
    $('#content-wide4-region .block-title').addClass(wide4_tiColor);
    
    $('#before-footer-region h1').addClass(before_footer_tiColor);
    $('#before-footer-region h2').addClass(before_footer_tiColor);
    $('#before-footer-region h3').addClass(before_footer_tiColor);
    $('#before-footer-region h4').addClass(before_footer_tiColor);
    $('#before-footer-region h5').addClass(before_footer_tiColor);
    $('#before-footer-region h6').addClass(before_footer_tiColor);
    $('#before-footer-region .block-title').addClass(before_footer_tiColor);
    
    $('#footer-four-columns h1').addClass(footer_four_tiColor);
    $('#footer-four-columns h2').addClass(footer_four_tiColor);
    $('#footer-four-columns h3').addClass(footer_four_tiColor);
    $('#footer-four-columns h4').addClass(footer_four_tiColor);
    $('#footer-four-columns h5').addClass(footer_four_tiColor);
    $('#footer-four-columns h6').addClass(footer_four_tiColor);
    $('#footer-four-columns .block-title').addClass(footer_four_tiColor);
    
    $('footer h1').addClass(footer_tiColor);
    $('footer h2').addClass(footer_tiColor);
    $('footer h3').addClass(footer_tiColor);
    $('footer h4').addClass(footer_tiColor);
    $('footer h5').addClass(footer_tiColor);
    $('footer h6').addClass(footer_tiColor);
    $('footer .block-title').addClass(footer_tiColor);
    
    
    // Set the Link color for the regions
    var header_lColor        = Drupal.settings['settings']['header_lColor'];
    var top_content_lColor   = Drupal.settings['settings']['top_content_lColor'];
    var featured_lColor      = Drupal.settings['settings']['featured_lColor'];
    var wide1_lColor         = Drupal.settings['settings']['wide1_lColor'];
    var wide2_lColor         = Drupal.settings['settings']['wide2_lColor'];
    var wide3_lColor         = Drupal.settings['settings']['wide3_lColor'];
    var wide4_lColor         = Drupal.settings['settings']['wide4_lColor'];
    var before_footer_lColor = Drupal.settings['settings']['before_footer_lColor'];
    var footer_four_lColor   = Drupal.settings['settings']['footer_four_lColor'];
    var footer_lColor        = Drupal.settings['settings']['footer_lColor'];
    
    $('#header-region a').addClass(header_lColor);
    $('#top-content-region a').addClass(top_content_lColor);
    $('#featured-region a').addClass(featured_lColor);
    $('#content-wide1-region a').addClass(wide1_lColor);
    $('#content-wide2-region a').addClass(wide2_lColor);
    $('#content-wide3-region a').addClass(wide3_lColor);
    $('#content-wide4-region a').addClass(wide4_lColor);
    $('#before-footer-region a').addClass(before_footer_lColor);
    $('#footer-four-columns a').addClass(footer_four_lColor);
    $('footer a').addClass(footer_lColor);
    
    // Set the background color or background image for the Sequence Slider
    var slider_use_bImg = Drupal.settings['settings']['slider_use_bImg'];
    
    if (slider_use_bImg == "1") {
      // if the user chooses the background image
      var slider_bImg = Drupal.settings['settings']['slider_bImg'];
      
      $('.sequence-theme').addClass(slider_bImg);
    } else {
      // if the user chooses not to use a background image it will apply a solid background color
      var slider_color = Drupal.settings['settings']['slider_color'];

      $('.sequence-theme').addClass(slider_color);
    }

  });

})(jQuery);


// Features
(function ($) {
  
  $(document).ready(function() {
    // loading the theme color for the rounded progress bars
    var theme_color = Drupal.settings['settings']['theme_color'];
    var strokeColor = "#a0ce4e";
    
    if      (theme_color == "aqua")   { strokeColor = "#9adada"; }
    else if (theme_color == "blue")   { strokeColor = "#5daed5"; }
    else if (theme_color == "brown")  { strokeColor = "#aa876d"; }
    else if (theme_color == "green")  { strokeColor = "#77d268"; }
    else if (theme_color == "orange") { strokeColor = "#ffb141"; }
    else if (theme_color == "red")    { strokeColor = "#e24f3d"; }
    else if (theme_color == "yellow") { strokeColor = "#eed271"; }
    else if (theme_color == "custom") { strokeColor = "#94ba65"; }
  
    // tooltips
    $('.tooltips').tooltip({
      container: 'body'
    });
    
    // popovers
    $('.popovers').popover({
      container: 'body'
    });
    
    // buttons loading
    $('.btn-loading').click(function () {
      var btn = $(this)
      btn.button('loading')
      setTimeout(function () {
        btn.button('reset')
      }, 3000)
    });
    
    // Rounded skills
    $('.chart').easyPieChart({
      barColor: strokeColor,
      trackColor: "#ededed",
  		scaleColor: false,
  		lineCap: "butt",
  		lineWidth: 15,
  		animate: 2000,
  		size: 150
    });
    
    // Video blocks magic business
    $(".video").fitVids();
    
    // Testimonials slider
    $('#testimonialsCarousel').carousel({
      interval: 7000
    });
    
    // Flexslider, used in blog, articles and portfolio.
    $('.flexslider').flexslider({
      touch: true,
      animation: "slide",
      slideshow: false,
      prevText: "",
      nextText: "",
      pauseOnAction: false,
      pauseOnHover: true
    });
    
    // Different version of flex slider to use in content
    $('.flexslider2').flexslider({
      touch: true,
      animation: "slide",
      slideshow: true,
      prevText: "",
      nextText: "",
      pauseOnAction: false,
      pauseOnHover: true,
    });
    
    // Elastic slider
    $('#ei-slider').eislideshow({
      animation			: 'center',
			autoplay			: true,
			slideshow_interval	: 3000,
			titlesFactor		: 0
    });
    
    // Sequence Slider
    $("#sequence").sequence({
        nextButton: true,
        prevButton: true,
        animateStartingFrameIn: true,
        autoPlay: true,
        preloader: true
    }).data("sequence");

  });

})(jQuery);

// Portfolio isotope
(function($) {

  $(window).load(function() {
    
    var $container = $('#container-isotope')
    
    $container.isotope({
      // options
      itemSelector : '.portfolio-item',
      layoutMode : 'fitRows',
      resizable: true
    });
    
    $('#filters a').click(function(){
      var selector = $(this).attr('data-filter');
      $container.isotope({ filter: selector });      
      return false;
    });
    
    $('#filters ul.nav-pills li a').click(function() {
      $('#filters ul.nav-pills li.active').removeClass('active');
      $(this).parent('li').addClass('active')
    });

  });

})(jQuery);


// Google maps goodness
jQuery(window).load(function() {
  
  if (document.getElementById('map_canvas')) {
    
    // loading the theme settings for the google maps
    var gLatitude = Drupal.settings['settings']['google_latitude'];
    var gLongitude = Drupal.settings['settings']['google_longitude'];
    var gZoom = Drupal.settings['settings']['google_zoom'];
    var gTitle = Drupal.settings['settings']['google_title'];
    var gDescription = Drupal.settings['settings']['google_description'];
      
	  var latlng = new google.maps.LatLng(gLatitude, gLongitude);
	  
	  var settings = {
	    zoom: parseInt(gZoom),
	    center: latlng,
	    scrollwheel: false,
	    mapTypeControl: true,
	    mapTypeControlOptions: {style: google.maps.MapTypeControlStyle.DROPDOWN_MENU},
	    navigationControl: true,
	    navigationControlOptions: {style: google.maps.NavigationControlStyle.SMALL},
	    mapTypeId: google.maps.MapTypeId.ROADMAP
    };
    
    var map = new google.maps.Map(document.getElementById("map_canvas"), settings);
    
    var companyLogo = new google.maps.MarkerImage('sites/all/themes/specialone/img/google-maps/map-marker.png',
    	new google.maps.Size(20,30),
    	new google.maps.Point(0,0),
    	new google.maps.Point(10,30)
    );
    
    var companyShadow = new google.maps.MarkerImage('sites/all/themes/specialone/img/google-maps/map-shadow-marker.png',
      new google.maps.Size(19,15),
      new google.maps.Point(0,0),
      new google.maps.Point(3,14)
    );
    
    var companyMarker = new google.maps.Marker({
      position: latlng,
           map: map,
          icon: companyLogo,
        shadow: companyShadow,
         title: gTitle
    });
    
    var contentString = '<div id="content-map">'+
        '<h3 style="margin-top: 0px;">' + gTitle + '</h3>'+
        '<p>' + gDescription + '</p>'+
        '</div>';
    
    var infowindow = new google.maps.InfoWindow({
        content: contentString
    });
    
    google.maps.event.addListener(companyMarker, 'click', function() {
      infowindow.open(map,companyMarker);
    });
  
  }

});

// Some Flickr flavor
(function ($) {
  
  $(document).ready(function(){
    
    // loading the theme settings for the google maps
    var fID = Drupal.settings['settings']['flickr_id'];
    var fLimit = Drupal.settings['settings']['flickr_limit'];
    
    $('#flickr').jflickrfeed({
    	limit: parseInt(fLimit),
    	qstrings: {
    		id: fID
    	},
    	itemTemplate:
    	'<li>' +
    		'<a href="{{link}}" title="{{title}}">' +
    			'<img src="{{image_s}}" alt="{{title}}" />' +
    		'</a>' +
    	'</li>'
    });

  });

})(jQuery);