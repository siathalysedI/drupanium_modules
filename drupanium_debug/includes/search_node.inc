<?php 


/**
 * Callback to demonstrate the use of Services Search Node Resource
 */
function drupanium_debug_search_node_page($form) {
  $form = array();
  
  $form['keys'] = array(
    '#type' => 'textfield',
    '#title' => t("Search words:"),
  );
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t("Search"),
    '#submit' => array("drupanium_debug_search_node_page_submit"),
  );
    
  return $form;
}

/**
 * Submit callback to search keys
 * 
 * @see drupanium_debug_search_node_page()
 */
function drupanium_debug_search_node_page_submit(&$form, &$form_state) {
  $keys = $form_state['values']['keys'];
    
  drupal_goto("drupanium/search_node/" . $keys);
}

/**
 * Callback to demonstrate the use of Services Search Node Resource Results
 * 
 * @param $keys string the words to search for
 */
function drupanium_debug_search_node_page_results($keys) {
  drupal_set_title(t("Searching for ") . $keys);
  
  $output = "";
  
  // Get the URI
  $uri = variable_get("drupanium_search_node") . "?keys=" . $keys;
  
  // Print the URI to the screen
  drupal_set_message("URI is: " . $uri);
  
  // Get the file
  $response = file_get_contents($uri);
  
  // Decode the response
  $elements = drupal_json_decode($response);
  
  // Print the elements using devel
  dsm($elements);
  
  // Loop trought the elements array
  foreach($elements as $element) {
    
    // Build the array $data with the element's title
    $data[] = $element['title'];
  }
  
  // Output the list
  $output .= theme("item_list", array('items' => $data));
  
  return $output;  
}