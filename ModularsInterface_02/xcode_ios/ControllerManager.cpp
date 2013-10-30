//
//  ControllerManager.cpp
//  ModularsInterface_02
//
//  Created by Florian Born on 04.09.13.
//
//

#include "ControllerManager.h"





ControllerManager::ControllerManager(){state = FREEZE;};

void ControllerManager::initialize(Vec2f windowSize, Vec2f size)
{
    controllerIdCounter = 0;
    int id = 0;
    for(int y = 0 ; y < windowSize.y ; y += windowSize.y/4){
        for (int x = 0; x < windowSize.x; x += windowSize.x/6) {
            controllerGrid.push_back(ControllerField(Vec2f(x,y), size , id));
            id++;
        }
    }
    controllerGrid.erase(controllerGrid.end()-1);
    controllerGrid.erase(controllerGrid.end()-1);
    console() << "ControllerManager had been initialized with: " << controllerGrid.size() << " Controllerfields" << endl;
}

void ControllerManager::draw()
{
    
        for( ControllerField cF : controllerGrid)
        {
            cF.draw();
        }
    
}

void ControllerManager::touchStarted(TouchEvent event)
{
    if (state == CALIBRATING) {
        for(vector<cinder::app::TouchEvent::Touch>::iterator iter = event.getTouches().begin(); iter != event.getTouches().end();){
            for (vector<ControllerField>::iterator it = controllerGrid.begin(); it != controllerGrid.end();) {
                if(it->contains(iter->getPos()))
                {
                    it->touch(iter->getPos());
                    if(it->waitForId()){
                        it->initilizeNewController(controllerIdCounter,oscSender);
//                        controllerIdCounter++;
                        
                    }
                    setNextId();
                }
                ++it;
            }
            ++iter;
        }
    }
    else if (state == FREEZE) {
        for (vector<ControllerField>::iterator it = controllerGrid.begin(); it != controllerGrid.end();) {
            if(it->getControllerType() == ControllerField::BUTTON){
                for (vector<cinder::app::TouchEvent::Touch>::iterator iter =  event.getTouches().begin(); iter != event.getTouches().end();)  {
                    if(it->controllerContains(iter->getPos())){
                        it->moved(iter->getPos());
                        it->touchStarted();
                    }
                    ++iter;
                }
            }
            else if (it->getControllerType() == ControllerField::KNOB || it->getControllerType() == ControllerField::SLIDER){
                for (vector<cinder::app::TouchEvent::Touch>::iterator iter =  event.getTouches().begin(); iter != event.getTouches().end();)  {
                    if(it->controllerContains(iter->getPos())){
                        it->touchStarted();
                    }
                    ++iter;
                }
                
            }
            ++it;
        }
        
    }
    
    
}

void ControllerManager::touchesEnded(TouchEvent event)
{
    if(state == FREEZE){
        for(vector<cinder::app::TouchEvent::Touch>::iterator iter = event.getTouches().begin(); iter != event.getTouches().end();){
            for(vector<ControllerField>::iterator it = controllerGrid.begin(); it  != controllerGrid.end();)
            {
                if (it->getControllerType() == ControllerField::KNOB || it->getControllerType() == ControllerField::SLIDER || it->getControllerType() == ControllerField::BUTTON){
                    if(it->controllerContains(iter->getPos())){
                        it->touchEnded();
                    }
                }
                ++it;
            }
            ++iter;
        }
    }
}


void ControllerManager::touchMoved(cinder::app::TouchEvent touch)
{
    if (state == FREEZE) {
        
        
        for (vector<ControllerField>::iterator it = controllerGrid.begin(); it != controllerGrid.end();) {
            if(it->getControllerType() == ControllerField::SLIDER || it->getControllerType() == ControllerField::KNOB){
                for (vector<cinder::app::TouchEvent::Touch>::iterator iter =  touch.getTouches().begin(); iter != touch.getTouches().end();)  {
                    if(it->controllerContains(iter->getPos())){
                        it->moved(iter->getPos());
                    }
                    ++iter;
                }
            }
            ++it;
        }
    }
}


void ControllerManager::update()
{
    
    
    vector<ControllerField>::iterator iter = controllerGrid.begin();
    for (int i = 0; i < controllerGrid.size(); i++) {
        
        if (iter->getControllerType() != ControllerField::NONE && iter->getControllerType() != ControllerField::BLOCKED)
        {
            
            if(iter->getControllerType() == ControllerField::SLIDER )
            {
                controllerGrid.at(i+6).setType(ControllerField::BLOCKED);
                iter->setLinkedField(controllerGrid.at(i+6));
            }
            if (iter->getControllerType() == ControllerField::KNOB)
            {
                controllerGrid.at(i+1).setType(ControllerField::BLOCKED);
                iter->setLinkedField(controllerGrid.at(i+1));
            }
        }
        else if(iter->getControllerType() == ControllerField::BLOCKED){
            if(blockedBySlider(i) == false && blockedByKnob(i) == false)
            {
                iter->setType(ControllerField::NONE);
            }
        }
        ++iter;
    }

    vector<ControllerField>::iterator it = controllerGrid.begin() ;
    for (int i = 0; i < controllerGrid.size(); i++) {
        if(i+6 < controllerGrid.size()){
            if(controllerGrid.at(i+6).getControllerType() != ControllerField::NONE )
            {
                it->setSliderPossibility(false);
            }
            else {
                it->setSliderPossibility(true);
            }
        }
        else
        {
            it->setSliderPossibility(false);
        }
        if (i+1 < controllerGrid.size() && it->getYPos() == controllerGrid.at(i+1).getYPos()) {
            
            if (controllerGrid.at(i+1).getControllerType() != ControllerField::NONE) {
                it->setKnobPossibility(false);
            }
            else
            {
                it->setKnobPossibility(true);
            }
        }
        else
        {
            it->setKnobPossibility(false);
        }
        ++it;
    }
    checkNewValues();
    for(vector<ControllerField>::iterator iterat = controllerGrid.begin(); iterat != controllerGrid.end();)
    {
        iterat->update();
        ++iterat;
    }
}

//void ControllerManager::checkNewController()
//{
//    for(vector<ControllerField>::iterator it = controllerGrid.begin(); it !=  controllerGrid.end();)
//    {
//        if (it->newController()) {
//            sendNewController(it->getNewControllerId());
//        }
//        ++it;
//    }
//
//}

void ControllerManager::checkNewValues()
{
    for(vector<ControllerField>::iterator it = controllerGrid.begin(); it !=  controllerGrid.end();)
    {
        if(it->getControllerType()!= ControllerField::NONE || it->getControllerType()!= ControllerField::BLOCKED)
        {
            
            if(it->newControllerValue())
            {
                sendNewControllerValue(it->getControllerId(), it->getControllerValue());
            }
        }
        ++it;
    }
}

void ControllerManager::sendNewControllerValue(int iD, float value)
{
    osc::Message message;
    message.addIntArg(iD);
    message.addFloatArg(value);
    message.setAddress("controllerValue");
    message.setRemoteEndpoint(host, port);
    oscSender->sendMessage(message);
    
    console() << "Sended Message: "<< message.getRemoteIp()<< "____" << message.getRemotePort() << "____" << message.getAddress() << endl;
    console() << "ID: " << iD << " Value: " << value << endl;
    
}

void ControllerManager::setNextId()
{
    
    int i = 0;
    int p = 1;
    for(i; i < p; )
    {
        if(checkId(i) == false){
            p++;
        }
        i++;
    }
    controllerIdCounter = i-1;
}

bool ControllerManager::checkId(int iD)
{
    for (vector<ControllerField>::iterator it = controllerGrid.begin();it != controllerGrid.end(); ) {
        if(it->controllerExsist()){
            if (it->getControllerId() == iD) {
                return false;
            }
        }
        ++it;
    }
    return true;
}

Vec3i ControllerManager::getControllers(){
    int button = 0;
    int slider = 0;
    int knob   = 0;
    for(vector<ControllerField>::iterator it = controllerGrid.begin(); it != controllerGrid.end(); )
    {
        if(it->getControllerType() == ControllerField::BUTTON){button++;}
        else if(it->getControllerType() == ControllerField::SLIDER){slider++;}
        else if(it->getControllerType() == ControllerField::KNOB){knob++;}
        ++it;
    }
    return Vec3i(button,slider,knob);
}


void ControllerManager::clearControllers()
{
    
    for(vector<ControllerField>::iterator it = controllerGrid.begin(); it != controllerGrid.end(); )
    {
        it->deleteController();
        ++it;
    }
    
}

void ControllerManager::loadLayout(cinder::XmlTree &layout)
{
    controllerIdCounter = 0;
    for(XmlTree::Iter it = layout.begin();it != layout.end();++it)
    {
        string v = it->getValue();
        int c = it->getAttributeValue<int>("id");
        int cId = it->getAttributeValue<int>("cId");
        console() << "cID: " << cId << endl;
        if (v == "1")
        {
            controllerGrid.at(c).setType(ControllerField::BUTTON);
            
            controllerGrid.at(c).initilizeNewController(cId);
            //setNextId();
        }
        else if (v == "2")
        {
            controllerGrid.at(c).setType(ControllerField::SLIDER);
            controllerGrid.at(c).initilizeNewController(cId);
            //setNextId();
        }
        else if (v == "3")
        {
            controllerGrid.at(c).setType(ControllerField::KNOB);
            controllerGrid.at(c).initilizeNewController(cId);
            //setNextId();
        }
        else if (v == "0")
        {
            controllerGrid.at(c).setType(ControllerField::NONE);
        }
        else if (v == "4")
        {
            controllerGrid.at(c).setType(ControllerField::BLOCKED);
        }
    }
    setNextId(); 
}

string ControllerManager::getField(int id){
    return to_string(controllerGrid.at(id).getControllerType());
}

bool ControllerManager::blockedByKnob(int i)
{
    if(i-1 >= 0 && controllerGrid.at(i-1).getControllerType() == ControllerField::KNOB){
        
        return true;
    }
    return false;
}
bool ControllerManager::blockedBySlider(int i)
{
    if(i-6 >= 0 && controllerGrid.at(i-6).getControllerType() == ControllerField::SLIDER)
    {
        
        return true;
    }
    return false;
}
string ControllerManager::getControllerId(int iD)
{
    if(controllerGrid.at(iD).controllerExsist()){
        if (controllerGrid.at(iD).getControllerType() != 0 && !controllerGrid.at(iD).getControllerType() != 4 )
        {
            return to_string(controllerGrid.at(iD).getControllerId());
            
        }
    
    }
    return to_string(-1);
}
