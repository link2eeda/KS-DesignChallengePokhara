#include<Servo.h>
Servo myservo;
const int trigPin=2;    
const int echoPin=4;          
const int vehicleCapacity=30;     
#define led 8
Servo gate;

long tmeduration;
int distance;
int currentoccupancy;



void setup() {

  myservo.attach(9);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(led,OUTPUT);
  Serial.begin(9600);

  gate.attach(9);
  
  

}

void loop() {
  //ultra sonic sensor

  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
   digitalWrite(trigPin,LOW);

   long t =pulseIn(echoPin,HIGH);
   long cm=t /29 / 2;

   Serial.print(cm);
Serial.println("cm");

//led
  if (cm<=19){
    digitalWrite(led,HIGH );

  }     

else{
  digialWrite(led,LOW);
}  
tmeduration=pulseIn(echoPin,HIGH);
distance=(0.034*tmeduration)/2;
if(currentoccupancy<vehicleCapacity)
 digitalWrite(7,HIGHdelaySeconds(3);
digitalWrite(7,LOW); 

{
if(distance<=20){
  
  myservo.write(90);
  }
  else{
    digitalWrite(6,HIGH);
    delaySeconds(3);
    digitalWrite(6,LOW);
        myservo.write(0);}
  
  Serial.print("distance:");
    Serial.println(distance);
  
    delay(1);
  

}
currentoccupancy++;
}