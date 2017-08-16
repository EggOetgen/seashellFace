#pragma once

#include "ofxFaceTracker.h"
#include "ofxOsc.h"
#include "ofxGrt.h"

#define WEKI_OSC_ADDRESS "/wek/inputs"
#define FACE_OSC_ADDRESS "/faceData"

class FaceOsc {
public:
    FaceOsc();
    void addMessage(ofVec3f data);
    void addMessage(ofVec2f data);
    void addMessage(float data);
    void addMessage(int data);
    void sendBundle();
    
    void sendFaceOsc(ofxFaceTracker& tracker);
    
    string host;
    int port;
    ofxOscSender osc;
    ofxOscSender oscFACE;

    ofxOscMessage msg;
    ofxOscMessage msgFace;
    
    string wekAddress, faceAddress;
    
    ofParameter<bool> bIncludePose;
    ofParameter<bool> bIncludeGestures;
    ofParameter<bool> bIncludeAllVertices;
    
    vector<MovingAverageFilter> filters;
};