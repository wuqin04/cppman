#include "Random.h"

#include <iostream>
#include <limits>
#include <algorithm>
#include <cctype>
#include <string>
#include <string_view>

namespace Settings{
    constexpr int wrongGuessAllowed{10};
}

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

    int m_wrongGuessLeft{Settings::wrongGuessAllowed};

    std::size_t toIndex(char input) const{return static_cast<std::size_t>((input % 32) - 1);}

public:
    std::string_view getWord() const{return m_word;}

    int wrongGuessLeft() const{return m_wrongGuessLeft;}
    void removeGuess() {--m_wrongGuessLeft;}

    
    bool isLetterGuessed(char input) const{return m_isLetterGuessed[toIndex(input)];}
    void setLetterGuessed(char input) {m_isLetterGuessed[toIndex(input)] = true;}

    bool isLetterInWord(char input) const{
        for (auto i : m_word) {
            if (i == input) {
                return true;
            }
        }

        return false;
    }

    bool won() {
        for (auto i : m_word) {
            if (!isLetterGuessed(i)) {
                return false;
            }
        }

        return true;
    }
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

        return input;
    }
}

void draw(const Session& s) {
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
    std::cout << "Wrong Guesses: ";
    for (int i{0}; i < s.wrongGuessLeft(); ++i) {
        std::cout << "+";
    }

    for (char input{'a'}; input <= 'z'; ++input) {
        if (s.isLetterGuessed(input) && !s.isLetterInWord(input)) {
            std::cout << input;
        }
    }

    std::cout << '\n';
}

void handleGuess(Session& s, char input) {
    s.setLetterGuessed(input);

    if (s.isLetterInWord(input)) {
        std::cout << "Yes, " << input << " is in the word!\n\n";
        return;
    }

    std::cout << "No, " << input << " is not in the word!\n\n";
    s.removeGuess();
} 

int main() {
    std::cout << "Welcome to C++man (a variant of Hangman)" << '\n';
    std::cout << "To win: guess the word.   To loss: run out of guesses." << '\n';

    Session s{};

    while (s.wrongGuessLeft() && !s.won()) {
        draw(s);
        char input{getUserInput(s)};
        handleGuess(s, input);
    }

    draw(s);

    if (!s.wrongGuessLeft()) {
        std::cout << "You lost! The word was: " << s.getWord() << '\n';
    }
    else {
        std::cout << "You won!\n";
    }
}