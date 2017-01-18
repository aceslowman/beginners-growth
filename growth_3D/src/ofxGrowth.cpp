#include "ofxGrowth.h"


//--------------------------------------------------------------
Growth::Growth(){
    this->density      = 0.2;
    this->length       = 0.7;
    this->scale        = 60;
    this->segments     = 35;
    this->depth        = 4;
    this->leaf_level   = 3;
    this->straightness = 0.5;
    this->origin       = ofVec3f(0,0,0);
    this->f_dim        = 0.5;
    this->color_mode   = 0;

    glPointSize(8);
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
            
        case 2: //all black branches, random colored leaves
            for(int i = 0; i < branches.size(); i++){
                

                if(i < this->leaf_level){
                    for(int j = 0; j < branches[i].size(); j++){
                        for(int k = 0; k < branches[i][j].getVertices().size(); k++){
                            branches[i][j].setColor(k, ofFloatColor(0));
                        }
                    }
                }else{
                    ofFloatColor branch_color = ofFloatColor(ofRandomuf(),ofRandomuf(),ofRandomuf());
                    for(int j = 0; j < branches[i].size(); j++){
                        for(int k = 0; k < branches[i][j].getVertices().size(); k++){
                            branches[i][j].setColor(k, branch_color);
                        }
                    }
                }
            }
            
            break;
        default:
            break;
    }
}

//--------------------------------------------------------------
void Growth::setupBranch(){
    ofVec3f initial_vector = ofVec3f(ofRandomf(),ofRandomf(),ofRandomf());
    
    generateBranch(this->origin, initial_vector, 0);
    
    for(int current_level = 0; current_level < this->depth-1; current_level++){
        
        for(int current_branch = 0; current_branch < branches[current_level].size(); current_branch++){
            
            for(int current_node = 0; current_node < branches[current_level][current_branch].getVertices().size(); current_node++){
                
                ofVec3f current_node_position = branches[current_level][current_branch].getVertex(current_node);
                
                ofVec3f t_vec = initial_vector.rotate(ofRandomf()*360, initial_vector);
                
                if(ofRandomuf() < this->density){
                    generateBranch(current_node_position, t_vec, current_level+1);
                }
            }
        }
    }
}

//--------------------------------------------------------------
void Growth::generateBranch(ofVec3f origin, ofVec3f initial_vector, int level){
    ofMesh t_branch;
    t_branch.setMode(OF_PRIMITIVE_LINE_STRIP);
    t_branch.setupIndicesAuto();
    
    t_branch.addIndex(0);
    t_branch.addVertex(origin);
    
    //Diminish parameters
//    int t_segments = this->segments * pow(this->f_dim,level);
    int t_segments = this->segments;
    float t_length = (this->length * this->scale) * pow(this->f_dim,level);
    
    //Initialize vector and point
    ofVec3f t_vec = initial_vector;
    ofVec3f t_point = origin;
    
    //begin assembling one cycle of sequence
    for(int i = 1; i < t_segments; i++){
        
        t_point = t_point + (t_vec * ( t_length * ofRandomuf() ) );
        
        t_branch.addIndex(i);
        t_branch.addColor(ofFloatColor(0));
        t_branch.addVertex(t_point);
        
        t_vec = ofVec3f(
            ofClamp(t_vec.x + (ofRandomf() * straightness),-1.0,1.0),
            ofClamp(t_vec.y + (ofRandomf() * straightness),-1.0,1.0),
            ofClamp(t_vec.z + (ofRandomf() * straightness),-1.0,1.0)
        );
    }
    
    branches[level].push_back(t_branch);
}

//--------------------------------------------------------------
void Growth::drawPoints(){
    for(int i = 0; i < branches.size(); i++){
        for(int j = 0; j < branches[i].size(); j++){
            branches[i][j].setMode(OF_PRIMITIVE_POINTS);
            branches[i][j].draw();
        }
    }
}

//--------------------------------------------------------------
void Growth::drawMeshes(){
    for(int i = 0; i < this->leaf_level; i++){
        for(int j = 0; j < branches[i].size(); j++){
            branches[i][j].draw();
        }
    }
}

//--------------------------------------------------------------
void Growth::drawLeaves(){
    for(int i = this->leaf_level; i < branches.size(); i++){
        for(int j = 0; j < branches[i].size(); j++){
            branches[i][j].setMode(OF_PRIMITIVE_TRIANGLE_FAN);
            branches[i][j].draw();
        }
    }
}

//--------------------------------------------------------------
void Growth::drawDebug(){
    for(int i = 0; i < branches.size(); i++){
        for(int j = 0; j < branches[i].size(); j++){
            for(int k = 0; k < branches[i][j].getVertices().size(); k++){
                ofPushMatrix();
                ofTranslate(branches[i][j].getVertices()[k]);
                int t_ind = branches[i][j].getIndices()[k];
                ofDrawBitmapString("ID:"+ofToString(t_ind)+" L:"+ofToString(i),0,0);
                ofPopMatrix();
            }
        }
    }
}

//--------------------------------------------------------------
void Growth::clearAll(){
    branches.clear();
}

void Growth::setDensity(float density){this->density = density;}
void Growth::setLength(float length){this->length = length;}
void Growth::setScale(float scale){this->scale = scale;}
void Growth::setSegments(int segments){this->segments = segments;}
void Growth::setDepth(int depth){this->depth = depth;}
void Growth::setStraightness(float straightness){this->straightness = straightness;}
void Growth::setColormode(int color_mode){this->color_mode = color_mode;}
