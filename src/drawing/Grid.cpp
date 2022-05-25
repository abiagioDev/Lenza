//
//  Grid.cpp
//  Lenza
//
//  Created by Matteo Chiti on 26/05/22.
//

#include "Grid.h"


Grid::Grid()
{
    
}
Grid::~Grid()
{
    
}

void Grid::setup()
{
    int xOffset = 800 / GRID_SIZE;
    int yOffset = 800 / GRID_SIZE;
    
    for(int row=0;row<GRID_SIZE;row++){
        for (int col=0;col<GRID_SIZE;col++){
            points[row][col] = ofVec2f(col*xOffset,row*yOffset);
            cout<<row<<":"<<col<<" ->" << points[row][col]<<endl;
        }
    }
}

void Grid::update()
{
    
}
void Grid::display()
{
    
    
    for(int row=0;row<GRID_SIZE-1;row++){
        for (int col=0;col<GRID_SIZE-1;col++){
            
            ofSetColor(255, 0, 0);
            ofFill();
            ofDrawCircle(points[row][col], 4);
            
            ofSetColor(0);
            ofNoFill();
            ofSetLineWidth(2);
            int p2x =points[row][col].x + (points[row][col+1].x - points[row][col].x)/3;
            int p3x = points[row][col].x + 2*(points[row][col+1].x - points[row][col].x)/3;
            ofVec2f p2 = ofVec2f(p2x,points[row][col].y);
            ofVec2f p3 = ofVec2f(p3x,points[row][col].y);
            
            ofBeginShape();
            ofVertex(points[row][col] );
            ofBezierVertex(p2, p3, points[row][col+1]);
            ofEndShape();
            
            int p2y =points[row][col].y + (points[row+1][col].y - points[row][col].y)/3;
            int p3y = points[row][col].y + 2*(points[row+1][col].y - points[row][col].y)/3;
            p2 = ofVec2f(points[row][col].x,p2y);
            p3 = ofVec2f(points[row][col].x,p3y);
            
            ofBeginShape();
            ofVertex(points[row][col] );
            ofBezierVertex(p2, p3, points[row+1][col]);
            ofEndShape();
            
        }
    }
}

