String readString;


#include <Wire.h>         




unsigned long message_time;
unsigned long message_time_prev;

int pwm_pin = 9;
int pwm_heat;

void setup() {
  pinMode(pwm_pin, OUTPUT);
  Serial.begin(9600);
 
}





void loop() {
  while (Serial.available()) {
    char c = Serial.read();  
    readString += c; 
    delay(2);  
  }

    if (readString.length() >0) { 
    pwm_heat  = readString.toInt();  
    
 readString=""; 
}

analogWrite(pwm_pin, pwm_heat);

message_time = millis() - message_time_prev;
if (message_time > 100){
  
  Serial.println(analogRead(A0));
  message_time_prev = millis();
  
}

}
