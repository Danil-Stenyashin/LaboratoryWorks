#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <algorithm>
#include <optional>

enum Rank {TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE};
enum Suit {CLUBS, DIAMONDS, HEARTS, SPADES};

class Card {
public:
    Card(Suit suit, Rank rank) : suit(suit), rank(rank) {}

    void printCard() const {
        std::string suits[] = {"CLUBS", "DIAMONDS", "HEARTS", "SPADES"};
        std::string ranks[] = {"", "", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};
        std::cout << ranks[rank] << " of " << suits[suit] << std::endl;
    }

    Rank getRank() const { return rank; }
    Suit getSuit() const { return suit; }

private:
    Suit suit;
    Rank rank;
};

class Deck {
public:
    Deck() {
        for (int suit = 0; suit < 4; ++suit) {
            for (int rank = 2; rank <= 14; ++rank) {
                cards.push_back(Card(static_cast<Suit>(suit), static_cast<Rank>(rank)));
            }
        }
    }

    void shuffle() {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(cards.begin(), cards.end(), g);
    }

    Card dealCard() {
        if (cards.empty()) {
            throw std::out_of_range("No more cards in the deck!");
        }
        Card card = cards.back();
        cards.pop_back();
        return card;
    }

private:
    std::vector<Card> cards;
};

class Player {
public:
    Player(std::string name) : name(name) {}

    void addCard(Card card) {
        hand.push_back(card);
    }

    void showCards() const {
        std::cout << name << " has:\n";
        for (const auto& card : hand) {
            card.printCard();
        }
    }

    bool hasCards() const {
        return !hand.empty();
    }

private:
    std::string name;
    std::vector<Card> hand;
};




class Game {
public:
    Game(int numPlayers) {
        if (numPlayers < 2 || numPlayers > 6) {
            throw std::invalid_argument("Количество игроков должно быть от 2 до 6.");
        }
        deck.shuffle();

        for (int i = 0; i < numPlayers; ++i) {
            players.emplace_back("Player " + std::to_string(i + 1));
        }

        dealCards();
        determineTrump();
        findFirstAttacker();
    }

    void dealCards() {
        const int CARDS_PER_PLAYER = 6;
        for (int i = 0; i < CARDS_PER_PLAYER; ++i) {
            for (auto& player : players) {
                player.addCard(deck.dealCard());
            }
        }
    }

    void determineTrump() {
        trumpCard = deck.dealCard();
        trumpSuit = trumpCard.getSuit();
        std::cout << "Козырь: ";
        trumpCard.printCard();
        std::cout << std::endl;
    }

    void findFirstAttacker() {
        std::optional<int> firstPlayer;
        Rank minTrumpRank = ACE;

        for (size_t i = 0; i < players.size(); ++i) {
            for (const auto& card : players[i].getHand()) {
                if (card.getSuit() == trumpSuit && card.getRank() < minTrumpRank) {
                    minTrumpRank = card.getRank();
                    firstPlayer = i;
                }
            }
        }

        attackerIndex = firstPlayer.value_or(0);
        defenderIndex = (attackerIndex + 1) % players.size();

        std::cout << players[attackerIndex].getName() << " ходит первым.\n";
    }

    void start() {
        std::cout << "Игра началась!\n";
        showPlayersCards();

        while (players.size() > 1) {
            playTurn();
        }

        std::cout << "Игра окончена! Победитель: " << players[0].getName() << std::endl;
    }

private:
    Deck deck;
    std::vector<Player> players;
    Card trumpCard;
    Suit trumpSuit;
    int attackerIndex = 0;
    int defenderIndex = 1;

    void showPlayersCards() const {
        for (const auto& player : players) {
            player.showCards();
            std::cout << "----------------\n";
        }
    }

    void playTurn() {
        Player& attacker = players[attackerIndex];
        Player& defender = players[defenderIndex];

        if (!attacker.hasCards()) {
            std::cout << attacker.getName() << " выиграл!\n";
            players.erase(players.begin() + attackerIndex);
            return;
        }

        std::cout << attacker.getName() << " атакует!\n";
        Card attackCard = attacker.playCard(); 
        attackCard.printCard();

        std::cout << defender.getName() << " защищается!\n";
        Card defenseCard = defender.defend(attackCard, trumpSuit);

        if (defenseCard.getRank() != TWO) {
            std::cout << defender.getName() << " отбился картой ";
            defenseCard.printCard();
        } else {
            std::cout << defender.getName() << " не смог отбиться и берёт карту.\n";
            defender.addCard(attackCard);
        }

        attackerIndex = (attackerIndex + 1) % players.size();
        defenderIndex = (attackerIndex + 1) % players.size();
    }
};
