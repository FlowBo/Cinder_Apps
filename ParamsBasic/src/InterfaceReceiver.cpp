//
//  InterfaceReceiver.cpp
//  OSCListener
//
//  Created by Florian Born on 08.09.13.
//
//

#include "InterfaceReceiver.h"



InterfaceReceiver::InterfaceReceiver(){
    
}

void InterfaceReceiver::setup(int port)
{
    mPort = port;
    receiver.setup(port);
}

void InterfaceReceiver::draw(Vec2f size)
{
    Vec2f pos = Vec2f(50,100);
    for(vector<Controller>::iterator it = mControllers.begin(); it != mControllers.end(); ){
        
        it->draw(pos);
        if(pos.x < size.x-100){
            pos.x += 100;
        }
        else{
            pos.x = 50;
            pos.y += 100;
        }
        ++it;
    }
}

void InterfaceReceiver::update(){
    while( receiver.hasWaitingMessages() ) {
		osc::Message message;
		receiver.getNextMessage( &message );
        bool foundExsistingController = false;
        for (vector<Controller>::iterator it = mControllers.begin(); it != mControllers.end(); ) {
            if(it->getId() == message.getArgAsInt32(0)){
                it->updateValue(message.getArgAsFloat(1));
                console() << "controller: " << it->getIdAsString() << endl;
                console() << "have new Value: " << it->getValue() <<endl;
                foundExsistingController = true;
            }
            else{
                            }
            ++it;
        }
        if(foundExsistingController == false)
        {
            mControllers.push_back(Controller(message.getArgAsInt32(0),message.getArgAsFloat(1)));
            console() << "Added new Controller with iD: " << message.getArgAsInt32(0) << endl;
            console() << "and new Value: " << message.getArgAsFloat(1) <<endl;
        }
    }
}

float InterfaceReceiver::getValue(int iD)
{
    for(vector<Controller>::iterator it = mControllers.begin(); it != mControllers.end();)
    {
        if (it->getId() == iD) {
            return it->getValue();
        }

    }
    return -1.11111111;
}

float InterfaceReceiver::getValue(int iD, float low, float high)
{
    for(vector<Controller>::iterator it = mControllers.begin(); it != mControllers.end();)
    {
        if (it->getId() == iD) {
            return lmap(it->getValue(), 0, 1, low, high);
        }   
    }
    return -1.111111111;
}

Controller::Controller(int iD, float v){
    mId = iD;
    mValue = v;
    mPos = Vec2f(iD*50,100);
    mFont = Font("Helvetica",14);
    txt = new TextBox();
    txt->size(Vec2f(100,50)).setFont(mFont);
    txt->color(Color(1,0,0));
}

void Controller::draw(Vec2f pos)
{
    gl::color(0, 0, 0);
    gl::drawStrokedRect(Rectf(pos,pos+Vec2f(40,-50)));
    gl::drawSolidRect(Rectf(pos,pos+(Vec2f(40,mValue*(-50) ))));
    string valueText = "value: " + std::to_string(mValue);
    valueText.resize(11);
    valueText = valueText + "\nid: " + std::to_string(mId);
    txt->setText(valueText);
        
    mTexture = gl::Texture(txt->render());
    gl::enableAlphaBlending();
    gl::draw(mTexture,pos);
    gl::disableAlphaBlending();
}