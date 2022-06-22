//
//  blobber.hpp
//  Lenza
//
//  Created by Matteo Chiti on 22/06/22.
//

#ifndef blobber_hpp
#define blobber_hpp

#include <stdio.h>
#include "ofxOpenCv.h"

class blobber {

public:
    
    void setup();
    void update();
    void draw();
    void bgLearning();
    
    bool bLearnBackground;
         ofVideoGrabber vidGrabber;
         ofxCvColorImage colorImg;
         ofxCvGrayscaleImage grayImage, grayBg, grayDiff;
         ofxCvContourFinder contourFinder;
};


#endif /* blobber_hpp */
