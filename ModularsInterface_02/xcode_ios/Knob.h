//
//  Knob.h
//  ModularsInterface_02
//
//  Created by Florian Born on 07.09.13.
//
//

#pragma once



#include "Knob.h"


#include "Controller.h"
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include <math.h>



class Knob : public Controller {
    
public:
    Knob();
    
    Knob(int iD);
    
    void touch(Vec2f touch );
    
    void draw();
    
    void initilize();
    
    void setText();
    
private:
    
    Vec2f mLastPos;
    Vec2f startPos;
    Vec2f midPoint;
    bool firstTime;
    
    
    Vec2f pos;
    float angleValue;
};