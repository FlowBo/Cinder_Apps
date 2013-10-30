//
//  Button.cpp
//  ModularesInterface
//
//  Created by Florian Born on 01.09.13.
//
//

#include "Button.h"


Button::Button(){
    
    
}

Button::Button(Vec2f pos, Vec2f size, string name, int view, int link)
{
    mPos = pos;
    mSize = size;
    mBounding = Rectf(mPos,mPos+mSize);
    mName = name;
    mView = view;
    mLink = link;
    console() << mName << ": " << mBounding << "  Link: " << mLink << endl;
}

void Button::draw()
{
    gl::color(1, 1, 1);
    gl::drawSolidRect(mBounding);

    gl::enableAlphaBlending();
    
    gl::color(0,0,0);
    gl::drawStrokedRect(mBounding);
    gl::drawString(mName, mPos+Vec2f(50,50));
}

bool Button::hitTest(Vec2f touch)
{
    if (mBounding.contains(touch)) {
        console() << mName << endl;
        return true;
    }
    else
    {
        return false;
    }
}

