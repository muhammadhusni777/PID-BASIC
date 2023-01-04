
//output variable
int output_pin = 9;
float error;

//input variable
float setpoint;
float sensor;

void setup() {
  
  Serial.begin(9600);

  pinMode(output_pin, OUTPUT);
  /*--- header -----*/
  Serial.print("setpoint |");
  Serial.println("sensor");
}


void loop() {
  /*-----------1. setpoint-----------*/
  setpoint = 60;
  
  /*-----------2. read sensor--------*/
  sensor = analogRead(A0);

  /*--------3.error -----------------*/
  error = setpoint - sensor;

  /*-----------4. on off control--------------*/
  if (error > 0){
    digitalWrite(output_pin, HIGH);
  } else{
    digitalWrite(output_pin, LOW);
  }

  
  Serial.print(setpoint);
  Serial.print("| ");
  Serial.println(sensor);
  delay(500);



}
