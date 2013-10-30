#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "Grid.h"
#include "Spot.h"
#include <list>
#include <vector>
#include "Home_Panel.h"
#include "cinder/Text.h"
#include "cinder/Font.h"
#include "cinder/gl/Texture.h"
#include "Resources.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class ModulInterfaceApp : public AppNative {
public:
    void prepareSettings( Settings *settings );
	void setup();
	void mouseDown( MouseEvent event );
	void update();
	void draw();
    int  getNextSpot(Vec2f touch);
    
	void	touchesBegan( TouchEvent event );
	void	touchesMoved( TouchEvent event );
	void	touchesEnded( TouchEvent event );
    
    Vec2f quadSize;
    Vec2f oneOne;
    

    float   timeBuffer;
    
    Grid    mGrind;
    vector<Spot> mSpots;
    
    Shape2d mShape;
    Path2d mPath;
    
    int  controllerType;
    
    
    bool touchBegan;
    
    
//    Home_Panel mHomePanel;
    vector <Panel> mMenuPanels;
    Vec2f mMenuOrigin;
    int activMenuPanel;
    
    bool mCalibrating;
};

void ModulInterfaceApp::setup()
{
    mMenuOrigin = Vec2f(512,768);
    quadSize = Vec2f(256,256);
    activMenuPanel = 0;
    mMenuPanels.push_back(Panel(0,mMenuOrigin,quadSize));
    mMenuPanels.push_back(Panel(1,mMenuOrigin,quadSize));

 
    int ids = 0;
    for (int y = 0; y < app::getWindowHeight(); y+=app::getWindowHeight()/4) {
        for (int x = 0; x < app::getWindowWidth(); x+=app::getWindowWidth()/6) {
            if (ids < 22) {
                mSpots.push_back(Spot(Vec2f(x,y),oneOne,ids));
            }
            
            ids++;
        }
        
    }
    
}

void ModulInterfaceApp::prepareSettings( Settings *settings )
{
	settings->enableMultiTouch();

}


void ModulInterfaceApp::mouseDown( MouseEvent event )
{
}


void ModulInterfaceApp::touchesBegan( TouchEvent event )
{
    console() << "Began: " << event << std::endl;
    Vec2f touch;
    if(getActiveTouches().size() == 1){
        vector<TouchEvent::Touch>::const_iterator touchIt = getActiveTouches().begin();
        touch = touchIt->getPos();
    }
    Panel a = mMenuPanels.at(activMenuPanel);
    if(mCalibrating && a.contain(touch)==false){
        if (getActiveTouches().size() == 1) {
            int nextSpot = getNextSpot(touch);
            if (!mSpots.at(nextSpot).isUsed()){
                mSpots.at(nextSpot).activate();
            }
//            else if (mSpots.at(nextSpot).isUsed() && mSpots.at(nextSpot).quit(touch)) {
//                mSpots.at(nextSpot).deactivate();
//                console() << "Deactivate" << endl;
//                touchBegan = false;
//            }
            else{
                for (Spot s : mSpots) {
                    s.update(touch);
                }
            }
            
        }
    }

    if(a.contain(touch)){
        
        activMenuPanel = a.hitTest(touch);
        
        if (activMenuPanel == 1) {
            mCalibrating = true;
        }
        else{
            mCalibrating = false;
        }
    }

}
void ModulInterfaceApp::touchesMoved( TouchEvent event )
{
    console() << "Moved: " << event << std::endl;
}

void ModulInterfaceApp::touchesEnded( TouchEvent event )
{
    console() << "Ended: " << event << std::endl;
    controllerType = 0;
}



void ModulInterfaceApp::update()
{
    
    for (Spot s : mSpots) {
        s.update();
    }
    
    
    
}
int ModulInterfaceApp::getNextSpot(Vec2f touch){
    int nextSpotId = 0;
    float distance;
    
    for(int i = 0; i < mSpots.size() ;i++){
        Spot s = mSpots.at(i);
        if (i == 0) {
            distance = s.getPos().distance(touch);
        }
        if( s.getPos().distance(touch) < distance && touch.x > s.getPos().x && touch.y > s.getPos().y) {
            nextSpotId = i;
            
            distance = s.getPos().distance(touch);
        }
    }
    console() << "ID:" << nextSpotId << endl;
    return nextSpotId;
}

void ModulInterfaceApp::draw()
{
    gl::setMatricesWindow( getWindowSize() );
    gl::clear( Color( 0, 0, 0 ) );
    
    for (Spot s : mSpots) {
        s.draw();
    }
    mGrind.draw();
    mMenuPanels.at(activMenuPanel).draw();
}

CINDER_APP_NATIVE( ModulInterfaceApp, RendererGl )
