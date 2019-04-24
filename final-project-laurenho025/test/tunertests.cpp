#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "tuner.hpp"

int main (int argc, char* argv[]) {
    int result = Catch::Session().run(1, argv);
    return result;
}

TEST_CASE("Catch working") {
    REQUIRE(1 == 1);
}
