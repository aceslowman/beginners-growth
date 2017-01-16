#include "ofxGrowth.h"

//--------------------------------------------------------------
void Growth::setup(){
    this->density      = ofRandomuf();
    this->length       = ofRandomuf();
    this->segments     = ofRandom(10);
    this->depth        = ofRandom(10);
    this->leaf_level   = ofRandom(10);
    this->straightness = ofRandomuf();
    
    generateBranch(ofVec3f(0),ofVec3f(ofRandomf(),ofRandomf(),ofRandomf()),0);
}

//--------------------------------------------------------------
void Growth::setupBranch(){
    int current_branch = 1;
    int current_level  = 1;
    
    for(int i = 0; i <= this->depth; i++){ // loop a level
        for(int j = 0; j < current_branch; j++){  // loop through each node
            for(EACH NODE IN THIS BRANCH)
                if(ofRandomuf() < this->density){ //introduce probability
                    generateBranch(THIS CURRENT NODE, initial_vector.rotate(ofRandomf()*360, initial_vector), current_level);
                }
        }
        current_branch++;
    }
    current_level++;
}
    
    //    generateBranch(origin,initial_vector,length,segments,0);
    //
    //    int branch_count = 1;
    //    int current_level = 1;
    //
    //    for(int l = 0; l <= levels; l++){
    //        for(int i = 0; i < branch_count; i++){
    //
    //            for(int j = 0; j < this->getOutline()[i].size(); j++){
    //                if(ofRandomuf() < density){
    //                    generateBranch(this->getOutline()[i].getPointAtIndexInterpolated(j), initial_vector.rotate(ofRandomf()*360, initial_vector), length, segments, current_level);
    //                }
    //            }
    //            current_level++;
    //        }
    //        branch_count++;
    //    }
}

//--------------------------------------------------------------
void Growth::generateBranch(ofVec3f origin, ofVec3f initial_vector, int level){
    ofMesh t_mesh;
    
    if(current_level > leaf_level){
        t_mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    }else{
        t_mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
    }
    
    //Diminish parameters
    int t_segments = this->segments * pow(f_dim,level);
    float t_length = this->length   * pow(f_dim,level);
    
    //Initialize t_point to match initial point
    ofVec3f t_point = origin;
    
    //begin assembling one cycle of sequence
    for(int i = 0; i < t_segments; i++){
        
        t_point = t_point + (t_vec * ( t_length * ofRandomuf() ) );
        
        t_mesh.addVertex(t_point);
        t_mesh.addColor(ofFloatColor(i/t_segments,1 - (i/t_segments),0));
        
        t_vec = ofVec3f(
                        ofClamp(t_vec.x + (ofRandomf() * straightness),0.0,1.0),
                        ofClamp(t_vec.y + (ofRandomf() * straightness),0.0,1.0),
                        ofClamp(t_vec.z + (ofRandomf() * straightness),0.0,1.0)
                        );
    }
    
    if(current_level > leaf_level){
        leaves.push_back(t_mesh);
    }else{
        branch.append(t_mesh);
    }
}




//
////--------------------------------------------------------------
//void Growth::setupBranches(ofVec3f origin, ofVec3f initial_vector, float length, int segments){
//    generateBranch(origin,initial_vector,length,segments,0);
//    
//    int branch_count = 1;
//    int current_level = 1;
//    
//    for(int l = 0; l <= levels; l++){
//        for(int i = 0; i < branch_count; i++){
//            
//            for(int j = 0; j < this->getOutline()[i].size(); j++){
//                if(ofRandomuf() < density){
//                    generateBranch(this->getOutline()[i].getPointAtIndexInterpolated(j), initial_vector.rotate(ofRandomf()*360, initial_vector), length, segments, current_level);
//                }
//            }
//            current_level++;
//        }
//        branch_count++;
//    }
//}
//
////--------------------------------------------------------------
//void Growth::generateBranch(ofVec3f origin, ofVec3f initial_vector, float length, int segments, int level){
//    this->moveTo(origin);
//    
//    int numPoints = segments / ((float)level + 1)*PI;
//    
//    ofVec3f t_vec = initial_vector;
//    ofPoint t_point = origin;
//    
//    for(int i = 0; i < numPoints; i++){
//        float t_len = length / ((float)level + 1)*PI;
//        
//        t_point = t_point + (t_vec*t_len);
//        
//        this->lineTo(t_point);
//        
//        t_vec = ofVec3f(t_vec.x + (ofRandomf()/smoothness),t_vec.y + (ofRandomf()/smoothness),t_vec.z + (ofRandomf()/smoothness));
//        
//        if(ofRandomuf() < density*3.5){
//            if(level > 2){
//                generateLeaf(t_point, initial_vector.rotate(ofRandomf()*360, initial_vector), length, segments, level);
//            }
//        }
//    }
//    
//    this->newSubPath();
//}
//
////--------------------------------------------------------------
//void Growth::generateLeaf(ofVec3f origin, ofVec3f initial_vector, float length, int segments, int level){
//    float theta   = 0.2;
//    int numPoints = segments / ((float)level + 1)*2*PI;
//    
//    ofVec3f t_vec = initial_vector;
//    ofPoint t_point = origin;
//    ofPoint t_point_mirrored = origin;
//    
//    ofMesh t_leaf;
//    
//    t_leaf.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
//    t_leaf.setMode(OF_PRIMITIVE_LINE_STRIP);
//    
//    t_leaf.addVertex(origin);
//    t_leaf.addColor(ofFloatColor(0,0,1));
//    
//    for(int i = 0; i < numPoints; i++){
//        float t_len = length / ((float)level + 1)*3*PI;
//
//        t_point = t_point + (t_vec * t_len);
//        t_point_mirrored = t_point_mirrored + (ofVec2f(-t_vec.x,t_vec.y)*t_len);
//
//        t_leaf.addVertex(t_point);
//        t_leaf.addColor(ofFloatColor(1,0,0));
//        t_leaf.addVertex(t_point_mirrored.rotate(theta, origin, t_vec));
//
//        t_leaf.addColor(ofFloatColor(0,1,0));
//        
//        t_vec = ofVec3f(t_vec.x + (ofRandomf()/smoothness),t_vec.y + (ofRandomf()/smoothness),t_vec.z + (ofRandomf()/smoothness));
//    }
//    
//    leaves.push_back(t_leaf);
//}
//
////--------------------------------------------------------------
//void Growth::drawGrowth(){
//    this->draw();
//    if(b_drawLeaves){
//        for(int i = 0; i < leaves.size(); i++){
//            leaves[i].draw();
////            leaves[i].getTessellation().draw();
//        }
//    }
//}
//
////--------------------------------------------------------------
//void Growth::drawDebug(){
//    for(int i = 0; i < this->getOutline().size(); i++){
//        for(int j = 0; j < this->getOutline()[i].size(); j++){
//            ofPoint t_point = this->getOutline()[i].getPointAtIndexInterpolated(j);
//            ofPushMatrix();
//            ofTranslate(t_point);
//            ofSetColor(ofColor(255,0,0));
//            ofNoFill();
//            ofSetSphereResolution(5);
//            ofDrawSphere(0,0,2);
//            ofSetColor(ofColor(0,0,255));
//            ofDrawBitmapString(ofToString(i), 0,0);
//            ofPopMatrix();
//        }
//    }
//}
//
////--------------------------------------------------------------
//void Growth::clearAll(){
//    this->clear();
//    leaves.clear();
//}
