/*Smart Car*/
/* R.Pahlevan*/
/*BOM: Arduino UNO + LED + Push Button+Resistor+ Ultrasonic Sensor*/
/*two DC motor(less than 7 volts),Motor dirverL2938,battery(9v)*/
/*Software Related elements: Interrputs, Multithread, ADC, DAC, GPIO*/ 


// pin configuratiuon section
// Arduino output
#define VCC_PIN 13 // input voltage from arduino Uno

//sensor (ultrasonic) pin configuration 
#define Trigger 4 // ultrasonic trigger pin
#define Echo 7 // ultra sonic echo pin

// LED configuiration
#define LED_PIN 3 // LED pin

// Switch pin configuration
#define SWITCH_PIN 2 // make a pin 2 as a switch pin

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
volatile uint8_t state=0;

//Variable section for Ultrasonic sensor
float Ping_time=0.0; // a variable to calculate the distance to obstacle
const float Speed_Of_Sound= 767.269;// speed of sound in miles per hour(mph) at 25 degree(c)
float Distance=0.0;

//Functions prototype
float Distance_Sensor(void);
void Keep_Straight(void);
void Spin(void);
void React(void);

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
  
  attachInterrupt(0, React, RISING);// make pin 2 ready for interrupt 
}

void loop()
{

  digitalWrite(VCC_PIN, HIGH); 
  // system will start to work after the push button pressed
  // at this configuration system will turn on/off as soon as push button pressed
    if(state==1){
    
    //LED section
    // LED will start to blink after the system start to work
    digitalWrite(LED_PIN, HIGH);
    delay(20); // Wait for 20 millisecond(s)
      
    // ultrasonic sensor section
     Distance=Distance_Sensor();
    
    //MOTOR Section
    if(Distance<20)
    {
       Spin();
       delay(100);
    }
    else
    {
       Keep_Straight();
    } 
    delay(100);
    
    //Make the LED off  
    digitalWrite(LED_PIN, LOW);
    delay(200); // Wait for 200 millisecond(s)
  }
  //PREVIOUS_STATUS=CURRENT_STATUS;
}

// interrupt function for make the system on or off 
void React(void)
{
  state=!state;
}

// This function will make the Robot to go forward.
// both motors will work at 100% of the power.
void Keep_Straight(void)
{
        digitalWrite(inputPin1, HIGH);
        digitalWrite(inputPin2, LOW);
        digitalWrite(inputPin3, HIGH);
        digitalWrite(inputPin4, LOW);
}

//Spin around
//This function wil make the robot to spin around 
//Spining will take place in 50% of the power

void Spin(void)
{
        analogWrite(PWMPin1, 127); // spin with 50% of the power
        analogWrite(PWMPin2, 127); // spin with 50% of the power
        
        // make the robot car to spin around by sending negative signal to motor driver second leg
        digitalWrite(inputPin1, HIGH);
        digitalWrite(inputPin2, LOW);
        digitalWrite(inputPin3, LOW);
        digitalWrite(inputPin4, HIGH);
        delay(200);
}

// Ultrasonic sensor function
// At this function distance to obstacle will be measured, and the value will be returned to the main function
float Distance_Sensor()
{
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
    
    //Serial.print("Distance: ");
    //Serial.println(Distance);
  return Distance;
}