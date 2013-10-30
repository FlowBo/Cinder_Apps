//
//  ControllerManager.h
//  ModularsInterface_02
//
//  Created by Florian Born on 04.09.13.
//
//

#pragma once
#include "cinder/app/AppNative.h"
#include "ControllerField.h"
#include "OscSender.h"
#include "cinder/Xml.h"

using namespace ci;
using namespace ci::app;
using namespace std;


class ControllerManager{
    
public:
    ControllerManager();
    enum State { CALIBRATING, FREEZE};
    void initialize(Vec2f windowSize, Vec2f size);
    void touchStarted(TouchEvent event);
    void touchesEnded(TouchEvent event);
    void touchMoved(TouchEvent event);
    void draw();
    void update();
    inline void setState(State s) {state = s;};
    inline State getState() {return state;};
    
    inline void setOsc(osc::Sender &osc,string h, int p ){oscSender = &osc, host = h, port = p ;};
    
    void checkNewValues();
//    void checkNewController();
    void clearControllers();
    void sendNewControllerValue(int iD, float value);
    void setNextId();
    bool checkId(int iD);
    Vec3i getControllers();
    void loadLayout(XmlTree& layout);
    string getField(int id);
    string getControllerId(int iD);
    bool blockedBySlider(int i);
    bool blockedByKnob(int i);
private:
    vector<ControllerField> controllerGrid;
    State state;
    int controllerIdCounter;
    osc::Sender* oscSender;
    string host;
    int port;
    
};