

const int analogInPin = A1;  
const int analogOutPin = 9; 

int pot = 0;       
int outputValue = 0;        

int heater = 0;

void setup() {
 
  Serial.begin(9600);
}

void loop() {

  pot = analogRead(analogInPin);
  
  heater = analogRead(A0); 
  
  outputValue = map(pot, 0, 1023, 0, 255);
  
  analogWrite(analogOutPin, outputValue);
  
  Serial.print("pot = ");
  Serial.print(pot);
  Serial.print("\t output = ");
  Serial.println(heater);


  delay(500);
}
