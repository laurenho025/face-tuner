#pragma once

#include <map>

using std::map;
using std::string;

class Tuner {
    
private:
    // Map that links char notes to its starting MIDI note number
    // MIDI number is incremented by 12 each octave
    const map<char, float> kNoteToMidi = { {'A', 21}, {'B', 23}, {'C', 24}, {'D', 26}, {'E', 28}, {'F', 29}, {'G', 31} };
    
    // The difference between the target and measured MIDI number
    float difference;
    
public:
    // Getter for testing only
    float GetDifference();
    
    // Find the closest MIDI pitch to tune to given the selected char note and measured MIDI number (21-127)
    // This function also calculates/updates the difference variable
    float FindClosestPitch(string selectednote, float measuredmidi);
    
    // Classifies the size of the MIDI difference as a corresponding facial emotion as a string
    map<string, float> ClassifyDifference();
    
    // Calculates the "weight" of each classified emotion
    map<string, float> CalculateEmotionWeight(map<string, float> emotionclassifications);
};
