#include "Enigma.h"
#include <iostream>

namespace Encryption {

    Rotor::Rotor(const std::string& permutation)
    {
        for (int i = 0; i < permutation.length(); i++)
        {
            permutations[permutation[i]] = permutation[(i+1) % permutation.length()] ;
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
        for (int i = 0; i < permutation.length(); i += 2)
        {
            char a = permutation[i];
            char b = permutation[i + 1];
            permutations[a] = b;
            permutations[b] = a;
        }
    }

    char Reflector::reflect(char input) const
    {
        return permutations.at(input);
    }

    Enigma::Enigma(const Rotor& left, const Rotor& middle, const Rotor& right, const Reflector& reflector)
        : rotorLeft(left), rotorMiddle(middle), rotorRight(right), reflector(reflector) {}

    char Enigma::encrypt(char c)
    {
        if (c < 'A' || c > 'Z') return c;

        rotorRight.rotate();

        char signal = rotorRight.mapForward(c);
        signal = rotorMiddle.mapForward(signal);
        signal = rotorLeft.mapForward(signal);

        signal = reflector.reflect(signal);

        signal = rotorLeft.mapBackward(signal);
        signal = rotorMiddle.mapBackward(signal);
        signal = rotorRight.mapBackward(signal);

        return signal;
    }

} // namespace Encryption
