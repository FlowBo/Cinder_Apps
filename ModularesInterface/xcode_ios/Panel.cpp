//
//  Panel.cpp
//  ModularesInterface
//
//  Created by Florian Born on 01.09.13.
//
//

#include "Panel.h"


Panel::Panel()
{
    
}

void Panel::setup(Vec2f pos, Vec2f size)
{
    mPos = pos;
    mSize = size;
    mActiveView = 0;
    mBounding = Rectf(mPos,mPos+mSize);
}

void Panel::draw(int view)
{
    
    gl::color(1, 1, 1);
    gl::drawStrokedRect(mBounding);
    for (Button b : mButtons) {
        if(b.getView() == view)
        {
            b.draw();
        }
    }
}

void Panel::addButton(Vec2f pos, Vec2f size, string name, int view, int link)
{
    mButtons.push_back(Button(mPos+pos,size,name,view,link));
}

void Panel::hitTest(Vec2f touch)
{
    for(Button b : mButtons)
    {
        
        if(b.hitTest(touch) && mActiveView == b.getView())
        {
            this->mActiveView = b.getLink();
            console() << "------------------------------" << mActiveView << endl;
            break;
        }       
    }

}

