//
//  Grid.cpp
//  ModulInterface
//
//  Created by Florian Born on 16.08.13.
//
//

#include "Grid.h"


Grid::Grid(){
    
}

void Grid::draw(){
    gl::color(0, 255, 255);
    for (int i = 0; i < app::getWindowWidth(); i += app::getWindowWidth()/6) {
        gl::drawLine(Vec2f(i,0), Vec2f(i,app::getWindowHeight()));
        
    }
    for (int i = 0; i < app::getWindowHeight(); i += app::getWindowHeight()/4) {
        gl::drawLine(Vec2f(0,i), Vec2f(getWindowWidth(),i));
    }
    
}

void Grid::drawPoints(){

    
    
}