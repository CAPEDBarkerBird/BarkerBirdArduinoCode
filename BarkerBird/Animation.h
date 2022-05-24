#ifndef ANIMATION_H
#define ANIMATIN_H

#include "Actions.h"

//This initalizes all the actions the Barker bird can take

SeroAction* BEAK  = new SeroAction();                     //this is the action that allows the BarkerBird to open and close its mouth
SeroAction* FLAP = new SeroAction();                     //this one will makes the BarkerBird flap its wings
SeroAction* NECK_L_R = new SeroAction();          //this one rotats the neck left and right
SeroAction* NECK_U_D = new SeroAction();            //this on rotates the neck up and down
SeroAction* WING_R = new SeroAction();            //this one extend the right wing
SeroAction* WING_L = new SeroAction();            //this one will extend the left wing
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

  {100,   NECK_L_R, 50, 20},
  {0,     NECK_U_D, 50, 20},
  {1000,  SPEAK, 1, 30},
  {1000,  BASE, -80, 100},
  {1000,  NECK_U_D, 25, 25},
  {1000,  FLAP, 100, 25},
  {1000,  WING_L, 100, 25},
  {1000,  WING_R, 100, 25},
  {1000,  BASE, 100, 100},
  {0,     NECK_U_D, 90, 25},
  {100,   NECK_L_R, 50, 30},
  {1000,  NECK_L_R, 10, 40},
  {1000,  WING_L, 0, 25},
  {1000,  WING_R, 0, 25},
  {1000,  FLAP, 0, 25},
  {0,     NECK_U_D, 25, 30},
  {1500,  NECK_L_R, 50, 40},
  {0,     NECK_U_D, 50, 30},
  {1000,  BASE, 0, 100}
 
};




#endif
