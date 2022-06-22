#pragma once

#include "ofMain.h"
#include "ofxMidi.h"
#include <stdio.h>
#include <stdlib.h>
#include "chords.h"
#include "music/midilyzer.h"
#include "music/midiCore.hpp"
#include "drawing/Grid.h"
#include "ofxOpenCv.h"
#include "tracking/blobber.hpp"

class ofApp : public ofBaseApp {
    
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
    
private:
    
    midiLyzer midi_analyzer;
    
    //Variable for storing the apps background colour
    int backgroundColour;
    
    //Flag that sets whether we're currently displaying the apps instructions
    bool showingInstructions;
    
    int control;
    
    midiCore midiCore;
    Grid grid;
    ofShader shader;
    blobber blobber;
};
