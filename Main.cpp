#include "Random.h"

#include <iostream>
#include <limits>
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
    std::string m_word{WordList::getRandomWorld()};
    std::vector<char> m_letter{};

public:
    std::string_view getWord() const{return m_word;}

    std::vector<char> setLetter(char letter) {
        for (std::size_t i{0}; i < m_letter.size(); ++i) {
            m_letter[i] = letter;
        }
    }
};

void ignoreLine() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

char getUserInput(Session& s) {
    char input{};

    while (true) {
        std::cout << "Enter your next letter: ";
        std::cin >> input;

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

    s.setLetter(input);

    return input;
}

void draw(Session& s) {
    std::cout << "The word: ";

    for (auto i : s.getWord()) {
        std::cout << "_";
    }

    std::cout << '\n';
}

int main() {
    std::cout << "Welcome to C++man (a variant of Hangman)" << '\n';
    std::cout << "To win: guess the word.   To loss: run out of pluses." << '\n';

    Session s{};

    draw(s);
    getUserInput(s);
}