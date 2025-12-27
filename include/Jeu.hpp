#include "Card.hpp"
#include "Joueur.hpp"
#include "Pioche.hpp"
#include <iostream>
#include <ctime>
#include <random>

class Jeu{
    private:
        Joueur Player;
        Joueur Ordi;
        Pioche P;
        std::list<Card> talon;
        Card current_card;
        int current_player; // 0 pour humain, 1 pour ordi

    public:
        Jeu(): Player(0), Ordi(1), current_card(P.piocher()) {
            // distribuer les cartes de la pioche
            Player.distribution(7, P);
            Ordi.distribution(7, P);
            // on définit le premier joueur aléatoirement
            std::mt19937_64 G(time(NULL));
            std::uniform_int_distribution<int> U(0,1);
            current_player = U(G);
            //tirer au sort la première carte dans la pioche : 
             //current_card :  carte au dessus du tas de cartes jouées
            talon.push_back(current_card); // talon: tas des cartes déjà jouées, current_card au dessus du tas
        };

        void Partie();

        Card TourOrdi();
        
        Card TourPlayer();

        void UnoCarteOrdi();

        void UnoCartePlayer();

        void special_card();
};