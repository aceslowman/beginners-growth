#pragma once

#include "ofMain.h"
#include "ofxGrowth.h"

class ofxCapillary : public ofxGrowth{
    
public:
    ofColor tissue_color;
    ofColor light_color;

    void animateCapillary();
    
    ofxCapillary();
};
