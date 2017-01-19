#include "ofxGrowth.h"


//--------------------------------------------------------------
Growth::Growth(){
    this->density       = 0.2;
    this->length        = 0.7;
    this->scale         = 60;
    this->segments      = 35;
    this->depth         = 4;
    this->leaf_level    = 4;
    this->crookedness   = 0.5;
    this->origin        = ofVec3f(0,0,0);
    this->f_dim         = 0.5;
    this->color_mode    = 0;
    this->growth_vector = ofVec3f(0,1,0);

    glPointSize(8);
}

//--------------------------------------------------------------
void Growth::setup(){
    /*
        PLUS 1 hack below, because there is something that is poorly structured in the setupBranches() method.
        Most likely having to do with the logic inherent behind
            Create one initial branch and level
            Loop through that level and branch, create new branches from it
     
        There is this kind of mismatch between current_level values. Does current_level refer to the level that I'm inserting?
        Or is it more that current_level refers to the branch that I am looping through. It should be the latter.
     
        CURRENT_LEVEL refers to the level that is being looped through, and all branches generated are then pushed back into the
        branches vector when the loop is over. This is a fix that I need to come back to eventually. For now, this fix:
     */
    
//    branches.resize(this->depth);
//    leaves.resize(this->depth);
    
    setupBranches();
    
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
void Growth::setupBranches(){
    vector<ofMesh> t_branches, t_leaves;
    
    ofVec3f initial_vector = this->growth_vector;
    
    ofMesh t_branch = generateBranch(this->origin, initial_vector, 0);
    t_branches.push_back(t_branch);
    branches.push_back(t_branches);
    
    for(int current_level = 0; current_level < this->depth; current_level++){
        vector<ofMesh> t_branches;
        
        for(int current_branch = 0; current_branch < branches[current_level].size(); current_branch++){

            for(int current_node = 0; current_node < branches[current_level][current_branch].getVertices().size(); current_node++){
                
                ofVec3f current_node_position = branches[current_level][current_branch].getVertex(current_node);
                ofVec3f t_vec = initial_vector.rotate(ofRandomf()*360, initial_vector);
                
                if(ofRandomuf() < this->density){
                    ofMesh t_branch = generateBranch(current_node_position, t_vec, current_level+1);
                    t_branches.push_back(t_branch);
                }
            }
        }
        branches.push_back(t_branches);
    }
}

/*
 
 ofVec3f initial_vector = this->growth_vector;
 
 generateBranch(this->origin, initial_vector, 0);
 
 for(int current_level = 0; current_level < this->depth-1; current_level++){
 for(int current_branch = 0; current_branch < branches[current_level].size(); current_branch++){
 
 //To generate new branches
 for(int current_node = 0; current_node < branches[current_level][current_branch].getVertices().size(); current_node++){
 
 ofVec3f current_node_position = branches[current_level][current_branch].getVertex(current_node);
 ofVec3f t_vec = initial_vector.rotate(ofRandomf()*360, initial_vector);
 
 if(ofRandomuf() < this->density){
 generateBranch(current_node_position, t_vec, current_level+1);
 }
 }
 
 //To leaf a branch
 if(current_level >= this->leaf_level){
 generateLeaf(branches[current_level][current_branch].getVertices(),current_level);
 }
 }
 }
 
 */

//--------------------------------------------------------------
ofMesh Growth::generateBranch(ofVec3f origin, ofVec3f initial_vector, int level){
    ofMesh t_branch;
    t_branch.setMode(OF_PRIMITIVE_LINE_STRIP);
    t_branch.setupIndicesAuto();
    
    t_branch.addIndex(0);
    t_branch.addVertex(origin);
    
    //Diminish parameters
    int t_segments = this->segments;
    float t_length = (this->length * this->scale) * pow(this->f_dim,level);
    
    //Initialize vector and point
    ofVec3f t_vec          = initial_vector;
    ofVec3f t_point        = origin;
    ofVec3f t_point_mirror = origin;
    
    //begin assembling one cycle of sequence
    for(int i = 1; i < t_segments; i++){
        float t_length_rand = ( t_length * ofRandomuf() );
        t_point = t_point + (t_vec *  t_length_rand);
        
        t_branch.addIndex(i);
        t_branch.addColor(ofFloatColor(0));
        t_branch.addVertex(t_point);
        
        t_vec = ofVec3f(
            ofClamp(t_vec.x + (ofRandomf() * this->crookedness),-1.0,1.0),
            ofClamp(t_vec.y + (ofRandomf() * this->crookedness),-1.0,1.0),
            ofClamp(t_vec.z + (ofRandomf() * this->crookedness),-1.0,1.0)
        );
    }
    
//    branches[level].push_back(t_branch);
    return t_branch;
}

//--------------------------------------------------------------
ofMesh Growth::generateLeaf(ofPolyline poly, int level){
    ofPath t_path, t_path_mirrored;
    
    ofVec3f p1(poly[0]);
    ofVec3f p2(poly[poly.size()-1]);
    
    ofVec3f t_vec(p2 - p1);
    ofVec3f t_vec_ortho(ofRandomf(),ofRandomf(),ofRandomf());
    t_vec_ortho.cross(t_vec.normalize());
    
    ofVec3f cp1(p1 + (t_vec_ortho*15));
    ofVec3f cp2(p2 + (t_vec_ortho*15));
    
    t_path.moveTo(poly[0]);
    t_path.bezierTo(cp1,cp2,p2);
    
    leaves[level].push_back(t_path);
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
    for(int i = 0; i < branches.size(); i++){
        for(int j = 0; j < branches[i].size(); j++){
            branches[i][j].setMode(OF_PRIMITIVE_LINE_STRIP);
            branches[i][j].draw();
        }
    }
}

//--------------------------------------------------------------
void Growth::drawLeaves(){
    for(int i = this->leaf_level; i < leaves.size(); i++){
        for(int j = 0; j < leaves[i].size(); j++){
            leaves[i][j].setFilled(false);
            leaves[i][j].setStrokeColor(ofFloatColor(0));
            leaves[i][j].setStrokeWidth(2);
            leaves[i][j].draw();
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
    leaves.clear();
}

void Growth::setDensity(float density){this->density = density;}
void Growth::setLength(float length){this->length = length;}
void Growth::setScale(float scale){this->scale = scale;}
void Growth::setSegments(int segments){this->segments = segments;}
void Growth::setDepth(int depth){this->depth = depth;}
void Growth::setLeafLevel(int leaf_level){this->leaf_level = leaf_level;}
void Growth::setCrookedness(float crookedness){this->crookedness = crookedness;}
void Growth::setColormode(int color_mode){this->color_mode = color_mode;colorMesh(color_mode);}
