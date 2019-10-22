// Declaration of input output pins which are connected to the Ultrasonic sensor and IR sensor

int TriggerPIN1 = 8;  // trigger pin 1 for the 1st ultrasonic sensor on the left
int EchoPIN1 = 9;     // echo pin 1 for the 1st ultrasonic sensor on the left
int TriggerPIN2 = 5;  // trigger pin 2 for the 2nd ultrasonic sensor on the right
int EchoPIN2 = 4;     // echo pin 2 for the 2nd ultrasonic sensor on the right
int ir_sensor1 = 10;  // left ir sensor
int ir_sensor2 = 11;  // right ir sensor
int dc_motor1 = 3;    //  left
int dc_motor2 = 2;    //  motor
int dc_motor3 = 1;    //  right
int dc_motor4 = 0;    //  motor
int led_pin   = 12;   //  indicator LED
int safe_distance = 25; //distance in centi-meters
void setup(){
  pinMode(led_pin, OUTPUT);
  pinMode(ir_sensor1, INPUT);
  pinMode(ir_sensor2, INPUT);
  pinMode(TriggerPIN1,OUTPUT);
  pinMode(EchoPIN2,INPUT);
  pinMode(TriggerPIN2,OUTPUT);
  pinMode(EchoPIN2,INPUT);
  pinMode(dc_motor1, OUTPUT);
  pinMode(dc_motor2, OUTPUT);
  pinMode(dc_motor3, OUTPUT);
  pinMode(dc_motor4, OUTPUT);
  Serial.begin(9600); 
  }

void loop(){  
  digitalWrite(TriggerPIN1,LOW);
  delayMicroseconds(2);
  digitalWrite(TriggerPIN1,HIGH);
  delayMicroseconds(2);
  digitalWrite(TriggerPIN1,LOW);

  long timedelay = pulseIn(EchoPIN1,HIGH);
  int distance1 = 0.0343 * (timedelay/2);

  delayMicroseconds(2);

  digitalWrite(TriggerPIN2,LOW);
  delayMicroseconds(2);
  digitalWrite(TriggerPIN2,HIGH);
  delayMicroseconds(2);
  digitalWrite(TriggerPIN2,LOW);

  long td = pulseIn(EchoPIN2,HIGH);
  int distance2 = 0.0343 * (td/2);
  
  Serial.print("Sensor 1 : ");
  Serial.println(distance1);
  Serial.print("Sensor 2 : ");
  Serial.println(distance2);
  Serial.println(" ");
  delay(2000);
// condition for blind-spot
// if distance between two cars less than 25cm generate an alert for the driver
  if (distance1 <= safe_distance and distance2 <= safe_distance){
    Serial.println("vehicles approaching from both sides");
    digitalWrite(dc_motor1,HIGH);
    digitalWrite(dc_motor2, LOW);
    digitalWrite(dc_motor3,HIGH);
    digitalWrite(dc_motor4, LOW);
    digitalWrite(led_pin, HIGH);
   }
   else if (distance2 <= safe_distance){
    digitalWrite(dc_motor1,HIGH);
    digitalWrite(dc_motor2, LOW);
    digitalWrite(dc_motor3,HIGH);
    digitalWrite(dc_motor4, LOW);
    Serial.println("vehicle approaching from back left");
    digitalWrite(led_pin, HIGH);    
   }
  else if (distance1 <= safe_distance){
    digitalWrite(dc_motor1,HIGH);
    digitalWrite(dc_motor2, LOW);
    digitalWrite(dc_motor3,HIGH);
    digitalWrite(dc_motor4, LOW);
    Serial.println("vehicle approaching from back right"); 
    digitalWrite(led_pin, HIGH);  
   }
   else if (distance1 > safe_distance and distance2> safe_distance){
    Serial.println("No threats from behind");
    digitalWrite(dc_motor1,LOW);
    digitalWrite(dc_motor2, HIGH);
    digitalWrite(dc_motor1,LOW);
    digitalWrite(dc_motor2, HIGH);
    digitalWrite(led_pin, LOW);
   }

   // for vehicles coming from sideways
   if (digitalRead(ir_sensor1) == 1){
    Serial.println("Vehicle coming from left");
    digitalWrite(led_pin, HIGH);
   }
    if (digitalRead(ir_sensor2) == 1){
    Serial.println("Vehicle coming from right");
    digitalWrite(led_pin, HIGH);
   }
}
