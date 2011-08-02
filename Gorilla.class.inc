<?php

/**
 *  Implements the Mailchimp API. Extends MCAPI to add better error handling.
 */
class Gorilla extends MCAPI {
  
  /**
   * This function overrides the callServer method of the MCAPI class. We did 
   * this to add exception handling.
   * 
   * @param string $method
   * @param array $params
   * @return mixed
   */
  function callServer($method, $params) {
    $dc = "us1";
    
    if (strstr($this->api_key,"-")) {
      list($key, $dc) = explode("-",$this->api_key,2);
      
      if (!$dc) $dc = "us1";
    }
    
    $host = $dc.".".$this->apiUrl["host"];
    $params["apikey"] = $this->api_key;

    $this->errorMessage = "";
    $this->errorCode = "";
    
    $post_vars = $this->httpBuildQuery($params);

    $payload = "POST " . $this->apiUrl["path"] . "?" . $this->apiUrl["query"] . "&method=" . $method . " HTTP/1.0\r\n";
    $payload .= "Host: " . $host . "\r\n";
    $payload .= "User-Agent: MCAPI/" . $this->version ."\r\n";
    $payload .= "Content-type: application/x-www-form-urlencoded\r\n";
    $payload .= "Content-length: " . strlen($post_vars) . "\r\n";
    $payload .= "Connection: close \r\n\r\n";
    $payload .= $post_vars;

    ob_start();
    if ($this->secure){
      $sock = @fsockopen("ssl://".$host, 443, $errno, $errstr, 30);
    } else {
      $sock = @fsockopen($host, 80, $errno, $errstr, 30);
    }
    
    if (!$sock) {
      $this->errorMessage = "Could not connect (ERR $errno: $errstr)";
      $this->errorCode = "-99";
      ob_end_clean();
      throw new GorillaConnectionException($this->errorMessage, $this->errorCode);
    }

    $response = "";
    fwrite($sock, $payload);
    stream_set_timeout($sock, $this->timeout);
    $info = stream_get_meta_data($sock);
    
    while ((!feof($sock)) && (!$info["timed_out"])) {
      $response .= fread($sock, $this->chunkSize);
      $info = stream_get_meta_data($sock);
    }
    
    if ($info["timed_out"]) {
      $this->errorMessage = "Could not read response (timed out)";
      $this->errorCode = -98;
    }
    
    fclose($sock);
    ob_end_clean();
    
    if ($info["timed_out"]) {
      throw new GorillaTimeoutException($this->errorMessage, $this->errorCode);
    }

    list($throw, $response) = explode("\r\n\r\n", $response, 2);

    if (ini_get("magic_quotes_runtime")) $response = stripslashes($response);

    $serial = unserialize($response);
    
    if ($response && $serial === false) {
      $response = array("error" => "Bad Response.  Got This: " . $response, "code" => "-99");
    } else {
      $response = $serial;
    }
    
    if (is_array($response) && isset($response["error"])) {
      $this->errorMessage = $response["error"];
      $this->errorCode = $response["code"];
      throw new GorillaBadresponseException($this->errorMessage, $this->errorCode);
    }

    return $response;
  }
}
