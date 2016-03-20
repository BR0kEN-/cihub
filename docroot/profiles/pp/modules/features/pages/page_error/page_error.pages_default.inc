<?php
/**
 * @file
 * page_error.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function page_error_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'error';
  $page->task = 'page';
  $page->admin_title = 'Error';
  $page->admin_description = '';
  $page->path = 'error';
  $page->access = array(
    'plugins' => array(),
    'logic' => 'and',
  );
  $page->menu = array();
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_error';
  $handler->task = 'page';
  $handler->subtask = 'error';
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
    'name' => 'panel',
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'ctools_api:CTools\\Plugins\\Access\\HTTPStatusCode',
          'settings' => array(
            'available_codes' => array(
              403 => '403',
              404 => '404',
            ),
          ),
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $display = new panels_display();
  $display->layout = 'flexible';
  $display->layout_settings = array(
    'items' => array(
      'canvas' => array(
        'type' => 'row',
        'contains' => 'column',
        'children' => array(
          0 => 'main',
        ),
        'parent' => NULL,
      ),
      'main' => array(
        'type' => 'column',
        'width' => 100,
        'width_type' => '%',
        'children' => array(
          0 => 'main-row',
        ),
        'parent' => 'canvas',
      ),
      'main-row' => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'center',
        ),
        'parent' => 'main',
      ),
      'center' => array(
        'type' => 'region',
        'title' => 'Content',
        'width' => 100,
        'width_type' => '%',
        'parent' => 'main-row',
        'class' => '',
        'hide_empty' => 0,
      ),
    ),
  );
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'center' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = 'Error';
  $display->uuid = 'adefdf58-78c3-45b4-9666-904b08b132e1';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-3d30903d-edac-4cf5-9361-e9494a7c7ce8';
    $pane->panel = 'center';
    $pane->type = 'custom';
    $pane->subtype = 'custom';
    $pane->shown = TRUE;
    $pane->access = array(
      'plugins' => array(
        0 => array(
          'name' => 'ctools_api:CTools\\Plugins\\Access\\HTTPStatusCode',
          'settings' => array(
            'available_codes' => array(
              403 => '403',
            ),
          ),
          'not' => FALSE,
        ),
      ),
    );
    $pane->configuration = array(
      'admin_title' => '403',
      'title' => '403',
      'body' => '403',
      'format' => 'plain_text',
      'substitute' => TRUE,
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '3d30903d-edac-4cf5-9361-e9494a7c7ce8';
    $display->content['new-3d30903d-edac-4cf5-9361-e9494a7c7ce8'] = $pane;
    $display->panels['center'][0] = 'new-3d30903d-edac-4cf5-9361-e9494a7c7ce8';
    $pane = new stdClass();
    $pane->pid = 'new-28a1319e-eed1-454c-8c19-0117ba11d1e3';
    $pane->panel = 'center';
    $pane->type = 'custom';
    $pane->subtype = 'custom';
    $pane->shown = TRUE;
    $pane->access = array(
      'plugins' => array(
        0 => array(
          'name' => 'ctools_api:CTools\\Plugins\\Access\\HTTPStatusCode',
          'settings' => array(
            'available_codes' => array(
              404 => '404',
            ),
          ),
          'not' => FALSE,
        ),
      ),
    );
    $pane->configuration = array(
      'admin_title' => '404',
      'title' => '404',
      'body' => '404',
      'format' => 'plain_text',
      'substitute' => TRUE,
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '28a1319e-eed1-454c-8c19-0117ba11d1e3';
    $display->content['new-28a1319e-eed1-454c-8c19-0117ba11d1e3'] = $pane;
    $display->panels['center'][1] = 'new-28a1319e-eed1-454c-8c19-0117ba11d1e3';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-3d30903d-edac-4cf5-9361-e9494a7c7ce8';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['error'] = $page;

  return $pages;

}
