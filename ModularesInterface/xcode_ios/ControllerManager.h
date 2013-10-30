//
//  ControllerManager.h
//  ModularesInterface
//
//  Created by Florian Born on 01.09.13.
//
//

#pragma once

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "Spot.h"
#include <vector>

using namespace ci;
using namespace ci::app;
using namespace std;

class ControllerManager {
public:
    ControllerManager();
    void setup(Vec2f size, Vec2f single);
    void draw();
    void update(int view);
    void hitTest(Vec2f touch);
private:
    vector<Spot> mSpots;
    int mActiveViewController;
    
};