<?php



function cp_utils_views_my_cruises_header(){
  if( user_is_anonymous() ){
    drupal_goto('/cruises');
    return;
  }
  print_r('[');
  print_r( l( 'New Cruise Plan','node/add/cruise',
        array('destination' => '/my-cruises') 
      )  
  );
  print_r(']&nbsp;&nbsp;&nbsp;[');
  print_r( l( 'Import UNOLS Ship Time Request','unols/schedule' )  );
  print_r(']<br/>');
}
function cp_utils_views_next_section($path){
  $item = menu_get_item();
  if( !empty($item) && $item['path'] != 'node/%'){
    $menu = cp_utils_local_tasks($path);
    print drupal_render(drupal_get_form('cp_utils_next_section_form', $menu));
  }
}

function cp_utils_views_add_funding_link($cruise, $destination){
  if( !cp_status_is_completed($cruise) ){
    print_r('<br/>[');
    print_r( 
      l( 'New funding source','node/add/funding',
        array('query' => array( OG_AUDIENCE_FIELD => $cruise, 'destination' => $destination) ) 
      ) 
    );
    print_r(']<br/>');
  }
}

function cp_utils_views_add_party_member_link($cruise, $destination){
  if( !cp_status_is_completed($cruise) ){
    print_r('<br/>[');
    print_r( 
      l( 'New cruise party member','node/add/cruise-party-member',
        array('query' => array( OG_AUDIENCE_FIELD => $cruise, 'destination' => $destination) ) 
      )  
    );
    print_r(']<br/>');
  }
}

function cp_utils_views_add_station_link($cruise, $destination){
  if( !cp_status_is_completed($cruise) ){
    print_r('<br/>[');
    print_r( 
      l( 'New cruise station','node/add/cruise-station',
        array('query' => array( OG_AUDIENCE_FIELD => $cruise, 'destination' => $destination) ) 
      )  
    );
    print_r(']<br/>');
  }
}

function cp_utils_views_cruise_editors_link($cruise){
  if( !cp_status_is_completed($cruise) && cp_utils_is_cruise_admin($cruise) ){
    if(module_exists('cp_invite') ){
      print_r(' [<a href="/node/'.$cruise.'/invitations">Invites</a>]');
    } else {
      print_r('[<a href="/node/'.$cruise.'/editors">Add</a>]');
    }
    print_r('<br/>');
  }
}