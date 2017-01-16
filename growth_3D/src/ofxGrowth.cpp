#include "ofxGrowth.h"

//--------------------------------------------------------------
void Growth::setup(){
    this->density      = 0.5;
    this->length       = 0.7;
    this->scale        = 60;
    this->segments     = 20;
    this->depth        = 4;
    this->leaf_level   = 3;
    this->straightness = 0.5;
    this->origin       = ofVec3f(0,0,0);
    this->f_dim        = 0.5;
    
    this->setStrokeColor(ofFloatColor(0));
    this->setFilled(false);
    this->setStrokeWidth(1);
    
    branches.resize(this->depth);
    
    setupBranch();
}

//--------------------------------------------------------------
void Growth::addMesh(ofPolyline poly, int level){
    /*
     I want to create a vector of meshes for each level, making branches
     organized as
     
     branches[level][branch_id]
     
     
     right now the problem is with creating that initial level (which needs to be created and entered
     immediately after the first generateBranch...)
     */

    ofMesh t_mesh;
//    t_mesh.setMode(OF_PRIMITIVE_POINTS);
    t_mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
    t_mesh.addVertices(poly.getVertices());
    
    branches[level].push_back(t_mesh);
}

//--------------------------------------------------------------
void Growth::setupBranch(){
    ofVec3f initial_vector = ofVec3f(ofRandomf(),ofRandomf(),ofRandomf());
    
    generateBranch(this->origin, initial_vector, 0);
    
    addMesh(this->getOutline()[0],0);
    
    int branch_count  = 1;
    
    for(int current_level = 1; current_level < this->depth; current_level++){
        for(int current_branch = 0; current_branch < branch_count; current_branch++){ //for however many branches are currently there

            for(int current_node = 0; current_node < this->getOutline()[current_branch].size(); current_node++){
                
                ofVec3f current_node_position = this->getOutline()[current_branch].getPointAtIndexInterpolated(current_node);
                ofVec3f t_vec = initial_vector.rotate(ofRandomf()*360, initial_vector);
                
                if(ofRandomuf() < this->density){
                    generateBranch(current_node_position, t_vec, current_level);
                }
            }
            addMesh(this->getOutline()[current_branch],current_level);
            
        }
        branch_count = this->getOutline().size();
    }
}

//--------------------------------------------------------------
void Growth::generateBranch(ofVec3f origin, ofVec3f initial_vector, int level){
    this->moveTo(origin);
    
    //Diminish parameters
    int t_segments = this->segments * pow(this->f_dim,level);
    float t_length = (this->length * this->scale) * pow(this->f_dim,level);
    
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
void Growth::drawPaths(){
    this->draw();
}

//--------------------------------------------------------------
void Growth::drawPoints(){

}

//--------------------------------------------------------------
void Growth::drawMeshes(){
    for(int i = 0; i < branches.size(); i++){
        for(int j = 0; j < branches[i].size(); j++){
            branches[i][j].draw();
        }
    }
}

//--------------------------------------------------------------
void Growth::clearAll(){
    this->clear();
}
