#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	ofSetupOpenGL(20,20,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OFw_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
