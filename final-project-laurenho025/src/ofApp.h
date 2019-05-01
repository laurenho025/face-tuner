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
    
        void audioIn(ofSoundBuffer &input);
        void audioOut();
    
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
