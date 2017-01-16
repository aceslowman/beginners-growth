#pragma once

#include "ofMain.h"

class Growth : public ofMesh {

public:
    
    void setup();
    void update();
    void draw();
    
    void generateBranch(ofVec3f origin, ofVec3f initial_vector, int level);
    
    float density;
    float length;
    int   segments;
    int   depth;
    int   leaf_level;
    float straightness;

    float f_dim; //diminishment factor, size of growth in subsequent levels
    
    ofMesh branch;
    vector<ofMesh> leaves;
    
    //void setupBranches(ofVec3f origin, ofVec3f initial_vector, float length, int segments);
    //void generateBranch(ofVec3f origin, ofVec3f initial_vector, float length, int segments, int level);
//    void generateLeaf(ofVec3f origin, ofVec3f initial_vector, float length, int segments, int level);
//    void drawGrowth();
//    void drawDebug();
//    void clearAll();
    
//    float smoothness, length, density;
//    int   levels, segments;
    
//    bool b_leaf, b_drawLeaves;
    
//    vector<ofMesh> leaves;
};
