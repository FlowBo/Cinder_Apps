//
//  Panel.h
//  ModulInterface
//
//  Created by Florian Born on 21.08.13.
//
//


#pragma once
#include <iostream>
#include "cinder/app/AppNative.h"
#include <vector>
#include "Panel_Button.h"
#include "cinder/Font.h"

using namespace std;
using namespace ci;
using namespace ci::app;

class Panel {
public:
    Panel();
//    Panel(int panelId);
    Panel(int panelId,Vec2f pos, Vec2f size);
    void setup();
    void draw();
    
    int hitTest(Vec2f touch);
    int getId();
    bool contain(Vec2f touch);
    inline bool isActive(){return mActive;};
private:
    vector<Panel_Button> panelButtons;
    Font mFont;
    int mPanelId;
    Vec2f mPos;
    Vec2f mSize;
    Rectf mBounding;
    bool mActive;
};