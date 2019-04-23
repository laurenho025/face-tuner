#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxDropdown.h"
#include "ofxObjLoader.h"
#include "ofxFacialBlendShape.h"
#include "ofxAudioAnalyzer.h"
#include "ofxAubio.h"

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
    
    // Audio analyzer
    ofxAudioAnalyzer audioanalyzer;
    float pitchfreq;
    float pitchconf;
    
    // Audio input
    ofSoundStream soundstream;
    vector<float> left;
    vector<float> right;
    
    // Accounting for room's ambient sound
    int updatecount;
    vector<int> ambientpitches;
    bool findingambientpitch;
    int ambientpitchfreq;
    
    // Aubio pitch detection
    ofxAubioPitch pitch;
    ofxFloatSlider midiPitch;

};
