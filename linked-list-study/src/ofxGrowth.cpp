#include "ofxGrowth.h"

//--------------------------------------------------------------
ofxGrowth::ofxGrowth(){
    length = 10.0;
    crookedness = 10.0;
    density = 10.0;
    
    root = new ofxGrowthNode(*this);
    root->growth_vector = ofVec3f(0,1,0);
}

//--------------------------------------------------------------
void ofxGrowth::setup(){
    
}

