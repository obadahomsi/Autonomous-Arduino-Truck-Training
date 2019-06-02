#include <Servo.h> //servo library
#include <IRremote.h>
#define P 16761405 //right
#define S 16712445 //okay
#define UNKNOWN_P 553536955
#define UNKNOWN_S 3622325019

Servo myservo; // create servo object to control servo
int RECV_PIN = 12;
int Echo = A4;  
int Trig = A5; 
int in1 = 6;
int in2 = 7;
int in3 = 8;
int in4 = 9;
int ENA = 5;
int ENB = 11;
int ABS = 30;
int rightDistance = 0,leftDistance = 0,middleDistance = 0 ;
char receivedChar;
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long val;
boolean newData = false;
// Serial.println(receivedChar);
void recvOneChar() {
 if (Serial.available() > 0) {
 receivedChar = Serial.read();
 newData = true;
 }
}


void _mForward()
{
 digitalWrite(ENA,HIGH);
 digitalWrite(ENB,HIGH);
  digitalWrite(in1,HIGH);//digital output
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
}

void _mBack()
{
 digitalWrite(ENA,HIGH);
  digitalWrite(ENB,HIGH);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
}

void _mleft()
{
 analogWrite(ENA,ABS);
  digitalWrite(ENB,HIGH);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW); 
}

void _mright()
{
 analogWrite(ENA,ABS);
  digitalWrite(ENB,HIGH);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
} 
void _mStop()
{
  digitalWrite(ENA,LOW);
  digitalWrite(ENB,LOW);
} 
int Distance_test()   
{
  digitalWrite(Trig, LOW);   
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);  
  delayMicroseconds(20);
  digitalWrite(Trig, LOW);   
  float Fdistance = pulseIn(Echo, HIGH);  
  Fdistance= Fdistance/58;     
  return (int)Fdistance;
}  
 /*Ultrasonic distance measurement Sub function*/
/*int Distance_test()   
{
  int uS = sonar.ping();
  float uSf = sonar.convert_cm(uS);
  return (int)uSf;
}*/

void ServoSwerl()
{
  float distances [17];
  int i;
  for( i=0;i<17;i++){
    if (i==0){
      myservo.write(10);
      delay(300);
      }
    else {
      int y = 10 + i*10;
      myservo.write(y);
    }  
    delay(100);
    distances [i] = Distance_test();
    Serial.println(distances[i]);
    Serial.flush();
}
delay(1000);
}
void showNewData() {
 if (newData == true) {
  if(receivedChar=='a'){
     _mForward(); //very forward
     delay(200);
     _mStop();}
             
     else if(receivedChar=='b'){
              _mForward(); //forward
              delay(100);
              _mStop();
     }
     else if(receivedChar=='c'){ 
              _mleft(); //very left
              delay(200);
              _mStop(); 
     }
    else if(receivedChar=='d'){
              _mleft(); //left
              delay(100);
              _mStop();
    }
   else if(receivedChar=='e'){ 
              _mright(); //very right
              delay(200);
              _mStop();
   }
    else if(receivedChar=='f'){ 
              _mright(); //right
              delay(100);
              _mStop();
    } 
    else if(receivedChar=='g'){ 
              ServoSwerl();
              delay(3.0);
    }
    
  }
 newData = false;
 }

void setup() {
  // put your setup code here, to run once:
myservo.attach(3);// attach servo on pin 3 to servo object
  Serial.begin(9600);    
  pinMode(Echo, INPUT);    
  pinMode(Trig, OUTPUT);  
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  _mStop();
  irrecv.enableIRIn();
}

void loop() {
 recvOneChar();
 showNewData();
 if(irrecv.decode(&results)){
    val = results.value;
    irrecv.resume();
    switch(val){
      case P: 
      case UNKNOWN_P: Serial.println(788);Serial.flush();break;
      case S: 
      case UNKNOWN_S: Serial.println(677);Serial.flush(); break;
      default:break;
      }
  }
 }
 
 
 
