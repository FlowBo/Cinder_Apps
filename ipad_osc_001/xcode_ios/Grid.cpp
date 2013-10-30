//
//  Grid.cpp
//  ipad_osc_001
//
//  Created by Florian Born on 22.07.13.
//
//


//step = app::getWindowHeight() / 4;
//step2 = app::getWindowWidth() / 6;


#include "Grid.h"
Grid::Grid(){

}

Grid::Grid(Vec2i size){
    mSize = size;
    steps = *new Vec2i(size.x/6,size.y/4);
    console() << mSize << endl;
    console() << steps << endl;
}
Vec2i Grid::getSize(){
    return mSize;
}
void Grid::draw(){

//    gl::color(255.0, 255.0, 255.0);
//    for(int i = 0; i < mSize.x ;i += steps.x){
//        gl::drawLine(Vec2f(0,i), Vec2f(mSize.x,i));
//    }
//    for(int i = 0; i < mSize.y;i += steps.y){
//        gl::drawLine(Vec2f(i,0), Vec2f(i,mSize.y));
//    }

    gl::color(255.0, 255.0, 255.0);
    for(int i = 0; i < mSize.y;i += steps.y){
        gl::drawLine(Vec2f(0,i), Vec2f(mSize.x,i));
    }
    for(int i = 0; i < mSize.y ;i += steps.x){
        gl::drawLine(Vec2f(i,0), Vec2f(i,mSize.y));
    }

}
