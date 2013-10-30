//
//  ControllerManager.cpp
//  ModularesInterface
//
//  Created by Florian Born on 01.09.13.
//
//

#include "ControllerManager.h"



ControllerManager::ControllerManager(){
    mActiveViewController = 0;
}

void ControllerManager::setup(Vec2f size, Vec2f single)
{
    int id = 0;
    for (int y = 0; y < size.y; y += size.y/4) {
        for (int x = 0; x < size.x; x += size.x/6) {
            mSpots.push_back(Spot(Vec2f(x,y),single,id));
            id++;
        }
    }
    
    mSpots.erase(mSpots.end()-1);
    mSpots.erase(mSpots.end()-1);
    console() << "Spots: " << mSpots.size() << endl;
    for(Spot s : mSpots){
        console() << s.getId() << endl;
        s.setup();
    }
}

void ControllerManager::draw()
{
    if (mActiveViewController == 1) {
        for(Spot s : mSpots)
        {
            s.draw();
            if(s.getControllerType() == 0){
                s.drawInterface();
            }
            
            else{

            }
        }
    }
}

void ControllerManager::update(int view)
{
    mActiveViewController = view;
    for(Spot s : mSpots){
        s.update();
    }
}

void ControllerManager::hitTest(Vec2f touch){
    for (Spot s : mSpots) {
        if(s.contain(touch)){
            s.hitTest(touch);
        }
    }
    
}