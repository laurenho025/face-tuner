#include "tuner.hpp"
#include <vector>
#include <string>
#include <math.h>

using std::vector;
using std::find;
using std::pair;

double Tuner::GetDifference() {
    return difference;
}

int Tuner::FindClosestPitch(string selectednote, float measuredmidi) {
    // MIDI note value can only be 21-127
    if (selectednote == "" || measuredmidi < 21 || measuredmidi > 127) {
        difference = 0;
        return 0;
    }
    
    double selectedmidi = kNoteToMidi.find(selectednote[0])->second;
    difference = abs(selectedmidi - measuredmidi);
    int targetmidi = selectedmidi;
    for (int i = selectedmidi; i <= 127; i += 12) {
        if (abs(i - measuredmidi) < difference) {
            difference = floor(abs(i - measuredmidi));
            targetmidi = i;
        }
    }
    return targetmidi;
}

map<string, double> Tuner::ClassifyDifference() {
    map<string, double> emotionweights;
    if (difference > 0) {
        emotionweights.insert(pair<string, double>("fury", 1));
        emotionweights.insert(pair<string, double>("rage", 1));
    }
    if (difference == 0) {
        emotionweights.insert(pair<string, double>("grin", 0.5));
        emotionweights.insert(pair<string, double>("laugh", 0.5));
        emotionweights.insert(pair<string, double>("smile", 0.5));
    }
    return emotionweights;
}

