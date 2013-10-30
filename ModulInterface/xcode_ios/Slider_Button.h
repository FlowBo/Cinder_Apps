//
//  Slider_Button.h
//  ModulInterface
//
//  Created by Florian Born on 19.08.13.
//
//

#pragma once
#include <iostream>
#include "cinder/app/AppNative.h"
#include "Button.h"
using namespace std;
using namespace ci;
using namespace ci::app;

class Slider_Button:public Button {
    
public:
    Slider_Button(Vec2f pos);
    Slider_Button();
    void setup();
};
