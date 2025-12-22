#include <iostream>
#include "Card.hpp"

void Card::affiche()const{
    switch(spec){
        case "p":
            std::cout << "[" << color << ", passe ton tour ]" << std::endl;
            break;
        case "+2":
            std::cout << "[ " << color <<", +2 ]" << std::endl;
            break;
        default:                    
            std::cout << "[" << color << ", " << spec  << "]" << std::endl; 
        };
    };

std::string Card::numero()const{
    return spec;
};

std::string Card::colorcard()const{
    return color;
};

bool Card::superpose(const Card& C2)const{
    std::string numC2=C2.numero();
    std::string col=C2.colorcard();
    return (numC2 == spec) || (color==C2.color);
};