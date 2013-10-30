//
//  Layout.h
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
#include "Grid.h"
using namespace std;
using namespace ci;
using namespace ci::app;

class Layout {
public:
    Layout();
    Layout(Vec2i size);
    Layout(AppNative &app);
    void draw();
    void upadte();
    Vec2f getSize();
    void calibrate();
private:
    AppNative *mApp;

    list <Knob> knobs;
    Grid mGrid;
    
//    list <Slider> sliders;
//    list <Button> buttons;
};
