//
//  midilyzer.hpp
//  Lenza
//
//  Created by Andrea Biagioni on 25/05/22.
//

#ifndef midilyzer_hpp
#define midilyzer_hpp

#include <stdio.h>
#include <stdlib.h>
#include "chords.h"
#include <iostream>
using namespace std;

class midiLyzer {
public:
    void printChord(chord chord);
    void sortNotes(NoteData noteData[],int numberOfNotes);
    void analyze(NoteData noteData[],int numberOfNotes);
    void printNoteName(int note);
    void printChordQuality(CHORD_QUALITY quality);
};

#endif /* midilyzer_hpp */
