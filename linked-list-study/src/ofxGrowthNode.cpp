#include "ofxGrowthNode.h"
#include "ofxGrowth.h"

ofxGrowthNode::ofxGrowthNode(ofxGrowth &t): tree(t) {
    distance_to_center = 0;
    level              = 0;
    growth_vector      = t.growth_vector;
    
    generateChild();
}

ofxGrowthNode::ofxGrowthNode(ofxGrowth &t, ofxGrowthNode* p): tree(t), parent(p) {
    distance_to_center = parent->distance_to_center + 1;
    level = parent->level;
    
    
    setupNode();
}

//--------------------------------------------------------------
void ofxGrowthNode::setupNode(){
    growth_vector = ofVec3f(
        ofClamp(parent->growth_vector.x + (ofRandomf() * tree.crookedness),-1.0,1.0),
        ofClamp(parent->growth_vector.y + (ofRandomf() * tree.crookedness),-1.0,1.0),
        ofClamp(parent->growth_vector.z + (ofRandomf() * tree.crookedness),-1.0,1.0)
    );
    
    float length = tree.length * ofRandomuf();
    
    //update location
    location = parent->location + (growth_vector * length);
    
    if(ofRandomuf() < tree.density && distance_to_center < 20){
        generateChild();
    }
}

//--------------------------------------------------------------
void ofxGrowthNode::generateChild(){
    shared_ptr<ofxGrowthNode> child(new ofxGrowthNode(tree,this));
    children.push_back(child);
}
