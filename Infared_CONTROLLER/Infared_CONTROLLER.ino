

/*
 Example sketch for the PS4 Bluetooth library - developed by Kristian Lauszus
 For more information visit my blog: http://blog.tkjelectronics.dk/ or
 send me an e-mail:  kristianl@tkjelectronics.com
 */

#include <IRremote.h>
#include <Servo.h>
#include <Stepper.h>


const int RECV_PIN = 7;
//#define pwm      3
// Motor direction pin


#define lpwm1      6
#define lpwm2      5
#define pwm1      9
#define pwm2     10


// Variable to represent PWM value
int pwm_value = 0; 
int pwm_value2 = 0; 

IRrecv irrecv(RECV_PIN);
decode_results results;




Servo myservo2;
Servo myservo1;// create servo object to control a servo
// twelve servo objects can be created on most boards

Stepper myStepper1(2048, 1, 3, 2, 4);
Stepper myStepper2(2048, 1, 3, 2, 4);

int pos = 0;    // variable to store the servo position
int led1 = A2;
int led2 = A3;
int led3 = A4;
int count = 0;
//int old = 0;

unsigned long key_value = 0;





void setup() {
  Serial.begin(115200);
  // Define Pins
  pinMode(pwm1,OUTPUT);
  pinMode(pwm2,OUTPUT);
  pinMode(lpwm1,OUTPUT);
  pinMode(lpwm2,OUTPUT);
  
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);

  irrecv.enableIRIn();
  Serial.println("recieved");
  
  

  myservo1.attach(A0);
  myservo2.attach(A1);
  // set the speed at 60 rpm:
  myStepper1.setSpeed(13);
  myStepper2.setSpeed(13);

}


void loop() {
  


  
   
 if (irrecv.decode(&results)){

  


  
  if(results.value == 0xFFFFFFFF){
    irrecv.resume();
  }

  Serial.println(results.value,HEX);

  if (results.value==0xFF906F){ 
         pwm_value+=50;
         pwm_value2+=50;
         
        if(pwm_value>255)   {   
           pwm_value= 255; 
         }
        else if(pwm_value<0){
           pwm_value= 0; 
         }

    Serial.println(pwm1);
     analogWrite(pwm1,pwm_value);
     
      if(pwm_value2>255)   {   
           pwm_value2= 255; 
        }
      else if(pwm_value2<0){
        pwm_value2= 0; 
      }

     analogWrite(pwm2,pwm_value2);

            
           
    }
  

     if (results.value==0xFFA857){ 
         pwm_value-=50;
         pwm_value2-=50;
         
    if(pwm_value>255)   {   
     pwm_value= 255; 
    }
   else if(pwm_value<0){
     pwm_value= 0; 
   }

     analogWrite(pwm1,pwm_value);
     
      if(pwm_value2>255)   {   
     pwm_value2= 255; 
    }
   else if(pwm_value2<0){
     pwm_value2= 0; 
   }

     analogWrite(pwm2,pwm_value2);

            
           
    }

   if (results.value==0xFF22DD){ 
       Serial.print(F("lift"));
      analogWrite(lpwm1,175);
      analogWrite(lpwm2,175);
    }

   


    
      if (results.value==0xFF52AD) {
        if(count==0){
        Serial.print(F("led1"));
         digitalWrite(led1, HIGH); 
        }
         if(count==1){
        Serial.print(F("led2"));
         digitalWrite(led2, HIGH); 
        }
         if(count==2){
        Serial.print(F("led3"));
         digitalWrite(led3, HIGH);
        }
      }
     

 if (results.value == 0xFF6897) {
        
          Serial.print(F("\r\nSmall"));
           myStepper1.step(50);
           myStepper2.step(50);
         
       
        
      } if (results.value == 0xFF5AA5) {
        Serial.print(F("\r\n90"));
           myStepper1.step(512);
           myStepper2.step(512);
          
      } if (results.value == 0xFF4AB5) {
        Serial.print(F("\r\n180"));
           myStepper1.step(1024);
          myStepper2.step(1024);
           
      } if (results.value == 0xFF10EF) {
        Serial.print(F("\r\n-90"));
           myStepper1.step(-512);
           myStepper2.step(-512);
      }

 

      if (results.value == 0xFF42BD){
        Serial.print(F("\r\nServo"));
         
         for (pos = 0; pos <= 90; pos += 1) { // goes from 180 degrees to 0 degrees
          myservo2.write(pos);              // tell servo to go to position in variable 'pos'
                                       // waits 15ms for the servo to reach the position
        }
      }
      if (results.value == 0xFF7A85){
        Serial.print(F("\r\nServo"));
         
         for (pos = 0; pos <= 90; pos += 1) { // goes from 180 degrees to 0 degrees
          myservo1.write(pos);              // tell servo to go to position in variable 'pos'
                                 // waits 15ms for the servo to reach the position
        }
        
      }

      if (results.value == 0xFFA25D){
      Serial.print(F("\r\nPower"));
        analogWrite(pwm1,0);
         analogWrite(pwm2,0);
         analogWrite(lpwm1,0);
         analogWrite(lpwm2,0);
    
        
      }
    
    irrecv.resume();
     Serial.print(F("\r\nResume"));
    
    }
  }
