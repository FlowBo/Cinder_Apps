//
//  ControllerField.cpp
//  ModularsInterface_02
//
//  Created by Florian Born on 04.09.13.
//
//

#include "ControllerField.h"



ControllerField::ControllerField(Vec2f pos, Vec2f size,int nid)
{
    controller = NULL;
    waitingForId = false;
    mPos = pos;
    mSize = size;
    mId = nid;
    mBounding = Rectf(mPos,mPos+mSize);
    state = EMPTY;
    controllerType = NONE;
    mUsed = false;
    isSliderPossible = true;
    isKnobPossible = true;
    darkGrey = Color(0.25,0.25,0.25);
    lightGrey = Color(0.75,0.75,0.75);
    mButtons.push_back(Button(mPos,Vec2f(mSize.x,mSize.y/4),"exit",0,0));
    mButtons.push_back(Button(Vec2f(mPos.x,mPos.y+mSize.y/4),Vec2f(mSize.x,mSize.y/4),"button",0,1));
    mButtons.push_back(Button(Vec2f(mPos.x,mPos.y+mSize.y/4*2),Vec2f(mSize.x,mSize.y/4),"slider",0,2));
    mButtons.push_back(Button(Vec2f(mPos.x,mPos.y+mSize.y/4*3),Vec2f(mSize.x,mSize.y/4),"knob",0,3));
}



void ControllerField::touch(Vec2f touch)
{
    if (state == CALIBRATING && controllerType != BLOCKED) {
        controller = NULL;
        for(vector<Button>::iterator it = mButtons.begin(); it != mButtons.end();)
        {
            if (it->hittest(touch)) {
                
                int v = it->getLinkedView();
                switch (v) {
                    case 0:
                        state = EMPTY;
                        controller = NULL;
                        controllerType = NONE;
                        break;
                    case 1:
                        waitingForId = true;
                        mType = "button";
                        controllerType = BUTTON;
                        state = USED;
                        break;
                    case 2:
                        if (isSliderPossible) {
                            waitingForId = true;
                            mType = "Slider";
                            controllerType = SLIDER;
                            state = USED;
                        }
                        break;
                    case 3:
                        if (isKnobPossible) {
                            waitingForId = true;
                            mType = "Knob";
                            controllerType = KNOB;
                            state = USED;
                        }
                        break;
                    default:
                        break;
                }
            }
            ++it;
        }
    }
    else if(state == EMPTY)
    {
        state = CALIBRATING;
        
    }
    else if (state == USED)
    {
        state = CALIBRATING;
        
    }
}

void ControllerField::moved(Vec2f touch)
{
    controller->touch(touch);
    
}
void ControllerField::moved(Vec2f touch, osc::Sender* sender)
{
    controller->touch(touch);
    controller->sendOSC(sender);
}
void ControllerField::draw()
{

    if(controllerType != NONE && controllerType != BLOCKED){
        if(controller){
            controller->display();
            controller->draw();
            
        }
    }
    
    if (state == CALIBRATING && controllerType != BLOCKED) {
        
        for(Button &b : mButtons)
        {
            int v = b.getLinkedView();
            switch (v) {
                case 0:
                    b.draw(lightGrey);
                    break;
                case 1:
                    b.draw(lightGrey);
                    break;
                case 2:
                    if (isSliderPossible)
                    {
                        b.draw(lightGrey);
                    }
                    else{
                        b.draw(darkGrey);
                    }
                    break;
                case 3:
                    if (isKnobPossible)
                    {
                        b.draw(lightGrey);
                    }
                    else{
                        b.draw(darkGrey);
                    }
                    break;
                    
                default:
                    break;
            }
        }
        
    }
    
    
    //    if(controllerType == BLOCKED){
    //        gl::color(0.25, 0.25, 0.25,0.25);
    //        gl::drawSolidRect(mBounding);
    //    }
}

bool ControllerField::contains(Vec2f touch)
{
    return mBounding.contains(touch);
}

void ControllerField::update()
{
    
    if (controllerType == NONE || controllerType == BLOCKED || controllerType == BUTTON) {
        deletLinkedField();
    }
    if (controller) {
        controller->update();
    }
}

bool ControllerField::controllerContains(Vec2f v)
{
    return controller->contains(v);
}


void ControllerField::initilizeNewController(int iD){
    switch (controllerType) {
        case BUTTON:
            controller = new CButton(iD);
            controller->setup(mPos, mSize);
            
            waitingForId = false;
            break;
        case SLIDER:
            controller = new Slider(iD);
            controller->setup(mPos, Vec2f(mSize.x,mSize.y*2));
            waitingForId = false;
            break;
        case KNOB:
            controller = new Knob(iD);
            controller->setup(mPos, Vec2f(mSize.x*2,mSize.y));
            waitingForId = false;
            break;
        default:
            break;
    }
}

void ControllerField::initilizeNewController(int iD, osc::Sender *sender){
    switch (controllerType) {
        case BUTTON:
            controller = new CButton(iD);
            controller->setup(mPos, mSize);
            waitingForId = false;
            gotNewController = true;
            //            sendNewController(iD, sender);
            break;
        case SLIDER:
            controller = new Slider(iD);
            controller->setup(mPos, Vec2f(mSize.x,mSize.y*2));
            waitingForId = false;
            gotNewController = true;
            //            sendNewController(iD, sender);
            break;
        case KNOB:
            controller = new Knob(iD);
            controller->setup(mPos, Vec2f(mSize.x*2,mSize.y));
            waitingForId = false;
            gotNewController = true;
            //            sendNewController(iD, sender);
            break;
        default:
            break;
    }
    
}

void ControllerField::sendNewController(int iD, osc::Sender *sender)
{
    console() << "Send osc: " << iD << endl;
    osc::Message message;
    message.addIntArg(iD);
    message.setAddress("cinder/newController");
    message.setRemoteEndpoint(System::getIpAddress(), 3000);
    sender->sendMessage(message);
}

bool ControllerField::newControllerValue()
{
    if (controller) {
        if(controller->newValue()){
            return true;
            
        }
    }
    return false;
}

int ControllerField::getNewControllerId()
{
    gotNewController = false;
    return controller->getId();
}

int ControllerField::getControllerId()
{
    return controller->getId();
}
float ControllerField::getControllerValue()
{
    return controller->getValue();
}

bool ControllerField::controllerExsist()
{
    if(controller){
        return true;
    }
    return false;
}

void ControllerField::deleteController()
{
    state = EMPTY;
    controller = NULL;
    controllerType = NONE;
}
