<?php

function gorilla_general_settings() {
  $form = array();
   
  $form['gorilla_api'] = array(
    '#type' => 'fieldset',
    '#title' => t('Mailchimp API'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  
  $form['gorilla_api']['gorilla_api_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Mailchimp API key'),
    '#size' => 60,
    '#maxlength' => 255,
    '#default_value' => variable_get('gorilla_api_key', ''),
  );
   
	return system_settings_form($form);
}