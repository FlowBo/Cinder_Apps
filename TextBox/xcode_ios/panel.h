//
//  panel.h
//  TextBox
//
//  Created by Florian Born on 22.08.13.
//
//

#pragma once

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

#include "cinder/Font.h"
#include "cinder/gl/Texture.h"
#include "cinder/Text.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class Panel{
public:
    Panel();
    void draw();
    void setup();
private:
    Font f;
    TextBox textBox;
    gl::Texture texture;
    string text;
};


