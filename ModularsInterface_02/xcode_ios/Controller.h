//
//  Controller.h
//  ModularsInterface_02
//
//  Created by Florian Born on 04.09.13.
//
//

#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/Text.h"
#include "cinder/Font.h"
#include "cinder/gl/Texture.h"
#include "OscSender.h"
#include "cinder/System.h"
using namespace ci;
using namespace ci::app;
using namespace std;

//class ControllerField;
class Controller{
    
public:
    
    Controller() : value( 0 ), oldValue(0) {};
    void setup(Vec2f pos, Vec2f size);
    virtual void draw() = 0;
    virtual void touch(Vec2f touch) = 0;
    virtual void setText() = 0;
    
    virtual void initilize() = 0;
    float map(float val, float inMin, float inMax, float outMin, float outMax);
    inline bool contains( Vec2f v ){ return mBounding.contains(v) ;};
    
    inline float getValue(){ return oldValue ;};
    inline int getId() { return mId ;};
    inline bool newValue(){return gotNewValue;};
    
    inline void touchStarted(){controllerIsActive = true;};
    inline void touchEndend(){controllerIsActive = false;};

    void display();
    void update();
    void sendOSC(osc::Sender* oscSender);
protected:
    Vec2f mPos;
    Vec2f mSize;
    Vec2f mInfoPos;
    
    Rectf mBounding;
    
//    virtual void input() =0;

    int     mId;
    float   value;
    float   oldValue;
    string valueText;
    string idText;
    Font mFont;
    TextBox mTextBox;
    gl::Texture mTextTexture;
    bool gotNewValue;
    
    bool controllerIsActive;
    
};