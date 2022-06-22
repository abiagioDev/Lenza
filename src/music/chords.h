//
//  chords.h
//  Lenza
//
//  Created by Andrea Biagioni on 16/05/22.
//

#ifndef chords_h
#define chords_h

typedef enum {
    OFF,
    ON
} NOTE_STATUS;


typedef struct {
    int note_num;
    int note_vel;
    NOTE_STATUS status;
} NoteData;

static int maj[7] = {0,4,7,11,2,6,9};
//int min = [4,3,4];
//int sev = [4,3,3];

typedef enum {
    UNDEF,
    M_TRIAD,
    MIN_TRIAD,
    DIM_TRIAD,
    MAJ_7,
    DOM7,
    MIN7,
    SEMIDIM,
    DIM,
    SUS2,
    SUS4,
    AUG,
    MIN_7MAJ,
} CHORD_QUALITY;

class chord {
public:
    CHORD_QUALITY quality;
    int root;
};

#endif /* chords_h */
