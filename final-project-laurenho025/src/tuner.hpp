#pragma once

#include <map>

using std::map;
using std::string;

class Tuner {
    
private:
    // Map that links char notes to its starting MIDI note number
    // MIDI number is incremented 12 for the next octave/pitch
    const map<char, int> kNoteToMidi = { {'A', 21}, {'B', 23}, {'C', 24}, {'D', 26}, {'E', 28}, {'F', 29}, {'G', 31} };
    double difference;
    
public:
    // Getter for testing
    double GetDifference();
    
    // Find the closest MIDI pitch to tune to given the selected char note and measured MIDI number (21-127)
    // This function also calculates/updates the difference between the target and measured MIDI
    int FindClosestPitch(string selectednote, float measuredmidi);
    
    // Classifies the size of the MIDI difference as a corresponding facial emotion as a string
    map<string, double> ClassifyDifference();
    
    double CalculateEmotionWeight();
};

// possible emotions: anger, cry, fury, grin, laugh, rage, sad, smile, surprise
// Classifying difference:
// 6 bad- fury 1, rage 1
// 0 perfect- grin 0.5, laugh 0.5, smile 0.5
//
