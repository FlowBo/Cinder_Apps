#include "cinder/Cinder.h"
#include "cinder/app/AppNative.h"
#include "cinder/System.h"
#include "cinder/Rand.h"

#include "OscSender.h"

using namespace ci;
using namespace ci::app;
using namespace std;
#include <vector>
#include <map>
#include <list>



struct TouchPoint {
	TouchPoint() {}
	TouchPoint( const Vec2f &initialPt, const Color &color ) : mColor( color ), mTimeOfDeath( -1.0 )
	{
		mLine.push_back( initialPt );
	}
	
	void addPoint( const Vec2f &pt ) { mLine.push_back( pt ); }
	
	void draw() const
	{
		if( mTimeOfDeath > 0 ) // are we dying? then fade out
			gl::color( ColorA( mColor, ( mTimeOfDeath - getElapsedSeconds() ) / 2.0f ) );
		else
			gl::color( mColor );
        
		gl::draw( mLine );
	}
	
	void startDying() { mTimeOfDeath = getElapsedSeconds() + 2.0f; } // two seconds til dead
	
	bool isDead() const { return getElapsedSeconds() > mTimeOfDeath; }
	
	PolyLine<Vec2f>	mLine;
	Color			mColor;
	float			mTimeOfDeath;
};

// We'll create a new Cinder Application by deriving from the BasicApp class
class OSC_011App : public AppNative {
public:
	void	prepareSettings( Settings *settings );
    
    osc::Sender sender;
    int     port;
    std::string host;
	void	touchesBegan( TouchEvent event );
	void	touchesMoved( TouchEvent event );
	void	touchesEnded( TouchEvent event );
    
    float positionX;
    float positionY;
    
	void	setup();
    void    update();
	void	draw();
	void	keyDown( KeyEvent event ) { setFullScreen( ! isFullScreen() ); }
	
	map<uint32_t,TouchPoint>	mActivePoints;
	list<TouchPoint>			mDyingPoints;
};

void OSC_011App::setup()
{
    port = 3000;
    host = System::getIpAddress();
	if( host.rfind( '.' ) != string::npos )
		host.replace( host.rfind( '.' ) + 1, 3, "255" );
	sender.setup( host, port, true );
	console() << "MT: " << System::hasMultiTouch() << " Max points: " << System::getMaxMultiTouchPoints() << std::endl;
}

void OSC_011App::update(){
    int counter = 0;
	
	osc::Message message0;
    //osc::Message message1;
	message0.addFloatArg(positionX);
    message0.addFloatArg(positionY);
	message0.setAddress("/cinder/osc/0");
	message0.setRemoteEndpoint(host, port);
	sender.sendMessage(message0);
}

void OSC_011App::prepareSettings( Settings *settings )
{
	settings->enableMultiTouch();
}

void OSC_011App::touchesBegan( TouchEvent event )
{
    console() << "Began: " << event << std::endl;
	for( vector<TouchEvent::Touch>::const_iterator touchIt = event.getTouches().begin(); touchIt != event.getTouches().end(); ++touchIt ) {
		Color newColor( CM_HSV, Rand::randFloat(), 1, 1 );
		mActivePoints.insert( make_pair( touchIt->getId(), TouchPoint( touchIt->getPos(), newColor ) ) );
	}
}

void OSC_011App::touchesMoved( TouchEvent event )
{
    console() << "Moved: " << event << std::endl;
	for( vector<TouchEvent::Touch>::iterator touchIt = event.getTouches().begin(); touchIt != event.getTouches().end(); ++touchIt ){
		mActivePoints[touchIt->getId()].addPoint( touchIt->getPos() );
        Vec2f vec = touchIt->getPos();
        positionX = vec.x;
        positionY = vec.y;
    }
}

void OSC_011App::touchesEnded( TouchEvent event )
{
    console() << "Ended: " << event << std::endl;
	for( vector<TouchEvent::Touch>::const_iterator touchIt = event.getTouches().begin(); touchIt != event.getTouches().end(); ++touchIt ) {
		mActivePoints[touchIt->getId()].startDying();
		mDyingPoints.push_back( mActivePoints[touchIt->getId()] );
		mActivePoints.erase( touchIt->getId() );
	}
}

void OSC_011App::draw()
{
	gl::enableAlphaBlending();
	gl::setMatricesWindow( getWindowSize() );
	gl::clear( Color( 0.1f, 0.1f, 0.1f ) );
    
	for( map<uint32_t,TouchPoint>::const_iterator activeIt = mActivePoints.begin(); activeIt != mActivePoints.end(); ++activeIt ) {
		activeIt->second.draw();
	}
    
	for( list<TouchPoint>::iterator dyingIt = mDyingPoints.begin(); dyingIt != mDyingPoints.end(); ) {
		dyingIt->draw();
		if( dyingIt->isDead() )
			dyingIt = mDyingPoints.erase( dyingIt );
		else
			++dyingIt;
	}
	
	// draw yellow circles at the active touch points
	gl::color( Color( 1, 1, 0 ) );
	for( vector<TouchEvent::Touch>::const_iterator touchIt = getActiveTouches().begin(); touchIt != getActiveTouches().end(); ++touchIt )
		gl::drawStrokedCircle( touchIt->getPos(), 20.0f );
}

CINDER_APP_NATIVE( OSC_011App, RendererGl )