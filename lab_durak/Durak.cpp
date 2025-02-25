#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

// ------------------- Карты -------------------
enum class Suit { CLUBS, DIAMONDS, HEARTS, SPADES };
enum class Rank { SIX = 6, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE };

class Card {
public:
    Card(Suit s, Rank r) : suit(s), rank(r) {}

    void print() const {
        const std::string suits[] = {"♣", "♦", "♥", "♠"};
        const std::string ranks[] = {"", "", "", "", "", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
        std::cout << ranks[static_cast<int>(rank)] << suits[static_cast<int>(suit)] << " ";
    }

    Suit getSuit() const { return suit; }
    Rank getRank() const { return rank; }

private:
    Suit suit;
    Rank rank;
};

// ------------------- Колода -------------------
class Deck {
public:
    Deck() {
        for (int s = 0; s < 4; ++s) {
            for (int r = 6; r <= 14; ++r) {
                cards.emplace_back(static_cast<Suit>(s), static_cast<Rank>(r));
            }
        }
        shuffle();
    }

    void shuffle() {
        std::srand(static_cast<unsigned int>(std::time(0)));
        std::random_shuffle(cards.begin(), cards.end());
    }

    Card dealCard() {
        if (cards.empty()) throw std::runtime_error("Колода пуста!");
        Card card = cards.back();
        cards.pop_back();
        return card;
    }

    bool empty() const { return cards.empty(); }

private:
    std::vector<Card> cards;
};

// ------------------- Игрок -------------------
class Player {
public:
    Player(std::string n) : name(n) {}

    void takeCard(Card card) { hand.push_back(card); }

    void showHand() const {
        std::cout << name << ": ";
        for (const auto& card : hand) card.print();
        std::cout << std::endl;
    }

    std::string getName() const { return name; }
    bool hasCards() const { return !hand.empty(); }

private:
    std::string name;
    std::vector<Card> hand;
};

// ------------------- Игра -------------------
class Game {
public:
    Game(int numPlayers) {
        for (int i = 1; i <= numPlayers; ++i) {
            players.emplace_back("Игрок " + std::to_string(i));
        }
        dealCards();
    }

    void dealCards() {
        for (int i = 0; i < 6; ++i) {
            for (auto& player : players) {
                if (!deck.empty()) player.takeCard(deck.dealCard());
            }
        }
    }

    void showPlayers() const {
        for (const auto& player : players) {
            player.showHand();
        }
    }

    void start() {
        std::cout << "Игра началась!\n";
        showPlayers();
        std::cout << "\n";
    }

private:
    Deck deck;
    std::vector<Player> players;
};

