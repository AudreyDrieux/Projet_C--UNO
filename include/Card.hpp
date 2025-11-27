#ifndef CARTE__HPP
#define CARTE__HPP

/**
 * \file card.hpp
 * \brief définition des cartes
 * \author A. Margot
 * \version 0.1
 * \date 27/11/2025
 */

#include <iostream>
#include <string>





class Card{
    /**
     * \class Card
     * \brief classe d'une carte
     * 
     * la classe définit une carte et ses "opérations" possibles
     */
    private:
        std::string color;  /*< couleur de la carte*/
        int num;    /*<numéro de la carte: 0 à 9 pour une standard, 10,11 pour une spéciale*/
    public:
        /**
         * \brief Constructeur
         * 
         * Constructeur de la classe Card
         * \param color1 : couleur de la carte
         * \param num1 : numéro de la carte (10 pour un passer le tour, 11 pour un +2)
         */
        Card(std::string color1, int num1): color(color1), num(num1){};
        
        /**
         * \brief affichage d'une carte
         * 
         * affichage de la carte
         */
        void affiche()const;

        /**
         * \brief test si la carte jouée est valide
         * 
         * indique si la carte est jouable dans le cas où l'autre carte est sur le tas(~"loi" symétrique)
         * \param carte: la carte sur le tas
         * \return si la carte est valide a jouer ou non
         */
        bool superpose(const Card&) const;

        /**
         * \brief numéro de la carte
         * 
         * accesseur au numéro de la carte
         * \return le numéro de la carte
         */
        int numero()const;

        /**
         * \brief couleur de la carte
         * 
         * accesseur à la couleur de la carte
         * \return la couleur de la carte
         */
        std::string colorcard()const;

        
    };
        
#endif