#pragma once

#include "ofMain.h"

class Growth : public ofPath {

public:
    
    void setup();
    void update();
    void drawPaths();
    void drawPoints();
    void drawMeshes();
    void clearAll();
    
    void colorMesh(int coloring_type);
    void addMesh(ofPolyline poly, int level);
    
    void setupBranch();
    void generateBranch(ofVec3f origin, ofVec3f initial_vector, int level);
    
    float   density;
    float   length;
    float   scale;
    int     segments;
    int     depth;
    int     leaf_level;
    float   straightness;
    ofVec3f origin;

    float f_dim;
    
    vector< vector<ofMesh> > branches;
    vector<ofMesh> leaves;
};
