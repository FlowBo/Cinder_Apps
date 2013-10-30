//
//  Button_Button.cpp
//  ModulInterface
//
//  Created by Florian Born on 20.08.13.
//
//

#include "Button_Button.h"




Button_Button::Button_Button(){
    this->setup();
};
Button_Button::Button_Button(Vec2f pos){
    this->setup();
    mPos = pos;
    offSet = Vec2f(0,130);
};

void Button_Button::setup(){
    mTexture = gl::Texture( loadImage( loadResource( "button.png" ) ) );
}