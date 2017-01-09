#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    sphere.set(40,20);
    
    
//    path.moveTo(-50,-50);
//    path.lineTo(-50,50);
//    path.lineTo(50,50);
//    path.lineTo(50,-50);
//    path.close();
    
    path.moveTo(0,0);
    
    int numPoints = 10;

    ofPoint t_dest = ofVec3f(ofRandom(250)+100);
    
    for(int i = 0; i < numPoints; i++){
        ofPoint t_len = t_dest / numPoints;
        ofPoint t_point = (t_len*i) + ofVec3f((ofRandomf()*10)-5,(ofRandomf()*10)-5,ofRandomf()*10)-5;
        path.lineTo(t_point);
    }
    
//    path.close();
    
    path.setStrokeWidth(2);
    path.setStrokeColor(ofColor(0));
    path.setFilled(false);
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableAntiAliasing();
    ofSetBackgroundColor(ofColor(255,255,255));
    ofSetColor(ofColor(0));
    
    cam.begin();
        path.draw();
        for(int i = 0; i < path.getOutline()[0].size(); i++){
            
            ofPoint t_point = path.getOutline()[0].getPointAtIndexInterpolated(i);
            ofPushMatrix();
            ofTranslate(t_point);
            ofSetColor(ofColor(255,0,0));
            ofDrawSphere(0,0,2);
            ofSetColor(ofColor(0,0,255));
            ofDrawBitmapString(ofToString(i), 0,0);
            ofPopMatrix();
        }
    cam.end();
    ofDisableAntiAliasing();
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

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

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
