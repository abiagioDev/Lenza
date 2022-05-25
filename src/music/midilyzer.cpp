//
//  midilyzer.cpp
//  Lenza
//
//  Created by Andrea Biagioni on 25/05/22.
//

#include "midilyzer.h"

void midiLyzer::analyze(NoteData noteData[],int numberOfNotes){
    chord chord;
   
    sortNotes(noteData,numberOfNotes);
    
    int relevantNotes[numberOfNotes];
    int relevants=0;
    bool found = false;
    
    chord.root = noteData[0].note_num %12;
    
    for(int i=0;i<numberOfNotes;i++){
        int target = (noteData[i].note_num-chord.root)%12 ;
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
     
    int beccate= 0;
  
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
    
    
    if(beccate==relevants){ //se abbiamo trovato tutte le note:
        if(hasThird&&hasSeventh){
            chord.quality = MAJ_7;
        }
        if(hasThird&&relevants==3){
            chord.quality= M_TRIAD;
        }        
        cout<<endl<<"Found chord: ";
        printChord(chord);
    }
    
}


void midiLyzer::printChord(chord chord){
    printNoteName(chord.root);
    printChordQuality(chord.quality);
}

const char *noteDiesis[5] = {"DO#","RE#","FA#","SOL#","LA#"};
const char *noteDiesisEN[5] = {"C#","D#","F#","G#","A#"};
const char *noteBemolle[5] = {"REb","MIb","SOLb","LAb","SIb"};
const char *noteBemolleEN[5] = {"Db","Eb","Gb","Ab","Bb"};


void midiLyzer::printNoteName(int note){
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


void midiLyzer::printChordQuality(CHORD_QUALITY quality){
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

int comp (const NoteData *primaNota, const NoteData *secondaNota) {
    return primaNota->status == OFF || primaNota->note_num > secondaNota->note_num ? 1 : -1;
}

bool note_sorter(NoteData const& lhs, NoteData const& rhs) {
    return lhs.note_num < rhs.note_num;
}

void midiLyzer::sortNotes(NoteData noteData[],int numberOfNotes){
    std::sort( noteData, noteData+numberOfNotes, &note_sorter);

  //  qsort(&noteData,numberOfNotes, sizeof(NoteData), (int (*) (const void *, const void *)) &note_sorter);
}


