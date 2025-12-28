//#include <catch2/catch_test_macros.hpp>
#define CATCH_CONFIG_MAIN
#include "../include/catch.hpp"
#include "../include/Card.hpp"

TEST_CASE("numéro") {
    Card C1("red", "2");
    Card C2("green", "+2");
    REQUIRE(C1.numero() == "2");
    REQUIRE(C2.numero() == "+2");
}

TEST_CASE("colorcard") {
    Card C1("red", "2");
    Card C2("green", "+2");
    REQUIRE(C1.colorcard() == "red");
    REQUIRE(C2.colorcard() == "green");
}

TEST_CASE("superpose") {
    Card C1("R", "2");
    Card C2("V", "+2");
    Card C3("V", "4");
    Card C4("B", "+2");
    Card C5("B", "p");
    REQUIRE(C1.superpose(C2) == false);
    REQUIRE(C2.superpose(C3) == true);
    REQUIRE(C2.superpose(C4) == true);
    REQUIRE(C5.superpose(C4) == true);
}

TEST_CASE("==") {
    Card C1("red", "2");
    Card C2("green", "+2");
    REQUIRE(C1 == C1);
    REQUIRE(not(C1 == C2));
}

TEST_CASE("=") {
    Card C1("red", "2");
    Card C2("green", "+2");
    REQUIRE((C1 == C2)==false);
    C1 = C2;
    REQUIRE(C1 == C2);
}