//
//  Button.h
//  ModulInterface
//
//  Created by Florian Born on 18.08.13.
//
//

#pragma once
#include <iostream>
#include "cinder/app/AppNative.h"
#include "cinder/gl/Texture.h"


using namespace std;
using namespace ci;
using namespace ci::app;

class Button {
    
public:
    Button();
    bool hitTest();
    void draw();
    void update();
    Shape2d mShape;
    Path2d mPath;
    Vec2f mPos;
    Color mColor;
    gl::Texture		mTexture;
    bool contains(Vec2f touch);
    Vec2f offSet;
};

