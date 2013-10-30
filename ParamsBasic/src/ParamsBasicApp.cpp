#include "cinder/app/AppBasic.h"
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Camera.h"
#include "cinder/params/Params.h"
#include "InterfaceReceiver.h"
#include "cinder/ObjLoader.h"
#include "cinder/gl/Vbo.h"

using namespace ci;
using namespace ci::app;

GLfloat no_mat[]			= { 0.0, 0.0, 0.0, 1.0 };
GLfloat mat_ambient[]		= { 0.6, 0.3, 0.4, 1.0 };
GLfloat mat_diffuse[]		= { 0.3, 0.5, 0.8, 1.0 };
GLfloat mat_specular[]		= { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_emission[]		= { 0.0, 0.1, 0.3, 0.0 };

GLfloat mat_shininess[]		= { 128.0 };
GLfloat no_shininess[]		= { 0.0 };

class ParamsBasicApp : public AppNative {
  public:
	void prepareSettings( Settings *settings ) { settings->enableHighDensityDisplay(); }
	void setup();
	void resize();
	void draw();
	void button();
	void update();
	CameraPersp				mCam;
	params::InterfaceGlRef	mParams;
	float					mObjSize;
	Quatf					mObjOrientation;
	Vec3f					mLightDirection;
    Vec3f                   mEye;
	ColorA					mColor;
	std::string				mString;
    float                   mCameraDistance;
    InterfaceReceiver       receiver;
    float drawCube;
    
    float r,g,b,x,y,z,a,e,c,d;
    
    TriMesh			mMesh;
	gl::VboMesh		mVBO;
    
};

void ParamsBasicApp::setup()
{
    
    ObjLoader loader( (DataSourceRef)loadResource( "Final_sculpture3.obj" ) );
	loader.load( &mMesh );
    a = 1;
    e = 1;
    c = 1;
	mVBO = gl::VboMesh( mMesh );
    mMesh.recalculateNormals();
        mCameraDistance = 25;
    receiver.setup(3000);
	mObjSize = 4;
    mEye = Vec3f(-1,0.8f,1);
	mLightDirection = Vec3f( -0.54f, -0.27f, -1.07f );
	mColor = ColorA( 0.25f, 0.5f, 1.0f, 1.0f );
    mCam.setPerspective( 60.0f, getWindowAspectRatio(), 0.1f, 30000.0f );
	// setup our default camera, looking down the z-axis
	mCam.lookAt( mEye, Vec3f(0,0,0) );
    
	// Setup the parameters
	mParams = params::InterfaceGl::create( getWindow(), "App parameters", toPixels( Vec2i( 200, 400 ) ) );
	mParams->addParam( "Cube Size", &mObjSize, "min=0.1 max=20.5 step=0.5 keyIncr=z keyDecr=Z" );
	mParams->addParam( "Cube Rotation", &mObjOrientation );
	//mParams->addParam( "Cube Color", &mColor, "" );
	mParams->addSeparator();
	mParams->addParam( "Light Direction", &mLightDirection, "" );
	mParams->addButton( "Button!", std::bind( &ParamsBasicApp::button, this ) );
	mParams->addText( "text", "label=`This is a label without a parameter.`" );
	mParams->addParam( "String ", &mString, "" );
    mParams->addParam( "Eye Distance", &mCameraDistance, "min=1.0 max=100.0 step=1.0 keyIncr=s keyDecr=w" );
    
    
    
    
}


void ParamsBasicApp::update(){
    receiver.update();
    
    drawCube = receiver.getValue(0);
    mCameraDistance = receiver.getValue(1,1,100);
    r = receiver.getValue(2);
    g = receiver.getValue(3);
//    b = receiver.getValue(4);
    a = receiver.getValue(4,-1,1);
    e = receiver.getValue(5,-1,1);
    c = receiver.getValue(6,-1,1);
//    x = receiver.getValue(8,-1,1);
//    y = receiver.getValue(9,-1,1);
//    z = receiver.getValue(10,-1,1);
    mEye = Vec3f(a,e,c);
     Color( CM_HSV, 0.7f, 0.85f, 1.0f );
    mColor.set(r, g, b,1);
    mColor.set( Color( CM_HSV, r, g, 1 ));
    Vec3f nDist = mEye * mCameraDistance;
    mCam.lookAt( nDist,Vec3f( 0, 0, 0 ) );
//    mObjOrientation.set(a, e, c, d);
//    mLightDirection.set(x, y, z);
//    mLightDirection.rotateX(x);
//    mLightDirection.rotateX(y);
//    mLightDirection.rotateX(z);
    console() << a << e << c << endl;
}

void ParamsBasicApp::button()
{
	app::console() << "Clicked!" << std::endl;
	mParams->setOptions( "text", "label=`Clicked!`" );
}

void ParamsBasicApp::resize()
{
	mCam.setAspectRatio( getWindowAspectRatio() );
}

void ParamsBasicApp::draw()
{
	// this pair of lines is the standard way to clear the screen in OpenGL
	gl::enableDepthRead();
	gl::enableDepthWrite();
	gl::clear( Color( 0.1f, 0.1f, 0.1f ) );

	glLoadIdentity();
	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );	
	GLfloat lightPosition[] = { -mLightDirection.x, -mLightDirection.y, -mLightDirection.z, 0.0f };
	glLightfv( GL_LIGHT0, GL_POSITION, lightPosition );
	glMaterialfv( GL_FRONT, GL_DIFFUSE,	mColor );
    glMaterialfv( GL_FRONT, GL_AMBIENT,	mat_ambient );
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular );
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess );
    glMaterialfv( GL_FRONT, GL_EMISSION, mat_emission );
    glShadeModel( GL_FLAT );
	gl::setMatrices( mCam );
//	gl::rotate( mObjOrientation );
	gl::color( mColor);
    if(drawCube == 1){
        gl::pushMatrices();
        
        gl::translate(Vec3f::zero());
        gl::draw( mMesh );
        gl::popMatrices();
    }
	// Draw the interface
//	mParams->draw();
    
}

CINDER_APP_BASIC( ParamsBasicApp, RendererGl )
