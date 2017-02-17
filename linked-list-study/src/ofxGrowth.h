#pragma once

#include "ofMain.h"
#include "ofxGrowthNode.h"

class ofxGrowth {
    
public:
    ofxGrowthNode * root;
    void setup();

    float length;
    float crookedness;
    float density;
    ofVec3f growth_vector;
    
    ofxGrowth();
//    ~ofxGrowth();
};
