#pragma once

#include <map>

using std::map;
using std::string;

class Tuner {
enum Emotion {Anger, Cry, Fury, Grin, Laugh, Rage, Sad, Smile, Surprise};
    
private:
    map<char, int> note_to_midi_num = { {'A', 21}, {'B', 23}, {'C', 24}, {'D', 26}, {'E', 28}, {'F', 29}, {'G', 31} };
    double difference;
public:
    // Find the closest MIDI pitch (needed to tune to) given the selected note and measured MIDI note number (21 - 127)
    int FindClosestPitch(string selectednote, float measuredmidi);
    void CalculateDifference(float actualfreq, float measuredfreq);
    Emotion ClassifyDifference();
    double CalculateEmotionWeight();
};

// pitch frequency is a float
// need a function to calculate the difference between measured pitch and actual pitch hz
// function to classify the size of the difference as a facial emotion

// Starts at 21 (A) to 127 (G)
// A: 21, plus 12 every time
// B: 23, plus 12 every time
// C: 24, plus 12 every time
// D: 26, plus 12 every time
// E: 28
// F: 29
// G: 31
// for loop, plus twelve each time, find minimized distance, tune to that pitch

