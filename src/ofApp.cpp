#include "ofApp.h"
#include "chords.h"

#define WIDTH_RES 1280
#define HEIGHT_RES 720

void printArray(int *array,int dim);
void printChord(int root,CHORD_QUALITY quality);
void printChordQuality(CHORD_QUALITY quality);
void printNoteName(int note);

//--------------------------------------------------------------
void ofApp::setup(){
    cout<<"Benvenuto da Lenza, fai come fossi a casa tua";
    ofSetVerticalSync(true);
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofSetFrameRate(60);
    
   // midiIn.listInPorts();
    midiIn.openPort(1);
    midiIn.addListener(this);
    
    for (int i = 0; i < MAX_NUM_OF_NOTES; i++)
    {
        noteData[i].status = OFF;
        noteData[i].note_num = 128;
    }
    onNotes =0;
    
    
    grid = Grid();
    grid.setup();
    
    
    bLearnBackground = false;
    
      vidGrabber.setVerbose(true);
    vidGrabber.listDevices();
    vidGrabber.setDeviceID(1);
      vidGrabber.initGrabber(WIDTH_RES,HEIGHT_RES);

      colorImg.allocate(WIDTH_RES,HEIGHT_RES);
      grayImage.allocate(WIDTH_RES,HEIGHT_RES);
      grayBg.allocate(WIDTH_RES,HEIGHT_RES);
      grayDiff.allocate(WIDTH_RES,HEIGHT_RES);
}
 

void ofApp::newMidiMessage (ofxMidiMessage& msg)
{
    //if we have received a note-on message
    if (msg.status == MIDI_NOTE_ON && msg.velocity != 0)
    {
        for (int i = 0; i < MAX_NUM_OF_NOTES; i++)
        {
            if (noteData[i].status == OFF)
            {
                noteData[i].status = ON;
                noteData[i].note_num = msg.pitch;
                noteData[i].note_vel = msg.velocity;
                
                onNotes++;
                
                //                cout << "Added ON NOTE :" ;
                //                cout <<"Velocity: "<<msg.velocity<<endl;
                //                cout <<"Pitch: "<<msg.pitch<<endl;
                //
                break;
            }
        }
    } else if(msg.status == MIDI_NOTE_OFF){
        
        for (int i = 0; i < MAX_NUM_OF_NOTES; i++)
        {
            if (noteData[i].note_num == msg.pitch)
            {
                noteData[i].status = OFF;
                
                onNotes--;
                
                //                cout << "TURNED OFF A NOTE :" ;
                //                cout <<"Pitch: "<<msg.pitch<<endl;
                break;
                
            }
            
        }
        
    } else if (msg.status == MIDI_CONTROL_CHANGE){
        
        cout<<"Control: "<<msg.control<<endl;
        cout<<"Value: "<<msg.value<<endl;
        
        if(msg.control== 1){
            control = msg.value;
        }
    }
    if(onNotes>0)
    midi_analyzer.analyze(noteData, onNotes);
}

//--------------------------------------------------------------
void ofApp::update(){
    grid.updateDots(noteData,onNotes);
    
    //Start tutorial Recognition
    vidGrabber.update();
       //do we have a new frame?
       if (vidGrabber.isFrameNew()){
           colorImg.setFromPixels(vidGrabber.getPixels());
           grayImage = colorImg; // convert our color image to a grayscale image
           if (bLearnBackground == true) {
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
    //end tut recognition
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    grid.display();
    
    
    ofSetHexColor(0xffffff);
       colorImg.draw(0, 0, WIDTH_RES/3, HEIGHT_RES/3);
       grayDiff.draw(0, HEIGHT_RES/3, WIDTH_RES/3, HEIGHT_RES/3);
       ofDrawRectangle(WIDTH_RES/3, 0, WIDTH_RES/3, HEIGHT_RES/3);
       contourFinder.draw(WIDTH_RES/3, 0, WIDTH_RES/3, HEIGHT_RES/3);
       ofColor c(255, 255, 255);
    
    
       for(int i = 0; i < contourFinder.nBlobs; i++) {
           
           //contourFinder.blobs.at(i).draw();
           ofPolyline line;
        
           line.addVertices(contourFinder.blobs.at(i).pts);
           
//
//           ofRectangle r = contourFinder.blobs.at(i).boundingRect;
//           r.x += WIDTH_RES/3; r.y += HEIGHT_RES/3 ;
           c.setHsb(i * 64, 255, 255);
              ofSetColor(c);
//           ofDrawRectangle(r);
           line.scale(.5,.5);
          
           ofPath path;
             
               for( int i = 0; i < line.getVertices().size(); i++) {
                   if(i == 0) {
                       path.newSubPath();
                       path.moveTo(line.getVertices()[i] );
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

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    bLearnBackground = true;

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}
