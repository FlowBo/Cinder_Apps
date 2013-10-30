//
//  InterfaceManager.cpp
//  ModularesInterface
//
//  Created by Florian Born on 01.09.13.
//
//

#include "InterfaceManager.h"


InterfaceManager::InterfaceManager(){
    mActiveViewInterface = 0;
}

void InterfaceManager::setup(Vec2f &origin, Vec2f &size, Vec2f &single, Vec2f &nDouble , Vec2f &nLong )
{
    mMenu.setup(size-nDouble,nDouble);
    mMenu.addButton(Vec2f(0,0),Vec2f(nDouble.x,nDouble.y/3), "First Button",0,1);
    mMenu.addButton(Vec2f(0,nDouble.y/3),Vec2f(nDouble.x,(nDouble.y/3)), "Second Button",0,1);
    mMenu.addButton(Vec2f(0,0),Vec2f(nDouble.x,(nDouble.y/3)), "Second View",1,0);
//    mButtons.push_back(Button(Vec2f(mPos.x, mPos.y+mSize.y/3),Vec2f(mSize.x,(mSize.y/3)), "Second Button",0,2));
//    mButtons.push_back(Button(pos,Vec2f(mSize.x,mSize.y/3), "SecondView",1,0));
}

void InterfaceManager::update()
{
    mActiveViewInterface = mMenu.getActiveView();
    
}

void InterfaceManager::draw()
{
    gl::color(1, 1, 1);
    mMenu.draw(mActiveViewInterface);
}

void InterfaceManager::hitTest(Vec2f touch)
{
    mMenu.hitTest(touch);
}