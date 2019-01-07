/*Distance measure*/
/* R.Pahlevan*/
/*BOM: Arduino UNO + LED + Push Button+Resistor+ Ultrasonic Sensor*/

// pin configuratiuon section
#define VCC_PIN 13 // input voltage from arduino Uno
#define Trigger 10 // ultrasonic trigger pin
#define Echo 11 // ultra sonic echo pin
#define LED_PIN 12 // LED pin
#define SWITCH_PIN 8 // push button pin

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
  Serial.begin(9600);
  pinMode(VCC_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(SWITCH_PIN, INPUT);
  pinMode(Trigger, OUTPUT);
  pinMode(Echo,INPUT);
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
  Serial.print("state: ");
  Serial.println(state);
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
    
    delay(1000);
   
    digitalWrite(LED_PIN, LOW);
    delay(200); // Wait for 1000 millisecond(s)
  }
  PREVIOUS_STATUS=CURRENT_STATUS;
}