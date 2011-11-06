<?php
/**
 * @file
 * drupanium_location.features.field.inc
 */

/**
 * Implements hook_field_default_fields().
 */
function drupanium_location_field_default_fields() {
  $fields = array();

  // Exported field: 'node-location-field_location'
  $fields['node-location-field_location'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_location',
      'foreign keys' => array(),
      'indexes' => array(
        'lat' => array(
          0 => 'lat',
        ),
        'lng' => array(
          0 => 'lng',
        ),
      ),
      'module' => 'geolocation',
      'settings' => array(),
      'translatable' => '0',
      'type' => 'geolocation_latlng',
    ),
    'field_instance' => array(
      'bundle' => 'location',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'module' => 'geolocation_googlemaps',
          'settings' => array(
            'map_dimensions' => '300x300',
            'map_imageformat' => 'png8',
            'map_maptype' => 'roadmap',
            'map_zoomlevel' => '15',
            'marker_icon' => '',
          ),
          'type' => 'geolocation_googlemaps_static',
          'weight' => '0',
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'field_location',
      'label' => 'Location',
      'required' => 1,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'geolocation_googlemaps',
        'settings' => array(
          'scrollwheel' => 0,
        ),
        'type' => 'geolocation_googlemap',
        'weight' => '-4',
      ),
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Location');

  return $fields;
}
