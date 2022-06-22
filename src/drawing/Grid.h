//
//  Grid.hpp
//  Lenza
//
//  Created by Matteo Chiti on 26/05/22.
//

#ifndef Grid_h
#define Grid_h

#include <stdio.h>
#include "../ofMain.h"
#include "../music/chords.h"
#include "./colors.h"

using namespace std;

#define COL_NUM 12
#define ROW_NUM 5

class Grid {

public:
    Grid();
    ~Grid();
    void setup();
    void update();
    void display();
    void updateDots(NoteData noteData[],int numberOfNotes);
    void drawGrid();
    void magnetone(NoteData noteData[],int numberOfNotes);
private:
    ofVec2f points[ROW_NUM][COL_NUM];
    
    int sizes[ROW_NUM][COL_NUM];
    ofVec2f pos_variation[ROW_NUM][COL_NUM];
    ofColor colors[ROW_NUM][COL_NUM];
    
};

#endif /* Grid_hpp */
