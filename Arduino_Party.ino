#include <Servo.h>

Servo servo;
int push_power = 2;   //pushbutton
int led_power = 3;    //power indicator

int push;
int state = 0; // LOW
int danceInput;
int danceValue = 33; //min threshold for start dance. (33 "todo calza pollo!")
int danceDelayValue;

// ---------------------- UTILS Functions ------------- //
// Format Serial.print for "Text: val"
void print(char *text, int val){
  Serial.print(text);
  Serial.print(": ");
  Serial.println(val);
}

// ---------------------- SYSTEM Functions ------------- //
// control power functions
void power(){
  push = digitalRead(push_power);
  if (push){    //if click push
      state = 1 - state; //change state
      delay(200);        //estability
      print("Power", state);
  }
  digitalWrite(led_power, state);
   if (state) { // attach/detach servo (on/off)
    servo.attach(9);
   } else {
    servo.detach();
   }
}

// Servo control
void servo_dance(){
  danceInput = analogRead(A0);
  // escalar de 0° -> 60°
  danceInput = map(danceInput,0,512,0,90);
  servo.write(90); //center
  // calculate delay
  danceDelayValue = map(danceInput,0,512,0,danceInput);
  if (danceInput >= 35){
    danceDelayValue += 100; //+100 for stability
    servo.write(danceInput);
    delay(danceDelayValue);
    print("danceInput", danceInput);
    print("danceDelayValue",danceDelayValue);
  };
}


// ------------------------ MAIN -------------------- //

void setup()
{
  Serial.begin(9600);
  // init
  pinMode(push_power,INPUT);
  pinMode(led_power,OUTPUT);
}


void loop()
{
  power();
  servo_dance();
}
// ---------------------------------------------------- //
