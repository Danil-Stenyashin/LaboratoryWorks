#include "Durak.cpp"

int main() {
    int numPlayers;
    std::cout << "Введите количество игроков (2-6): ";
    std::cin >> numPlayers;

    if (numPlayers < 2 || numPlayers > 6) {
        std::cout << "Ошибка! Количество игроков должно быть от 2 до 6.\n";
        return 1;
    }

    Game game(numPlayers);
    game.start();

    return 0;
}

