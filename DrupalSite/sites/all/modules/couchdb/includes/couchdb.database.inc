<?php

/**
 * @file
 * An abstraction of a CouchDB Database.
 * 
 * Copyright (c) 2010-2011 DOCOMO Innovations, Inc.
 * 
 */
class CouchDBDatabase {
  
  private $info;
  private $name;

  function __construct($couchdb, $database_name) {
    // Fetch information about this database, bailout if the database doesn't exist.
    $this->info = $couchdb->databaseInfo($database_name);
    if (empty($this->info) || isset($this->info->error)) {
      throw new CouchDBException("Unable to fetch information about the database.");
    }

    // Store the couchdb object.
    $this->couchdb = $couchdb;

    // Store the database name.
    $this->name = urlencode($database_name);
  }

  /**
   * Return a design document class, loaded with
   * design_document name
   * @param $design_document
   * @return CouchDBDesign
   */
  function getDesign($design_document) {
    return new CouchDBDesign($this->couchdb, $this->name, $design_document);
  }
  
  /**
   * Upload the specified design document, design-doc, to the specified database.
   *
   * @param unknown_type $name
   * @param unknown_type $document
   */
  public function storeDesignDocument($document_name, $document) {
    return $this->couchdb->put($this->name . '/_design/' . $document_name, json_encode($document));
  }
  
  /**
   * Fetch a document.
   * @param $doc_id
   *   Document id
   * @param $rev
   *   Optional parameter. Specify $rev to return a specific revision
   */
  function getDocument($doc_id, $rev = NULL) {
    return $this->couchdb->get($this->name . '/' . urlencode($doc_id) . ($rev ? '?rev=' . urlencode($rev) : ''));
  }

  /**
   * Fetch the revision IDs associated to a document.
   * @param $doc_id
   *   Document id
   */
  function getDocumentRevisions($doc_id) {
    return $this->couchdb->get($this->name . '/' . urlencode($doc_id) . '?revs_info=true')->_revs_info;
  }

  /**
   * Store a document.
   * @param $doc_id
   *   Document id
   * @param $document
   *   Full Document Object
   * @param $batch
   *   True will result in an immediate HTTP 200 return.  The document will be processed later.
   */
  function storeDocument($doc_id, $document, $batch = FALSE) {
    return $this->couchdb->put($this->name . '/' . urlencode($doc_id) . (($batch) ? '?batch=ok' : ''), json_encode($document));
  }

  /**
   * Bulk document storage
   * @param array $documents
   *   An array of documents to be stored
   * @param $all_or_nothing
   *   Specify TRUE to preserve transactions.  This means if one document
   *   fails, all the documents will fail.
   */
  function storeDocuments(array $documents = array(), $all_or_nothing = FALSE) {
    $docs = array('docs' => $documents);
    // support transactional updates. If true, if one fails
    // all updates will fail
    if ($all_or_nothing) {
      $docs['all_or_nothing'] = TRUE;
    }
    return $this->couchdb->post($this->name . '/' . '_bulk_docs', json_encode($docs), array('Content-type: application/json'));
  }


  /**
   * Copy a document from one location to another.
   * Enter description here ...
   * @param $source
   *   Source document
   * @param $destination
   *   Destination Document
   * @param $rev_id
   *   The destination revision to copy into
   */
  public function copyDocument($source, $destination, $rev_id = 0) {
    return $this->couchdb->copy($this->name . '/' . $source, array('Content-type: application/json', 'Destination: ' . $destination . (($rev_id > 0) ? 'rev=' . $rev_id : '')));
  }

  /**
   * Delete a document.
   * @param $doc_id
   *   Document id
   * @param $rev
   *   Revision
   */
  function deleteDocument($doc_id, $rev) {
    return $this->couchdb->delete($this->name . '/' . urlencode($doc_id) . '?rev=' . urlencode($rev));
  }

  /**
   * Obtains a list of the changes made to the database.
   * @param $since
   *   Start the results from the specified sequence number
   * @param $limit
   *   Maximum number of rows rows to return
   * @param $timeout
   *   Maximum period to wait before the response is sent
   * @param $filter
   *   Filter function from a design document to get updates
   * @param $include_docs
   *   Include the document with the result
   */
  function getChanges($since = 0, $limit = 0, $timeout = 60000, $filter = '', $include_docs = 'false') {
    $query = 'since=' . $since . '&feed=normal' . '&timeout=' . $timeout . '&filter=' . $filter . '&include_docs' . $include_docs;
    if ($limit) {
      $query .= '&limit=' . $limit;
    }
    return $this->couchdb->get($this->name . '/_changes' . '?' . $query);
  }

  /**
   * Request compaction of the specified database
   */
  public function compactDatabase() {
    return $this->couchdb->post($this->name . '/_compact', '', array('Content-type: application/json'));
  }

  /**
   * Cleans up the cached view output on disk for a given view
   */
  public function viewCleanup() {
    return $this->couchdb->post($this->name . '/_view_cleanup', '', array('Content-type: application/json'));
  }

  /**
   * Commits any recent changes to the specified database to disk.
   */
  public function ensureFullCommit() {
    return $this->couchdb->post($this->name . '/_ensure_full_commit', '', array('Content-type: application/json'));
  }

  /**
   * A database purge permanently removes the references to deleted documents from the database.
   * @param $documents
   *   An associative array of Document_id and revisions like such
   *   <code>
   *   	array(
   *      'doc_id' => array(
   *      	'rev_id1', 'rev_id2',
   *      )
   *    );
   *   </code>
   */
  public function purge($documents) {
    return $this->couchdb->post($this->name . '/_purge', json_encode($documents), array('Content-type: application/json'));
  }

  /**
   * Returns a JSON structure of all of the documents in a given database.
   * Enter description here ...
   * @param $keys
   * @param $descending
   * @param $startkey
   * @param $endkey
   * @param $limit
   * @param $additional_args
   *   Additional arguments are passed in an array.  Refer to couchdb api for the rest
   *   of the parameters
   *   example: ['reduce=true', 'skip=4', 'stale=ok']
   */
  public function getAllDocuments($keys = array(), $descending = FALSE, $startkey = '', $endkey = '', $limit = '', $additional_args = array()) {
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
    if (count($keys)) {
      // execute as post
      $key_array = array(
        'keys' => $keys,
      );
      return $this->couchdb->post($this->name . '/_all_docs', json_encode($key_array), array('Content-type: application/json'));
    }
    else {

      if (count($additional_args)) {
        $query = array_merge($query, $additional_args);
      }
      return $this->couchdb->get($this->name . '/_all_docs' . (count($query) ? "?" . implode('&', $query) : ''));
    }
  }

  /**
   * Execute a temporary view on a couchDB.
   * @param $view
   */
  public function executeTempView($view) {
    $map = array(
      'map' => $view,
    );
    return $this->couchdb->post($this->name . '/_temp_view', json_encode($map), array('Content-type: application/json'));
  }

  /**
   * Gets the current secrity object from the specified database.
   * The security object consists of two compulsory elements, admins
   * and readers, which are used to specify the list of users and/or
   * roles that have admin and reader rights to the database respectively.
   */
  public function getSecurity() {
    return $this->couchdb->get($this->name . '/_security');
  }

  /**
   * Sets the security object for the given database.
   * @param array $roles
   *   An array of admin and reader objects.
   *
   *  // @todo: Make this api function easier
   */
  public function storeSecurity(array $roles) {
    return $this->couchdb->put($this->name . '/_security', json_encode($roles));
  }

  /**
   * Gets the current revs_limit (revision limit) setting
   */
  public function getRevsLimit() {
    return $this->couchdb->get($this->name . '/_revs_limit');
  }

  /**
   * Sets the maximum number of document revisions that
   * will be tracked by CouchDB, even after compaction has occurred.
   */
  public function storeRevsLimit($limit) {
    return $this->couchdb->put($this->name . '/_revs_limit', $limit);
  }

  /**
   * Returns the file attachment attachment associated with the document doc.
   * @param $doc_id
   * @param $att_name
   */
  public function getAttachment($doc_id, $att_name) {
    return $this->couchdb->get($this->name . '/' . $doc_id . '/' . urlencode($att_name));
  }

  /**
   * Upload the supplied content as an attachment to the specified document (doc).
   * Uploading an attachment using an existing attachment name will update the
   * corresponding stored content of the database. Since you must supply the revision
   * information to add an attachment to a document, this serves as validation
   * to update the existing attachment.
   * @param $doc_id
   * @param $att_name
   * @param $att_data
   * @param $content_type
   * @param $rev
   */
  public function storeAttachment($doc_id, $att_name, $att_data, $content_type, $rev) {
    $headers = array(
      'Content-Type: ' . $content_type,
    );
    return $this->couchdb->put($this->name . '/' . $doc_id . '/' . urlencode($att_name) . '?rev=' . $rev, $att_data, $headers);
  }

  /**
   * Deletes the attachment attachment to the specified doc.
   * @param $doc_id
   * @param $att_name
   * @param $rev
   */
  public function deleteAttachment($doc_id, $att_name, $rev) {
    return $this->couchdb->delete($this->name . '/' . $doc_id . '/' . urlencode($att_name) . '?rev=' . $rev);
  }

  //Non-replicating Documents

  /**
   * Fetch a document.
   */
  function getLocalDocument($doc_id, $rev = NULL) {
    return $this->couchdb->get($this->name . '/_local/' . urlencode($doc_id) . ($rev ? '?rev=' . urlencode($rev) : ''));
  }

  /**
   * Store a document.
   */
  function storeLocalDocument($doc_id, $document, $batch = FALSE) {
    return $this->couchdb->put($this->name . '/_local/' . urlencode($doc_id), json_encode($document));
  }

  /**
   * Delete a document.
   */
  function deleteLocalDocument($doc_id, $rev) {
    return $this->couchdb->delete($this->name . '/_local/' . urlencode($doc_id) . '?rev=' . urlencode($rev));
  }

  /**
   * Copy a document from one location to another.
   * Enter description here ...
   * @param unknown_type $source
   * @param unknown_type $destination
   */
  public function copyLocalDocument($source, $destination, $rev_id = 0) {
    return $this->couchdb->copy($this->name . '/_local/' . $source, array('Content-type: application/json', 'Destination: ' . $destination . (($rev_id > 0) ? 'rev=' . $rev_id : '')));
  }

}
