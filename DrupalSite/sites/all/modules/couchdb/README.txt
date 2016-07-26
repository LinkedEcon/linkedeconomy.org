Introduction
============
The CouchDB module provides API access to any couchDB database.  The API exposes 
a majority of the Database, Document, Design and Views api.  The CouchDB module, by
itself, does not do anything once enabled.  It provides a library to build additional
functionality or applications.

The module couchdb_watchdog is an example implementation of watchdog in CouchDB.  It
serves as an example of what can be done with the API. 

Installation
============
The CouchDB module requires a $conf['couchdb'] associative array to be declared in 
settings.php before the module can be enabled.  The module will not be enabled if 
without $conf['couchdb'].

The $conf['couchdb'] is configured as followed:

$conf['couchdb'] = array(
  'base_url' => 'http://localhost:5984',
  'http_auth' => 'admin:admin',
);

'base_url'  - This is the url to CouchDB
'http_auth' - If the database is password protected, declare the HTTP Authentication 
              credentials
              
RoadMap
============
- Implement caching with CouchDB
- Implement Views Integration


