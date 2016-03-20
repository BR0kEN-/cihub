<?php
/**
 * @file
 * page_node_view.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_handlers().
 */
function page_node_view_default_page_manager_handlers() {
  $export = array();

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'node_server';
  $handler->task = 'node_view';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Server',
    'no_blocks' => 1,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'name' => '',
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'node_type',
          'settings' => array(
            'type' => array(
              'server' => 'server',
            ),
          ),
          'context' => 'argument_entity_id:node_1',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $display = new panels_display();
  $display->layout = 'flexible';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'center' => NULL,
      'default' => NULL,
    ),
    'style' => 'naked',
    'center' => array(
      'style' => 'naked',
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '7f3518a6-d58a-4251-ab6e-78258ccd2160';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-4236a565-f66f-4af5-9ee2-316291d21350';
    $pane->panel = 'center';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:ansible_host';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'hidden',
      'formatter' => 'text_default',
      'delta_limit' => 0,
      'delta_offset' => '0',
      'delta_reversed' => FALSE,
      'formatter_settings' => array(),
      'context' => 'argument_entity_id:node_1',
      'override_title' => 0,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'style' => 'naked',
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '4236a565-f66f-4af5-9ee2-316291d21350';
    $display->content['new-4236a565-f66f-4af5-9ee2-316291d21350'] = $pane;
    $display->panels['center'][0] = 'new-4236a565-f66f-4af5-9ee2-316291d21350';
    $pane = new stdClass();
    $pane->pid = 'new-d583a6bd-93b0-4876-a736-6df5422389a1';
    $pane->panel = 'center';
    $pane->type = 'ctools_api';
    $pane->subtype = 'CTools\\Plugins\\ContentTypes\\AnsibleProvision';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'theme' => 'default',
      'context' => 'argument_entity_id:node_1',
      'override_title' => TRUE,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = 'd583a6bd-93b0-4876-a736-6df5422389a1';
    $display->content['new-d583a6bd-93b0-4876-a736-6df5422389a1'] = $pane;
    $display->panels['center'][1] = 'new-d583a6bd-93b0-4876-a736-6df5422389a1';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $export['node_server'] = $handler;

  return $export;
}
