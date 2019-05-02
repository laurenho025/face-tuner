#include "tuner.hpp"
#include <vector>
#include <string>
#include <math.h>

using std::vector;
using std::find;
using std::pair;

float Tuner::GetDifference() {
    return difference;
}

float Tuner::FindClosestPitch(string selectednote, float measuredmidi) {
    // A valid MIDI note number can only be between 21-127
    if (selectednote == "" || measuredmidi < 21 || measuredmidi > 127) {
        difference = 0;
        return 0;
    }
    
    // Cycle through the possible pitches for the selected note and find the smallest difference
    float selectedmidi = kNoteToMidi.find(selectednote[0])->second;
    difference = abs(selectedmidi - measuredmidi);
    float targetmidi = selectedmidi;
    for (double i = selectedmidi; i <= 127; i += 12) {
        if (abs(i - measuredmidi) < difference) {
            difference = abs(i - measuredmidi);
            targetmidi = i;
        }
    }
    return targetmidi;
}

map<string, float> Tuner::ClassifyDifference() {
    map<string, float> emotionclassifications;
    // Classify the difference as a corresponding facial emotion,
    // and populate a map of emotions corresponding to their initial "weights"
    if (difference >= 4 && difference <= 6) {
        emotionclassifications.insert(pair<string, float>("fury", 1));
        emotionclassifications.insert(pair<string, float>("rage", 1));
    } else if (difference >= 2 && difference < 4) {
        emotionclassifications.insert(pair<string, float>("cry", 1));
        emotionclassifications.insert(pair<string, float>("sad", 1));
    } else if (difference >= 0 && difference < 2) {
        emotionclassifications.insert(pair<string, float>("grin", 0.5));
        emotionclassifications.insert(pair<string, float>("laugh", 0.5));
        emotionclassifications.insert(pair<string, float>("smile", 0.5));
    }
    return emotionclassifications;
}

map<string, float> Tuner::CalculateEmotionWeight(map<string, float> emotionclassifications) {
    // If the difference is negligible, do not alter the initial emotion weight
    if (difference <= 0.1) {
        return emotionclassifications;
    }
    
    // Weight each emotion according to the size of the current MIDI difference
    map<string, float> emotionswithweight;
    map<string, float>::iterator it;
    float standardized_diff = fmod(difference, 2.0);
    for (it = emotionclassifications.begin(); it != emotionclassifications.end(); it++) {
        it->second = (1 - (standardized_diff / 2)) * it->second;
        emotionswithweight.insert(pair<string, float>(it->first, it->second));
    }
    return emotionswithweight;
}
