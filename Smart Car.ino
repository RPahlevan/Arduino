/*Samrt Car*/
/* R.Pahlevan*/
/*BOM: Arduino UNO + LED + Push Button+Resistor+ Ultrasonic Sensor*/
/*two DC motor(less than 7 volts),Motor dirverL2938,battery(9v)*/

// pin configuratiuon section
// Arduino output
#define VCC_PIN 13 // input voltage from arduino Uno

//sensor (ultrasonic) pin configuration 
#define Trigger 4 // ultrasonic trigger pin
#define Echo 7 // ultra sonic echo pin

// LED configuiration
#define LED_PIN 3 // LED pin

//Switch configuatiuon
#define SWITCH_PIN 2// push button pin

//Motor A
#define inputPin1 10    // Pin 15 of L293D IC
#define inputPin2 11    // Pin 10 of L293D IC

//Motor B
#define inputPin3 9   // Pin  7 of L293D IC
#define inputPin4 8   // Pin  2 of L293D IC

//Motor A speed control
#define PWMPin1 6      // PWM pin control for MOTOR A
#define PWMPin2 5    // PWM pin control for MOTOR A

//global variable section
volatile unsigned short CURRENT_STATUS;
unsigned short PREVIOUS_STATUS=0;
unsigned short state=0;

//Variable section for Ultrasonic sensor
float Ping_time=0.0; // a variable to calculate the distance to obstacle
const float Speed_Of_Sound= 767.269;// speed of sound in miles per hour(mph) at 25 degree(c)
float Distance=0.0;

void setup()
{
  Serial.begin(9600);// UART for Monitor view
  
  pinMode(VCC_PIN, OUTPUT);//Arduino power output
  pinMode(LED_PIN, OUTPUT);//LED 
  pinMode(SWITCH_PIN, INPUT);//push button
  pinMode(Trigger, OUTPUT);//Ultrasonic sensor
  pinMode(Echo,INPUT);//ultrasonic sensor
  pinMode(inputPin1, OUTPUT);//MOTOR A
  pinMode(inputPin2, OUTPUT);//MOTOR A
  pinMode(inputPin3, OUTPUT);//MOTOR B
  pinMode(inputPin4, OUTPUT);// MOTOR B
  pinMode(PWMPin1,OUTPUT);// PWM for MOTOR A
  pinMode(PWMPin2,OUTPUT);// PWM for MOTOR B
}

void loop()
{
  digitalWrite(VCC_PIN, HIGH); 
  CURRENT_STATUS=digitalRead(SWITCH_PIN);
  
  // system will start to work after the push button pressed
  // at this configuration, the user has to push the button for few milisecond inorder to make the system off
  if (CURRENT_STATUS==1 && PREVIOUS_STATUS==0) {
      if (state == 1)
        state = 0;
    else
      state = 1;
  }
  //Serial.print("state: ");
  //Serial.println(state);
    if(state==1){
    //LED section
    // LED will start to blink after the system start to work
    digitalWrite(LED_PIN, HIGH);
    delay(200); // Wait for 1000 millisecond(s)
    
    // ultrasonic sensor section
    digitalWrite(Trigger, LOW);
    delayMicroseconds(2000);
    digitalWrite(Trigger,HIGH);
    delayMicroseconds(20);
    digitalWrite(Trigger, LOW);
    
    // Reads the echo pin, returns the sound wave travel time in microseconds
    Ping_time=pulseIn(Echo,HIGH);
    //Serial.print("Pingtime: ");
    //Serial.print(Ping_time);
    
    // output has to be change from microsecond to hour
    Ping_time=Ping_time/1000000.0;//change microseconds to seconds
    Ping_time=Ping_time/3600;// chenge from seconds to hours

    // calaculate the distance and convert to inches
    Distance=(Ping_time*Speed_Of_Sound)/2;// divided by two cause the signal will go two ways(round trip)
    Distance=Distance*63360;// convert miles to inches
    Serial.print("Distance: ");
    Serial.println(Distance);
      
    //MOTOR Section
      if(Distance<30)
      {
        analogWrite(PWMPin1, 127); // spin with 50% of the power
        analogWrite(PWMPin2, 127); // spin with 50% of the power
        digitalWrite(inputPin1, HIGH);
        digitalWrite(inputPin2, LOW);
        digitalWrite(inputPin3, LOW);
        digitalWrite(inputPin4, HIGH);
        delay(1200);
      }
      else
      {
        digitalWrite(inputPin1, HIGH);
        digitalWrite(inputPin2, LOW);
        digitalWrite(inputPin3, HIGH);
        digitalWrite(inputPin4, LOW);
      } 
    
      delay(100);
      digitalWrite(LED_PIN, LOW);
      delay(200); // Wait for 1000 millisecond(s)
  }
  PREVIOUS_STATUS=CURRENT_STATUS;
}