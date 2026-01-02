#include "uno.h"
#include <QDebug>
#include <QApplication>

// Déclaration des variables

map<QString, QPixmap> jeu;    // correspondance entre code carte et image

Paquet pioche;                        // codes des cartes dans la pioche de la partie en cours

Paquet talon;                          // codes des cartes dans le talon de la partie en cours

Paquet mainordi;                    // codes des cartes dans la main de l'ordinateur

Paquet mainjou;                     // codes des cartes dans la main du joueur

int kidon;            	           // celui qui donne ( 1 = ordinateur, 2= joueur )

int kijou;               	           // celui qui joue

int ncordi;                             // nombre de cartes dans la main de l'ordinateur

int ncpio;                             // nombre de cartes dans la pioche

int ncjou;                              // nombre de cartes dans la main du joueur

int icarte;                          // indice dans mainjou de la carte jouée par le joueur

int iclic;                              // indice du bouton z[i] cliqué par le joueur

int isignal;                            // indique le signal utilisé par le joueur (voir uno.cpp )

int ndebor;                            // indice dans mainjou de la carte affichée dans z[0]

bool clicuno;                        // true si le joueur a cliqué uno

bool passe;                            // true si kijou a passé

bool enfonc = true;

char coulatt;        // couleur attendue sur le talon

// Début du programme

int main(int argc, char *argv[]) {

    qputenv("QT_QPA_PLATFORM", "windows:darkmode=0");

    QApplication a(argc, argv);

    Fenetre uno;

    uno.show();

    uno.initjeu();                                         // constitution map du jeu

    kidon = 2;                                             // L'ordinateur donne la 1ère partie

    do {                                                  // tant que le joueur n'a pas fermé sa fenêtre

    // on distribue 14 cartes aux joueurs, 7 à chacun en commençant par l'adversaire de kidon
    // puis on met la 15ème carte sur le talon ( ça ne peut pas être un +4 )

    if (kidon == 1) kidon = 2;

    else kidon = 1;

    kijou = kidon;                                          // kidon est celui qui a la main car il va distribuer

    uno.nouvpartie();                                      // voir uno.cpp

    do {                                                  // tant que les 2 joueurs ont des cartes en main

        passe = false;                                  // pour l'instant, kijou n'a pas passé

        if ( kijou == 1 ) uno.tourordi();             // c'est au tour de l'ordinateur de jouer

        else {

            uno.tourjou();

        }              // sinon, c'est au tour du joueur

        if (passe) {

            uno.changekijou();

        }          // celui qui vient de jouer a passé

        else {

            uno.akiltour();

        }                   // sinon on regarde comment doit continuer la partie

           // on a fait un tour et on continue la partie tant que les 2 joueurs ont tous deux des cartes

    } while (enfonc && (ncjou > 0) && (ncordi > 0) );

    // la partie en cours est finie. On regarde qui a gagné et on le dit au joueur

    if ( ncjou == 0 ) uno.acquitter ("Vous avez gagné ! Cliquez ici pour jouer une nouvelle partie" ) ;

    else uno.acquitter(" L'ordinateur a gagné... Cliquez ici pour jouer une nouvelle partie");

    // si le joueur ne ferme pas sa fenêtre, on continue

    } while(enfonc);

  return a.exec();
}
