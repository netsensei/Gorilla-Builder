<?php

/**
 * General exception class. Adds watchdog support.
 */
class GorillaException extends Exception {  
  

  public function __construct($message, $code = 0) {
    $vars = array(
      '%class' => get_class($this),
      '%code' => $code,
      '%message' => $message,
    );
    
    watchdog('gorilla_builder', '%class : [%code] %message', $vars, WATCHDOG_ERROR);
    
    parent::__construct($message, $code);
  }

}

/**
 * When we can't connect to Mailchimp
 */
class GorillaConnectionException extends GorillaException {  

  public function __toString() {
    return t('Could not connect with Mailchimp.');
  }

}

/**
 * When the connection times out
 */
class GorillaTimeoutException extends GorillaException {  
  
  public function __toString() {
    return t('The connection with Mailchimp timed out.');
  }

}

/**
 * When a bad response is illicited from Mailchimp
 */
class GorillaBadresponseException extends GorillaException {
  
  public function __toString() {
    return t('The Mailchimp API returned an error.');
  }

}