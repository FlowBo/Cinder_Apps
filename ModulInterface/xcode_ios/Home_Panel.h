//
//  Home_Panel.h
//  ModulInterface
//
//  Created by Florian Born on 21.08.13.
//
//


#pragma once
#include <iostream>
#include "cinder/app/AppNative.h"
#include <vector>
#include "Panel.h"
using namespace std;
using namespace ci;
using namespace ci::app;

class Home_Panel {
public:
    Home_Panel();
    Home_Panel(bool &calibrating);
    void draw();
    void hitTest(Vec2f touch);
    
    inline int getActivePanel(){return mActivePanel;};
    bool inside(Vec2f touch);
private:
    vector<Panel> panels;
    Vec2f mPos;	
    int mActivePanel;
    int mState;
    Rectf mBounding;
};