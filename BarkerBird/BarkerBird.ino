
#include "Actions.h"
#include "Animation.h"

//This initalizes all the actions the Barker bird can take 

SeroAction* BEAK = new SeroAction();                     //this is the action that allows the BarkerBird to open and close its mouth
SeroAction* FLAP = new SeroAction();                     //this one will makes the BarkerBird flap its wings
SeroAction* NECK_HORIZONTAL = new SeroAction();          //this one rotats the neck left and right
SeroAction* NECK_VERTICAL = new SeroAction();            //this on rotates the neck up and down
SeroAction* R_WING_EXTEND = new SeroAction();            //this one extend the right wing
SeroAction* L_WING_EXTEND = new SeroAction();            //this one will extend the left wing
AudioAction* SPEAK = new AudioAction();                  //this one will make the BarkerBird play a pre recorded voice live
StepperAction* BASE = new StepperAction();               //this one will move the base the BarkerBird sits on left and right

//to use any of the actions above you will call the by the all upercase letters for example FLAP


//This Animation struct is the format in with each animation will be called 

struct Animation
{
  unsigned long ActionTime; // Number of milliseconds after last animation or starts to do this action
  Action* ActionToAct;      // Which Action is it?
  int PositionTrack;        // Position form 0-100 or track number (for the base - numbers are CCW and + are clockwise
  int SpeedValume;          // Speed or Valume 0-100
};


//the animations will be created bellow by fallowing the animation format above 
//for example if I wanted the BarkerBird to flap its wing to 50% 100 milliseconds after the the last action at 20% speed 
//I would right {100, FLAP, 50, 20}
//  {time, thing proforming the action, move to, howFast }, 

Animation Actions[] = {

  {100,   NECK_HORIZONTAL, 50, 20},
  {0,     NECK_VERTICAL, 50, 20},
  {1000,  SPEAK, 1, 2},
  {1000,  NECK_VERTICAL, 25, 25},
  {1000,  FLAP, 100, 25},
  {1000,  BASE, 100, 100},
  {10000,  BASE, -80, 100},
  {0,     NECK_VERTICAL, 90, 25},
  {100,   NECK_HORIZONTAL, 50, 30},
  {1000,  NECK_HORIZONTAL, 10, 40},
  {1000,  FLAP, 0, 25},
  {0,     NECK_VERTICAL, 25, 30},
  {1500,  NECK_HORIZONTAL, 50, 40},
  {0,     NECK_VERTICAL, 50, 30}

 
};

//this will will let the BarkerBird know how many actions are in the amination
const byte numberOfActions = sizeof Actions / sizeof Actions[0];

//used to index the animations
int index = 0;

//sets the start time
unsigned long StartTime;

//sets up the inital all the moters and moves to the starting location
void setup()
{
  Serial.begin(115200);
 
  SPEAK->init(&Serial2,9600);
  BEAK->init(BEAK_PIN , BEAK_PIN_SLOP, BEAK_PIN_INTERCEPT, BEAKdefault); 
  NECK_VERTICAL->init(NECK_VERTICAL_PIN,NECK_VERTICAL_SLOP, NECK_VERTICAL_INTERCEPT, NECK_VERTICALdefault);
  NECK_HORIZONTAL->init(NECK_HORIZONTAL_PIN, NECK_HORIZONTAL_SLOP, NECK_HORIZONTAL_INTERCEPT, NECK_HORIZONTALdefault);
  FLAP->init(FLAP_PIN,FLAP_SLOP, FLAP_INTERCEPT,FLAPdefault );
  R_WING_EXTEND->init(R_WING_EXTEND_PIN,R_WING_EXTEND_SLOP, R_WING_EXTEND_INTERCEPT,R_WING_EXTEND_DEFALT);
  L_WING_EXTEND->init(L_WING_EXTEND_PIN,L_WING_EXTEND_SLOP, L_WING_EXTEND_INTERCEPT,L_WING_EXTEND_DEFALT);
  
  BASE->init(BAS_DIRECTION_PIN, BAS_STEP_PIN, BASEdefault);
  
  delay (2000);
  StartTime = millis();
  
}


int AudioFeedBack = 7;  // analog pin used to connect the potentiometer
int SpeachVal;    // variable to read the value from the analog pin

//used to see when all the actions are done
int check_done(){
  return( //FLAP->isDone()          ||
          NECK_HORIZONTAL->isDone() ||
           BASE->isDone()           ||
          //SPEAK->isDone()           ||
          NECK_VERTICAL->isDone() );
         // R_WING_EXTEND->isDone()   || 
         // L_WING_EXTEND->isDone()   ||
         // SPEAK->isDone()           ||
         //;
}

void speach(){
    //if the MP3 Player is not assleep the set BEAK to position based on amplatude else set to the defalt position
   // if(SPEAK->isDone()){
  
      SpeachVal = analogRead(AudioFeedBack);              // reads the value of the potentiometer (value between 0 and 1023)
      //Serial.println(SpeachVal);
      SpeachVal = map(SpeachVal, 0, 1023, 0, 100);       // Should go away after testing scale it to use it with the servo (value between 0 and 180)
      BEAK->doAction(SpeachVal, 25);
  //  } else {
  
    //  BEAK->doAction(BEAKdefault, 25);
   // }
}

//the main loop this happens as long as the bird is activated
void loop() 
{

   speach();

   
    if(index < numberOfActions){
      
        if(millis()-StartTime > Actions[index].ActionTime){                                                 // if enugh time hase passed start the new action
            Actions[index].ActionToAct->doAction(Actions[index].PositionTrack, Actions[index].SpeedValume); // this starts the action
            StartTime = millis();                                                                           //sets the time realative to the last action
            index++;
        }                                            
                                                                                                             // if the animation is complet start over
    } else if (!check_done()){                                                                               //cheack if the animations should start over
             StartTime = millis();
             index = 0; 
             
    }
    BASE->run();                                                                                             // if the base would move move it
}
