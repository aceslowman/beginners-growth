#include "ofxGrowth.h"

//--------------------------------------------------------------
void Growth::setup(){
    this->density      = 0.5;
    this->length       = 0.7;
    this->segments     = 20;
    this->depth        = 3;
    this->leaf_level   = 3;
    this->straightness = 0.5;
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
    
    int branch_count  = 1;
    int current_level = 1;
    
    for(int i = 0; i <= this->depth; i++){
        
        for(int j = 0; j < branch_count; j++){
            
            for(int k = 0; k < this->getOutline()[i].size(); k++){
                ofVec3f current_node_position = this->getOutline()[i].getPointAtIndexInterpolated(k);
                ofVec3f t_vec = initial_vector.rotate(ofRandomf()*360, initial_vector);
                
                if(ofRandomuf() < this->density){
                    generateBranch(current_node_position, t_vec, current_level);
                }
            }
            current_level++;
        }
        branch_count++;
    }
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
