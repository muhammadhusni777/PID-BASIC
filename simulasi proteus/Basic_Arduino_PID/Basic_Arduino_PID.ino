//PID_control Command variable
float error;
float setpoint;
float kp = 1; //kp
float ki = 0.07; //ki
float kd = 0.0; //kd
float P_control;
float I_control;
float I_windup = 255;
float D_control;
float PID_control;
float Time;
float dt;
float time_prev;
float previous_error;
float saturation = 255;

//output variable
int output_pin = 9;


//input variable
float sensor;
float filter_weight = 0.9;
float filtered_sensor;



void setup() {
  // put your setup code here, to run once:
  pinMode (output_pin, OUTPUT);
  Serial.begin(9600);
  Serial.print("setpoint");
  Serial.print("|");
  Serial.print("filtered_sensor");
  Serial.print("|");
  Serial.print("error");
  Serial.print("|");
  Serial.print("error prev");
  Serial.print("|");
  Serial.print("P_control");
  Serial.print("|");
  Serial.print("I_control");
  Serial.print("|");
  Serial.print("D_control");
  Serial.print("|");
  Serial.print("PID_control");
  Serial.print("|");
  Serial.println("dt");
  
}

void loop() {
  // put your main code here, to run repeatedly:
  /*-----------setpoint-----------*/
  
  //setpoint = 60;

  setpoint = analogRead(A1);
  
  /*-----------read sensor--------*/
  sensor = analogRead(A0);
  //sensor = analogRead(A0);

  /*--------SET FILTER-----------------*/
  filtered_sensor = ((1-filter_weight) * filtered_sensor) + (filter_weight * sensor);
  
  /*-----------error--------------*/
  error = setpoint - filtered_sensor;

  /*-----------PID_control SIGNAL----------*/
  //proportional control
  P_control = kp*error;

  //integral control
  I_control = I_control + (ki * error * dt);
  
  //integral windup
  if (I_control > I_windup){
    I_control = I_windup;
  } else if (I_control < 0){
    I_control = 0;
  }else {
    I_control = I_control; 
  }
  
  //derivative control
  if (dt < 0.000000001){
    dt = 0.000000001;
  }
  D_control = kd * ((error - previous_error)/dt);

  //summing P I D
  PID_control = P_control + I_control + D_control;

  //saturation
  if (PID_control > saturation){
    PID_control = saturation;
  
  //integral windup max value 
    I_windup = saturation - (P_control + D_control);

  } 
  else if (PID_control < 0) {
    PID_control = 0;  
    I_windup = 0;
  }
  else {
    PID_control = PID_control;
    I_windup = saturation;
  }

  //control signal to output_pin;
  analogWrite(output_pin, PID_control);
  //analogWrite(output_pin, 255);


  /*---------ADDITIONAL CODE------------*/
  //TIMER
  time_prev = Time;                            
  Time = millis();                           
  dt = (Time - time_prev) / 1000; 

  
  //DEBUG SERIAL MONITOR
  // /*
  //Serial.print("setpoint : ");
  Serial.print(setpoint);
  Serial.print("|");
  Serial.print(filtered_sensor);
  Serial.print("|");
  Serial.print(error);
  Serial.print("|");
  Serial.print(previous_error);
  Serial.print("|");
  Serial.print(P_control);
  Serial.print("|");
  Serial.print(I_control);
  Serial.print("|");
  Serial.print(D_control);
  Serial.print("|");
  Serial.print(PID_control);
  Serial.print("|");
  Serial.println(dt);
  delay(500);
  //*/
  //Serial.print(filtered_sensor);
  //Serial.print(",");
  //Serial.println(setpoint);
  
  //PREVIOUS ERROR
  previous_error = error;

}
