//
//  Button.cpp
//  ModularsInterface_02
//
//  Created by Florian Born on 04.09.13.
//
//

#include "Button.h"



Button::Button(Vec2f pos, Vec2f size, string name, int view, int linkedView){
    mPos = pos;
    mSize = size;
    mName = name;
    mView = view;
    mLinkedView = linkedView;
    mBounding = Rectf(mPos, mPos+mSize);
    mFont.getNames();
    mFont = Font( "Helvetica", 25 );
    txt =new TextBox();
    txt->color(Color(1,1,1)).font(mFont).size( Vec2i( size.x, TextBox::GROW ) ).text( mName ).setAlignment(TextBox::CENTER);
    mTextTexture = gl::Texture( txt->render() );
    
}

bool Button::hittest(Vec2f touch){
    return mBounding.contains(touch);
}

void Button::draw(){
    gl::color(1, 0, 0);
    gl::drawSolidRect(mBounding);
    gl::color(1, 1, 1);
    gl::drawStrokedRect(mBounding);
    gl::enableAlphaBlending();
    gl::pushMatrices();
    gl::translate(mPos+Vec2f(20,20));
    gl::draw(mTextTexture);
    gl::popMatrices();
    gl::disableAlphaBlending();
    //gl::drawString(mName, mPos + Vec2f(20,20));
    
}

void Button::draw(Color c){
    gl::color(c);
    gl::drawSolidRect(mBounding);
    gl::color(1, 1, 1);
    gl::drawStrokedRect(mBounding);
    gl::enableAlphaBlending();
    gl::pushMatrices();
    gl::translate(mPos+Vec2f(0,20));
    gl::draw(mTextTexture);
    gl::popMatrices();
    gl::disableAlphaBlending();
    //gl::drawString(mName, mPos + Vec2f(20,20));
    
}

void Button::printName()
{
    console() << "You Hit: " << mName << endl;
}