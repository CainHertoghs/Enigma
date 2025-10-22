#ifndef ENIGMA_H
#define ENIGMA_H

#include <map>
#include <string>

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

        // explicit PlugBoard(const std::string& permutation);
        //
        // char plugBoardMap(char input);
    };


    class Enigma
    {
        Rotor rotorLeft;
        Rotor rotorMiddle;
        Rotor rotorRight;
        Reflector reflector;

    public:
        Enigma(const Rotor& left, const Rotor& middle, const Rotor& right, const Reflector& reflector);

        char encryptChar(char c);

        char* encrypt(const char *c);
    };

} // namespace Encryption

#endif //ENIGMA_H
