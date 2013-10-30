//
//  Slider_Button.cpp
//  ModulInterface
//
//  Created by Florian Born on 19.08.13.
//
//

#include "Slider_Button.h"

Slider_Button::Slider_Button(){
    this->setup();
};
Slider_Button::Slider_Button(Vec2f pos){
    this->setup();
    mPos = pos;
    offSet = Vec2f(0,65);
};

void Slider_Button::setup(){
    mTexture = gl::Texture( loadImage( loadResource( "slider.png" ) ) );


}