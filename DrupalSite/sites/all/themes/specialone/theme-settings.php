<?php

function specialone_form_system_theme_settings_alter(&$form, $form_state) {
  
  $theme_colors = array('aqua'   => t('Aqua'),
	                      'blue'   => t('Blue'),
	                      'brown'  => t('Brown'),
		                    'green'  => t('Green'),
		                    'orange' => t('Orange'),
		                    'red'    => t('Red'),
		                    'yellow' => t('Yellow'),
		                    'custom' => t('Custom'));
	
	$background_colors = array('bg-color-theme'        => t('Theme Color'),
	                           'bg-color-white'        => t('White'),
                             'bg-color-grayDark1'    => t('Gray Dark 1'),
                		         'bg-color-grayDark2'    => t('Gray Dark 2'),
                		         'bg-color-grayLight1'   => t('Gray Light 1'),
                		         'bg-color-grayLight2'   => t('Gray Light 2'),
                		         'bg-color-turquoise'    => t('Turquoise'),
                		         'bg-color-greenSea'     => t('Green Sea'),
                		         'bg-color-emerald'      => t('Emerald'),
                			       'bg-color-nephritis'    => t('Nephritis'),
                			       'bg-color-sunFlower'    => t('Sun Flower'),
                			       'bg-color-orange'       => t('Orange'),
                			       'bg-color-carrot'       => t('Carrot'),
                			       'bg-color-pumpkin'      => t('Pumpkin'),
                			       'bg-color-peterRiver'   => t('Peter River'),
                		         'bg-color-belizeHole'   => t('Belize Hole'),
                		         'bg-color-alizarin'     => t('Alizarin'),
                			       'bg-color-pomegranate'  => t('Pomegranate'),
                			       'bg-color-amethyst'     => t('Amethyst'),
                			       'bg-color-wisteria'     => t('Wisteria'),
                			       'bg-color-clouds'       => t('Clouds'),
                			       'bg-color-silver'       => t('Silver'),
                			       'bg-color-wetAsphalt'   => t('Wet Asphalt'),
                			       'bg-color-midnightBlue' => t('Midnight Blue'),
                			       'bg-color-concrete'     => t('Concrete'),
                			       'bg-color-asbestos'     => t('Asbestos'),
                			       'bg-color-custom'       => t('Custom'));
	
	$text_colors = array('text-color-theme'      => t('Theme Color'),
	                     'text-color-white'      => t('White'),
	                     'text-color-grayDark1'  => t('Gray Dark 1'),
	                     'text-color-grayDark2'  => t('Gray Dark 2'),
	                     'text-color-grayLight1' => t('Gray Light 1'),
	                     'text-color-grayLight2' => t('Gray Light 2'),
	                     'text-color-grayLight3' => t('Gray Light 3'),
	                     'text-color-custom'     => t('Custom'));
	
	$background_patterns = array('bg-pattern-45degreee_fabric'       => t('45 Degreee Fabric'),
	                             'bg-pattern-agsquare'               => t('Agsquare'),
	                             'bg-pattern-asfalt'                 => t('Asfalt'),
	                             'bg-pattern-bedge_grunge'           => t('Bedge Grunge'),
	                             'bg-pattern-billie_holiday'         => t('Billie Holiday'),
	                             'bg-pattern-binding_dark'           => t('Binding Dark'),
	                             'bg-pattern-binding_light'          => t('Binding Light'),
	                             'bg-pattern-black_linen'            => t('Black Linen'),
	                             'bg-pattern-blackorchid'            => t('Blackorchid'),
	                             'bg-pattern-brickwall'              => t('Brickwall'),
	                             'bg-pattern-bright_squares'         => t('Bright Squares'),
	                             'bg-pattern-brillant'               => t('Brillant'),
	                             'bg-pattern-brushed_alu_dark'       => t('Brushed Alu Dark'),
	                             'bg-pattern-brushed_alu'            => t('Brushed Alu'),
	                             'bg-pattern-carbon_fibre_big'       => t('Carbon Fibre Big'),
	                             'bg-pattern-cardboard_flat'         => t('Cardboard Flat'),
	                             'bg-pattern-cartographer'           => t('Cartographer'),
	                             'bg-pattern-chruch'                 => t('Chruch'),
	                             'bg-pattern-climpek'                => t('Climpek'),
	                             'bg-pattern-concrete_wall_3'        => t('Concrete Wall 3'),
	                             'bg-pattern-cream_pixels'           => t('Cream Pixels'),
	                             'bg-pattern-crisp_paper_ruffles'    => t('Crisp Paper Ruffles'),
	                             'bg-pattern-cross_scratches'        => t('Cross Scratches'),
	                             'bg-pattern-crossed_stripes'        => t('Crossed Stripes'),
	                             'bg-pattern-dark_dotted'            => t('Dark Dotted'),
	                             'bg-pattern-dark_dotted2'           => t('Dark Dotted 2'),
	                             'bg-pattern-dark_fish_skin'         => t('Dark Fish Skin'),
	                             'bg-pattern-dark_geometric'         => t('Dark Geometric'),
	                             'bg-pattern-dark_mosaic'            => t('Dark Mosaic'),
	                             'bg-pattern-dark_wood'              => t('Dark Wood'),
	                             'bg-pattern-debut_dark'             => t('Debut Dark'),
	                             'bg-pattern-debut_light'            => t('Debut Light'),
	                             'bg-pattern-diagonales_decalees'    => t('Diagonales Decalees'),
	                             'bg-pattern-dust'                   => t('Dust'),
	                             'bg-pattern-escheresque_ste'        => t('Escheresque Ste'),
	                             'bg-pattern-fabric_of_squares_gray' => t('Fabric of Squares Gray'),
	                             'bg-pattern-fabric_plaid'           => t('Fabric Plaid'),
	                             'bg-pattern-gplaypattern'           => t('GPlay Pattern'),
	                             'bg-pattern-grey'                   => t('Grey'),
	                             'bg-pattern-grey_wash_wall'         => t('Grey Wash Wall'),
	                             'bg-pattern-greyfloral'             => t('Greyfloral'),
	                             'bg-pattern-honey_im_subtle'        => t('Honey I am subtle'),
	                             'bg-pattern-low_contrast_linen'     => t('Low contrast Linen'),
	                             'bg-pattern-mochaGrunge'            => t('Mocha Grunge'),
	                             'bg-pattern-mooning'                => t('Mooning'),
	                             'bg-pattern-navy_blue'              => t('Navy Blue'),
	                             'bg-pattern-otis_redding'           => t('Otis Redding'),
	                             'bg-pattern-p1'                     => t('P1'),
	                             'bg-pattern-p2'                     => t('P2'),
	                             'bg-pattern-p4'                     => t('P4'),
	                             'bg-pattern-p5'                     => t('P5'),
	                             'bg-pattern-p6'                     => t('P6'),
	                             'bg-pattern-ps_neutral'             => t('Ps Neutral'),
	                             'bg-pattern-pw_maze_black'          => t('Pw Maze Black'),
	                             'bg-pattern-pw_pattern'             => t('Pw Pattern'),
	                             'bg-pattern-retina_wood'            => t('Retina Wood'),
	                             'bg-pattern-shattered'              => t('Shattered'),
	                             'bg-pattern-skelatal_weave'         => t('Skelatal Weave'),
	                             'bg-pattern-slash_it'               => t('Slash it'),
	                             'bg-pattern-squairy_light'          => t('Squairy Light'),
	                             'bg-pattern-subtle_grunge'          => t('Subtle Grunge'),
	                             'bg-pattern-subtle_surface'         => t('Subtle Surface'),
	                             'bg-pattern-textured_paper'         => t('Textured Paper'),
                               'bg-pattern-ticks'                  => t('Ticks'),
	                             'bg-pattern-tileable_wood_texture'  => t('Tileable Wood Texture'),
	                             'bg-pattern-tweed'                  => t('Tweed'),
	                             'bg-pattern-type'                   => t('Type'),
	                             'bg-pattern-use_your_illusion'      => t('Use Your Illusion'),
	                             'bg-pattern-washi'                  => t('Washi'),
	                             'bg-pattern-wavegrid'               => t('Wavegrid'),
	                             'bg-pattern-white_wall_hash'        => t('White Wall Hash'),
	                             'bg-pattern-wild_oliva'             => t('Wild Oliva'),
	                             'bg-pattern-witewall_3'             => t('Wite Wall 3'));
  
  $background_images = array('bg-image-one'       => t('Background Image One'),
                             'bg-image-two'       => t('Background Image Two'),
                             'bg-image-three'     => t('Background Image Three'),
                             'bg-image-four'      => t('Background Image Four'),
                             'bg-image-five'      => t('Background Image Five'),
                             'bg-image-six'       => t('Background Image Six'),
                             'bg-image-seven'     => t('Background Image Seven'),
                             'bg-image-eight'     => t('Background Image Eight'),
                             'bg-image-nine'      => t('Background Image Nine'),
                             'bg-image-ten'       => t('Background Image Ten'),
                             'bg-image-eleven'    => t('Background Image Eleven'),
                             'bg-image-twelve'    => t('Background Image Twelve'),
                             'bg-image-thirteen'  => t('Background Image Thirteen'),
                             'bg-image-fourteen'  => t('Background Image Fourteen'),
                             'bg-image-fifteen'   => t('Background Image Fifteen'),
                             'bg-image-sixteen'   => t('Background Image Sixteen'),
                             'bg-image-seventeen' => t('Background Image Seventeen'),
                             'bg-image-eighteen'  => t('Background Image Eighteen'),
                             'bg-image-nineteen'  => t('Background Image Nineteen'),
                             'bg-image-twenty'    => t('Background Image Twenty'),
                             'bg-image-twentyOne' => t('Background Image Twenty One'),
                             'bg-image-twentyTwo' => t('Background Image Twenty Two'));
	
	$form['settings'] = array(     
		'#type' => 'vertical_tabs',  
		'#title' => t('Special One Settings'),
		'#weight' => 2,              
		'#collapsible' => TRUE,      
		'#collapsed' => FALSE,       
	);                             
                                 

  /************************/
	/*** General Settings ***/
	/************************/

	$form['settings']['general'] = array(
		'#type' => 'fieldset',
		'#title' => t('General settings'),
		'#collapsible' => TRUE,
		'#collapsed' => FALSE,
	);
	
	// Layout version
	$form['settings']['general']['layout'] = array(
		'#type' => 'fieldset',
		'#title' => t('Layout settings'),
		'#collapsible' => TRUE,
		'#collapsed' => TRUE,
	);
	
	$form['settings']['general']['layout']['layout_version'] = array(
		'#type' => 'select',
		'#title' => t('Layout Version'),
		'#options' => array('wide' => 'Wide', 'boxed' => "Boxed"),
		'#default_value' => theme_get_setting('layout_version'),
		'#description' => t('Set the layout version of your theme.'),
	);
	
	// Theme Colors
	$form['settings']['general']['colors'] = array(
		'#type' => 'fieldset',
		'#title' => t('Color settings'),
		'#collapsible' => TRUE,
		'#collapsed' => TRUE,
	);
	
	$form['settings']['general']['colors']['theme_color'] = array(
		'#type' => 'select',
		'#title' => t('Theme Color'),
		'#options' => $theme_colors,
		'#default_value' => theme_get_setting('theme_color'),
		'#description' => t('Set the main color of your theme.'),
	);
	
	$form['settings']['general']['colors']['boxed_bColor'] = array(
		'#type' => 'select',
		'#title' => t('Boxed Color'),
		'#options' => $background_colors,
		'#default_value' => theme_get_setting('boxed_bColor'),
		'#description' => t('Set the background color for the boxed version.'),
	);
	
	$form['settings']['general']['colors']['use_bPattern'] = array(
		'#type' => 'radios',
		'#title' => t('Do you want a background Pattern?'),
		'#options' => array('0' => t('No'), '1' => t('Yes')),
		'#default_value' => theme_get_setting('use_bPattern'),
		'#description' => t('If you want to use a background pattern instead of a background color choose \'Yes\'.'),
	);
	
	$form['settings']['general']['colors']['boxed_bPattern'] = array(
		'#type' => 'select',
		'#title' => t('Boxed Pattern'),
		'#options' => $background_patterns,
		'#default_value' => theme_get_setting('boxed_bPattern'),
		'#description' => t('Set the background pattern for the boxed version.'),
	);
	
	// Breadcrumbs
	
	$form['settings']['general']['breadcrumb'] = array(
		'#type' => 'fieldset',
		'#title' => t('Breadcrumb settings'),
		'#collapsible' => TRUE,
		'#collapsed' => TRUE,
	);
	
	$form['settings']['general']['breadcrumb']['breadcrumb_position'] = array(
		'#type' => 'select',
		'#title' => t('Breadcrumb position'),
		'#options' => array(
		  'none' => t('-none-'),
		  'left' => t('Left'),
		  'right' => t('Right')
		),
		'#default_value' => theme_get_setting('breadcrumb_position')
	);
	
	$form['settings']['general']['breadcrumb']['breadcrumb_delimiter'] = array(
		'#type' => 'textfield',
		'#title' => t('Breadcrumb Delimiter'),
		'#default_value' => theme_get_setting('breadcrumb_delimiter'),
		'#size' => 10,
		'#maxlength' => 10,
	);
	
	// Demo switcher
	$form['settings']['general']['demo'] = array(
	  '#type' => 'fieldset',
	  '#title' => t('Demo settings'),
	  '#collapsible' => TRUE,
	  '#collapsed' => TRUE
	);
	
	$form['settings']['general']['demo']['switcher'] = array(
	  '#type' => 'radios',
		'#title' => t('Activate switcher'),
		'#options' => array('on' => t('on'), 'off' => t('off')),
		'#default_value' => theme_get_setting('switcher'),
		'#description' => t('Set the switcher on or off.'),
	);
	
	
	/************************/
	/*** Regions Settings ***/
	/************************/
	
	$form['settings']['regions'] = array(
		'#type' => 'fieldset',
		'#title' => t('Regions'),
		'#collapsible' => TRUE,
		'#collapsed' => FALSE,
	);
	
	// Header region
	$form['settings']['regions']['header_region'] = array(
		'#type' => 'fieldset',
		'#title' => t('Header Region'),
		'#collapsible' => TRUE,
		'#collapsed' => TRUE,
	);
	
	$form['settings']['regions']['header_region']['header_bColor'] = array(
		'#type' => 'select',
		'#title' => t('Background Color'),
		'#options' => $background_colors,
		'#default_value' => theme_get_setting('header_bColor'),
		'#description' => t('Set the Background Color for your Header Region.'),
	);
	
	$form['settings']['regions']['header_region']['header_tColor'] = array(
		'#type' => 'select',
		'#title' => t('Text Color'),
		'#options' => $text_colors,
		'#default_value' => theme_get_setting('header_tColor'),
		'#description' => t('Set the Text Color for your Header Region.'),
	);
	
	$form['settings']['regions']['header_region']['header_tiColor'] = array(
		'#type' => 'select',
		'#title' => t('Title Color'),
		'#options' => $text_colors,
		'#default_value' => theme_get_setting('header_tiColor'),
		'#description' => t('Set the Color for your Titles in Header Region.'),
	);
	
	$form['settings']['regions']['header_region']['header_lColor'] = array(
		'#type' => 'select',
		'#title' => t('Link Color'),
		'#options' => $text_colors,
		'#default_value' => theme_get_setting('header_lColor'),
		'#description' => t('Set the Color for your Links in Header Region.'),
	);
	
	// Top content region
	$form['settings']['regions']['top_content_region'] = array(
		'#type' => 'fieldset',
		'#title' => t('Top Content Region'),
		'#collapsible' => TRUE,
		'#collapsed' => TRUE,
	);
	
	$form['settings']['regions']['top_content_region']['top_content_bColor'] = array(
		'#type' => 'select',
		'#title' => t('Background Color'),
		'#options' => $background_colors,
		'#default_value' => theme_get_setting('top_content_bColor'),
		'#description' => t('Set the Background Color for your Top Content Region.'),
	);
	
	$form['settings']['regions']['top_content_region']['top_content_tColor'] = array(
		'#type' => 'select',
		'#title' => t('Text Color'),
		'#options' => $text_colors,
		'#default_value' => theme_get_setting('top_content_tColor'),
		'#description' => t('Set the Text Color for your Top Content Region.'),
	);
	
	$form['settings']['regions']['top_content_region']['top_content_tiColor'] = array(
		'#type' => 'select',
		'#title' => t('Title Color'),
		'#options' => $text_colors,
		'#default_value' => theme_get_setting('top_content_tiColor'),
		'#description' => t('Set the Color for your Titles in Top Content Region.'),
	);
	
	$form['settings']['regions']['top_content_region']['top_content_lColor'] = array(
		'#type' => 'select',
		'#title' => t('Link Color'),
		'#options' => $text_colors,
		'#default_value' => theme_get_setting('top_content_lColor'),
		'#description' => t('Set the Color for your Links in Top Content Region.'),
	);
	
	// Featured Region
	$form['settings']['regions']['featured_region'] = array(
		'#type' => 'fieldset',
		'#title' => t('Featured Region'),
		'#collapsible' => TRUE,
		'#collapsed' => TRUE,
	);
	
	$form['settings']['regions']['featured_region']['featured_bColor'] = array(
		'#type' => 'select',
		'#title' => t('Background Color'),
		'#options' => $background_colors,
		'#default_value' => theme_get_setting('featured_bColor'),
		'#description' => t('Set the Background Color for your Featured Region.'),
	);
	
	$form['settings']['regions']['featured_region']['featured_tColor'] = array(
		'#type' => 'select',
		'#title' => t('Text Color'),
		'#options' => $text_colors,
		'#default_value' => theme_get_setting('featured_tColor'),
		'#description' => t('Set the Text Color for your Featured Region.'),
	);
	
	$form['settings']['regions']['featured_region']['featured_tiColor'] = array(
		'#type' => 'select',
		'#title' => t('Title Color'),
		'#options' => $text_colors,
		'#default_value' => theme_get_setting('featured_tiColor'),
		'#description' => t('Set the Color for your Titles in Featured Region.'),
	);
	
	$form['settings']['regions']['featured_region']['featured_lColor'] = array(
		'#type' => 'select',
		'#title' => t('Link Color'),
		'#options' => $text_colors,
		'#default_value' => theme_get_setting('featured_lColor'),
		'#description' => t('Set the Color for your Links in Featured Region.'),
	);
	
	// Wide1 Region
	$form['settings']['regions']['wide1_region'] = array(
		'#type' => 'fieldset',
		'#title' => t('Content Wide1 Region'),
		'#collapsible' => TRUE,
		'#collapsed' => TRUE,
	);
	
	$form['settings']['regions']['wide1_region']['wide1_bColor'] = array(
		'#type' => 'select',
		'#title' => t('Background Color'),
		'#options' => $background_colors,
		'#default_value' => theme_get_setting('wide1_bColor'),
		'#description' => t('Set the Background Color for your Content Wide1 Region.'),
	);
	
	$form['settings']['regions']['wide1_region']['wide1_tColor'] = array(
		'#type' => 'select',
		'#title' => t('Text Color'),
		'#options' => $text_colors,
		'#default_value' => theme_get_setting('wide1_tColor'),
		'#description' => t('Set the Text Color for your Content Wide1 Region.'),
	);
	
	$form['settings']['regions']['wide1_region']['wide1_tiColor'] = array(
		'#type' => 'select',
		'#title' => t('Title Color'),
		'#options' => $text_colors,
		'#default_value' => theme_get_setting('wide1_tiColor'),
		'#description' => t('Set the Color for your Titles in Content Wide1 Region.'),
	);
	
	$form['settings']['regions']['wide1_region']['wide1_lColor'] = array(
		'#type' => 'select',
		'#title' => t('Link Color'),
		'#options' => $text_colors,
		'#default_value' => theme_get_setting('wide1_lColor'),
		'#description' => t('Set the Color for your Links in Content Wide1 Region.'),
	);
	
	$form['settings']['regions']['wide1_region']['wide1_use_bImg'] = array(
		'#type' => 'radios',
		'#title' => t('Do you want a background Image?'),
		'#options' => array('0' => t('No'), '1' => t('Yes')),
		'#default_value' => theme_get_setting('wide1_use_bImg'),
		'#description' => t('If you want to use a background image instead of a background color choose \'Yes\'.'),
	);
	
	$form['settings']['regions']['wide1_region']['wide1_bImg'] = array(
		'#type' => 'select',
		'#title' => t('Content Wide1 Region Image Background'),
		'#options' => $background_images,
		'#default_value' => theme_get_setting('wide1_bImg'),
		'#description' => t('Set the background image of your Content Wide1 Region.'),
	);
	
	// Wide2 Region
	$form['settings']['regions']['wide2_region'] = array(
		'#type' => 'fieldset',
		'#title' => t('Content Wide2 Region'),
		'#collapsible' => TRUE,
		'#collapsed' => TRUE,
	);
	
	$form['settings']['regions']['wide2_region']['wide2_bColor'] = array(
		'#type' => 'select',
		'#title' => t('Background Color'),
		'#options' => $background_colors,
		'#default_value' => theme_get_setting('wide2_bColor'),
		'#description' => t('Set the Background Color for your Content Wide2 Region.'),
	);
	
	$form['settings']['regions']['wide2_region']['wide2_tColor'] = array(
		'#type' => 'select',
		'#title' => t('Text Color'),
		'#options' => $text_colors,
		'#default_value' => theme_get_setting('wide2_tColor'),
		'#description' => t('Set the Text Color for your Content Wide2 Region.'),
	);
	
	$form['settings']['regions']['wide2_region']['wide2_tiColor'] = array(
		'#type' => 'select',
		'#title' => t('Title Color'),
		'#options' => $text_colors,
		'#default_value' => theme_get_setting('wide2_tiColor'),
		'#description' => t('Set the Color for your Titles in Content Wide2 Region.'),
	);
	
	$form['settings']['regions']['wide2_region']['wide2_lColor'] = array(
		'#type' => 'select',
		'#title' => t('Link Color'),
		'#options' => $text_colors,
		'#default_value' => theme_get_setting('wide2_lColor'),
		'#description' => t('Set the Color for your Links in Content Wide2 Region.'),
	);
	
	// Wide3 Region
	$form['settings']['regions']['wide3_region'] = array(
		'#type' => 'fieldset',
		'#title' => t('Content Wide3 Region'),
		'#collapsible' => TRUE,
		'#collapsed' => TRUE,
	);
	
	$form['settings']['regions']['wide3_region']['wide3_bColor'] = array(
		'#type' => 'select',
		'#title' => t('Background Color'),
		'#options' => $background_colors,
		'#default_value' => theme_get_setting('wide3_bColor'),
		'#description' => t('Set the Background Color for your Content Wide3 Region.'),
	);
	
	$form['settings']['regions']['wide3_region']['wide3_tColor'] = array(
		'#type' => 'select',
		'#title' => t('Text Color'),
		'#options' => $text_colors,
		'#default_value' => theme_get_setting('wide3_tColor'),
		'#description' => t('Set the Text Color for your Content Wide3 Region.'),
	);
	
	$form['settings']['regions']['wide3_region']['wide3_tiColor'] = array(
		'#type' => 'select',
		'#title' => t('Title Color'),
		'#options' => $text_colors,
		'#default_value' => theme_get_setting('wide3_tiColor'),
		'#description' => t('Set the Color for your Titles in Content Wide3 Region.'),
	);
	
	$form['settings']['regions']['wide3_region']['wide3_lColor'] = array(
		'#type' => 'select',
		'#title' => t('Link Color'),
		'#options' => $text_colors,
		'#default_value' => theme_get_setting('wide3_lColor'),
		'#description' => t('Set the Color for your Links in Content Wide3 Region.'),
	);
	
	$form['settings']['regions']['wide3_region']['wide3_use_bImg'] = array(
		'#type' => 'radios',
		'#title' => t('Do you want a background Image?'),
		'#options' => array('0' => t('No'), '1' => t('Yes')),
		'#default_value' => theme_get_setting('wide3_use_bImg'),
		'#description' => t('If you want to use a background image instead of a background color choose \'Yes\'.'),
	);
	
	$form['settings']['regions']['wide3_region']['wide3_bImg'] = array(
		'#type' => 'select',
		'#title' => t('Content Wide3 Region Image Background'),
		'#options' => $background_images,
		'#default_value' => theme_get_setting('wide3_bImg'),
		'#description' => t('Set the background image of your Content Wide3 Region.'),
	);
	
	// Wide4 Region
	$form['settings']['regions']['wide4_region'] = array(
		'#type' => 'fieldset',
		'#title' => t('Content Wide4 Region'),
		'#collapsible' => TRUE,
		'#collapsed' => TRUE,
	);
	
	$form['settings']['regions']['wide4_region']['wide4_bColor'] = array(
		'#type' => 'select',
		'#title' => t('Background Color'),
		'#options' => $background_colors,
		'#default_value' => theme_get_setting('wide4_bColor'),
		'#description' => t('Set the Background Color for your Content Wide4 Region.'),
	);
	
	$form['settings']['regions']['wide4_region']['wide4_tColor'] = array(
		'#type' => 'select',
		'#title' => t('Text Color'),
		'#options' => $text_colors,
		'#default_value' => theme_get_setting('wide4_tColor'),
		'#description' => t('Set the Text Color for your Content Wide4 Region.'),
	);
	
	$form['settings']['regions']['wide4_region']['wide4_tiColor'] = array(
		'#type' => 'select',
		'#title' => t('Title Color'),
		'#options' => $text_colors,
		'#default_value' => theme_get_setting('wide4_tiColor'),
		'#description' => t('Set the Color for your Titles in Content Wide4 Region.'),
	);
	
	$form['settings']['regions']['wide4_region']['wide4_lColor'] = array(
		'#type' => 'select',
		'#title' => t('Link Color'),
		'#options' => $text_colors,
		'#default_value' => theme_get_setting('wide4_lColor'),
		'#description' => t('Set the Color for your Links in Content Wide4 Region.'),
	);
	
	// Before Footer Region
	$form['settings']['regions']['before_footer_region'] = array(
		'#type' => 'fieldset',
		'#title' => t('Before Footer Region'),
		'#collapsible' => TRUE,
		'#collapsed' => TRUE,
	);
	
	$form['settings']['regions']['before_footer_region']['before_footer_bColor'] = array(
		'#type' => 'select',
		'#title' => t('Background Color'),
		'#options' => $background_colors,
		'#default_value' => theme_get_setting('before_footer_bColor'),
		'#description' => t('Set the Background Color for your Before Footer Region.'),
	);
	
	$form['settings']['regions']['before_footer_region']['before_footer_tColor'] = array(
		'#type' => 'select',
		'#title' => t('Text Color'),
		'#options' => $text_colors,
		'#default_value' => theme_get_setting('before_footer_tColor'),
		'#description' => t('Set the Text Color for your Before Footer Region.'),
	);
	
	$form['settings']['regions']['before_footer_region']['before_footer_tiColor'] = array(
		'#type' => 'select',
		'#title' => t('Title Color'),
		'#options' => $text_colors,
		'#default_value' => theme_get_setting('before_footer_tiColor'),
		'#description' => t('Set the Color for your Titles in Before Footer Region.'),
	);
	
	$form['settings']['regions']['before_footer_region']['before_footer_lColor'] = array(
		'#type' => 'select',
		'#title' => t('Link Color'),
		'#options' => $text_colors,
		'#default_value' => theme_get_setting('before_footer_lColor'),
		'#description' => t('Set the Color for your Links in Before Footer Region.'),
	);
	
	// Footer Four Columns Region
	$form['settings']['regions']['footer_four_region'] = array(
		'#type' => 'fieldset',
		'#title' => t('Footer Four Columns Region'),
		'#collapsible' => TRUE,
		'#collapsed' => TRUE,
	);
	
	$form['settings']['regions']['footer_four_region']['footer_four_bColor'] = array(
		'#type' => 'select',
		'#title' => t('Background Color'),
		'#options' => $background_colors,
		'#default_value' => theme_get_setting('footer_four_bColor'),
		'#description' => t('Set the Background Color for your Footer Four Columns Region.'),
	);
	
	$form['settings']['regions']['footer_four_region']['footer_four_tColor'] = array(
		'#type' => 'select',
		'#title' => t('Text Color'),
		'#options' => $text_colors,
		'#default_value' => theme_get_setting('footer_four_tColor'),
		'#description' => t('Set the Text Color for your Footer Four Columns Region.'),
	);
	
	$form['settings']['regions']['footer_four_region']['footer_four_tiColor'] = array(
		'#type' => 'select',
		'#title' => t('Title Color'),
		'#options' => $text_colors,
		'#default_value' => theme_get_setting('footer_four_tiColor'),
		'#description' => t('Set the Color for your Titles in Footer Four Columns Region.'),
	);
	
	$form['settings']['regions']['footer_four_region']['footer_four_lColor'] = array(
		'#type' => 'select',
		'#title' => t('Link Color'),
		'#options' => $text_colors,
		'#default_value' => theme_get_setting('footer_four_lColor'),
		'#description' => t('Set the Color for your Links in Footer Four Columns Region.'),
	);
	
	// Footer Region
	$form['settings']['regions']['footer_region'] = array(
		'#type' => 'fieldset',
		'#title' => t('Footer Region'),
		'#collapsible' => TRUE,
		'#collapsed' => TRUE,
	);
	
	$form['settings']['regions']['footer_region']['footer_bColor'] = array(
		'#type' => 'select',
		'#title' => t('Background Color'),
		'#options' => $background_colors,
		'#default_value' => theme_get_setting('footer_bColor'),
		'#description' => t('Set the Background Color for your Footer Region.'),
	);
	
	$form['settings']['regions']['footer_region']['footer_tColor'] = array(
		'#type' => 'select',
		'#title' => t('Text Color'),
		'#options' => $text_colors,
		'#default_value' => theme_get_setting('footer_tColor'),
		'#description' => t('Set the Text Color for your Footer Region.'),
	);
	
	$form['settings']['regions']['footer_region']['footer_tiColor'] = array(
		'#type' => 'select',
		'#title' => t('Title Color'),
		'#options' => $text_colors,
		'#default_value' => theme_get_setting('footer_tiColor'),
		'#description' => t('Set the Color for your Titles in Footer Region.'),
	);
	
	$form['settings']['regions']['footer_region']['footer_lColor'] = array(
		'#type' => 'select',
		'#title' => t('Link Color'),
		'#options' => $text_colors,
		'#default_value' => theme_get_setting('footer_lColor'),
		'#description' => t('Set the Color for your Links in Footer Region.'),
	);
	
	
	/************************/
	/*** Sequence Slider  ***/
	/************************/
	$form['settings']['sequence_slider'] = array(
		'#type' => 'fieldset',
		'#title' => t('Sequence Slider'),
		'#collapsible' => TRUE,
		'#collapsed' => FALSE,
	);
	
	$form['settings']['sequence_slider']['colors'] = array(
		'#type' => 'fieldset',
		'#title' => t('Color settings'),
		'#collapsible' => TRUE,
		'#collapsed' => FALSE,
	);
	
	$form['settings']['sequence_slider']['colors']['slider_color'] = array(
		'#type' => 'select',
		'#title' => t('Sequence Slider background color'),
		'#options' => $background_colors,
		'#default_value' => theme_get_setting('slider_color'),
		'#description' => t('Set the background color of your Sequence Slider.'),
	);
	
	$form['settings']['sequence_slider']['colors']['slider_use_bImg'] = array(
		'#type' => 'radios',
		'#title' => t('Do you want a background Image?'),
		'#options' => array('0' => t('No'), '1' => t('Yes')),
		'#default_value' => theme_get_setting('slider_use_bImg'),
		'#description' => t('If you want to use a background image instead of a background color choose \'Yes\'.'),
	);
	
	$form['settings']['sequence_slider']['colors']['slider_bImg'] = array(
		'#type' => 'select',
		'#title' => t('Sequence Slider Image Background'),
		'#options' => $background_images,
		'#default_value' => theme_get_setting('slider_bImg'),
		'#description' => t('Set the background image of your Sequence Slider.'),
	);
	
	
	/************************/
	/*** Maintenance page ***/
	/************************/
	$form['settings']['maintenance'] = array(
		'#type' => 'fieldset',
		'#title' => t('Maintenance page'),
		'#collapsible' => TRUE,
		'#collapsed' => FALSE,
	);
	
	$form['settings']['maintenance']['email'] = array(
		'#type' => 'fieldset',
		'#title' => t('Email settings'),
		'#collapsible' => TRUE,
		'#collapsed' => FALSE,
	);
	
	$form['settings']['maintenance']['email']['email_maintenance'] = array(
		'#type' => 'textfield',
		'#title' => t('Email for maintenance'),
		'#default_value' => theme_get_setting('email_maintenance'),
		'#size' => 50,
		'#maxlength' => 50,
	);
	
	
	/************************/
	/***   Google Maps    ***/
	/************************/
	
	$form['settings']['google_maps'] = array(
		'#type' => 'fieldset',
		'#title' => t('Google maps'),
		'#collapsible' => TRUE,
		'#collapsed' => FALSE,
	);
	
	$form['settings']['google_maps']['latitude'] = array(
		'#type' => 'textfield',
		'#title' => t('Latitude'),
		'#default_value' => theme_get_setting('latitude'),
		'#size' => 50,
		'#maxlength' => 50,
	);
	
	$form['settings']['google_maps']['longitude'] = array(
		'#type' => 'textfield',
		'#title' => t('Longitude'),
		'#default_value' => theme_get_setting('longitude'),
		'#size' => 50,
		'#maxlength' => 50,
	);
	
	$form['settings']['google_maps']['google_zoom'] = array(
		'#type' => 'select',
		'#title' => t('Google maps zoom'),
		'#options' => array('1'  => '1',  '2'  => '2',  '3'  => '3',  '4'  => '4',  '5'  => '5',
		                    '6'  => '6',  '7'  => '7',  '8'  => '8',  '9'  => '9',  '10' => '10',
		                    '11' => '11', '12' => '12', '13' => '13', '14' => '14', '15' => '15',
		                    '16' => '16', '17' => '17', '18' => '18', '19' => '19', '20' => '20'),
		'#default_value' => theme_get_setting('google_zoom'),
		'#description' => t('Set the zoom for your google maps.'),
	);
	
	$form['settings']['google_maps']['google_title'] = array(
		'#type' => 'textfield',
		'#title' => t('Google maps title'),
		'#default_value' => theme_get_setting('google_title'),
		'#size' => 50,
		'#maxlength' => 50,
	);
	
	$form['settings']['google_maps']['google_description'] = array(
		'#type' => 'textarea',
		'#title' => t('Google maps description'),
		'#default_value' => theme_get_setting('google_description'),
		'#size' => 500,
		'#maxlength' => 500,
	);
	
	
	/************************/
	/***      Flickr      ***/
	/************************/

	$form['settings']['flickr'] = array(
		'#type' => 'fieldset',
		'#title' => t('Flickr'),
		'#collapsible' => TRUE,
		'#collapsed' => FALSE,
	);
	
	$form['settings']['flickr']['flickr_id'] = array(
		'#type' => 'textfield',
		'#title' => t('User ID'),
		'#default_value' => theme_get_setting('flickr_id'),
		'#size' => 50,
		'#maxlength' => 50,
	);
	
	$form['settings']['flickr']['flickr_limit'] = array(
		'#type' => 'select',
		'#title' => t('Number of images'),
		'#options' => array('1' => '1', '2' => '2', '3' => '3', '4' => '4', '5' => '5',
		                    '6' => '6', '7' => '7', '8' => '8', '9' => '9'),
		'#default_value' => theme_get_setting('flickr_limit'),
		'#description' => t('Set the number of images to show up in the flickr block.'),
	);
	
}