#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    glCullFace(GL_BACK);
    ofSetVerticalSync(true);
    ofSetSmoothLighting(true);
    
    pointLight.setDiffuseColor( ofColor(0.f, 255.f, 255.f));
    pointLight.setSpecularColor( ofColor(255.f, 255.f, 255.f));
    pointLight.setPosition(0, 0, 0);
    
    capillary_group.add(capillary_density.set("Density",0.5,0.0,1.0));
    capillary_group.add(capillary_length.set("Length",0.5,0.0,1.0));
    capillary_group.add(capillary_crookedness.set("Crookedness",0.5,0.0,1.0));
    capillary_group.add(capillary_segments.set("Segments",15,0,30));
    capillary_group.add(capillary_depth.set("Depth",4,1,10));
    capillary_group.add(capillary_leaf_level.set("Leaf Level",3,1,10));
    
    light_group.add(light_color.set("Light Color",ofFloatColor(0,0,0),ofFloatColor(0,0,0),ofFloatColor(1,1,1)));
    light_group.add(light_position.set("Light Position",ofVec3f(0,0,0), ofVec3f(-200,-200,-200), ofVec3f(200,200,200)));
    
    gui.setup();
    gui.add(capillary_group);
    gui.add(light_group);
    
    capillary.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
    capillary.setDensity(capillary_density);
    capillary.setLength(capillary_length);
    capillary.setSegments(capillary_segments);
    capillary.setDepth(capillary_depth);
    capillary.setCrookedness(capillary_crookedness);
    capillary.setLeafLevel(capillary_leaf_level);
    
    pointLight.setPosition(light_position);
    pointLight.setDiffuseColor(light_color);
    
    //capillary.animateCapillary();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableLighting();
    ofEnableAntiAliasing();
    ofEnableSmoothing();
    ofEnableDepthTest();
    
    ofSetBackgroundColor(ofFloatColor(0));
    ofSetColor(ofColor(0));
    
    cam.begin();
    pointLight.enable();
    
    capillary.drawMeshes();
    
    ofSetColor(ofFloatColor(1));
    ofDrawSphere(pointLight.getPosition(), 5);
    cam.end();
    
    ofDisableAntiAliasing();
    ofDisableDepthTest();
    ofDisableLighting();
    
    syphon.publishScreen();
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'b'){
        capillary.clearAll();
        capillary.setup();
    }
    if(key == 'c'){
        capillary.clearAll();
    }
    
    if(key == '1')
        capillary.setColormode(0);
    if(key == '2')
        capillary.setColormode(1);
    if(key == '3')
        capillary.setColormode(2);
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
