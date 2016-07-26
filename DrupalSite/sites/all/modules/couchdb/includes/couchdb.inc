<?php

/**
 * @file
 * A highly optimized CouchDB wrapping class.
 * 
 * Copyright (c) 2010-2011 DOCOMO Innovations, Inc.
 * 
 */

/**
 * A CouchDB wrapping class.
 */
class CouchDB {

  /**
   * The base URL of the CouchDB server.
   */
  public $baseURL;

  /**
   * Additional cURL options to use.
   *
   * @var array
   */
  public $additionalCurlOptions = array();

  /**
   * The cURL handle.
   */
  protected $curlHandle = NULL;

  /**
   * The HTTP credential to use, or NULL if none are required.
   */
  public $httpAuthCredentials = NULL;

  /**
   * Constructor.
   */
  public function __construct() {
    // load the $baseURL and httpAuthCredentials from settings.php
    $couch_vars = variable_get('couchdb', FALSE);
    // throw an exception if the variables are not set
    if (!$couch_vars) {
      throw new CouchDBException('No CouchDB configurations in settings.php');
    }
    if (!isset($couch_vars['base_url']) || empty($couch_vars['base_url'])) {
      throw new CouchDBException('CouchDB base_url not set');
    }
    $this->baseURL = $couch_vars['base_url'];
    
    if (isset($couch_vars['http_auth']) && !empty($couch_vars['http_auth'])) {
      $this->httpAuthCredentials = $couch_vars['http_auth'];
    }
  }
  
  /**
   * Initializes the cURL connection.
   */
  protected function curlInitialize() {
    if (!isset($this->curlHandle)) {
      $this->curlHandle = curl_init();
      $curl_options = $this->additionalCurlOptions + array(
        CURLOPT_URL => $this->baseURL,
        CURLOPT_FOLLOWLOCATION => TRUE,
        CURLOPT_MAXREDIRS => 5,
        CURLOPT_RETURNTRANSFER => TRUE,
        CURLOPT_SSL_VERIFYPEER => FALSE,
        CURLOPT_SSL_VERIFYHOST => FALSE,
        CURLOPT_HEADERFUNCTION => array(&$this, 'curlHeaderCallback'),
      );
      if (isset($this->httpAuthCredentials)) {
        $curl_options[CURLOPT_USERPWD] = $this->httpAuthCredentials;
      }
      curl_setopt_array($this->curlHandle, $this->additionalCurlOptions + $curl_options);
    }
  }

  /**
   * Execute a cURL request.
   */
  protected function curlExec($curl_options) {
    $this->curlInitialize();
    curl_setopt_array($this->curlHandle, $this->additionalCurlOptions + $curl_options);

    $this->headers = array();
    $this->content = curl_exec($this->curlHandle);
    $this->url = curl_getinfo($this->curlHandle, CURLINFO_EFFECTIVE_URL);
    $this->status = curl_getinfo($this->curlHandle, CURLINFO_HTTP_CODE);

    // Automatically decode JSON-encoded responses.
    if ($content = json_decode($this->content)) {
      $this->content = $content;
    }
    
    // close the curl handler - Reset the handle for the next request
    curl_close($this->curlHandle);
    $this->curlHandle = NULL;
    return $this->content;
  }

  /**
   * Reads headers.
   *
   * @param $curlHandler
   *   The cURL handler.
   * @param $header
   *   An header.
   */
  protected function curlHeaderCallback($curlHandler, $header) {
    if (preg_match('/^([^:]+): (.*)$/', $header, $matches)) {
      list(, $name, $value) = $matches;
      $this->headers[$name][] = $value;
    }

    // This is required by cURL.
    return strlen($header);
  }

  /**
   * Get the content retrieved by the last request.
   */
  public function getContent() {
    return $this->content;
  }

  /**
   * Get the headers of the response to the last request.
   */
  public function getHeaders() {
    return $this->headers;
  }

  /**
   * Get the headers of the response to the last request.
   */
  public function getStatus() {
    return $this->status;
  }

  /**
   * Execute a GET request to the CouchDB server.
   *
   * @param $path
   *   The path to use, relative to the CouchDB URL.
   * @param $headers
   *   An array containing additional HTTP request headers, each formatted as
   *   "name: value".
   * @return
   *   The retrieved content, also available as $this->getContent().
   *   Headers are available as $this->getHeaders().
   */
  public function get($path, array $headers = array()) {
    return $this->curlExec(array(
      CURLOPT_URL => $this->baseURL . '/' . $path,
      CURLOPT_CUSTOMREQUEST => 'GET',
      CURLOPT_HTTPGET => TRUE,
      CURLOPT_NOBODY => FALSE,
      CURLOPT_HTTPHEADER => $headers,
    ));
  }

  /**
   * Execute a POST request to the CouchDB server.
   *
   * @param $path
   *   The path to use, relative to the CouchDB URL.
   * @param $values
   *   The values to send to the server.
   * @param $headers
   *   An array containing additional HTTP request headers, each formatted as
   *   "name: value".
   * @return
   *   The retrieved content, also available as $this->getContent().
   *   Headers are available as $this->getHeaders().
   */
  public function post($path, $values = '', array $headers = array()) {
    return $this->curlExec(array(
      CURLOPT_URL => $this->baseURL . '/' . $path,
      CURLOPT_CUSTOMREQUEST => 'POST',
      CURLOPT_POST => TRUE,
      CURLOPT_POSTFIELDS => $values,
      CURLOPT_HTTPHEADER => $headers,
    ));
  }

  /**
   * Execute a COPY request to the CouchDB server. This is a 
   * non-standard HTTP Method, only supported in CouchDB
   * @param unknown_type $path
   * @param array $headers
   */
  public function copy($path, array $headers = array()) {
    return $this->curlExec(array(
      CURLOPT_URL => $this->baseURL . '/' . $path,
      CURLOPT_CUSTOMREQUEST => 'COPY',
      CURLOPT_HTTPHEADER => $headers,
    ));
  }
  
  /**
   * Execute a PUT request to the CouchDB server.
   *
   * @param $path
   *   The path to use, relative to the CouchDB URL.
   * @param $content
   *   The content to send to the server.
   * @return
   *   The retrieved content, also available as $this->getContent().
   *   Headers are available as $this->getHeaders().
   */
  public function put($path, $content, $header = array()) {
    // Prepare the content.
    $fp = fopen("php://temp", 'r+');
    fputs($fp, $content);
    rewind($fp);

    $result = $this->curlExec(array(
      CURLOPT_URL => $this->baseURL . '/' . $path,
      CURLOPT_CUSTOMREQUEST => 'PUT',
      CURLOPT_PUT => TRUE,
      CURLOPT_INFILE => $fp,
      CURLOPT_INFILESIZE => strlen($content),
      CURLOPT_HTTPHEADER => $header,
    ));

    fclose($fp);
    return $result;
  }

  /**
   * Execute a DELETE request to the CouchDB server.
   *
   * @param $path
   *   The path to use, relative to the CouchDB URL.
   * @return
   *   The retrieved content, also available as $this->getContent().
   *   Headers are available as $this->getHeaders().
   */
  public function delete($path) {
    return $this->curlExec(array(
      CURLOPT_URL => $this->baseURL . '/' . $path,
      CURLOPT_CUSTOMREQUEST => 'DELETE',
      CURLOPT_HTTPHEADER => array(),
    ));
  }

  /**
   * List databases available in the CouchDB server.
   * @return
   *   Return all the databases in this couchDB.
   */
  public function listDatabases() {
    return $this->get("_all_dbs");
  }


  /**
   * List active tasks in a couchdb 
   * @return
   *   Return all active tasks that are running
   */
  public function getActiveTasks() {
    return $this->get("_active_tasks");
  }
  
  /**
   * Replicate a database 
   * @param $source
   *   The source database 
   * @param $target
   *   The target database
   * @param $continuous
   *   True for continuous replication. Defaults to FALSE
   * @param $cancel
   *   True to cancel replication
   * @return
   *   Return replication status
   */
  public function replicateDatabase($source, $target, $continuous = FALSE, $cancel = FALSE) {
    $values = array(
      'source' => $source,
      'target' => $target,
    );
    // identifies if continuous replication is needed
    if ($continuous) {
      $values['continuous'] = TRUE;
    }
    // cancel sends a cancel replication command to couchdb
    if ($cancel) {
      $values['cancel'] = TRUE;
    }
    return $this->post("_replicate", json_encode($values), array('Content-type: application/json'));
  }

  /**
   * Get UUIDs from CouchDB 
   * @param $count
   *   The number of ids to return.  Defaults to 1 UUID
   * @return
   *   Returns the requested UUIDS
   */
  public function getUUIDS($count = 1) {
    return $this->get('_uuids' . (($count > 1) ? '?count=' . $count : ''));
  }
  
  /**
   * Get server stats
   * @return
   *   Return couchDB stats
   */
  public function getStats() {
    return $this->get('_stats');
  }
  
  /**
   * Create a database.
   * @param $name
   *   The name of the database to create
   * @return
   *   Create Database Status
   */
  public function createDatabase($name) {
    return $this->put(urlencode($name), '');
  }

  /**
   * Delete a database.
   * @param $name
   *   The name of the database to delete
   */
  public function deleteDatabase($name) {
    return $this->delete(urlencode($name));
  }

  /**
   * Fetch information about a database.
   * @param $name
   *   The name of the database to retrieve
   * @return
   *   Database info
   */
  public function databaseInfo($name) {
    if (!empty($name)) {
      return $this->get(urlencode($name));
    }
    else {
      return NULL;
    }
  }

  /**
   * Fetch a CouchDB database object.
   *
   * @param $name
   *   The name of the database to load
   * @return
   *   Fully loaded CouchDBDatabase object with available
   *   methods for database specific operations 
   */
  public function getDatabase($name) {
    return new CouchDBDatabase($this, $name);
  }
  
}


/**
 * A simple CouchDB-specific exception.
 */
class CouchDBException extends Exception { }
