//
//  Grid.h
//  ModulInterface
//
//  Created by Florian Born on 16.08.13.
//
//
#pragma once
#include <iostream>
#include "cinder/app/AppNative.h"

using namespace std;
using namespace ci;
using namespace ci::app;

class Grid {
public:
    Grid();
    Grid(Vec2i size);
    void setup();
    void draw();
    void drawPoints();
    void upadte();
    Vec2i getSize();
private:
    Vec2i mSize;
    Vec2i steps;
};
