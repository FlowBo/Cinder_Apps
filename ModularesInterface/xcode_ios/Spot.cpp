//
//  Spot.cpp
//  ModulInterface
//
//  Created by Florian Born on 18.08.13.
//
//

#include "Spot.h"



Spot::Spot(){
    
}

Spot::Spot(Vec2f pos,Vec2f size, int id){
    mPos = pos;
    mSize = size;
    mId = id;
    mUsed = false;
    mBounding = Rectf(mPos,mPos+mSize);
    this->setup();
    value = 0;
    mPanel.setup(mPos, mSize);
    mPanel.addButton(Vec2f(0,0), Vec2f(mSize.x,mSize.y/4), "Exit", 0, 0);
    mPanel.addButton(Vec2f(0,mSize.y/4), Vec2f(mSize.x,mSize.y/4), "Slider", 0, 1);
    mPanel.addButton(Vec2f(0,mSize.y/4*2), Vec2f(mSize.x,mSize.y/4), "Button", 0, 2);
    mPanel.addButton(Vec2f(0,mSize.y/4*3), Vec2f(mSize.x,mSize.y/4), "Knob", 0, 3);
    console() << "------ Spot constructor once ----------" << endl;
}



void Spot::draw(){
    gl::color(1, 1, 1);
    gl::enableAlphaBlending();
    gl::drawStrokedRect(mBounding);
    gl::drawString(std::to_string(mId), mPos+Vec2f(10,20));
    gl::disableAlphaBlending();
}

Vec2f Spot::getPos(){
    return mPos;
}

void Spot::activate(){
    mUsed = true;
}

void Spot::deactivate(){
    mUsed = false;
}

void Spot::update(){
    mControllerType = mPanel.getActiveView();
    console() << "Spot View: " << mControllerType << endl;
}

void Spot::update(Vec2f touch){
   
}

bool Spot::isUsed(){
    return mUsed;
}

int Spot::getId(){
    return mId;
}

void Spot::setup(){
    mControllerType = 0;
}

void Spot::drawInterface()
{
    mPanel.draw(mControllerType);
}

bool Spot::contain(Vec2f touch)
{
    return mBounding.contains(touch);
}

void Spot::hitTest(Vec2f touch){
    mPanel.hitTest(touch);
}