#pragma once

#include "ofMain.h"
#include "ofxGrowthNode.h"

class ofxGrowth {
    
    ofxGrowthNode * root;
    
public:
    
    void setup();
    
    ofVec3f growth_vector;
    ofVec3f initial_growth;
    
    float length;
    float crookedness;
    float density;
    
    ofxGrowth();
};
