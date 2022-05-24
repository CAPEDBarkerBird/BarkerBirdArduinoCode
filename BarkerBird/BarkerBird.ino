
#include "Actions.h"
#include "Animation.h"

 




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
  BEAK->init(BEAK_PIN , BEAK_SLOP, BEAK_INTERCEPT, BEAKdefault); 
  NECK_U_D->init(NECK_U_D_PIN,NECK_U_D_SLOP, NECK_U_D_INTERCEPT, NECK_U_Ddefault);
  NECK_L_R->init(NECK_L_R_PIN, NECK_L_R_SLOP, NECK_L_R_INTERCEPT, NECK_L_Rdefault);
  FLAP->init(FLAP_PIN,FLAP_SLOP, FLAP_INTERCEPT,FLAPdefault );
  WING_R->init(WING_R_PIN,WING_R_SLOP, WING_R_INTERCEPT,WING_R_DEFALT);
  WING_L->init(WING_L_PIN,WING_L_SLOP, WING_L_INTERCEPT,WING_L_DEFALT);
  
// BASE->init(BAS_DIRECTION_PIN, BAS_STEP_PIN, BASEdefault);
  
  delay (2000);
  StartTime = millis();
  
}


int AudioFeedBack = 7;  // analog pin used to connect the potentiometer
int SpeachVal;    // variable to read the value from the analog pin

//used to see when all the actions are done
int check_done(){
return( // FLAP->isDone()             ||
//           NECK_L_R->isDone() ||
//           BASE->isDone()             ||
//          NECK_U_D->isDone()   ||
         WING_R->isDone());
//          WING_L->isDone());
          //SPEAK->isDone()           ||
         
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

//   speach();

   
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
