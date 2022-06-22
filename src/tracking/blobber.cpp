//
//  blobber.cpp
//  Lenza
//
//  Created by Matteo Chiti on 22/06/22.
//

#include "blobber.hpp"

#define WIDTH_RES 1280
#define HEIGHT_RES 720

void blobber::setup() {
    // start tracking
    bLearnBackground = false;

    vidGrabber.setVerbose(true);
    vidGrabber.listDevices();
    vidGrabber.setDeviceID(0);
    vidGrabber.initGrabber(WIDTH_RES,HEIGHT_RES);

    colorImg.allocate(WIDTH_RES,HEIGHT_RES);
    grayImage.allocate(WIDTH_RES,HEIGHT_RES);
    grayBg.allocate(WIDTH_RES,HEIGHT_RES);
    grayDiff.allocate(WIDTH_RES,HEIGHT_RES);
    // end tracking
}

void blobber::update() {
    
    vidGrabber.update();
    
    //do we have a new frame?
    if (vidGrabber.isFrameNew()) {
       colorImg.setFromPixels(vidGrabber.getPixels());
       grayImage = colorImg; // convert our color image to a grayscale image
       
        if ( bLearnBackground == true ) {
           grayBg = grayImage; // update the background image
           bLearnBackground = false;
       }
        
       grayDiff.absDiff(grayBg, grayImage);
       grayDiff.threshold(50);
       grayDiff.erode();
       grayDiff.erode();
       grayDiff.dilate();
       contourFinder.findContours(grayDiff, 5, (WIDTH_RES*HEIGHT_RES)/3, 1, false, true);
    }

}

void blobber::draw() {
    
    ofSetHexColor(0xffffff);
    colorImg.draw(0, 0, WIDTH_RES/3, HEIGHT_RES/3);
    grayDiff.draw(0, HEIGHT_RES/3, WIDTH_RES/3, HEIGHT_RES/3);
    ofDrawRectangle(WIDTH_RES/3, 0, WIDTH_RES/3, HEIGHT_RES/3);
    contourFinder.draw(WIDTH_RES/3, 0, WIDTH_RES/3, HEIGHT_RES/3);
    ofColor c(255, 255, 255);
    
    
    for ( int i = 0; i < contourFinder.nBlobs; i++ ) {
           
        // contourFinder.blobs.at(i).draw();
        ofPolyline line;
        
        line.addVertices(contourFinder.blobs.at(i).pts);
        // ofRectangle r = contourFinder.blobs.at(i).boundingRect;
        // r.x += WIDTH_RES/3; r.y += HEIGHT_RES/3 ;
        c.setHsb(i * 64, 255, 255);
        ofSetColor(c);
        // ofDrawRectangle(r);
        line.scale(.5,.5);
        ofPath path;
             
        for ( int i = 0; i < line.getVertices().size(); i++ ) {
            if ( i == 0 ) {
                path.newSubPath();
                path.moveTo( line.getVertices()[i] );
            } else {
                path.lineTo( line.getVertices()[i] );
            }
        }
             
        path.close();
        path.simplify();
        path.simplify();
        path.setColor(c);
        path.draw();

    }
}

void blobber::bgLearning() {
    bLearnBackground = true;
}
