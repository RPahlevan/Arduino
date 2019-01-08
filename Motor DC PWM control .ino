
//Motor A
#define inputPin1 10    // Pin 15 of L293D IC
#define inputPin2 11    // Pin 10 of L293D IC
//Motor B
#define inputPin3 9   // Pin  7 of L293D IC
#define inputPin4 8   // Pin  2 of L293D IC

//Motor A speed control
#define PWMPin1 6      // PWM pin control for MOTOR A
#define PWMPin2 5    // PWM pin control for MOTOR A

void setup() 
{
    pinMode(inputPin1, OUTPUT);
    pinMode(inputPin2, OUTPUT);
    pinMode(inputPin3, OUTPUT);
    pinMode(inputPin4, OUTPUT);
  pinMode(PWMPin1,OUTPUT);
  pinMode(PWMPin2,OUTPUT);
  
}

void loop() 
{
  analogWrite(PWMPin1, 127); // spin with 50% of the power
  analogWrite(PWMPin2, 127); // spin with 50% of the power
  digitalWrite(inputPin1, HIGH);
    digitalWrite(inputPin2, LOW);
    digitalWrite(inputPin3, HIGH);
    digitalWrite(inputPin4, LOW);  
}