#include "ofxCapillary.h"


//--------------------------------------------------------------
ofxCapillary::ofxCapillary(){
    this->tissue_color = ofColor(ofRandom(255),ofRandom(255),ofRandom(255));
}

//--------------------------------------------------------------
void ofxCapillary::setup(){
    ofxGrowth::setup();
    setColormode(3);
    
    this->level = 0;
    this->branch = 0;
    this->node = 1;
}

//--------------------------------------------------------------
void ofxCapillary::animateCapillary(){
    /*
        Animate a moving particle, either filling up, or just traveling along the growth pattern.
        To do this, I will want to update a current node, and use time to push that number along through each level.
     
        Right at the beginning, calculate full number of nodes
     */
    
    int t_driver = ofGetElapsedTimeMillis()/15;
    
    int t_num_levels = branches.size();

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
    driver = t_driver;
}
