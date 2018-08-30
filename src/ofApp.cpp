#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofSetLogLevel(OF_LOG_VERBOSE);

    //initialise the printer
    myPrinter.open("/dev/ttyUSB0");
    //these settings seem to work well!
    myPrinter.setControlParameter(1, 100, 10);
    //Settings to play with
    //density
    myPrinter.setPrintDensity(1,1);


    ofSetBackgroundColor(255);
//    w = ofGetWidth()/2;
//    h = ofGetHeight()/2;

    w = ofGetWidth() / 3;
    h = ofGetHeight() / 3;

    //w = 352;
    //h = 288;

    tLapse.load("timelapseSlower.avi");

    tLapse.play();

    grainSize = 1;

    //myCam.initGrabber(w,h);
    //set max buffer size to be the same as the width (for now)
    maxBuffersize = w*2;

}

//--------------------------------------------------------------
void ofApp::update(){
    //myCam.update();

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

    time ++;
    if(time >= 30){
            time = 0;
    }


}

//--------------------------------------------------------------
void ofApp::draw(){

    //tLapse.draw(0,0, w, h);

     ImgBuffer[0].draw(0,0,w,h);

    if(ImgBuffer.size() >= 201){
    ImgBuffer[50].draw(w,0,w,h);
    ImgBuffer[150].draw(0,h,w,h);
    ImgBuffer[200].draw(w,h,w,h);

    }


    //for the binarising bit, set between 0-255, find which one works best for the light levels
//    int threshold = 200;

//    for(int x = 0; x < w; x += grainSize*2){
//        for(int y = 0; y < h; y += grainSize*2){
//            ofPushStyle();
//            ofColor colXY = ImgBuffer[0].getColor(x,y);
//            int colBright = colXY.getBrightness();
//            float colMap = ofMap(colBright, 0, 255, 20, 0);
//            int b;
//            //binarise the values to get just black or white
//            if(colBright < threshold){
//                b = 0;
//            }
//            else if(colBright > threshold){
//                b = 255;
//            }
//            //different ways of setting the colour - 'colBright' gives more detailed greyscale, 'b' is binary contrast(black or white)
//            //ofSetColor(b);
//            //ofSetCircleResolution(20);
//            ofSetColor(colBright);
//            //use 'grain size' to draw a uniform grid, or use 'colMap' for brightness to size mapping
//            ofDrawCircle(x,y, grainSize);
//            //OF_RECTMODE_CENTER;
//            //ofNoFill();
//            //ofDrawRectangle(x,y, colMap/2, colMap/2);
//            ofPopStyle();

//        }
//    }




    //Now to figure out how to get a slitscan from the image above...
//        for(int i = 0; i < sGrab.size(); i ++){
//            ofPushStyle();
//            //ofSetColor(255);
//            //vertical scan
//            sGrab[0].drawSubsection(i,h,grainSize,h,i, 0);
//            //horizontal scan
//            sGrab[0].drawSubsection(0, i + h + h,w,grainSize, 0, i);
//            ofPopStyle();
//        }

//    for(int i = 0; i < sGrab.size(); i ++){
//        sGrab[sGrab.size() - 1].draw(0,h,w,h);
//    }

//        if(ofGetElapsedTimef() >= 60){
//            myPrinter.print(sGrab2[0]);
//            ofResetElapsedTimeCounter();
//        }


}
void ofApp::exit(){
    myPrinter.close();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'p'){
        //with a for loop this prints quite a lot...
//        for(int i = 0; i < sGrab2.size(); i += 10){
//        myPrinter.print(sGrab2[i]);
//        }
        myPrinter.print(sGrab2[0]);

    }

}
//---
void ofApp::timer(){
    if(time >= 30){
        myPrinter.print(ImgBuffer[0]);
    }
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
