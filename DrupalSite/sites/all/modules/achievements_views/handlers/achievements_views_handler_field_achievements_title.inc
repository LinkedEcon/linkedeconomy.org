<?php

/**
 * A handler for achievement titles.
 *
 */
class achievements_views_handler_field_achievements_title extends views_handler_field_prerender_list {
  function construct() {
    parent::construct();
    $this->additional_fields['uid'] = array('table' => 'users', 'field' => 'uid');
 
  }
  function query() {
     $this->add_additional_fields();
    $this->field_alias = $this->aliases['uid'];
   }

  function pre_render(&$values) {
    $uids = array();
    $this->items = array();

    foreach ($values as $result) {
      $uids[] = $this->get_value($result, NULL, TRUE);
    }

    if ($uids) {
      $result = db_query("SELECT a.uid, a.achievement_id FROM {$this->table} a WHERE a.uid IN (:uids)", array(':uids' => $uids));
      foreach ($result as $item) {
        $achievement = achievements_load($item->achievement_id);
        if ($achievement) {
          $this->items[$item->uid][$item->achievement_id]['title'] = check_plain($achievement['title']);
        }
        else {
          $this->items[$item->uid][$item->achievement_id]['title'] = t('Unknown');
        }
       }
    }
  }

      function render_item($count, $item) {
    return $item['title'];
  }
}
