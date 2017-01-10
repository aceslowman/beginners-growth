#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    path.setStrokeWidth(2);
    path.setStrokeColor(ofColor(0));
    path.setFilled(false);
    
    branch.add(branch_smooth.set("Smooth",4.0,0.0,20.0));
    branch.add(branch_length.set("Length",20.0,0.0,20.0));
    branch.add(branch_levels.set("Levels",1,1,10));
    branch.add(branch_segments.set("Segments",15,1,50));
    
    gui.setup();
    gui.add(branch);
    
    setupBranches(ofVec3f(0),ofVec3f(ofRandomf(),ofRandomf(),ofRandomf()),branch_length,branch_segments);
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableAntiAliasing();
    ofEnableSmoothing();
    ofSetBackgroundColor(ofColor(255,255,255));
    ofSetColor(ofColor(0));
    
    cam.begin();
        path.draw();
        if(debug)
            drawDebug();
    cam.end();
    ofDisableAntiAliasing();
    
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::drawDebug(){
    for(int i = 0; i < path.getOutline().size(); i++){
//        ofSetColor(ofFloatColor(ofRandomf(),ofRandomf(),ofRandomf()));
        for(int j = 0; j < path.getOutline()[i].size(); j++){
            ofPoint t_point = path.getOutline()[i].getPointAtIndexInterpolated(j);
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
    }
}

//--------------------------------------------------------------
void ofApp::setupBranches(ofVec3f origin, ofVec3f initial_vector, float length, int segments){
    generateBranch(origin,initial_vector,length,segments,0);
    
    /*
     Below is where the recursion takes place. First I get the outline of the new path...
     Once that is found, generate a new branch with that point being the origin.
     I need this to be done properly. I need this to perform generateBranch() of every point a certain number of times
    */
    int branch_count = 1;
    
    for(int l = 0; l < branch_levels; l++){
        for(int i = 0; i < branch_count; i++){
            //willing to bet that it gets stuck here because we keep increasing the number of paths
            for(int j = 0; j < path.getOutline()[i].size(); j++){
                generateBranch(path.getOutline()[i].getPointAtIndexInterpolated(j),initial_vector,length, segments, l);
            }
        }
        branch_count++;
    }
}

//--------------------------------------------------------------
void ofApp::generateBranch(ofVec3f origin, ofVec3f initial_vector, float length, int segments, int level){
    path.moveTo(origin);
    
    int numPoints = segments;
    
    ofVec3f t_vec = initial_vector;
    ofPoint t_point = origin; //Origin (seed)
    
    for(int i = 0; i < numPoints; i++){
        float t_len = ofRandom(branch_length)+(branch_length/2);
        
        t_point = t_point + (t_vec*t_len);
        
        path.lineTo(t_point);

        t_vec = ofVec3f(t_vec.x + (ofRandomf()/branch_smooth),t_vec.y + (ofRandomf()/branch_smooth),t_vec.z + (ofRandomf()/branch_smooth));
    }
    
    path.newSubPath();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'b'){
        path.clear();
        setupBranches(ofVec3f(0),ofVec3f(ofRandomf(),ofRandomf(),ofRandomf()),branch_length,branch_segments);
    }
    if(key == 'd'){
        debug = !debug;
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
