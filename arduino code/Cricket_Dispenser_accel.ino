/*
 * RAMPS 1.4: pin for steppers 1, 2, 3, 4
 */
#define X_STEP_PIN         54
#define X_DIR_PIN          55
#define X_ENABLE_PIN       38
#define X_MIN_PIN           3
#define X_MAX_PIN           2

#define Y_STEP_PIN         60 
#define Y_DIR_PIN          61 
#define Y_ENABLE_PIN       56 

#define Z_STEP_PIN         46
#define Z_DIR_PIN          48
#define Z_ENABLE_PIN       62
#define Z_MIN_PIN          18
#define Z_MAX_PIN          19

#define E_STEP_PIN         26
#define E_DIR_PIN          28
#define E_ENABLE_PIN       24

/*
 * Cricket specific numbers
 */
#define num_of_chambers   8
#define full_steps_per_rotation 100 //1.8 deg per full step, 360/1.8=200
//3.942 diameter inside of ridge, 1.875in diameter inside of ridge
#define pulley_ratio (3.942/1.875) //motor is 1/2 the size of chamber
#define microstepping 8 //microstepping mode
#define total_steps_for_rotation  (full_steps_per_rotation*pulley_ratio*microstepping)


#define cricket_per_chamber 7         

#define cricket_pin         11

/*
 * Setup for stepper motors and the different chambers
 */
//#include <Stepper.h>
#include <AccelStepper.h> //ManageLibraries > AccelStepper
 
const int turn = total_steps_for_rotation/num_of_chambers;//one turn's steps is total steps / number of chambers
//Stepper cricketFeeder[4] = { Stepper(200, X_STEP_PIN, X_DIR_PIN),
//                            Stepper(200, Y_STEP_PIN, Y_DIR_PIN),
//                            Stepper(200, Z_STEP_PIN, Z_DIR_PIN),
//                            Stepper(200, E_STEP_PIN, E_DIR_PIN)};

//AccelStepper stepper[] = {AccelStepper (1, 2, 5), AccelStepper (1, 3, 6)};

AccelStepper cricketFeeder[4] =
  { 
  AccelStepper(AccelStepper::DRIVER, X_STEP_PIN, X_DIR_PIN),   //1
  AccelStepper(AccelStepper::DRIVER, Y_STEP_PIN, Y_DIR_PIN),   //2
  AccelStepper(AccelStepper::DRIVER, Z_STEP_PIN, Z_DIR_PIN),   //3
  AccelStepper(AccelStepper::DRIVER, E_STEP_PIN, E_DIR_PIN)    //4
  };

int turnCounter[4] = {0,
                      0,
                      0,
                      0};
bool enabled = HIGH;

void setup() {
  //initializes the 1 chamber's stepper motor
  pinMode(X_STEP_PIN  , OUTPUT);
  pinMode(X_DIR_PIN    , OUTPUT);
  pinMode(X_ENABLE_PIN    , OUTPUT);
  digitalWrite(X_ENABLE_PIN    , LOW);
  
  //initializes the 2 chamber's stepper motor
  pinMode(Y_STEP_PIN  , OUTPUT);
  pinMode(Y_DIR_PIN    , OUTPUT);
  pinMode(Y_ENABLE_PIN    , OUTPUT);
  digitalWrite(Y_ENABLE_PIN    , LOW);

  //initializes the 3 chamber's stepper motor
  pinMode(Z_STEP_PIN  , OUTPUT);
  pinMode(Z_DIR_PIN    , OUTPUT);
  pinMode(Z_ENABLE_PIN    , OUTPUT);
  digitalWrite(Z_ENABLE_PIN    , LOW);

  //initializes the 4 chamber's stepper motor
  pinMode(E_STEP_PIN  , OUTPUT);
  pinMode(E_DIR_PIN    , OUTPUT);
  pinMode(E_ENABLE_PIN    , OUTPUT);
  digitalWrite(E_ENABLE_PIN    , LOW);
  
//initializes the pulse signal for the entire system
   pinMode(cricket_pin, OUTPUT);


   Serial.begin(9600);
   Serial.println("Program Start: enter t or r to turn the steppers 1/3 and 2/4 respectively. \nPress 1,2,3,4 to increment the respective motors a small amount. \nPress d to disable steppers, e to enable steppers.");
   Serial.print("Steps per turn: ");
   Serial.println(turn);
   delay(200);
}

void loop() {


  char input = Serial.read();         //reads serial input for what to do next
  if(input=='d'){
    enabled = LOW;
    digitalWrite(X_ENABLE_PIN    , HIGH);
    digitalWrite(Y_ENABLE_PIN    , HIGH);
    digitalWrite(Z_ENABLE_PIN    , HIGH);
    digitalWrite(E_ENABLE_PIN    , HIGH);
    turnCounter[0]=0;
    turnCounter[1]=0;
    Serial.println("Steppers disabled, resetting chambers");
  }
  if(input=='e'){
    enabled = HIGH;
    digitalWrite(X_ENABLE_PIN    , LOW);
    digitalWrite(Y_ENABLE_PIN    , LOW);
    digitalWrite(Z_ENABLE_PIN    , LOW);
    digitalWrite(E_ENABLE_PIN    , LOW);
    Serial.println("Steppers enabled");
  }
  if(input=='t' && enabled == HIGH){
    //Serial.println("t");
    if(turnCounter[0]==cricket_per_chamber){
      Serial.println("t! Chambers 1&3 are fully turned");
    }else{
      turnTask(0);
      Serial.print("t! Turning motors 1&3... Turn ");
      turnCounter[0]++;
      Serial.println(turnCounter[0]);
    }
  }
  if(input=='r' && enabled == HIGH){
    //Serial.println("r");
    if(turnCounter[1]==cricket_per_chamber){
      Serial.println("r! Chambers 2&4 are fully turned");
    }else{
      turnTask(1);
      Serial.print("r! Turning motors 2&4... Turn ");
      turnCounter[1]++;
      Serial.println(turnCounter[1]);
    }
 }

// if(input=='1'||input=='2'||input=='3'||input=='4'){
//   //turnIncrement((int) input - 49); //offset by ascii value of number key?
//    Serial.print("incrementing motor ");
//   Serial.println(input);
// }
//}
//
  if(input=='1'||input=='2'||input=='3'||input=='4' && enabled == HIGH){
    Serial.println("turn one chamber");
    if(turnCounter[input]==cricket_per_chamber){
      Serial.println(" Chamber is fully turned");
    }
    else{
      turnOne(input);
      Serial.print("Turning motor ");
      Serial.print(input);
      turnCounter[input]++;
      Serial.println(turnCounter[input]);
    }
  }
//void turnTask (int x) {//for normal stepper library
//      sendSignal();
//      cricketFeeder[x].setSpeed(3000);
//      cricketFeeder[x+2].setSpeed(3000);
//      
//      for(int s=0; s<turn/4; s++){
//        cricketFeeder[x+2].step(-4);
//        cricketFeeder[x].step(-4);
//        delay(10);
//      }
}

void turnTask (int x) {//for accelstepper library
      Serial.println("turntask");
      sendSignal();
      setStepperDefaults(x);
      //Serial.println(turn);
      cricketFeeder[x].setCurrentPosition(0); //set current position as zero
      cricketFeeder[x+2].setCurrentPosition(0); //set current position as zero
      //Serial.println(cricketFeeder[x].distanceToGo());
      cricketFeeder[x].moveTo(turn);
      cricketFeeder[x+2].moveTo(turn);
      //Serial.println(cricketFeeder[x].distanceToGo());
      while(cricketFeeder[x].distanceToGo() > 0)
      {
        cricketFeeder[x].run();
        cricketFeeder[x+2].run();
      }
}

void turnOne (int x){ //turn one motor at a time
      Serial.println("turnOne");
      sendSignal();
      setStepperDefaults(x);
      //Serial.println(turn);
      cricketFeeder[x].setCurrentPosition(0); //set current position as zero
      //Serial.println(cricketFeeder[x].distanceToGo());
      cricketFeeder[x].moveTo(turn);
      //Serial.println(cricketFeeder[x].distanceToGo());
      while(cricketFeeder[x].distanceToGo() > 0)
      {
        cricketFeeder[x].run();
      }
}

void setStepperDefaults(int x){
    cricketFeeder[x].setMaxSpeed(200.0); //200 is default
    cricketFeeder[x+2].setMaxSpeed(200.0); //200 is default,
    cricketFeeder[x].setAcceleration(100.0); //100 is default
    cricketFeeder[x+2].setAcceleration(100.0); //100 is default
}

//void turnIncrement(int x){
//  sendSignal();
//  cricketFeeder[x].setSpeed(10);
//  cricketFeeder[x].step(-10);
//}


/*
 * Sends signal to the main board for logging when a cricket is dropped
 */
void sendSignal (){
    digitalWrite(cricket_pin, HIGH);
    delay(200);
    digitalWrite(cricket_pin, LOW);
}
