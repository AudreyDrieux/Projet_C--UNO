#include "/users/home/28624202/Documents/Projet_C--UNO/include/Joueur.hpp"
#include <iostream>
#include <algorithm>

using namespace std;

void Joueur::affiche() const {

	cout << numero << ":" << " ";
	for (Card const & cartes : jeu_cartes_joueur) cartes.affiche();
	cout << endl;
}

void Joueur::distribution(int nb_cartes, Pioche & pioche) {

	for (int i = 1; i <= nb_cartes; i++) {

		Card carte_piocher = pioche.piocher();
		jeu_cartes_joueur.push_front(carte_piocher);

	}
}

void Joueur::retire_carte(list<Card>::iterator const it) {

	jeu_cartes_joueur.erase(it);

}




