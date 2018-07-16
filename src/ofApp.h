#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxThermalPrinter.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    void exit();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    //cam stuff
    ofVideoGrabber myCam;

    deque<ofImage> ImgBuffer;

    deque<ofImage> sGrab;

    deque<ofImage> sGrab2;

    ofPixels pixelData;

    //printer stuff

    ofxThermalPrinter myPrinter;



    int maxBuffersize;

    //width & height of the image buffer
    int w,h;
    //location variables
    int posX,posY;
    //size of dots
    int grainSize;
    //colour mapping to brightness
    int colBright;






};
