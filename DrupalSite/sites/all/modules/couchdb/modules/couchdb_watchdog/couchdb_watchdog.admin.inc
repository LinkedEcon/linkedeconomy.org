<?php

/**
 * @file
 * Administrative pages
 * 
 * Copyright (c) 2010-2011 DOCOMO Innovations, Inc.
 * 
 */

/**
 * Build the listing page for watchdog messages
 */
function couchdb_watchdog_list() {
  $couch = new CouchDB();
  $database = $couch->getDatabase(COUCHDB_WATCHDOG_DB);

  $icons = array(
    WATCHDOG_DEBUG    => '',
    WATCHDOG_INFO     => '',
    WATCHDOG_NOTICE   => '',
    WATCHDOG_WARNING  => theme('image', array('path' => 'misc/watchdog-warning.png', 'alt' => t('warning'), 'title' => t('warning'))),
    WATCHDOG_ERROR    => theme('image', array('path' => 'misc/watchdog-error.png', 'alt' => t('error'), 'title' => t('error'))),
    WATCHDOG_CRITICAL => theme('image', array('path' => 'misc/watchdog-error.png', 'alt' => t('critical'), 'title' => t('critical'))),
    WATCHDOG_ALERT    => theme('image', array('path' => 'misc/watchdog-error.png', 'alt' => t('alert'), 'title' => t('alert'))),
    WATCHDOG_EMERGENCY    => theme('image', array('path' => 'misc/watchdog-error.png', 'alt' => t('emergency'), 'title' => t('emergency'))),
  );
  $classes = array(
    WATCHDOG_DEBUG     => 'dblog-debug',
    WATCHDOG_INFO      => 'dblog-info',
    WATCHDOG_NOTICE    => 'dblog-notice',
    WATCHDOG_WARNING   => 'dblog-warning',
    WATCHDOG_ERROR     => 'dblog-error',
    WATCHDOG_CRITICAL  => 'dblog-critical',
    WATCHDOG_ALERT     => 'dblog-alert',
    WATCHDOG_EMERGENCY => 'dblog-emerg',
  );
  
  // initialize the pager stuff
  global $pager_page_array, $pager_total, $pager_total_items, $pager_limits;
  $page = isset($_GET['page']) ? $_GET['page'] : '';
  $pager_page_array = explode(',', $page);
  $on_page = $pager_page_array[0];
  $skip = $on_page * COUCHDB_WATCHDOG_PER_PAGE;
  // get the documents from couch
  $docs = couchdb_watchdog_get_docs($database, $skip);
  
  $rows = array();
  if (isset($docs->rows)) {
    foreach ($docs->rows as $doc) {
      $message = truncate_utf8(strip_tags(t($doc->value->message, (array)$doc->value->variables)), 100, TRUE, TRUE);
      $rows[] = array('data' =>
        array(
          $icons[$doc->value->severity], // Icon
          $doc->value->type,
          empty($doc->value->timestamp) ? '' : format_date($doc->value->timestamp, 'short'),
          l($message, 'admin/reports/couchdb-watchdog/' . $doc->id),
          theme('username', array('account' => $doc->value->user)),
        ),
        'class' => array(drupal_html_class('dblog-' . $doc->value->type), $classes[$doc->value->severity]),
      );    
    }
  }
  
  $build['couchdb_watchdog_filter_form'] = drupal_get_form('couchdb_watchdog_filter_form');
  $build['couchdb_watchdog_log_form'] = drupal_get_form('couchdb_watchdog_clear_log_form');
  $build['couchdb_watchdog_table'] = array(
    '#theme' => 'table',
    '#header' => couchdb_watchdog_header(),
    '#rows' => $rows,
    '#empty' => t('No log messages available.'),
  );
  
  // Add the pager.
  if ($on_page > 0 || count($rows) >= COUCHDB_WATCHDOG_PER_PAGE) {
    $pager_total_items[0] = $docs->count;
    $pager_total[0] = ceil($pager_total_items[0] / COUCHDB_WATCHDOG_PER_PAGE);
    $pager_page_array[0] = max(0, min((int) $pager_page_array[0], ((int)$pager_total[0]) - 1));
    $pager_limits[0] = COUCHDB_WATCHDOG_PER_PAGE;
    $build['pager'] = array(
      '#theme' => 'pager',
    );
  }
  return $build;
}


/**
 * Watchdog entry detail page
 */
function couchdb_watchdog_detail($id) {
  $severity = watchdog_severity_levels();
  
  $couch = new CouchDB();
  $database = $couch->getDatabase(COUCHDB_WATCHDOG_DB);  
  $watchdog_details = $database->getDocument($id);
  if (isset($watchdog_details->_id)) {
    // theme out the table
    $rows = array(
      array(
        array('data' => t('Type'), 'header' => TRUE),
        t($watchdog_details->type),
      ),
      array(
        array('data' => t('Date'), 'header' => TRUE),
        format_date($watchdog_details->timestamp, 'long'),
      ),
      array(
        array('data' => t('User'), 'header' => TRUE),
        theme('username', array('account' => $watchdog_details->user)),
      ),
      array(
        array('data' => t('Referrer'), 'header' => TRUE),
        l($watchdog_details->referer, $watchdog_details->referer),
      ),
      array(
        array('data' => t('Message'), 'header' => TRUE),
        t($watchdog_details->message, (array)$watchdog_details->variables),
      ),
      array(
        array('data' => t('Severity'), 'header' => TRUE),
        $severity[$watchdog_details->severity],
      ),
      array(
        array('data' => t('Hostname'), 'header' => TRUE),
        check_plain($watchdog_details->ip),
      ),
      array(
        array('data' => t('Operations'), 'header' => TRUE),
        $watchdog_details->link,
      ),
    );
    $build['dblog_table'] = array(
      '#theme' => 'table',
      '#rows' => $rows,
      '#attributes' => array('class' => array('dblog-event')),
    );
    return $build;
  }
  else {
    return '';
  }
}

/**
 * Helper function determines the available filters 
 * the overview page can filter by
 */
function couchdb_filters() {
  $filters = array();
  $types = _couchdb_watchdog_get_message_types();
  if (count($types)) {
    $filters['type'] = array(
      'title' => t('Type'),
      'options' => $types,
    );
  }
  $filters['severity'] = array(
    'title' => t('Severity'),
    'options' => watchdog_severity_levels(),
  );
  return $filters;
}


/**
 * Watchdog filter form
 */
function couchdb_watchdog_filter_form($form) {
  $filters = couchdb_filters();
  
  $form['filters'] = array(
    '#type' => 'fieldset',
    '#title' => t('Filter log messages'),
    '#collapsible' => TRUE,
    '#collapsed' => empty($_SESSION['couchdb_watchdog_filter']),
  );
  foreach ($filters as $key => $filter) {
    $form['filters']['status'][$key] = array(
      '#title' => check_plain($filter['title']),
      '#type' => 'select',
      '#multiple' => TRUE,
      '#size' => 8,
      '#options' => $filter['options'],
    );
    if (!empty($_SESSION['couchdb_watchdog_filter'][$key])) {
      $form['filters']['status'][$key]['#default_value'] = $_SESSION['couchdb_watchdog_filter'][$key];
    }
  }  
  $form['filters']['buttons']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Filter'),
  );
  if (!empty($_SESSION['couchdb_watchdog_filter'])) {
    $form['filters']['buttons']['reset'] = array(
        '#type' => 'submit',
        '#value' => t('Reset')
    );
  }
  return $form;
}

/**
 * Filter validation
 */
function couchdb_watchdog_filter_form_validate($form, &$form_state) {
  if ($form_state['values']['op'] == t('Filter') && empty($form_state['values']['type']) && empty($form_state['values']['severity'])) {
    form_set_error('type', t('You must select something to filter by.'));
  }
}

/**
 * Filter submit
 */
function couchdb_watchdog_filter_form_submit($form, &$form_state) {
  $op = $form_state['values']['op'];
  $filters = couchdb_filters();
  switch ($op) {
    case t('Filter'):
      foreach ($filters as $name => $filter) {
        if (isset($form_state['values'][$name])) {
          $_SESSION['couchdb_watchdog_filter'][$name] = $form_state['values'][$name];
        }
      }
      break;
    case t('Reset'):
      $_SESSION['couchdb_watchdog_filter'] = array();
      break;
  }
  return 'admin/reports/couchdb-watchdog';
}

/**
 * Clear the watchdog documents from couch
 */
function couchdb_watchdog_clear_log_form($form) {
  $form['couchdb_watchdog_clear'] = array(
    '#type' => 'fieldset',
    '#title' => t('Clear log messages'),
    '#description' => t('This will permanently remove the log messages from the CouchDB.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['couchdb_watchdog_clear']['clear'] = array(
    '#type' => 'submit',
    '#value' => t('Clear log messages'),
    '#submit' => array('couchdb_watchdog_clear_log_form_submit'),
  );
  
  return $form;
}

/**
 * Clear the watchdog database 
 */
function couchdb_watchdog_clear_log_form_submit($form, &$form_values) {
  $_SESSION['couchdb_watchdog_filter'] = array();
  // Delete the database
  $couch = new CouchDB();
  $couch->deleteDatabase(COUCHDB_WATCHDOG_DB);
  
  // Recreate it, along with the views
  module_load_include('install', 'couchdb_watchdog');
  couchdb_watchdog_create_database();
}

/**
 * Get the documents via a couchdb view.
 * @todo: The current filter+sort when using the filter form
 * is sorted in code.  There might be a better way to do that.
 */
function couchdb_watchdog_get_docs($database, $skip) {
  $view = _couchdb_watchdog_init_order();
  $descending = _couchdb_watchdog_init_sort();
  $docs = new stdClass();
  
  // couchdb views filtering required. The sorting
  // is then done in code
  if (!empty($_SESSION['couchdb_watchdog_filter'])) {
    $types = $_SESSION['couchdb_watchdog_filter']['type'] ? $_SESSION['couchdb_watchdog_filter']['type'] : NULL;
    $severities = $_SESSION['couchdb_watchdog_filter']['severity'] ? $_SESSION['couchdb_watchdog_filter']['severity'] : NULL;
    $keys = array();
    if ($types != NULL && $severities != NULL) {
      $view = 'list_by_type_severity';
      // build each possible key combination based
      // on the user selection
      foreach ($types as $type) {
        foreach ($severities as $severity) {
          $keys[] = array($type, (int) $severity);
        }
      }
    }
    elseif ($types != NULL) {
      $view = 'list_by_type';
      $keys = array_values($types);
    }
    elseif ($severities != NULL) {
      $view = 'list_by_severity';
      // iterate and cast the severity into an integer
      foreach ($severities as $severity) {
        $keys[] = (int) $severity;
      }
    }
    
    $all_docs = $database->getDesign('drupal_watchdog_view')->getView($view, $keys, $descending, '', '', '', array('reduce=false'));
    if (isset($all_docs->rows)) {
      // sort the documents
      usort($all_docs->rows, '_couchdb_watchdog_sort');
      // get a paginated list
      global $pager_page_array;
      $page = isset($_GET['page']) ? $_GET['page'] : '';
      $pager_page_array = explode(',', $page);
      $on_page = $pager_page_array[0];
      $skip = $on_page * COUCHDB_WATCHDOG_PER_PAGE;
      // only grab the rows for each paginated page
      $docs->rows = array_slice($all_docs->rows, $skip, COUCHDB_WATCHDOG_PER_PAGE);
      $docs->count = count($all_docs->rows);
    }
  }
  else {
    // no complex filtering needed, so just execute the view and let couch handle everything
    $docs = $database->getDesign('drupal_watchdog_view')->getView($view, array(), $descending, '', '', COUCHDB_WATCHDOG_PER_PAGE, array("skip={$skip}", "reduce=false"));
    $docs->count = 0;
    $count = $database->getDesign('drupal_watchdog_view')->getView($view, array(), $descending, '', '', '', array("group=true"));
    foreach ($count->rows as $row) {
      $docs->count = $docs->count + $row->value;
    }
  }
  return $docs;
}

/**
 * Sort the couchdb docs that were filtered 
 */
function _couchdb_watchdog_sort($a, $b) {
  $cache = &drupal_static(__FUNCTION__);

  if (!isset($cache['field'])) {
    $cache['field'] = _couchdb_watchdog_init_order();
  }
  if (!isset($cache['descending'])) {
    $cache['descending'] = _couchdb_watchdog_init_sort();    
  }

  $a_field = ''; 
  $b_field = '';
  switch ($cache['field']) {
    case 'list_by_date':
      $a_field = $a->value->timestamp;
      $b_field = $b->value->timestamp;
      break;
    case 'list_by_type':
      $a_field = $a->value->type;
      $b_field = $b->value->type;
      break;
    case 'list_by_user':
      $a_field = $a->value->user->name;
      $b_field = $b->value->user->name;
      break;
  }

  if ($a_field == $b_field) {
    return 0;
  }
  if ($cache['descending']) {
    return ($a_field > $b_field) ? -1 : 1;
  }
  else {
    return ($a_field < $b_field) ? -1 : 1;
  }

}

/**
 * Get the available message types stored in couch
 */
function _couchdb_watchdog_get_message_types() {
  $types = array();
  $couch = new CouchDB();
  $database = $couch->getDatabase(COUCHDB_WATCHDOG_DB);
  $results = $database->getDesign('drupal_watchdog_view')->getView('distinct_types', array(), FALSE, '', '', '', array("group=true"));
  foreach ($results->rows as $result) {
    if (isset($result->key)) {
      $types[$result->key] = $result->key;
    }
  }
  return $types;
}

/**
 * Helper function that determines which
 * couch view to query by
 */
function _couchdb_watchdog_init_order() {
  $header = couchdb_watchdog_header();
  $order = tablesort_get_order($header);
  // set the default list
  $view = "list_by_date";
  if (isset($order['sql'])) {
    $view = $order['sql'];
  }
  return $view;
}

/**
 * Helper function that determines which
 * sort order
 */
function _couchdb_watchdog_init_sort() {
  $header = couchdb_watchdog_header();
  $sort = tablesort_get_sort($header);
  $descending = TRUE;
  $sort = tablesort_get_sort($header);
  if (isset($sort)) {
    if ($sort == 'asc') {
      $descending = FALSE;
    }
  }
  return $descending;
}

/**
 * Function build the table header
 */
function couchdb_watchdog_header() {
  $header = &drupal_static(__FUNCTION__);
  if (count($header) == 0) {
    $header = array(
      '', 
      array('data' => t('Type'), 'field' => 'list_by_type'),
      array('data' => t('Date'), 'field' => 'list_by_date', 'sort' => 'desc'),
      t('Message'),
      array('data' => t('User'), 'field' => 'list_by_user'),
    );
  }
  return $header;
}
