<?php

/**
 * This class represents a campaign in mailchimp
 */
class GorillaCampaign {
  var $list_id;
  var $title;
  var $type;
  var $subject;
  var $from_email;
  var $from_name;
  var $tracking_opens;
  var $tracking_html_clicks;
  var $tracking_text_clicks;
  var $authenticate;
  var $template_id;
  var $content;
  
  function __construct() {
  }
  
  function __set($var, $value) {
    if (!isset($this->{$var})) {
      $error = t('The variable %var does not exist', array('%var' => $var));
      trigger_error($error, E_USER_ERROR);
    }
    
    $this->{$var} = $value;
  }
  
  function __get($var) {
    switch ($var) {
      case 'options' :
        return $this->getOptions();
      default :
        return $this->getVar($var);
    }
  }
  
  private function getVar($var) {
    if (!isset($this->{$var})) {
      $error = t('The variable %var does not exist', array('%var' => $var));
      trigger_error($error, E_USER_ERROR);
    }
 
    return $this->{$var};    
  }
  
  private function getOptions() {
    return array(
      'list_id' => $this->list_id,
      'title' => $this->title,
      'subject' => $this->subject,
      'from_email' => $this->from_email,
      'from_name' => $this->from_name,
      'tracking' => array(
        'opens' => $this->tracking_opens,
        'html_clicks' => $this->tracking_html_clicks,
        'text_clicks' => $this->tracking_text_clicks,
      ),
     'authenticate' => $this->authenticate,
     'template_id' => $this->template_id,
    );
  }
}