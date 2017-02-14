#pragma once

#include "ofMain.h"
class ofxGrowth;

class ofxGrowthNode {
    
    ofxGrowth &tree;
    ofVec3f location;
    ofVec3f growth_vector;
    int level;
    
    ofxGrowthNode * parent;
    vector<shared_ptr<ofxGrowthNode>> children;
    
    ofxGrowthNode();
    
public:
    
    void generateChildren();
    
private:

};
