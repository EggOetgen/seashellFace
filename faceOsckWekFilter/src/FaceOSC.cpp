#include "FaceOsc.h"

FaceOsc::FaceOsc() {
    wekAddress = WEKI_OSC_ADDRESS;
    faceAddress = FACE_OSC_ADDRESS;

    
    for (int i = 0; i < 8; i++){
        filters.push_back(MovingAverageFilter(28,1));
    
    }
}

void FaceOsc::sendFaceOsc(ofxFaceTracker& tracker) {
    
    if(tracker.getFound()) {
        
        msg.clear();
        msg.setAddress(wekAddress);
        msgFace.clear();
        msgFace.setAddress(faceAddress);
        
        if(bIncludePose) {
            ofVec2f position = tracker.getPosition();
            addMessage(position);
            addMessage(tracker.getScale());
            ofVec3f orientation = tracker.getOrientation();
            addMessage(orientation);
        }
        
//        if (bIncludeGestures) {
            float mouthWidth  = filters[0].filter(tracker.getGesture(ofxFaceTracker::MOUTH_WIDTH));
            float mouthHeight = filters[1].filter(tracker.getGesture(ofxFaceTracker::MOUTH_HEIGHT));
            float leftEyebrowHeight = filters[2].filter(tracker.getGesture(ofxFaceTracker::LEFT_EYEBROW_HEIGHT));
            float rightEyebrowHeight = filters[3].filter(tracker.getGesture(ofxFaceTracker::RIGHT_EYEBROW_HEIGHT));
            float leftEyeOpenness = filters[4].filter(tracker.getGesture(ofxFaceTracker::LEFT_EYE_OPENNESS));
            float rightEyeOpenness = filters[5].filter(tracker.getGesture(ofxFaceTracker::RIGHT_EYE_OPENNESS));
            float jawOpenness = filters[6].filter(tracker.getGesture(ofxFaceTracker::JAW_OPENNESS));
            float nostrilFlare = filters[7].filter(tracker.getGesture(ofxFaceTracker::NOSTRIL_FLARE));
            
            addMessage(mouthWidth);
            addMessage(mouthHeight);
            addMessage(leftEyebrowHeight);
            addMessage(rightEyebrowHeight);
            addMessage(leftEyeOpenness);
            addMessage(rightEyeOpenness);
            addMessage(jawOpenness);
            addMessage(nostrilFlare);
//    }
//
//        if(bIncludeAllVertices){
            ofVec2f center = tracker.getPosition();
            vector<ofVec2f> imagePoints = tracker.getImagePoints();
        
            for(int i = 0; i < imagePoints.size(); i++){
                ofVec2f p = imagePoints.at(i);
//              cout << p.x << " " << (p.x - center.x)/tracker.getScale() <<endl;
              //  cout << p.x << " " << p.y <<endl;
                //                msgFace.addFloatArg((p.x - center.x)/tracker.getScale());
//                msgFace.addFloatArg((p.y - center.y)/tracker.getScale());
                                msgFace.addFloatArg((p.x));
                                msgFace.addFloatArg((p.y));
//
            }
//        }
//        ofPolyline leftEye = tracker.getImageFeature(ofxFaceTracker::LEFT_EYE);
//        vector <glm::vec3> leftEyePoints = leftEye.getVertices();
//        ofPoint leftEyePosition;
//        for(int i = 0; i < leftEyePoints.size(); i++){
//        leftEyePosition += leftEyePoints[i];
//        }
//        leftEyePosition/=leftEyePoints.size();
//        
//        msgFace.addFloatArg(( leftEyePosition.x ));
//        msgFace.addFloatArg(( leftEyePosition.y ));
        
        osc.sendMessage(msg);
        oscFACE.sendMessage(msgFace);
        
    } else {
        // not found
    }
}

void FaceOsc::addMessage(ofVec3f data) {
    msg.addFloatArg(data.x);
    msg.addFloatArg(data.y);
    msg.addFloatArg(data.z);
}

void FaceOsc::addMessage(ofVec2f data) {
    msg.addFloatArg(data.x);
    msg.addFloatArg(data.y);
}

void FaceOsc::addMessage(float data) {
    msg.addFloatArg(data);
}

void FaceOsc::addMessage(int data) {
    msg.setAddress(wekAddress);
    msg.addIntArg(data);
}
