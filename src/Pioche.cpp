#include "/users/home/28624202/Documents/Projet_C--UNO/include/Pioche.hpp" 
#include <string>
#include <list>

using namespace std;

Pioche::Pioche() {

	list<string> Couleur{"rouge", "vert", "jaune", "bleu"};
	for (string const & color : Couleur)  {

		for (int i = 1; i <= 23; i++) {

			Card carte(color, i%12);
			jeu_cartes.push_front(carte);
		}
	}
}

Card Pioche::piocher() {

	Card carte = jeu_cartes.front();
	jeu_cartes.pop_front();
	return carte;

}



	
