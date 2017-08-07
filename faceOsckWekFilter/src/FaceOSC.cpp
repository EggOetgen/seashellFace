#include "FaceOsc.h"

using namespace ofxCv;
using namespace cv;

FaceOsc::FaceOsc() {
    address = DEFAULT_OSC_ADDRESS;
    
    for (int i = 0; i < 8; i++){
        filters.push_back(MovingAverageFilter(28,1));
    
    }
}

void FaceOsc::sendFaceOsc(ofxFaceTracker2& tracker) {
    
  //  if(tracker.getFound()) {
        
        msg.clear();
        msg.setAddress(address);
  //  tracker[0].calulatePoseMatrix;
    //cout<<tracker[i]
//        if(bIncludePose) {
//            ofVec2f position = tracker.getPosition();
//            addMessage(position);
//            addMessage(tracker.getScale());
//            ofVec3f orientation = tracker.getOrientation();
//            addMessage(orientation);
//        }
    
   
//        if (bIncludeGestures) {
    
//        float mouthWidth  = filters[0].filter(tracker[i].getGesture
//            float mouthHeight = filters[1].filter(tracker.getGesture(ofxFaceTracker::MOUTH_HEIGHT));
//            float leftEyebrowHeight = filters[2].filter(tracker.getGesture(ofxFaceTracker::LEFT_EYEBROW_HEIGHT));
//            float rightEyebrowHeight = filters[3].filter(tracker.getGesture(ofxFaceTracker::RIGHT_EYEBROW_HEIGHT));
//            float leftEyeOpenness = filters[4].filter(tracker.getGesture(ofxFaceTracker::LEFT_EYE_OPENNESS));
//            float rightEyeOpenness = filters[5].filter(tracker.getGesture(ofxFaceTracker::RIGHT_EYE_OPENNESS));
//            float jawOpenness = filters[6].filter(tracker.getGesture(ofxFaceTracker::JAW_OPENNESS));
//            float nostrilFlare = filters[7].filter(tracker.getGesture(ofxFaceTracker::NOSTRIL_FLARE));
//            
//            addMessage(mouthWidth);
//            addMessage(mouthHeight);
//            addMessage(leftEyebrowHeight);
//            addMessage(rightEyebrowHeight);
//            addMessage(leftEyeOpenness);
//            addMessage(rightEyeOpenness);
//            addMessage(jawOpenness);
//            addMessage(nostrilFlare);        }

//        if(bIncludeAllVertices){
//            ofVec2f center = tracker.getPosition();
//            vector<ofVec2f> imagePoints = tracker.getImagePoints();
//            for(int i = 0; i < imagePoints.size(); i++){
//                ofVec2f p = imagePoints.at(i);
//                msg.addFloatArg((p.x - center.x)/tracker.getScale());
//                msg.addFloatArg((p.y - center.y)/tracker.getScale());
//            }
//        }
//
        osc.sendMessage(msg);
        
//    } else {
//        // not found
//    }
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
    msg.setAddress(address);
    msg.addIntArg(data);
}

//vector<ofVec3f> ofxFaceTracker::getObjectPoints() const {
//    int n = size();
//    vector<ofVec3f> objectPoints(n);
//    for(int i = 0; i < n; i++) {
//        objectPoints[i] = getObjectPoint(i);
//    }
//    return objectPoints;
//}
//
////ofVec3f ofxFaceTracker::getObjectPoint(int i) const {
//////    if(failed) {
//////        return ofVec3f();
//////    }
////    int n = objectPoints.rows / 3;
//// //   return ofVec3f(objectPoints.db(i,0), objectPoints.db(i+n,0), objectPoints.db(i+n+n,0));
////}
//
//void ofxFaceTracker::updateObjectPoints() {
//    const Mat& mean = tracker._clm._pdm._M;
//    const Mat& variation = tracker._clm._pdm._V;
//    const Mat& weights = tracker._clm._plocal;
//    objectPoints = mean + variation * weights;
//}