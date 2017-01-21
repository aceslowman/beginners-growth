#include "ofxCapillary.h"


//--------------------------------------------------------------
ofxCapillary::ofxCapillary(){
    this->tissue_color = ofColor(ofRandom(255),ofRandom(255),ofRandom(255));
}

//--------------------------------------------------------------
void ofxCapillary::animateCapillary(){
    /*
        Animate a moving particle, either filling up, or just traveling along the growth pattern.
        To do this, I will want to update a current node, and use time to push that number along through each level.
     
        Right at the beginning, calculate full number of nodes
     */
    
    int t_driver = ofGetElapsedTimeMillis();
    
    ofWrap(t_driver,0,getNodeSize());
    ofLog(OF_LOG_NOTICE,ofToString(t_driver));
    
    
//    for(int current_level = 0; current_level < branches.size(); current_level++){
//        for(int current_branch = 0; current_branch < branches[current_level].size(); current_branch++){
//            for(int current_node = 0; branches[current_level][current_branch].getVertices().size(); current_node++){
//                branches[current_level][current_branch].setColorForIndices(0,current_node,ofColor(90,0))
//                branches[current_level][current_branch].setColor(current_node,ofColor(90,0,255));
//            }
//        }
//    }
}
