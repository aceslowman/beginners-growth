#include "ofxGrowth.h"


//--------------------------------------------------------------
Growth::Growth(){
    this->density      = 0.5;
    this->length       = 0.7;
    this->scale        = 60;
    this->segments     = 20;
    this->depth        = 4;
    this->leaf_level   = 3;
    this->straightness = 0.5;
    this->origin       = ofVec3f(0,0,0);
    this->f_dim        = 0.5;
    this->color_mode   = 0;
    
    this->setStrokeColor(ofFloatColor(0));
    this->setFilled(false);
    this->setStrokeWidth(1);
}

//--------------------------------------------------------------
void Growth::setup(){
    branches.resize(this->depth);
    
    setupBranch();
    colorMesh(this->color_mode);
}

//--------------------------------------------------------------
void Growth::colorMesh(int coloring_type){
    switch (coloring_type) {
        case 0: //color for each branch
            
            for(int i = 0; i < branches.size(); i++){
                for(int j = 0; j < branches[i].size(); j++){
                    ofFloatColor branch_color = ofFloatColor(ofRandomuf(),ofRandomuf(),ofRandomuf());
                    
                    branches[i][j].addColors(&branch_color, branches[i][j].getVertices().size());
                    for(int k = 0; k < branches[i][j].getVertices().size(); k++){
                        branches[i][j].setColor(k, branch_color);
                    }
                }
            }
            
            break;
            
        case 1: //color for each level
            for(int i = 0; i < branches.size(); i++){
                ofFloatColor branch_color = ofFloatColor(ofRandomuf(),ofRandomuf(),ofRandomuf());
                
                for(int j = 0; j < branches[i].size(); j++){
                    branches[i][j].addColors(&branch_color, branches[i][j].getVertices().size());
                    for(int k = 0; k < branches[i][j].getVertices().size(); k++){
                        branches[i][j].setColor(k, branch_color);
                    }
                }
            }
            
            break;
        default:
            break;
    }
}

//--------------------------------------------------------------
void Growth::addMesh(ofPolyline poly, int level){
    /*
     branches[level][branch_id]
     */

    ofMesh t_mesh;
    t_mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
    t_mesh.setupIndicesAuto();
    
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
    for(int i = 0; i < branches.size(); i++){
        for(int j = 0; j < branches[i].size(); j++){
            branches[i][j].setMode(OF_PRIMITIVE_POINTS);
            branches[i][j].setMode(OF_PRIMITIVE_POINTS);
            branches[i][j].draw();
        }
    }
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
    branches.clear();
}

void Growth::setDensity(float density){this->density = density;}
void Growth::setLength(float length){this->length = length;}
void Growth::setScale(float scale){this->scale = scale;}
void Growth::setSegments(int segments){this->segments = segments;}
void Growth::setDepth(int depth){this->depth = depth;}
void Growth::setStraightness(float straightness){this->straightness = straightness;}
void Growth::setColormode(int color_mode){this->color_mode = color_mode;}
