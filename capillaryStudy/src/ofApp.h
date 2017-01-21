#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxSyphon.h"
#include "ofxCapillary.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
        void animateCapillaries();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    ofEasyCam cam;
    ofLight pointLight;
    
    ofxPanel gui;
    ofParameterGroup capillary_group;
    ofParameterGroup light_group;
    
    ofParameter<float> capillary_density;
    ofParameter<float> capillary_length;
    ofParameter<int>   capillary_segments;
    ofParameter<int>   capillary_depth;
    ofParameter<int>   capillary_leaf_level;
    ofParameter<float> capillary_crookedness;
    
    ofParameter<ofFloatColor> light_color;
    ofParameter<ofVec3f>      light_position;
		
    ofxCapillary capillary;
    
    ofxSyphonServer syphon;
};
