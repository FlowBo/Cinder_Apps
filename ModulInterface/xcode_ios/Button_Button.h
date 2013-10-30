//
//  Button_Button.h
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

class Button_Button:public Button {
    
public:
    Button_Button(Vec2f pos);
    Button_Button();
    void setup();
};
