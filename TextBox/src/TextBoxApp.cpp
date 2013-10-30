#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "panel.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class TextBoxApp : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    
    Panel cont;
};

void TextBoxApp::setup()
{
//    cont = Controller();
//    c.setup();
}

void TextBoxApp::mouseDown( MouseEvent event )
{
}

void TextBoxApp::update()
{
}

void TextBoxApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
//    c.draw();
}

CINDER_APP_NATIVE( TextBoxApp, RendererGl )
