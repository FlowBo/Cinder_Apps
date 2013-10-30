//
//  InterfaceReceiver.h
//  OSCListener
//
//  Created by Florian Born on 08.09.13.
//
//
#pragma once

#include "cinder/app/AppNative.h"
#include "cinder/Font.h"
#include "cinder/gl/gl.h"
#include "cinder/Text.h"
#include "cinder/gl/Texture.h"
using namespace ci;
using namespace ci::app;
using namespace std;

#include "OscListener.h"

class Controller;

class InterfaceReceiver{
public:
    InterfaceReceiver();
    void draw(Vec2f size);
    void update();
    void setup(int port);
    float getValue(int iD);
    float getValue(int iD,float low, float high);
    inline float lmap(float val, float inMin, float inMax, float outMin, float outMax)
    {
        return outMin + (outMax - outMin) * ((val - inMin) / (inMax - inMin));
    };
private:
    osc::Listener receiver;
    int mPort;
    vector<Controller> mControllers;
    
};

class Controller{
public:
    Controller();
    inline Controller(int iD){mId = iD ;};
    Controller(int iD, float v);
    inline void updateValue(float v){ mValue = v;};
    inline float getValue(){ return mValue; };
    inline int getId() { return mId;};
    inline string getIdAsString() { return std::to_string(mId);};
    void draw(Vec2f pos);
private:
    float mValue;
    int mId;
    Font mFont;
    TextBox *txt;
    gl::Texture mTexture;
    Vec2f mPos;
};

