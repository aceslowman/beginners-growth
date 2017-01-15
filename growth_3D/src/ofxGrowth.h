#pragma once

#include "ofMain.h"

class Growth : public ofMesh {

public:

    void setup();
    void update();
    void draw();
    
    float density;
    float length;
    int   segments;
    int   depth;
    float straightness;
    
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
