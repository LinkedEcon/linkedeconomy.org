
Protected Node Documentation
----------------------------

 * Original :   http://www.m2osw.com/doc-protected-node
 * Drupal.org : https://drupal.org/node/2176627


Description
-----------

With the protected node module users can restrict access to a node with a
password they provide when creating the node (or a site wide password or a per
node type password.) On node creation authorized authors can protect a node by
supplying a password and verify strength of the password via JavaScript.

People who want to view the node or download one of its private attachments are
first redirected to a password query page (/protected-node). Once the user
entered the right password, he is redirected back to the original node.
Authorizations are stored in sessions, so users don't have to enter the
password over and over again once provided (requires cookies.)

The module includes support for sending emails, views, and rules.


Installation
------------

There is no special requirement for this module.

Once enabled, go to the administer permissions page to set the new permissions.


Configuration
-------------

Global settings : /admin/config/content/protected_node

Per content type : admin/structure/types/manage/%content_type
In the fieldset "Protected node settings".

You can set password on the add/edit node form in the fieldset
"Password protect this %type_name".


Email extension
---------------

The module is capable of sending the password via unencrypted emails. This is
useful if you create a page to be viewed only by a few people you know.


Views extension
---------------

The module has a few extensions supporting Views. It includes filters and
output extensions.


Rules extension
---------------

The module includes a Rules extension allowing you to act on a protected node
and test the current state of a node for the current user.


Known conflicts
---------------

 * Login Destination


Similar Modules
---------------

 * Protected Pages
