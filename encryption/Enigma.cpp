#include "Enigma.h"
#include <iostream>
#include <string.h>

namespace Encryption {

    Rotor::Rotor(const std::string& permutation)
    {
        for (int i = 0; i < 26; i++)
        {
            permutations['A' + i] = permutation[i] ;
            reversePermutations[permutation[i]] = 'A' + i;
        }
        startPosition = 'A';
        currentPosition = 'A';
    }

    void Rotor::setStartPosition(char startPosition)
    {
        this->startPosition = startPosition;
        this->currentPosition = startPosition;
    }

    void Rotor::setCurrentPosition(char currentPosition)
    {
        this->currentPosition = currentPosition;
    }

    char Rotor::getStartPosition() const { return this->startPosition; }

    char Rotor::getCurrentPosition() const { return this->currentPosition; }

    void Rotor::rotate()
    {
        currentPosition = (currentPosition == 'Z') ? 'A' : currentPosition + 1;
    }

    static char shiftChar(char c, int shift)
    {
        int offset = (c - 'A' + shift + 26) % 26;
        return 'A' + offset;
    }

    char Rotor::mapForward(char input) const
    {
        int shift = currentPosition - 'A';
        char shiftedIn = shiftChar(input, shift);
        char mapped = permutations.at(shiftedIn);
        char shiftedOut = shiftChar(mapped, -shift);
        return shiftedOut;
    }

    char Rotor::mapBackward(char input) const
    {
        int shift = currentPosition - 'A';
        char shiftedIn = shiftChar(input, shift);
        char mapped = reversePermutations.at(shiftedIn);
        char shiftedOut = shiftChar(mapped, -shift);
        return shiftedOut;
    }


    Reflector::Reflector(const std::string& permutation)
    {
        for (int i = 0; i < 26; i++)
        {
            permutations['A' + i] = permutation[i];
        }
    }

    char Reflector::reflect(char input) const
    {
        return permutations.at(input);
    }

    Enigma::Enigma(const Rotor& left, const Rotor& middle, const Rotor& right, const Reflector& reflector, const PlugBoard& plugBoard)
        : rotorLeft(left), rotorMiddle(middle), rotorRight(right), reflector(reflector), plugBoard(plugBoard) {}

    char Enigma::encryptChar(char c)
    {
        if (c < 'A' || c > 'Z') return c;

        char signal = plugBoard.plugBoardMap(c);

        signal = rotorRight.mapForward(signal);
        signal = rotorMiddle.mapForward(signal);
        signal = rotorLeft.mapForward(signal);

        signal = reflector.reflect(signal);

        signal = rotorLeft.mapBackward(signal);
        signal = rotorMiddle.mapBackward(signal);
        signal = rotorRight.mapBackward(signal);

        signal = plugBoard.plugBoardMap(signal);

        rotorRight.rotate();
        if (rotorRight.getCurrentPosition() == 'A')
        {
            rotorMiddle.rotate();
            if (rotorMiddle.getCurrentPosition() == 'A')
            {
                rotorLeft.rotate();
            }
        }

        return signal;
    }

    char* Enigma::encrypt(const char* c)
    {
        char * encrypted = new char[strlen(c) + 1];
        for (int i = 0; i < strlen(c); i++)
        {
            encrypted[i] = this->encryptChar(c[i]);
        }

        return encrypted;
    }

    PlugBoard::PlugBoard(std::vector<std::pair<char, char>> connections) {
        for (const auto& pair : connections) {
            permutations[pair.first] = pair.second;
            permutations[pair.second] = pair.first;
        }
    }

    char PlugBoard::plugBoardMap(char input) {
        if (permutations.find(input) != permutations.end()) {
            return permutations[input];
        }
        return input;
    }
} // namespace Encryption
