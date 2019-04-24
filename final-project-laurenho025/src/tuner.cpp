#include "tuner.hpp"
#include <vector>
#include <string>
#include <math.h>

using std::vector;
using std::find;

double Tuner::GetDifference() {
    return difference;
}

int Tuner::FindClosestPitch(string selectednote, float measuredmidi) {
    // MIDI note value can only be 21-127
    if (measuredmidi < 21 || measuredmidi > 127) {
        return 0;
    }
    
    double selectedmidi = kNoteToMidi.find(selectednote[0])->second;
    difference = abs(selectedmidi - measuredmidi);
    int targetmidi = selectedmidi;
    for (int i = selectedmidi; i <= 127; i += 12) {
        if (abs(i - measuredmidi) < difference) {
            difference = abs(i - measuredmidi);
            targetmidi = i;
        }
    }
    return targetmidi;
}
