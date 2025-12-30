#include "Joueur.hpp"
#include <iostream>
#include <algorithm>

using namespace std;

void Joueur::affiche() const {
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

void Joueur::retire_carte(const Card& card) {
	const auto it = std::find_if(jeu_cartes_joueur.begin(), jeu_cartes_joueur.end(), [& card](const Card& carte){return carte == card;});
	if(it != jeu_cartes_joueur.end()){
        jeu_cartes_joueur.erase(it);
	}
}


