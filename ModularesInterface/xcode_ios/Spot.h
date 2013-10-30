//
//  Spot.h
//  ModulInterface
//
//  Created by Florian Born on 18.08.13.
//
//

#pragma once
#include <iostream>
#include "cinder/app/AppNative.h"
#include <vector>
#include "Panel.h"

using namespace std;
using namespace ci;
using namespace ci::app;

class Spot {
public:
    
    Spot();
    Spot(Vec2f pos,Vec2f size, int id);
    Spot(float x, float y);
    void draw();
    void drawInterface();
    Vec2f getPos();
    void activate();
    void deactivate();
    void update();
    void update(Vec2f touch);
    bool isUsed();
    bool quit(Vec2f touch);
    int getId();
    inline int getControllerType(){return mControllerType;};
    void setControllerType(int type);
    void    setup();
    
    
    
    bool contain(Vec2f touch);
    void hitTest(Vec2f touch);
private:
    Vec2f   mPos;
    Vec2f   mSize;
    Rectf   mBounding;
    bool    mUsed;
    bool    mSet;
    int     mId;
    
    string  type;
    Panel   mPanel;
    int mControllerType;
    int value;
};