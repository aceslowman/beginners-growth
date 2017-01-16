#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    glCullFace(GL_BACK);
    ofSetVerticalSync(true);
    
    branch_group.add(branch_smooth.set("Smooth",4.0,0.0,20.0));
    branch_group.add(branch_length.set("Length",20.0,0.0,20.0));
    branch_group.add(branch_density.set("Density",0.2,0.0,1.0));
    branch_group.add(branch_levels.set("Levels",2,1,10));
    branch_group.add(branch_segments.set("Segments",8,1,50));
    
    camera_group.add(cam_long.set("Longitude",15,0,360));
    camera_group.add(cam_lat.set("Latitude",15,0,360));
    
    gui.setup();
    gui.add(branch_group);
    gui.add(camera_group);
    
    cam.setFarClip(20000.0);
    
    t_center = ofPoint(0);
    
    growth.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
    if(b_orbit)
    cam.orbit((ofGetElapsedTimef())*15,(ofGetElapsedTimef()*1.5)*15, 10000);
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableAntiAliasing();
    ofEnableSmoothing();
    ofEnableDepthTest();
    
    ofSetBackgroundColor(ofColor(255,255,255));
    ofSetColor(ofColor(0));
    
    if(b_snapCenter){
        ofDrawBitmapString("SNAP",30,30);
    }
    
    cam.begin();
        ofPushMatrix();
            ofTranslate(t_center);
            growth.drawPath();
    
        ofPopMatrix();
    cam.end();
    ofDisableAntiAliasing();
    ofDisableDepthTest();
    
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'b'){
        growth.setup();
    }
    if(key == 'c'){
        growth.clearAll();
    }
    if(key == 'd'){
        debug = !debug;
    }
    if(key == 'o'){
        b_orbit = !b_orbit;
    }
    if(key == 's'){
        b_snapCenter = !b_snapCenter;
        
        if(b_snapCenter == true && growth.hasOutline()){
            t_center = -growth.getOutline()[0].getCentroid2D();
        }else{
            t_center = ofPoint(0);
        }
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
