#pragma once

#include "ofxFaceTracker.h"
#include "ofxFaceTracker2.h"
#include "ofxOsc.h"
#include "ofxGrt.h"


#define DEFAULT_OSC_ADDRESS "/wek/inputs"

class FaceOsc {
public:
    FaceOsc();
    void addMessage(ofVec3f data);
    void addMessage(ofVec2f data);
    void addMessage(float data);
    void addMessage(int data);
    void sendBundle();
    
//    vector<ofVec3f> ofxFaceTracker::getObjectPoints() const;
//  //  ofVec3f ofxFaceTracker::getObjectPoint(int i) const;
//    void ofxFaceTracker::updateObjectPoints();
    
    void sendFaceOsc(ofxFaceTracker2& tracker);
    
    string host;
    int port;
    ofxOscSender osc;
    ofxOscMessage msg;
    string address;
    
    ofParameter<bool> bIncludePose;
    ofParameter<bool> bIncludeGestures;
    ofParameter<bool> bIncludeAllVertices;
    
    vector<MovingAverageFilter> filters;
};