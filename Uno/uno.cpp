#include "uno.h"
#include "ui_uno.h"

#include <algorithm>
#include <random>
#include <chrono>

#include <QObject>
#include <Qstring>
#include <QDrag>
#include <QMimeData>
#include <QDebug>
#include <QThread>

using namespace std;

//========== METHODES DE CLASSE =================

// Définition des méthodes de la classe Carte

char Carte::coul() const { return couleur;}

char Carte::val() const {  return valeur;}

bool Carte::egal(const Carte& autre) const {

    return (couleur == autre.couleur) && (valeur == autre.valeur);
}

void Carte::operator=(const Carte& autre) {

    couleur = autre.couleur;

    valeur = autre.valeur;
}

// Définitions des méthodes de la classe Paquet

Carte Paquet::dessus() const {

    if (cartes.empty()) return Carte('x', 'x');

    return cartes.back();
}

Carte Paquet::operator()(int i) const {

    if (i < 0 || i >= cartes.size()) return Carte('x', 'x');

    return cartes[i];
}

void Paquet::empile(const Carte& c) {

    cartes.push_back(c);
}

Carte Paquet::depile() {

    Carte c;

    if (!cartes.empty()) { c = cartes.back(); cartes.pop_back(); }

    return c;
}

void Paquet::vers(Paquet& destination) {

    if (!cartes.empty()) {

        Carte c = cartes.back();

        cartes.pop_back();

        destination.empile(c);
    }
}

int Paquet::taille() const { return cartes.size(); }

Carte Paquet::enleve(int i) {

    if (i >= 0 && i < cartes.size()) {

        Carte c = cartes[i];

        cartes.erase(cartes.begin() + i);

        return c;
    }

    return Carte('x', 'x');
}

//============= Constructeur de la fenêtre ================================

Fenetre::Fenetre(QWidget *parent) : QMainWindow(parent), ui(new Ui::Fenetre) {

    ui->setupUi(this);

    sonuno = new QSoundEffect(this);

    sonuno->setSource(QUrl::fromLocalFile("dcartes/tada.wav"));

    // Récupérer les labels ztal, zordi et ztour

    ui->ztal -> findChild<QLabel*>("ztal");
    ui->zordi -> findChild<QLabel*>("zordi");
    ui->ztour -> findChild<QLabel*>("ztour");

    // Récupérer les labels des boutons

    ui->zuno -> findChild<QPushButton*>("zuno");
    ui->zb -> findChild<QPushButton*>("zb");
    ui->zj -> findChild<QPushButton*>("zj");
    ui->zr -> findChild<QPushButton*>("zr");
    ui->zv -> findChild<QPushButton*>("zv");
    ui->zavan -> findChild<QPushButton*>("zavan");
    ui->zapres -> findChild<QPushButton*>("zapres");
    ui->zpio->findChild<QPushButton*>("zpio");
    ui->zinfo->findChild<QPushButton*>("zinfo");
    ui->quit->findChild<QPushButton*>("quit");

    // Récupérer les labels des boutons z0 à z13

    ui->z0 -> findChild<QPushButton*>("z0");
    ui->z1 -> findChild<QPushButton*>("z1");
    ui->z2 -> findChild<QPushButton*>("z2");
    ui->z3 -> findChild<QPushButton*>("z3");
    ui->z4 -> findChild<QPushButton*>("z4");
    ui->z5 -> findChild<QPushButton*>("z5");
    ui->z6 -> findChild<QPushButton*>("z6");
    ui->z7 -> findChild<QPushButton*>("z7");
    ui->z8 -> findChild<QPushButton*>("z8");
    ui->z9 -> findChild<QPushButton*>("z9");
    ui->z10 -> findChild<QPushButton*>("z10");
    ui->z11 -> findChild<QPushButton*>("z11");
    ui->z12 -> findChild<QPushButton*>("z12");
    ui->z13 -> findChild<QPushButton*>("z13");

//-------------------- Initialisation des pushbuttons "zpio" et "zinfo" -----------------------


    QIcon icon = QIcon("dcartes/Cxx.png");
    ui->zpio -> setIcon(icon);
    ui->zpio -> setIconSize(QSize(91, 131));

//-------------------- Initialisation des pushbuttons z[i] -----------------------


    ui->z0 -> setIconSize(QSize(91, 131));
    ui->z1 -> setIconSize(QSize(91, 131));
    ui->z2 -> setIconSize(QSize(91, 131));
    ui->z3 -> setIconSize(QSize(91, 131));
    ui->z4 -> setIconSize(QSize(91, 131));
    ui->z5 -> setIconSize(QSize(91, 131));
    ui->z6 -> setIconSize(QSize(91, 131));
    ui->z7 -> setIconSize(QSize(91, 131));
    ui->z8 -> setIconSize(QSize(91, 131));
    ui->z9 -> setIconSize(QSize(91, 131));
    ui->z10 -> setIconSize(QSize(91, 131));
    ui->z11 -> setIconSize(QSize(91, 131));
    ui->z12 -> setIconSize(QSize(91, 131));
    ui->z13 -> setIconSize(QSize(91, 131));

    metclicoff(); 
}

// Destructeur de la fenêtre

Fenetre::~Fenetre() {

    delete ui;
}

// ===================== SLOTS POUR LES SIGNAUX =====================================


//---------------------- sur zpio ---------------------------------------------------

// A la sortie, ndebor est l'indice dans mainjou correspondant à la 1ère carte z0 du groupe de
// 14 cartes où se trouve la carte piochée qui a été mise dans z[ipioche] et isignal vaut 2.
// ipioche est délivré au retour

int Fenetre::on_zpio_clicked() {

    int ipioche = 0;

    if (zpioon){

        piocher();                          // ncjou a été incrémenté

        // si kijou = 2, on calcule le ndebor correspondant à la fin de mainjou
        // la carte piochée a été mise au dessus de mainjou

        if ( kijou == 2) {

            ndebor = 0;

            while ( ndebor < mainjou.taille() ) ndebor += 14;

            ipioche = mainjou.taille() - ndebor - 1;

            // ipioche est l'indice tel que z[ipioche] soit la carte piochée

            garnicartes(false,false);                 // on désactive les clics sur les autres cartes



            zon[ipioche] = true;                      // on active le clic sur z[ipioche]
        }

        isignal = 2;                                  // on indique un clic sur zpio
    }
    return ipioche;
}


//------------------------------ sur zuno ----------------------------

void Fenetre::on_zuno_clicked() {

    if (zunoon){

        sonuno->play();

        clicuno = true;                        // on mémorise que uno a été cliqué

        isignal = 0;                           // on indique un clic sur zuno

        zunoon = false;
    }
}


//----------------------------- sur zb,zj,zr,zv -----------------------

// permettant au joueur de choisir  la couleur ( coulatt ) de la prochaine carte à jouer
// le bouton correspondant est allumé et les autres sont éteints

void Fenetre::on_zb_clicked() {

    if (zbon){

        coulatt = 'b'; allumer('b'); isignal = 0;
    }
}

void Fenetre::on_zj_clicked() {


    if (zjon){

        coulatt = 'j'; allumer('j'); isignal = 0;
    }
}

void Fenetre::on_zr_clicked() {

    if (zron){

        coulatt = 'r'; allumer('r'); isignal = 0;
    }
}

void Fenetre::on_zv_clicked() {

    if (zvon){

        coulatt = 'v'; allumer('v'); isignal = 0;
    }
}

//---------------------- sur z0, z1, ..., z13 -------------------------------------


    void Fenetre::on_z0_clicked() {  if(zon[0]){isignal = 3;  // on indique que le joueur a cliqué sur une zi

                                     iclic = 0;} } // celle d'indice iclic égal à 0

    void Fenetre::on_z1_clicked() { if(zon[1]){isignal = 3; iclic = 1;} }

    void Fenetre::on_z2_clicked() { if(zon[2]){isignal = 3; iclic = 2;} }

    void Fenetre::on_z3_clicked() { if(zon[3]){isignal = 3; iclic = 3;} }

    void Fenetre::on_z4_clicked() { if(zon[4]){isignal = 3; iclic = 4;} }

    void Fenetre::on_z5_clicked() { if(zon[5]){isignal = 3; iclic = 5;} }

    void Fenetre::on_z6_clicked() { if(zon[6]){isignal = 3; iclic = 6;} }

    void Fenetre::on_z7_clicked() { if(zon[7]){isignal = 3; iclic = 7;} }

    void Fenetre::on_z8_clicked() { if(zon[8]){isignal = 3; iclic = 8;} }

    void Fenetre::on_z9_clicked() { if(zon[9]){isignal = 3; iclic = 9;} }

    void Fenetre::on_z10_clicked() { if(zon[10]){isignal = 3; iclic = 10;} }

    void Fenetre::on_z11_clicked() { if(zon[11]){isignal = 3; iclic = 11;} }

    void Fenetre::on_z12_clicked() { if(zon[12]){isignal = 3; iclic = 12;} }

    void Fenetre::on_z13_clicked() { if(zon[13]){isignal = 3; iclic = 13;} }




//-------------------- sur zinfo ---------------------------------------

void Fenetre::on_zinfo_clicked() {

    if (zinfoon) isignal = 4;

}

//-------------------- quit ---------------------------------------------

void Fenetre::on_quit_clicked() {

    this -> close();

    QApplication::quit();

    enfonc = false;
}

//-------------------- sur zavan et zapres -----------------------------

// augmente ou diminue ndebor de 14 et met isignal à 1
// garnit les labels z[i] avec les cartes du ''bloc de 14 cartes'' précédent ou suivant

void Fenetre::on_zavan_clicked() {

    if (zavanon){

        if (ndebor > 0) {

            ndebor -= 14;                                              // Reculer de 14 cartes

            if (ndebor < 0) ndebor = 0;

            if (kijou == 2) garnicartes(true,true);

            else garnicartes(false,false);

            isignal = 1;

            metclicnav();
        }
    }
}

void Fenetre::on_zapres_clicked() {

    if (zapreson){

        if (ndebor + 14 < mainjou.taille()) {

            ndebor += 14;                                              // Avancer de 14 cartes

            if (kijou == 2) garnicartes(true,true);

            else garnicartes(false,false);

            isignal = 1;

            metclicnav();
        }
    }
}


//==================== METHODES GRAPHIQUES ======================================


//------------------------ Méthode acquitter -----------------------------------------

// affiche le message en paramètre et attend que le joueur l'acquitte par un clic sur zinfo

// NOTA: au retour, TOUS les signaux sont désactivés; isignal vaut 0

void Fenetre::acquitter(string mes) {

    ui -> zinfo->setText(QString::fromStdString(mes));    // Affiche le message dans zinfo

    // désactiver tous les signaux

    metclicoff();   metclicoul(false);   metclicartes(false);

    // Active le clic sur zinfo

    zinfoon = true;

    // Attendre le clic  du joueur

    isignal = 1;

    do {

        this -> repaint();

        QApplication::processEvents();
    }

    while (enfonc&&(isignal != 4));

    // Désactiver le clic sur zinfo

    ui -> zinfo -> setText(""); // on efface zinfo

    zinfoon = false ; isignal = 1;

    this -> repaint();
}

//---------------------  Méthode allumer ----------------------------------

// Allume le bouton de la couleur du paramètre, éteint les autres

void Fenetre::allumer(char c) {


    // Style sombre pour les boutons :


    QString bsombre = "QPushButton { "   "  border-radius: 15px ; "

                      "  background-color: rgb(0, 118, 177) ;  "

                      "  border: 2px solid darkyblue ; "

                      " min-width: 30px ;"  "  min-height: 30 px ; "  "}";

    QString jsombre = "QPushButton { "   "  border-radius: 15px ; "

                      "  background-color: rgb(214, 143, 0) ;  "

                      "  border: 2px solid darkyyellow ; "

                      " min-width: 30px ;"  "  min-height: 30 px ; "  "}";

    QString rsombre = "QPushButton { "   "  border-radius: 15px ; "

                      "  background-color: rgb(100, 0, 0) ;  "

                      "  border: 2px solid darkyred ; "

                      " min-width: 30px ;"  "  min-height: 30 px ; "  "}";

    QString vsombre = "QPushButton { "   "  border-radius: 15px ; "

                      "  background-color: rgb(0, 100, 0) ;  "

                      "  border: 2px solid darkygreen ; "

                      " min-width: 30px ;"  "  min-height: 30 px ; "  "}";


    // Style "allumé" pour les boutons


    QString bclair = "QPushButton { "   "  border-radius: 15px ; "

                      "  background-color: rgb(85,255, 255) ;  "

                      "  border: 2px solid darkyblue ; "

                      " min-width: 30px ;"  "  min-height: 30 px ; "  "}";

    QString jclair = "QPushButton { "   "  border-radius: 15px ; "

                      "  background-color: rgb(255, 255, 0) ;  "

                      "  border: 2px solid darkyyellow ; "

                      " min-width: 30px ;"  "  min-height: 30 px ; "  "}";

    QString rclair = "QPushButton { "   "  border-radius: 15px ; "

                      "  background-color: rgb(255, 0, 0) ;  "

                      "  border: 2px solid darkyred ; "

                      " min-width: 30px ;"  "  min-height: 30 px ; "  "}";

    QString vclair = "QPushButton { "   "  border-radius: 15px ; "

                      "  background-color: rgb(0, 255, 0) ;  "

                      "  border: 2px solid darkygreen ; "

                      " min-width: 30px ;"  "  min-height: 30 px ; "  "}";

 // Eteindre tous les boutons

    ui->zb->setStyleSheet(bsombre);

    ui->zj->setStyleSheet(jsombre);

    ui->zr->setStyleSheet(rsombre);

    ui->zv->setStyleSheet(vsombre);

    // Allume le bouton de couleur c

    switch (c) {

    case 'b':   ui->zb->setStyleSheet( bclair ) ;  break;                   // bleu clair 85,255,255

    case 'j':   ui->zj->setStyleSheet( jclair ) ;  break;                   // jaune clair 255,255,0

    case 'r':   ui->zr->setStyleSheet( rclair ) ;  break;                   // rouge clair 255,3,7

    case 'v':   ui->zv->setStyleSheet( vclair ) ;  break;                   // vert clair  0,255,0

    default:  break;

    }

    this -> repaint();
}


//--------------------------- Méthode metclicoff -------------------------------------------

// Désactive tous les signaux sauf zinfo, zuno, zavan et zapres qui sont désactivés selon les besoins

void Fenetre::metclicoff() {

    zpioon = false;

    metclicoul(false);  metclicartes(false);

}

//---------------------------- Méthode metclicon -----------------------------------------

// Active le clic de zpio et les clics sur les cartes 

void Fenetre::metclicon() {

    zpioon = true;

    metclicartes(true);

}

//--------------------------- Méthode metclicartes ------------------------------------------

// Active ou désactive les clics des cartes affichées selon la valeur du paramètre

void Fenetre::metclicartes(bool onoff) {

    for (int i = 0; i < 14; ++i) {

        zon[i] = onoff;

        }
}

//------------------------- Méthode metclicoul --------------------------------------------------

// Active ou désactive les clics sur les boutons de couleur selon la valeur du paramètre

void Fenetre::metclicoul(bool onoff) {


    zbon = onoff; zjon = onoff; zron = onoff; zvon = onoff;

}

//----------------------- Méthode metclicnav --------------------------------------------------

// Active ou désactive les clic sur zavan et zapres selon la valeur de ndebor

void Fenetre::metclicnav() {

    if ( ndebor < 14 ) {zavanon = false; ui->zavan->hide();} else {zavanon = true; ui->zavan->show();}

    if (ndebor + 14 >=  mainjou.taille()){zapreson = false; ui->zapres->hide();} else {zapreson = true; ui->zapres->show();}
}

//-------------------------- Méthode garnilabels ----------------------------------------------------

// garnit les labels zpio avec le dos d'une carte, ztal avec l'image de la carte sur le talon
// et zordi avec le nombre de cartes que l'ordinateur a en main
//
// les boutons zavan et zapres sont affichés ou cachés en fonction de ncjou ( > ou < 14 )
// ils sont activés ou désactivés en fonction de ndebor
//
// NOTA: le label ztour est géré par la fonction logique changekijou et le label zinfo
// par la fonction acquitter

void Fenetre::garnilabels() {

    ui -> zpio->setIcon(jeu["xx"]);

    if (talon.taille() > 0) {

        Carte cartalon = talon.dessus();

        string code = string() + cartalon.coul() + cartalon.val();

        QString qcode = QString::fromStdString(code);

        ui -> ztal->setPixmap(jeu[qcode]);
    }

    if ( ncordi < 2 ) ui -> zordi->setText(QString("L'ordinateur a %1 carte en main").arg(ncordi));

                else  ui -> zordi->setText(QString("L'ordinateur a %1 cartes en main").arg(ncordi));

    ncpio = pioche.taille();

    if ( ncpio < 2 ) ui -> zcpio->setText(QString("La pioche contient %1 carte").arg(ncpio));

               else  ui -> zcpio->setText(QString("La pioche contient %1 cartes").arg(ncpio));

    // Afficher ou masquer les boutons zavan et zapres

    if (ndebor > 0) {
        ui -> zavan->show();
    } else {
        ui -> zavan->hide();
    }

    if (ncjou > ndebor+14) {
        ui -> zapres->show();
    } else {
        ui -> zapres->hide();
    }

    // Activer/désactiver les boutons zavan et zapres

    zavanon = (ndebor > 0);

    zapreson = (ndebor + 14 < mainjou.taille());

    this -> repaint();
}

//------------------------- Méthode garniz ---------------------------------------------

// garnit le label z[i] avec l'image de la carte c; c est le 1er paramètre, i est le 2ème

void Fenetre:: garniz( Carte c , int i) {

    string code = string() + c.coul() + c.val();

    QString qcode = QString::fromStdString(code);

    switch (i) {
        case 0 : ui->z0->setIcon(jeu[qcode]); ui->z0 -> setIconSize(QSize(91, 131)); ui->z0->show(); break;
        case 1 : ui->z1->setIcon(jeu[qcode]); ui->z1 -> setIconSize(QSize(91, 131)); ui->z1->show(); ui->z1->repaint(); break;
        case 2 : ui->z2->setIcon(jeu[qcode]); ui->z2 -> setIconSize(QSize(91, 131)); ui->z2->show(); ui->z2->repaint(); break;
        case 3 : ui->z3->setIcon(jeu[qcode]); ui->z3 -> setIconSize(QSize(91, 131)); ui->z3->show(); ui->z3->repaint(); break;
        case 4 : ui->z4->setIcon(jeu[qcode]); ui->z4 -> setIconSize(QSize(91, 131)); ui->z4->show(); ui->z4->repaint(); break;
        case 5 : ui->z5->setIcon(jeu[qcode]); ui->z5 -> setIconSize(QSize(91, 131)); ui->z5->show(); ui->z5->repaint(); break;
        case 6 : ui->z6->setIcon(jeu[qcode]); ui->z6 -> setIconSize(QSize(91, 131)); ui->z6->show(); ui->z6->repaint(); break;
        case 7 : ui->z7->setIcon(jeu[qcode]); ui->z7 -> setIconSize(QSize(91, 131)); ui->z7->show(); ui->z7->repaint(); break;
        case 8 : ui->z8->setIcon(jeu[qcode]); ui->z8 -> setIconSize(QSize(91, 131)); ui->z8->show(); ui->z8->repaint(); break;
        case 9 : ui->z9->setIcon(jeu[qcode]); ui->z9 -> setIconSize(QSize(91, 131)); ui->z9->show(); ui->z9->repaint(); break;
        case 10 : ui->z10->setIcon(jeu[qcode]); ui->z10 -> setIconSize(QSize(91, 131)); ui->z10->show(); ui->z10->repaint(); break;
        case 11 : ui->z11->setIcon(jeu[qcode]); ui->z11 -> setIconSize(QSize(91, 131)); ui->z11->show(); ui->z11->repaint(); break;
        case 12 : ui->z12->setIcon(jeu[qcode]); ui->z12 -> setIconSize(QSize(91, 131)); ui->z12->show(); ui->z12->repaint(); break;
        case 13 : ui->z13->setIcon(jeu[qcode]); ui->z13 -> setIconSize(QSize(91, 131)); ui->z13->show(); ui->z13->repaint(); break;

        default : break;
    }

    this->repaint();

}


//---------------------------- Méthode garnicartes ------------------------------------------

// Garnit les labels z[i] des cartes affichées en les "prenant" dans mainjou
// à partir de celle d'indice ndebor
// active ou désactive selon le paramètre les clics sur les z[i]
// cependant le dernier z[i] affiché est mis à dern (2ème paramètre) pour traiter
// le cas où le joueur a pioché et ne peut cliquer que sur cette carte
// cache les z[i] non remplis avec une carte

void Fenetre::garnicartes (bool onoff, bool dern ) {

    int i = 0 ;int index;

    do {

            index = ndebor + i;  Carte carte = mainjou(index);

            if ((mainjou.taille())!=0){

                garniz ( carte, i ); zon[i] = onoff;

            }

            i += 1;

    } while(( i < 14 )&&( index < (mainjou.taille()-1) ));

    zon[i-1] = dern;       // le clic sur la dernière affichée est mis à dern

    if ((mainjou.taille())==0){

        ui->z0->hide();

    }

    //  rend invisible les labels suivants

    while ( i < 14 ) {

        switch (i) {

            case 0 : ui->z0->hide(); break;
            case 1 : ui->z1->hide(); break;
            case 2 : ui->z2->hide(); break;
            case 3 : ui->z3->hide(); break;
            case 4 : ui->z4->hide(); break;
            case 5 : ui->z5->hide(); break;
            case 6 : ui->z6->hide(); break;
            case 7 : ui->z7->hide(); break;
            case 8 : ui->z8->hide(); break;
            case 9 : ui->z9->hide(); break;
            case 10 : ui->z10->hide(); break;
            case 11 : ui->z11->hide(); break;
            case 12 : ui->z12->hide(); break;
            case 13 : ui->z13->hide(); break;

            default : break;
        }

        zon[i] = false;

        i += 1;

    }

    this -> repaint();
}



//=============================== FONCTIONS LOGIQUES ======================================


//--------------------- Fonction comparcartes (comparaison pour la fonction trier) --------

bool comparcartes(const Carte& a, const Carte& b) {

    // Ordre des couleurs : 'b' < 'j' < 'r' < 'v' < 'n'

    if (a.coul() != b.coul()) {

        return a.coul() < b.coul();
    }

    // on peut perfectionner en triant par valeur les cartes d'une même couleur

    return a.val() < b.val();
}

//-------------------- Méthode trier (trie les cartes de la main en paramètre) -----------------

void Fenetre::trier(Paquet & main) {

    // Utiliser sort avec la fonction de comparaison définie précédemment

    sort(main.cartes.begin(), main.cartes.end(), comparcartes);
}

//--------------------------------- Méthode piocher ----------------------------------

// si la pioche est vide, on remet les cartes du talon dans la pioche sauf celle du dessus qui reste
// sur le talon comme nouvelle 1ère carte et on mélange la nouvelle pioche
// Dans tous les cas, on transfère le sommet de pioche dans la main de kijou
// et on augmente de 1 ncordi ou ncjou selon les cas

void Fenetre::piocher() {

    if ( pioche.taille() == 0 ) {                         // la pioche est vide

        Carte dessutalon = talon.depile();                // on garde le dessus du talon

        while ( talon.taille() > 0 ) talon.vers(pioche);  // on remet le talon dans la pioche

        // Mélanger la pioche: on base le seed sur l'heure

        unsigned seed = chrono::system_clock::now().time_since_epoch().count();

        shuffle(pioche.cartes.begin(), pioche.cartes.end(), mt19937(seed));

        talon.empile(dessutalon);                          // on remet le dernier talon

    } // fin de remise talon sur pioche

    Carte cartepio = pioche.depile();                    // cartepio est la carte piochée

    if ( kijou== 1 ) { mainordi.empile(cartepio); ncordi += 1; }

    else { mainjou.empile(cartepio); ncjou += 1; }

    garnilabels();                                      // rafraichit l'écran pour ncordi et ncpio
}

//------------------------ Méthode initjeu --------------------------------

void Fenetre::initjeu() {


    vector<char> couleurs = {'b', 'j', 'r', 'v'};

    vector<char> valeurs = {'0', '1', '2', '3', '4', '5', '6', '7', '8',
                            '9' ,'+', 'i', 'p'};

    // construction de la map

    for (const char &couleur : couleurs) {

        for (const char &valeur : valeurs) {

            string code = string() + couleur + valeur;

            string fichier = string() + "dcartes/C" + couleur + valeur + ".png" ;

            // dans la ligne suivante, code doit être converti en une const char * car
            // c'est ce qu'attend Qpixmap comme type d'argument

            QPixmap pixmap((fichier).c_str());

            if (pixmap.isNull()){


            } else {

                QString qcode = QString::fromStdString(code);
                jeu[qcode] =pixmap;
            }
        }
    }


    jeu["n+"] = QPixmap("dcartes/Cn+.png" );

    jeu["nc"] = QPixmap("dcartes/Cnc.png" );

    jeu["xx"] = QPixmap("dcartes/Cxx.png" );


}

//---------------------------- Méthode nouvpartie --------------------------------

void Fenetre::nouvpartie() {

    // on réinitialise tous les paquets

    pioche.cartes.clear(); talon.cartes.clear();

    ncpio = 0;

    mainjou.cartes.clear(); mainordi.cartes.clear();

    ncjou = 0; ncordi = 0;

    // on crée la pioche

    vector<char> couleurs = {'b', 'j', 'r', 'v'};

    vector<char> valeurs = {'0', '1', '2', '3', '4', '5', '6', '7', '8',
                            '9' ,'+', 'i', 'p'};

    for (const char &couleur : couleurs) {

        for (const char &valeur : valeurs) {

            pioche.empile(Carte(couleur, valeur));

            // on double les cartes de couleur sauf le 0

            if ( valeur!= '0' ) pioche.empile(Carte(couleur,valeur));
        }

    }

    // on met 4 cartes noires de chaque valeur

    for ( int i=1; i < 5; i++ ) {

        pioche.empile(Carte('n','c'));        pioche.empile(Carte('n','+'));

    }

    // on mélange la pioche: on base le seed sur l'heure

    unsigned seed = chrono::system_clock::now().time_since_epoch().count();

    shuffle(pioche.cartes.begin(), pioche.cartes.end(), mt19937(seed));

    //  on désactive tous les signaux

    metclicoff(); metclicartes(false); metclicoul(false);

    zunoon = false; zinfoon = true;

    zavanon = true; zapreson = true;

    allumer('n'); // éteint les boutons de couleur

    //on cache éventuellement ztal, zordi, zcpio et ztour

    ui -> ztal -> hide();   ui -> zordi -> hide(); ui -> zcpio -> hide();

    ui -> zavan-> hide();  ui -> zapres-> hide();

    // on cache toutes les z[i]

    ui->z0->hide(); ui->z1->hide(); ui->z2->hide(); ui->z3->hide(); ui->z4->hide(); ui->z5->hide(); ui->z6->hide();
    ui->z7->hide(); ui->z8->hide(); ui->z9->hide(); ui->z10->hide(); ui->z11->hide(); ui->z12->hide(); ui->z13->hide();

    garnilabels(); ui->zcpio->show(); ui->zordi->show();

    // on indique qui donne au joueur

    if ( kidon== 1 ) ui->ztour-> setText ("À l'ordinateur de donner");

    else ui->ztour-> setText ("À vous de donner");

    acquitter("Cliquez ici pour commencer");

    if ( kidon== 1 ) ui->ztour-> setText ("L'ordinateur donne");

    else ui->ztour-> setText ("Vous donnez");

    ui -> zinfo -> setText("Distribution en cours");

    // On distribue 7 cartes à chaque joueur en alternant et en commençant par l'adversaire de kidon

    for (int i = 0; i < 7; ++i) {

        Carte c = pioche.depile();

        if (kidon == 2) {mainordi.empile(c); ncordi += 1;}

        else {mainjou.empile(c); garniz(c,i); ncjou += 1;}

        c = pioche.depile();

        if (kidon == 2 )  {mainjou.empile(c); garniz(c,i); ncjou += 1;}

        else {mainordi.empile(c); ncordi += 1;}

        // on affiche la carte qui vient dêtre donnée au joueur

        switch (i) {
        case 0 : ui->z0->repaint(); break;
        case 1 : ui->z1->repaint(); break;
        case 2 : ui->z2->repaint(); break;
        case 3 : ui->z3->repaint(); break;
        case 4 : ui->z4->repaint(); break;
        case 5 : ui->z5->repaint(); break;
        case 6 : ui->z6->repaint(); break;
        case 7 : ui->z7->repaint(); break;
        case 8 : ui->z8->repaint(); break;
        case 9 : ui->z9->repaint(); break;
        case 10 : ui->z10->repaint(); break;
        case 11 : ui->z11->repaint(); break;
        case 12 : ui->z12->repaint(); break;
        case 13 : ui->z13->repaint(); break;

        default : break;
        }

        garnilabels();         // on rafraichit l'affichage de zordi et zcpio

        QThread::sleep(1);     // on temporise 1 seconde pour que les cartes paraissent distribuées une à une

    }  // fin de la distribution

    // Tant que la carte au sommet de la pioche est une +4,
    //  on mélange la pioche

    Carte dessuspioche = pioche.dessus();       // on regarde le dessus de la pioche

    while (dessuspioche.val() == '+' && dessuspioche.coul() == 'n'){

        unsigned seed = chrono::system_clock::now().time_since_epoch().count();

        shuffle(pioche.cartes.begin(), pioche.cartes.end(), mt19937(seed));

        dessuspioche = pioche.dessus();
    }

    pioche.vers(talon);      // on retourne la 1ère carte du talon

    ui -> ztal -> show();   ui -> zordi -> show();

    ui -> zcpio -> show();  ui -> ztour -> show();

    // on initialise ndebor ( moins de 14 cartes dans la main du joueur ) puis on regarde à qui c'est le tour
    // de jouer en supposant que celui qui vient de jouer la carte sur le talon est kidon
    // on garnit ztour pour indiquer à qui c'est le tour

    ndebor = 0;   kijou = kidon;

    Carte c = talon.dessus(); coulatt = c.coul(); allumer(coulatt);

    this->repaint();

    akiltour();

    if (kijou==1) ui -> ztour->setText("Au tour de l'ordinateur");

    else  ui -> ztour->setText("A votre tour");

    ui -> zinfo -> setText(""); // on efface zinfo

    // on trie la main du joueur et on garnit les labels ztal, zordi et z[i] sans autoriser des clics

    trier(mainjou) ;

    garnilabels(); garnicartes(false,false);

}


//----------------------- Méthode choixcoul -----------------------------

// choix d'une couleur par kijou qui a joué une carte changement de couleur

void Fenetre::choixcoul() {


    if  ( kijou == 1 ) { ordichoixcoul();   // l'ordinateur doit choisir une couleur

        allumer(coulatt); this -> repaint();

    }

    else {  // le joueur choisit une couleur

        // on interdit tous les signaux sauf ceux sur zb, zj, zr, zv, zavan et zapres

        metclicoff();  zunoon = false ;    zinfoon = false ;

        isignal = 1;      // permet au joueur de naviguer dans sa main avant de choisir la couleur

        metclicoul(true);

        ui -> zinfo -> setText("Cliquez sur un bouton de couleur pour choisir une couleur");

        do {
            this -> repaint();

            QApplication::processEvents();

            // le joueur a la main tant qu'il ne clique pas sur un bouton de couleur
            // lorsque le joueur a cliqué sur un bouton de couleur, celui-ci est allumé 
            // et la couleur correspondante est mise dans coulatt

        } while (enfonc&&(isignal == 1));

        isignal = 1;

        metclicoul(false);  ui -> zinfo -> setText(""); // on efface zinfo

    }

}


//--------------------- Méthode changekijou ------------------------------------------

void Fenetre::changekijou() {

    if ( kijou ==  1 ) kijou =2; else kijou = 1;

    passe = false;
}

//---------------------- Méthode plus2 ------------------------------------------------

// distribue 2 cartes à l'adversaire de kijou en mettant à jour zordi si kijou = 2 et
// en signalant cette pénalité au joueur

void Fenetre::plus2 () {

    if ( kijou == 2 ) {

        kijou = 1;  // on met kijou temporairement à 1 pour faire piocher l'ordinateur

        piocher();  piocher();

        // ncordi ayant augmenté de 2, on regarnit zordi

        ui -> zordi -> setText(QString("L'ordinateur a %1 cartes en main").arg(ncordi));

        kijou = 2;            // on remet kijou à sa valeur initiale

    }

    else {

        kijou = 2;   //  on met kijou temporairement à 2 pour faire piocher le joueur

        int i = 0;

        while(i < mainjou.taille()) {
            i += 14;
        }

        ndebor = i - 14;

        metclicnav();

        garnicartes(false, false);

        ui -> zinfo -> setText("Distribution en cours");

        this -> repaint();

        QThread::sleep(1);

        piocher();

        if (ndebor + 14 < mainjou.taille()) {ndebor += 14; metclicnav();}

        garnicartes(false, false);

        this -> repaint();

        QThread::sleep(1);

        piocher();

        if (ndebor + 14 < mainjou.taille()) {ndebor += 14; metclicnav();}

        garnicartes(false, false);

        this -> repaint();

        QThread::sleep(1);

        kijou = 1;               // on remet kijou à sa valeur initiale

        trier(mainjou);          // on retrie mainjou qui a changé

        garnicartes(false , false);   // on regarnit les z[i] en interdisant les clics

        metclicnav();          // on autorise la navigation dans la main
    }

}

//-------------------------- Méthode plus4 ----------------------------------------

// distribue 4 cartes à l'adversaire de kijou en mettant à jour zordi si kijou = 2 et
// en signalant cette pénalité au joueur

void Fenetre::plus4 () {

    if ( kijou == 2 ) {

        kijou = 1;  // on met kijou temporairement à 1 pour faire piocher l'ordinateur

        piocher();  piocher();  piocher();  piocher();

        kijou = 2;            // on remet kijou à sa valeur initiale

        // ncordi ayant augmenté de 4, on regarnit zordi

        ui -> zordi -> setText(QString("L'ordinateur a %1 cartes en main").arg(ncordi));

    }

    else { 

        kijou = 2;              //  on met kijou temporairement à 2 pour faire piocher le joueur

        int i = 0;

        while(i < mainjou.taille()) {
            i += 14;
        }

        ndebor = i - 14;

        metclicnav();

        garnicartes(false, false);

        ui -> zinfo -> setText("Distribution en cours");

        this -> repaint();

        QThread::sleep(1);

        piocher();

        if (ndebor + 14 < mainjou.taille()) {ndebor += 14; metclicnav();}

        garnicartes(false, false);

        this -> repaint();

        QThread::sleep(1);

        piocher();

        if (ndebor + 14 < mainjou.taille()) {ndebor += 14; metclicnav();}

        garnicartes(false, false);

        this -> repaint();

        QThread::sleep(1);

        piocher();

        if (ndebor + 14 < mainjou.taille()) {ndebor += 14; metclicnav();}

        garnicartes(false, false);

        this -> repaint();

        QThread::sleep(1);

        piocher();

        if (ndebor + 14 < mainjou.taille()) {ndebor += 14; metclicnav();}

        garnicartes(false, false);

        this -> repaint();

        QThread::sleep(1);

        kijou = 1;              // on remet kijou à sa valeur initiale

        trier(mainjou);         // on retrie mainjou qui a changé

        garnicartes(false, false);     // on regarnit les z[i] en interdisant les clics

        metclicnav();          // on autorise la navigation dans la main
    }

}


//---------------------- Méthode akiltour -----------------------------------------------------

// si le talon est 'nc', on demande une couleur coulatt à kijou et la main passe à son adversaire

// si le talon est 'n+', kijou donne 4 cartes à son adversaire et garde la main

// sinon le talon est une carte de couleur :
//    si sa valeur est '+', kijou donne 2 cartes à son adversaire et garde la main
//    si cette valeur est 'i' ou 'p', kijou garde la main
//    sinon le talon est une carte "ordinaire", la main passe à l'adversaire de kijou

void Fenetre::akiltour() {

    Carte cartalon = talon.dessus();                 // cartalon est la carte au dessus du talon

    char coultalon = cartalon.coul();

    char valtalon = cartalon.val();

    string code = string() + cartalon.coul() + cartalon.val();

    QString qcode = QString::fromStdString(code);

    ui -> ztal->setPixmap(jeu[qcode]);               // on garnit ztal avec le dessus du talon

    switch  (coultalon)  {

    case   'n'   : choixcoul();                      // on demande à kijou de choisir une couleur

        if ( valtalon == '+' ) { plus4(); break; }   // kijou garde la main

        else { changekijou();break; }                // kijou perd la main après avoir choisi la couleur

    default : // le talon est une carte de couleur

        allumer(coultalon);                          // on allume le bouton de la couleur du talon

        coulatt = coultalon;

        switch  ( valtalon) {

        case  'i'   : break;         // kijou garde la main

        case  'p'   : break;        // kijou garde la main

        case  '+'   : plus2(); break;                // l'adversaire de kijou pioche 2 cartes et
                                                     // kijou garde la main

        default :  // le talon est une carte de couleur "ordinaire"

            changekijou();                           // kijou perd la main

            if ( kijou == 1 ) ui-> ztour -> setText(QString::fromStdString("Au tour de l'ordinateur"));

            else ui-> ztour -> setText(QString::fromStdString("A votre tour"));
        }
    }

    if ((ncjou==0)||(ncordi==0)) ui->ztour->setText("Fin de la partie");
}


//---------------------------- Méthode cartevalid -------------------------------------------

// paramètre : l'indice de la carte dans la main de kijou

// délivre un booléen égal à true ssi la carte est jouable compte-tenu de celle sur le talon

// pour cela, il faut qu'elle soit noire ou que sa couleur soit égale à coulatt ( couleur attendue qui
// peut être différente de la couleur de la carte sur le talon ) ou sinon, qu'elle ait la même valeur
// que celle de la carte sur le talon et alors, on change de couleur ( coulatt est mis à jour )

bool Fenetre::cartevalid( int i) {

    Carte cartatester;  Carte cartalon;

    if ( kijou == 1 )  cartatester = mainordi(i);

    else cartatester = mainjou(i);

    char coulatester = cartatester.coul();

    char valatester = cartatester.val();

    cartalon = talon.dessus(); char valatt = cartalon.val();

    bool ireturn;

    switch (coulatester )  {

    case   'n':  ireturn = true ; break;  // une carte noire est toujours jouable

    default  : if ( coulatester == coulatt ) ireturn = true;

        else ireturn = ( valatester == valatt );
    }

    return (ireturn);

}

//------------------ Méthode suitour ----------------------------------------

// enlève main(i) de main, l'empile sur talon; regarnit cartes affichées si kijou = 2

void Fenetre::suitour( Paquet &main,int i ) {

    Carte cartjouee = main(i);

    talon.empile(cartjouee);

    main.enleve(i);

    // si kijou est le joueur, on réaffiche sa main depuis le début

    if ( kijou== 2 ) {

        if(((main.taille())%14)==0) ndebor = 0;

        garnicartes(false,false);}

    garnilabels();

    this -> repaint();

}

//--------------------------- Méthode jouajoue ------------------------------

// la carte du joueur a été validée: elle correspond à l'indice icarte dans mainjou
// on enlève cette carte de mainjou, on la met sur le talon et ncjou -= 1
// si ncjou vaut 1, on regarde si le joueur a dit Uno

void Fenetre::jouajoue() {

    suitour(mainjou,icarte); garnicartes(false,false); metclicnav();

    ncjou -= 1;

    if ( ncjou == 1) {        // Le joueur n'a plus qu'une carte

        if ( !clicuno ) {     // et il n'a pas cliqué sur uno

            acquitter("Vous n'avez pas dit Uno ! Vous devez piocher une carte en cliquant ici");

            piocher();

            trier(mainjou);

            garnicartes(false, false);

            isignal = 3;
        }

        this -> repaint();
    }
}


//--------------------------- Méthode jouveujouer ------------------------------

// Le joueur veut jouer la carte d'indice iclic 
// On teste si sa carte est permise

void Fenetre::jouveujouer() {

    icarte = ndebor + iclic ;        // icarte est l'indice dans mainjou de la carte qu'il veut jouer

    if ( ! cartevalid(icarte ) ) {   // mais sa carte n'est pas permise

        ui -> zinfo -> setText("Vous devez jouer une carte permise");

        isignal = 1 ;                 

    }

    else {

        jouajoue();                 // sa carte est permise; il la joue
    }               

}

//------------------------- Méthode jouapioche ------------------------------

// Le joueur a pioché

void Fenetre::jouapioche() {

    ui -> zinfo -> setText("La carte piochée est la dernière montrée. Jouez la ou passez en cliquant ici");

    metclicoff(); metclicartes(false); metclicoul(false);

    zunoon = false ; zinfoon = true ; zavanon = false; zapreson = false;

    if (ncjou <= 2) {  zunoon = true; clicuno = false; }

    // calcul du ndebor correspondant à la fin de mainjou

    int i = 0;

    while(i < mainjou.taille()) {
        i += 14;
    }

    ndebor = i - 14;

    metclicnav();

    garnicartes(false,true);

    isignal = 1;  

    do {

    QApplication::processEvents();

    } while (enfonc&&((isignal == 1)||(isignal==0)));

    if ( isignal == 4 ) {

        passe = true ;

        trier(mainjou);

        garnicartes(false, false);

        this -> repaint();
    }// le joueur a passé


    else { icarte = ndebor + iclic ;   // icarte est l'indice dans mainjou de la carte piochée

        if (!cartevalid(icarte)) {

            acquitter("La carte piochée n'est pas permise ! Passez en cliquant ici");

            passe = true;

            isignal = 4;
        }

        else jouajoue(); 
    }
}

//---------------------- Méthode tourjou -----------------------------------

// le joueur a la main et joue un tour

void Fenetre::tourjou() {

    // on met off tous les signaux

    metclicoff(); metclicartes(false); metclicoul(false);

    zunoon = false ; zinfoon = false ;

    ui -> ztour -> setText(" A votre tour");

    ui -> zinfo -> setText("Jouez ou piochez en cliquant sur les zones correspondantes ");

    trier(mainjou); garnilabels();

    metclicnav();

    garnicartes(true,true); zpioon = true;

    this -> repaint();

    // on met zuno on si le joueur n'a plus que 2 cartes: il pourra cliquer uno

    if ( ncjou <= 2) {  zunoon = true; clicuno = false; }

    isignal=1;

    do { QApplication::processEvents();

        switch (isignal) {

            case 0 : break;                   // clic sur uno : clicuno a été mis à true

            case 1 : break;                   // navigation zavan et/ou zapres

            case 2 : jouapioche(); break;     // pioche

            default : jouveujouer();          // clic sur z[iclic]
        }

    } while (enfonc&&(isignal < 2));

    isignal = 1;
}


//-------------------------- Méthode choixcarte -----------------------------------

// choix d'une carte valide dans mainordi
// s'il y en a une, retourne son indice itrouv; sinon, retourne -1

int Fenetre::choixcarte() {

    int itrouv = -1 ;

    for ( int i =0; i < mainordi.taille() ; ++i )  {

        if ( cartevalid (i))  return itrouv ;

    } // fin du for : on n'a pas trouvé

    return itrouv;

}


//----------------------- Méthode chercher ------------------------------------

// trouve la 1ère carte dans mainordi dont la couleur est égale à celle en paramètre
// délivre l'indice itrouv de cette carte dans mainjou

int Fenetre::chercher( char coul ) {

    int itrouv = -1 ;

    for ( int i =0; i < mainordi.taille() ; ++i )  {

        Carte cart = mainordi(i) ;

        if ( cart.coul() == coul ) return i;

    } // fin du for : on n'a pas trouvé

    return -1;

}


//---------------------- Méthode tourordi -----------------------------------

// l'ordinateur a la main et joue un tour

void Fenetre::tourordi( ) {

    ui -> ztour->setText("Au tour de l'ordinateur");

    ui -> zinfo->setText("L'ordinateur est en train de jouer");

    this -> repaint();

    QThread::sleep(3);

    // recherche de la 1ère carte valide

    int i = 0; bool bcartjou = false; bool bcjsimpl = false;

    while ( ( i < mainordi.taille() )&&!bcartjou )  {

        if ( cartevalid(i) ) {

            if((mainordi(i).coul() != 'n')&&(mainordi(i).val() != '+')&&(mainordi(i).val() != 'p')&&(mainordi(i).val() != 'i')){
                bcjsimpl = true;
            }

            allumer(mainordi(i).coul());

            suitour(mainordi,i);         // si trouvée, on la joue

            ncordi -= 1; bcartjou = true;
        }

        i += 1;
    }

    if (!bcartjou){ piocher();

        int i = mainordi.taille() - 1;      // indice de la carte piochée

        if ( cartevalid(i) ) {

            allumer(mainordi(i).coul());

            suitour(mainordi,i);   // elle est valide donc on la joue

            ncordi -= 1;

            if ( ncordi < 2 ) ui -> zordi->setText(QString("L'ordinateur a %1 carte en main").arg(ncordi));

            else  ui -> zordi -> setText(QString("L'ordinateur a %1 cartes en main").arg(ncordi));

            if (ncordi==1) sonuno->play();

            this->repaint();
        }

        else { passe = true; }

    }

    if ( ncordi < 2 ) ui -> zordi->setText(QString("L'ordinateur a %1 carte en main").arg(ncordi));

    else  ui -> zordi->setText(QString("L'ordinateur a %1 cartes en main").arg(ncordi));

    this -> repaint();

    if ((bcartjou)&&(ncordi==1)) sonuno->play();

}

//----------------------- fonction classer ----------------------------------------------

// délivre un vecteur de taille 5 dont les éléments sont
// le nombre de cartes par couleur ( b,j,r,v,n ) dans la 
// main donnée en paramètre

vector<int> Fenetre::classer(Paquet main) {

    vector<int> compteurs(5, 0);

    for (int i = 0; i < main.taille(); ++i) {

        Carte carte = main(i);

        char couleur = carte.coul();

        switch (couleur) {
        case 'b': compteurs[0]++; break;
        case 'j': compteurs[1]++; break;
        case 'r': compteurs[2]++; break;
        case 'v': compteurs[3]++; break;
        case 'n': compteurs[4]++; break;

        default: break;
        }
    }
    return compteurs;
}

//---------------------- fonction ordichoixcoul -------------------------

// choix d'une couleur par l'ordinateur

void Fenetre::ordichoixcoul() {

    // on choisit la couleur dans laquelle l'ordinateur a le plus de cartes

    vector mordicoul = classer(mainordi);

    int nb =0; int j = 0;

    for ( int i = 0 ; i < 5 ; ++i ) {

        if (mordicoul[i] > nb ) { nb = mordicoul[i]; j= i; }

    } 

    switch (j) {

    case 0 : coulatt = 'b' ; break;

    case 1 : coulatt = 'j' ; break;

    case 2 : coulatt = 'r' ; break;

    case 3 : coulatt = 'v' ; break;

    default : coulatt = 'n';

    }

}
