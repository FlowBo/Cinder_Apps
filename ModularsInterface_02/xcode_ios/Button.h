//
//  Button.h
//  ModularsInterface_02
//
//  Created by Florian Born on 04.09.13.
//
//

#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/Font.h"
#include "cinder/Text.h"

using namespace ci;
using namespace ci::app;
using namespace std;

extern Color lightColor;
class Button{
    
public:
    Button(Vec2f pos, Vec2f size, string name, int view, int linkedView);
    bool hittest(Vec2f touch);
    inline int getLinkedView(){ return mLinkedView;};
    inline int getView(){ return mView;};
    void draw();
    void draw(Color c);
    void printName();
private:
    Vec2f mPos;
    Vec2f mSize;
    string mName;
    int mView;
    int mLinkedView;
    Rectf mBounding;
    TextBox *txt;
    Font mFont;
    gl::Texture mTextTexture;
};