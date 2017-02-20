#include "ofxGrowth.h"

//--------------------------------------------------------------
ofxGrowth::ofxGrowth(){
    length      = 30.0;
    crookedness = 1.0;
    density     = 0.5;
    depth       = 3;
    
//    meshes.resize(depth);
    
    root = new ofxGrowthNode(*this);
    root->growth_vector = ofVec3f(0,1,0);
    root->location = ofVec3f(0,0,0);
    
    num_nodes = 0;
    
    setupMesh();
}

//--------------------------------------------------------------
void ofxGrowth::setupMesh(){
    int index = 0;

    ofMesh temp_mesh;
    temp_mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
    temp_mesh.setupIndicesAuto();
    temp_mesh.addVertex(root->location);
    temp_mesh.addColor(ofColor(0));
    
    //I have to be assured that temp_mesh is inserted properly into shared_ptr, and THEN meshes
    shared_ptr<ofMesh> shared_mesh(&temp_mesh);
    meshes.push_back(shared_mesh);
    
    checkChildren(root, &temp_mesh);
}

//--------------------------------------------------------------
void ofxGrowth::checkChildren(ofxGrowthNode * temp_node, ofMesh * temp_mesh){
    if(!temp_node->children.empty()){
        for(int i = 0; i < temp_node->children.size(); i++){//because even when it is 0, I still grab the child?
            if(i > 0){
        
                add a new mesh (we have branched off)
                push the new mesh pointer into the meshes vector
                shared_ptr<ofMesh> new_mesh(new ofMesh);
                
                new_mesh->setMode(OF_PRIMITIVE_LINE_STRIP);
                new_mesh->addVertex(temp_node->location);
                new_mesh->addColor(ofFloatColor(0,0,0));
                
                meshes.push_back(new_mesh);
            }else{
        
                temp_mesh->addVertex(temp_node->location);
                temp_mesh->addColor(ofFloatColor(0,0,0));
            }

            num_nodes++;
            
            ofxGrowthNode * temp_child = temp_node->children[0].get();
            
            checkChildren(temp_child, temp_mesh);//check all children of the child
        }

    }
    
}

//--------------------------------------------------------------
void ofxGrowth::drawMesh(){
//    for(auto & mesh : meshes){
    for(int i = 0; i < meshes.size(); i++){
        meshes[i].get()->draw();
    }
}
