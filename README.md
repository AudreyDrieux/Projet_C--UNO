# Projet_C--UNO

### Installation
Pour installer le programme, téléchargez l'ensemble du contenu de la branche main.

### Tests
Catch2 v3 doit être installé pour compiler les tests.
1. Placez votre terminal dans le dossier qui contient l'ensemble du programme.
2. tapez dans votre terminal:    
- `cmake -B build -G "MinGW Makefiles" -DCMAKE_CXX_COMPILER="C:/MinGW/bin/g++.exe"`    
- Pour lancer les tests, utilisez  
`cmake --build build --target **test_card**` 
`cmake --build build --target **test_pioche**`
`cmake --build build --target **test_joueur**`   

## Partie
Pour commencer une partie, placez votre terminal dans le dossier qui contient l'ensemble du programme.
La première fois, executer les commandes `cmake -B build` puis `cmake --build build --target uno_game` dans votre terminal.

Pour démarrer la partie, executer la commande `build\uno_game.exe` .

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
  
