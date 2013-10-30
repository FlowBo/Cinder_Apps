#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "Button.h"
#include "ControllerManager.h"
#include "cinder/System.h"
#include "OscSender.h"
#include "cinder/Utilities.h"

#include "cinder/Font.h"
#include "cinder/Text.h"
#include "cinder/gl/Texture.h"

#include "cinder/Xml.h"
#include <list>


using namespace ci;
using namespace ci::app;
using namespace std;



class ModularsInterface_02App : public AppNative {
  public:
	void setup();
    void prepareSettings( Settings *settings );
	void mouseDown( MouseEvent event );
    void touchesBegan( TouchEvent event );
    void touchesEnded( TouchEvent event );
    void touchesMoved( TouchEvent event );
	void update();
	void draw();
    void saveLayout();
    
    int view;
    int port;
    
    vector<Button> buttons;
    
    ControllerManager controllerManager;
    osc::Sender sender;
    Font mFontSmall;
    Font mFontBig;
    TextBox *mTextbox;
    gl::Texture mTextTexture;
    gl::Texture mStatus;
    gl::Texture mController;
    gl::Texture mLayoutBarTex;
    
    Vec2f fieldSize;
    Vec2f menuPos;
    
    string host;
    
    TextBox *mStatusBar;
    TextBox *mControllerCounter;
    
    TextBox *layoutBar;
    
    XmlTree& getLayout(XmlTree xml, int num);
    int layoutCounter;
    XmlTree sendableLayout;
    
    
    DataSourceRef source;
    XmlTree data;
    
    Color lightGrey;
    Color darkGrey;
};

void ModularsInterface_02App::prepareSettings( Settings *settings )
{
    settings->enableMultiTouch();
    settings->setFrameRate(30.0);
}

void ModularsInterface_02App::setup()
{
    
    lightGrey = Color(0.75f,0.75f,0.75f);
    darkGrey = Color(0.25f,0.25f,0.25f);
//    source = loadResource( "layouts.xml" );
    fs::path p1 = getDocumentsDirectory() / "layouts.xml" ;
    if(fs::exists( p1) == false){
        XmlTree doc = XmlTree::createDoc();
        doc.write(writeFile(p1));
    }
    
    console() << p1 << endl;
    
    source = loadFile(p1);
    data = XmlTree( source );
    
//	activeLayout = new XmlTree();
    layoutCounter = 0;
    view = 0;
    fieldSize = Vec2f(getWindowWidth()/6,getWindowHeight()/4);
    menuPos = Vec2f((getWindowWidth()/6)*4,(getWindowHeight()/4)*3);
    controllerManager.initialize(getWindowSize(), fieldSize);
    
    port = 3000;
	// assume the broadcast address is this machine's IP address but with 255 as the final value
	// so to multicast from IP 192.168.1.100, the host should be 192.168.1.255
	host = System::getIpAddress();
	if( host.rfind( '.' ) != string::npos )
		host.replace( host.rfind( '.' ) + 1, 3, "255" );
	sender.setup( "Florians-MacBook-Pro.local", port, true );
    console() << "IP-Adresse: " << host << endl;
    controllerManager.setOsc(sender,host,port);


    mFontBig = Font( "Helvetica", 22 );
    mTextbox = new TextBox();
    mTextbox->color(Color(1,1,1)).font(mFontBig).size( Vec2f( fieldSize.x*2, fieldSize.y/3 ) ).text( "\ntab into a field to add\nor delete controllers" ).backgroundColor(darkGrey).setAlignment(TextBox::CENTER) ;
    mTextTexture = gl::Texture( mTextbox->render() );
    
    mStatusBar = new TextBox();
    mFontSmall = Font("Helvetica", 14);
    mStatusBar->color(Color(1,1,1)).font(mFontSmall).size( Vec2f( fieldSize.x+fieldSize.x/3+1, fieldSize.y/3 ) ).text( "\n  host: " + host + "\n  port: "+ std::to_string( port )).backgroundColor(darkGrey).setAlignment(TextBox::LEFT);
    mStatus = gl::Texture(mStatusBar->render());

    
    
    
    mControllerCounter = new TextBox();
    mControllerCounter->color(Color(1,1,1)).font(mFontSmall).size( Vec2f( fieldSize.x, fieldSize.y/3 ) ).backgroundColor(darkGrey).setAlignment(TextBox::LEFT);
    //View 0
    buttons.push_back(Button(menuPos,Vec2f(fieldSize.x*2,fieldSize.y/3),"calibrate",0,1));
    buttons.push_back(Button(Vec2f(menuPos.x, menuPos.y+fieldSize.y/3),Vec2f(fieldSize.x,fieldSize.y/3),"load",0,3));
    buttons.push_back(Button(Vec2f(menuPos.x+fieldSize.x, menuPos.y+fieldSize.y/3),Vec2f(fieldSize.x,fieldSize.y/3),"save",0,4));
    //view 1
    buttons.push_back(Button(Vec2f(menuPos.x,menuPos.y+fieldSize.y/3),Vec2f(fieldSize.x,fieldSize.y/3),"done",1,0));
    buttons.push_back(Button(Vec2f(menuPos.x+fieldSize.x,menuPos.y+fieldSize.y/3),Vec2f(fieldSize.x,fieldSize.y/3),"clear\nall",1,2));
    //view 3
    
    buttons.push_back(Button(Vec2f(menuPos.x,menuPos.y+fieldSize.y/3),Vec2f(fieldSize.x,fieldSize.y/3),"done",3,0));
    buttons.push_back(Button(Vec2f(menuPos.x+fieldSize.x,menuPos.y+fieldSize.y/3),Vec2f(fieldSize.x,fieldSize.y/3),"load",3,5));
    
    buttons.push_back(Button(Vec2f(menuPos.x,menuPos.y),Vec2f(fieldSize.x/2,fieldSize.y/3),"prev",3,10));
    buttons.push_back(Button(Vec2f(menuPos.x+fieldSize.x+fieldSize.x/2,menuPos.y),Vec2f(fieldSize.x/2,fieldSize.y/3),"next",3,11));
    layoutBar = new TextBox();
    layoutBar->color(Color(1,1,1)).font(mFontBig).size( Vec2f( fieldSize.x, fieldSize.y/3 ) ).backgroundColor(darkGrey).setAlignment(TextBox::CENTER);
}

XmlTree& ModularsInterface_02App::getLayout(XmlTree xml, int num)
{
    for(XmlTree::Iter it = xml.begin(); it != xml.end();)
    {
        if(it->getAttributeValue<int>("id") == num){
            return *it;
        }
        ++it;
    }
    XmlTree::Iter iter = xml.begin() ;

    layoutCounter = 0;
    return *iter;

    // failed to find a track named 'searchTrack'
    throw XmlTree::ExcChildNotFound( xml, std::to_string(num) );
}

void ModularsInterface_02App::saveLayout()
{
    int lastLayoutId = 0;
    if(data.hasChild("layout"))
    {
        lastLayoutId = data.getChildren().back()->getAttributeValue<int>("id");
        ++lastLayoutId;
    }
    XmlTree save = XmlTree("layout","");
    save.setAttribute("id", lastLayoutId);
    save.setAttribute("button", controllerManager.getControllers().x);
    save.setAttribute("slider", controllerManager.getControllers().y);
    save.setAttribute("knob", controllerManager.getControllers().z);
    for(int i = 0; i < 22; i++){
        save.push_back(XmlTree("field",controllerManager.getField(i)).setAttribute("id", i).setAttribute("cId", controllerManager.getControllerId(i) ));
    }
    data.push_back(save);
    data.write( writeFile( source->getFilePath() ) );
    console() << data << endl;
    console() << source->getFilePath() << endl;
}

void ModularsInterface_02App::mouseDown( MouseEvent event )
{

}



void ModularsInterface_02App::touchesBegan(TouchEvent event )
{
 
    
    
    for(vector<cinder::app::TouchEvent::Touch>::iterator it = event.getTouches().begin(); it != event.getTouches().end();){
        for(Button &b : buttons){
            if(b.getView() == view && b.hittest(it->getPos())){
                b.printName();
                view = b.getLinkedView();
                switch (view) {
                    case 0:
                        controllerManager.setState(ControllerManager::FREEZE);
                        
                        break;
                    case 1:
                        controllerManager.setState(ControllerManager::CALIBRATING);
                        break;
                    case 2:
                        controllerManager.setState(ControllerManager::CALIBRATING);
                        controllerManager.clearControllers();
                        view = 1;
                        break;
                    case 3:
                        return;
                        break;
                    case 4:
                        console() << "save" << endl;
                        saveLayout();
                        view = 0;
                        break;
                    case 5:
                        controllerManager.setState(ControllerManager::CALIBRATING);
                        controllerManager.loadLayout(sendableLayout);
                        controllerManager.setState(ControllerManager::FREEZE);
                        
                        return;
                        break;
                    case 10:
                        layoutCounter--;
                        view = 3;
                        break;
                    case 11:
                        layoutCounter++;
                        view = 3;
                        break;
                        
                    default:
                        break;
                }
                console() << "View is now: " << view << endl;
            }
            
        }
        ++it;
    }
    controllerManager.touchStarted(event);
}

void ModularsInterface_02App::touchesMoved(TouchEvent event){
    controllerManager.touchMoved(event);
}

void ModularsInterface_02App::touchesEnded(TouchEvent event)
{
    if (view == 5) {
        view = 0;
    }
    else{
     controllerManager.touchesEnded(event);   
    }
}

void ModularsInterface_02App::update()
{
    controllerManager.update();
    Vec3i c;
    if(view == 3){
        
        if(data.hasChild("layout")){
            auto activeLayout = getLayout(data, layoutCounter);
            sendableLayout = activeLayout;
            c = Vec3i(activeLayout.getAttributeValue<int>("button"), activeLayout.getAttributeValue<int>("slider"),activeLayout.getAttributeValue<int>("knob") );
            layoutBar->text("\nlayout\n"+std::to_string(layoutCounter));
        }
        else{
            layoutBar->text("\nno\nlayouts");
        }
        mLayoutBarTex = gl::Texture(layoutBar->render());
    }
    else{
        c = controllerManager.getControllers();
        
    }
    mControllerCounter->text("\nbuttons: " + to_string(c.x)+ "\nslider: " + to_string(c.y)+"\nknobs: " + to_string(c.z));
    mController = gl::Texture(mControllerCounter->render());
}

void ModularsInterface_02App::draw()
{
    
	gl::clear( Color( 0, 0, 0 ) );
    if(view == 0)
    {
        gl::color(Color(darkGrey));
    }
    else{
        gl::color(Color(lightGrey));
    }
    for(int x = 0; x <= getWindowWidth(); x += getWindowWidth()/6)
    {
        gl::drawLine(Vec2f(x,0), Vec2f(x,getWindowHeight()));
    }
    for (int y = 0; y <= getWindowHeight(); y += getWindowHeight()/4) {
        gl::drawLine(Vec2f(0,y), Vec2f(getWindowWidth(),y));
    }
    
    gl::color(1, 1, 1);
    for(Button &b : buttons){
        if(b.getView() == view){
            b.draw(lightGrey);
        }
    }
    
    if (view == 1) {
        gl::draw(mTextTexture,menuPos);
    }
    if(view == 3){
        gl::draw(mLayoutBarTex ,Vec2f(menuPos.x+fieldSize.x/2,menuPos.y));
    }
    gl::draw(mStatus,menuPos+Vec2f( 0 , (256/3)*2 ));
    gl::draw(mController,menuPos+Vec2f( fieldSize.x+fieldSize.x/3 , (256/3)*2 ));
    controllerManager.draw();
    
    
}

CINDER_APP_NATIVE( ModularsInterface_02App, RendererGl )
