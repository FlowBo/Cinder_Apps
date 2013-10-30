#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "OscListener.h"
#include "cinder/CinderMath.h"
using namespace ci;
using namespace ci::app;
using namespace std;

class mac_osc_001App : public AppNative {
public:
	void setup();
	void update();
	void draw();
	void prepareSettings( Settings *settings );
	osc::Listener 	listener;
	float 			positionX;
   	float 			positionY;
    float           angle;
    float           px,py;
    float           height;
};
void mac_osc_001App::prepareSettings( Settings *settings ){
    settings->setWindowSize( 800, 600 );
    settings->setFrameRate( 60.0f );
}
void mac_osc_001App::setup()
{
    listener.setup( 3000 );
	positionX = 0;
    positionY = 0;
}


void mac_osc_001App::update()
{
    while( listener.hasWaitingMessages() ) {
		osc::Message message;
		listener.getNextMessage( &message );
		
        console() << "Address: " << message.getAddress() << std::endl;
        console() << "Num Arg: " << message.getNumArgs() << std::endl;
        
        
//		console() << "New message received" << std::endl;
//		console() << "Address: " << message.getAddress() << std::endl;
//		console() << "Num Arg: " << message.getNumArgs() << std::endl;
		for (int i = 0; i < message.getNumArgs(); i++) {
			console() << "-- Argument " << i << std::endl;
			console() << "---- type: " << message.getArgTypeName(i) << std::endl;
			if( message.getArgType(i) == osc::TYPE_INT32 ) {
				try {
					console() << "------ value: "<< message.getArgAsInt32(i) << std::endl;
                    
				}
				catch (...) {
					console() << "Exception reading argument as int32" << std::endl;
				}
			}
			else if( message.getArgType(i) == osc::TYPE_FLOAT ) {
				try {
					console() << "------ value: " << message.getArgAsFloat(i) << std::endl;
				}
				catch (...) {
					console() << "Exception reading argument as float" << std::endl;
				}
			}
			else if( message.getArgType(i) == osc::TYPE_STRING) {
				try {
					console() << "------ value: " << message.getArgAsString(i).c_str() << std::endl;
				}
				catch (...) {
					console() << "Exception reading argument as string" << std::endl;
				}
			}
		}
        
//        if( message.getNumArgs() != 0 && message.getArgType( 0 ) == osc::TYPE_FLOAT )
//            positionX = message.getArgAsFloat(0);
        
        positionX = message.getArgAsFloat(0);
        positionY = message.getArgAsFloat(1);
        angle = message.getArgAsFloat(2);

        
        px = math<float>::sin(toRadians(angle))*80;
        py = math<float>::cos(toRadians(angle))*80;
        
	}

}

void mac_osc_001App::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    gl::pushMatrices();
    gl::translate(app::getWindowCenter());
//    gl::color(255, 255, 255);
//    gl::drawSolidRect(Rectf(-500,500,500, angle));
//    gl::color(0, 160, 160);
    gl::drawSolidCircle(Vec2f(positionX,positionY)*50, 10.0);
    gl::drawLine(Vec2f(0,0), Vec2f(px,py) );


    gl::popMatrices();
}

CINDER_APP_NATIVE( mac_osc_001App, RendererGl )
