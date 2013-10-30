//
//  Panel_Button.cpp
//  ModulInterface
//
//  Created by Florian Born on 21.08.13.
//
//

#include "Panel_Button.h"



Panel_Button::Panel_Button(Vec2f pos, Vec2i size, string text,int id, int view, Font f){
    mPos = pos;
    mSize = size;
    mText = text;
    mNextViewId = view;
    mFont = f;
    setup();
}
void Panel_Button::setup(){

    mField = Rectf(Area( mPos,mSize+mPos));
    console() << mField << endl;
    mTextField.setFont(mFont);
    mTextField.setColor(Color( 1, 1, 0 ));
    mTextField.setText(mText);
    mType = gl::Texture(mTextField.render());
    console() << "Id: " << mNextViewId << "  mPos: " << mPos << endl;
    
}

void Panel_Button::draw(Color c){
    
    gl::pushMatrices();
    gl::color(c);
    gl::drawSolidRect(mField);
    gl::color(1, 1, 1);
    gl::drawStrokedRect(mField);
    gl::enableAlphaBlending(true);
    gl::drawString(mText, mPos+Vec2f(30,85/2),ColorA(1,1,1,1),mFont);
    gl::popMatrices();
    

}

bool Panel_Button::hitTest(Vec2f touch){
    return mField.contains(touch);
}
