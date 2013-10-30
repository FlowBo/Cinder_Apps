//
//  ControllerField.h
//  ModularsInterface_02
//
//  Created by Florian Born on 04.09.13.
//
//

#pragma once
#include "cinder/app/AppNative.h"
#include "Controller.h"
#include "Button.h"
#include "cinder/Text.h"
#include "cinder/gl/Texture.h"
#include "cinder/Font.h"
#include "cinder/System.h"

#include "Slider.h"
#include "Knob.h"
#include "CButton.h"

#include "OscSender.h"

using namespace ci;
using namespace ci::app;
using namespace std;


class ControllerField{
    
public:
    ControllerField(Vec2f pos, Vec2f size,int nid);
    enum State { USED, EMPTY, CALIBRATING};
    enum ControllerType{ NONE, BUTTON, SLIDER, KNOB, BLOCKED};
    void touch(Vec2f touch);
    inline void touchStarted(){controller->touchStarted() ;};
    inline void touchEnded(){controller->touchEndend() ;};
    void moved(Vec2f touch, osc::Sender* sender);
    void moved(Vec2f touch);
    void draw();
    void update();
    bool contains(Vec2f touch);
    inline bool isUsed(){return mUsed;};
    inline void setSliderPossibility(bool value){isSliderPossible = value;};
    inline void setKnobPossibility(bool value){isKnobPossible = value ;};
    inline float getYPos(){return mPos.y ;};
    inline State getState(){return state;};
    inline ControllerType getControllerType(){return controllerType;};
    
    void deleteController();
    
    inline void setType(ControllerType cT){controllerType = cT;};
    inline void setState(State s){state = s;};
    
    inline void setLinkedField(ControllerField &link){ linkedField = &link ;};
    inline void deletLinkedField(){linkedField = NULL;};
    
    bool controllerContains(Vec2f v);
    inline bool waitForId(){return waitingForId ;};
    
    void initilizeNewController(int iD);
    void initilizeNewController(int iD, osc::Sender *sender);
    void sendNewController(int iD, osc::Sender *sender);
    
    bool newControllerValue();
    int getControllerId();
    float getControllerValue();
    inline bool newController(){return gotNewController;};
    int getNewControllerId();
    
    bool controllerExsist();
    
private:
    Controller *controller;
    State state;
    vector<Button> mButtons;
    Vec2f mPos;
    Vec2f mSize;
    Rectf mBounding;
    int mId;
    
    bool mUsed;
    bool isSliderPossible;
    bool isKnobPossible;
    bool waitingForId;
    bool gotNewController;
    
    string mType;
    ControllerType controllerType;
    ControllerField* linkedField;
    Font mFont;
    TextBox mText;
    gl::Texture mTexture;
    Color lightGrey;
    Color darkGrey;

    
};