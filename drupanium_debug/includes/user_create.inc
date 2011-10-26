<?php 


/**
 * Callback to demonstrate the use of Services User Resource
 */
function drupanium_debug_user_create_page($form) {
  $form = array();
  
  $form['user']['username'] = array(
    '#type' => 'textfield',
    '#title' => 'Username',
    '#required' => TRUE,
  );
  
  $form['user']['mail'] = array(
    '#type' => 'textfield',
    '#title' => 'Mail',
  	'#required' => TRUE,
  );
  
  $form['user']['password'] = array(
    '#type' => 'textfield',
    '#title' => 'Password',
  	'#required' => TRUE,
  );
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t("Create user"),
    '#submit' => array("drupanium_debug_user_create_page_submit"),
  );
    
  return $form;
}

/**
 * Submit callback to get a user
 * 
 * @see drupanium_debug_user_page()
 */
function drupanium_debug_user_create_page_submit(&$form, &$form_state) {
    
  // Get the URI
  $uri = variable_get("drupanium_user");
  
  // Print the URI to the screen
  drupal_set_message("URI is: " . $uri);
  
  $account = array(
    'name' => $form_state['values']['username'],
    'pass' => $form_state['values']['password'],
    'mail' => $form_state['values']['mail'],
  );
  
  $data = http_build_query($account, '', '&');
  
  $headers = array();
  $options = array(
    'headers' => array(
      'Accept' => 'application/json',
    ),
    'method' => 'POST',
    'data' => $data
  );
  
  // Get the file
  $response = drupal_http_request($uri, $options);
  
  dsm($response);
  
  // Decode the response
  $auth = drupal_json_decode($response->data);
  
  // Print the elements using devel
  dsm($auth);
  
  // Check if login was successful
  if ($response->code == 200) {
      // Now recycle the login cookie we recieved in the first request
      // Decode the response
      $new_user = drupal_json_decode($response->data);
      
      drupal_set_message("User was created with uid: " . $new_user['uid']);
      dsm($new_user);
    }
    else {
      drupal_set_message("There was an error, the status code is: " . $response->code);
    }
  
}
