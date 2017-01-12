#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    path.setStrokeWidth(3);
    path.setStrokeColor(ofColor(0));
    path.setFilled(false);
    
    outputFbo.allocate(ofGetWidth(),ofGetHeight());
    
    //TODO: Normalize all of these control values
    branch_group.add(branch_smooth.set("Smooth",4.0,0.0,20.0));
    branch_group.add(branch_length.set("Length",20.0,0.0,20.0));
    branch_group.add(branch_density.set("Density",0.2,0.0,1.0));
    branch_group.add(branch_levels.set("Levels",2,1,10));
    branch_group.add(branch_stroke.set("Stroke",2,1,100));
    branch_group.add(branch_segments.set("Segments",8,1,50));
    branch_group.add(path_top_color.set("Top Path",ofColor(0,0,0,0)));
    branch_group.add(fade_color.set("Fade Color",ofColor(0,0,0,0)));
    branch_group.add(b_randColor.set("Random Colors?",false));
    camera_group.add(cam_long.set("Longitude",15,0,360));
    camera_group.add(cam_lat.set("Latitude",15,0,360));
    camera_group.add(cam_fade.set("Fade",1.0,0.0,100.0));
    
    gui.setup();
    gui.add(branch_group);
    gui.add(camera_group);
    
    setupBranches(ofVec3f(0),ofVec3f(ofRandomf(),ofRandomf(),ofRandomf()),branch_length,branch_segments);
    
    cam.setFarClip(20000.0);
    
    outputFbo.begin();
    ofClear(255,255,255,0);
    outputFbo.end();
}

//--------------------------------------------------------------
void ofApp::update(){
    
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    ofEnableAntiAliasing();
    
    if(b_orbit)
        cam.orbit((ofGetElapsedTimef())*15,(ofGetElapsedTimef()*1.5)*15, 5000);
    
    path.setStrokeWidth(branch_stroke);
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetBackgroundColor(ofColor(0));
    outputFbo.begin();
    
        if( ofGetKeyPressed('c') ){
            ofClear(255,255,255,0);
        }
        
        ofFill();
        ofSetColor(fade_color);
        ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
        ofNoFill();
        
        cam.begin();
            if(b_randColor){
                path.setStrokeColor(ofFloatColor(ofRandomuf(),ofRandomuf(),ofRandomuf()));
            }else{
                path.setStrokeColor( ofFloatColor(sin(ofGetElapsedTimef()*0.2),sin(ofGetElapsedTimef()*0.5),sin(ofGetElapsedTimef())) );
            }
            ofPushMatrix();
            path.draw();
            if(debug)
                drawDebug();
            ofPopMatrix();
        cam.end();
    
    outputFbo.end();
    
    outputFbo.draw(0,0);
    
    cam.begin();
        path.setColor(path_top_color);
        path.draw();
    cam.end();
    
    syphon.publishScreen();
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::drawDebug(){
    for(int i = 0; i < path.getOutline().size(); i++){
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
                if(ofRandomuf() < branch_density){
                    generateBranch(path.getOutline()[i].getPointAtIndexInterpolated(j), initial_vector.rotate(ofRandomf()*360, initial_vector), length, segments, current_level);
                }
            }
            current_level++;
        }
        branch_count++;
    }
}

//--------------------------------------------------------------
void ofApp::generateBranch(ofVec3f origin, ofVec3f initial_vector, float length, int segments, int level){
    path.moveTo(origin);
    
    int numPoints = segments / ((float)level + 1)*PI;
    
    ofVec3f t_vec = initial_vector;
    ofPoint t_point = origin; //Origin (seed)
    
    for(int i = 0; i < numPoints; i++){
        float t_len = length / ((float)level + 1)*PI;
        
        t_point = t_point + (t_vec*t_len);
        
        path.lineTo(t_point);
        
        t_vec = ofVec3f(t_vec.x + (ofRandomf()/branch_smooth),t_vec.y + (ofRandomf()/branch_smooth),t_vec.z + (ofRandomf()/branch_smooth));
    }
    
    path.newSubPath();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'b'){
        setupBranches(ofVec3f(0),ofVec3f(ofRandomf(),ofRandomf(),ofRandomf()),branch_length,branch_segments);
    }
    if(key == 'c'){
        path.clear();
    }
    if(key == 'd'){
        debug = !debug;
    }
    if(key == 'o'){
        b_orbit = !b_orbit;
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
