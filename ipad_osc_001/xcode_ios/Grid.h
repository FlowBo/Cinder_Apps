//
//  Grid.h
//  ipad_osc_001
//
//  Created by Florian Born on 22.07.13.
//
//

#pragma once

#include "cinder/app/AppNative.h"

#include <vector>
#include <map>
#include <list>
#include "Knob.h"
using namespace std;
using namespace ci;
using namespace ci::app;

class Grid {
public:
    Grid();
    Grid(Vec2i size);
    void setup();
    void draw();
    void upadte();
    Vec2i getSize();
private:
    Vec2i mSize;
    Vec2i steps;
};
