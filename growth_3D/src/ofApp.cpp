#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    glCullFace(GL_BACK);
    ofSetVerticalSync(true);
    
    growth_group.add(growth_density.set("Density",0.0,0.0,1.0));
    growth_group.add(growth_length.set("Length",0.0,0.0,1.0));
    growth_group.add(growth_straightness.set("Straightness",0.0,0.0,1.0));
    growth_group.add(growth_segments.set("Segments",15,0,30));
    growth_group.add(growth_depth.set("Depth",2,1,10));

    gui.setup();
    gui.add(growth_group);
    
    growth.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
    growth.density      = growth_density;
    growth.length       = growth_length;
    growth.segments     = growth_segments;
    growth.depth        = growth_depth;
    growth.straightness = growth_straightness;
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableAntiAliasing();
    ofEnableSmoothing();
    ofEnableDepthTest();
    
    ofSetBackgroundColor(ofColor(255,255,255));
    ofSetColor(ofColor(0));
    
    cam.begin();
        growth.drawPath();
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
