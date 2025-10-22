//
// Created by cain on 21/10/2025.
//

#include <iostream>
#include <ostream>

#include "encryption/Enigma.h"

using namespace Encryption;

int main()
{

    // Rotors and reflectors initialized (see assignment)
    Rotor rotor0 = Rotor{"AJDKSIRUXBLHWTMCQGZNPYFVOE"};
    Rotor rotor1 = Rotor{"EKMFLGDQVZNTOWYHXUSPAIBRCJ"};
    Rotor rotor2 = Rotor{"BDFHJLCPRTXVZNYEIWGAKMUSQO"};
    Rotor rotor3 = Rotor{"THEQUICKBROWNFXJMPSVLAZYDG"};
    Rotor rotor4 = Rotor{"XANTIPESOKRWUDVBCFGHJLMQYZ"};

    rotor0.setStartPosition('A');
    rotor1.setStartPosition('A');
    rotor2.setStartPosition('A');

    Reflector reflector = Reflector{"YRUHQSLDPXNGOKMIEBFZCWVJAT"};

    // Crib
    std::string crib = "DEOPGAVEVOORENIGMA";


    Enigma enigma = Enigma(rotor2, rotor1, rotor0, reflector);

    char * c = enigma.encrypt("GOEDEMORGEN");
    std::cout << c << std::endl;

}
