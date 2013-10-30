#include "cinder/app/AppNative.h"

using namespace ci;
using namespace ci::app;

#include "OscListener.h"

class OSCListenerApp : public AppNative {
public:
	void setup();
	void update();
	void draw();
	
	osc::Listener 	listener;
	float 			positionX;
    float 			positionY;
};

void OSCListenerApp::setup()
{
	listener.setup( 3000 );
	positionX = 0;
}

void OSCListenerApp::update()
{
	while( listener.hasWaitingMessages() ) {
		osc::Message message;
		listener.getNextMessage( &message );
		
		console() << "New message received" << std::endl;
		console() << "Address: " << message.getAddress() << std::endl;
		console() << "Num Arg: " << message.getNumArgs() << std::endl;
        try {
            positionX = message.getArgAsFloat(0);
            console() << "X: " << positionX << std::endl;
            positionY = message.getArgAsFloat(1);
            console() << "Y: " << positionY << std::endl;
        } catch (...) {
            console() << "no Data" << std::endl;
        }
        
        
		/*for (int i = 0; i < message.getNumArgs(); i++) {
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
        
        if( message.getNumArgs() != 0 && message.getArgType( 0 ) == osc::TYPE_FLOAT )
            positionX = message.getArgAsFloat(0);
	}*/
    }
}

void OSCListenerApp::draw()
{
	gl::clear();
	gl::color( Color::white() );
	gl::drawSolidCircle(Vec2f(positionX,positionY), 20);
}

CINDER_APP_NATIVE( OSCListenerApp, RendererGl )