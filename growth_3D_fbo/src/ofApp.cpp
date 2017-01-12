#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    
    outputFbo.allocate(ofGetWidth(),ofGetHeight());
    
    
    branch_group.add(branch_smooth.set("Smooth",4.0,0.0,20.0));
    branch_group.add(branch_length.set("Length",20.0,0.0,20.0));
    branch_group.add(branch_density.set("Density",0.2,0.0,1.0));
    branch_group.add(branch_levels.set("Levels",2,1,10));
    branch_group.add(branch_segments.set("Segments",8,1,50));
    branch_group.add(branch_stroke.set("Stroke",2,1,100));
    branch_group.add(path_top_color.set("Top Path",ofColor(0,0,0,0)));
    branch_group.add(fade_color.set("Fade Color",ofColor(0,0,0,0)));
    branch_group.add(b_randColor.set("Random Colors?",false));
    camera_group.add(cam_long.set("Longitude",15,0,360));
    camera_group.add(cam_lat.set("Latitude",15,0,360));
    
    gui.setup();
    gui.add(branch_group);
    gui.add(camera_group);
    
    cam.setFarClip(20000.0);
    
    t_center = ofPoint(0);
    
    growth.setup();
    
    outputFbo.begin();
    ofClear(255,255,255,0);
    outputFbo.end();
}

//--------------------------------------------------------------
void ofApp::update(){
    if(b_orbit)
    cam.orbit((ofGetElapsedTimef())*15,(ofGetElapsedTimef()*1.5)*15, 1000);
    
    growth.smoothness = branch_smooth;
    growth.length     = branch_length;
    growth.density    = branch_density;
    growth.levels     = branch_levels;
    growth.segments   = branch_segments;
    
    growth.setStrokeWidth(branch_stroke);
}

//--------------------------------------------------------------
void ofApp::draw(){
//    ofEnableAntiAliasing();
//    ofEnableSmoothing();
    
    
    if(b_snapCenter){
        ofDrawBitmapString("SNAP",30,30);
    }

    ofSetBackgroundColor(ofColor(0));
    outputFbo.begin();
    
        if( ofGetKeyPressed('c') ){
            ofClear(255,255,255,0);
        }
        
        ofFill();
        ofSetColor(fade_color);
        ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
        ofNoFill();
    
        ofEnableDepthTest();
        cam.begin();
            if(b_randColor){
                growth.setStrokeColor(ofFloatColor(ofRandom(0.1,1.0),ofRandom(0.1,1.0),ofRandom(0.1,1.0)));
            }else{
                growth.setStrokeColor( ofFloatColor(sin(ofGetElapsedTimef()*0.2),sin(ofGetElapsedTimef()*0.5),sin(ofGetElapsedTimef())) );
            }
    
            ofPushMatrix();
            ofTranslate(t_center);
            growth.drawGrowth();
            ofPopMatrix();
        cam.end();
        ofDisableDepthTest();
    
    outputFbo.end();
    
    outputFbo.draw(0,0);
    
//    cam.begin();
//    ofPushMatrix();
//    ofTranslate(t_center);
//    growth.drawGrowth();
//    ofPopMatrix();
//    cam.end();
    
    ofDisableAntiAliasing();
    
    
    syphon.publishScreen();
    gui.draw();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'b'){
        growth.setupBranches(ofVec3f(0),ofVec3f(ofRandomf(),ofRandomf(),ofRandomf()),branch_length,branch_segments);
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
