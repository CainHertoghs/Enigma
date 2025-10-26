#ifndef ENIGMA_H
#define ENIGMA_H

#include <map>
#include <string>
#include <vector>
#include <array>

namespace Encryption {

    class Rotor
    {
        std::map<char, char> permutations;
        std::map<char, char> reversePermutations;
        char startPosition;
        char currentPosition;

    public:
        explicit Rotor(const std::string& permutation);

        void setStartPosition(char startPosition);
        void setCurrentPosition(char currentPosition);
        char getStartPosition() const;
        char getCurrentPosition() const;

        void rotate();

        char mapForward(char input) const;

        char mapBackward(char input) const;
    };


    class Reflector
    {
        std::map<char, char> permutations;

    public:
        explicit Reflector(const std::string& permutation);
        char reflect(char input) const;
    };

    class PlugBoard
    {
        std::map<char, char> permutations;
    public:
        PlugBoard(); // identity
        PlugBoard(std::vector<std::pair<char, char>> connections);

        char plugBoardMap(char input) const;
        std::vector<std::pair<char,char>> getConnections() const;
    };


    class Enigma
    {
        Rotor rotorLeft;
        Rotor rotorMiddle;
        Rotor rotorRight;
        Reflector reflector;
        PlugBoard plugBoard;

        // store start positions for reset
        char leftStart;
        char middleStart;
        char rightStart;

    public:
        Enigma(const Rotor& left, const Rotor& middle, const Rotor& right, const Reflector& reflector, const PlugBoard& plugBoard);

        // encryption/decryption of single char (affects rotor positions)
        char encryptChar(char c);

        // encrypt C-string, returns a null-terminated heap buffer (caller must delete[])
        char* encrypt(const char *c);

        // safer string-based decrypt/encrypt helpers:
        std::string decryptString(const std::string& text);

        // New utility API used by Bombe:
        void setPlugBoard(const PlugBoard& pb);
        void setRotorCurrentPositions(char left, char middle, char right);
        void setRotorStartPositions(char left, char middle, char right);
        void resetToStartPositions();

        // convenience: get start positions
        std::array<char,3> getStartPositions() const;
        std::array<char,3> getCurrentPositions() const;
    };

} // namespace Encryption

#endif //ENIGMA_H
