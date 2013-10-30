//
//  Knob_Button.cpp
//  ModulInterface
//
//  Created by Florian Born on 20.08.13.
//
//

#include "Knob_Button.h"



Knob_Button::Knob_Button(){
    this->setup();
};
Knob_Button::Knob_Button(Vec2f pos){
    this->setup();
    mPos = pos;
    offSet = Vec2f(0,195);
};

void Knob_Button::setup(){
    mTexture = gl::Texture( loadImage( loadResource( "knob.png" ) ) );
}