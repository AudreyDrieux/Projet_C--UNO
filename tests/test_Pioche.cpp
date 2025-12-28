#include <catch2/catch_test_macros.hpp>
#include "../include/Pioche.hpp"


TEST_CASE("piocher") {
    Pioche P;
    size_t size_P = P.size();
    Card C = P.piocher();
    REQUIRE(P.size() == size_P -1);
}

TEST_CASE("size") {
    Pioche P;
    size_t size_P = P.size();
    for(int i = 0; i < size_P - 1; i++){
        Card C = P.piocher();
    }
    REQUIRE(P.size() == 1);
}

TEST_CASE("=="){
    Card C1("R", "p");
    Card C2("V", "3");
    REQUIRE((C1==C2) == false);
    REQUIRE(C1==C1);
}
