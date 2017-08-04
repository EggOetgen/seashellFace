#pragma once

#include "ofMain.h"
#include "ofxImGui.h"
#include "shell.hpp"
#include "ofxOsc.h"
#include "ofxGui.h"
#include "ofxCv.h"
#include "FaceOsc.h"
#include "ofxXmlSettings.h"
#include "ofxPS3EyeGrabber.h"

//OSC:
#define HOST "localhost"
#define IN_PORT 12000
#define OUT_PORT 6448


class ofApp : public ofBaseApp, public FaceOsc{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        void randomise();
        void autoPilot();
    
    /*TAKEN FROM https://github.com/genekogan/SeashellGenerator */
    
       
    shell shell;
    
    ofLight light;
    
   // ofNode cam;
    ofCamera cam;
    ofEasyCam testCam;
    int n, m;
//    
//   ofxIntSlider D;
//    ofxFloatSlider turns;
//    ofxFloatSlider alpha;
//    ofxFloatSlider beta;
//    ofxFloatSlider A;
//    //ofxFloatSlider k;
//    ofxFloatSlider mu;
//    ofxFloatSlider omega;
//    ofxFloatSlider phi;
//    ofxFloatSlider a;
//    ofxFloatSlider b;
//    ofxFloatSlider L;
//    ofxFloatSlider P;
//    ofxFloatSlider W1;
//    ofxFloatSlider W2;
//    ofxIntSlider N;
    
    // spiral parameters
    int D = 1; //varying this stretches and compresses along an axis orthoganal to the "A" parameter
    float turns = 6 * TWO_PI;
    
    float alpha = 1.49;
    float beta = .47;
    float A = 0;
    float k = 0.86; // test variable for rate of growth
    
    // ellipse orientation parameters
    float mu = .08; // angle given in radians
    float omega = .01; // angle given in radians
    float phi = 2.6; //rotation of elipse about normal axis, angle given in radians
    
    // ellipsoid parameters
    float a = 13.13; //elipse radii
    float b = 20; //elipse radii
    
    // surface parameters
    float L = 5;
    float P = 5;
    float W1 = 5;
    float W2 = .39;
    int N = 10;
    
    // render mod
    
   
    ofxImGui::Gui GUI;
    float pTurns;
    
    bool rando;

    ofVec2f lastMouse;
    ofQuaternion curRot;

    ofVideoGrabber wCam;
    ofxFaceTracker tracker;


    ofxOscReceiver receiver;

    

    float rotation =0;

};
