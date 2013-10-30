//
//  Home_Panel.cpp
//  ModulInterface
//
//  Created by Florian Born on 21.08.13.
//
//

#include "Home_Panel.h"


Home_Panel::Home_Panel(){
    mPos = Vec2f(512,768);
    mBounding.set(mPos.x, mPos.y,768,1024);
//    panels.push_back(Panel(0));
//    panels.push_back(Panel(1));
    mActivePanel = 0;
    
}

void Home_Panel::hitTest(Vec2f touch){
    
    for(Panel p : panels){
        if(p.getId()== mActivePanel){
            mActivePanel =  p.hitTest(touch-mPos);
            console() << "ActivPanel: "<< mActivePanel << endl;
            break;
        }
    }
}
bool Home_Panel::inside(Vec2f touch){
    if(mBounding.contains(touch)){
        return true;
    }
    else{
        return false;
    }
}
void Home_Panel::draw(){
    gl::pushMatrices();
    gl::translate(mPos);
    for(Panel p : panels){
        if(p.getId() == mActivePanel){
            p.draw();
        }
    }
    gl::popMatrices();
}