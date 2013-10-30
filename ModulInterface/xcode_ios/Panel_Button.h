//
//  Panel_Button.h
//  ModulInterface
//
//  Created by Florian Born on 21.08.13.
//
//

#pragma once
#include <iostream>
#include "cinder/app/AppNative.h"
#include <vector>
#include "cinder/Text.h"
#include "cinder/gl/Texture.h"
#include "cinder/Font.h"
#include "cinder/gl/gl.h"


using namespace std;
using namespace ci;
using namespace ci::app;

class Panel_Button {
public:
    Panel_Button();
    Panel_Button(Vec2f pos, Vec2i size, string text, int id,int view,Font mFont);
    
    void setup();
    void draw(Color c);
    
    bool hitTest(Vec2f touch);

    inline int getNextView(){return mNextViewId;};

private:
    Vec2f mPos;
    Vec2f mSize;
    string mText;
    int mNextViewId;
    Rectf mField;
    TextBox mTextField;
    Font mFont;
    gl::Texture mType;
};