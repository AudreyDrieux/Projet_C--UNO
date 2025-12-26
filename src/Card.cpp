#include <iostream>
#include "Card.hpp"
#include <string>


void Card::affiche()const{
    if(spec == "p"){
        std::cout << "[" << color << ", passe ton tour ]" << std::endl;
    }
    else{                    
        std::cout << "[" << color << ", " << spec  << "]" << std::endl; 
    }
    };

std::string Card::numero()const{
    return spec;
};

std::string Card::numero(){
    return spec;
}

std::string Card::colorcard()const{
    return color;
};

std::string Card::colorcard(){
    return color;
}

bool Card::superpose(const Card& C2)const{
    std::string numC2=C2.numero();
    std::string colC2=C2.colorcard();
    return (spec == numC2) || (color==C2.color);
};

bool Card::operator==(const Card& C)const{
    return (color == C.colorcard()) && (spec == C.numero());
};

Card& Card::operator=(const Card& card){
    if(this == &card){
        return *this;
    }
    spec = card.numero();
    color = card.colorcard();
    return *this;
}