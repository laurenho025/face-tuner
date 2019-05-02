#include "ofApp.h"
#include "constants.h"
#include <map>

//--------------------------------------------------------------
void ofApp::setup(){
    
    gui.setup();
    
    // Setup the note selector dropdown menu
    notesoptions.setName("Choose a note");
    notesdropdown = make_unique<ofxDropdown>(notesoptions);
    vector<string> notes = { "A", "B", "C", "D", "E", "F", "G" };
    notesdropdown->add(notes);
    gui.add(notesdropdown.get());
    
    // Set up the 3D face model (code derived from ofxFacialBlendShape example project)
    // Load the facial mesh data from the file
    ofMesh headmesh;
    ofxObjLoader::load("model/head-reference.obj", headmesh);
    face.setTempleteModel(headmesh);
    
    // Load the 7 possible facial emotions
    ofMesh model[constants::kNumberOfEmotions];
    ofxObjLoader::load("model/head-02-cry.obj", model[0]);
    ofxObjLoader::load("model/head-03-fury.obj", model[1]);
    ofxObjLoader::load("model/head-04-grin.obj", model[2]);
    ofxObjLoader::load("model/head-05-laugh.obj", model[3]);
    ofxObjLoader::load("model/head-06-rage.obj", model[4]);
    ofxObjLoader::load("model/head-07-sad.obj", model[5]);
    ofxObjLoader::load("model/head-08-smile.obj", model[6]);
    for (int i = 0; i < constants::kNumberOfEmotions; i++) {
        face.addModel(model[i]);
    }
    
    // Setup the emotion parameter
    emotion = new ofParameter<float> [constants::kNumberOfEmotions];
    
    // Setup the gui emotion viewer
    gui.add(emotion[0].set("cry", 0, 0, 1.0));
    gui.add(emotion[1].set("fury", 0, 0, 1.0));
    gui.add(emotion[2].set("grin", 0, 0, 1.0));
    gui.add(emotion[3].set("laugh", 0, 0, 1.0));
    gui.add(emotion[4].set("rage", 0, 0, 1.0));
    gui.add(emotion[5].set("sad", 0, 0, 1.0));
    gui.add(emotion[6].set("smile", 0, 0, 1.0));
    
    face.setEmotion(emotion);
    face.init();
    
    // Set up aubio pitch object
    pitch.setup();
    
    // Set up ofSoundStream to take input from default mic
    soundstream.printDeviceList();
    left.assign(constants::kBufferSize, 0.0);
    right.assign(constants::kBufferSize, 0.0);
    ofSoundStreamSettings settings;
    auto devices = soundstream.getMatchingDevices("default");
    if(!devices.empty()){
        settings.setInDevice(devices[0]);
    }
    settings.setInListener(this);
    settings.sampleRate = constants::kSampleRate;
    settings.numOutputChannels = constants::kNumberOfOutputChannels;
    settings.numInputChannels = constants::kNumberOfInputChannels;
    settings.bufferSize = constants::kBufferSize;
    
    soundstream.setup(settings);
}

//--------------------------------------------------------------
void ofApp::audioIn(ofSoundBuffer &input){
    pitch.audioIn(input.getBuffer().data(), constants::kBufferSize, constants::kNumberOfInputChannels);
}

void audioOut(){
}

//--------------------------------------------------------------
void ofApp::update(){
    face.update();

    // Reset the facial emotions to 0
    for (int i = 0; i < constants::kNumberOfEmotions; i++) {
        emotion[i].set(0);
    }

    // Calculate the closest pitch to tune to
    int closestpitch = tuner.FindClosestPitch(notesdropdown->getParameter().toString(), pitch.latestPitch);
    
    // If there is a pitch currently playing and the MIDI number is valid, calculate and set the approriate emotions
    if (closestpitch != 0) {
        map<string, float> emotionclassifications = tuner.ClassifyDifference();
        map<string, float> emotionsweighted = tuner.CalculateEmotionWeight(emotionclassifications);
        
        // Set the classified and weighted emotions calculated from the tuner emotionsweighted map
        map<string, float>::iterator it;
        for (it = emotionsweighted.begin(); it != emotionsweighted.end(); it++) {
            if (it->first == "cry") {
                emotion[0].set(it->second);
            } else if (it->first == "fury") {
                emotion[1].set(it->second);
            } else if (it->first == "grin") {
                emotion[2].set(it->second);
            } else if (it->first == "laugh") {
                emotion[3].set(it->second);
            } else if (it->first == "rage") {
                emotion[4].set(it->second);
            } else if (it->first == "sad") {
                emotion[5].set(it->second);
            } else if (it->first == "smile") {
                emotion[6].set(it->second);
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // Code to draw the face animation derived from the ofxFacialBlendShape example project
    ofBackgroundGradient(ofColor(64), ofColor(0));
    
    cam.begin();
    
    ofEnableDepthTest();
    ofEnableLighting();
    
    light.setPosition(cam.getPosition());
    light.enable();
    
    ofSetColor(150);
    face.draw();
    
    ofDisableDepthTest();
    ofDisableLighting();
    
    cam.end();
    
    // Draw the target note, measured MIDI note, and the difference
    ofSetColor(ofColor::white);
    
    string targetnote = "Target MIDI Note: " + ofToString(tuner.FindClosestPitch(notesdropdown->getParameter().toString(), pitch.latestPitch));
    ofDrawBitmapString(targetnote, 15, 200);
    
    string actualnote = "Measured MIDI Note: " + ofToString(pitch.latestPitch, constants::kNumberOfInputChannels);
    ofDrawBitmapString(actualnote, 15, 220);
    
    string difference = "Difference: " + ofToString(tuner.GetDifference());
    ofDrawBitmapString(difference, 15, 240);
        
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    // Code used from the ofxFacialBlendShape example project
    float length = 200;
    if (x > 0 && x < length) {
        cam.disableMouseInput();
    } else {
        cam.enableMouseInput();
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
