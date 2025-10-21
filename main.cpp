//
// Created by cain on 21/10/2025.
//

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

    Reflector reflector = Reflector{"YRUHQSLDPXNGOKMIEBFZCWVJAT"};

    // Crib
    std::string crib = "DEOPGAVEVOORENIGMA";

}
