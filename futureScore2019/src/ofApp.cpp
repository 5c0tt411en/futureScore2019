#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

void ofApp::setup() {
    ofSetWindowShape(1080, 1920);
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    finder.setup("haarcascade_frontalface_default.xml");
    finder.setPreset(ObjectFinder::Fast);
    cam.setup(camSize.x, camSize.y);
    
//    dir.allowExt("png");
//    for (int i = 0; i < dir.listDir("types/"); i++) {
//        types.push_back(ofImage(dir.getPath(i)));
//    }
//    for (int i = 0; i < 5; i++)
//        types.push_back(ofImage("types/" + ofToString(i) + ".png"));
    img.load("types/" + ofToString(0) + ".png");
}

void ofApp::update() {
    time = ofGetElapsedTimef() - timeStamp;
    cam.update();
    if(cam.isFrameNew()) {
        finder.update(cam);
    }
}

void ofApp::draw() {
    ofSetColor(255, 255);
    cam.draw(853+1080, 0, -3413, 1920);
    ofPushMatrix();
    ofTranslate(853+1080, 0);
    ofScale(-3413 / 640, 3413 / 640);
    finder.draw();
    ofPopMatrix();

    ofPushMatrix();
    ofScale(5, 5);
    ofDrawBitmapStringHighlight(ofToString(finder.size()), 10, 20);
    ofDrawBitmapStringHighlight("fps: " + ofToString(ofGetFrameRate()), 10, 50);
    ofPopMatrix();
    
    switch (mode) {
        case 0: //FADE IN
                ofSetColor(255, time * 255);
//                types[n].draw(0, 0);
                img.draw(0,0);
            if (time >= 1) {
                timeStamp = ofGetElapsedTimef();
                time = ofGetElapsedTimef() - timeStamp;
                mode = 1;
            }
            break;
        case 1: // STAY
                ofSetColor(255);
//                types[n].draw(0, 0);
                img.draw(0,0);
            if (time >= 5) {
                timeStamp = ofGetElapsedTimef();
                time = ofGetElapsedTimef() - timeStamp;
                mode = 2;
            }
            break;
        case 2: //FADE OUT
                ofSetColor(255, (1 - time) * 255);
//                types[n].draw(0, 0);
                img.draw(0,0);
            if (time >= 1) {
                timeStamp = ofGetElapsedTimef();
                time = ofGetElapsedTimef() - timeStamp;
                mode = 3;
//                if (n == dir.listDir("types/") - 1) {
//                    n = 0;
//                }
//                else {
//                    n++;
//                }
//                ofLog() << n << endl;
//                img.load("types/" + ofToString(n) + ".png");
            }
            break;
        case 3: //WAIT
//            ofSetColor(255);
            //                types[n].draw(0, 0);
//            img.draw(0,0);
            if (time >= 1) {
                timeStamp = ofGetElapsedTimef();
                time = ofGetElapsedTimef() - timeStamp;
                mode = 0;
            }
            break;
        default:
            break;
    }
    
}
