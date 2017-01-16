#include "ofxGrowth.h"

//--------------------------------------------------------------
void Growth::setup(){
    this->density      = ofRandomuf();
    this->length       = 0.7;
//    this->segments     = ofRandom(10);
    this->segments     = 15;
    this->depth        = ofRandom(10);
    this->leaf_level   = ofRandom(10);
    this->straightness = ofRandomuf();
    this->origin       = ofVec3f(0,0,0);
    this->f_dim        = 0.5;
    
    this->setStrokeColor(ofFloatColor(0));
    this->setFilled(false);
    this->setStrokeWidth(2);
    
    setupBranch();
}

//--------------------------------------------------------------
void Growth::setupBranch(){
    ofVec3f initial_vector = ofVec3f(ofRandomf(),ofRandomf(),ofRandomf());
    
    generateBranch(this->origin, initial_vector, 0);
    
    int current_branch = 1;
    int current_level  = 2;
    
//    for(int i = 0; i <= this->depth; i++){
//        
//        for(int j = 0; j < current_branch; j++){
//            
//            for(int k = 0; k < this->getOutline()[i].size(); k++){
//                ofVec3f current_node_position = this->getOutline()[i].getPointAtIndexInterpolated(k);
//                ofVec3f t_vec = initial_vector.rotate(ofRandomf()*360, initial_vector);
//                
//                if(ofRandomuf() < this->density){
//                    generateBranch(current_node_position, t_vec, current_level);
//                }
//            }
//            current_branch++;
//        }
//        current_level++;
//    }
}

//--------------------------------------------------------------
void Growth::generateBranch(ofVec3f origin, ofVec3f initial_vector, int level){
    this->moveTo(origin);
    
    //Diminish parameters
    int t_segments = this->segments * pow(this->f_dim,level);
    float t_length = (this->length * 30) * pow(this->f_dim,level);
    
    //Initialize vector and point
    ofVec3f t_vec = initial_vector;
    ofVec3f t_point = origin;
    
    //begin assembling one cycle of sequence
    for(int i = 0; i < t_segments; i++){
        
        t_point = t_point + (t_vec * ( t_length * ofRandomuf() ) );
        
        this->lineTo(t_point);
        
        t_vec = ofVec3f(
            ofClamp(t_vec.x + (ofRandomf() * straightness),-1.0,1.0),
            ofClamp(t_vec.y + (ofRandomf() * straightness),-1.0,1.0),
            ofClamp(t_vec.z + (ofRandomf() * straightness),-1.0,1.0)
        );
    }
    
    this->newSubPath();
}

//--------------------------------------------------------------
void Growth::drawPath(){
    this->draw();
}

//--------------------------------------------------------------
void Growth::clearAll(){
    this->clear();
}
