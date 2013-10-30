//
//  CButton.h
//  ModularsInterface_02
//
//  Created by Florian Born on 07.09.13.
//
//
#pragma once


#include "Controller.h"
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include <cstring>


#include <math.h>

class CButton : public Controller {
    
public:
    CButton();
    CButton(int iD);
    void touch(Vec2f touch );
    void draw();
    void initilize();
    void setText();
private:
    Vec2f mLastPos;
    bool state;
    
};