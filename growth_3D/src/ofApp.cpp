#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    path.setStrokeWidth(1);
    path.setStrokeColor(ofColor(0));
    path.setFilled(false);
    
    branch.add(branch_smooth.set("Smooth",4.0,0.0,20.0));
    branch.add(branch_length.set("Length",20.0,0.0,20.0));
    branch.add(branch_levels.set("Levels",1,1,10));
    branch.add(branch_segments.set("Segments",15,1,50));
    branch.add(cam_orbit.set("Orbit",15,0,360));
    branch.add(cam_lat.set("Orbit",15,0,360));
    
    gui.setup();
    gui.add(branch);
    
    setupBranches(ofVec3f(0),ofVec3f(ofRandomf(),ofRandomf(),ofRandomf()),branch_length,branch_segments);
    
    cam.setFarClip(20000.0);
}

//--------------------------------------------------------------
void ofApp::update(){
    cam.orbit((ofGetElapsedTimef())*15,(ofGetElapsedTimef()*1.5)*15, 10000);
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
    
    int branch_count = 1;
    
    int current_level = 0;
    
    for(int l = 0; l < branch_levels; l++){
        for(int i = 0; i < branch_count; i++){
            for(int j = 0; j < path.getOutline()[i].size(); j++){
                
                /*
                    Initial vector shouldn't be used for each.
                    Let's walk through the problem
                    It looks like I am getting the unnatural shape that I am by using the initial vector only in each of the nested branches. I need the initial vector, but also a RANDOM rotation of it, around the axis, defined by the INITIAL VECTOR.
                */
                generateBranch(path.getOutline()[i].getPointAtIndexInterpolated(j), initial_vector.rotate(ofRandomf()*360, initial_vector), length, segments, current_level);
//                generateBranch(path.getOutline()[i].getPointAtIndexInterpolated(j),ofVec3f(ofRandomf(),ofRandomf(),ofRandomf()),length, segments, l);
            }
            current_level++;
        }
        branch_count++;
    }
}

//--------------------------------------------------------------
void ofApp::generateBranch(ofVec3f origin, ofVec3f initial_vector, float length, int segments, int level){
    path.moveTo(origin);
    
    
    // WHY ISN'T LEVEL SHOWING UP AS ANYTHING?
    
    int numPoints = segments / ((float)level + 1)*PI;
    
    ofVec3f t_vec = initial_vector;
    ofPoint t_point = origin; //Origin (seed)
    
    for(int i = 0; i < numPoints; i++){
        float t_len = length / ((float)level + 1)*PI;
        
        t_point = t_point + (t_vec*t_len);
        
        path.lineTo(t_point);

        /*
            Below we update the vector to being the previous vector + something random.
            since ofRandomf() returns -1 to 1, this should actually be fine. 
            I guess it comes down to whether or not I ADD to the original vector, or just create a new one.
         */
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
