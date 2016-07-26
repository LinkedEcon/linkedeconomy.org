<?php

/**
 * @file
 * Abstraction of a CouchDB Design Documents
 * 
 * Copyright (c) 2010-2011 DOCOMO Innovations, Inc.
 * 
 */
class CouchDBDesign {
  
  private $design_document;
  private $couchdb;
  private $name;
  
  /**
   * Constructor
   * @param $design_document
   */
  function __construct($couchdb, $name, $design_document) {
    $this->couchdb = $couchdb;
    $this->name = $name;
    $this->design_document = $design_document;
  }
  
  /**
  * Compacts the view indexes associated with the specified design document.
  * @param $design
  *   Design document to compact
  */
  public function compactDesign() {
    return $this->couchdb->post($this->name . '/_compact' . '/' . $this->design_document, '', array('Content-type: application/json'));
  }
  
  /**
   * Returns the specified design document, design-doc from the specified db.
   * @param $name
   * @param $rev
   * @param $revs
   * @param $revs_info
   */
  public function getDesignDocument($rev = NULL, $revs = FALSE, $revs_info = FALSE) {
    $query = array();
    if ($rev) {
      $query[] = 'rev=' . urlencode($rev);
    }
    if ($revs) {
      $query[] = 'revs=true';
    }
    if ($revs_info) {
      $query[] = 'revs_info=true';
    }
    return $this->couchdb->get($this->name . '/_design/' . $this->design_document . (count($query) ? '?' . implode('&', $query) : ''));
  }
  
  
  /**
   * Delete an existing design document. Deleting a design
   * document also deletes all of the associated view indexes,
   * and recovers the corresponding space on disk for the indexes in question.
   * @param $name
   * @param $rev
   */
  public function deleteDesignDocument($rev) {
    return $this->couchdb->delete($this->name . '/_design/' . $this->design_document . '?rev=' . urlencode($rev));
  }
  
  /**
   * The COPY command (non-standard HTTP) copies an existing design document to a new or existing document.
   */
  public function copyDesignDocument($source, $destination, $source_rev_id = NULL, $target_rev_id = NULL) {
    return $this->couchdb->copy($this->name . '/_design/' . $source . (($source_rev_id) ? '?rev=' . urlencode($source_rev_id) : ''), array('Content-type: application/json', 'Destination: ' . $this->name . '/_design/' . $destination . (($target_rev_id) ? 'rev=' . urlencode($target_rev_id) : '')));
  }
  
  /**
   * Returns the file attachment attachment associated with the design document /_design_/design-doc.
   * @param $design_document
   * @param $attachment
   */
  public function getDesignAttachment($attachment) {
    return $this->couchdb->get($this->name . '/_design/' . $this->design_document . '/' . urlencode($attachment));
  }
  
  /**
  * Upload the supplied content as an attachment to the specified design document
  * @param $design_document
  * @param $att_name
  * @param $att_data
  * @param $content_type
  * @param $rev
  */
  public function storeDesignAttachment($att_name, $att_data, $content_type, $rev) {
    $headers = array(
      'Content-Type: ' . $content_type,
    );
    return $this->couchdb->put($this->name . '/_design/' . $this->design_document . '/' . urlencode($att_name) . '?rev=' . $rev, $att_data, $headers);
  }
  
  /**
     * Deletes the attachment attachment to the specified _design/design-doc.
  */
  public function deleteDesignAttachment($att_name, $rev) {
    return $this->couchdb->delete($this->name . '/_design/' . $this->design_document . '/' . urlencode($att_name) . '?rev=' . $rev);
  }
  
  public function getInfo() {
    return $this->couchdb->get($this->name . '/_design/' . $this->design_document . '/_info');
  }
  
  /**
   * Executes the specified view-name from the specified design-doc design document.
   * @param $view_name
   * @param $keys
   * @param $descending
   * @param $startkey
   * @param $endkey
   * @param $limit
   * @param $additional_args
   */
  public function getView($view_name, $keys = array(), $descending = FALSE, $startkey = '', $endkey = '', $limit = '', $additional_args = array()) {
    $query = array();
    if ($descending) {
      $query[] = 'descending=true';
    }
    if (!empty($startkey)) {
      $query[] = 'startkey="' . urlencode($startkey) . '"';
    }
    if (!empty($endkey)) {
      $query[] = 'endkey="' . urlencode($endkey) . '"';
    }
    if (!empty($limit)) {
      $query[] = 'limit=' . $limit;
    }
    
    if (count($additional_args)) {
      $query = array_merge($query, $additional_args);
    }
    
    // The presence of $keys means this is a post
    if (count($keys)) {
      $key_array = array(
        'keys' => $keys,
      );
      return $this->couchdb->post($this->name . '/_design/' . $this->design_document . '/_view/' . $view_name . (count($query) ? "?" . implode('&', $query) : ''), json_encode($key_array), array('Content-type: application/json'));
    }
    else {
      return $this->couchdb->get($this->name . '/_design/' . $this->design_document . '/_view/' . $view_name . (count($query) ? "?" . implode('&', $query) : ''));
    }
  }

}