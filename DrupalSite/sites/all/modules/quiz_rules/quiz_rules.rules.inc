<?php

/**
* Implementation of hook_rules_action_info().
*/
function quiz_rules_rules_action_info() {
	$actions = array(
		'quiz_rules_action_create_role' => array(
			'label' => t('Create a new role'),
			'group' => t('Quiz Rules'),
			'parameter' => array(
				'prefix' => array(
					'type' => 'text',
					'label' => t('Prefix to add to role name'),
					'optional' => TRUE,
					),
				'suffix' => array(
					'type' => 'text',
					'label' => t('Suffix to add to role name'),
					'optional' => TRUE,
					),
				'target' => array(
					'type' => 'text',
					'label' => t('Target of role name'),
					),
				),
			'provides' => array(
        		'new_role_name' => array(
          			'type' => 'text',
          			'label' => t('Name of new role that was created'),
        			),
				),
			),
		);

		if(module_exists('content_access_rules')){
			$actions['quiz_rules_action_assign_content_access_role'] = array(
				'label' => t('Assign view access to role'),
				'description' => t('Content type must have per node access enabled using Content Access module.'),
				'group' => t('Quiz Rules'),
				'parameter' => array(
					'role_name' => array(
						'type' => 'text',
						'label' => t('Name of role to give view access'),
						),
					'quiz' => array(
						'type' => 'node',
						'label' => t('Newly created quiz')
						),
					),
				);
		}

	return $actions;
}

function quiz_rules_action_create_role($prefix, $suffix, $target) {
	
	
	$name = $target;
	if(isset($prefix)) {
		$name = $prefix . $name;
	}
	if(isset($suffix)) {
		$name = $name . $suffix;	
	}
	
	$existingRole = user_role_load_by_name($name);
	if($existingRole){
		drupal_set_message('Role already exists: ' . $name, 'warning');
		return;
	}

	$newRole = new stdClass();
	$newRole->name = $name;
	user_role_save($newRole);
	drupal_set_message('Role created: ' . $name, 'status');

	return array(
    	'new_role_name' => $name,
  	);
}

function quiz_rules_action_assign_content_access_role($role_name, $quiz) {
	module_load_include('inc', 'content_access_rules', 'content_access_rules.rules');

	$ca = array();
	$ca['view:'.$role_name] = $role_name;

	$params = array(
		'node' => $quiz,
		'content_access' => $ca,
		);
	content_access_action_grant_node_permissions($params);

}

/**
* Implementation of hook_rules_event_info().
*/
function quiz_rules_rules_event_info() {
  return array(
    'quiz_rules_quiz_passed' => array(
      'label' => t('User has passed a quiz'),
      'group' => t('Quiz Rules'),
      'variables' => array(
        'user' => array('type' => 'user', 'label' => t('Quiz Taker')),
        'author' => array('type' => 'user', 'label' => t('Quiz Author')),
        'node' => array('type' => 'node', 'label' => t('Quiz')),
      ),
    ),
    'quiz_rules_quiz_failed' => array(
      'label' => t('User has failed a quiz'),
      'group' => t('Quiz Rules'),
      'variables' => array(
        'user' => array('type' => 'user', 'label' => t('Quiz Taker')),
        'author' => array('type' => 'user', 'label' => t('Quiz Author')),
        'node' => array('type' => 'node', 'label' => t('Quiz')),
      ),
    ),
    'quiz_rules_quiz_taken' => array(
      'label' => t('User has taken a quiz'),
      'group' => t('Quiz Rules'),
      'variables' => array(
        'user' => array('type' => 'user', 'label' => t('Quiz Taker')),
        'author' => array('type' => 'user', 'label' => t('Quiz Author')),
        'node' => array('type' => 'node', 'label' => t('Quiz')),
      ),
    ),
  );
}
