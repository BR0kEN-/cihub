<?php
/**
 * @file
 * page_site_template.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_handlers().
 */
function page_site_template_default_page_manager_handlers() {
  $export = array();

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'content';
  $handler->task = 'site_template';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = 1;
  $handler->conf = array(
    'title' => 'Content only',
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
      'plugins' => array(),
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
    'center' => array(
      'style' => 'naked',
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = 'd20ff045-b5a3-4423-a853-7be62f28a74e';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-4217f66c-50af-4f23-b77a-5d7b51cd264a';
    $pane->panel = 'center';
    $pane->type = 'page_tabs';
    $pane->subtype = 'page_tabs';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'type' => 'both',
      'id' => 'tabs',
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
    $pane->uuid = '4217f66c-50af-4f23-b77a-5d7b51cd264a';
    $display->content['new-4217f66c-50af-4f23-b77a-5d7b51cd264a'] = $pane;
    $display->panels['center'][0] = 'new-4217f66c-50af-4f23-b77a-5d7b51cd264a';
    $pane = new stdClass();
    $pane->pid = 'new-5c843c69-6133-4f41-898b-6b0483738138';
    $pane->panel = 'center';
    $pane->type = 'page_messages';
    $pane->subtype = 'page_messages';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '5c843c69-6133-4f41-898b-6b0483738138';
    $display->content['new-5c843c69-6133-4f41-898b-6b0483738138'] = $pane;
    $display->panels['center'][1] = 'new-5c843c69-6133-4f41-898b-6b0483738138';
    $pane = new stdClass();
    $pane->pid = 'new-a41a1775-6fe6-49cf-9cbe-4e2ef137c70e';
    $pane->panel = 'center';
    $pane->type = 'page_content';
    $pane->subtype = 'page_content';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => 'argument_page_content_1',
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
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = 'a41a1775-6fe6-49cf-9cbe-4e2ef137c70e';
    $display->content['new-a41a1775-6fe6-49cf-9cbe-4e2ef137c70e'] = $pane;
    $display->panels['center'][2] = 'new-a41a1775-6fe6-49cf-9cbe-4e2ef137c70e';
  $display->hide_title = PANELS_TITLE_NONE;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $export['content'] = $handler;

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'default';
  $handler->task = 'site_template';
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
          0 => 1,
          1 => 'main-row',
          2 => 2,
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
      1 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'header',
        ),
        'parent' => 'main',
        'class' => '',
        'hide_empty' => 0,
      ),
      'header' => array(
        'type' => 'region',
        'title' => 'Header',
        'width' => 100,
        'width_type' => '%',
        'parent' => '1',
        'class' => '',
        'hide_empty' => 0,
      ),
      2 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'footer',
        ),
        'parent' => 'main',
        'class' => '',
        'hide_empty' => 0,
      ),
      'footer' => array(
        'type' => 'region',
        'title' => 'Footer',
        'width' => 100,
        'width_type' => '%',
        'parent' => '2',
        'class' => '',
        'hide_empty' => 0,
      ),
    ),
  );
  $display->panel_settings = array(
    1 => array(
      'style' => NULL,
    ),
    'style_settings' => array(
      1 => NULL,
      'header' => NULL,
      2 => NULL,
      'footer' => NULL,
      'default' => NULL,
      'center' => NULL,
    ),
    'header' => array(
      'style' => 'naked',
    ),
    2 => array(
      'style' => NULL,
    ),
    'footer' => array(
      'style' => 'naked',
    ),
    'center' => array(
      'style' => 'naked',
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '36a84fbc-d9a3-490f-a019-36e4d874ac1a';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-fe9a232e-4070-4a8e-a473-bca4e7f76efe';
    $pane->panel = 'center';
    $pane->type = 'page_tabs';
    $pane->subtype = 'page_tabs';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'type' => 'both',
      'id' => 'tabs',
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
    $pane->uuid = 'fe9a232e-4070-4a8e-a473-bca4e7f76efe';
    $display->content['new-fe9a232e-4070-4a8e-a473-bca4e7f76efe'] = $pane;
    $display->panels['center'][0] = 'new-fe9a232e-4070-4a8e-a473-bca4e7f76efe';
    $pane = new stdClass();
    $pane->pid = 'new-dc69268a-5351-4679-97c0-4f7760dbe2bd';
    $pane->panel = 'center';
    $pane->type = 'page_messages';
    $pane->subtype = 'page_messages';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = 'dc69268a-5351-4679-97c0-4f7760dbe2bd';
    $display->content['new-dc69268a-5351-4679-97c0-4f7760dbe2bd'] = $pane;
    $display->panels['center'][1] = 'new-dc69268a-5351-4679-97c0-4f7760dbe2bd';
    $pane = new stdClass();
    $pane->pid = 'new-e3ffe04a-2d01-45b7-ba35-b0c491c9154e';
    $pane->panel = 'center';
    $pane->type = 'page_content';
    $pane->subtype = 'page_content';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => 'argument_page_content_1',
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
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = 'e3ffe04a-2d01-45b7-ba35-b0c491c9154e';
    $display->content['new-e3ffe04a-2d01-45b7-ba35-b0c491c9154e'] = $pane;
    $display->panels['center'][2] = 'new-e3ffe04a-2d01-45b7-ba35-b0c491c9154e';
    $pane = new stdClass();
    $pane->pid = 'new-1902acc1-241d-4967-b461-283dbca55591';
    $pane->panel = 'footer';
    $pane->type = 'panels_mini';
    $pane->subtype = 'footer';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
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
    $pane->uuid = '1902acc1-241d-4967-b461-283dbca55591';
    $display->content['new-1902acc1-241d-4967-b461-283dbca55591'] = $pane;
    $display->panels['footer'][0] = 'new-1902acc1-241d-4967-b461-283dbca55591';
    $pane = new stdClass();
    $pane->pid = 'new-43e1c17f-733b-4ef1-936d-bd3d9d3d1ac1';
    $pane->panel = 'header';
    $pane->type = 'panels_mini';
    $pane->subtype = 'header';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
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
    $pane->uuid = '43e1c17f-733b-4ef1-936d-bd3d9d3d1ac1';
    $display->content['new-43e1c17f-733b-4ef1-936d-bd3d9d3d1ac1'] = $pane;
    $display->panels['header'][0] = 'new-43e1c17f-733b-4ef1-936d-bd3d9d3d1ac1';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-43e1c17f-733b-4ef1-936d-bd3d9d3d1ac1';
  $handler->conf['display'] = $display;
  $export['default'] = $handler;

  return $export;
}
