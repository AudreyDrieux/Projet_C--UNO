#include "Card.hpp"
#include "Joueur.hpp"
#include "Pioche.hpp"
#include <iostream>
#include <list>
#include <ctime>
#include <random>

int main(){
    //On définit les joueurs
    Pioche P;
    // distribuer les cartes de la pioche dans 2 listes l0 et l1
    // mélanger les cartes de la pioche directement dans le constructeur?
    std::list<Card> l0{}, l1{};
    Joueur Player(0, l0);
    Joueur Ordi(1,l1);
    Player.distribution(7, P);
    Ordi.distribution(7, P);
    

    // on définit le premier joueur: current_player=rd(0,1)
    std::mt19937_64 G(time(NULL));
    std::uniform_int_distribution<int> U(0,1);
    int current_player = U(G);

    //tirer au sort la première carte dans la pioche : 
    Card current_card = P.piocher(); //current_card :  carte au dessus du tas de cartes jouées
    std::list<Card> talon{current_card}; //played_cards:tas des cartes déjà jouées, current_card au dessus du tas
    //si possible enlever les cartes "+" 
    
    !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! P.size();
    
    //début de la partie:
    while(Player.nb_cartes_joueur()!=0 && Ordi.nb_cartes_joueur()!=0 && P.size()!=0){
        
        //cas jeu de l'ordinateur
        if(current_player==1){ 
            std::list<Card> jeu = Ordi.get_jeu_cartes();
            const auto it = std::find_if(jeu.begin(), jeu.end(), superpose(current_card)); //ou à peu près
                if(jeu[i].superpose(current_card) == 1){
                    Ordi.retire_carte(jeu[i]);
                    current_card = jeu[i];
                    talon.append(jeu[i]);
                }
            };
            if(it != jeu.end()){ 
                //si une carte jouable a été trouvée
                Ordi.retire_carte(*it); //on retire la première carte jouable
                current_card = *it;
                talon.push_front(*it);
                if((current_card.spec != "+2") && (current_card.spec != "p")){ //prochain tour: Ordi si la carte jouée est "+2" ou "p", Player sinon
                        current_player = 0;
                    }
            }
            else{ 
                //cas pas de carte jouable
                Ordi.distribution(1, P); // on pioche une carte
                Card new_card = Ordi.get_jeu_cartes().front();
                if(new_card.superpose(current_card) == 1){ 
                    // si on peut poser la carte piochée
                    played_cards.push_front(new_card); //on l'ajoute au dessus du tas des cartes joué
                    current_card = new_card; //maj de la carte courante
                    Ordi.retire_carte(new_card); // on retire la carte jouée du jeu du joueur
                    if((current_card.spec != "+2") && (current_card.spec != "p")){
                        current_player = 0;
                    }
                }
            else{ 
                //si on ne peut pas poser la carte pioché: on passe son tour
                current_player = 0
            }
        };


        if(current_player == 0){ 
            //Cas Joueur intéractif
            Player0.affiche();
            std::cout << "Veuillez choisir une carte: " << std::endl;
            std::string color;
            //temps (20 secondes?)
            std::cout << "couleur (B, J, R, V), 'pass' pour passer votre tour : " << std::endl;
            std::cin >> color; //cas où la couleur n'est pas valide
            if(color == "pass"){
            //cas ou le joueur décide de passer son tour
                current_player = 1;
            }else{
                std::string spec;
                std::cout << "spécialité/numéro (0 à 9 , '+2', 'p'): " << std::endl;
                

            }
             
            std::cin >> ;
            while( (std::find(Player.get_jeu_cartes.begin(), Player.get_jeu_cartes.end(), chosen) == Player.get_jeu_cartes.end()) || (chosen.superpose(current_card) == 0) ){
                //tant que la carte choisie n'est pas dans le jeu du joueur ou n'est pas valide
                std::cout << "Veuillez choisir une carte valide: " << std::endl;
                std::cin >> chosen;
            }
            //si la carte choisie est bien dans le jeu du joueur et si elle est valide
            current_card = chosen;
            talon.push_front(chosen); // on pose la carte
            Player.retire_carte(chosen);
        

            
        }
        
    }

    }

    return 0;
}