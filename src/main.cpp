#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){

    //ofSetupOpenGL(352, 864, OF_WINDOW);			// <-------- setup the GL context
    ofSetupOpenGL(1500, 500,OF_WINDOW);
    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
    ofRunApp(new ofApp());

}
