// initial library
#include <Servo.h>

//define macro for the project
#define Pot_Pin A0 // potentiameter pin
#define Servo_Pin 9 // servo pin
#define wait 20 // wait time
//initialise object for servo class
Servo servo;

//global variable
volatile float Pot_Val=0;
void setup()
{
  Serial.begin(9600);// initialise 9600 baud rate for UART connection to monitor
  pinMode(Pot_Pin,INPUT);//make the potentiameter(pin A0) as an input
  servo.attach(Servo_Pin);//make a pin 9 connect to servo class(attach variable)
}

void loop()
{
  Pot_Val=analogRead(Pot_Pin);
  //Serial.println(Pot_Val);
  float position;
  position=(0.160/0.1023)*Pot_Val+20;//make position adjusted by potentiameter
  // there is linear relation between position and potentiameter value.
  // potentiameter can change from 0 to 1023(10 byte).
  // servo in my case can change it's position from 20 to 160 degree
    servo.write(position);
    delay(wait);
}