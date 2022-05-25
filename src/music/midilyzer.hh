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
//const [[]]


class midiLyzer {
public:
    void printChord(chord chord);
    void sortNotes();
    void analyze();
    void printNoteName(int note);
    void printChordQuality(CHORD_QUALITY quality);
};

#endif /* midilyzer_hpp */
