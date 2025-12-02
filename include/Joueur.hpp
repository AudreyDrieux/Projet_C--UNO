#ifndef __JOUEUR__HPP
#define __JOUEUR__HPP

/*!
 * \file Joueur.hpp
 * \brief classe joueur représentant un joueur  
 * \author Audrey Drieux
 * \version 0.1
 */

#include "Card.hpp"
#include "/users/home/28624202/Documents/Projet_UNO/include/Pioche.hpp" 
#include <list>

class Joueur {

	private:
		int numero; /*!< Numéro du joueur*/
		std::list<Card> jeu_cartes_joueur; /*!< Jeu de cartes du joueur*/

	public:
		/*!
		 * \brief Constructeur
		 * Constructeur de la classe Joueur
		 *
		 * \param num : numéro du joueur (1 ou 2)
		 * \param jeu_cartes_ini : jeu de cartes initial du joueur
		 */

		Joueur(int num, std::list<Card> jeu_cartes_ini): numero(num), jeu_cartes_joueur(jeu_cartes_ini) {};
		
		/*!
		 * \brief Afficher un joueur
		 *
		 * Méthode qui affiche le numéro et le jeu de cartes d'un joueur
		 * dans le terminal
		 *
		 */

		void affiche() const;

		/*!
		 * \brief Obtenir le nombre de cartes d'un joueur
		 *
		 * Méthode qui retourne le nombre de cartes d'un joueur
		 *
		 * \return un entier non signé
		 */

		size_t nb_cartes_joueur() const {return jeu_cartes_joueur.size();};

		/*!
		 * \brief Accesseur à l'attribut privé numero
		 *
		 * Méthode qui retourne le numéro d'un joueur
		 *
		 * \return un entier
		 */

		int get_numero_joueur() const {return numero;};

		/*!
		 * \brief Accesseur à l'attribut privé jeu_cartes_joueur
		 *
		 * Méthode qui retourne le jeu de cartes d'un joueur
		 *
		 * \return une liste de cartes
		 */

		std::list<Card> get_jeu_cartes() const {return jeu_cartes_joueur;};

		/*!
		 * \brief Ajoute des cartes au jeu de cartes d'un joueur
		 *
		 * Méthode qui permet d'ajouter des cartes au jeu de cartes d'un joueur
		 *
		 * \param nb_cartes : nombre de cartes à ajouter
		 * \param pioche : cartes ajoutées proviennent de la pioche   
		 * 
		 */

		void distribution(int nb_cartes, Pioche & pioche);

};

#endif



