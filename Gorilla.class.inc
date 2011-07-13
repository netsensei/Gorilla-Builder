<?php

class Gorilla {
  
  private $mcapi;
  private $api_key;
  private $current_cid = NULL;
  
  /**
   * Constructor
   * @param api_key
   *  The API key from Mailchimp.
   */ 
  function __construct($api_key) {
    $this->mcapi = new MCAPI($api_key);
  }
 
 /**
  * Create a new campaign
  */
  function create_campaign($type, $options, $content, $segment_opts = NULL, $type_opts = NULL) {
    $params = array(
      'type' => $type,
      'options' => $options,
      'content' => $content,
      'segment_opts' => $segment_opts,
      'type_opts' => $type_opts,
    );
    
    $this->current_cid = $this->call('campaignCreate', $params);

    return $this->current_cid;
  }

  /**
   * Send the campaign. No scheduling or delaying. Just shoves it right out of the door.
   * You'll need to create a campaign before you can send it.
   */
  function send_campaign_now($cid = NULL) {
    $params = array(
      'cid' => ($cid) ? $cid : $this->current_cid,
    );

    return $this->call('campaignSendNow', $params);
  }
  
  /**
   * Get the active campaign id
   * @return integer
   *  The active campaign identifier
   */
  function get_current_cid() {
    return $this->current_cid;
  }
  
  function list_interesting_groups($lid) {
    $params = array(
      'id' => $lid,
    );
    return $this->call('listInterestGroupings', $params);    
  }
  
  /**
   * Gets a list of all available templates
   * @return array
   *  A structured array of all available templates
   */
  function campaign_templates() {
    $params = array();
    return $this->call('campaignTemplates', $params);
  }

  /**
   * Makes the API call to the MCAPI class. Just adds exception error handling
   */
  private function call($call, $params = array()) {
    if (method_exists($this->mcapi, $call)) {
      $result = call_user_func_array(array($this->mcapi, $call), $params);
      
      if ($this->mcapi->errorCode) {
        throw new Exception("Error: " . $mcapi->errorCode . " :: " . $mcapi->errorMessage); 
      }

      return $result;
    }
  }
}