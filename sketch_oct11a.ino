/*
Serial Communication Module  for xBee
latest update : 18/09/10
*/

#include <Arduino.h>
#include "Comunication.h"

Communication::Communication(){
  // all initializations go into setup function
  last_com = millis();
}

void Communication::Com_setup(){
  Serial.begin(SERIAL_RATE);
  for(byte i = 0; i < DATA_NUM; i++){
     data[i] = 0;
  }
}

bool Communication::CheckConnected(){
    if(millis() - last_com > MAX_CONNECTED_TIME) return false;
  return true;
}

bool Communication::CheckReceivedData() {
  if (Serial.available() < 2) return false;

  byte upper_value = (byte)Serial.read();
  byte lower_value  = (byte)Serial.read();

  byte upper_check = upper_value  / 128;
  byte lower_check = lower_value  / 128;

  byte data_kind = upper_value / 4;
  data_kind = data_kind  % 16;

  if(upper_check == 0) return false;
  if(lower_check == 1) return false;
  if(data_kind > DATA_NUM) return false;

  byte receivedData = (upper_value % 4) * 64;  //(upper_value % 4) <<6
  receivedData += lower_value % 64;

  data[data_kind] = receivedData;
  return true;
}

byte Communication::RecieveManyData(){
  byte data_num_in_buffer = Serial.available() / 2;
  for( int i = 0; i < min(data_num_in_buffer, MAX_RECEIPABLE_DATA_NUM); i++){
      CheckReceivedData();
  }
  return data_num_in_buffer;
}


void Communication::ClearBuffer(){
  while(Serial.available() > 1){
    Serial.read();
  }
}

void Communication::SendOneData(byte kind) {
  /*kind must be following int:
   0 =< kind =< 16*/ 
  if(SendCounter == 0) SendCounter = 1;
  if(SendCounter == 1) SendCounter = 0;
  
  byte upper_byte = kind * 4 + 128 + SendCounter * 32;  //(kind-1)  << 2
  
  upper_byte += data[kind] / 64;
  byte lower_byte = data[kind] % 64 + SendCounter * 32;
  
  Serial.write(upper_byte);
  Serial.write(lower_byte);  
}

byte Communication::getCommand() {
  return data[COMMAND];
}
