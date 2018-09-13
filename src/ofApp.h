//See ofApp.cpp for description

#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
 
    //cam/video stuff
 
    ofVideoPlayer tLapse;

    deque<ofImage> ImgBuffer;

    deque<ofImage> sGrab;

    deque<ofImage> sGrab2;

    ofPixels pixelData;

    int maxBuffersize;

    //width & height of the image buffer
    int w,h;
    //location variables
    int posX,posY;
    //size of scan
    int grainSize;



};
