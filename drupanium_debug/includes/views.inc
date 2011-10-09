<?php 

/**
 * Callback to demonstrate the use of a views resource in a REST Server
 */
function drupanium_debug_views_page() {
  
  $output = "";
  
  // Get the URI
  // MODIFY THIS TO YOUR NEEDS
  $uri = variable_get("drupanium_views");
  
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
