<?php
/**
* @file
* Administration page callbacks for the mtsslide module.
*/

/**
* Form builder. Configure mtsslide.
*
* @ingroup forms
* @see system_settings_form().
*/
function mtsslide_admin_settings() {
    // Get an array of node types with internal names as keys and
    // "friendly names" as values. E.g.,
    // array('page' => ’Basic Page, 'article' => 'Articles')
    $types = node_type_get_types();

    foreach($types as $node_type) {
        $options[$node_type->type] = $node_type->name;
    }

    $effect_options = array(
        'blindX' => 'blindX',
        'blindY' => 'blindY',
        'blindZ' => 'blindZ',
        'cover' => 'cover',
        'curtainX' => 'curtainX',
        'curtainY' => 'curtainY',
        'fade' => 'fade',
        'fadeZoom' => 'fadeZoom',
        'growX' => 'growX',
        'growY' => 'growY',
        'none' => 'none',
        'scrollUp' => 'scrollUp',
        'scrollDown' => 'scrollDown',
        'scrollLeft' => 'scrollLeft',
        'scrollRight' => 'scrollRight',
        'scrollHorz' => 'scrollHorz',
        'scrollVert' => 'scrollVert',
        'shuffle' => 'shuffle',
        'slideX' => 'slideX',
        'slideY' => 'slideY',
        'toss' => 'toss',
        'turnUp' => 'turnUp',
        'turnDown' => 'turnDown',
        'turnLeft' => 'turnLeft',
        'turnRight' => 'turnRight',
        'uncover' => 'uncover',
        'wipe' => 'wipe',
        'zoom' => 'zoom',
    );

    $form['mtsslide_node_types'] = array(
        '#type' => 'select',
        '#title' => t('select one content types to display in slide'),
        '#options' => $options,
        '#default_value' => variable_get('mtsslide_node_types', 'page'),
    );

    $form['mtsslide_total_node'] = array(
        '#type' => 'textfield',
        '#title' => t('Insert total node to display in slide'),
        '#default_value' => variable_get('mtsslide_total_node', '0'),
        '#description' => t('if total node is smaller than 1, this will display all node for selected content type.'),

    );

    $form['mtsslide_width'] = array(
        '#type' => 'textfield',
        '#title' => t('Width of slide block'),
        '#default_value' => variable_get('mtsslide_width', '675'),
        '#description' => t('Example:  200px or 200 or 200pt'),

    );

    $form['mtsslide_height'] = array(
        '#type' => 'textfield',
        '#title' => t('Height of slide block'),
        '#default_value' => variable_get('mtsslide_height', '200'),
        '#description' => t('Example:  200px or 200 or 200pt'),

    );

    $form['mtsslide_js_effect'] = array(
        '#type' => 'select',
        '#title' => t('select one effect types to display slide'),
        '#options' => $effect_options,
        '#default_value' => variable_get('mtsslide_js_effect', 'fade'),
    );

    $form['mtsslide_js_timeout'] = array(
        '#type' => 'textfield',
        '#title' => t('Height of slide block'),
        '#default_value' => variable_get('mtsslide_js_timeout', '4000'),
        '#description' => t('Unit in milisecond'),

    );

    $form['mtsslide_js_speed'] = array(
        '#type' => 'textfield',
        '#title' => t('Speed of a slide'),
        '#default_value' => variable_get('mtsslide_js_speed', '1000'),
        '#description' => t('Unit in milisecond'),
    );

    $form['#submit'][] = 'mtsslide_admin_settings_submit';
    return system_settings_form($form);
    //return $form;
}

function mtsslide_admin_settings_submit($form, $form_state) {
    variable_set(
        'mtsslide_node_types',
        $form_state['values']['mtsslide_node_types']
    );

    variable_set(
        'mtsslide_total_node',
        $form_state['values']['mtsslide_total_node']
    );

    variable_set(
        'mtsslide_width',
        $form_state['values']['mtsslide_width']
    );

    variable_set(
        'mtsslide_height',
        $form_state['values']['mtsslide_height']
    );

    variable_set(
        'mtsslide_js_effect',
        $form_state['values']['mtsslide_js_effect']
    );

    variable_set(
        'mtsslide_js_timeout',
        $form_state['values']['mtsslide_js_timeout']
    );

    variable_set(
        'mtsslide_js_speed',
        $form_state['values']['mtsslide_js_speed']
    );


    $css_file = file_get_contents(
        drupal_get_path('module', 'mtsslide'). '/css/mtsslide-pat.css'
    );

    $replacement = array(
        variable_get('mtsslide_width', '675'),
        variable_get('mtsslide_height', '200'),
    );

    $pattern = array('/\$width/', '/\$height/');

    file_put_contents(
        drupal_get_path('module', 'mtsslide'). '/css/mtsslide.css',
        preg_replace($pattern, $replacement, $css_file)
    );


    $js_file = file_get_contents(
        drupal_get_path('module', 'mtsslide'). '/js/mtsslide-pat.js'
    );

    $replacement = array(
        variable_get('mtsslide_js_effect', 'fade'),
        variable_get('mtsslide_js_timeout', '4000'),
        variable_get('mtsslide_js_speed', '1000'),
    );

    $pattern = array('/\$fx/', '/\$timeout/', '/\$speed/');

    file_put_contents(
        drupal_get_path('module', 'mtsslide'). '/js/mtsslide.js',
        preg_replace($pattern, $replacement, $js_file)
    );


    watchdog(
        'MTSSlide',
        'update mtsslide configuration'
    );
}
