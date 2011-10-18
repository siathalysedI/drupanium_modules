<?php 


/**
 * Callback to demonstrate the use of Services Search Node Resource
 */
function drupanium_debug_node_get_page($form) {
  $form = array();
  
  $form['nid'] = array(
    '#type' => 'textfield',
    '#title' => t("Node NID:"),
  );
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t("Get node"),
    '#submit' => array("drupanium_debug_node_get_page_submit"),
  );
    
  return $form;
}

/**
 * Submit callback to search keys
 * 
 * @see drupanium_debug_search_node_page()
 */
function drupanium_debug_node_get_page_submit(&$form, &$form_state) {
  $nid = $form_state['values']['nid'];
    
  drupal_goto("drupanium/node_get/" . $nid);
}

/**
 * Callback to demonstrate the use of Services Search Node Resource Results
 * 
 * @param $keys string the words to search for
 */
function drupanium_debug_node_get_page_results($nid) {
  drupal_set_title(t("Getting node with nid: ") . $nid);
  
  $output = "";
  
  // Get the URI
  $uri = variable_get("drupanium_node") . $nid . '.json';
  
  // Print the URI to the screen
  drupal_set_message("URI is: " . $uri);
  
  // Get the file
  $response = file_get_contents($uri);
  
  // Decode the response
  $elements = drupal_json_decode($response);
  
  // Print the elements using devel
  dsm($elements);
  
  $data[] = "Title: " . $elements['title'];
  $data[] = "NID: " . $elements['nid'];
  
  // Output the list
  $output .= theme("item_list", array('items' => $data));
  
  return $output;  
}