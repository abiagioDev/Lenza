#include "ofApp.h"
#include "chords.h"

void printArray(int *array,int dim);
void printChord(int root,CHORD_QUALITY quality);
void printChordQuality(CHORD_QUALITY quality);
void printNoteName(int note);

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
    onNotes =0;
}

void ofApp::printOnNotes(){
    
    //cout << endl << "CURRENT ON NOTES: "<<endl;
    for (int i = 0; i < MAX_NUM_OF_NOTES; i++)
    {
        if (noteData[i].status == ON)
        {
            printNoteName(noteData[i].note_num);
            //cout <<" at index "<< i <<endl;
        }
    }
}

const char *noteDiesis[5] = {"DO#","RE#","FA#","SOL#","LA#"};
const char *noteDiesisEN[5] = {"C#","D#","F#","G#","A#"};
const char *noteBemolle[5] = {"REb","MIb","SOLb","LAb","SIb"};
const char *noteBemolleEN[5] = {"Db","Eb","Gb","Ab","Bb"};


void printNoteName(int note){
    cout << note << " ";
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
    // cout << (note/12) -2;
}

void ofApp::majMin(){
    int relevantNotes[MAX_NUM_OF_NOTES];
    int relevants=0;
    bool found = false;
    int root = noteData[0].note_num %12;
    
    //    cout << endl<<"La root è: ";
    //    printNoteName(root);
    //    cout<<endl;
    //
    for(int i=0;i<onNotes;i++){
        int target = (noteData[i].note_num-root)%12 ;
        for(int j=0;j<relevants;j++){
            if(relevantNotes[j] == target){
                found = true;
                break;
            }
        }
        if(!found){
            relevantNotes[relevants++]= target;
        }
    }
    
    for(int i=1;i<relevants;i++){
        cout<<relevantNotes[i]<<" ";
    }
    
    int beccate= 0;
    // cout<<endl<<"Relevant Notes";
    
    //printArray(relevantNotes,relevants);
    // cout<<endl<<"Maj Notes";
    // printArray(maj, 7);
    
    
    bool hasThird = false;
    bool hasSeventh = false;
    bool isTriad = false;
    bool hasFourth = false;
    
    
    for(int j=0;j<relevants;j++){
        
        if(relevantNotes[j]==5){
            hasFourth = true; //potrebbe essere un rivolto
        }
        
        for(int i=0;i<7;i++){
            if(relevantNotes[j]==maj[i]){
                beccate++;
                switch(i){
                    case 1: //terza
                        hasThird = true;
                        break;
                    case 2: //quinta
                        
                        break;
                        
                    case 3: // settima
                        hasSeventh = true;
                        break;
                    case 4: // nona
                        break;
                        
                    case 5: //undicesima
                        
                        break;
                        
                    case 6: //tredicesima
                        
                        break;
                        
                }
                // cout<<"MATCH! "<<relevantNotes[j]<<"=="<<maj[i]<<endl;
                break;
            }
        }
        
    }
    
    CHORD_QUALITY detected = UNDEF;
    if(beccate==relevants){ //se abbiamo trovato tutte le note:
        if(hasThird&&hasSeventh){
            detected = MAJ_7;
        }
        if(hasThird&&relevants==3){
            detected= M_TRIAD;
        }
        
        
        cout<<endl<<"Found chord: ";
        printChord(root, detected);
    }
    
}


void printChord(int root,CHORD_QUALITY quality){
    printNoteName(root);
    printChordQuality(quality);
}

void printChordQuality(CHORD_QUALITY quality){
    switch(quality){
        case  M_TRIAD:
            cout<<" TRIADE MAGGIORE";
            break;
            
        case MIN_TRIAD:
            cout<<" TRIADE MINORE";
            break;
            
        case DIM_TRIAD:
            cout<<" TRIADE DIMINUITA";
            break;
            
        case  MAJ_7:
            cout<<" MAJOR 7";
            break;
            
        case    DOM7:
            cout<<" SETTIMA DOMINANTE";
            
            break;
            
        case   MIN7:
            cout<<" MINORE SETTIMA";
            break;
            
        case  SEMIDIM:
            cout<<" SEMIDIMINUITO";
            break;
            
        case DIM:
            cout<<" DIMINUITO";
            break;
            
            
        case SUS2:
            cout<<" SUS2";
            break;
            
        case SUS4:
            cout<<" SUS4";
            break;
            
        case AUG:
            cout<<" AUMENTATO";
            break;
            
        case MIN_7MAJ:
            cout<<" MINORE 7MA MAGGIORE";
            break;
            
            
        case  UNDEF:
        default:
            cout<<" UNDEF";
            break;
            
    }
    
}



void printArray(int *array,int dim){
    cout<<endl<<"[";
    for(int j=0;j<dim;j++){
        cout<<array[j]<<",";
    }
    cout<<"]";
}

int comp (const NoteData *primaNota, const NoteData *secondaNota) {
    return primaNota->status == OFF || primaNota->note_num > secondaNota->note_num ? 1 : -1;
}

void ofApp::sortNotes(){
    qsort(&noteData, sizeof(noteData) / sizeof(NoteData), sizeof(NoteData), (int (*) (const void *, const void *)) &comp);
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
    
    // printOnNotes();
    if(onNotes>0){
        sortNotes();
        majMin();
    }
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
