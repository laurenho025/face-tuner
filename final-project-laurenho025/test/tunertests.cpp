#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "tuner.hpp"

int main (int argc, char* argv[]) {
    int result = Catch::Session().run(1, argv);
    return result;
}

TEST_CASE("Find closest pitch to tune to given selected note and measured MIDI number") {
    Tuner tuner;

    SECTION("Measured MIDI is below 21") {
        REQUIRE(tuner.FindClosestPitch("A", 5) == 0);
    }

    SECTION("Measured MIDI is above 127") {
        REQUIRE(tuner.FindClosestPitch("A", 200) == 0);
    }

    SECTION("Measured MIDI is already at target note") {
        REQUIRE(tuner.FindClosestPitch("C", 60) == 60);
    }

    SECTION("Measured MIDI not already at target note") {
        REQUIRE(tuner.FindClosestPitch("C", 62) == 60);
    }
}

TEST_CASE("FindClosestPitch correctly calculates the MIDI note difference") {
    Tuner tuner;
    int targetmidi = tuner.FindClosestPitch("C", 65); // Closest 'C' MIDI note to 65 is 60

    REQUIRE(tuner.GetDifference() == 5);
}

TEST_CASE("MIDI difference is correctly classified as an emotion") {
    Tuner tuner;
    tuner.FindClosestPitch("C", 62);
    map<string, double> classifiedemotions = tuner.ClassifyDifference();

    SECTION("Map is the correct size") {
        REQUIRE(classifiedemotions.size() == 2);
    }

    SECTION("Map contains the correct emotions") {
        REQUIRE(classifiedemotions.begin()->first == "cry");
    }
}

TEST_CASE("Emotion weights are correctly calculated") {
    Tuner tuner;
    tuner.FindClosestPitch("C", 65);
    map<string, double> classifiedemotions = tuner.ClassifyDifference();
    map<string, double> emotionsweighted = tuner.CalculateEmotionWeight(classifiedemotions);
    
    SECTION("Difference is 5, so emotion weight should be 0.5") {
        REQUIRE(emotionsweighted.begin()->second == 0.5);
    }
}
