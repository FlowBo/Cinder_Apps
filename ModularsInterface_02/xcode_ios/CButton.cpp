//
//  CButton.cpp
//  ModularsInterface_02
//
//  Created by Florian Born on 07.09.13.
//
//

#include "CButton.h"


CButton::CButton(){
    
}

CButton::CButton(int iD)
{
    mId = iD;
    initilize();
}

void CButton::initilize(){
    state = false;
    mInfoPos = Vec2f(10,200);
}

void CButton::draw(){
    gl::color(1, 1, 1);
    gl::pushMatrices();
    gl::translate(mPos+mInfoPos+Vec2f(20,-40));
    gl::enableAlphaBlending();
    gl::draw(mTextTexture);
    gl::disableAlphaBlending();
    gl::popMatrices();
}

void CButton::touch(Vec2f touch)
{
    state = !state;
    if(value == 1){
        value = 0;
    }
    else{
        value = 1;
    }
}

void CButton::setText()
{
    valueText = "value: " + std::to_string(value);
    valueText.resize(11);
    valueText = valueText + "\nid: " + std::to_string(mId);
    mTextBox.text(valueText);
}