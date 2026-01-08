#include <iostream>
#include <chrono>
#include <ctime>
#include <limits>
#include "Jeu.hpp"
              
    
void Jeu::UnoCarteOrdi(){
    //on laisse 10 secondes pour que l'adversaire contre le UNO
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //pour ignorer le \n 
    //On lance le chrono
    auto depart = std::chrono::steady_clock::now();
    
    std::string contre_uno;
    std::getline(std::cin, contre_uno);
    
    //On arrête le chrono
    auto fin = std::chrono::steady_clock::now();
    
    //On calcule le temps mis en secondes
    std::chrono::duration<double> secondes_mises = fin - depart;

    if(((contre_uno == "contre UNO") ||(contre_uno == "contre uno")) && secondes_mises.count() <= 10.0) {
        std::cout << "Contre UNO, votre adversaire pioche 2 cartes" << std::endl;
        Ordi.distribution(2,P);
    } else {
        std::cout << "adversaire: UNO" << std::endl;
    }
    } 

void Jeu::UnoCartePlayer(){
    //on laisse 10 secondes pour que le joueur dise UNO
    //On lance le chrono
    auto depart = std::chrono::steady_clock::now();
    
    std::string uno;
    std::cin >> uno;
    
    //On arrête le chrono
    auto fin = std::chrono::steady_clock::now();
    
    //On calcule le temps mis en secondes
    std::chrono::duration<double> secondes_mises = fin - depart;

    if(((uno == "UNO") ||(uno == "uno")) && secondes_mises.count() <= 10.0){
        std::cout << "UNO" << std::endl;              
    }else{
        std::cout << "adversaire: contre UNO" << std::endl;
        std::cout << "Vous devez piocher 2 cartes" << std::endl;
        Player.distribution(2, P);
    }
}

void Jeu::Partie(){
    //tant que les deux joueurs ont des cartes et que la pioche n'est pas vide
    while(Player.nb_cartes_joueur()!=0 && Ordi.nb_cartes_joueur()!=0 && P.size()!=0){
        if(current_player==1){
        Card ordi = TourOrdi();
        if(ordi == Card("0","0")){
            current_player = 0;
        }else{
            std::cout << "Adversaire: " <<  Ordi.nb_cartes_joueur() << " cartes" << std::endl;
            if(Ordi.nb_cartes_joueur() == 1){ //si l'ordinateur n'a plus qu'une carte en main
                UnoCarteOrdi();
            }
        special_card();
            }
        }

        else if(current_player == 0){
            Card player = TourPlayer();
            if(player == Card("0","0") ){
                current_player = 1;
            }else{
                if(Player.nb_cartes_joueur() == 1){ //si le joueur n'a plus qu'une carte en main
                    UnoCartePlayer();
                }
                special_card();
            }
        }
    }

    if(P.size() == 0){
        std::cout << "Pioche vide: fin du jeu" << std::endl;
    }

    if(Player.nb_cartes_joueur()==0){
        std::cout << "Player won" << std::endl;
    }
    if(Ordi.nb_cartes_joueur()==0){
        std::cout << "Computer won" << std::endl;
    }   
}

Card Jeu::TourOrdi(){
    //on copie le jeu de cartes de l'ordinateur pour le parcourir
    std::list<Card> jeu = Ordi.get_jeu_cartes();
    //on cherche une carte que l'ordinateur peut poser au hasard dans son jeu
    const auto it = std::find_if(jeu.begin(), jeu.end(), [this](const Card& carte){return carte.superpose(this -> current_card) == 1;}); //ou à peu près
    //si on a trouvé une carte
    if(it != jeu.end()){
        Ordi.retire_carte(*it);
        current_card = *it;
        talon.push_back(*it);
        return current_card;
    }else{
        //si on a pas trouvé de carte a jouer
        std::cout << "*adversaire pioche*" << std::endl;
        Ordi.distribution(1, P); // on pioche une carte
        Card new_card = Ordi.get_jeu_cartes().front();

        if(new_card.superpose(current_card) == 1){ 
            // si on peut poser la carte piochée
            talon.push_front(new_card); //on l'ajoute au dessus du tas des cartes joué
            current_card = new_card; //maj de la carte courante
            Ordi.retire_carte(new_card); // on retire la carte jouée du jeu du joueur     
            return current_card;
        }else{ 
            //si on ne peut pas poser la carte pioché: on passe son tour
            return Card("0", "0");
        }
    }
}

Card Jeu::TourPlayer(){
    std::cout << "Votre jeu:" << std::endl;
    Player.affiche();
    std::list<Card> jeuJ = Player.get_jeu_cartes();
    const auto it2 = std::find_if(jeuJ.begin(), jeuJ.end(), [this](const Card& carte){return carte.superpose(this -> current_card) == 1;});
    if(it2 != jeuJ.end()){
        //s'il a une carte valide
        std::cout << "Veuillez choisir une carte: " << std::endl;
        std::string color;
        std::cout << "couleur (B, J, R, V, N), 'pass' pour passer votre tour : " << std::endl;
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
                        return current_card;
                    }
            }
            return Card("0","0");
        }else{
            //s'il joue une carte
            std::string spec;
            std::cout << "specialite/numero (0 : 9 , '+2', '+4', 'p'): " << std::endl;
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
            return current_card;
        }
    }else{
        //si pas de carte valide dans le jeu du joueur
        //il pioche
        std::cout << "Vous piochez" << std::endl;
        Player.distribution(1, P);
        Card new_cardJ = Player.get_jeu_cartes().front();
        if(new_cardJ.superpose(current_card) == 1){ 
            //si la carte piochée est valide
            std::cout << "carte piochee: ";
            new_cardJ.affiche();
            std::cout << "Voulez-vous jouer cette carte? (non: 0, oui:1)" << std::endl;
            bool answer; //1 pour oui, 0 pour non
            std::cin >> answer;
            if(answer){
                talon.push_front(new_cardJ); //on l'ajoute au dessus du tas des cartes joué
                current_card = new_cardJ; //maj de la carte courante
                Player.retire_carte(new_cardJ);
                return current_card;
            }
        }else{
           return Card("0", "0"); 
        }
    }
}

void Jeu::special_card(){
    if(current_player == 1){
        if((current_card.numero() != "+2") && (current_card.numero() != "p") && (current_card.numero()!="+4")){ 
            current_player = 0;
        }else if(current_card.numero() == "+2"){
            std::cout << "Carte '+2' jouee, vous piochez 2 cartes" << std::endl;
            Player.distribution(2, P);
        }else if(current_card.numero() == "+4"){
            std::cout << "Carte '+4' jouee, vous piochez 4 cartes" << std::endl;
            Player.distribution(4, P);
            std::string color = Ordi.get_jeu_cartes().front().colorcard();
            std:: cout << "Couleur choisie: " << color << std::endl;
            current_card = Card(color, "None");
        }

    }else if(current_player == 0){
        if((current_card.numero() != "+2") && (current_card.numero() != "p") && (current_card.numero()!="+4")){ 
            current_player = 1;
        }else if(current_card.numero() == "+2"){
            std::cout << "Carte '+2' jouee, votre adversaire pioche 2 cartes" << std::endl;
            Ordi.distribution(2, P);
        }else if(current_card.numero() == "+4"){
            std::cout << "Carte '+4' jouee, votre adversaire pioche 4 cartes" << std::endl;
            std::cout << "Quelle couleur choisissez-vous?" << std::endl;
            std::string color;
            std::cin >> color;
            current_card = Card(color, "None");
            Ordi.distribution(4, P);
    }
    }
}
