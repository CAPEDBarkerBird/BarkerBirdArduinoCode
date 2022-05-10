#ifndef ACTIONS_H
#define ACTIONS_H

#include <VarSpeedServo.h> 
#include "DFRobotDFPlayerMini.h"
#include "AccelStepper.h"

const int BEAK_PIN = 13;
const int NECK_VERTICAL_PIN = 10;
const int NECK_HORIZONTAL_PIN = 9;
const int BAS_DIRECTION_PIN = 2;
const int BAS_STEP_PIN = 3;


const int BEAK_PIN_INTERCEPT = 1029;
const int NECK_VERTICAL_INTERCEPT = 613;
const int NECK_HORIZONTAL_INTERCEPT = 1094;

const int BEAK_PIN_SLOP = -1.97;
const int NECK_VERTICAL_SLOP = 15.87;
const int NECK_HORIZONTAL_SLOP = 13.25;

const int BEAKdefault = 1500;
const int NECK_HORIZONTALdefault = 1500;
const int NECK_VERTICALdefault = 1500;
const int FLAPdefault = 1500;
const int R_WING_EXTENDdefault = 1500;
const int BASEdefault = 675;

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
          myPlayer.play(track);  //Play the mp3
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

          myStepper.setMaxSpeed(Speed);
         // myStepper.setAcceleration(Speed/2);
          myStepper.moveTo(Steps); 
          
    }

    void init(int dirpin,int steppin, int stepstosenter){   
           
      myStepper = AccelStepper(steppin, dirpin);
      myStepper.setAcceleration(100.0);
      myStepper.runToNewPosition(stepstosenter);
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
