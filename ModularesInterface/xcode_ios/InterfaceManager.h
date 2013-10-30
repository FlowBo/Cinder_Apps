//
//  InterfaceManager.h
//  ModularesInterface
//
//  Created by Florian Born on 01.09.13.
//
//

#pragma once

#include "cinder/app/AppNative.h"

#include "cinder/gl/gl.h"
#include <iostream>
#include "Panel.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class InterfaceManager {
public:
    InterfaceManager();
    void draw();
    void update();
    void setup(Vec2f &origin, Vec2f &size, Vec2f &single, Vec2f &nDouble , Vec2f &nLong);
    void hitTest(Vec2f touch);
    inline int getActiveViewInterface(){return mActiveViewInterface;};
private:

    Rectf mRect;
    Panel mMenu;
    
    int mActiveViewInterface;
};