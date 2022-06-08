//
//  Grid.cpp
//  Lenza
//
//  Created by Matteo Chiti on 26/05/22.
//

#include "Grid.h"

RGB HSVToRGB(HSV hsv) {
   double r = 0, g = 0, b = 0;

   if (hsv.S == 0)
   {
       r = hsv.V;
       g = hsv.V;
       b = hsv.V;
   }
   else
   {
       int i;
       double f, p, q, t;

       if (hsv.H == 360)
           hsv.H = 0;
       else
           hsv.H = hsv.H / 60;

       i = (int)trunc(hsv.H);
       f = hsv.H - i;

       p = hsv.V * (1.0 - hsv.S);
       q = hsv.V * (1.0 - (hsv.S * f));
       t = hsv.V * (1.0 - (hsv.S * (1.0 - f)));

       switch (i)
       {
       case 0:
           r = hsv.V;
           g = t;
           b = p;
           break;

       case 1:
           r = q;
           g = hsv.V;
           b = p;
           break;

       case 2:
           r = p;
           g = hsv.V;
           b = t;
           break;

       case 3:
           r = p;
           g = q;
           b = hsv.V;
           break;

       case 4:
           r = t;
           g = p;
           b = hsv.V;
           break;

       default:
           r = hsv.V;
           g = p;
           b = q;
           break;
       }

   }

   RGB rgb;
   rgb.R = r * 255;
   rgb.G = g * 255;
   rgb.B = b * 255;

   return rgb;
}





Grid::Grid()
{
    
}
Grid::~Grid()
{
    
}

void Grid::setup()
{
    int xOffset = 800 / COL_NUM;
    int yOffset = 800 / ROW_NUM;
    
    for(int row=0;row<ROW_NUM;row++){
        for (int col=0;col<COL_NUM;col++){
            points[row][col] = ofVec2f(xOffset/2+col*xOffset,yOffset/2+row*yOffset);
       //     cout<<row<<":"<<col<<" ->" << points[row][col]<<endl;
            
            sizes[row][col]=0;
            pos_variation[row][col]=ofVec2f(0,0);
        }
    }
}

void Grid::update()
{
    
}
void Grid::updateDots(NoteData noteData[],int numberOfNotes){
    for(int i=0;i<numberOfNotes;i++){
        int row= (noteData[i].note_num-36)/12;
        int col= (noteData[i].note_num-36)%12;
        
        
        HSV hsv_value;
        hsv_value.H = 198 ;
        cout<<"Printing value:"<< hsv_value.H <<endl;
        hsv_value.S = 70;
        hsv_value.V =  85;
        
        ofColor color;
        color.setHsb(((float)(noteData[i].note_num-36))/60*255, 70, 85);
        
        colors[row][col] = color;
        
        cout<<endl<<"VEL"<<(float)noteData[i].note_vel/127;
        
        sizes[row][col] = ((float)noteData[i].note_vel/127)*50 + ((int)ofRandom(1,30)*(float)noteData[i].note_vel/127);
       
    }
    
    for(int row=0;row<ROW_NUM;row++){
        for (int col=0;col<COL_NUM;col++){
            if( sizes[row][col]>0){
                sizes[row][col]--;
            }
        }
    }
    magnetone(noteData,numberOfNotes);
    
}

void Grid::magnetone(NoteData noteData[],int numberOfNotes){
    
    for(int i=0;i<numberOfNotes;i++){
        int row= (noteData[i].note_num-36)/12;
        int col= (noteData[i].note_num-36)%12;
        
        float intensity =2+8*(float)noteData[i].note_vel/127;
        
        if(row>0){
            pos_variation[row-1][col].y+=intensity;
        }
        if(row<ROW_NUM-1){
            pos_variation[row+1][col].y-=intensity;
        }
        if(col>0){
            pos_variation[row][col-1].x+=intensity;
        }
        if(col<COL_NUM-1){
            pos_variation[row][col+1].x-=intensity;
        }
    }
}

void Grid::drawGrid(){
    ofVec2f p1,p2,p3,p4,pn,pk;

    
    for(int row=0;row<ROW_NUM;row++){
        for (int col=0;col<COL_NUM;col++){
            if(col<COL_NUM-1){

            ofSetColor(0);
            ofNoFill();
            ofSetLineWidth(2);
            
             p1 = ofVec2f(  points[row][col].x +          pos_variation[row][col].x,points[row][col].y + pos_variation[row][col].y);
            
              p4 = ofVec2f(  points[row][col+1].x +          pos_variation[row][col+1].x,points[row][col+1].y + pos_variation[row][col+1].y);
              
              pk = ofVec2f(  p4.x ,p1.y);
              pn =  ofVec2f(  p1.x ,p4.y);

              p2 = p1.getInterpolated( pk, 0.5 );
               p3 =  p4.getInterpolated( pn, 0.5 );
           
            ofBeginShape();
            ofVertex(p1);
            ofBezierVertex(p2, p3,p4);
            ofEndShape();
            }
            if(row<ROW_NUM-1){
                p1 = ofVec2f(  points[row][col].x +          pos_variation[row][col].x,points[row][col].y + pos_variation[row][col].y);
               
            p4 = ofVec2f(  points[row+1][col].x +          pos_variation[row+1][col].x,points[row+1][col].y + pos_variation[row+1][col].y);
            
            
          
           pk = ofVec2f(  p1.x ,p4.y);
              pn =  ofVec2f(  p4.x ,p1.y);

              p2 = p1.getInterpolated( pk, 0.5 );
              p3 =  p4.getInterpolated( pn, 0.5 );
            
            ofBeginShape();
            ofVertex(p1);
            ofBezierVertex(p2, p3,p4);
            ofEndShape();
            }
            const float elasticity = 1.8;
         
            if(pos_variation[row][col].x>0){
                pos_variation[row][col].x/=elasticity;
                
            }
            if(pos_variation[row][col].y>0){
                pos_variation[row][col].y/=elasticity;
                
            }
            if(pos_variation[row][col].x<0){
                pos_variation[row][col].x/=elasticity;
                
            }
            if(pos_variation[row][col].y<0){
                pos_variation[row][col].y/=elasticity;
                
            }
        }
    }
    
}
void Grid::display()
{
    
    
    for(int row=0;row<ROW_NUM;row++){
        for (int col=0;col<COL_NUM;col++){
            
            ofSetColor(colors[row][col]);
            ofFill();
            ofDrawCircle(points[row][col],sizes[row][col]);
            
        }
    }
    
    drawGrid();
    
    
    
}

