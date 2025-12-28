//#include <catch2/catch_test_macros.hpp>
#define CATCH_CONFIG_MAIN
#include "../include/catch.hpp"
#include "../include/Joueur.hpp"


TEST_CASE("distribution") {
    Pioche P;
    Joueur Player(1);
    size_t taille_initiale = P.size(); // Supposons que vous avez size() ou get_taille()
    Player.distribution(2, P);
    REQUIRE(Player.get_jeu_cartes().size() == 2);
    REQUIRE(P.size() == (taille_initiale - 2));
}

TEST_CASE("nb_cartes_joueur") {
    Card C("R", "2");
    std::list<Card> l{C};
    Joueur Player(1, l);
    REQUIRE(Player.nb_cartes_joueur() == 1);
}

TEST_CASE("get_jeu_cartes") {
    Card C("R", "2");
    std::list<Card> l{C};
    Joueur Player(1, l);
    REQUIRE(Player.get_jeu_cartes() == l);
}

TEST_CASE("retire_carte") {
    Card C1("R", "2");
    Card C2("V", "+2");
    std::list<Card> l{C1, C2};
    std::list<Card> l2{C2};
    Joueur Player(1, l);
    Player.retire_carte(C1);
    REQUIRE(Player.get_jeu_cartes() == l2);
    Joueur Player2(1, l);
    Player2.retire_carte(l.begin());
    REQUIRE(Player2.get_jeu_cartes() == l2);
    
}