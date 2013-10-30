#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "Manager.h"
#include <vector>
using namespace ci;
using namespace ci::app;
using namespace std;

class ModularesInterfaceApp : public AppNative {
  public:
    //Functions
	void setup();
    void prepareSettings( Settings *settings );
	void mouseDown( MouseEvent event );
    void	touchesBegan( TouchEvent event );
//	void	touchesMoved( TouchEvent event );
//	void	touchesEnded( TouchEvent event );
	void update();
	void draw();

    //Objects
    Manager mManager;
    //vectors
    
    //Lists
    
    //Vecs
    Vec2f mOrigin;
    Vec2f mSize;
    Vec2f mSingle;
    Vec2f mDouble;
    Vec2f mLong;
};

void ModularesInterfaceApp::prepareSettings( Settings *settings )
{
	settings->enableMultiTouch();
    
}
void ModularesInterfaceApp::setup()
{
    mOrigin = Vec2f(0,0);
    mSize = getWindowSize();
    mSingle = Vec2f(getWindowWidth()/6,getWindowHeight()/4);
    mDouble = Vec2f(mSingle.x*2,mSingle.y);
    mLong = Vec2f(mSingle.x,mSingle.y*2);
    mManager.setup(mOrigin, mSize, mSingle, mDouble, mLong);
}

void ModularesInterfaceApp::mouseDown( MouseEvent event )
{
}

void ModularesInterfaceApp::touchesBegan(TouchEvent event)
{
    console() << "TouchBegan: " << event << endl;
    mManager.touchBegan(event);
}

void ModularesInterfaceApp::update()
{
    mManager.update();
}

void ModularesInterfaceApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    gl::color(1.0f, 1.0f, 1.0f);
    mManager.draw();
}

CINDER_APP_NATIVE( ModularesInterfaceApp, RendererGl )
