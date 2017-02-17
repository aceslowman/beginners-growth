#include "ofxGrowth.h"

//--------------------------------------------------------------
ofxGrowth::ofxGrowth(){
    float length = 10.0;
    float crookedness = 10.0;
    float density = 10.0;
}

//--------------------------------------------------------------
void ofxGrowth::setup(){
    root = new ofxGrowthNode(*this, NULL);
}

