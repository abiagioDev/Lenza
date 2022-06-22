//
//  midiCore.hpp
//  Lenza
//
//  Created by Matteo Chiti on 22/06/22.
//

#ifndef midiCore_hpp
#define midiCore_hpp

#include <stdio.h>
#include "ofxMidi.h"
#include "chords.h"
#include "music/midilyzer.h"

#define MAX_NUM_OF_NOTES 1000

class midiCore : public ofxMidiListener {
public:
    void setup();
    void newMidiMessage(ofxMidiMessage& eventArgs);
    
    NoteData* getNoteData();
    int getOnNotes();

private:
    midiLyzer midi_analyzer;
    ofxMidiIn midiIn; // Object that handles the MIDI input
    NoteData noteData[MAX_NUM_OF_NOTES]; // Array that stores information for each note/circle being displayed
    NoteData noteOn[MAX_NUM_OF_NOTES];
    
    int onNotes; // Numero delle note accese
    int control;
};

#endif /* midiCore_hpp */
