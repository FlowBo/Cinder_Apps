#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Text.h"
#include "cinder/Font.h"
#include "cinder/gl/Texture.h"
#include "cinder/CinderMath.h"


using namespace ci;
using namespace ci::app;
using namespace std;

class coding_01App : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    void prepareSettings( Settings *settings);
    
    TextBox text;
    cinder::Font font;
    
    gl::Texture texture;
    
    int division;
    
    float angle;
};

void coding_01App::prepareSettings( Settings *settings ){
    settings->setWindowSize( 800, 600 );
    settings->setFrameRate( 60.0f );

    
    
}

void coding_01App::setup()
{
    division = 20;
    angle = 10;
    font = Font("Helvetica", 15);
    text = TextBox();
    text.setColor(Color(0,0,0));
    text.setFont(font);
    text.setBackgroundColor(ColorA(0,0,0,0));
}

void coding_01App::mouseDown( MouseEvent event )
{
}

void coding_01App::update()
{
}

void coding_01App::draw()
{
	// clear out the window with black
	gl::clear( Color( 1, 1, 1 ) );
    angle = 1;
    angle *= getMousePos().x/50;
    console() << angle << endl;
    gl::enableAlphaBlending();
    for(int x = 0; x < division ; x++)
    {
        float xValue = x * getWindowWidth()/(division-1);
        float yValue = 100;
        gl::color(0.6, 0.3, 0.0);
        if(x%2 == 0){yValue+=50;};
        gl::drawLine(Vec2f(xValue,0), Vec2f(xValue,yValue));
        text.setText(to_string(x));
        texture = text.render();
        gl::draw(texture, Vec2f(xValue+5,yValue-10));
    }
    gl::disableAlphaBlending();
    gl::pushMatrices();
    gl::translate(getWindowCenter());
    for(float t = 0; t < 360 ; t += angle)
    {
        
        Vec2f v = Vec2f(math<float>::cos(toRadians(t))*100,math<float>::sin(toRadians(t))*100);
        gl::drawSolidCircle(v, 2);
        
    }
    
    gl::popMatrices();
}

CINDER_APP_NATIVE( coding_01App, RendererGl )
