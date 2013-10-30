//
//  Slider.h
//  ModularsInterface_02
//
//  Created by Florian Born on 06.09.13.
//
//

#pragma once
#include "Controller.h"
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include <cstring>


#include <math.h>

class Slider : public Controller {
    
public:
    Slider();
    Slider(int iD);
    void touch(Vec2f touch );

    void draw();
    void checkRange(Vec2f touch);
    void initilize();
    void setText();
private:
    Vec2f mLastPos;
    bool firstTime;
    
    
    
    float upperY,lowerY;
};