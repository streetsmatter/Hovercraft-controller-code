

/*
 Example sketch for the PS4 Bluetooth library - developed by Kristian Lauszus
 For more information visit my blog: http://blog.tkjelectronics.dk/ or
 send me an e-mail:  kristianl@tkjelectronics.com
 */

#include <PS4BT.h>
#include <usbhub.h>
#include <Servo.h>
#include <Stepper.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

//#define pwm      3
// Motor direction pin
#define dir      2
//#define dir1      4
#define pwm1      5
#define pwm2     6
//#define dir2      7

// Variable to represent PWM value
int pwm_value = 0; 
int pwm_value2 = 0; 


USB Usb;
USBHub Hub1(&Usb); // Some dongles have a hub inside
BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so

/* You can create the instance of the PS4BT class in two ways */
// This will start an inquiry and then pair with the PS4 controller - you only have to do this once
// You will need to hold down the PS and Share button at the same time, the PS4 controller will then start to blink rapidly indicating that it is in pairing mode
PS4BT PS4(&Btd, PAIR);
//PS4BT PS4(&Btd);

Servo myservo2;
Servo myservo1;// create servo object to control a servo
// twelve servo objects can be created on most boards

Stepper myStepper1(2048, 1, 3, 2, 4);
Stepper myStepper2(2048, 1, 3, 2, 4);

int pos = 0;    // variable to store the servo position
int led1 = 0;
int led2 = 1;
int led3 = 2;
int count = 0;
int old = 0;


// After that you can simply create the instance like so and then press the PS button on the device
//PS4BT PS4(&Btd);

bool printAngle, printTouch;
uint8_t oldL2Value, oldR2Value;

void setup() {
  Serial.begin(115200);
  // Define Pins
  pinMode(pwm1,OUTPUT);
  pinMode(dir,OUTPUT); 
  
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
 
  
  

  myservo1.attach(A0);
  myservo2.attach(A1);
  // set the speed at 60 rpm:
  myStepper1.setSpeed(13);
  myStepper2.setSpeed(13);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); // Halt
  }
  Serial.print(F("\r\nPS4 Bluetooth Library Started"));
  
}
void loop() {
  


  
   
  Usb.Task();

  if (PS4.connected()) {
    if (PS4.getAnalogHat(LeftHatX) > 137 || PS4.getAnalogHat(LeftHatX) < 117 || PS4.getAnalogHat(LeftHatY) > 137 || PS4.getAnalogHat(LeftHatY) < 117 || PS4.getAnalogHat(RightHatX) > 137 || PS4.getAnalogHat(RightHatX) < 117 || PS4.getAnalogHat(RightHatY) > 137 || PS4.getAnalogHat(RightHatY) < 117) {
      Serial.print(F("\r\nLeftHatX: "));
      Serial.print(PS4.getAnalogHat(LeftHatX));
      Serial.print(F("\tLeftHatY: "));
      Serial.print(PS4.getAnalogHat(LeftHatY));
      Serial.print(F("\tRightHatX: "));
      Serial.print(PS4.getAnalogHat(RightHatX));
      Serial.print(F("\tRightHatY: "));
      Serial.print(PS4.getAnalogHat(RightHatY));
    }

    if (PS4.getAnalogButton(L2) || PS4.getAnalogButton(R2)) { // These are the only analog buttons on the PS4 controller
      Serial.print(F("\r\nL2: "));
      Serial.print(PS4.getAnalogButton(L2));
     // pwm_value=PS4.getAnalogButton(L2);
      // Serial.print((pwm_value));
      Serial.print(F("\tR2: "));
      Serial.print(PS4.getAnalogButton(R2));
   
      Serial.print(F("\tPWM: "));
       
          Serial.print(pwm_value);
     
       
    }

  /*  if(pwm_value>255)   {   
     pwm_value= 250; 
    }
   else if(pwm_value<0){
     pwm_value= 0; 
   }

     analogWrite(pwm1,pwm_value); */

     
      
    if (PS4.getAnalogButton(L2) != oldL2Value || PS4.getAnalogButton(R2) != oldR2Value){ 
      oldL2Value = PS4.getAnalogButton(L2);
      oldR2Value = PS4.getAnalogButton(R2);
        Serial.print(F("\tPWM: "));
         pwm_value=PS4.getAnalogButton(R2);
         pwm_value2=PS4.getAnalogButton(L2);
         
    if(pwm_value>255)   {   
     pwm_value= 255; 
    }
   else if(pwm_value<0){
     pwm_value= 0; 
   }

      pwm_value= pwm_value/2;
     analogWrite(pwm1,pwm_value);
     
      if(pwm_value2>255)   {   
     pwm_value2= 255; 
    }
   else if(pwm_value2<0){
     pwm_value2= 0; 
   }

     analogWrite(pwm2,pwm_value2);

            
           
    } 


    if (PS4.getButtonClick(PS)) {
      Serial.print(F("\r\nPS"));
      PS4.disconnect();
    }
    else {
      if (PS4.getButtonClick(TRIANGLE)) {
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
      if (PS4.getButtonClick(CIRCLE)) {
      //  PS4.setRumbleOn(RumbleHigh);
      }
      if (PS4.getButtonClick(CROSS)) {
        Serial.print(F("\r\nCross"));
        PS4.setLedFlash(10, 10); // Set it to blink rapidly
      }
      if (PS4.getButtonClick(SQUARE)) {
        Serial.print(F("\r\nSquare"));
        analogWrite(pwm1,100);
      //  PS4.setLedFlash(0, 0); // Turn off blinking
      }

 if (PS4.getButtonClick(UP)) {
        
          Serial.print(F("\r\nSmall"));
           myStepper1.step(50);
           myStepper2.step(50);
         
       
        PS4.setLed(Red);
      } if (PS4.getButtonClick(RIGHT)) {
        Serial.print(F("\r\n90"));
           myStepper1.step(512);
           myStepper2.step(512);
          
      } if (PS4.getButtonClick(DOWN)) {
        Serial.print(F("\r\n180"));
           myStepper1.step(1024);
          myStepper2.step(1024);
           
      } if (PS4.getButtonClick(LEFT)) {
        Serial.print(F("\r\n-90"));
           myStepper1.step(-512);
           myStepper2.step(-512);
        PS4.setLed(Green);
      }

    /*  if (PS4.getButtonClick(UP)) {
        Serial.print(F("\r\nUp"));
         pwm_value++;
          Serial.print((pwm_value));
       
        PS4.setLed(Red);
      } if (PS4.getButtonClick(RIGHT)) {
        Serial.print(F("\r\nRight"));
        PS4.setLed(Blue);
      } if (PS4.getButtonClick(DOWN)) {
        Serial.print(F("\r\nDown"));
         pwm_value--;
         
        PS4.setLed(Yellow);
      } if (PS4.getButtonClick(LEFT)) {
        Serial.print(F("\r\nLeft"));
        digitalWrite(dir,0);
      
        PS4.setLed(Green);
      }*/

      if (PS4.getButtonClick(L1)){
        Serial.print(F("\r\nServo"));
         
         for (pos = 0; pos <= 90; pos += 1) { // goes from 180 degrees to 0 degrees
          myservo2.write(pos);              // tell servo to go to position in variable 'pos'
                                       // waits 15ms for the servo to reach the position
        }
      }
      if (PS4.getButtonClick(L3)){
        Serial.print(F("\r\nL3"));
        Serial.print(F("\r\nLift fans on"));
        
      }
      if (PS4.getButtonClick(R1)){
        Serial.print(F("\r\nServo"));
         
         for (pos = 0; pos <= 90; pos += 1) { // goes from 180 degrees to 0 degrees
          myservo1.write(pos);              // tell servo to go to position in variable 'pos'
                                 // waits 15ms for the servo to reach the position
        }
      }
      if (PS4.getButtonClick(R3)){
        Serial.print(F("\r\nR3"));
        analogWrite(pwm1,0);
    
        
      }

      if (PS4.getButtonClick(SHARE))
        Serial.print(F("\r\nShare"));
      if (PS4.getButtonClick(OPTIONS)) {
        
      }
      if (PS4.getButtonClick(TOUCHPAD)) {
       Serial.print(F("\r\nLift fans on"));
        
      }

      if (printAngle) { // Print angle calculated using the accelerometer only
        Serial.print(F("\r\nPitch: "));
        Serial.print(PS4.getAngle(Pitch));
        Serial.print(F("\tRoll: "));
        Serial.print(PS4.getAngle(Roll));
      }

      if (printTouch) { // Print the x, y coordinates of the touchpad
        if (PS4.isTouching(0) || PS4.isTouching(1)) // Print newline and carriage return if any of the fingers are touching the touchpad
          Serial.print(F("\r\n"));
        for (uint8_t i = 0; i < 2; i++) { // The touchpad track two fingers
          if (PS4.isTouching(i)) { // Print the position of the finger if it is touching the touchpad
            Serial.print(F("X")); Serial.print(i + 1); Serial.print(F(": "));
            Serial.print(PS4.getX(i));
            Serial.print(F("\tY")); Serial.print(i + 1); Serial.print(F(": "));
            Serial.print(PS4.getY(i));
            Serial.print(F("\t"));
          }
        }
      }
    }
  }
}
