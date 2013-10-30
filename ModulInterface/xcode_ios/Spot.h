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
#include "Button.h"
#include "Exit_Button.h"
#include "Slider_Button.h"
#include "Button_Button.h"
#include "Knob_Button.h"
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
    Vec2f getPos();
    void activate();
    void deactivate();
    void update();
    void update(Vec2f touch);
    bool isUsed();
    bool quit(Vec2f touch);
    int getId();
private:
    Vec2f   mPos;
    Vec2f   mSize;
    bool    mUsed;
    bool    mSet;
    int     mId;
    void    setup();
    string  type;
    Panel mPanel;
    vector<Button> buttons;
    Exit_Button exitButton;
    Slider_Button sliderButton;
    Button_Button buttonButton;
    Knob_Button knobButton;
};