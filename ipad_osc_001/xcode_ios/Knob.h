//
//  knob.h
//  ipad_osc_001
//
//  Created by Florian Born on 17.07.13.
//
//

#pragma once

#include "cinder/app/AppNative.h"
using namespace ci;
using namespace ci::app;

class Knob {
public:
    Knob();
    Knob(Vec2i size);
    void draw();
    void upadte();

private:
    bool mCalibrated;
    Vec2f mCenter;
    Vec2f mPos;
    Vec2f mSize;
    float mRadius;
    
    
};
