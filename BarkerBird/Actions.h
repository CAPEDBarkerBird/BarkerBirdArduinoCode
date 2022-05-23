#ifndef ACTIONS_H
#define ACTIONS_H

#include <VarSpeedServo.h> 
#include "DFRobotDFPlayerMini.h"
#include "AccelStepper.h"

const int BEAK_PIN = 13;
const int NECK_U_D_PIN = 10;
const int NECK_L_R_PIN = 9;
const int FLAP_PIN = 8;
const int BAS_DIRECTION_PIN = 5;
const int BAS_STEP_PIN = 4;
const int WING_R_PIN = 11;
const int WING_L_PIN = 12;

const int STEPPER_CONST = 3;


const int BEAK_INTERCEPT = 1029;
const int FLAP_INTERCEPT = 1500;
const int NECK_U_D_INTERCEPT = 613;
const int NECK_L_R_INTERCEPT = 1094;
const int WING_R_INTERCEPT = 1500;
const int WING_L_INTERCEPT = 1500;

const double BEAK_SLOP = -1.97;
const double FLAP_SLOP = 5;
const double NECK_U_D_SLOP = 15.87;
const double NECK_L_R_SLOP = 13.25;
const double WING_R_SLOP = -4;
const double WING_L_SLOP = 4;

const int BEAKdefault = 1500;
const int FLAPdefault = 1500;
const int NECK_L_Rdefault = 1500;
const int NECK_U_Ddefault = 1500;
const int WING_Rdefault = 1500;
const int BASEdefault = 675;
const int WING_R_DEFALT = 1500;
const int WING_L_DEFALT = 1500;

class Action {
   public :
   virtual void doAction(int pos, int Speed){
    
  }
  virtual int isDone(){
       return 0;
  }
  
};

class SeroAction : public Action{

  private:
    VarSpeedServo MyServo;
    double Slop;
    int intersept;
    int pin;
    int initalPositon;
    int finalPosition;

  public:
    void doAction(int pos, int Speed){
        
        if(pos > 100){ pos = 100; }
        if (pos < 0) { pos = 0; }
        
        this->finalPosition = Slop*pos + intersept;
        MyServo.slowmove(finalPosition ,Speed);
  }

   int isDone(){
     /* retruns 0 if done and nonzer if not */
     return this->MyServo.readMicroseconds() - this->finalPosition;
   }
  int getFinalPosition(){
    return this->finalPosition;
  }
  void setPin(int pin){
    this->pin = pin;
  }
  int getPin(){
    return pin;
  }
  void setSlop(double slop){
    this->Slop = slop;
  }
  double getSlop(){
    return Slop;
  }
  void setIntersept(int intersept){
    this->intersept = intersept;
  }
  int getIntersept(){
    return intersept;
  }
  void setInitalPositon(int intersept){
    this->initalPositon = initalPositon;
  }
  int getInitalPositon(){
    return initalPositon;
  }
  void setMyServo(VarSpeedServo myServo){
    this->MyServo = myServo;
  }
  VarSpeedServo getMyServo(){
    return MyServo;
  }
  
  
   void init(int Pin, double Slop, int Intersept, int InitalPositon){
   
    this->setPin(Pin);
    this->setIntersept(Intersept);
    this->setSlop(Slop);
    this->setInitalPositon(InitalPositon);
    
    getMyServo().attach(Pin);
    getMyServo().slowmove(InitalPositon, 25);
  }
  
};

class AudioAction : public Action{

    private:
    DFRobotDFPlayerMini myPlayer;


    public:
    void init(HardwareSerial *stream, int baudrate){
        
        stream->begin(baudrate);
        myPlayer.begin(*stream);
    }

     void doAction(int track, int volume){

          myPlayer.volume(volume);  //Set volume value. From 0 to 30
          myPlayer.playMp3Folder(track);  //Play the mp3
    }

    int isDone(){
      return (myPlayer.read() == Sleeping) ? 0 : -1;
      
    }
};


class StepperAction : public Action{

  private:

   AccelStepper myStepper;
    
    

  public:
    

    void doAction(int Steps, int Speed){
         
         
         if(Steps > 100){ Steps = 100; }
         if(Steps < -100) { Steps = -100; }
        
          Steps = Steps*(STEPPER_CONST)*(STEPPER_CONST);
          
          myStepper.setMaxSpeed(Speed);
         // myStepper.setAcceleration(Speed/2);
          Serial.println(Steps);
          myStepper.moveTo(Steps); 
          
    }

    void init(int dirpin,int steppin, int stepstosenter){   
           
      myStepper = AccelStepper(steppin, dirpin);
      myStepper.setAcceleration(100.0);
      myStepper.runToNewPosition(STEPPER_CONST*stepstosenter);
      myStepper.setCurrentPosition(0);
      
    }

    int isDone(){
      return myStepper.distanceToGo();
    }

    void run(){
      myStepper.run();
    }


};



#endif
