#include "ofxCapillary.h"


//--------------------------------------------------------------
ofxCapillary::ofxCapillary(){
    this->tissue_color = ofColor(ofRandom(255),ofRandom(255),ofRandom(255));
}

//--------------------------------------------------------------
void ofxCapillary::setup(){
    ofxGrowth::setup();
    
    this->node = 1;
}

//--------------------------------------------------------------
void ofxCapillary::animateCapillary(){
    int t_driver = ofGetElapsedTimeMillis()/30;

    if(t_driver != driver){

        int t_num_nodes = branches[0].get()->getMesh().getVertices().size();
        
        if(this->node < t_num_nodes){
            branches[0].get()->getMesh().setColor(this->node - 1, ofColor(255,255,255,0));
            branches[0].get()->getMesh().setColor(this->node, ofColor(255,255,255,255));
            
            this->node++;
        }else{
            this->node = 1;
        }
    }
    
    driver = t_driver;
}

/*
 if(t_driver != driver){
 if(this->level < t_num_levels){
 int t_num_branches = branches[this->level].size();
 
 
 if(this->branch < t_num_branches){
 for(int i = 0; i < t_num_branches; i++){
 int t_num_nodes = branches[this->level][i].getVertices().size();
 
 if(this->node < t_num_nodes){
 //                        for(int j = 0; j < t_num_nodes; j++){
 
 ofColor color = branches[this->level][i].getColor(this->node);
 
 //                            branches[this->level][this->branch].setColor(this->node - 1, ofColor(255,255,255,0));
 branches[this->level][i].setColor(this->node, ofColor(0,0,0,255));
 
 this->node++;
 //                        }
 }else{
 this->node = 1;
 this->branch++;
 }
 }
 }else{
 this->branch = 0;
 this->level++;
 }
 }else{
 this->level = 0;
 
 //            ofxGrowth::clearAll();
 //            ofxGrowth::setup();
 
 colorMesh(3);
 }
 }
 */
