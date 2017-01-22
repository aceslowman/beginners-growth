#pragma once

#include "ofMain.h"
#include "ofxGrowth.h"

class ofxCapillary : public ofxGrowth{
    
public:
    ofColor tissue_color;
    ofColor light_color;

    void animateCapillary();
    void drawAnimatedCapillary();
    
    ofMaterial material;
    
    ofxCapillary();
    
    void setup();
    
private:
    
    int driver;
    
    int level;
    int branch;
    int node;
};
