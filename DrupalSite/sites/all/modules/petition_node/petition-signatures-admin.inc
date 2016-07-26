<?php

/**
 * @file
 * Administration of the "petition" node type.
 *
 * @author Samuel Gauvain <gauvain@kth.se>
 * @author Dan Smith <dan.smith@codeenigma.com>
 */


/**
 * Menu callback: petition_signatures_admin_page.
 */
function petition_signatures_admin_page($node) {
  $output = drupal_get_form('_petition_administer_signatures', $node);
  return $output;
}


/**
 * Menu callback: petition_signatures_edit_page.
 */
function petition_signatures_edit_page($signature) {
  $output = drupal_get_form('_petition_edit_signatures', $signature);
  return $output;
}



function _petition_administer_signatures($form, $form_state, $node) {
  if (isset($form_state['values']['operation']) && $form_state['values']['operation'] ==  'delete') {
    return _signatures_multiple_delete_confirm($form_state, array_filter($form_state['values']['signatures']));
  }
  $form['admin'] = petition_admin_signatures($node);

  return $form;
}


/**
 * Validate petition_admin_signatures form submissions.
 *
 * Check if any nodes have been selected to perform the chosen
 * 'Update option' on.
 */
function _petition_administer_signatures_validate($form, &$form_state) {
  $signatures = array_filter($form_state['values']['signatures']);
  if (count($signatures) ==  0) {
    form_set_error('', t('No items selected.'));
  }
}

/**
 * Process petition_admin_signatures form submissions.
 *
 * Rebuild the form for the confirmation step
 */
function _petition_admin_signatures_submit($form, &$form_state) {

  $signatures = array_filter($form_state['values']['signatures']);
  $form_state['rebuild'] = TRUE;
}

function _signatures_multiple_delete_confirm(&$form_state, $signatures) {

  $form['signatures'] = array(
    '#prefix' => '<ul>',
    '#suffix' => '</ul>',
    '#tree' => TRUE,
  );
  // array_filter returns only elements with TRUE values
  foreach ($signatures as $cid => $value) {
    $result = db_query('SELECT * FROM {petition_signatures} WHERE cid = :cid', array(':cid' => $cid));
    $result = db_select('petition_signatures', 'ps')
      ->fields('ps')
      ->condition('ps.cid', $cid)
      ->execute();
    $signature = $result->fetchObject();

    $signature_string = check_plain($signature->name . ', ' . $signature->firstname);
    if (!empty($signature->town) || !empty($signature->zip)) {
      $signature_string .= ' from ';
      if (!empty($signature->town)) {
        $signature_string .= check_plain($signature->town);
        if (!empty($signature->zip)) {
          $signature_string .= ', ' . check_plain($signature->zip);
        }
      }
      else {
        $signature_string .= check_plain($signature->zip);
      }
    }
    $signature_string .= "</li>\n";

    $form['signatures'][$cid] = array(
      '#type' => 'hidden',
      '#value' => $cid,
      '#prefix' => '<li>',
      '#suffix' => $signature_string,
    );
  }
  $form['operation'] = array(
    '#type' => 'hidden',
    '#value' => 'delete',
  );
  $form['#submit'][] = '_signatures_multiple_delete_confirm_submit';
  return confirm_form($form,
                      t('Are you sure you want to delete these signatures?'),
                      check_plain($_GET['q']), t('This action cannot be undone.'),
                      t('Delete all'), t('Cancel'));
}

function _signatures_multiple_delete_confirm_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {
    foreach ($form_state['values']['signatures'] as $cid => $value) {
      $nid = db_select('petition_signatures', 'ps')
        ->fields('ps', array('nid'))
        ->condition('ps.cid', $cid)
        ->execute()
        ->fetchField();

      db_delete('petition_signatures')
        ->condition('cid', $cid)
        ->execute();
    }
    _update_sigature_position($nid);
    drupal_set_message(t('The items have been deleted.'));
  }
  $form_state['redirect'] = check_plain($_GET['q']);
  return;
}

function _petition_edit_signatures($form, $form_state, $signature) {
  // validate parameter
  $result = db_query('SELECT * FROM {petition_signatures} WHERE cid = :cid', array(':cid' => $signature));
  $entry = db_fetch_object($result);
  if ($node = node_load($entry->nid)) {
    $form = petition_signature_form($node);
    unset($form['#submit']);
    unset($form['#validate']);
    $form['signature']['#title'] = t('Edit the signature');
    unset($form['signature']['remote_address']);
    unset($form['signature']['date']);
    $form['signature_details']['cid'] = array(
      '#type' => 'hidden',
      '#value' => $signature,
    );
    $form['signature']['submitbutton']['#value'] = t('Submit');

    $fields = array('name', 'firstname', 'title', 'profession', 'institution', 'website', 'address', 'zip', 'town', 'country', 'tel', 'email', 'comment', 'canbe_informed');
    foreach ($fields as $field) {
      if (isset($form['signature'][$field]['#type'])) {
        $form['signature'][$field]['#default_value'] = $entry->$field;
      }
      elseif (isset($form['signature']['comment_filter'][$field]['#type'])) {
        $form['signature']['comment_filter'][$field]['#default_value'] = $entry->$field;
      }
    }

    // disable email editing
    $form['signature']['email']['#disabled'] = TRUE;
    $form['signature']['email']['#required'] = FALSE;

    // add initial signer
    $form['signature']['initial_signer'] = array(
      '#type' => 'checkbox',
      '#title' => t('Initial signer'),
      '#default_value' => $entry->initial_signer,
      '#weight' => 20,
    );

  }
  else {
    return drupal_access_denied();
  }
  return ($form);
}

function _petition_edit_signatures_submit($form, &$form_state) {
  $signature->nid = $form_state['values']['nid'];
  $signature->cid = $form_state['values']['cid'];
  $signature->name = $form_state['values']['name'];
  $signature->firstname = $form_state['values']['firstname'];
  $signature->title = $form_state['values']['title'];
  $signature->address = $form_state['values']['address'];
  $signature->zip = $form_state['values']['zip'];
  $signature->town = $form_state['values']['town'];
  $signature->country = $form_state['values']['country'];
  $signature->tel = $form_state['values']['tel'];
  $signature->canbe_informed = $form_state['values']['canbe_informed'];
  $signature->profession = $form_state['values']['profession'];
  $signature->institution = $form_state['values']['institution'];
  $signature->website = $form_state['values']['website'];
  $signature->comment = $form_state['values']['comment'];
  $signature->initial_signer = $form_state['values']['initial_signer'];
  $signature->language = $form_state['values']['language'];

  // IF the form was submitted from a translation, retrieve the nid of the translated version to send the email in the correct languge
  if (empty($signature->language)) {
    $nid = $signature->nid;
  }
  else {
    $nid = db_query("SELECT nid FROM {petition_translation} WHERE tnid = :tnid AND language = :language", array(':tnid' => $signature->nid, ':language' => $signature->language))->fetchField();
  }
  // Load the petition node
  $node = node_load($nid);

  $signature->comment = check_markup($signature->comment, $node->format);

  db_update('petition_signatures')
  ->fields(array(
    'name' => $signature->name,
    'firstname' => $signature->firstname,
    'title' => $signature->title,
    'address' => $signature->address,
    'zip' => $signature->zip,
    'town' => $signature->town,
    'country' => $signature->country,
    'tel' => $signature->tel,
    'profession' => $signature->profession,
    'institution' => $signature->institution,
    'website' => $signature->website,
    'comment' => $signature->comment,
    'canbe_informed' => $signature->canbe_informed,
    'initial_signer' => $signature->initial_signer,
  ))
  ->condition('cid', $signature->cid)
  ->execute();

  // show a message to the admin
  drupal_set_message(t("The signature has been updated"));

  // redirect to the admin page
  $form_state['redirect'] = 'node/' . $signature->nid . '/signatures-admin';
}


/*
 * petition_admin_signatures form.
 */
function petition_admin_signatures($node) {

  // submit button with 'delete' value
  $form['options'] = array(
    '#type' => 'fieldset',
    '#title' => t('Delete Signatures'),
    '#prefix' => '<div class = "container-inline">',
    '#suffix' => '</div>',
  );

  $form['options']['operation'] = array(
    '#type' => 'value',
    '#default_value' => 'delete',
  );
  $form['options']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Delete Selected Signatures'),
    '#submit' => array('_petition_admin_signatures_submit'),
  );

  $destination = drupal_get_destination();

  // Pager information.
  $max = variable_get('petition_signature_number', 50);

  $result = db_select('node', 'n')
    ->fields('n')
    ->condition('status', 0)
    ->condition(db_or()->condition('n.tnid', 'n.nid')->condition('n.tnid', 0))
    ->orderBy('created', 'ASC')
    ->addTag('node_access')
    ->execute();

  $fields = variable_get('petition_report_fields_fields', array('position', 'name', 'firstname', 'title', 'zip', 'town', 'country'));
  $field_array = array(
    'position' => t('Signature position'),
    'name' => t('Surname'),
    'firstname' => t('First name'),
    'title' => t('Self-description'),
    'address' => t('Address'),
    'zip' => t('ZIP code'),
    'town' => t('Town'),
    'country' => t('Country'),
    'tel' => t('Phone number'),
    'email' => t('Email'),
    'profession' => t('Profession'),
    'institution' => t('Institution'),
    'website' => t('Website'),
    'comment' => t('Comment'),
  );

  $header = array();
  $i = 0;
  foreach ($fields as $field) {
    if (!empty($field)) {
      $header[$field] = $i < 1 ? array(
        'data' => $field_array[$field],
        'field' => $field,
        'sort' => 'asc',
      ) : array(
        'data' => $field_array[$field],
        'field' => $field,
      );
      $i++;
    }
  }

  $result = db_select('petition_signatures', 'ps')
    ->fields('ps')
    ->condition('ps.nid', $node->nid)
    ->condition('ps.confirmed', 1)
    ->extend('TableSort')
    ->orderByHeader($header)
    ->extend('PagerDefault')
    ->limit($max)
    ->execute();

  $signatures = array();

  while ($signature = $result->fetchObject()) {
    $signatures[$signature->cid] = '';
    foreach ($fields as $field) {
      if (!empty($field)) {
        $form[$field][$signature->cid] = array('#markup' => check_plain($signature->$field));
      }
    }
  }
  $form['signatures'] = array(
    '#type' => 'checkboxes',
    '#options' => $signatures,
  );
  $form['pager'] = array('#value' => theme('pager', array('tags' => NULL, 'element' => 0)));
  $form['#theme'] = 'petition_admin_signatures';
  return $form;

}

/**
 * Theme signature administration overview.
 * @ingroup themeable
 */
function theme_petition_admin_signatures($variables) {
  $form = $variables['form'];
  $fields = variable_get('petition_report_fields_fields', array('position', 'name', 'firstname', 'title', 'zip', 'town', 'country'));
  $field_array = array(
    'position' => t('Signature position'),
    'name' => t('Surname'),
    'firstname' => t('First name'),
    'title' => t('Title'),
    'address' => t('Address'),
    'zip' => t('ZIP code'),
    'town' => t('Town'),
    'country' => t('Country'),
    'tel' => t('Phone number'),
    'email' => t('Email'),
    'profession' => t('Profession'),
    'institution' => t('Institution'),
    'website' => t('Website'),
    'comment' => t('Comment'),
  );

  $header = array('box' => '');
  $has_posts = FALSE;
  $i = 0;
  foreach ($fields as $field) {
    if (!empty($field)) {
      $header[$field] = $i < 1 ? array(
        'data' => $field_array[$field],
        'field' => $field,
        'sort' => 'asc',
      ) : array(
        'data' => $field_array[$field],
        'field' => $field,
      );
      if (isset($form[$field]) && is_array($form[$field])) {
        $has_posts = TRUE;
      }
      if (isset($form[$field]) && is_array($form[$field]) && $i < 1) {
        $firstcol = $field;
      }
      $i++;
    }
  }
  $header['edit'] = t('Edit');

  $output = '';

  $output .=  drupal_render($form['options']);
  $i = 0;
  if ($has_posts) {
    foreach (element_children($form[$firstcol]) as $key) {
      $row = array();
      foreach ($header as $col => $col_title) {
        if ($col == 'box' ) {
          $row[] = drupal_render($form['signatures'][$key]);
        }
        elseif ($col == 'edit') {
          $row[] = l(t('Edit'), "signature/edit/$key");
        }
        else {
          $row[] = drupal_render($form[$col][$key]);
        }
      }

      $rows[$i]['data'] = $row;
      $i++;
    }
  }
  else {
    $rows[] = array(array(
        'data' => t('No signatures available.'),
        'colspan' => '6',
      ));
  }

  $output .=  theme('table', array('header' => $header, 'rows' => $rows));

  $output .=  drupal_render_children($form);
  $output .= drupal_render($form['pager']);

  return $output;
}

/**
 * Helper function to update the signatures posiion after deletion of a signature.
 * @param
 * nid of the node
 */
function _update_sigature_position($nid) {
  $signatures = db_select('petition_signatures', 'ps')
    ->fields('ps')
    ->condition('ps.nid', $nid)
    ->condition('ps.confirmed', 1)
    ->orderBy('ps.cid', 'ASC')
    ->execute();

  $position = 0;

  while ($signature = $signatures->fetchObject()) {
    $position += 1;

    db_update('petition_signatures')
      ->fields(array('position' => $position))
      ->condition('nid', $signature->nid)
      ->condition('cid', $signature->cid)
      ->execute();
  }

  $signature_count = db_select('petition_signatures', 'ps')
    ->fields('ps', array('cid'))
    ->condition('ps.nid', $nid)
    ->condition('ps.confirmed', 1)
    ->countQuery()
    ->execute()
    ->fetchField();

  $signature_count = is_numeric($signature_count) ? $signature_count : 0;

  db_update('petition')
    ->fields(array('signatures' => $signature_count))
    ->condition('nid', $nid)
    ->execute();
}
