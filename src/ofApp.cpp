#include "ofApp.h"
#include "chords.h"

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
    
}
 
 

void printArray(int *array,int dim){
    cout<<endl<<"[";
    for(int j=0;j<dim;j++){
        cout<<array[j]<<",";
    }
    cout<<"]";
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
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    grid.display();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
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
