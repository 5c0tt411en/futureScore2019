#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

void ofApp::setup() {
#ifdef MAC
    ofSetWindowPosition(-1080, 0);
    ofSetFullscreen(true);
#endif
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    finder.setup("haarcascade_frontalface_default.xml");
    finder.setPreset(ObjectFinder::Fast);
    finder.setMinSizeScale(0.001);
    cam.setup(camSize.x, camSize.y);
    img.load("types/" + ofToString(0) + ".png");
    
    font.load("Roboto-Regular.ttf", 50);
}

void ofApp::update() {
    ofHideCursor();
    time = ofGetElapsedTimef() - timeStamp;
    valTime = ofGetElapsedTimef() - valTimeStamp;
//    if (valTime >= 60) {
//        valTimeStamp = ofGetElapsedTimef();
//        val = ofRandom(8000, 12000);
//    }
    cam.update();
    if(cam.isFrameNew()) {
        finder.update(cam);
    }
}

void ofApp::draw() {
    ofSetColor(255);
    cam.draw(
            (camDisplaySize.x - ofGetWidth()) / 2 + ofGetWidth(),
            0,
            -camDisplaySize.x,
            camDisplaySize.y
            );
    if (finder.size() == 1) {
        progressTime = ofGetElapsedTimef() - progressTimeStamp + progressTimeStamp2;
        resetTimeStamp = ofGetElapsedTimef();
        rec = true;
//        if (progressTime >= judgeThre) {
//            isProcessDone = true;
//        }
    }
    else if (finder.size() == 0) {
        if (rec) {
            progressTimeStamp2 = progressTime;
            rec = false;
        }
        resetTime = ofGetElapsedTimef() - resetTimeStamp;
        progressTimeStamp = ofGetElapsedTimef();
        if (resetTime >= resetThre) {
            isProcessDone = false;
            progressTimeStamp2 = 0;
        }
    }
    for ( int i=0; i < finder.size(); i++){
        if (finder.size() == 1) {
            ofRectangle rect = finder.getObjectSmoothed(i);
            ofVec4f converted = ofVec4f(
                                        (camDisplaySize.x - ofGetWidth()) / 2 + ofGetWidth() - rect.getMinX() * camDisplaySize.x / camSize.x,
                                        rect.getMinY() * camDisplaySize.x / camSize.x,
                                        - rect.getWidth() * camDisplaySize.x / camSize.x,
                                        rect.getHeight() * camDisplaySize.x / camSize.x
                                        );
            ofSetColor(255, 0, 0);
            ofNoFill();
            ofDrawRectangle(converted.x, converted.y, converted.z, converted.w);
            ofSetColor(255);
            ofFill();
            if (isProcessDone) {
                //            ofDrawRectangle(converted.x, converted.y - 5, converted.z, -30);
                switch (roomNum) {
                    case 1:
                        font.drawString("Physical condition: " + judgeSt, converted.x + converted.z, converted.y - 10);
                        break;
                    case 2:
                        font.drawString("Behavior: " + judgeSt, converted.x + converted.z, converted.y - 10);
                        break;
                    case 3:
                        font.drawString(ofToString(int(val + ofNoise(ofGetElapsedTimef() / 30) * 100)), converted.x + converted.z, converted.y - 10);
                        break;
                    default:
                        break;
                }
            }
            else {
                font.drawString("Under calculation...", converted.x + converted.z, converted.y - 40);
                ofDrawRectangle(converted.x + converted.z, converted.y - 5, - converted.z * (progressTime) / judgeThre, -30);
                if (progressTime >= judgeThre) {
                    isProcessDone = true;
                    judgeRandom = int(ofRandom(1, 4));
                    switch (judgeRandom) {
                        case 1:
                            judgeSt = "PERFECT";
                            break;
                        case 2:
                            judgeSt = "GREAT";
                            break;
                        case 3:
                            judgeSt = "GOOD";
                            break;
                        default:
                            break;
                    }
                }
            }
        }
        
    }
    
    ofPushMatrix();
    {
        ofTranslate((camDisplaySize.x - ofGetWidth()) / 2 + ofGetWidth(), 0);
        ofScale(-camDisplaySize.x / camSize.x, camDisplaySize.x / camSize.x);
        ofSetLineWidth(lineW);
        ofSetColor(255, 0, 0);
    }
    ofPopMatrix();

#ifdef DEBUG
    ofSetColor(255);
    ofPushMatrix();
    {
        ofScale(5, 5);
        ofDrawBitmapStringHighlight(ofToString(finder.size()), 10, 20);
        ofDrawBitmapStringHighlight("fps: " + ofToString(ofGetFrameRate()), 10, 50);
    }
    ofPopMatrix();
#endif
    
    switch (mode) {
        case 0: //FADE IN
                ofSetColor(255, time * 255);
                img.draw(0,0);
            if (time >= fadeInTime) {
                timeStamp = ofGetElapsedTimef();
                time = ofGetElapsedTimef() - timeStamp;
                mode = 1;
            }
            break;
        case 1: // STAY
                ofSetColor(255);
                img.draw(0,0);
            if (time >= stayTime) {
                timeStamp = ofGetElapsedTimef();
                time = ofGetElapsedTimef() - timeStamp;
                mode = 2;
            }
            break;
        case 2: //FADE OUT
                ofSetColor(255, (fadeOutTime - time) * 255);
                img.draw(0,0);
            if (time >= fadeOutTime) {
                timeStamp = ofGetElapsedTimef();
                time = ofGetElapsedTimef() - timeStamp;
                mode = 3;
            }
            break;
        case 3: //WAIT
            if (time >= waitTime) {
                timeStamp = ofGetElapsedTimef();
                time = ofGetElapsedTimef() - timeStamp;
                mode = 0;
            }
            break;
        default:
            break;
    }
    
}
