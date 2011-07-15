<?php

class GorillaException extends Exception {
  private $errorCode;
  private $errorMessage;
  
  function __construct($errorCode, $errorMessage) {
    $this->errorCode = $errorCode;
    $this->errorMessage = $errorMessage;
  }
  
  function getErrorCode() {
    return $this->errorCode;
  }
  
  function getErrorMessage() {
    return $this->errorMessage;
  }
}