<?php
/**
 * @file
 * page_user_view.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_handlers().
 */
function page_user_view_default_page_manager_handlers() {
  $export = array();

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'user';
  $handler->task = 'user_view';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Default',
    'no_blocks' => 1,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'name' => '',
  );
  $display = new panels_display();
  $display->layout = 'flexible';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'center' => NULL,
    ),
    'style' => 'naked',
    'center' => array(
      'style' => 'naked',
    ),
  );
  $display->cache = array();
  $display->title = '%user:name';
  $display->uuid = '7eaa8a62-559f-4bbd-8ba9-2c4a300b8ab7';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-7fb46b96-f1ef-4685-ad85-9fb37fd60105';
    $pane->panel = 'center';
    $pane->type = 'views';
    $pane->subtype = 'servers';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_pager_settings' => 0,
      'use_pager' => 1,
      'nodes_per_page' => '0',
      'pager_id' => '0',
      'offset' => '0',
      'more_link' => 0,
      'feed_icons' => 0,
      'panel_args' => 0,
      'link_to_view' => 0,
      'args' => '',
      'url' => '',
      'display' => 'default',
      'context' => array(
        0 => 'argument_entity_id:user_1.uid',
      ),
      'override_title' => 0,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '7fb46b96-f1ef-4685-ad85-9fb37fd60105';
    $display->content['new-7fb46b96-f1ef-4685-ad85-9fb37fd60105'] = $pane;
    $display->panels['center'][0] = 'new-7fb46b96-f1ef-4685-ad85-9fb37fd60105';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $export['user'] = $handler;

  return $export;
}
