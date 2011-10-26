<?php 


/**
 * Callback to demonstrate the use of Services User Resource
 */
function drupanium_debug_user_page($form) {
  $form = array();
  
  $form['uid'] = array(
    '#type' => 'textfield',
    '#title' => t("User uid to get:"),
  );
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t("Search"),
    '#submit' => array("drupanium_debug_user_page_submit"),
  );
    
  return $form;
}

/**
 * Submit callback to get a user
 * 
 * @see drupanium_debug_user_page()
 */
function drupanium_debug_user_page_submit(&$form, &$form_state) {
  $uid = $form_state['values']['uid'];
    
  drupal_goto("drupanium/user/" . $uid);
}

/**
 * Callback to demonstrate the use of Services Search User Get 
 * 
 * @param $uid string the uid of the user to search for
 */
function drupanium_debug_user_page_results($uid) {
  drupal_set_title(t("Getting user with uid ") . $uid);
  
  // Get the URI
  $uri = variable_get("drupanium_user") . $uid . '.json';
  
  // Print the URI to the screen
  drupal_set_message("URI is: " . $uri);
  
  // Get the file
  $response = file_get_contents($uri);
  
  drupal_set_message("Response is: ");
  dsm($response);
  
  // Decode the response
  $user = drupal_json_decode($response);
  
  // Print the elements using devel
  dsm($user);
  
  $data[] = "Username: " . $user['name'];
  $data[] = "E-mail: " . $user['mail'];
  $data[] = "UID: " . $user['uid'];
  
  $output = theme("item_list", array('items' => $data));
  
  return $output;  
}