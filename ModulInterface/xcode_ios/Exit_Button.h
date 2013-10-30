//
//  Exit_Button.h
//  ModulInterface
//
//  Created by Florian Born on 18.08.13.
//
//

#pragma once
#include <iostream>
#include "cinder/app/AppNative.h"
#include "Button.h"
using namespace std;
using namespace ci;
using namespace ci::app;

class Exit_Button:public Button {
    
public:
    Exit_Button(Vec2f pos);
    Exit_Button();
    void setup();
};
