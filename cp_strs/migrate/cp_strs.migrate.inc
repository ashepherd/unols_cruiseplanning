<?php

function cp_strs_migrate_api() {
  $api = array(
    'api' => 2,
  );
  return $api;
}

function _cp_strs_migrate($cruise, $form_values){
  
  $migration = Migration::getInstance('STRSCruise');
  if( $migration ){
    $migration->setCruise($cruise, $form_values);
    $status = $migration->processImport(array());
  }
  
  $migration = Migration::getInstance('STRSCruiseFunding');
  if( $migration ){
    $migration->setCruise($cruise, $form_values);
    $status = $migration->processImport(array());    
  }
}






//getMachineName = STRSCruise
class STRSCruiseMigration extends Migration {
  public function __construct(array $arguments) {
    $this->arguments = $arguments;

    parent::__construct();
    $this->description = t('Import UNOLS STRS schedule.');
    
    $this->destination = new MigrateDestinationNode('cruise');
    $this->map = new MigrateSQLMap($this->machineName,
      array('strs_cruise_id' => array(
              'type' => 'varchar',
              'schedule_id' => 'varchar',
              'length' => 255,
              'not null' => TRUE,
              'description' => 'UNOLS STRS Cruise ID',
             )
      ),
      MigrateDestinationNode::getKeySchema()
    );
    
    
    
  }
  
  public function setCruise($cruise, $form_values){
    
    $this->source = new MigrateSourceSTRSCruise($cruise, $form_values);
    
    $this->addFieldMapping('field_unols_schedule_id', 'strs_cruise_id');
    $this->addSimpleMappings(array('title'));
    $this->addFieldMapping('group_group', 'group');
    $this->addFieldMapping('field_ship', 'ship');
  }
  
  public function prepareRow($row) { 
    //do something
  }
}

class MigrateSourceSTRSCruise extends MigrateSource {

  protected $fields = array();
  
  public function __construct($cruise, array $form_values = array(), array $options = array(), array $fields = array()) {
    parent::__construct($options);
    
    $this->cruise = $cruise;
    $this->form_values = $form_values;
    
    $this->options = $options;
    $this->fields = $fields;
  }
  
  public function getNextRow() {
    $the_cruise = &drupal_static(__FUNCTION__);

    if (!isset($the_cruise)) {
      $this->currentKey = array();
      $the_cruise = new stdClass();
      $the_cruise->cruise = $this->cruise;
      $the_cruise->form = $this->form_values;
      $the_cruise->strs_cruise_id = $this->cruise['ID'];
      $the_cruise->group = 1;
      $the_cruise->title = $this->form_values['cruise_title'];
      $the_cruise->ship = (string)$this->form_values['ship'];
      $the_cruise->schedule_id = (string)$this->form_values['cruiseID'];

      return $the_cruise;
    }
    return NULL;
  }

  protected function getNextLine() {
    return $this->cruise;
  }
  
   /**
   * Return a count of all available source records.
   */
  public function computeCount() {
    if( $this->cruise ) return 1;
    return 0;
  }

  public function __toString() {
    return (string)$this->cruise['ID'];
  }
  
  public function fields() {
    $fields = array();
    
    if ($this->fields) {
      $fields = $this->fields + $fields;
    }

    return $fields;
  }

  public function performRewind() {}
}

/*
      'AncilFacilities' => t('AncilFacilities'),
      'BeginLat' => t('BeginLat'),
      'BeginLon' => t('BeginLon'),
      'BeginMarsdenGrid' => t('BeginMarsdenGrid'),
      'BeginNavyOpArea' => t('BeginNavyOpArea'),
      'ChiefScientist' => t('ChiefScientist'),
      'CoastalStates' => t('CoastalStates'),
      'CruiseAgencies' => t('CruiseAgencies'),
      'CruiseType' => t('CruiseType'),
      'DatesPending' => t('DatesPending'),
      'DemobDate' => t('DemobDate'),
      'DemobDays' => t('DemobDays'),
      'EndDate' => t('EndDate'),
      'EndLat' => t('EndLat'),
      'EndLon' => t('EndLon'),
      'EndMarsdenGrid' => t('EndMarsdenGrid'),
      'EndNavyOpArea' => t('EndNavyOpArea'),
      'EndPortID' => t('EndPortID'),
      'ID' => t('ID'),
      'MobDate' => t('MobDate'),
      'MobDays' => t('MobDays'),
      'OpAreaDescription' => t('OpAreaDescription'),
      'ScienceDays' => t('ScienceDays'),
      'StartDate' => t('StartDate'),
      'StartPortID' => t('StartPortID'),
      'StartPortNameAndLocation' => t('StartPortNameAndLocation'),
      'TransitDays' => t('TransitDays'),
      'Webpage' => t('Webpage'),
*/

class STRSCruiseFundingMigration extends Migration {
  public function __construct(array $arguments) {
    $this->arguments = $arguments;

    parent::__construct();
    $this->description = t('Import UNOLS STRS schedule - Funding');
    
    
    $this->map = new MigrateSQLMap($this->machineName,
      array('strs_cruise_id' => array(
              'type' => 'varchar',
              'schedule_id' => 'varchar',
              'length' => 255,
              'not null' => TRUE,
              'description' => 'UNOLS STRS Cruise ID',
             )
      ),
      MigrateDestinationComment::getKeySchema()
    );
    
    $this->destination = new MigrateDestinationNode('funding');
    
  }
  
  public function setCruise($cruise, $form_values){
    
    $this->source = new MigrateSourceSTRSCruiseFunding($cruise, $id, $form_values);
    
    $this->addFieldMapping('field_unols_schedule_id', 'strs_cruise_id');
    $this->addSimpleMappings(array('title'));
    $this->addFieldMapping('group_group', 'group');
    $this->addFieldMapping('field_ship', 'ship');
  }
  
  public function prepareRow($row) { 
    //do something
  }
}

class MigrateSourceSTRSCruiseFunding extends MigrateSource {

  protected $fields = array();
  
  public function __construct($cruise, $id, array $form_values = array(), array $options = array(), array $fields = array()) {
    parent::__construct($options);
    $this->funding_id = $id;
    $this->cruise = $cruise;
    $this->form_values = $form_values;
    
    $this->options = $options;
    $this->fields = $fields;
  }
  
  public function getNextRow() {
    $the_cruise = &drupal_static(__FUNCTION__);

    if (!isset($the_cruise)) {
      $this->currentKey = array();
      $the_cruise = new stdClass();
      $the_cruise->cruise = $this->cruise;
      $the_cruise->form = $this->form_values;
      $the_cruise->strs_cruise_id = $this->cruise['ID'];
      $the_cruise->{OG_AUDIENCE_FIELD} = 1;
      $the_cruise->title = $this->form_values['cruise_title'];
      $the_cruise->ship = (string)$this->form_values['ship'];
      $the_cruise->schedule_id = (string)$this->form_values['cruiseID'];

      return $the_cruise;
    }
    return NULL;
  }

  protected function getNextLine() {
    return $this->cruise;
  }
  
   /**
   * Return a count of all available source records.
   */
  public function computeCount() {
    if( $this->cruise ) return 1;
    return 0;
  }

  public function __toString() {
    return (string)$this->cruise['ID'] . 'Funding : '. $this->funding_id;
  }
  
  public function fields() {
    $fields = array();
    
    if ($this->fields) {
      $fields = $this->fields + $fields;
    }

    return $fields;
  }

  public function performRewind() {}
}