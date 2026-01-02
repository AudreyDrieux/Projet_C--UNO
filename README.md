# Projet_C--UNO

Le projet utilise CMake. Aucune bibliothèque externe n'est requise.

## Installation
Pour installer le programme, téléchargez l'ensemble du contenu de la branche main.
  
## Tests
Les tests utilisent Catch2.
1. Placez votre terminal à la racine du projet.
2. tapez dans votre terminal:     
- __Windows:__ `cmake -B build -G "MinGW Makefiles"`  __Linux/Mac:__  `cmake -B build`  
- Pour lancer les tests, utilisez    
`cmake --build build --target test_card`  
__Windows:__ `./build/test_card.exe`  __Linux/Mac:__ `./build/test_card`
`cmake --build build --target test_pioche`  
__Windows:__`./build/test_pioche.exe`  __Linux/Mac:__ `./build/test_pioche`
`cmake --build build --target test_joueur`   
__Windows:__`./build/test_joueur.exe` __Linux/Mac:__ `./build/test_joueur`   

## Documentation
Pour générer la documentation technique du projet :
1. Installez Doxygen.
2. Lancez la commande `doxygen Doxyfile`.
3. Ouvrez `html/index.html` dans votre navigateur.
 

## Partie
Pour commencer une partie, placez votre terminal dans le dossier qui contient l'ensemble du programme.
La première fois, executer les commandes `cmake -B build` puis `cmake --build build --target uno_game` dans votre terminal.

Pour démarrer la partie, executer la commande __Windows:__`./build/uno_game.exe` , __Linux/Mac:__ `./build/uno_game` .

### **Jeu** *sans interface graphique*
Les cartes sont représentées ainsi: [*couleur*, *numéro*]  
Les couleurs disponibles sont jaune (J), rouge (R), vert (V), bleu (B) et noir (N).
un jeu contient, pour chaque couleur, sauf noir:  
- une carte 0
- deux cartes pour chaque nombre de 1 à 9 
- deux cartes '+2' [*couleur*, '+2'] 
- deux cartes 'passer' [*couleur*, 'p']  

La couleur noir n'est valable que pour la spécialité '+4'.  
Lorsqu'une carte '+2' est jouée, l'adversaire pioche 2 cartes.  
Lorsqu'une carte 'passer' est jouée, le joueur rejoue.  
Lorsqu'une carte '+4' est jouée, le joueur choisit la couleur qu'il souhaite jouer et rejoue. 
Une carte '+4' peut se jouer n'importe quand. En revanche, toutes les autres cartes  ne peuvent se jouer que lorsqu'au moins la couleur ou le numéro/la spécialité coïncide avec celui de la carte au sommet du talon.  

Au début de chaque tour, le talon s'affiche. Par exemple:  
talon : [J, 1]  
  
#### Joueur interactif
Si c'est à votre tour, toutes vos cartes s'affichent.  
Si au moins l'une de vos cartes peut être jouée, il vous est demandé d'en sélectionner une: vous devez commencer par choisir la couleur: (**J**, **R**, **V**, **B** ou **N**) puis le nombre/la spécialité (**0** à **9**, **+2**, **p** ou **+4**). Si elle est valide, elle sera posée sur le talon et s'il ne s'agit pas d'une carte "spéciale", le tour sera passé à l'ordinateur.  
Si vous avez une carte valide mais que vous souhaitez tout de même passer votre tour, tapez "pass" lorsque la couleur vous est demandée.  
Si vous n'avez pas de carte valide, vous piochez une carte. Si la carte piochée est valide, il vous sera demandé si vous souhaitez la jouer: tapez 1 dans le terminal si vous souhaitez la jouer, 0 sinon. Si la carte piochée n'est pas valide, le tour sera passée à votre adversaire.  

#### Jeu de l'ordinateur
Lorsque c'est à l'ordinateur de jouer, s'il possède une carte valide, le nombre de carte qu'il possède s'affiche puis la carte qu'il joue. S'il ne possède pas de carte valide, il pioche et *adversaire pioche* est affiché

#### 1 carte restante
Si vous ne possedez plus qu'une seule carte, vous disposez de 10 secondes pour écrire dans le terminal "UNO" ou "uno". Si vous avez mis plus de 10 secondes, votre adversaire contre votre UNO et vous devez piocher 2 cartes.  
Si votre adversaire ne poosède plus qu'une seule carte, vous disposez de 10 secondes pour écrire "contre UNO"  ou "contre uno". Si vous avez mis moins de 10 secondes, votre adversaire pioche 2 cartes. 
  
#### Fin de la partie
La partie s'arrête lorsque l'un des deux joueurs ne possède plus aucune carte ou lorsque la pioche est vide.

## Installation de l'interface graphique 
Télécharger le dossier Uno. Dans ce dossier, vous trouverez :
1. un dossier dcartes dans lequel se trouve les images des cartes du jeu de Uno ainsi qu'un fichier son utilisé par le programme;
2. un fichier CMakeLists.txt;
3. un fichier d'en tête uno.h;
4. deux fichiers sources uno.cpp et main.cpp;
5. un fichier uno.ui qui correspond à l'interface de la fenêtre;
6. trois fichiers pdf : Notice_installation_Qt.pdf, Compilation_et_execution_dans_QtCreator.pdf, Utilisation_programme_uno.pdf.

Pour lancer le programme uno, vous devez dans un premier temps installer le logiciel Qt. Pour ce faire, suiver les instructions indiquées dans le pdf Notice_installation_Qt.pdf.
Après avoir installé le logiciel Qt, suivre les instructions du pdf Compilation_et_execution_dans_QtCreator.pdf pour compiler et exécuter le programme uno.
Enfin, une notice d'utilisation détaillée du programme est disponible dans le fichier Utilisation_programme_uno.pdf.

  
