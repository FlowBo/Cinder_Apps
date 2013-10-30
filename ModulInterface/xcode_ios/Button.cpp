//
//  Button.cpp
//  ModulInterface
//
//  Created by Florian Born on 18.08.13.
//
//

#include "Button.h"


Button::Button(){
};

void Button::draw(){
    
    gl::pushMatrices();
    gl::translate(mPos+offSet);
    gl::color(255,255,255);
    gl::draw(mTexture);
    gl::popMatrices();
    
}

bool Button::contains(Vec2f touch){
    return mTexture.getBounds().contains(touch-(mPos+offSet));
}