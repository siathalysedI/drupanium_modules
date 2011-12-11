<?php 
/**
 * Callback to show a form and flag a node
 */
function drupanium_debug_flag_page($form) {
  
  $form['markup'] = array(
    '#markup' => t("Flag a node")
  );
  
  $form['flag_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Flag name'),
    '#default_value' => 'bookmarks',
    '#description' => t("Enter the name of the flag"),
  	'#required' => TRUE,
  );

  $form['content_id'] = array(
    '#type' => 'textfield',
    '#title' => t("Content ID"),
    '#description' => t("This could be a node id, a comment id or a user id"),
    '#required' => TRUE,
  );
  
  $form['uid'] = array(
    '#type' => 'textfield',
    '#title' => t("User ID"),
    '#description' => t("Enter the user id"),
  	'#required' => TRUE,
  );
  
  $form['action'] = array(
    '#type' => 'select',
    '#title' => t("Action to perform"),
    '#options' => array(
      'flag' => t("Flag"),
      'unflag' => t("Unflag")
    ),
    '#required' => TRUE,
  );
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t("Submit")
  );
  
  return $form;
}

/**
 * Submit callback for drupanium_debug_flag_page
 */
function drupanium_debug_flag_page_submit($form, &$form_state) {
  $values = $form_state['values'];
  
  $is_flagged = drupanium_check_if_flagged($values['flag_name'], $values['content_id'], $values['uid']);
  
  // The URL doesn't change
  $url = variable_get("drupanium_url") . "flag/flag.json";
  
  drupal_set_message("URL is: " . $url);
  
  // Build and array
  $flag = array(
    'flag_name' => $values['flag_name'],
    'content_id' => $values['content_id'],
    'uid' => $values['uid'],
    'action' => $values['action']
  );
  
  // The content is flagged, we can't select the action as "flag"
  if($is_flagged) {
    // Check what is the action we're requesting
    if($values['action'] == "flag") {
      drupal_set_message("The content is already flagged by that user, can't flag it again. Change the action to unflag.");
    }
    else {
      // Do the magic
      $response = _drupanium_send($flag, $url);
      dsm($response);
    }
  }
  // The content is not flagged, we can't select "unflag" as the action
  else {
    if($values['action'] == "unflag") {
      drupal_set_message("The content is not flagged by that user, can't unflag it. Change the action to flag.");
    }
    else {
      // Do the magic
      $response = _drupanium_send($flag, $url);
      dsm($response);      
    }
  }
}

/**
 * Check if the given node is flagged by the given user
 * @return TRUE if is flagged
 */
function drupanium_check_if_flagged($flag_name, $content_id, $uid) {
  $flag = array(
    'flag_name' => $flag_name,
    'content_id' => $content_id,
    'uid' => $uid,
  );
  
  $url = variable_get("drupanium_url") . "flag/is_flagged.json";
  
  drupal_set_message("Checking if the content_id is flagged. URL is: " . $url);
  
  $response = _drupanium_send($flag, $url);
  if($response) {
    return $response;
  }
}

/**
 * This function will send the data to the server and return the response
 * 
 * @param array $flag
 * @param string $url
 */
function _drupanium_send($flag, $url) {
  $data = http_build_query($flag, '', '&');
      
  $headers = array();
  $options = array(
    'headers' => array(
      'Accept' => 'application/json',
    ),
    'method' => 'POST',
    'data' => $data
  );
      
  $response = drupal_http_request($url, $options);
     
  if ($response->code == 200) {
    $res = drupal_json_decode($response->data);
    return $res;
  }
}

/**
 * Callback to customize the isflag
 */
function drupanium_debug_isflag_page($form) {
  
  $form['markup'] = array(
    '#markup' => t("Check if the given user has flagged a node")
  );
  
  $form['flag_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Flag name'),
    '#default_value' => 'bookmarks',
    '#description' => t("Enter the name of the flag"),
  	'#required' => TRUE,
  );

  $form['content_id'] = array(
    '#type' => 'textfield',
    '#title' => t("Content ID"),
    '#description' => t("This could be a node id, a comment id or a user id"),
    '#default_value' => 1,
    '#required' => TRUE,
  );
  
  $form['uid'] = array(
    '#type' => 'textfield',
    '#title' => t("User ID"),
    '#default_value' => 1,
    '#description' => t("Enter the user id"),
  	'#required' => TRUE,
  ); 
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t("Submit")
  );
  
  return $form;
}

/**
 * Submit callback for drupanium_debug_isflag_page
 */
function drupanium_debug_isflag_page_submit($form, &$form_state) {
  $values = $form_state['values'];
    
  $response = drupanium_check_if_flagged($values['flag_name'], $values['content_id'], $values['uid']);
  
  drupal_set_message("If the node is flagged, you'll get TRUE (1) as response, if the node is not flagged, you'll get FALSE (nothing)");
  if($response) {
    dsm($response);
  }
}