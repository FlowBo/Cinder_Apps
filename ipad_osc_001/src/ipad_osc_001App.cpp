#define _USE_MATH_DEFINES

#include "cinder/Cinder.h"
#include "cinder/app/AppNative.h"
#include "cinder/System.h"
#include "cinder/Rand.h"
#include "cinder/CinderMath.h"
#include "cinder/Font.h"
#include "OscSender.h"
#include <math.h>
#include "Layout.h"

using namespace ci;
using namespace ci::app;

#include <vector>
#include <map>
#include <list>
using namespace std;

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


class ipad_osc_001App : public AppNative {
public:
    
	void	mouseDown( MouseEvent event );
	void	mouseDrag( MouseEvent event );
    
	void	touchesBegan( TouchEvent event );
	void	touchesMoved( TouchEvent event );
	void	touchesEnded( TouchEvent event );
    
	void	setup();
    void    update();
	void	draw();
	void	keyDown( KeyEvent event ) { setFullScreen( ! isFullScreen() ); }
	
    float   linmap(float val, float inMin, float inMax, float outMin, float outMax);
    
    
	map<uint32_t,TouchPoint>	mActivePoints;
	list<TouchPoint>			mDyingPoints;
    list<Vec2f>                 initVecs;

    
    osc::Sender     sender;
    float           positionX;
    float           positionY;
    float           angle;
    float           angle2;
    float           blackMagic;
	std::string     host;
	int             port;
    int             id;
    Vec2f           pos;
    Vec2f           def;
    Vec2f           center;
    bool            first;
    bool            init;
    int             step;
    int             step2;
    cinder::Font    text_font;    
    Layout          mLayout;
    
    
    
    
    
    
};
float ipad_osc_001App::linmap(float val, float inMin, float inMax, float outMin, float outMax){
    return outMin + (outMax - outMin) * ((val - inMin) / (inMax - inMin));
}
void ipad_osc_001App::setup()
{
    
    mLayout = *new Layout(*this);
    
    
    
    console() << "MT: " << System::hasMultiTouch() << " Max points: " << System::getMaxMultiTouchPoints() << std::endl;
    def = Vec2f(1,0);
    port = 3000;
    host = System::getIpAddress();
    if( host.rfind( '.' ) != string::npos )
		host.replace( host.rfind( '.' ) + 1, 3, "255" );
	sender.setup( host, port, true );
    
    console() << "ip Adresse: " <<host << std::endl;
    console() << "Port: " << port << std::endl;
    id = 1;
    first = true;
    init = true;
    step = app::getWindowHeight() / 4;
    step2 = app::getWindowWidth() / 6;
    console() << "height: "<<app::getWindowHeight() << endl;
    console() << "width: "<< app::getWindowWidth() << endl;
    console() << "x step: "<< step2 << endl;
    console() << "y step: "<< step << endl;
    text_font = *new cinder::Font ("Arial", 16.0);

}

void ipad_osc_001App::update()
{

    if (first && mActivePoints.size()!=0) {
        initVecs.push_back(getActiveTouches().begin()->getPos());
    }
    if(!first && init){
        center = Vec2f(0,0);
        for (Vec2f v : initVecs) {
            center+=v;
        }
        center /= initVecs.size();
        init = false;
    }
	if (mActivePoints.size() != 0) {
        vector<TouchEvent::Touch>::const_iterator touchIt = getActiveTouches().begin();
        pos = touchIt->getPos();
        pos -= center;
        pos.normalize();
        positionX = pos.x;
        positionY = pos.y;
        blackMagic = (atan2(def.x-pos.x,def.y-pos.y) * 180 / M_PI) * 2;
//        blackMagic = toDegrees(( atan2(def.x-pos.x,def.y-pos.y) + M_PI ) % M_PI_2);
        console() << "BlackMagic: " << blackMagic << endl;
    }
    
	osc::Message message;
	message.addFloatArg(positionX);
    message.addFloatArg(positionY);
  	message.addFloatArg(blackMagic);
	message.setAddress("/cinder/osc/" + id);
	message.setRemoteEndpoint(host, port);
	sender.sendMessage(message);
}

void ipad_osc_001App::prepareSettings( Settings *settings )
{
	settings->enableMultiTouch();

}
void ipad_osc_001App::touchesBegan( TouchEvent event )
{
    console() << "Began: " << event << std::endl;
	for( vector<TouchEvent::Touch>::const_iterator touchIt = event.getTouches().begin(); touchIt != event.getTouches().end(); ++touchIt ) {
		Color newColor( CM_HSV, Rand::randFloat(), 1, 1 );
		mActivePoints.insert( make_pair( touchIt->getId(), TouchPoint( touchIt->getPos(), newColor ) ) );
	}
}
void ipad_osc_001App::touchesMoved( TouchEvent event )
{
//    console() << "Moved: " << event << std::endl;
	for( vector<TouchEvent::Touch>::const_iterator touchIt = event.getTouches().begin(); touchIt != event.getTouches().end(); ++touchIt )
		mActivePoints[touchIt->getId()].addPoint( touchIt->getPos() );
}

void ipad_osc_001App::touchesEnded( TouchEvent event )
{
    console() << "Ended: " << event << std::endl;
	for( vector<TouchEvent::Touch>::const_iterator touchIt = event.getTouches().begin(); touchIt != event.getTouches().end(); ++touchIt ) {
		mActivePoints[touchIt->getId()].startDying();
		mDyingPoints.push_back( mActivePoints[touchIt->getId()] );
		mActivePoints.erase( touchIt->getId() );
	}
    first = false;
}

void ipad_osc_001App::mouseDown( MouseEvent event )
{
	console() << "Mouse down: " << event.isRight() << " & " << event.isControlDown() << std::endl;
}

void ipad_osc_001App::mouseDrag( MouseEvent event )
{
	console() << "Mouse drag: " << std::endl;
}

void ipad_osc_001App::draw()
{
    
	gl::enableAlphaBlending();
	gl::setMatricesWindow( getWindowSize() );
	gl::clear( Color( 0.1f, 0.1f, 0.1f ) );
    mLayout.draw();
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
    
    gl::pushMatrices();
    gl::translate(Vec2f(768/2,1024/2));
    gl::drawLine(Vec2f(0,0), pos*50);
    gl::drawLine(Vec2f(0,0), def*50);
    
    gl::popMatrices();
    std::string s = std::to_string(blackMagic);
    std::string tx = "id_01     Value: " + s;
    gl::drawString( tx, Vec2f(50,200),ColorA(1,1,1,1),text_font);
    

    
    
    linmap(angle, 0, 360, 0, 500);
    
//    gl::color(255.0, 255.0, 255.0);
//    for(int i = 0; i < app::getWindowHeight();i += step){
//        gl::drawLine(Vec2f(0,i), Vec2f(app::getWindowWidth(),i));
//    }
//    for(int i = 0; i < app::getWindowHeight();i += step2){
//        gl::drawLine(Vec2f(i,0), Vec2f(i,app::getWindowHeight()));
//    }
//    
}

CINDER_APP_NATIVE( ipad_osc_001App, RendererGl )
