#include "ofApp.h"
#include "chords.h"

void printArray(int *array,int dim);
void printChord(int root,CHORD_QUALITY quality);
void printChordQuality(CHORD_QUALITY quality);
void printNoteName(int note);

//--------------------------------------------------------------
void ofApp::setup() {
    cout<<"Benvenuto da Lenza, fai come fossi a casa tua";
    
    ofSetVerticalSync(true);
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofSetFrameRate(60);
    
    midiCore.setup();
    
    grid = Grid();
    grid.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
    grid.updateDots(midiCore.getNoteData(),midiCore.getOnNotes());
}

//--------------------------------------------------------------
void ofApp::draw(){
    grid.display();
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
