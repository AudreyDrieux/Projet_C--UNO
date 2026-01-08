cmake_minimum_required(VERSION 3.16)
project(Projet_UNO)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

# Bibliothèques
add_library(card src/Card.cpp)
add_library(pioche src/Pioche.cpp)
add_library(joueur src/Joueur.cpp)
add_library(jeu src/Jeu.cpp)

target_link_libraries(pioche PUBLIC card)
target_link_libraries(joueur PUBLIC card)
target_link_libraries(jeu PUBLIC card)

# Tests 
add_executable(test_card tests/test_Card.cpp)
target_link_libraries(test_card card)

add_executable(test_pioche tests/test_Pioche.cpp)
target_link_libraries(test_pioche card pioche)

add_executable(test_joueur tests/test_Joueur.cpp)
target_link_libraries(test_joueur card joueur pioche)

add_executable(uno_game src/main.cpp)
target_link_libraries(uno_game PRIVATE card joueur pioche jeu)
