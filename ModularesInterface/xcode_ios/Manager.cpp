//
//  Manager.cpp
//  ModularesInterface
//
//  Created by Florian Born on 01.09.13.
//
//

#include "Manager.h"



Manager::Manager()
{
    
}

void Manager::setup()
{
    
}

void Manager::setup(Vec2f &origin, Vec2f &size, Vec2f &single, Vec2f &nDouble , Vec2f &nLong)
{
    console() << "Origin: " << origin << endl;
    mInterfaceManager.setup(origin,size,single, nDouble, nLong);
    mControllerManager.setup(size,single);
}

void Manager::update()
{
    mInterfaceManager.update();
    mControllerManager.update(mInterfaceManager.getActiveViewInterface());
}

void Manager::draw()
{
    mInterfaceManager.draw();
    mControllerManager.draw();
}

void Manager::touchBegan(TouchEvent touch)
{
    Vec2f touchPos = touch.getTouches().begin()->getPos();
    mInterfaceManager.hitTest(touchPos);
    mControllerManager.hitTest(touchPos);
}