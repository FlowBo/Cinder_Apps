//
//  Knob.cpp
//  ModularsInterface_02
//
//  Created by Florian Born on 07.09.13.
//
//


#include "Knob.h"


Knob::Knob(){};
Knob::Knob(int iD){
    mId = iD;
    
}

void Knob::initilize(){
    midPoint = Vec2f(mPos.x+mSize.x/2,mPos.y+(mSize.y/8)*3);
    startPos = Vec2f(1,0);
    mInfoPos = Vec2f(50,200);
}

void Knob::draw()
{
    gl::color(0, 0, 1);
    gl::drawSolidCircle(midPoint, 5);
    gl::drawLine(midPoint, midPoint + startPos*30);
    gl::drawLine(midPoint, midPoint + pos*30);
    gl::color(1, 1, 1);
    gl::pushMatrices();
    gl::translate(mPos+mInfoPos+Vec2f(20,0));
    gl::enableAlphaBlending();
    gl::draw(mTextTexture);
    gl::disableAlphaBlending();
    gl::popMatrices();

}

void Knob::touch(Vec2f touch)
{
    pos = touch;
    pos -= midPoint;
    pos.normalize();
    
    console() << "Touchpos: " << pos << endl;
//    angleValue = (atan2(startPos.x-pos.x,startPos.y-pos.y) * 180 / M_PI) * 2;
    angleValue = atan2(startPos.x-pos.x,startPos.y-pos.y) ;
    value = map(angleValue, 0, M_PI, 1, 0);
}

void Knob::setText()
{
    valueText = "value: " + std::to_string(value);
    valueText.resize(11);
    valueText = valueText + "   id: " + std::to_string(mId);
    mTextBox.text(valueText);
}
