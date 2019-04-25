#include "tuner.hpp"
#include <vector>
#include <string>
#include <math.h>

#include <iostream>

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
    map<string, double> emotionclassifications;
    if (difference <= 6 && difference >= 4) {
        emotionclassifications.insert(pair<string, double>("fury", 1));
        emotionclassifications.insert(pair<string, double>("rage", 1));
    }
    if (difference < 4 && difference >= 2) {
        emotionclassifications.insert(pair<string, double>("cry", 1));
        emotionclassifications.insert(pair<string, double>("sad", 1));
    }
    if (difference < 2 && difference > 0) {
        emotionclassifications.insert(pair<string, double>("grin", 0.4));
        emotionclassifications.insert(pair<string, double>("laugh", 0.4));
        emotionclassifications.insert(pair<string, double>("smile", 0.4));
    }
    if (difference == 0) {
        emotionclassifications.insert(pair<string, double>("grin", 0.5));
        emotionclassifications.insert(pair<string, double>("laugh", 0.5));
        emotionclassifications.insert(pair<string, double>("smile", 0.5));
    }
    return emotionclassifications;
}

map<string, double> Tuner::CalculateEmotionWeight(map<string, double> emotionclassifications) {
    map<string, double> emotionswithweight;
    map<string, double>::iterator it;
    double standardized_diff = fmod(difference, 2.0);
    for (it = emotionclassifications.begin(); it != emotionclassifications.end(); it++) {
        it->second = standardized_diff / 2;
        emotionswithweight.insert(pair<string, double>(it->first, it->second));
    }
    return emotionswithweight;
}
