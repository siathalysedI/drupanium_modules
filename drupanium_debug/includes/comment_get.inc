<?php 


/**
 * Callback to demonstrate the use of Services Search Node Resource
 */
function drupanium_debug_comment_get_page($form) {
  $form = array();
  
  $form['cid'] = array(
    '#type' => 'textfield',
    '#title' => t("Comment CID:"),
  );
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t("Get comment"),
    '#submit' => array("drupanium_debug_comment_get_page_submit"),
  );
    
  return $form;
}

/**
 * Submit callback to search keys
 * 
 * @see drupanium_debug_search_node_page()
 */
function drupanium_debug_comment_get_page_submit(&$form, &$form_state) {
  $cid = $form_state['values']['cid'];
    
  drupal_goto("drupanium/comment_get/" . $cid);
}

/**
 * Callback to demonstrate the use of Services Search Node Resource Results
 * 
 * @param $keys string the words to search for
 */
function drupanium_debug_comment_get_page_results($cid) {
  drupal_set_title(t("Getting comment with cid: ") . $cid);
  
  $output = "";
  
  // Get the URI
  $uri = variable_get("drupanium_comment") . $cid . '.json';
  
  // Print the URI to the screen
  drupal_set_message("URI is: " . $uri);
  
  // Get the file
  $response = file_get_contents($uri);
  
  // Decode the response
  $elements = drupal_json_decode($response);
  
  // Print the elements using devel
  dsm($elements);
  
  $data[] = "Subject: " . $elements['subject'];
  $data[] = "CID: " . $elements['cid'];
  $data[] = "NID: " . $elements['nid'];
  
  // Output the list
  $output .= theme("item_list", array('items' => $data));
  
  return $output;  
}