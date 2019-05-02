#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxDropdown.h"
#include "ofxObjLoader.h"
#include "ofxFacialBlendShape.h"
#include "ofxAubio.h"
#include "tuner.hpp"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void mouseDragged(int x, int y, int button);
        void audioIn(ofSoundBuffer &input);
    
    // GUI Panel
    ofxPanel gui;
    
    // Dropdown note selector
    unique_ptr<ofxDropdown> notesdropdown;
    ofParameter<string> notesoptions;
    
    // 3D face animation
    ofEasyCam cam;
    ofLight light;
    ofParameter<float> *emotion;
    ofxFacialBlendShape face;
    
    // Audio input
    ofSoundStream soundstream;
    vector<float> left;
    vector<float> right;
    
    // Aubio pitch detection
    ofxAubioPitch pitch;
    
    // Tuner object
    Tuner tuner;
};
