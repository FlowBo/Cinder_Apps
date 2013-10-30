//
//  Button.h
//  ModularesInterface
//
//  Created by Florian Born on 01.09.13.
//
//

#pragma once


#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include <iostream>

using namespace ci;
using namespace ci::app;
using namespace std;

class Button{
public:
    Button();
    Button(Vec2f pos, Vec2f size, string name,int view, int link);
    void draw();
    bool hitTest(Vec2f touch);
    inline int getView(){return mView;};
    inline int getLink(){return mLink;};
    inline string getName(){return mName;};
private:
    Rectf mBounding;
    string mName;
    Vec2f mPos;
    Vec2f mSize;
    int mView;
    int mLink;
};