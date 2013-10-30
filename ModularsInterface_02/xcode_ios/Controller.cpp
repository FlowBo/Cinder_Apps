//
//  Controller.cpp
//  ModularsInterface_02
//
//  Created by Florian Born on 04.09.13.
//
//

#include "Controller.h"


void Controller::setup(Vec2f pos, Vec2f size)
{
    gotNewValue = true;
    controllerIsActive = false;
    mPos = pos;
    mSize = size;
    mBounding = Rectf(mPos,mPos+mSize);
    mFont.getNames();
    mFont = Font( "Helvetica", 14 );
    mTextBox = TextBox().color(Color(0,0,0)).font(mFont).size( Vec2i( 200, TextBox::GROW ) );
    initilize();
}

float Controller::map(float val, float inMin, float inMax, float outMin, float outMax)
{
    return outMin + (outMax - outMin) * ((val - inMin) / (inMax - inMin));
}

void Controller::sendOSC(osc::Sender *oscSender)
{
    osc::Message message;
    message.addIntArg(mId);
    message.addFloatArg(value);
    message.setAddress("cinder/controller");
    message.setRemoteEndpoint(System::getIpAddress(), 3000);
    oscSender->sendMessage(message);
}

void Controller::update()
{
    if (oldValue != value) {
        gotNewValue = true;
        oldValue = value;
    }
    else{
        gotNewValue = false;
    }
}

void Controller::display()
{
    
    setText();
    if (!controllerIsActive) {
        gl::color(0.25,0.25,0.25); 
        mTextBox.setColor(Color(1,1,1));
    }
    else{
        gl::color(0.75,0.75,0.75);
        mTextBox.setColor(Color(0,0,0));
    }
    mTextTexture = gl::Texture( mTextBox.render() );
    gl::drawSolidRect(mBounding);
    
}