#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class iPadTestApp : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
};

void iPadTestApp::setup()
{
}

void iPadTestApp::mouseDown( MouseEvent event )
{
}

void iPadTestApp::update()
{
}

void iPadTestApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_NATIVE( iPadTestApp, RendererGl )
