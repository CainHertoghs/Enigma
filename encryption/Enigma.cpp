#include "Enigma.h"
#include <iostream>
#include <string.h>
#include <stdexcept>

namespace Encryption {

    Rotor::Rotor(const std::string& permutation)
    {
        if ((int)permutation.size() != 26) throw std::invalid_argument("permutation must be length 26");
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

    // PlugBoard implementations
    PlugBoard::PlugBoard()
    {
        for (int i = 0; i < 26; ++i) {
            permutations['A' + i] = 'A' + i;
        }
    }

    PlugBoard::PlugBoard(std::vector<std::pair<char, char>> connections) {
        // start identity
        for (int i = 0; i < 26; ++i) permutations['A' + i] = 'A' + i;
        for (const auto& pair : connections) {
            permutations[pair.first] = pair.second;
            permutations[pair.second] = pair.first;
        }
    }

    char PlugBoard::plugBoardMap(char input) const {
        auto it = permutations.find(input);
        if (it != permutations.end()) return it->second;
        return input;
    }

    std::vector<std::pair<char,char>> PlugBoard::getConnections() const {
        std::vector<std::pair<char,char>> out;
        std::array<bool,26> seen{};
        for (char a = 'A'; a <= 'Z'; ++a) {
            char b = permutations.at(a);
            if (a < b) {
                if (a != b) out.push_back({a,b});
            }
        }
        return out;
    }

    // Enigma implementation
    Enigma::Enigma(const Rotor& left, const Rotor& middle, const Rotor& right, const Reflector& reflector, const PlugBoard& plugBoard)
        : rotorLeft(left), rotorMiddle(middle), rotorRight(right), reflector(reflector), plugBoard(plugBoard)
    {
        leftStart = rotorLeft.getStartPosition();
        middleStart = rotorMiddle.getStartPosition();
        rightStart = rotorRight.getStartPosition();
    }

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
        size_t len = strlen(c);
        char * encrypted = new char[len + 1];
        for (size_t i = 0; i < len; i++)
        {
            encrypted[i] = this->encryptChar(c[i]);
        }
        encrypted[len] = '\0';
        return encrypted;
    }

    std::string Enigma::decryptString(const std::string& text)
    {
        // Enigma is symmetric — encryption == decryption
        // Work on a copy so rotor state outside stays unchanged
        Enigma copy = *this;
        std::string out;
        out.reserve(text.size());
        for (char ch : text) out.push_back(copy.encryptChar(ch));
        return out;
    }

    void Enigma::setPlugBoard(const PlugBoard& pb)
    {
        this->plugBoard = pb;
    }

    void Enigma::setRotorCurrentPositions(char left, char middle, char right)
    {
        rotorLeft.setCurrentPosition(left);
        rotorMiddle.setCurrentPosition(middle);
        rotorRight.setCurrentPosition(right);
    }

    void Enigma::setRotorStartPositions(char left, char middle, char right)
    {
        rotorLeft.setStartPosition(left);
        rotorMiddle.setStartPosition(middle);
        rotorRight.setStartPosition(right);
        leftStart = left; middleStart = middle; rightStart = right;
    }

    void Enigma::resetToStartPositions()
    {
        rotorLeft.setCurrentPosition(leftStart);
        rotorMiddle.setCurrentPosition(middleStart);
        rotorRight.setCurrentPosition(rightStart);
    }

    std::array<char,3> Enigma::getStartPositions() const {
        return {leftStart, middleStart, rightStart};
    }

    std::array<char,3> Enigma::getCurrentPositions() const {
        return {rotorLeft.getCurrentPosition(), rotorMiddle.getCurrentPosition(), rotorRight.getCurrentPosition()};
    }

} // namespace Encryption
