#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Xml.h"
#include "Resources.h"
#include "cinder/gl/Texture.h"
//#include <list>

using namespace ci;
using namespace ci::app;
using namespace std;

class XMLExampleApp : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    gl::Texture myTexture;
};

void XMLExampleApp::setup()
{
    DataSourceRef source = loadResource( "layouts.xml" );
    XmlTree data = XmlTree( source );
    if(data.hasChild("layout"))
    {

        int lastId = data.getChildren().back()->getAttributeValue<int>("id");
        XmlTree lay("layout","");
        lay.setAttribute("id", lastId++);
        for(int i = 0 ; i < 22; i++){
            lay.push_back(XmlTree("field","button").setAttribute("id", i));
        }
        data.push_back(lay);
        data.write( writeFile( source->getFilePath() ) );
        console() << XmlTree(source) << endl;
        console() << data << endl;


    }
    else{
        XmlTree lay("layout","");
        lay.setAttribute("id", 0);
        for(int i = 0 ; i < 22; i++){
            lay.push_back(XmlTree("field","button").setAttribute("id", i));
        }
        data.push_back(lay);
        data.write( writeFile( source->getFilePath() ) );
        console() << XmlTree(source) << endl;
        console() << data << endl;

    }
       
    
    
}   


void XMLExampleApp::mouseDown( MouseEvent event )
{
}

void XMLExampleApp::update()
{
//    DataSourceRef source = loadResource( "layouts.xml" );
//    XmlTree data = XmlTree( source );
//    console() << data << endl;
}

void XMLExampleApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
//    gl::draw(myTexture,Vec2f(0,0));
    gl::color(1, 0, 0);
    gl::drawString(std::to_string( getElapsedSeconds()), Vec2f(20,20));
}

CINDER_APP_NATIVE( XMLExampleApp, RendererGl )
