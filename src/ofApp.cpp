/*This is the code for my 2018 end of year project in Computational Arts at Goldsmiths university. All credit for the code goes to
Theo Papatheodorou and the week 6 lesson in Workshops in Creative Coding from which this code is adapted. The footage used was gathered by myself 
using a raspberry pi with a camera attached using a timelapse photography technique, the methods of which are detailed here: https://www.raspberrypi.org/documentation/usage/camera/raspicam/timelapse.md
The footage is roughly sixteen hours of growth of the slime-mould Phsarum Polycephalum, condensed into just a few minutes.
This program is very simple but quite satisfying to watch!*/


#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
   
    ofSetBackgroundColor(255);

//segment the canvas nicely
    w = ofGetWidth()/3;
    h = ofGetHeight();

//load the timelapse footage
    tLapse.load("timelapse2.avi");
//start the video
    tLapse.play();
//change this to get a smaller/wider slitscan image
    grainSize = 1;

//set max buffer size to be the same as the width (this will make sense when the slitscan code is doing its thing)
    maxBuffersize = w;


}

//--------------------------------------------------------------
void ofApp::update(){
    //update the footage
    tLapse.update();

    //save video data into an ofImage deque to store the individual frames
    if(tLapse.isFrameNew()){
        //to push to the deque
        //'normal' image
        ofImage frameImage;
        frameImage.setFromPixels(tLapse.getPixels());
        frameImage.mirror(false, true);
        frameImage.setImageType(OF_IMAGE_GRAYSCALE);
        ImgBuffer.push_front(frameImage);
        //alt image #1
        ofImage aI1;
        aI1.grabScreen(0,0, w, h);
        sGrab.push_front(aI1);
        //alt image #2
        ofImage aI2;
        //change this to include more/less of the image
        aI2.grabScreen(0, h, w, h);
        sGrab2.push_front(aI2);

    }
    //remove frames once max buffer size has been reached
    if(ImgBuffer.size() > maxBuffersize){
        ImgBuffer.pop_back();
        sGrab.pop_back();
        sGrab2.pop_back();
    }

}

//--------------------------------------------------------------
void ofApp::draw(){

    tLapse.draw(0,0, w, h);



    //Below utilises the 'slitscan' technique with a subsection of pixels being drawn across the screen
    //In this case, two sigle pixel lines moving horizontally and vertically which scan across the
    //timelapse footage. 
        for(int i = 0; i < sGrab.size(); i ++){
            ofPushStyle();
            //vertical scan
            sGrab[i].drawSubsection(i + w,0,grainSize,h,i, 0);
            //horizontal scan
            sGrab[i].drawSubsection(w*2,0 + i,w,grainSize, 0, i);
            ofPopStyle();
        }
}


