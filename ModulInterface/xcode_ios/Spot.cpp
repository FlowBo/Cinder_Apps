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
    type = "empty";
    mPanel = Panel(100,mPos,mSize);

}

void Spot::draw(){

    if (mUsed) {
        gl::color(255, 255, 255);
        mPanel.draw();
    }
    
    std::string s = std::to_string(mId);
    gl::drawString("id: " + s, mPos+Vec2f(15,55));
}

Vec2f Spot::getPos(){
    return mPos;
}

void Spot::activate(){
    mUsed = true;
}

void Spot::deactivate(){
    mUsed = false;
    console() << "BYE" << endl;
    
}

void Spot::update(){
    
}

void Spot::update(Vec2f touch){
    int value = mPanel.hitTest(touch);
    if(value != 0){
        switch (value) {
            case 101:
                this->deactivate();
                break;
            default:
                break;
        }
       
    }
    else{
        mUsed = false;
    }
}

bool Spot::isUsed(){
    return mUsed;
}

int Spot::getId(){
    return mId;
}

void Spot::setup(){

    
}