//
//  panel.cpp
//  TextBox
//
//  Created by Florian Born on 22.08.13.
//
//

#include "panel.h"
Panel::Panel(){
    setup();
}

void Panel::setup(){
    text = "HALLO";
    f.getNames();
    for (string s : f.getNames()) {
        console() << s << endl;
    }
//    f = Font("Helvetica", 28);
//    textBox.setFont(f);
//    textBox.setColor(Color(1,1,1));
//    textBox.setText(text);
//    texture = gl::Texture(textBox.render());
}

void Panel::draw(){
    gl::draw(texture);
}