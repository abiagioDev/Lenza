//
//  midiCore.cpp
//  Lenza
//
//  Created by Matteo Chiti on 22/06/22.
//

#include "midiCore.hpp"

void midiCore::setup() {
    // midiIn.listInPorts();
     midiIn.openPort(0);
     midiIn.addListener(this);
     
     for (int i = 0; i < MAX_NUM_OF_NOTES; i++) {
         noteData[i].status = OFF;
         noteData[i].note_num = 128;
     }
     onNotes = 0;
}

void midiCore::newMidiMessage (ofxMidiMessage& msg) {
    //if we have received a note-on message
    if (msg.status == MIDI_NOTE_ON && msg.velocity != 0) {
        for (int i = 0; i < MAX_NUM_OF_NOTES; i++) {
            if (noteData[i].status == OFF) {
                noteData[i].status = ON;
                noteData[i].note_num = msg.pitch;
                noteData[i].note_vel = msg.velocity;
                
                onNotes++;
                
                // cout << "Added ON NOTE :" ;
                // cout <<"Velocity: "<<msg.velocity<<endl;
                // cout <<"Pitch: "<<msg.pitch<<endl;
                //
                break;
            }
        }
    } else if (msg.status == MIDI_NOTE_OFF) {
        
        for (int i = 0; i < MAX_NUM_OF_NOTES; i++) {
            
            if (noteData[i].note_num == msg.pitch) {
                
                noteData[i].status = OFF;
                onNotes--;
                
                // cout << "TURNED OFF A NOTE :" ;
                // cout <<"Pitch: "<<msg.pitch<<endl;
                break;
                
            }
            
        }
        
    } else if (msg.status == MIDI_CONTROL_CHANGE){
        
        cout<<"Control: "<<msg.control<<endl;
        cout<<"Value: "<<msg.value<<endl;
        
        if(msg.control== 1) {
            control = msg.value;
        }
    }
    if (onNotes>0)
    midi_analyzer.analyze(noteData, onNotes);
}

NoteData* midiCore::getNoteData() {
    return noteData;
}

int midiCore::getOnNotes() {
    return onNotes;
}
