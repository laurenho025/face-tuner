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
