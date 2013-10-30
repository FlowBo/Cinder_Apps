//
//  Slider.cpp
//  ModularsInterface_02
//
//  Created by Florian Born on 06.09.13.
//
//

#include "Slider.h"


Slider::Slider(){}

Slider::Slider(int iD){
    mId = iD;
}
void Slider::initilize()
{
    firstTime = true;
    lowerY = mPos.y+(mSize.y-195);
    upperY = mPos.y + 110;
    mInfoPos = Vec2f(10,400);
    console() << "Size : " << mSize << endl;
}
void Slider::touch(Vec2f touch)
{
    checkRange(touch);
    if(firstTime){
        mLastPos = touch;
        firstTime = false;
        return;
    }
    else{
        value = map(touch.y, upperY, lowerY, 1, 0);
        if (value < 0.00f) {
            value = 0.00f;
        }
        else if (value > 1.00f)
        {
            value = 1.00f;
        }
        //checkRange(touch);
        console() << value << endl;
    }
    
    console() << "lowerY = " << lowerY << "  upperY = " << upperY << endl;
    console() << "TouchPos: " << touch << endl;
}

void Slider::draw()
{
    gl::color(1, 1, 1);
    gl::pushMatrices();
    gl::translate(mPos+mInfoPos+Vec2f(20,20));
    gl::enableAlphaBlending();
    gl::draw(mTextTexture);
    gl::disableAlphaBlending();
    gl::popMatrices();
}

void Slider::checkRange(Vec2f touch)
{
//    Vec2f nTouch = touch+mPos;
//    if(nTouch.y < upperY){
//        upperY = nTouch.y;
//    }
//    else if (nTouch.y > lowerY)
//    {
//        lowerY = nTouch.y;
//    }
//    else{return;}
}

void Slider::setText()
{
    valueText = "value: " + std::to_string(value);
    valueText.resize(11);
    valueText = valueText + "\nid: " + std::to_string(mId);
    mTextBox.text(valueText);
}

