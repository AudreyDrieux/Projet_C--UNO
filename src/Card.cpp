#include <iostream>
#include "Card.hpp"

void Card::affiche()const{
    switch(num){
        case 10:
            std::cout << "[" << color << ", passe ton tour ]" << std::endl;
            break;
        case 11:
            std::cout << "[ " << color <<", +2 ]" << std::endl;
            break;
        default:                    
            std::cout << "[" << color << ", " << num  << "]" << std::endl; 
        };
    };

int Card::numero()const{
    return num;
};

std::string Card::colorcard()const{
    return color;
};

bool Card::superpose(const Card& C2)const{
    int numC2=C2.numero();
    std::string col=C2.colorcard();
    return (numC2 == num) || (color==C2.color);
};