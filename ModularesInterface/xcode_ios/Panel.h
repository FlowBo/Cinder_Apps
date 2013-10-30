//
//  Panel.h
//  ModularesInterface
//
//  Created by Florian Born on 01.09.13.
//
//

#pragma once


#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include <iostream>
#include "Button.h"

using namespace ci;
using namespace ci::app;
using namespace std;


class Panel{
public:
    Panel();
    void draw(int view);
    void setup( Vec2f pos, Vec2f size );
    void hitTest(Vec2f touch);
    int hitTestInt(Vec2f touch);
    inline int getActiveView(){return mActiveView;};
    void addButton(Vec2f pos, Vec2f size, string name,int view, int link);
    
private:
    Vec2f mPos;
    Vec2f mSize;
    Rectf mBounding;
    vector<Button> mButtons;
    int mActiveView;
};