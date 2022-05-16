#pragma once

#include "ofMain.h"
#include "ofxMidi.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM_OF_NOTES 1000

typedef enum
{
    OFF,
    ON
} NOTE_STATUS;

typedef struct
{
    int note_num;
    int note_vel;
    NOTE_STATUS status;
} NoteData;

class ofApp : public ofBaseApp,
public ofxMidiListener {
    
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
    
    void newMidiMessage(ofxMidiMessage& eventArgs);
    
    void printOnNotes();
    void printNoteName(int note);
    void sortNotes();
private:
    
    //Array that stores information for each note/circle being displayed
    NoteData noteData[MAX_NUM_OF_NOTES];
    
    //Variable for storing the apps background colour
    int backgroundColour;
    
    //Object that handles the MIDI input
    ofxMidiIn midiIn;
    
    //Flag that sets whether we're currently displaying the apps instructions
    bool showingInstructions;
    
    int control;
    
    
};
