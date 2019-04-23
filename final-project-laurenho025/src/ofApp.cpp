#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    gui.setup();
    
    // Sets note selector dropdown
    notesoptions.setName("Choose a note");
    notesdropdown = make_unique<ofxDropdown>(notesoptions);
    vector<string> notes = { "A", "B", "C", "D", "E", "F", "G" };
    notesdropdown->add(notes);
    gui.add(notesdropdown.get());
    
    // Set up 3d face animation
    // Set the mesh data
    ofMesh headmesh;
    ofxObjLoader::load("model/head-reference.obj", headmesh);
    face.setTempleteModel(headmesh);
    
    // Set the face's emotions
    ofMesh model[9];
    ofxObjLoader::load("model/head-01-anger.obj", model[0]);
    ofxObjLoader::load("model/head-02-cry.obj", model[1]);
    ofxObjLoader::load("model/head-03-fury.obj", model[2]);
    ofxObjLoader::load("model/head-04-grin.obj", model[3]);
    ofxObjLoader::load("model/head-05-laugh.obj", model[4]);
    ofxObjLoader::load("model/head-06-rage.obj", model[5]);
    ofxObjLoader::load("model/head-07-sad.obj", model[6]);
    ofxObjLoader::load("model/head-08-smile.obj", model[7]);
    ofxObjLoader::load("model/head-09-surprise.obj", model[8]);
    for (int i=0; i<9; i++) {
        face.addModel(model[i]);
    }
    
    // Set the emotion parameter
    emotion = new ofParameter<float> [9];
    
    // Set up the gui emotion viewer
    gui.add(emotion[0].set("anger", 0, 0, 1.0));
    gui.add(emotion[1].set("cry", 0, 0, 1.0));
    gui.add(emotion[2].set("fury", 0, 0, 1.0));
    gui.add(emotion[3].set("grin", 0, 0, 1.0));
    gui.add(emotion[4].set("laugh", 0, 0, 1.0));
    gui.add(emotion[5].set("rage", 0, 0, 1.0));
    gui.add(emotion[6].set("sad", 0, 0, 1.0));
    gui.add(emotion[7].set("smile", 0, 0, 1.0));
    gui.add(emotion[8].set("surprise", 0, 0, 1.0));
    
    face.setEmotion(emotion);
    face.init();
    
    // Set up audio analyzer
    audioanalyzer.setup(44100, 512, 2);
    // Set up ofSoundStream to take input from default mic
    soundstream.printDeviceList();
    left.assign(256, 0.0);
    right.assign(256, 0.0);
    ofSoundStreamSettings settings;
    auto devices = soundstream.getMatchingDevices("default");
    if(!devices.empty()){
        settings.setInDevice(devices[0]);
    }
    settings.setInListener(this);
    settings.sampleRate = 44100;
    settings.numOutputChannels = 0;
    settings.numInputChannels = 2;
    settings.bufferSize = 256;
    
    soundstream.setup(settings);
}

//--------------------------------------------------------------
void ofApp::audioIn(ofSoundBuffer &input){
    audioanalyzer.analyze(input);
}

void audioOut(){
}

//--------------------------------------------------------------
void ofApp::update(){
    face.update();
    
    // Get values from audioAnalyzer
    pitchfreq = audioanalyzer.getValue(PITCH_FREQ, 0);
    pitchconf = audioanalyzer.getValue(PITCH_CONFIDENCE, 0);
    
//    if (notesdropdown->getParameter().toString() != "A") {
//        emotion[4].set(1);
//    }
//    
//    if (notesdropdown->getParameter().toString() == "A") {
//        emotion[4].set(0);
//        emotion[2].set(1);
//    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // Code used from the ofxFacialBlendShape example project
    // Draw the face animation
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
    
    // Draw the pitch frequency and confidence values
    ofSetColor(ofColor::white);
    
    string strpitchfreqvalue = "Pitch Frequency: " + ofToString(pitchfreq, 2) + " hz.";
    ofDrawBitmapString(strpitchfreqvalue, 15, 240);
    
    string strpitchconfvalue = "Pitch Confidence: " + ofToString(pitchconf, 2);
    ofDrawBitmapString(strpitchconfvalue, 15, 260);

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
