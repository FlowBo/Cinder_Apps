//
//  Layout.cpp
//  ipad_osc_001
//
//  Created by Florian Born on 22.07.13.
//
//

#include "Layout.h"



Layout::Layout(){

}
Layout::Layout( Vec2i size){
    mGrid = *new Grid(size);
}
Layout::Layout( AppNative &app){
    mApp = &app;
    mGrid = *new Grid(mApp->getWindowSize());
}
Vec2f Layout::getSize(){
    return mGrid.getSize();
    
}
void Layout::draw(){
    mGrid.draw();
}

void Layout::calibrate(){
    
}