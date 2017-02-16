#pragma once

#include "ofMain.h"

class ofxGrowth;

class ofxGrowthNode {
    
    ofxGrowth &tree;
    ofVec3f location;
    ofVec3f growth_vector;

    int level;
    int distance_to_center;
    
    ofxGrowthNode * parent;
    vector<shared_ptr<ofxGrowthNode>> children;
        
public:
    
    void setup();
    void generateChild();
    
    ofxGrowthNode(ofxGrowth &t, ofxGrowthNode* p);
};
