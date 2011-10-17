<?php 

/**
 * Callback to demonstrate the use of Services User Resource
 */
function drupanium_debug_user_login_page($form) {
  $form = array();
  
  drupal_set_message("Passwords will be transfered in plain text, be careful");
  
  $form['username'] = array(
    '#type' => 'textfield',
    '#title' => t("Username"),
  );
  
  $form['password'] = array(
    '#type' => 'textfield',
    '#title' => t("Password"),
  );
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t("Login"),
    '#submit' => array("drupanium_debug_user_login_page_submit"),
  );
    
  return $form;
}

/**
 * Submit callback to login a user
 * 
 * @see drupanium_debug_user_login_page()
 */
function drupanium_debug_user_login_page_submit(&$form, &$form_state) {
  $username = $form_state['values']['username'];
  $password = $form_state['values']['password'];
  
  drupal_set_message("Trying to login using username " . $username . " and password " . $password);
    
  // Get the URI
  $uri = variable_get("drupanium_user_login");
  
  // Print the URI to the screen
  drupal_set_message("URI is: " . $uri);
  
  $account = array(
    'username' => $username,
    'password' => $password,
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
  
  // Decode the response
  $auth = drupal_json_decode($response->data);
  
  // Print the elements using devel
  dsm($auth);
  
  // Check if login was successful
  if ($response->code == 200) {
    drupal_set_message("Login successful. Session name is: " . $auth["session_name"] . " and Session ID is: " . $auth["sessid"]);
    
    // Now recycle the login cookie we recieved in the first request
    $options['headers']['Cookie'] = $auth['session_name'] . '=' . $auth['sessid'];
    $uid = 1;
    
    // Get info about a user
    $user = array();
    $options['data'] = http_build_query($user, '', '&');
    $options['method'] = 'GET';
    $user_requested = drupal_http_request(variable_get("drupanium_user") . $uid . '.json', $options);
    
    drupal_set_message("Requesting user");
    dsm($user_requested);
    
    // Decode the response
    $user_response = drupal_json_decode($user_requested->data);
        
    drupal_set_message("Getting information about the user " . $user_response['name']);
    dsm($user_response);
  }
  
}
 