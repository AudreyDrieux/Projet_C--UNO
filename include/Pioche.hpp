#ifndef __PIOCHE__HPP
#define __PIOCHE__HPP

/*!
 * \file Pioche.hpp
 * \brief classe pioche représentant la pioche du jeu
 * \author Audrey Drieux
 * \version 0.1
 */

#include <list>
#include <algorithm>
#include "/users/home/28624202/Documents/Projet_C--UNO/include/Card.hpp"

class Pioche {

	private:
		std::list<Card> jeu_cartes; /*!< Jeu de cartes du UNO*/ 

	public:
		/*!
		 * \brief Constructeur
		 * Constructeur par défaut de la classe Pioche
		 */

		Pioche();

		/*!
		 * \brief Mélanger les cartes de la pioche
		 *
		 * Méthode qui permet de mélanger les cartes de la pioche
		 *
		 * \param gen : un générateur de nombres pseudo-aléatoires
		 */

		template<class RandomGenerator> void melange_cartes(RandomGenerator & gen);

		/*!
		 * \brief Piocher une carte dans la pioche
		 *
		 * Méthode qui permet de piocher une carte dans la pioche
		 *
		 * \return une carte
		 */

		Card piocher();

		/*!
		 * \brief Taille de la pioche
		 *
		 * Méthode qui retourne la taille de la pioche
		 *
		 * \return un entier non signé
		 */

		std::size_t size() const {return jeu_cartes.size();};

};

template<class RandomGenerator>
void Pioche::melange_cartes(RandomGenerator & gen) {

	shuffle(jeu_cartes.begin(), jeu_cartes.end(), gen);

}

#endif
