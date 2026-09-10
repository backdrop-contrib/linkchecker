<?php

/**
 * @file
 * Bee interface to linkchecker functionalities.
 */

/**
 * Implements hook_bee_command().
 */
function linkchecker_bee_command() {
  $commands = array();

  $commands['linkchecker-analyze'] = array(
    'description' => 'Reanalyzes content for links. Recommended after module has been upgraded.',
    'callback' => 'bee_linkchecker_analyze',
    'group' => 'linkchecker',
    'examples' => array(
      'bee linkchecker-analyze' => bt('Reanalyzes content for links.'),
    ),
    'bootstrap' => BEE_BOOTSTRAP_FULL,
  );
  $commands['linkchecker-clear'] = array(
    'description' => 'Clears all link data and analyze content for links. WARNING: Custom link check settings are deleted.',
    'callback' => 'bee_linkchecker_clear',
    'group' => 'linkchecker',
    'examples' => array(
      'bee linkchecker-clear' => bt('Clears all link data and analyze content for links.'),
    ),
    'bootstrap' => BEE_BOOTSTRAP_FULL,
  );
  $commands['linkchecker-check'] = array(
    'description' => 'Check link status.',
    'callback' => 'bee_linkchecker_check',
    'group' => 'linkchecker',
    // 'options' => array(
    //   'links' => 'Number of links to check in one round. Default: 1000',
    // ),
    'examples' => array(
      'bee linkchecker-checker' => bt('Check link status.'),
    ),
    'bootstrap' => BEE_BOOTSTRAP_FULL,
  );

  return $commands;
}

/**
 * Callback for command linkchecker-analyze.
 */
function bee_linkchecker_analyze() {
  global $base_url;
  if ($base_url == 'http://default') {
    bee_message(bt('You MUST configure the site $base_url or provide --root parameter.'), 'error');
    return;
  }

  module_load_include('inc', 'linkchecker', 'linkchecker.admin');

  // Fake $form_state to leverage _submit function.
  $form_state = array(
    'values' => array('op' => t('Analyze content for links')),
    'buttons' => array(),
  );

  $node_types = linkchecker_scan_node_types();
  if (!empty($node_types) || config_get('linkchecker.settings', 'scan_blocks')) {
    linkchecker_analyze_links_submit(NULL, $form_state);
    $batch = &batch_get();
    $batch['progressive'] = FALSE;
    batch_process();
  }
  else {
    bee_message(bt('No content configured for link analysis.'), 'info');
    return;
  }
}

/**
 * Callback for command linkchecker-analyze.
 */
function bee_linkchecker_clear() {
  global $base_url;
  if ($base_url == 'http://default') {
    bee_message(bt('You MUST configure the site $base_url or provide --root parameter.'), 'error');
    return;
  }

  module_load_include('inc', 'linkchecker', 'linkchecker.admin');

  // Fake $form_state to leverage _submit function.
  $form_state = array(
    'values' => array('op' => t('Clear link data and analyze content for links')),
    'buttons' => array(),
  );

  $node_types = linkchecker_scan_node_types();
  if (!empty($node_types) || config_get('linkchecker.settings', 'scan_blocks')) {
    linkchecker_clear_analyze_links_submit(NULL, $form_state);
    $batch = &batch_get();
    $batch['progressive'] = FALSE;
    batch_process();
  }
  else {
    bee_message(bt('No content configured for link analysis.'), 'info');
    return;
  }
}

/**
 * Callback for command linkchecker-check.
 */
function bee_linkchecker_check() {
  bee_instant_message(bt('Starting link checking...'), 'info');
  $run = _linkchecker_check_links();
  if (!$run) {
    bee_message(
      bt('Attempted to re-run link checks while they are already running.'), 'warning');
  }
  else {
    bee_message(bt('Finished checking links.'), 'info');
  }
}
