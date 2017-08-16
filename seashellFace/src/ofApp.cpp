#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

//    n = 512;
//    m = 96;
 
//    n = 384;
//    m = 80;
    
    n = 256;
    m = 48;

//    n = 128;
//    m = 32;
//    n = 64;
//    m = 16;
    
   
 
//    gui.setup();
//    gui.add(turns.setup("turns", 6 * TWO_PI, 0, 10 * TWO_PI));
//    gui.add(D.setup("D", 1.f, 1.f, 1.f));
//    gui.add(alpha.setup("alpha", 1.49f, 0, PI));
//    gui.add(beta.setup("beta", .47f, -PI, PI));
//    gui.add(A.setup("A", .0f, 0.f, 100.f));
//   // gui.add(k.setup("k", .47f, 0.f, 2.f));
//    gui.add(mu.setup("mu", 0.08f, 0.f, 6.283185f));
//    gui.add(omega.setup("omega", -6.283185f, 0.f, 6.283185f));
//    gui.add(phi.setup("phi", 2.6f, -PI, PI));
//    gui.add(a.setup("a", 13.13f, 0.f, 50.f));
//    gui.add(b.setup("b", 20.f, 0.f, 50.f));
//    gui.add(L.setup("L", 5.f, 0.f, 5.f));
//    gui.add(P.setup("P", 5.f, 0.f, 5.f));
//    gui.add(W1.setup("W1", 5.f, -5.f, 5.f));
//    gui.add(W2.setup("W2", .39f, -10.f, 10.f));
//    gui.add(N.setup("N", 10, -10, 10));
//    gui.add(k.setup("k", .86f, 0.f, 10.f));

    pTurns = turns;
    rando = false;
  
    
    shell.generate(n,m,D, turns, alpha, beta, A, mu, omega, phi, a, b, L, P, W1, W2, N);
    shell.generateMesh(n,m, turns);
 
    light.setPosition(-100,-300,-600);

    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.5f);
    
    testCam.disableMouseInput();
    cam.setPosition(0, 0, -375);
    cam.setParent(shell.test);
    cam.enableOrtho();
    testCam.setPosition(0,0,-600);
    
    cout << "listening for osc messages on port " << PORT << "\n";
    receiver.setup(PORT);
    faceReceiver.setup(FACE_PORT);

    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    // check for waiting messages
    while(receiver.hasWaitingMessages()){
        
        // get the next message
        ofxOscMessage m;
        receiver.getNextMessage(m);
        if(m.getAddress() == "/shellData"){
        
            //alpha = ofMap(m.getArgAsFloat(0),0, 1, PI/3,PI);
            beta = ofMap(m.getArgAsFloat(1), 0, 1, 0, PI/2);
            A = ofMap(m.getArgAsFloat(2), 0, 1,0.0f, 100.f);
            mu = ofMap(m.getArgAsFloat(3), 0, 1,0.0f,  PI);
            omega= ofMap(m.getArgAsFloat(4), 0, 1, 0, PI);
            phi = ofMap(m.getArgAsFloat(5), 0, 1, 0, PI);
            a = ofMap(m.getArgAsFloat(6),0, 1, 0.0f, 50.f);
            b = ofMap(m.getArgAsFloat(7),0, 1, 0.0f, 50.f);
            L = ofMap(m.getArgAsFloat(8),0, 1, 0.0f, 20.f);
            W1 = ofMap(m.getArgAsFloat(9),0, 1, -25.f, 25.f);
            W2 = ofMap(m.getArgAsFloat(10),0, 1, 0.f, 10.f);
            N = (int)ofMap(m.getArgAsFloat(11),0, 1, 0, 50);
        }
        
    
    }
    
    while(faceReceiver.hasWaitingMessages()){
        
        // get the next message
        ofxOscMessage m;
        faceReceiver.getNextMessage(m);

        
      if(m.getAddress() == "/faceData"){
            facialPoints.clear();
            for(int i = 0; i < 60; i+=2){
                ofPoint p;
                p.x = m.getArgAsFloat(i);
                p.y = m.getArgAsFloat(i + 1);
                facialPoints.push_back(p);
              
            }
        
    }
    }


   shell.generate(n,m, D, turns, alpha, beta, A, mu, omega, phi, a, b, L, P, W1, W2, N);
    if(turns != pTurns){
        shell.generateMesh(n,m, turns);
     
        


    }else{    
    shell.updateMesh(n, m ,turns);
   // cam.setPosition(0,0,shell.centroid.z);
    }
   
}

//--------------------------------------------------------------
void ofApp::draw(){
   
   // gui.draw();
     ofDrawBitmapString(ofToString((int) ofGetFrameRate()), ofGetWidth()-20, 20);
//    GUI.begin();
//    if(ImGui::Button("Random"))
//    {
//        rando = !rando;
//            }
//    ImGui::SliderFloat("Turns", &turns, 0.0f, 10 * TWO_PI);
//    ImGui::SliderFloat("alpha", &alpha, 0.0f, PI);
//    ImGui::SliderFloat("beta", &beta, -PI, PI);
//    ImGui::SliderFloat("A", &A, 0.0f, 100.f);
//    ImGui::SliderFloat("mu", &mu, 0.0f,  TWO_PI);
//    ImGui::SliderFloat("omega", &omega, -TWO_PI,  TWO_PI);
//    ImGui::SliderFloat("phi", &phi, -PI, PI);
//    ImGui::SliderFloat("a", &a, 0.0f, 50.f);
//    ImGui::SliderFloat("b", &b, 0.0f, 50.f);
//    ImGui::SliderFloat("L", &L, 0.0f, 5.f);
//    ImGui::SliderFloat("W1", &W1, -5.f, 5.f);
//    ImGui::SliderFloat("W2", &W2, -10.f, 10.f);
//    ImGui::SliderInt("N", &N, -10.f, 10.f);
//    GUI.end();
//    
    if(rando) randomise();
   // autoPilot();
    ofEnableDepthTest();
   
    
    
    light.enable();
    for(int i = 17; i < facialPoints.size(); i ++){
        
        ofDrawSphere(facialPoints[i].x, facialPoints[i].y, 4.f);
        
    }

//    ofVec3f target = shell.shellMesh.getCentroid();
      cam.lookAt(shell.test);
   // cam.rotateAround(curRot,shell.centroid);
    //    testCam.begin();
    cam.begin();
   // ofPushMatrix();
//    ofRotateY(rotation);
//    ofRotateZ(rotation);
                   shell.draw(m);
    //  cam.draw();
//    ofSetColor(255, 255, 0);
//    ofVec3f v1 = cam.getGlobalPosition();
//    ofVec3f v2 = shell.test.getGlobalPosition();
//    ofDrawLine(v1,v2);
  //  ofPopMatrix();
    cam.end();
       // testCam.end();
    light.disable();
    
    ofDisableDepthTest();
    rotation++;
}

//--------------------------------------------------------------
void ofApp::randomise(){
    
   // alpha = ofRandom( PI/3, PI);
    beta =ofRandom( -PI, PI);
    A = ofRandom( 0.0f, 100.f);
    mu = ofRandom( 0.0f,  TWO_PI);
    omega= ofRandom( -TWO_PI,  TWO_PI);
    phi = ofRandom( -PI, PI);
    a = ofRandom( 0.0f, 50.f);
    b = ofRandom( 0.0f, 50.f);
    L = ofRandom( 0.0f, 5.f);
    W1 = ofRandom( -5.f, 5.f);
    W2 = ofRandom( -10.f, 10.f);
    N = ofRandom( -10.f, 10.f);
    rando = !rando;
}

//--------------------------------------------------------------
void ofApp::autoPilot(){
    
    float time = ofGetElapsedTimef()+764;
     alpha = ofMap(ofNoise(time/100), 0, 1, 0, PI);
    beta = ofMap(ofNoise(time/10), 0, 1, -PI, PI);
    A = ofMap(ofNoise(time/12), 0, 1,0.0f, 100.f);
    mu = ofMap(ofNoise(time/15), 0, 1,0.0f,  TWO_PI);
    omega= ofMap(ofNoise(time/14), 0, 1, -TWO_PI,  TWO_PI);
    phi = ofMap(ofNoise(time/24), 0, 1, -PI, PI);
    a = ofMap(ofNoise(time/8),0, 1, 0.0f, 50.f);
    b = ofMap(ofNoise(time/9),0, 1, 0.0f, 50.f);
    L = ofMap(ofNoise(time/40),0, 1, 0.0f, 5.f);
    W1 = ofMap(ofNoise(time/13),0, 1, -5.f, 5.f);
    W2 = ofMap(ofNoise(time/18),0, 1, -10.f, 10.f);
    N = (int)ofMap(ofNoise(time),0, 1, -10, 10);
    //rando = !rando;
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

    if (button == 2)
    shell.move(x, y, lastMouse);
    
//
//    ofVec2f mouse(x/10,y/10);
//    ofQuaternion yRot(x-lastMouse.x, ofVec3f(0,1,0));
//    ofQuaternion xRot(y-lastMouse.y, ofVec3f(-1,0,0));
//    curRot *= yRot*xRot;
    //lastMouse = mouse;
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

    lastMouse = ofVec2f(x,y);  
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
