#pragma once

#include "ofMain.h"

class Growth : public ofPath {

public:
    
    void setupBranches(ofVec3f origin, ofVec3f initial_vector, float length, int segments);
    void generateBranch(ofVec3f origin, ofVec3f initial_vector, float length, int segments, int level);
    void generateLeaf(ofVec3f origin, ofVec3f initial_vector, float length, int segments, int level);
    void drawGrowth();
    void drawDebug();
    
    float smoothness, length, density;
    int   levels, segments;
    
    Growth();
};
