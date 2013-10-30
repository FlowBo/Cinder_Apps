//
//  Panel.cpp
//  ModulInterface
//
//  Created by Florian Born on 21.08.13.
//
//

#include "Panel.h"

Panel::Panel(){
    setup();
    
}

Panel::Panel(int panelId, Vec2f pos,Vec2f size){
    mPos = pos;
    mSize = size;
    mPanelId = panelId;
    mBounding = Rectf(mPos,mPos+mSize);
    setup();
    switch (mPanelId) {
        case 0:
            panelButtons.push_back(Panel_Button(Vec2f(0,0), Vec2f(256,85.4f), "calibrate",0, 1,mFont));
            panelButtons.push_back(Panel_Button(Vec2f(0,85.4f), Vec2f(256,85.4f), "load preset",1, 2, mFont));
            break;
        case 1:
            panelButtons.push_back(Panel_Button(Vec2f(0,0), Vec2f(256,85.4f), "Tab into a field and select controller",0, 100,mFont));
            panelButtons.push_back(Panel_Button(Vec2f(0,85.4f), Vec2f(256,85.4f), "all",1, 2, mFont));
            panelButtons.push_back(Panel_Button(Vec2f(0,2*85.4f), Vec2f(256,85.4f), "home",2, 0, mFont));
            break;
        case 100:
            panelButtons.push_back(Panel_Button(Vec2f(0,0), Vec2f(128,64), "EXIT",100, 101,mFont));
            panelButtons.push_back(Panel_Button(Vec2f(0,64), Vec2f(128,64), "SLIDER",100, 102,mFont));
            panelButtons.push_back(Panel_Button(Vec2f(0,2*64), Vec2f(128,64), "BUTTON",100, 103,mFont));
            panelButtons.push_back(Panel_Button(Vec2f(0,3*64), Vec2f(128,64), "KNOB",100, 104,mFont));
            break;
        default:
            break;
    }
}

void Panel::setup(){
    mFont.getNames();
    mFont = Font("Helvetica", 22.0f);

}

void Panel::draw(){
    gl::pushMatrices();
    gl::translate(mPos);
    for (Panel_Button pb : panelButtons) {
        pb.draw(Color(1,0.5,0));
    }
    gl::popMatrices();
}

int Panel::hitTest(Vec2f touch){
    for(Panel_Button pb : panelButtons){
        if(pb.hitTest(touch-mPos)){
            return pb.getNextView();
        }
    }

    return 0;
}

int Panel::getId(){
    return mPanelId;
}

bool Panel::contain(Vec2f touch){
    if(mBounding.contains(touch)){
        return true;
    }
    else{
        return false;
    }
}
