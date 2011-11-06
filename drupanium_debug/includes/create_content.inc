<?php 

/**
 * Callback to demonstrate the use of Services User Resource
 */
function drupanium_debug_create_content_page($form) {
  $form = array();
  
  $form['user'] = array(
    '#type' => 'fieldset',
    '#title' => t("User"),
  );
  
  $form['user']['username'] = array(
    '#type' => 'textfield',
    '#title' => 'Username',
    '#required' => TRUE,
  );
  
  $form['user']['password'] = array(
    '#type' => 'textfield',
    '#title' => 'Password',
  	'#required' => TRUE,
  );
    
  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t("Title"),
  );
  
  $form['body'] = array(
    '#type' => 'textarea',
    '#title' => t("Body"),
  );
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t("Save"),
    '#submit' => array("drupanium_debug_create_content_page_submit"),
  );
    
  return $form;
}

/**
 * Submit callback to login a user
 * 
 * @see drupanium_debug_user_login_page()
 */
function drupanium_debug_create_content_page_submit(&$form, &$form_state) {
  // Get the URI
  $uri = variable_get("drupanium_user_login");
  
  // Print the URI to the screen
  drupal_set_message("URI is: " . $uri);
  
  $account = array(
    'username' => $form_state['values']['username'],
    'password' => $form_state['values']['password'],
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
  
  if ($response->code == 200) {
    // Now recycle the login cookie we recieved in the first request
    $options['headers']['Cookie'] = $auth['session_name'] . '=' . $auth['sessid'];
  
    $title = $form_state['values']['title'];
    $body = $form_state['values']['body'];
  
    $uri_node = variable_get("drupanium_create_content");
    
     // Print the URI to the screen
    drupal_set_message("URI is: " . $uri_node);
    
    $node = array(
      	'title' => $title,
        'body' => array(
					'und' => array(
						0 => array(
							'value' => $body,	
						)
					)
				),
        'type' => 'article',
    );
		
		drupal_set_message(check_plain(drupal_json_encode($node)));
    
    $query = http_build_query($node, '', '&');
    
    drupal_set_message("Query is: " . $query);
    
    $options["data"] = $query;
    
    // Get the file
    $node_response = drupal_http_request($uri_node, $options);
    
    drupal_set_message("Response is: ");
    dsm($node_response);
    
   // Decode the response
    $auth_node = drupal_json_decode($node_response->data);
    
    // Print the elements using devel
    if($auth_node) {
      dsm($auth_node);
    }
    
    // Check if login was successful
    if ($node_response->code == 200) {
      // Now recycle the login cookie we recieved in the first request
      
      // Decode the response
      $new_node = drupal_json_decode($node_response->data);
      
      $new_node_uri = $new_node['uri'];
      drupal_set_message("New node URI is: " . $new_node_uri);
      
      $new_node_response = file_get_contents($new_node_uri);
  
      // Decode the response
      $elements = drupal_json_decode($new_node_response);
          
      drupal_set_message("Getting information about the node " . $elements['title']);
      drupal_set_message("This is the new node: "); 
      dsm($elements);
    }
    else {
      drupal_set_message("There was an error, code is: " . $node_response->code);
    }
  }
}
 