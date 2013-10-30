//
//  Manager.h
//  ModularesInterface
//
//  Created by Florian Born on 01.09.13.
//
//
#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include <iostream>

#include "InterfaceManager.h"
#include "ControllerManager.h"


using namespace ci;
using namespace ci::app;
using namespace std;





class Manager {
public:
    Manager();
    void setup();
    void setup(Vec2f &origin, Vec2f &size, Vec2f &single, Vec2f &nDouble , Vec2f &nLong);
    void draw();
    void update();
    void touchBegan(TouchEvent touch);
private:
    InterfaceManager mInterfaceManager;
    ControllerManager mControllerManager;
  
};