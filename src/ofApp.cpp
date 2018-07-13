#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColor(255);
    w = ofGetWidth()/2;
    h = ofGetHeight()/2;

    grainSize = 2;



    myCam.setDesiredFrameRate(30);


    myCam.initGrabber(w,h);
    //set max buffer size to be the same as the width (for now)
    maxBuffersize = w;
}

//--------------------------------------------------------------
void ofApp::update(){
    myCam.update();

    //save video data into an ofImage deque to store the individual frames
    if(myCam.isFrameNew()){
        ofImage frameImage;
        frameImage.setFromPixels(myCam.getPixels());
        frameImage.mirror(false, true);
        ImgBuffer.push_front(frameImage);
    }
    //remove frames once max buffer size has been reached
    if(ImgBuffer.size() > maxBuffersize) ImgBuffer.pop_back();

    //same as above (these could be combined in the future), but pushing a screen grab rather than a vid grab (a screen grab of the vid grab, sort of)
    if(myCam.isFrameNew()){
        ofImage fImage;
        fImage.grabScreen(0,0, w, h);
        sGrab.push_front(fImage);
    }
    if(sGrab.size() > w) sGrab.pop_back();

}

//--------------------------------------------------------------
void ofApp::draw(){
    //myCam.draw(0,0);

    for(int x = 0; x < w; x += grainSize*2){
        for(int y = 0; y < h; y += grainSize*2){
            ofColor colXY = ImgBuffer[0].getColor(x,y);
            int colBright = colXY.getBrightness();
            float colMap = ofMap(colBright, 0, 255, 0, 5);
            int b;
            //binarise the values to get just black or white
            if(colBright < 175){
                b = 0;
            }
            else if(colBright > 175){
                b = 255;
            }
            ofSetColor(b);
            ofSetCircleResolution(20);
            //ofSetColor(colBright);
            ofDrawCircle(x,y, grainSize);
        }
    }



    //Now to figure out how to get a slitscan from the image above...
        for(int i = 0; i < sGrab.size(); i ++){
            ofSetColor(255, 0, 0);
            ofSetColor(255,255,255);
            sGrab[i].drawSubsection(i,h,grainSize,h,i + 2, 0);
        }



}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
