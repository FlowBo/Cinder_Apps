//
//  Exit_Button.cpp
//  ModulInterface
//
//  Created by Florian Born on 18.08.13.
//
//

#include "Exit_Button.h"


Exit_Button::Exit_Button(){
    this->setup();
};
Exit_Button::Exit_Button(Vec2f pos){
    this->setup();
    mPos = pos;
    offSet = Vec2f(0,0);
};

void Exit_Button::setup(){
     mTexture = gl::Texture( loadImage( loadResource( "esc.png" ) ) );
}