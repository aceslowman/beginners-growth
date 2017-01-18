#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    glCullFace(GL_BACK);
    ofSetVerticalSync(true);
    
    growth_group.add(growth_density.set("Density",0.5,0.0,1.0));
    growth_group.add(growth_length.set("Length",0.5,0.0,1.0));
    growth_group.add(growth_straightness.set("Straightness",0.5,0.0,1.0));
    growth_group.add(growth_segments.set("Segments",15,0,30));
    growth_group.add(growth_depth.set("Depth",4,1,10));

    gui.setup();
    gui.add(growth_group);
    
    growth.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
    growth.setDensity(growth_density);
    growth.setLength(growth_length);
    growth.setSegments(growth_segments);
    growth.setDepth(growth_depth);
    growth.setStraightness(growth_straightness);
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableAntiAliasing();
    ofEnableSmoothing();
    ofEnableDepthTest();
    
    ofSetBackgroundColor(ofFloatColor(1));
    ofSetColor(ofColor(0));
    
    cam.begin();
        growth.drawMeshes();
        growth.drawLeaves();
        if(debug)
            growth.drawDebug();
    cam.end();
    
    ofDisableAntiAliasing();
    ofDisableDepthTest();
    
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'b'){
        growth.clearAll();
        growth.setup();
    }
    if(key == 'c'){
        growth.clearAll();
    }
    if(key == 'd'){
        debug = !debug;
    }
    
    if(key == '1')
        growth.colorMesh(0);
    if(key == '2')
        growth.colorMesh(1);
    if(key == '3')
        growth.colorMesh(2);
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
