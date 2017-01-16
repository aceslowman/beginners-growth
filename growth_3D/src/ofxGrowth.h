#pragma once

#include "ofMain.h"

class Growth : public ofPath {

public:
    
    void setup();
    void update();
    void drawPath();
    void clearAll();
    
    void setupBranch();
    void generateBranch(ofVec3f origin, ofVec3f initial_vector, int level);
    
    float   density;
    float   length;
    int     segments;
    int     depth;
    int     leaf_level;
    float   straightness;
    ofVec3f origin;

    float f_dim;
    
    ofMesh branch;
    vector<ofMesh> leaves;
};
