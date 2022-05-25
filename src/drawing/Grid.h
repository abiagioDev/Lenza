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

using namespace std;

#define GRID_SIZE 30

class Grid {
public:
    Grid();
    ~Grid();
    void setup();
    void update();
    void display();
    
private:
    ofVec2f points[GRID_SIZE][GRID_SIZE];
};

#endif /* Grid_hpp */
