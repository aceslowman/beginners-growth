#pragma once

#include "ofMain.h"
#include "ofxGrowthNode.h"

class ofxGrowth {
    
    ofxGrowthNode * root;
    
public:
    
    void setup();
    
    ofxGrowth();
    
private:
    
    ofVec3f growth_vector;
};
