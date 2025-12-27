cmake_minimum_required(VERSION 3.16)
project(Projet_UNO)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_PREFIX_PATH "$ENV{USERPROFILE}/local/install_catch2")

find_package(Catch2 3 REQUIRED)


include_directories(include)
add_library(card src/Card.cpp)
add_library(pioche src/Pioche.cpp)
add_library(joueur src/Joueur.cpp)
add_library(jeu src/Jeu.cpp)

add_executable(test_card tests/test_Card.cpp)
add_executable(test_pioche tests/test_Pioche.cpp)
add_executable(test_joueur tests/test_Joueur.cpp)
add_executable(uno_game src/main.cpp)

target_link_libraries(test_card card Catch2::Catch2WithMain)
target_link_libraries(test_pioche pioche Catch2::Catch2WithMain)
target_link_libraries(pioche PUBLIC card)
target_link_libraries(test_joueur joueur Catch2::Catch2WithMain)
target_link_libraries(joueur PUBLIC card)
target_link_libraries(jeu PUBLIC card)
target_link_libraries(uno_game PRIVATE joueur pioche jeu)