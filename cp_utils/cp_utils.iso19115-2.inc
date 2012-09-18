<?php


/*
 * NOT COMPLETED 8/30/2012
 */
function cp_utils_cruise_metadata_deliver($build){
  if (!$build['#cruise']) {
    return drupal_not_found();
  }
  $cruise = $build['#cruise'];
  $cruise_content = _cp_utils_get_cruise_content($cruise->nid);
  if (!$cruise_content || empty($cruise_content)) {
    return drupal_not_found();
  }
  foreach ($cruise_content as $content) {
    if ($content->node_type == 'cruise_party_member') {
      
    } else if ($content->node_type == 'funding') {
      
    } //...
  }
  
  _cp_utils_print_array($cruise);
  
  $cruise_content = _cp_utils_get_cruise_content($cruise->nid);
  
  
  //*
  $lang = 'eng; USA';
  $charset = 'utf8';
  $heirarchy_level = 'fieldSession';
  
  $contact = new stdClass();
  $contact_name = 'Doug Russell'; //OPS MANAGER
  $contact_org = 'University of Washington'; //ORG NAME
  $contact_position = 'Bill Rall'; //OPS LEADER
  
  $metadata_date = format_date($node->changed, 'custom', 'Y-m-d\TH:i:s\Z');
  $cruiseID = $cruise->field_cruise_id['und']['0']['value'];

  drupal_add_http_header('Content-type', 'text/xml');
  
  $output = '<?xml version="1.0" encoding="UTF-8"?>'. "\n";
  $output .= '<gmd:MD_Metadata ' . "\n";
  $output .= '  xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"' . "\n";
  $output .= '  xmlns:xlink="http://www.w3.org/1999/xlink" ' . "\n";
  $output .= '  xmlns:gco="http://www.isotc211.org/2005/gco" ' . "\n";
  $output .= '  xmlns:gmd="http://www.isotc211.org/2005/gmd" ' . "\n";
  $output .= '  xmlns:gmx="http://www.isotc211.org/2005/gmx" ' . "\n";
  $output .= '  xmlns:gml="http://www.opengis.net/gml/3.2" ' . "\n";
  $output .= '  xmlns:gss="http://www.isotc211.org/2005/gss" ' . "\n";
  $output .= '  xmlns:gts="http://www.isotc211.org/2005/gts" ' . "\n";
  $output .= '  xmlns:gsr="http://www.isotc211.org/2005/gsr" ' . "\n";
  $output .= '  xmlns:gmi="http://www.isotc211.org/2005/gmi" ' . "\n";
  
  
  $output .= '  xsi:schemaLocation="http://www.isotc211.org/2005/gmd http://schemas.opengis.net/csw/2.0.2/profiles/apiso/1.0.0/apiso.xsd">' . "\n";
  $output .= '  <gmd:fileIdentifier>' . "\n";
  $output .= '    <gco:CharacterString>' . $cruise->field_cruise_id['und']['0']['value'] . '</gco:CharacterString>' . "\n";
  $output .= '  </gmd:fileIdentifier>' . "\n";
  $output .= '  <gmd:language>' . "\n";
  $output .= '    <gco:CharacterString>'.$lang. '</gco:CharacterString>' . "\n";
  $output .= '  </gmd:language>' . "\n";
  $output .= '  <gmd:characterSet>' . "\n";
  $output .= '    <gmd:MD_CharacterSetCode ' . "\n";
  $output .= '      codeList="http://standards.iso.org/ittf/PubliclyAvailableStandards/ISO_19139_Schemas/resources/Codelist/gmxCodelists.xml#MD_CharacterSetCode" ' . "\n";
  $output .= '      codeListValue="'.$charset.'">'.$charset.'</gmd:MD_CharacterSetCode>' . "\n";
  $output .= '  </gmd:characterSet>' . "\n";
  $output .= '  <gmd:hierarchyLevel>' . "\n";
  $output .= '    <gmd:MD_ScopeCode ' . "\n";
  $output .= '      codeList="http://standards.iso.org/ittf/PubliclyAvailableStandards/ISO_19139_Schemas/resources/Codelist/gmxCodelists.xml#MD_ScopeCode" ' . "\n";
  $output .= '      codeListValue="'.$heirarchy_level.'">'.$heirarchy_level.'</gmd:MD_ScopeCode>' . "\n";
  $output .= '  </gmd:hierarchyLevel>' . "\n";
  $output .= '  <gmd:hierarchyLevelName>' . "\n";
  $output .= '    <gco:CharacterString>cruise level metadata</gco:CharacterString>' . "\n";
  $output .= '  </gmd:hierarchyLevelName>' . "\n";
  
  
  $output .= '  <!-- Metadata point of contact - Point of contact for the metadata record, e.g. for users to report errors, updates to metadata, etc. -->' . "\n";
  $output .= '  <gmd:contact>' . "\n";
  $output .= '    <gmd:CI_ResponsibleParty>' . "\n";
  $output .= '      <gmd:individualName>';
  
  if( $contact && $contact->personURI){
    //href="http://get.rvdata.us/voc/person/100001
    //Data Manager
    $output = '<gmx:Anchor xlink:'.$contact->personURI.'" xlink:actuate="onRequest">'.$contact->personName.'</gmx:Anchor>';
  }
  
  $output = '</gmd:individualName>' . "\n";
  $output .= '      <gmd:organisationName>';
  
  if( $contact && $contact->orgURI){
    //http://get.rvdata.us/voc/organization/us.rvdata
    $output = '<gmx:Anchor xlink:href="'.$contact->orgURI.'" xlink:actuate="onRequest">Rolling Deck to Repository (R2R) Program</gmx:Anchor>';
  }
  
  $output = '</gmd:organisationName>' . "\n";
  
  if( $contact && $contact->position){
    $output .= '      <gmd:positionName><gco:CharacterString>'.$contact->position.'</gco:CharacterString></gmd:positionName>' . "\n";
  }
  
  $output .= '      <gmd:contactInfo>' . "\n";
  $output .= '        <gmd:CI_Contact>' . "\n";
  
  if ($contact ) {
    if( $contact->voice || $contact->fax ){
      $output .= '          <gmd:phone>' . "\n";
      $output .= '            <gmd:CI_Telephone>' . "\n";
      if( $contact->voice ){
        $output .= '              <gmd:voice>' . "\n";
        $output .= '                <gco:CharacterString>'. $contact->voice. '</gco:CharacterString>' . "\n";
        $output .= '              </gmd:voice>' . "\n";
      }
      if( $contact->fax ){
        $output .= '              <gmd:facsimile>' . "\n";
        $output .= '                <gco:CharacterString><?php print $fields["metadata_contact_facsimile"]; ?></gco:CharacterString>' . "\n";
        $output .= '              </gmd:facsimile>' . "\n";
      }
      $output .= '            </gmd:CI_Telephone>' . "\n";
      $output .= '          </gmd:phone>' . "\n";
    }
    
    if( $contact->address ){
      $output .= '          <gmd:address>' . "\n";
      $output .= '            <gmd:CI_Address>' . "\n";
      if( $contact->mailing_address ){
        $output .= '              <gmd:deliveryPoint>' . "\n";
        $output .= '                <gco:CharacterString><?php print $fields["metadata_contact_deliveryPoint"]; ?></gco:CharacterString>' . "\n";
        $output .= '              </gmd:deliveryPoint>' . "\n";
      }
      if( $contact->city ){
        $output .= '              <gmd:city>' . "\n";
        $output .= '                <gco:CharacterString><?php print $fields["metadata_contact_city"]; ?></gco:CharacterString>' . "\n";
        $output .= '              </gmd:city>' . "\n";
      }
      if( $contact->state ){
        $output .= '              <gmd:administrativeArea>' . "\n";
        $output .= '                <gco:CharacterString><?php print $fields["metadata_contact_administrativeArea"]; ?></gco:CharacterString>' . "\n";
        $output .= '              </gmd:administrativeArea>' . "\n";
      }
      if( $contact->postal_code ){
        $output .= '              <gmd:postalCode>' . "\n";
        $output .= '                <gco:CharacterString><?php print $fields["metadata_contact_postalCode"]; ?></gco:CharacterString>' . "\n";
        $output .= '              </gmd:postalCode>' . "\n";
      }
      if( $contact->country ){
        $output .= '              <gmd:country>' . "\n";
        $output .= '                <gco:CharacterString><?php print $fields["metadata_contact_country"]; ?></gco:CharacterString>' . "\n";
        $output .= '              </gmd:country>' . "\n";
      }
    }
    if( $contact->email ){
      $output .= '              <gmd:electronicMailAddress>' . "\n";
      $output .= '                <gco:CharacterString><?php print $fields["metadata_contact_electronicMailAddress"]; ?></gco:CharacterString>' . "\n";
      $output .= '              </gmd:electronicMailAddress>' . "\n";
      $output .= '            </gmd:CI_Address>' . "\n";
      $output .= '          </gmd:address>' . "\n";
    }
    
    /* NOT IMPLEMENTED */
    $output .= '          <?php if ($fields["metadata_contact_onlineResource_URL"]) {?>' . "\n";
    $output .= '          <gmd:onlineResource>' . "\n";
    $output .= '            <gmd:CI_OnlineResource>' . "\n";
    $output .= '              <gmd:linkage>' . "\n";
    $output .= '                <gmd:URL><?php print $fields["metadata_contact_onlineResource_URL"]; ?></gmd:URL>' . "\n";
    $output .= '              </gmd:linkage>' . "\n";
    $output .= '              <gmd:protocol>' . "\n";
    $output .= '                <gco:CharacterString>http</gco:CharacterString>' . "\n";
    $output .= '              </gmd:protocol>' . "\n";
    $output .= '              <?php if ($fields["metadata_contact_onlineResource_description"]) {?>' . "\n";
    $output .= '              <gmd:description>' . "\n";
    $output .= '                <gco:CharacterString><?php print $fields["metadata_contact_onlineResource_description"]; ?></gco:CharacterString>' . "\n";
    $output .= '              </gmd:description>' . "\n";
    $output .= '              <?php } ?>' . "\n";
    $output .= '            </gmd:CI_OnlineResource>' . "\n";
    $output .= '          </gmd:onlineResource>' . "\n";
    
    $output .= '          <?php if ($fields["metadata_contact_hoursOfService"]) {?>' . "\n";
    $output .= '          <gmd:hoursOfService>' . "\n";
    $output .= '            <gco:CharacterString><?php print $fields["metadata_contact_hoursOfService"]; ?></gco:CharacterString>' . "\n";
    $output .= '          </gmd:hoursOfService>' . "\n";
    $output .= '          <?php } ?>' . "\n";
    $output .= '          <?php if ($fields["metadata_contact_contactInstructions"]) {?>' . "\n";
    $output .= '          <gmd:contactInstructions>' . "\n";
    $output .= '            <gco:CharacterString><?php print $fields["metadata_contact_contactInstructions"]; ?></gco:CharacterString>' . "\n";
    $output .= '          </gmd:contactInstructions>' . "\n";
    $output .= '          <?php } ?>  ' . "\n";
    /* */
  }
  $output .= '        </gmd:CI_Contact>' . "\n";
  $output .= '      </gmd:contactInfo>' . "\n";
  $output .= '      <gmd:role>' . "\n";
  $output .= '        <gmd:CI_RoleCode ' . "\n";
  $output .= '          codeList="http://standards.iso.org/ittf/PubliclyAvailableStandards/ISO_19139_Schemas/resources/Codelist/gmxCodelists.xml#CI_RoleCode" ' . "\n";
  $output .= '          codeListValue="pointOfContact">point of contact</gmd:CI_RoleCode>' . "\n";
  $output .= '      </gmd:role>' . "\n";
  $output .= '    </gmd:CI_ResponsibleParty>' . "\n";
  $output .= '  </gmd:contact>' . "\n";
  
  //END OF CONTACT @ OPERATOR
  
  //Date format: 2012-07-03T06:30:08Z
  $output .= '  <gmd:dateStamp>' . "\n";
  $output .= '    <gco:DateTime>'.$metadata_date.'</gco:DateTime>' . "\n";
  $output .= '  </gmd:dateStamp>' . "\n";
  
  
  $output .= '  <gmd:metadataStandardName>' . "\n";
  $output .= '    <gco:CharacterString>ISO 19115-2 Geographic Information - Metadata Part 2 Extensions for imagery and gridded data</gco:CharacterString>' . "\n";
  $output .= '  </gmd:metadataStandardName>' . "\n";
  $output .= '  <gmd:metadataStandardVersion>' . "\n";
  $output .= '    <gco:CharacterString>ISO 19115-2:2009(E)</gco:CharacterString>' . "\n";
  $output .= '  </gmd:metadataStandardVersion>' . "\n";
  
  /* NOT IMPLEMENTED */
  $output .= '  <gmd:dataSetURI>' . "\n";
  $output .= '    <gco:CharacterString>xxxxx</gco:CharacterString>' . "\n";
  $output .= '  </gmd:dataSetURI>' . "\n";
  /* */
  
  $output .= '  <!-- **************** -->' . "\n";
  $output .= '  <gmd:identificationInfo>' . "\n";
  $output .= '    <gmd:MD_DataIdentification>' . "\n";
  $output .= '      <gmd:citation>' . "\n";
  $output .= '        <gmd:CI_Citation>' . "\n";
  $output .= '          <gmd:title>' . "\n";
  $output .= '            <gco:CharacterString>'.$cruiseID.'</gco:CharacterString>' . "\n";
  $output .= '          </gmd:title>' . "\n";
  $output .= '          <gmd:date>' . "\n";
  $output .= '            <gmd:CI_Date>' . "\n";
  $output .= '              <gmd:date>' . "\n";
  $output .= '                <gco:DateTime>'.$metadata_date.'</gco:DateTime>' . "\n";
  $output .= '              </gmd:date>' . "\n";
  $output .= '              <gmd:dateType>' . "\n";
  $output .= '                <gmd:CI_DateTypeCode ' . "\n";
  $output .= '                  codeList="http://standards.iso.org/ittf/PubliclyAvailableStandards/ISO_19139_Schemas/resources/Codelist/gmxCodelists.xml#CI_DateTypeCode" ' . "\n";
  $output .= '                  codeListValue="creation">creation</gmd:CI_DateTypeCode>' . "\n";
  $output .= '              </gmd:dateType>' . "\n";
  $output .= '            </gmd:CI_Date>' . "\n";
  $output .= '          </gmd:date>' . "\n";
  
  $output .= '          <?php if ($fields["citation_identifier"]) {?>' . "\n";
  $output .= '          <gmd:identifier>' . "\n";
  $output .= '            <gmd:MD_Identifier>' . "\n";
  $output .= '              <gmd:code>' . "\n";
  $output .= '                <gco:CharacterString><?php print $fields["citation_identifier"]; ?></gco:CharacterString>' . "\n";
  $output .= '              </gmd:code>' . "\n";
  $output .= '            </gmd:MD_Identifier>' . "\n";
  $output .= '          </gmd:identifier>' . "\n";
  $output .= '          <?php } ?>' . "\n";
  
  $output .= '          <!-- (M) Resource Ciatation (Responsible Party) - The citation attribute provides information for citing the described resource. Citation is defined by Webster as "an act of quoting". The precise semantics of what an identification/citation is supposed to be are not very well articulated in ISO19115. For USGIN purposes, this should be viewed as information to identify the intellectual origin (or property) of the content in the described resource, along the lines of a citation in a scientific journal. -->' . "\n";
  $output .= '          <gmd:citedResponsibleParty>' . "\n";
  $output .= '            <gmd:CI_ResponsibleParty>' . "\n";
  $output .= '              <?php if ($fields["citation_contact_individualName"]) {?>' . "\n";
  $output .= '              <gmd:individualName>' . "\n";
  $output .= '                <gco:CharacterString><?php print $fields["citation_contact_individualName"]; ?></gco:CharacterString>' . "\n";
  $output .= '              </gmd:individualName>' . "\n";
  $output .= '              <?php } ?>' . "\n";
  $output .= '              <?php if ($fields["citation_contact_organisationName"]) {?>' . "\n";
  $output .= '              <gmd:organisationName>' . "\n";
  $output .= '                <gco:CharacterString><?php print $fields["citation_contact_organisationName"]; ?></gco:CharacterString>' . "\n";
  $output .= '              </gmd:organisationName>' . "\n";
  $output .= '              <?php if ($fields["citation_contact_positionName"]) {?>' . "\n";
  $output .= '              <?php } ?>' . "\n";
  $output .= '              <gmd:positionName>' . "\n";
  $output .= '                <gco:CharacterString><?php print $fields["citation_contact_positionName"]; ?></gco:CharacterString>' . "\n";
  $output .= '              </gmd:positionName>' . "\n";
  $output .= '              <?php } ?>' . "\n";
  $output .= '              <?php if (($fields["citation_contact_voice"]) || ($fields["citation_contact_facsimile"]) || ($fields["citation_contact_deliveryPoint"]) || ($fields["citation_contact_electronicMailAddress"])) {?>' . "\n";
  $output .= '              <gmd:contactInfo>' . "\n";
  $output .= '                <gmd:CI_Contact>' . "\n";
  $output .= '                  <?php if (($fields["citation_contact_voice"]) || ($fields["citation_contact_facsimile"])) {?>' . "\n";
  $output .= '                  <gmd:phone>' . "\n";
  $output .= '                    <gmd:CI_Telephone>' . "\n";
  $output .= '                      <?php if ($fields["citation_contact_voice"]) {?>' . "\n";
  $output .= '                      <gmd:voice>' . "\n";
  $output .= '                        <gco:CharacterString><?php print $fields["citation_contact_voice"]; ?></gco:CharacterString>' . "\n";
  $output .= '                      </gmd:voice>' . "\n";
  $output .= '                      <?php } ?>' . "\n";
  $output .= '                      <?php if ($fields["citation_contact_facsimile"]) {?>' . "\n";
  $output .= '                      <gmd:facsimile>' . "\n";
  $output .= '                        <gco:CharacterString><?php print $fields["citation_contact_facsimile"]; ?></gco:CharacterString>' . "\n";
  $output .= '                      </gmd:facsimile>' . "\n";
  $output .= '                      <?php } ?>' . "\n";
  $output .= '                    </gmd:CI_Telephone>' . "\n";
  $output .= '                  </gmd:phone>' . "\n";
  $output .= '                  <?php } ?>' . "\n";
  $output .= '                  <?php if (($fields["citation_contact_deliveryPoint"]) || ($fields["citation_contact_electronicMailAddress"])) {?>' . "\n";
  $output .= '                  <gmd:address>' . "\n";
  $output .= '                    <gmd:CI_Address>' . "\n";
  $output .= '                      <?php if ($fields["citation_contact_deliveryPoint"]) {?>' . "\n";
  $output .= '                      <gmd:deliveryPoint>' . "\n";
  $output .= '                        <gco:CharacterString><?php print $fields["citation_contact_deliveryPoint"]; ?></gco:CharacterString>' . "\n";
  $output .= '                      </gmd:deliveryPoint>' . "\n";
  $output .= '                      <gmd:city>' . "\n";
  $output .= '                        <gco:CharacterString><?php print $fields["citation_contact_city"]; ?></gco:CharacterString>' . "\n";
  $output .= '                      </gmd:city>' . "\n";
  $output .= '                      <gmd:administrativeArea>' . "\n";
  $output .= '                        <gco:CharacterString><?php print $fields["citation_contact_administrativeArea"]; ?></gco:CharacterString>' . "\n";
  $output .= '                      </gmd:administrativeArea>' . "\n";
  $output .= '                      <gmd:postalCode>' . "\n";
  $output .= '                        <gco:CharacterString><?php print $fields["citation_contact_postalCode"]; ?></gco:CharacterString>' . "\n";
  $output .= '                      </gmd:postalCode>' . "\n";
  $output .= '                      <gmd:country>' . "\n";
  $output .= '                        <gco:CharacterString><?php print $fields["citation_contact_country"]; ?></gco:CharacterString>' . "\n";
  $output .= '                      </gmd:country>' . "\n";
  $output .= '                      <?php } ?>' . "\n";
  $output .= '                      <?php if ($fields["citation_contact_electronicMailAddress"]) {?>' . "\n";
  $output .= '                      <gmd:electronicMailAddress>' . "\n";
  $output .= '                        <gco:CharacterString><?php print $fields["citation_contact_electronicMailAddress"]; ?></gco:CharacterString>' . "\n";
  $output .= '                      </gmd:electronicMailAddress>' . "\n";
  $output .= '                      <?php } ?>' . "\n";
  $output .= '                    </gmd:CI_Address>' . "\n";
  $output .= '                  </gmd:address>' . "\n";
  $output .= '                  <?php } ?>' . "\n";
  $output .= '                  <?php if ($fields["citation_contact_onlineResource_URL"]) {?>' . "\n";
  $output .= '                  <gmd:onlineResource>' . "\n";
  $output .= '                    <gmd:CI_OnlineResource>' . "\n";
  $output .= '                      <gmd:linkage>' . "\n";
  $output .= '                        <gmd:URL><?php print $fields["citation_contact_onlineResource_URL"]; ?></gmd:URL>' . "\n";
  $output .= '                      </gmd:linkage>' . "\n";
  $output .= '                      <gmd:protocol>' . "\n";
  $output .= '                        <gco:CharacterString>http</gco:CharacterString>' . "\n";
  $output .= '                      </gmd:protocol>' . "\n";
  $output .= '                      <?php if ($fields["citation_contact_onlineResource_description"]) {?>' . "\n";
  $output .= '                      <gmd:description>' . "\n";
  $output .= '                        <gco:CharacterString><?php print $fields["citation_contact_onlineResource_description"]; ?></gco:CharacterString>' . "\n";
  $output .= '                      </gmd:description>' . "\n";
  $output .= '                      <?php } ?>' . "\n";
  $output .= '                    </gmd:CI_OnlineResource>' . "\n";
  $output .= '                  </gmd:onlineResource>' . "\n";
  $output .= '                  <?php } ?>' . "\n";
  $output .= '                  <?php if ($fields["citation_contact_hoursOfService"]) {?>' . "\n";
  $output .= '                  <gmd:hoursOfService>' . "\n";
  $output .= '                    <gco:CharacterString><?php print $fields["citation_contact_hoursOfService"]; ?></gco:CharacterString>' . "\n";
  $output .= '                  </gmd:hoursOfService>' . "\n";
  $output .= '                  <?php } ?>' . "\n";
  $output .= '                  <?php if ($fields["citation_contact_contactInstructions"]) {?>' . "\n";
  $output .= '                  <gmd:contactInstructions>' . "\n";
  $output .= '                    <gco:CharacterString><?php print $fields["citation_contact_contactInstructions"]; ?></gco:CharacterString>' . "\n";
  $output .= '                  </gmd:contactInstructions>' . "\n";
  $output .= '                  <?php } ?>' . "\n";
  $output .= '                </gmd:CI_Contact>' . "\n";
  $output .= '              </gmd:contactInfo>' . "\n";
  $output .= '              <?php } ?>' . "\n";
  $output .= '              <gmd:role>' . "\n";
  $output .= '                <gmd:CI_RoleCode ' . "\n";
  $output .= '                  codeList="http://standards.iso.org/ittf/PubliclyAvailableStandards/ISO_19139_Schemas/resources/Codelist/gmxCodelists.xml#CI_RoleCode" ' . "\n";
  $output .= '                  codeListValue="author">author</gmd:CI_RoleCode>' . "\n";
  $output .= '              </gmd:role>' . "\n";
  $output .= '            </gmd:CI_ResponsibleParty>' . "\n";
  $output .= '          </gmd:citedResponsibleParty>' . "\n";
  $output .= '          <?php if ($fields["citation_otherCitationDetails"]) {?>' . "\n";
  $output .= '          <gmd:otherCitationDetails>' . "\n";
  $output .= '            <gco:CharacterString><?php print $fields["citation_otherCitationDetails"]; ?></gco:CharacterString>' . "\n";
  $output .= '          </gmd:otherCitationDetails>' . "\n";
  $output .= '          <?php } ?>' . "\n";
  $output .= '        </gmd:CI_Citation>' . "\n";
  $output .= '      </gmd:citation>' . "\n";
  $output .= '      <gmd:abstract>' . "\n";
  $output .= '        <gco:CharacterString><?php print $fields["resource_abstract"]; ?></gco:CharacterString>' . "\n";
  $output .= '      </gmd:abstract>' . "\n";
  $output .= '      <gmd:status>' . "\n";
  $output .= '        <gmd:MD_ProgressCode ' . "\n";
  $output .= '          codeList="http://standards.iso.org/ittf/PubliclyAvailableStandards/ISO_19139_Schemas/resources/Codelist/gmxCodelists.xml#MD_ProgressCode" ' . "\n";
  $output .= '          codeListValue="<?php print $fields["resource_status_progressCode"]; ?>"><?php print $fields["resource_status_progressCode"]; ?></gmd:MD_ProgressCode>' . "\n";
  $output .= '      </gmd:status>' . "\n";
  $output .= '      <?php if (($fields["resource_contact_individualName"]) || ($fields["resource_contact_organisationName"]) || ($fields["resource_contact_positionName"])) {?>' . "\n";
  $output .= '      <!-- (C) Resource point of contact (access contact) - CI_ResponsibleParty element here would contain information for point of contact to access the resource. This information is mandatory for physical resources such as core, cuttings, samples, manuscripts. -->' . "\n";
  $output .= '      <gmd:pointOfContact>' . "\n";
  $output .= '        <gmd:CI_ResponsibleParty>' . "\n";
  $output .= '          <?php if ($fields["resource_contact_individualName"]) {?>' . "\n";
  $output .= '          <gmd:individualName>' . "\n";
  $output .= '            <gco:CharacterString><?php print $fields["resource_contact_individualName"]; ?></gco:CharacterString>' . "\n";
  $output .= '          </gmd:individualName>' . "\n";
  $output .= '          <?php } ?>' . "\n";
  $output .= '          <?php if ($fields["resource_contact_organisationName"]) {?>' . "\n";
  $output .= '          <gmd:organisationName>' . "\n";
  $output .= '            <gco:CharacterString><?php print $fields["resource_contact_organisationName"]; ?></gco:CharacterString>' . "\n";
  $output .= '          </gmd:organisationName>' . "\n";
  $output .= '          <?php } ?>' . "\n";
  $output .= '          <?php if ($fields["resource_contact_positionName"]) {?>' . "\n";
  $output .= '          <gmd:positionName>' . "\n";
  $output .= '            <gco:CharacterString><?php print $fields["resource_contact_positionName"]; ?></gco:CharacterString>' . "\n";
  $output .= '          </gmd:positionName>' . "\n";
  $output .= '          <?php } ?>' . "\n";
  $output .= '          <?php if (($fields["resource_contact_voice"]) || ($fields["resource_contact_facsimile"]) || ($fields["resource_contact_deliveryPoint"]) || ($fields["resource_contact_electronicMailAddress"])) {?>' . "\n";
  $output .= '          <gmd:contactInfo>' . "\n";
  $output .= '            <gmd:CI_Contact>' . "\n";
  $output .= '              <?php if (($fields["resource_contact_voice"]) || ($fields["resource_contact_facsimile"])) {?>' . "\n";
  $output .= '              <gmd:phone>' . "\n";
  $output .= '                <gmd:CI_Telephone>' . "\n";
  $output .= '                  <?php if ($fields["resource_contact_voice"]) {?>' . "\n";
  $output .= '                  <gmd:voice>' . "\n";
  $output .= '                    <gco:CharacterString><?php print $fields["resource_contact_voice"]; ?></gco:CharacterString>' . "\n";
  $output .= '                  </gmd:voice>' . "\n";
  $output .= '                  <?php } ?>' . "\n";
  $output .= '                  <?php if ($fields["resource_contact_facsimile"]) {?>' . "\n";
  $output .= '                  <gmd:facsimile>' . "\n";
  $output .= '                    <gco:CharacterString><?php print $fields["resource_contact_facsimile"]; ?></gco:CharacterString>' . "\n";
  $output .= '                  </gmd:facsimile>' . "\n";
  $output .= '                  <?php } ?>' . "\n";
  $output .= '                </gmd:CI_Telephone>' . "\n";
  $output .= '              </gmd:phone>' . "\n";
  $output .= '              <?php } ?>' . "\n";
  $output .= '              <?php if (($fields["resource_contact_deliveryPoint"]) || ($fields["resource_contact_electronicMailAddress"])) {?>' . "\n";
  $output .= '              <gmd:address>' . "\n";
  $output .= '                <gmd:CI_Address>' . "\n";
  $output .= '                  <?php if ($fields["resource_contact_deliveryPoint"]) {?>' . "\n";
  $output .= '                  <gmd:deliveryPoint>' . "\n";
  $output .= '                    <gco:CharacterString><?php print $fields["resource_contact_deliveryPoint"]; ?></gco:CharacterString>' . "\n";
  $output .= '                  </gmd:deliveryPoint>' . "\n";
  $output .= '                  <gmd:city>' . "\n";
  $output .= '                    <gco:CharacterString><?php print $fields["resource_contact_city"]; ?></gco:CharacterString>' . "\n";
  $output .= '                  </gmd:city>' . "\n";
  $output .= '                  <gmd:administrativeArea>' . "\n";
  $output .= '                    <gco:CharacterString><?php print $fields["resource_contact_administrativeArea"]; ?></gco:CharacterString>' . "\n";
  $output .= '                  </gmd:administrativeArea>' . "\n";
  $output .= '                  <gmd:postalCode>' . "\n";
  $output .= '                    <gco:CharacterString><?php print $fields["resource_contact_postalCode"]; ?></gco:CharacterString>' . "\n";
  $output .= '                  </gmd:postalCode>' . "\n";
  $output .= '                  <gmd:country>' . "\n";
  $output .= '                    <gco:CharacterString><?php print $fields["resource_contact_country"]; ?></gco:CharacterString>' . "\n";
  $output .= '                  </gmd:country>' . "\n";
  $output .= '                  <?php } ?>' . "\n";
  $output .= '                  <?php if ($fields["resource_contact_electronicMailAddress"]) {?>' . "\n";
  $output .= '                  <gmd:electronicMailAddress>' . "\n";
  $output .= '                    <gco:CharacterString><?php print $fields["resource_contact_electronicMailAddress"]; ?></gco:CharacterString>' . "\n";
  $output .= '                  </gmd:electronicMailAddress>' . "\n";
  $output .= '                  <?php } ?>' . "\n";
  $output .= '                </gmd:CI_Address>' . "\n";
  $output .= '              </gmd:address>' . "\n";
  $output .= '              <?php } ?>' . "\n";
  $output .= '              <?php if ($fields["resource_contact_onlineResource_URL"]) {?>' . "\n";
  $output .= '              <gmd:onlineResource>' . "\n";
  $output .= '                <gmd:CI_OnlineResource>' . "\n";
  $output .= '                  <gmd:linkage>' . "\n";
  $output .= '                    <gmd:URL><?php print $fields["resource_contact_onlineResource_URL"]; ?></gmd:URL>' . "\n";
  $output .= '                  </gmd:linkage>' . "\n";
  $output .= '                  <gmd:protocol>' . "\n";
  $output .= '                    <gco:CharacterString>http</gco:CharacterString>' . "\n";
  $output .= '                  </gmd:protocol>' . "\n";
  $output .= '                  <?php if ($fields["resource_contact_onlineResource_description"]) {?>' . "\n";
  $output .= '                  <gmd:description>' . "\n";
  $output .= '                    <gco:CharacterString><?php print $fields["resource_contact_onlineResource_description"]; ?></gco:CharacterString>' . "\n";
  $output .= '                  </gmd:description>' . "\n";
  $output .= '                  <?php } ?>' . "\n";
  $output .= '                </gmd:CI_OnlineResource>' . "\n";
  $output .= '              </gmd:onlineResource>' . "\n";
  $output .= '              <?php } ?>' . "\n";
  $output .= '              <?php if ($fields["resource_contact_hoursOfService"]) {?>' . "\n";
  $output .= '              <gmd:hoursOfService>' . "\n";
  $output .= '                <gco:CharacterString><?php print $fields["resource_contact_hoursOfService"]; ?></gco:CharacterString>' . "\n";
  $output .= '              </gmd:hoursOfService>' . "\n";
  $output .= '              <?php } ?>' . "\n";
  $output .= '              <?php if ($fields["resource_contact_contactInstructions"]) {?>' . "\n";
  $output .= '              <gmd:contactInstructions>' . "\n";
  $output .= '                <gco:CharacterString><?php print $fields["resource_contact_contactInstructions"]; ?></gco:CharacterString>' . "\n";
  $output .= '              </gmd:contactInstructions>' . "\n";
  $output .= '              <?php } ?>' . "\n";
  $output .= '            </gmd:CI_Contact>' . "\n";
  $output .= '          </gmd:contactInfo>' . "\n";
  $output .= '          <?php } ?>' . "\n";
  $output .= '          <gmd:role>' . "\n";
  $output .= '            <gmd:CI_RoleCode ' . "\n";
  $output .= '              codeList="http://standards.iso.org/ittf/PubliclyAvailableStandards/ISO_19139_Schemas/resources/Codelist/gmxCodelists.xml#CI_RoleCode" ' . "\n";
  $output .= '              codeListValue="pointOfContact">point of contact</gmd:CI_RoleCode>' . "\n";
  $output .= '          </gmd:role>' . "\n";
  $output .= '        </gmd:CI_ResponsibleParty>' . "\n";
  $output .= '      </gmd:pointOfContact>' . "\n";
  $output .= '      <?php } ?>' . "\n";
  $output .= '      <?php if ($fields["descriptiveKeywords_theme"]) {' . "\n";
  $output .= '        $keywordsArr = explode("|", $fields["descriptiveKeywords_theme"]);' . "\n";
  $output .= '        ?>' . "\n";
  $output .= '      <gmd:descriptiveKeywords>' . "\n";
  $output .= '        <gmd:MD_Keywords>' . "\n";
  $output .= '          <?php foreach ($keywordsArr as $keyword) { ?>' . "\n";
  $output .= '          <gmd:keyword>' . "\n";
  $output .= '            <gco:CharacterString><?php print trim($keyword); ?></gco:CharacterString>' . "\n";
  $output .= '          </gmd:keyword>' . "\n";
  $output .= '          <?php } ?>' . "\n";
  $output .= '          <gmd:type>' . "\n";
  $output .= '            <gmd:MD_KeywordTypeCode ' . "\n";
  $output .= '              codeList="http://standards.iso.org/ittf/PubliclyAvailableStandards/ISO_19139_Schemas/resources/Codelist/gmxCodelists.xml#MD_KeywordTypeCode" ' . "\n";
  $output .= '              codeListValue="theme">theme</gmd:MD_KeywordTypeCode>' . "\n";
  $output .= '          </gmd:type>' . "\n";
  $output .= '        </gmd:MD_Keywords>' . "\n";
  $output .= '      </gmd:descriptiveKeywords>' . "\n";
  $output .= '      <?php } ?>' . "\n";
  $output .= '      <?php if ($fields["descriptiveKeywords_temporal"]) {' . "\n";
  $output .= '        $keywordsArr = explode("|", $fields["descriptiveKeywords_temporal"]);' . "\n";
  $output .= '        ?>' . "\n";
  $output .= '      <gmd:descriptiveKeywords>' . "\n";
  $output .= '        <gmd:MD_Keywords>' . "\n";
  $output .= '          <?php foreach ($keywordsArr as $keyword) { ?>' . "\n";
  $output .= '          <gmd:keyword>' . "\n";
  $output .= '            <gco:CharacterString><?php print trim($keyword); ?></gco:CharacterString>' . "\n";
  $output .= '          </gmd:keyword>' . "\n";
  $output .= '          <?php } ?>' . "\n";
  $output .= '          <gmd:type>' . "\n";
  $output .= '            <gmd:MD_KeywordTypeCode ' . "\n";
  $output .= '              codeList="http://standards.iso.org/ittf/PubliclyAvailableStandards/ISO_19139_Schemas/resources/Codelist/gmxCodelists.xml#MD_KeywordTypeCode" ' . "\n";
  $output .= '              codeListValue="temporal">temporal</gmd:MD_KeywordTypeCode>' . "\n";
  $output .= '          </gmd:type>' . "\n";
  $output .= '        </gmd:MD_Keywords>' . "\n";
  $output .= '      </gmd:descriptiveKeywords>' . "\n";
  $output .= '      <?php } ?>' . "\n";
  $output .= '      <?php if ($fields["descriptiveKeywords_place"]) {' . "\n";
  $output .= '        $keywordsArr = explode("|", $fields["descriptiveKeywords_place"]);' . "\n";
  $output .= '        ?>' . "\n";
  $output .= '      <gmd:descriptiveKeywords>' . "\n";
  $output .= '        <gmd:MD_Keywords>' . "\n";
  $output .= '          <?php foreach ($keywordsArr as $keyword) { ?>' . "\n";
  $output .= '          <gmd:keyword>' . "\n";
  $output .= '            <gco:CharacterString><?php print trim($keyword); ?></gco:CharacterString>' . "\n";
  $output .= '          </gmd:keyword>' . "\n";
  $output .= '          <?php } ?>' . "\n";
  $output .= '          <gmd:type>' . "\n";
  $output .= '            <gmd:MD_KeywordTypeCode ' . "\n";
  $output .= '              codeList="http://standards.iso.org/ittf/PubliclyAvailableStandards/ISO_19139_Schemas/resources/Codelist/gmxCodelists.xml#MD_KeywordTypeCode" ' . "\n";
  $output .= '              codeListValue="place">place</gmd:MD_KeywordTypeCode>' . "\n";
  $output .= '          </gmd:type>' . "\n";
  $output .= '        </gmd:MD_Keywords>' . "\n";
  $output .= '      </gmd:descriptiveKeywords>' . "\n";
  $output .= '      <?php } ?>' . "\n";
  $output .= '      <?php if ($fields["resourceConstraints_useLimitation"]) {?>' . "\n";
  $output .= '      <gmd:resourceConstraints>' . "\n";
  $output .= '        <gmd:MD_LegalConstraints>' . "\n";
  $output .= '          <gmd:useLimitation>' . "\n";
  $output .= '            <gco:CharacterString><?php print $fields["resourceConstraints_useLimitation"]; ?></gco:CharacterString>' . "\n";
  $output .= '          </gmd:useLimitation>' . "\n";
  $output .= '        </gmd:MD_LegalConstraints>' . "\n";
  $output .= '      </gmd:resourceConstraints>' . "\n";
  $output .= '      <?php } ?>' . "\n";
  $output .= '      <?php if ($fields["spatialResolution_equivalentScale_denominator"]) {?>' . "\n";
  $output .= '      <gmd:spatialResolution>' . "\n";
  $output .= '        <gmd:MD_Resolution>' . "\n";
  $output .= '          <gmd:equivalentScale>' . "\n";
  $output .= '            <gmd:MD_RepresentativeFraction>' . "\n";
  $output .= '              <gmd:denominator>' . "\n";
  $output .= '                <gco:Integer><?php print $fields["spatialResolution_equivalentScale_denominator"]; ?></gco:Integer>' . "\n";
  $output .= '              </gmd:denominator>' . "\n";
  $output .= '            </gmd:MD_RepresentativeFraction>' . "\n";
  $output .= '          </gmd:equivalentScale>' . "\n";
  $output .= '        </gmd:MD_Resolution>' . "\n";
  $output .= '      </gmd:spatialResolution>' . "\n";
  $output .= '      <?php } ?>' . "\n";
  $output .= '      <gmd:language>' . "\n";
  $output .= '        <gco:CharacterString><?php print $fields["resource_language"]; ?></gco:CharacterString>' . "\n";
  $output .= '      </gmd:language>' . "\n";
  $output .= '      <gmd:topicCategory>' . "\n";
  $output .= '        <gmd:MD_TopicCategoryCode><?php print $fields["resource_topicCategory"]; ?></gmd:MD_TopicCategoryCode>' . "\n";
  $output .= '      </gmd:topicCategory>' . "\n";
  $output .= '      <gmd:extent>' . "\n";
  $output .= '        <gmd:EX_Extent>' . "\n";
  $output .= '          <?php if ($fields["extent_description"]) {?>' . "\n";
  $output .= '          <gmd:description>' . "\n";
  $output .= '            <gco:CharacterString><?php print $fields["extent_description"]; ?></gco:CharacterString>' . "\n";
  $output .= '          </gmd:description>' . "\n";
  $output .= '          <?php } ?>' . "\n";
  $output .= '          <?php if (($fields["extent_westBoundLongitude"]) && ($fields["extent_eastBoundLongitude"]) && ($fields["extent_southBoundLatitude"]) && ($fields["extent_northBoundLatitude"])) {?>' . "\n";
  $output .= '          <gmd:geographicElement>' . "\n";
  $output .= '            <gmd:EX_GeographicBoundingBox>' . "\n";
  $output .= '              <gmd:extentTypeCode>' . "\n";
  $output .= '                <gco:Boolean>1</gco:Boolean>' . "\n";
  $output .= '              </gmd:extentTypeCode>' . "\n";
  $output .= '              <gmd:westBoundLongitude>' . "\n";
  $output .= '                <gco:Decimal><?php print $fields["extent_westBoundLongitude"]; ?></gco:Decimal>' . "\n";
  $output .= '              </gmd:westBoundLongitude>' . "\n";
  $output .= '              <gmd:eastBoundLongitude>' . "\n";
  $output .= '                <gco:Decimal><?php print $fields["extent_eastBoundLongitude"]; ?></gco:Decimal>' . "\n";
  $output .= '              </gmd:eastBoundLongitude>' . "\n";
  $output .= '              <gmd:southBoundLatitude>' . "\n";
  $output .= '                <gco:Decimal><?php print $fields["extent_southBoundLatitude"]; ?></gco:Decimal>' . "\n";
  $output .= '              </gmd:southBoundLatitude>' . "\n";
  $output .= '              <gmd:northBoundLatitude>' . "\n";
  $output .= '                <gco:Decimal><?php print $fields["extent_northBoundLatitude"]; ?></gco:Decimal>' . "\n";
  $output .= '              </gmd:northBoundLatitude>' . "\n";
  $output .= '            </gmd:EX_GeographicBoundingBox>' . "\n";
  $output .= '          </gmd:geographicElement>' . "\n";
  $output .= '          <?php } ?>' . "\n";
  $output .= '        </gmd:EX_Extent>' . "\n";
  $output .= '      </gmd:extent>' . "\n";
  $output .= '      <?php if (($fields["extent_TimePeriod_frame"]) && (($fields["resource_TimePeriod_frame"] == "#ISO-8601") || ($fields["resource_TimePeriod_frame"] == "urn:cgi:trs:CGI:StandardGeologicTimeMa"))) {?>' . "\n";
  $output .= '      <gmd:extent>' . "\n";
  $output .= '        <gmd:EX_Extent>' . "\n";
  $output .= '          <gmd:temporalElement>' . "\n";
  $output .= '            <gmd:EX_TemporalExtent>' . "\n";
  $output .= '              <gmd:extent>' . "\n";
  $output .= '                <?php if (($fields["resource_TimePeriod_frame"] == "#ISO-8601")) {?>' . "\n";
  $output .= '                <gml:TimePeriod gml:id="IdModern">' . "\n";
  $output .= '                  <gml:name><?php print $fields["extent_TimePeriod_name"]; ?></gml:name>' . "\n";
  $output .= '                  <gml:beginPosition frame="<?php print $fields["extent_TimePeriod_frame"]; ?>"><?php print $fields["extent_TimePeriod_beginPosition"]; ?></gml:beginPosition>' . "\n";
  $output .= '                  <gml:endPosition frame="<?php print $fields["extent_TimePeriod_frame"]; ?>"><?php print $fields["extent_TimePeriod_endPosition"]; ?></gml:endPosition>' . "\n";
  $output .= '                </gml:TimePeriod>' . "\n";
  $output .= '                <?php } ?>' . "\n";
  $output .= '                <?php if (($fields["resource_TimePeriod_frame"] == "urn:cgi:trs:CGI:StandardGeologicTimeMa")) {?>' . "\n";
  $output .= '                <gml:TimePeriod gml:id="IdGeological">' . "\n";
  $output .= '                  <gml:name><?php print $fields["extent_TimePeriod_name"]; ?></gml:name>' . "\n";
  $output .= '                  <gml:beginPosition frame="<?php print $fields["extent_TimePeriod_frame"]; ?>"><?php print $fields["extent_TimePeriod_beginPosition"]; ?></gml:beginPosition>' . "\n";
  $output .= '                  <gml:endPosition frame="<?php print $fields["extent_TimePeriod_frame"]; ?>"><?php print $fields["extent_TimePeriod_endPosition"]; ?></gml:endPosition>' . "\n";
  $output .= '                </gml:TimePeriod>' . "\n";
  $output .= '                <?php } ?>' . "\n";
  $output .= '              </gmd:extent>' . "\n";
  $output .= '            </gmd:EX_TemporalExtent>' . "\n";
  $output .= '          </gmd:temporalElement>' . "\n";
  $output .= '        </gmd:EX_Extent>' . "\n";
  $output .= '      </gmd:extent>' . "\n";
  $output .= '      <?php } ?>' . "\n";
  $output .= '      <?php if (($fields["extent_verticalElement_minimumValue"]) && ($fields["extent_verticalElement_maximumValue"])) {?>' . "\n";
  $output .= '      <gmd:extent>' . "\n";
  $output .= '        <gmd:EX_Extent>' . "\n";
  $output .= '          <gmd:verticalElement>' . "\n";
  $output .= '            <gmd:EX_VerticalExtent>' . "\n";
  $output .= '              <gmd:minimumValue>' . "\n";
  $output .= '                <gco:Real><?php print $fields["extent_verticalElement_minimumValue"]; ?></gco:Real>' . "\n";
  $output .= '              </gmd:minimumValue>' . "\n";
  $output .= '              <gmd:maximumValue>' . "\n";
  $output .= '                <gco:Real><?php print $fields["extent_verticalElement_maximumValue"]; ?></gco:Real>' . "\n";
  $output .= '              </gmd:maximumValue>' . "\n";
  $output .= '              <gmd:verticalCRS xlink:href="urn:ogc:def:crs:EPSG::5714"/>' . "\n";
  $output .= '            </gmd:EX_VerticalExtent>' . "\n";
  $output .= '          </gmd:verticalElement>' . "\n";
  $output .= '        </gmd:EX_Extent>' . "\n";
  $output .= '      </gmd:extent>' . "\n";
  $output .= '      <?php } ?>' . "\n";
  $output .= '    </gmd:MD_DataIdentification>' . "\n";
  $output .= '  </gmd:identificationInfo>' . "\n";
  $output .= '  <!-- **************** -->' . "\n";
  $output .= '  <?php if (' . "\n";
  $output .= '						(($fields["distributor_contact_individualName"]) || ($fields["distributor_contact_organisationName"]) || ($fields["distributor_contact_positionName"]))' . "\n";
  $output .= '						&& (($fields["distributorTransferOptions_url"]) || ($fields["distributionOrderProcess_orderingInstructions"])) ) {?>' . "\n";
  $output .= '	<gmd:distributionInfo>' . "\n";
  $output .= '		<gmd:MD_Distribution>' . "\n";
  $output .= '			<gmd:distributor>' . "\n";
  $output .= '				<gmd:MD_Distributor>' . "\n";
  $output .= '					<?php if (($fields["distributor_contact_individualName"]) || ($fields["distributor_contact_organisationName"]) || ($fields["distributor_contact_positionName"])) {?>' . "\n";
  $output .= '          <!-- (C) Distribution responsible party -->' . "\n";
  $output .= '					<gmd:distributorContact>' . "\n";
  $output .= '						<gmd:CI_ResponsibleParty>' . "\n";
  $output .= '              <?php if ($fields["distributor_contact_individualName"]) {?>' . "\n";
  $output .= '              <gmd:individualName>' . "\n";
  $output .= '                <gco:CharacterString><?php print $fields["distributor_contact_individualName"]; ?></gco:CharacterString>' . "\n";
  $output .= '              </gmd:individualName>' . "\n";
  $output .= '              <?php } ?>' . "\n";
  $output .= '              <?php if ($fields["distributor_contact_organisationName"]) {?>' . "\n";
  $output .= '              <gmd:organisationName>' . "\n";
  $output .= '                <gco:CharacterString><?php print $fields["distributor_contact_organisationName"]; ?></gco:CharacterString>' . "\n";
  $output .= '              </gmd:organisationName>' . "\n";
  $output .= '              <?php if ($fields["distributor_contact_positionName"]) {?>' . "\n";
  $output .= '              <?php } ?>' . "\n";
  $output .= '              <gmd:positionName>' . "\n";
  $output .= '                <gco:CharacterString><?php print $fields["distributor_contact_positionName"]; ?></gco:CharacterString>' . "\n";
  $output .= '              </gmd:positionName>' . "\n";
  $output .= '              <?php } ?>' . "\n";
  $output .= '              <?php if (($fields["distributor_contact_voice"]) || ($fields["distributor_contact_facsimile"]) || ($fields["distributor_contact_deliveryPoint"]) || ($fields["distributor_contact_electronicMailAddress"])) {?>' . "\n";
  $output .= '              <gmd:contactInfo>' . "\n";
  $output .= '                <gmd:CI_Contact>' . "\n";
  $output .= '                  <?php if (($fields["distributor_contact_voice"]) || ($fields["distributor_contact_facsimile"])) {?>' . "\n";
  $output .= '                  <gmd:phone>' . "\n";
  $output .= '                    <gmd:CI_Telephone>' . "\n";
  $output .= '                      <?php if ($fields["distributor_contact_voice"]) {?>' . "\n";
  $output .= '                      <gmd:voice>' . "\n";
  $output .= '                        <gco:CharacterString><?php print $fields["distributor_contact_voice"]; ?></gco:CharacterString>' . "\n";
  $output .= '                      </gmd:voice>' . "\n";
  $output .= '                      <?php } ?>' . "\n";
  $output .= '                      <?php if ($fields["distributor_contact_facsimile"]) {?>' . "\n";
  $output .= '                      <gmd:facsimile>' . "\n";
  $output .= '                        <gco:CharacterString><?php print $fields["distributor_contact_facsimile"]; ?></gco:CharacterString>' . "\n";
  $output .= '                      </gmd:facsimile>' . "\n";
  $output .= '                      <?php } ?>' . "\n";
  $output .= '                    </gmd:CI_Telephone>' . "\n";
  $output .= '                  </gmd:phone>' . "\n";
  $output .= '                  <?php } ?>' . "\n";
  $output .= '                  <?php if (($fields["distributor_contact_deliveryPoint"]) || ($fields["distributor_contact_electronicMailAddress"])) {?>' . "\n";
  $output .= '                  <gmd:address>' . "\n";
  $output .= '                    <gmd:CI_Address>' . "\n";
  $output .= '                      <?php if ($fields["distributor_contact_deliveryPoint"]) {?>' . "\n";
  $output .= '                      <gmd:deliveryPoint>' . "\n";
  $output .= '                        <gco:CharacterString><?php print $fields["distributor_contact_deliveryPoint"]; ?></gco:CharacterString>' . "\n";
  $output .= '                      </gmd:deliveryPoint>' . "\n";
  $output .= '                      <gmd:city>' . "\n";
  $output .= '                        <gco:CharacterString><?php print $fields["distributor_contact_city"]; ?></gco:CharacterString>' . "\n";
  $output .= '                      </gmd:city>' . "\n";
  $output .= '                      <gmd:administrativeArea>' . "\n";
  $output .= '                        <gco:CharacterString><?php print $fields["distributor_contact_administrativeArea"]; ?></gco:CharacterString>' . "\n";
  $output .= '                      </gmd:administrativeArea>' . "\n";
  $output .= '                      <gmd:postalCode>' . "\n";
  $output .= '                        <gco:CharacterString><?php print $fields["distributor_contact_postalCode"]; ?></gco:CharacterString>' . "\n";
  $output .= '                      </gmd:postalCode>' . "\n";
  $output .= '                      <gmd:country>' . "\n";
  $output .= '                        <gco:CharacterString><?php print $fields["distributor_contact_country"]; ?></gco:CharacterString>' . "\n";
  $output .= '                      </gmd:country>' . "\n";
  $output .= '                      <?php } ?>' . "\n";
  $output .= '                      <?php if ($fields["distributor_contact_electronicMailAddress"]) {?>' . "\n";
  $output .= '                      <gmd:electronicMailAddress>' . "\n";
  $output .= '                        <gco:CharacterString><?php print $fields["distributor_contact_electronicMailAddress"]; ?></gco:CharacterString>' . "\n";
  $output .= '                      </gmd:electronicMailAddress>' . "\n";
  $output .= '                      <?php } ?>' . "\n";
  $output .= '                    </gmd:CI_Address>' . "\n";
  $output .= '                  </gmd:address>' . "\n";
  $output .= '                  <?php } ?>' . "\n";
  $output .= '                  <?php if ($fields["distributor_contact_onlineResource_URL"]) {?>' . "\n";
  $output .= '                  <gmd:onlineResource>' . "\n";
  $output .= '                    <gmd:CI_OnlineResource>' . "\n";
  $output .= '                      <gmd:linkage>' . "\n";
  $output .= '                        <gmd:URL><?php print $fields["distributor_contact_onlineResource_URL"]; ?></gmd:URL>' . "\n";
  $output .= '                      </gmd:linkage>' . "\n";
  $output .= '                      <gmd:protocol>' . "\n";
  $output .= '                        <gco:CharacterString>http</gco:CharacterString>' . "\n";
  $output .= '                      </gmd:protocol>' . "\n";
  $output .= '                      <?php if ($fields["distributor_contact_onlineResource_description"]) {?>' . "\n";
  $output .= '                      <gmd:description>' . "\n";
  $output .= '                        <gco:CharacterString><?php print $fields["distributor_contact_onlineResource_description"]; ?></gco:CharacterString>' . "\n";
  $output .= '                      </gmd:description>' . "\n";
  $output .= '                      <?php } ?>' . "\n";
  $output .= '                    </gmd:CI_OnlineResource>' . "\n";
  $output .= '                  </gmd:onlineResource>' . "\n";
  $output .= '                  <?php } ?>' . "\n";
  $output .= '                  <?php if ($fields["distributor_contact_hoursOfService"]) {?>' . "\n";
  $output .= '                  <gmd:hoursOfService>' . "\n";
  $output .= '                    <gco:CharacterString><?php print $fields["distributor_contact_hoursOfService"]; ?></gco:CharacterString>' . "\n";
  $output .= '                  </gmd:hoursOfService>' . "\n";
  $output .= '                  <?php } ?>' . "\n";
  $output .= '                  <?php if ($fields["distributor_contact_contactInstructions"]) {?>' . "\n";
  $output .= '                  <gmd:contactInstructions>' . "\n";
  $output .= '                    <gco:CharacterString><?php print $fields["distributor_contact_contactInstructions"]; ?></gco:CharacterString>' . "\n";
  $output .= '                  </gmd:contactInstructions>' . "\n";
  $output .= '                  <?php } ?>' . "\n";
  $output .= '                </gmd:CI_Contact>' . "\n";
  $output .= '              </gmd:contactInfo>' . "\n";
  $output .= '              <?php } ?>' . "\n";
  $output .= '              <gmd:role>' . "\n";
  $output .= '	              <gmd:CI_RoleCode ' . "\n";
  $output .= '									codeList="http://standards.iso.org/ittf/PubliclyAvailableStandards/ISO_19139_Schemas/resources/Codelist/gmxCodelists.xml#CI_RoleCode" ' . "\n";
  $output .= '									codeListValue="distributor">distributor</gmd:CI_RoleCode>' . "\n";
  $output .= '							</gmd:role>' . "\n";
  $output .= '						</gmd:CI_ResponsibleParty>' . "\n";
  $output .= '					</gmd:distributorContact>' . "\n";
  $output .= '          <?php } ?>' . "\n";
  $output .= '          <?php if ($fields["distributionOrderProcess_orderingInstructions"]) {?>' . "\n";
  $output .= '					<!-- (O) Resource distributor order process - Information on the availability of the service which includes at least one of fees, available date and time, ordering instructions, or turnaround. -->' . "\n";
  $output .= '					<gmd:distributionOrderProcess>' . "\n";
  $output .= '						<gmd:MD_StandardOrderProcess>' . "\n";
  $output .= '            	<?php if ($fields["distributionOrderProcess_fees"]) {?>' . "\n";
  $output .= '							<gmd:fees>' . "\n";
  $output .= '								<gco:CharacterString><?php print $fields["distributionOrderProcess_fees"]; ?></gco:CharacterString>' . "\n";
  $output .= '							</gmd:fees>' . "\n";
  $output .= '							<?php } ?>' . "\n";
  $output .= '              <!-- (M) Ordering instructions - general instructions, terms and services provided by the distributor -->' . "\n";
  $output .= '              <?php if ($fields["distributionOrderProcess_orderingInstructions"]) {?>' . "\n";
  $output .= '							<gmd:orderingInstructions>' . "\n";
  $output .= '								<gco:CharacterString><?php print $fields["distributionOrderProcess_orderingInstructions"]; ?></gco:CharacterString>' . "\n";
  $output .= '							</gmd:orderingInstructions>' . "\n";
  $output .= '              <?php } ?>' . "\n";
  $output .= '							<?php if ($fields["distributionOrderProcess_turnaround"]) {?>' . "\n";
  $output .= '							<gmd:turnaround>' . "\n";
  $output .= '								<gco:CharacterString><?php print $fields["distributionOrderProcess_turnaround"]; ?></gco:CharacterString>' . "\n";
  $output .= '							</gmd:turnaround>' . "\n";
  $output .= '              <?php } ?>' . "\n";
  $output .= '						</gmd:MD_StandardOrderProcess>' . "\n";
  $output .= '					</gmd:distributionOrderProcess>' . "\n";
  $output .= '          <?php } ?>' . "\n";
  $output .= '          <?php if ($fields["distributorTransferOptions_url"]) {?>' . "\n";
  $output .= '					<!-- Resource distributor transfer options - Provides information about the technical means and media used by the distributor. -->' . "\n";
  $output .= '					<gmd:distributorTransferOptions>' . "\n";
  $output .= '						<gmd:MD_DigitalTransferOptions>' . "\n";
  $output .= '							<gmd:onLine>' . "\n";
  $output .= '								<gmd:CI_OnlineResource>' . "\n";
  $output .= '									<gmd:linkage>' . "\n";
  $output .= '										<gmd:URL><?php print $fields["distributorTransferOptions_url"]; ?></gmd:URL>' . "\n";
  $output .= '									</gmd:linkage>' . "\n";
  $output .= '									<gmd:protocol>' . "\n";
  $output .= '										<gco:CharacterString>http</gco:CharacterString>' . "\n";
  $output .= '									</gmd:protocol>' . "\n";
  $output .= '									<gmd:description>' . "\n";
  $output .= '										<gco:CharacterString><?php print $fields["distributorTransferOptions_description"]; ?></gco:CharacterString>' . "\n";
  $output .= '									</gmd:description>' . "\n";
  $output .= '									<gmd:function>' . "\n";
  $output .= '										<gmd:CI_OnLineFunctionCode ' . "\n";
  $output .= '											codeList="http://standards.iso.org/ittf/PubliclyAvailableStandards/ISO_19139_Schemas/resources/Codelist/gmxCodelists.xml#CI_OnLineFunctionCode" ' . "\n";
  $output .= '											codeListValue="information">information</gmd:CI_OnLineFunctionCode>' . "\n";
  $output .= '									</gmd:function>' . "\n";
  $output .= '								</gmd:CI_OnlineResource>' . "\n";
  $output .= '							</gmd:onLine>' . "\n";
  $output .= '						</gmd:MD_DigitalTransferOptions>' . "\n";
  $output .= '					</gmd:distributorTransferOptions>' . "\n";
  $output .= '          <?php } ?>' . "\n";
  $output .= '				</gmd:MD_Distributor>' . "\n";
  $output .= '			</gmd:distributor>' . "\n";
  $output .= '      <?php if ($fields["distributorTransferOptions_url"]) {?>' . "\n";
  $output .= '			<gmd:transferOptions>' . "\n";
  $output .= '				<gmd:MD_DigitalTransferOptions>' . "\n";
  $output .= '							<gmd:onLine>' . "\n";
  $output .= '								<gmd:CI_OnlineResource>' . "\n";
  $output .= '									<gmd:linkage>' . "\n";
  $output .= '										<gmd:URL><?php print $fields["distributorTransferOptions_url"]; ?></gmd:URL>' . "\n";
  $output .= '									</gmd:linkage>' . "\n";
  $output .= '									<gmd:protocol>' . "\n";
  $output .= '										<gco:CharacterString>http</gco:CharacterString>' . "\n";
  $output .= '									</gmd:protocol>' . "\n";
  $output .= '									<gmd:description>' . "\n";
  $output .= '										<gco:CharacterString><?php print $fields["distributorTransferOptions_description"]; ?></gco:CharacterString>' . "\n";
  $output .= '									</gmd:description>' . "\n";
  $output .= '									<gmd:function>' . "\n";
  $output .= '										<gmd:CI_OnLineFunctionCode ' . "\n";
  $output .= '											codeList="http://standards.iso.org/ittf/PubliclyAvailableStandards/ISO_19139_Schemas/resources/Codelist/gmxCodelists.xml#CI_OnLineFunctionCode" ' . "\n";
  $output .= '											codeListValue="information">information</gmd:CI_OnLineFunctionCode>' . "\n";
  $output .= '									</gmd:function>' . "\n";
  $output .= '								</gmd:CI_OnlineResource>' . "\n";
  $output .= '							</gmd:onLine>' . "\n";
  $output .= '				</gmd:MD_DigitalTransferOptions>' . "\n";
  $output .= '			</gmd:transferOptions>' . "\n";
  $output .= '      <?php } ?>' . "\n";
  $output .= '		</gmd:MD_Distribution>' . "\n";
  $output .= '	</gmd:distributionInfo>	' . "\n";
  $output .= '  <?php } ?>' . "\n";
  $output .= '</gmd:MD_Metadata>' . "\n";

  print $output;
}