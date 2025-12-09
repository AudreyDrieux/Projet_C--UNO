#include "/users/home/28624202/Documents/Projet_C--UNO/include/Pioche.hpp" 
#include <string>
#include <list>

using namespace std;

Pioche::Pioche() {

	list<string> Couleur{"B", "J", "R", "V"};
	for (string const & color : Couleur)  {

		for (int i = 1; i <= 19; i++) {

			string spec = to_string(i%10);
			Card carteord(color,spec);
			jeu_cartes.push_front(carteord);
		}

		for (int i = 1; i <= 2; i++) {

			Card cartespec1(color, "+2");
			Card cartespec2(color, "p");
		}
	}
}

Card Pioche::piocher() {

	Card carte = jeu_cartes.front();
	jeu_cartes.pop_front();
	return carte;

}



	
