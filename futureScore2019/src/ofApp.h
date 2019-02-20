#pragma once

#include "ofMain.h"
#include "ofxCv.h"

//#define DEBUG
#define MAC

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	
	ofVideoGrabber cam;
	ofxCv::ObjectFinder finder;

    ofVec2f
        camSize = ofVec2f(1280, 720),
        camDisplaySize = ofVec2f(1920 * camSize.x / camSize.y, 1920);
    
    ofImage img;
    
    float
        time = 0,
        timeStamp = 0,
        valTime = 0,
        valTimeStamp = 0,
        progressTime = 0,
        progressTimeStamp = 0,
        progressTimeStamp2 = 0,
        resetTime = 0,
        resetTimeStamp = 0,
        fadeInTime = 1.0,
        stayTime = 10.0,
        fadeOutTime = 1.0,
        waitTime = 1.0,
        judgeThre = 5,
        resetThre = 10;
    int
        mode = 0,
        lineW = 4,
        fontSize = 50,
        val = ofRandom(8000, 12000),
        roomNum = 1,
        judgeRandom;
    bool
        isProcessDone = false,
        rec = false;
    string judgeSt = "";
    ofTrueTypeFont font;
};
