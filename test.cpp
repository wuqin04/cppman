#include <vector>
#include <iostream>

int main() {
    std::vector<bool> m_letterGuessed { std::vector<bool>(26) };

    std::cout << m_letterGuessed.size();
}