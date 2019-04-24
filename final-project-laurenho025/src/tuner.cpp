#include "tuner.hpp"
#include <vector>
#include <string>
#include <math.h>

using std::vector;
using std::find;

int Tuner::FindClosestPitch(string selectednote, float measuredmidi) {
    // MIDI note value can only be 21-127
    if (measuredmidi < 21 || measuredmidi > 127) {
        return 0;
    }
    
    double selectedmidi = note_to_midi_num.find(selectednote[0])->second;
    double smallestdiff = abs(selectedmidi - measuredmidi);
    int targetmidinum = selectedmidi;
    for (int i = selectedmidi; i <= 127; i += 12) {
        if (abs(i - measuredmidi) < smallestdiff) {
            smallestdiff = abs(i - measuredmidi);
            targetmidinum = i;
        }
    }
    return targetmidinum;
}
