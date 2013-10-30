//
//  Knob_Button.h
//  ModulInterface
//
//  Created by Florian Born on 20.08.13.
//
//

#pragma once
#include <iostream>
#include "cinder/app/AppNative.h"
#include "Button.h"
using namespace std;
using namespace ci;
using namespace ci::app;

class Knob_Button:public Button {
    
public:
    Knob_Button(Vec2f pos);
    Knob_Button();
    void setup();
};
