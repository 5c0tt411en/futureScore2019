#pragma once

#include "ofMain.h"
#include "ofxCv.h"

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	
	ofVideoGrabber cam;
	ofxCv::ObjectFinder finder;

    ofVec2f camSize = ofVec2f(1280, 720);
//    vector <ofImage> types;
    ofImage img;
    ofDirectory dir;
    float time = 0, timeStamp = 0;
    int mode = 0, n = 0;
};
