#include "Card.hpp"
#include "Joueur.hpp"
#include "Pioche.hpp"
#include <iostream>
#include <list>
#include <ctime>
#include <random>

int main(){
    
    Pioche P;
    // On définit les joueurs
    Joueur Player(0);
    Joueur Ordi(1);
    // distribuer les cartes de la pioche
    Player.distribution(7, P);
    Ordi.distribution(7, P);
    
    // on définit le premier joueur aléatoirement
    std::mt19937_64 G(time(NULL));
    std::uniform_int_distribution<int> U(0,1);
    int current_player = U(G);

    //tirer au sort la première carte dans la pioche : 
    Card current_card = P.piocher(); //current_card :  carte au dessus du tas de cartes jouées
    std::list<Card> talon{current_card}; // talon: tas des cartes déjà jouées, current_card au dessus du tas
    std::cout << "talon : ";
    current_card.affiche();

    //début de la partie:
    //tant que les deux joueurs ont des cartes et que la pioche n'est pas vide
    while(Player.nb_cartes_joueur()!=0 && Ordi.nb_cartes_joueur()!=0 && P.size()!=0){
        
        //cas jeu de l'ordinateur
        if(current_player==1){ 
            //on copie le jeu de cartes de l'ordinateur pour le parcourir
            std::list<Card> jeu = Ordi.get_jeu_cartes();
            //on cherche une carte que l'ordinateur peut poser au hasard dans son jeu
            const auto it = std::find_if(jeu.begin(), jeu.end(), [& current_card](const Card& carte){return carte.superpose(current_card) == 1;}); //ou à peu près
            //si on a trouvé une carte
            if(it != jeu.end()){
                Ordi.retire_carte(*it);
                current_card = *it;
                std::cout << "jeu adversaire: ";
                current_card.affiche();
                talon.push_back(*it);
                //si on a pas posé une carte spéciale ("+2" ou "passe tour"): le prochain tour est à l'adversaire
                if((current_card.numero() != "+2") && (current_card.numero() != "p")){ 
                        current_player = 0;
                    }
            }else{
                //si on a pas trouvé de carte a jouer
                Ordi.distribution(1, P); // on pioche une carte
                Card new_card = Ordi.get_jeu_cartes().front(); 
                if(new_card.superpose(current_card) == 1){ 
                    // si on peut poser la carte piochée
                    talon.push_front(new_card); //on l'ajoute au dessus du tas des cartes joué
                    current_card = new_card; //maj de la carte courante
                    Ordi.retire_carte(new_card); // on retire la carte jouée du jeu du joueur
                    std::cout << "jeu adversaire : ";
                    current_card.affiche();
                    if((current_card.numero() != "+2") && (current_card.numero() != "p")){
                        current_player = 0;
                    }
                }else{ 
                    //si on ne peut pas poser la carte pioché: on passe son tour
                    current_player = 0;
                }
            };//fin jeu ordinateur
        };

            //Cas Joueur intéractif
            if(current_player == 0){ 
                std::cout << "talon: ";
                current_card.affiche();
                std::cout << "Votre jeu:" << std::endl;
                Player.affiche();
                std::list<Card> jeuJ = Player.get_jeu_cartes();
                const auto it2 = std::find_if(jeuJ.begin(), jeuJ.end(), [& current_card](const Card& carte){return carte.superpose(current_card) == 1;});
                
                if(it2 != jeuJ.end()){
                    //s'il a une carte valide
                    std::cout << "Veuillez choisir une carte: " << std::endl;
                    std::string color;
                    std::cout << "couleur (B, J, R, V), 'pass' pour passer votre tour : " << std::endl;
                    std::cin >> color; 

                    if(color == "pass"){
                        //si joueur décide de passer son tour
                        //il pioche
                        std::cout << "*pioche*" << std::endl;
                        Player.distribution(1, P);
                        Card new_cardJ = Player.get_jeu_cartes().front();
                        std::cout << "carte piochée :";
                        new_cardJ.affiche();

                        if(new_cardJ.superpose(current_card) == 1){ 
                            //si la carte piochée est valide
                            std::cout << "Voulez-vous jouer cette carte? (0 pour non, 1 pour oui)" << std::endl;
                            bool answer; //1 pour oui, 0 pour non
                            std::cin >> answer;
                            if(answer){
                                talon.push_front(new_cardJ); //on l'ajoute au dessus du tas des cartes joué
                                current_card = new_cardJ; //maj de la carte courante
                                Player.retire_carte(new_cardJ);
                                if((current_card.numero() != "+2") && (current_card.numero() != "p")){ 
                                    current_player = 1;
                                }
                                
                            }else{
                               current_player = 1; 
                            }
                        }else{
                            current_player = 1;
                        }
                }else{
                    //s'il joue une carte
                    std::string spec;
                    std::cout << "specialite/numero (0 : 9 , '+2', 'p'): " << std::endl;
                    std::cin >> spec;
                    Card chosen(color, spec);
                    //cas où la carte n'est pas valide
                    while( (std::find(jeuJ.begin(), jeuJ.end(), chosen) == jeuJ.end()) || (chosen.superpose(current_card) == 0) ){
                        std::cout << "Veuillez choisir une carte valide: " << std::endl;
                        std::cout << "couleur: " << std::endl;
                        std::cin >> color;
                        std::cout << "specialite/numero: " << std::endl;
                        std::cin >> spec;
                        chosen=Card(color, spec);
                    }
                    //si la carte choisie est bien dans le jeu du joueur et si elle est valide
                    current_card = chosen;
                    talon.push_front(chosen);
                    Player.retire_carte(chosen);
                    std::cout << "talon : ";
                    current_card.affiche();
                    if((current_card.numero() != "+2") && (current_card.numero() != "p")){ 
                        current_player = 1;
                    }
                }
                }else{
                    //si pas de carte valide dans le jeu du joueur
                    //il pioche
                    Player.distribution(1, P);
                    Card new_cardJ = Player.get_jeu_cartes().front();
                    if(new_cardJ.superpose(current_card) == 1){ 
                        //si la carte picohée est valide
                        std::cout << "carte piochée: ";
                        new_cardJ.affiche();
                        std::cout << "Voulez-vous jouer cette carte? (non: 0, oui:1)" << std::endl;
                        bool answer; //1 pour oui, 0 pour non
                        std::cin >> answer;
                        if(answer){
                            talon.push_front(new_cardJ); //on l'ajoute au dessus du tas des cartes joué
                            current_card = new_cardJ; //maj de la carte courante
                            Player.retire_carte(new_cardJ);
                            if((current_card.numero() != "+2") && (current_card.numero() != "p")){ 
                                current_player = 1;
                            }
                        }else{
                            current_player = 1; 
                        }
                    }else{
                        current_player = 1;
                    }
                }
        }; //fin jeu du joueur intéractif
        
    }; //fin boucle while
    if(P.size() == 0){
        std::cout << "Pioche vide: fin du jeu" << std::endl;
    }
    if(Player.nb_cartes_joueur()==0){
        std::cout << "Player won" << std::endl;
    }
    if(Ordi.nb_cartes_joueur()==0){
        std::cout << "Computer won" << std::endl;
    }

    return 0;
};
