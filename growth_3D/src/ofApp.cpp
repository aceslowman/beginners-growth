#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    sphere.set(40,20);
    
    setupBranch();
    
    path.setStrokeWidth(2);
    path.setStrokeColor(ofColor(0));
    path.setFilled(false);
    
    branch.add(branch_smooth.set("Smooth",4.0,0.0,20.0));
    branch.add(branch_length.set("Length",20.0,0.0,20.0));
    
    gui.setup();
    gui.add(branch);
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
            ofNoFill();
            ofSetSphereResolution(5);
            ofDrawSphere(0,0,2);
            ofSetColor(ofColor(0,0,255));
            ofDrawBitmapString(ofToString(i), 0,0);
            ofPopMatrix();
        }
    cam.end();
    ofDisableAntiAliasing();
    
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::setupBranch(){
    path.moveTo(0,0);
    
    int numPoints = 10;
    
    ofPoint t_dest = ofVec3f(ofRandom(250)+100);
    ofVec3f t_vec = ofVec3f(ofRandomf(),ofRandomf(),ofRandomf());
    
    ofPoint t_point = ofVec3f(0); //Origin (seed)
    
    for(int i = 0; i < numPoints; i++){
        float t_len = ofRandom(branch_length)+(branch_length/2);
        
        t_point = t_point + (t_vec*t_len);
        
        path.lineTo(t_point);
        
        t_vec = t_vec + (ofRandomf()/branch_smooth);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'b'){
        path.clear();
        setupBranch();
    }
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
