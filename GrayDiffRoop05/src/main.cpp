#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    ofGLFWWindowSettings settings;
    settings.width = 1024;
    settings.height = 768;
    settings.setPosition(ofVec2f(640,0));
    settings.resizable = true;
    shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);
    
    settings.width = 1920;
    settings.height = 1080;
    settings.setPosition(ofVec2f(0,0));
    settings.resizable = false;
    // uncomment next line to share main's OpenGL resources with gui
    //settings.shareContextWith = mainWindow;
    shared_ptr<ofAppBaseWindow> camWindow = ofCreateWindow(settings);
    camWindow->setVerticalSync(false);
    
    shared_ptr<ofApp> mainApp(new ofApp);
    mainApp->setupCam();
    ofAddListener(camWindow->events().draw,mainApp.get(),&ofApp::drawCam);
    ofAddListener(camWindow->events().update,mainApp.get(),&ofApp::updateCam);
    ofAddListener(camWindow->events().keyPressed,mainApp.get(),&ofApp::keyPressedCam);
    ofAddListener(camWindow->events().mouseDragged,mainApp.get(),&ofApp::mouseDraggedCam);
    ofAddListener(camWindow->events().mousePressed,mainApp.get(),&ofApp::mousePressedCam);
    
    ofRunApp(mainWindow, mainApp);
    ofRunMainLoop();
    
}
