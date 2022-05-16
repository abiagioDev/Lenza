#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofSetFrameRate(60);
    
    //midiIn.listInPorts();
    midiIn.openPort(1);
    midiIn.addListener(this);
    
    
    for (int i = 0; i < MAX_NUM_OF_NOTES; i++)
    {
        noteData[i].status = OFF;
        noteData[i].note_num = 128;
    }
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
                
                cout << "Added ON NOTE :" ;
                cout <<"Velocity: "<<msg.velocity<<endl;
                cout <<"Pitch: "<<msg.pitch<<endl;
                break;
            }
        }
    } else if(msg.status == MIDI_NOTE_OFF){
        
        for (int i = 0; i < MAX_NUM_OF_NOTES; i++)
        {
            if (noteData[i].note_num == msg.pitch)
            {
                noteData[i].status = OFF;
                
                cout << "TURNED OFF A NOTE :" ;
                cout <<"Pitch: "<<msg.pitch<<endl;
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
    
    printOnNotes();
    
}

void ofApp::printOnNotes(){
    sortNotes();
    
    cout << endl << "CURRENT ON NOTES: "<<endl;
    for (int i = 0; i < MAX_NUM_OF_NOTES; i++)
    {
        if (noteData[i].status == ON)
        {
            printNoteName(noteData[i].note_num);
            cout <<" at index "<< i <<endl;
        }
    }
}

const char *noteDiesis[5] = {"DO#","RE#","FA#","SOL#","LA#"};
const char *noteDiesisEN[5] = {"C#","D#","F#","G#","A#"};
const char *noteBemolle[5] = {"REb","MIb","SOLb","LAb","SIb"};
const char *noteBemolleEN[5] = {"Db","Eb","Gb","Ab","Bb"};


void ofApp::printNoteName(int note){
    switch(note%12){
        case 0:
            cout << "DO" ;
            break;
        case 1:
            
            cout << "DO#";
            break;
        case 2:
            cout << "RE";
            break;
        case 3:
            cout << "RE#";
            break;
        case 4:
            cout << "MI";
            break;
        case 5:
            cout << "FA";
            break;
        case 6:
            cout << "FA#";
            break;
        case 7:
            cout << "SOL";
            break;
        case 8:
            cout << "SOL#";
            break;
        case 9:
            cout << "LA";
            break;
        case 10:
            cout << "LA#";
            break;
        case 11:
            cout << "SI";
            break;
    }
    cout << (note/12) -2;
}

int comp (const NoteData *primaNota, const NoteData *secondaNota) {
    return primaNota->status == OFF || primaNota->note_num > secondaNota->note_num ? 1 : -1;
}

void ofApp::sortNotes(){
    qsort(&noteData, sizeof(noteData) / sizeof(NoteData), sizeof(NoteData), (int (*) (const void *, const void *)) &comp);
}


//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
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
