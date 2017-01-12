#include "ofxGrowth.h"

//--------------------------------------------------------------
void Growth::setup(){
    this->setStrokeWidth(1);
    this->setStrokeColor(ofColor(0));
    this->setFilled(false);
    
    this->smoothness = 4.0;
    this->length     = 20.0;
    this->density    = 0.2;
    this->levels     = 2;
    this->segments   = 8;
    
    setupBranches(ofVec3f(0),ofVec3f(ofRandomf(),ofRandomf(),ofRandomf()),length,segments);
    
    b_leaf = false;
}

//--------------------------------------------------------------
void Growth::setupBranches(ofVec3f origin, ofVec3f initial_vector, float length, int segments){
    generateBranch(origin,initial_vector,length,segments,0);
    
    int branch_count = 1;
    int current_level = 1;
    
    for(int l = 0; l <= levels; l++){
        for(int i = 0; i < branch_count; i++){
            
            for(int j = 0; j < this->getOutline()[i].size(); j++){
                if(ofRandomuf() < density){
                    generateBranch(this->getOutline()[i].getPointAtIndexInterpolated(j), initial_vector.rotate(ofRandomf()*360, initial_vector), length, segments, current_level);
                }
            }
            current_level++;
        }
        branch_count++;
    }
}

//--------------------------------------------------------------
void Growth::generateBranch(ofVec3f origin, ofVec3f initial_vector, float length, int segments, int level){
    this->moveTo(origin);
    
    int numPoints = segments / ((float)level + 1)*PI;
    
    ofVec3f t_vec = initial_vector;
    ofPoint t_point = origin;
    
    for(int i = 0; i < numPoints; i++){
        float t_len = length / ((float)level + 1)*PI;
        
        t_point = t_point + (t_vec*t_len);
        
        this->lineTo(t_point);
        
        t_vec = ofVec3f(t_vec.x + (ofRandomf()/smoothness),t_vec.y + (ofRandomf()/smoothness),t_vec.z + (ofRandomf()/smoothness));
        
    if(ofRandomuf() < density*3.5){
            if(level > 1){
                generateLeaf(t_point, initial_vector.rotate(ofRandomf()*360, initial_vector), length, segments, level);
            }
        }
    }
    
    this->newSubPath();
}

//--------------------------------------------------------------
void Growth::generateLeaf(ofVec3f origin, ofVec3f initial_vector, float length, int segments, int level){

    ofPath t_leaf;
    t_leaf.setStrokeWidth(1);
    t_leaf.setStrokeColor(ofColor(0));
    t_leaf.setFillColor(ofColor(0,255,255));
    t_leaf.setFilled(true);
    t_leaf.moveTo(origin);
    
    int numPoints = segments / ((float)level + 1)*PI;
    
    ofVec3f t_vec = initial_vector;
    ofPoint t_point = origin;
    
    for(int i = 0; i < numPoints; i++){
        float t_len = length / ((float)level + 1)*PI;
        
        t_point = t_point + (t_vec * t_len);
        
        t_leaf.lineTo(t_point);
        
        t_vec = ofVec3f(t_vec.x + (ofRandomf()/smoothness),t_vec.y + (ofRandomf()/smoothness),t_vec.z + (ofRandomf()/smoothness));
    }
    t_leaf.close();
    
    leaves.push_back(t_leaf);
}

//--------------------------------------------------------------
void Growth::drawGrowth(){
    this->draw();
    for(int i = 0; i < leaves.size(); i++){
        leaves[i].draw();
    }
}

//--------------------------------------------------------------
void Growth::drawDebug(){
    for(int i = 0; i < this->getOutline().size(); i++){
        for(int j = 0; j < this->getOutline()[i].size(); j++){
            ofPoint t_point = this->getOutline()[i].getPointAtIndexInterpolated(j);
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
void Growth::clearAll(){
    this->clear();
    leaves.clear();
}
