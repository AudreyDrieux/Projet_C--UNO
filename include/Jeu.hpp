#ifndef JEU__HPP
#define JEU__HPP

/**
 * \file Jeu.hpp
 * \brief définition des cartes
 * \author A. Drieux, A. Margot
 * \version 1.0
 * \date 27/12/2025
 */

#include "Card.hpp"
#include "Joueur.hpp"
#include "Pioche.hpp"
#include <iostream>
#include <ctime>
#include <random>

class Jeu{
    /**
     * \class Jeu
     * \brief classe d'une partie de UNO
     * 
     * la classe définit une partie de UNO
     */
    private:
        Joueur Player; /*joueur intéractif*/
        Joueur Ordi; /*joueur ordinateur*/
        Pioche P;   /*pioche du jeu*/
        std::list<Card> talon; /*tas des cartes jouées*/
        Card current_card; /*carte sur le talon*/
        int current_player; /*0 pour humain, 1 pour ordi*/

    public:
        /**
         * \brief Constructeur
         * 
         * Constructeur par défault de la classe Jeu
         */
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

        /**
         * \brief partie de UNO
         * 
         * définit une partie de UNO
         */
        void Partie();

        /**
         * \brief tour du joueur ordinateur
         * 
         * effectue le jeu de l'ordinateur lors de son tour
         */
        Card TourOrdi();
        
        /**
         * \brief tour du joueur intéractif
         * 
         * demande au joueur intéractif la carte qu'il souhaite jouer et interprète son jeu
         */
        Card TourPlayer();

        /**
         * \brief UNO ordinateur
         * 
         * lorsque l'ordinateur n'a plus q'une seule carte, propose au joueur intéractif de contrer son UNO sous 10 secondes
         */
        void UnoCarteOrdi();

        /**
         * \brief UNO joueur
         * 
         * lorsque le joueur n'a plus qu'une seule carte, il lui est proposé de dire UNO sous 10 secondes, sinon son adversaire contre son UNO
         */
        void UnoCartePlayer();

        /**
         * \brief interprétation de la carte jouée
         * 
         * distribue le nombre de carte indiquées sur la carte si '+2' ou '+4', fait passer son tour à l'adversaire si nécessaire
         */
        void special_card();
};
#endif