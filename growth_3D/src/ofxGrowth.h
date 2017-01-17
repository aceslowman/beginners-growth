#pragma once

#include "ofMain.h"

class Growth {

public:
    
    void setup();
    void update();
//    void drawPaths();
    void drawPoints();
    void drawMeshes();
    void drawLeaves();
    void drawDebug();
    void clearAll();
    
    void setDensity(float density);
    void setLength(float length);
    void setScale(float scale);
    void setSegments(int segments);
    void setDepth(int depth);
    void setStraightness(float straightness);
    void setColormode(int color_mode);
    
    void colorMesh(int coloring_type);
    void addMesh(ofPolyline poly, int level);
    
    void setupBranch();
    void generateBranch(ofVec3f origin, ofVec3f initial_vector, int level);
    
    float f_dim;
    
    /*
     branches[level][branch_id]
     */
    vector< vector<ofMesh> > branches;
    
    Growth();
    
private:
    
    float   density;
    float   length;
    float   scale;
    int     segments;
    int     depth;
    int     leaf_level;
    float   straightness;
    int     color_mode;
    ofVec3f origin;
};
