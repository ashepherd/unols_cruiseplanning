<?php

function cp_checklist_views_add_milestone_link(){
  print_r('<br/>[');
  print_r( 
    l( 'Add new Milestone','node/add/milestone',
      array('query' => array( 'destination' => 'milestones') ) 
    )  
  );
  print_r(']<br/>');
}
