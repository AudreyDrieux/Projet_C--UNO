#include "Pioche.hpp" 
#include <string>
#include <list>
#include <ctime>
#include <vector>
#include <random>

using namespace std;

Pioche::Pioche() {
	list<string> Couleur{"B", "J", "R", "V"};
	for (string const & color : Couleur)  {

		for (int i = 1; i <= 19; i++) {

			string spec = to_string(i%10);
			Card carteord(color, spec);
			jeu_cartes.push_front(carteord);
		}

		for (int i = 1; i <= 2; i++) {

			Card cartespec1(color, "+2");
			Card cartespec2(color, "p");
			jeu_cartes.push_front(cartespec1);
			jeu_cartes.push_front(cartespec2);
		}
	}
	// on copie la liste dans un vecteur
    std::vector<Card> v(jeu_cartes.begin(), jeu_cartes.end());

    // générateur de nombres aléatoires
    std::mt19937_64 G(time(NULL));

    //Mélanger le vecteur
    std::shuffle(v.begin(), v.end(), G);

    // Remplacer le contenu de la liste par celui du vecteur mélangé
    jeu_cartes.assign(v.begin(), v.end());
}

Card Pioche::piocher() {

	Card carte = jeu_cartes.front();
	jeu_cartes.pop_front();
	return carte;

}



	
