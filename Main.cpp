#include "Random.h"

#include <iostream>
#include <limits>
#include <algorithm>
#include <cctype>
#include <string>
#include <string_view>

namespace WordList{
    std::vector<std::string_view> word{"mystery", "broccoli", "account", "almost", "spaghetti", "opinion", "beautiful", "distance", "luggage"};

    std::string_view getRandomWorld() {
        return word[Random::get(0, word.size() - 1)];
    }
}

class Session {
private:
    //Game Datas
    std::string m_word{WordList::getRandomWorld()};
    std::vector<bool> m_isLetterGuessed {std::vector<bool>(26)};

    std::size_t toIndex(char input) const{return static_cast<std::size_t>((input % 32) - 1);}

public:
    std::string_view getWord() const{return m_word;}
    
    bool isLetterGuessed(char input) const{return m_isLetterGuessed[toIndex(input)];}
    void setLetterGuessed(char input) {m_isLetterGuessed[toIndex(input)] = true;}
};

void ignoreLine() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

char getUserInput(const Session& s) {
    char input{};

    while (true) {
        std::cout << "Enter your next letter: ";
        std::cin >> input;

        if (s.isLetterGuessed(input)) {
            std::cout << "You already guessed that. Try again." << '\n';

            std::cin.clear();
            ignoreLine();

            continue;
        }

        if (!std::cin) {
            std::cin.clear();
            ignoreLine();

            continue;
        }

        if (input < 61 || input > 172) {
            std::cout << "That was invalid input. Try again." << '\n';
            
            std::cin.clear();
            ignoreLine();

            continue;
        }

        break;
    }
    
    input = std::tolower(input);
    return input;
}

void draw(Session& s) {
    std::cout << "The word: ";

    //Display Word State
    for (auto i : s.getWord()) {
        if (s.isLetterGuessed(i)) {
            std::cout << i;
        }
        else {
            std::cout << "_";
        }
    }
    
    std::cout << '\t';

    //Display Wrong Guesses

    std::cout << '\n';
}

int main() {
    std::cout << "Welcome to C++man (a variant of Hangman)" << '\n';
    std::cout << "To win: guess the word.   To loss: run out of guesses." << '\n';

    Session s{};

    int attempts{10};

    while (--attempts) {
        draw(s);
        char userInput{getUserInput(s)};
        s.setLetterGuessed(userInput);

    }
    
    draw(s);

    std::cout << "You Lose! You ran out of guesses.";
}