<?php

/**
 * @file
 * Default simple view template to display a rows in a grid.
 *
 * - $rows contains a nested array of rows. Each row contains an array of
 *   columns.
 *
 * @ingroup views_templates
 */
?>
<?php if (!empty($title)) : ?>
  <h3><?php print $title; ?></h3>
<?php endif; ?>

<?php foreach ($rows as $row_number => $columns): ?>
  <div class="row-fluid portfolio-block-2">
    <?php foreach ($columns as $column_number => $item): ?>
      <div class="span4 portfolio2-item">
        <?php print $item; ?>
      </div>
    <?php endforeach; ?>
  </div>
<?php endforeach; ?>
