#ifndef UNO_H
#define UNO_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>
#include <QMap>
#include <Qstring>
#include <QWidget>
#include <QSoundEffect>
#include <QApplication>

#include <map>
#include <vector>
#include <string>

using namespace std;

// Déclaration de la classe Carte

class Carte {

private:

    char couleur;
    char valeur;

public:

    Carte(char c = 'b', char v = '0') : couleur(c), valeur(v) {};
    char coul() const;
    char val() const;
    bool egal(const Carte& autre) const;
    void operator=(const Carte& autre);

};

// Déclaration de la classe Paquet

class Paquet {

public:

    vector<Carte> cartes;
    Paquet(vector<Carte> c ={} ) : cartes(c) {};
    Carte dessus() const;
    Carte operator()(int i) const;
    void empile(const Carte& c);
    Carte depile();
    void vers(Paquet& destination);
    int taille() const;
    Carte enleve(int i);

};

// Déclaration de la classe Fenetre

QT_BEGIN_NAMESPACE

namespace Ui { class Fenetre; }

QT_END_NAMESPACE

class Fenetre : public QMainWindow {
    Q_OBJECT

public:

    Fenetre(QWidget *parent = nullptr);
    ~Fenetre();

    // Méthodes de la classe Fenetre

    void acquitter(string mes);
    void allumer(char c);
    void metclicoff();
    void metclicon();
    void metclicartes(bool onoff);
    void metclicoul(bool onoff);
    void metclicnav();
    void garnilabels();
    void garniz( Carte c , int i);
    void garnicartes (bool onoff, bool dern );

    // Fonctions logiques

    void initjeu();                                     // initialisation du jeu

    void nouvpartie();                                  // distribue la 1ère main

    void trier( Paquet & main);                         // trier par couleur le paquet main

    void piocher();                                     // pioche une carte sur pioche et la met dans main kijou

    vector<int> classer(Paquet main);                   // calcule les nombres de carte de main par couleur

    void ordichoixcoul();                               // fait choisir une couleur par l'ordinateur

    void choixcoul();                                   // fait choisir une couleur à kijou

    void plus2 ();                                      // donne 2 cartes à l'adversaire de kijou

    void plus4 ();                                      // donne 4 cartes à l'adversaire de kijou

    void changekijou();                                 // change kijou en son adversaire

    void  akiltour();                                   // détermine la suite de la partie en fonction de la carte sur le talon

    bool cartevalid( int i);                            // détermine si la carte d'indice i dans main de kijou est jouable

    void jouajoue();                                    // le joueur a joué une carte permise

    void jouapioche();                                  // le joueur a pioché

    void jouveujouer();                                 // le joueur veut jouer la carte d'indice dans z[i]

    void tourjou();                                     // fait jouer un tour au joueur

    int choixcarte();                                   // l'ordinateur choisit une carte à jouer

    int chercher( char coul );

    void tourordi();                                    // fait jouer un tour à l'ordinateur

    void suitour( Paquet &main,int i );                  // enlève la carte d'indice i dans main et la met sur le talon,
                                                        // calcule si passe devient true

    // Labels utilisés dans ces méthodes

    QLabel *ztal;
    QLabel *zordi;
    QLabel *ztour;

// Déclaration des ''Pushbutton''

private:

    bool zpioon;
    bool ztalon;
    bool zunoon;
    bool zbon;
    bool zjon;
    bool zron;
    bool zvon;

    bool zon[14];

    bool zinfoon;

    bool zavanon;
    bool zapreson;

    Ui::Fenetre *ui;

    QSoundEffect *sonuno;

    QPushButton *zuno,*zb, *zj, *zr, *zv, *zpio, *zinfo, *quit;

    // pushbuttons des cartes de la main du joueur affichées

    QPushButton *z0;
    QPushButton *z1;
    QPushButton *z2;
    QPushButton *z3;
    QPushButton *z4;
    QPushButton *z5;
    QPushButton *z6;
    QPushButton *z7;
    QPushButton *z8;
    QPushButton *z9;
    QPushButton *z10;
    QPushButton *z11;
    QPushButton *z12;
    QPushButton *z13;

    QPushButton *zavan;
    QPushButton *zapres;

 // Slots associés aux signaux de la fenêtre

private slots:

    int on_zpio_clicked();
    void on_zuno_clicked();
    void on_zb_clicked();
    void on_zj_clicked();
    void on_zr_clicked();
    void on_zv_clicked();
    void on_zinfo_clicked();
    void on_quit_clicked();
    void on_zavan_clicked();
    void on_zapres_clicked();

    void on_z0_clicked();
    void on_z1_clicked();
    void on_z2_clicked();
    void on_z3_clicked();
    void on_z4_clicked();
    void on_z5_clicked();
    void on_z6_clicked();
    void on_z7_clicked();
    void on_z8_clicked();
    void on_z9_clicked();
    void on_z10_clicked();
    void on_z11_clicked();
    void on_z12_clicked();
    void on_z13_clicked();


};


// Déclaration en extern des variables déclarées dans main.cpp

extern bool passe;                    // vaut true ssi kijou a passé

extern int  kidon;            	      // celui qui donne ( 1 = ordinateur, 2= joueur )

extern int  kijou;               	  // celui qui joue

extern int  ncordi;              	  // nombre de cartes dans la main de l'ordinateur

extern int  ncpio;              	  // nombre de cartes dans la pioche

extern int  ncjou;               	  // nombre de cartes dans la main du joueur

extern char coulatt;                 // couleur attendue pour la prochaine carte jouée

extern Paquet pioche;             	  // pioche de la partie en cours

extern Paquet talon;               	  // talon de la partie en cours

extern Paquet mainordi;               // codes des cartes dans la main de l'ordinateur

extern Paquet mainjou;                // codes des cartes dans la main du joueur

extern map<QString, QPixmap> jeu;     // correspondance entre code carte et image

extern bool clicuno;                  //  true si le joueur a cliqué uno

extern bool enfonc;

extern int  ndebor;                    // indice dans mainjoue de la carte mise dans z[0]

extern int  isignal;                   // voir signification dans main.cpp

extern int  iclic;                     // indice du bouton z[i] cliqué par le joueur

extern int  icarte;                     // indice dans mainjou correspondant au bouton cliqué

// Méthodes logiques

bool comparcartes(const Carte& a, const Carte& b);  // compare les cartes a et b pour trier

#endif // UNO_H
