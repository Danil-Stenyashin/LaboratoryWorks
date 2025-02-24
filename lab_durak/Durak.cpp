#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

enum Rank {TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE};
enum Suit {CLUBS, DIAMONDS, HEARTS, SPADES};

class Card {
public:
    Card(Suit suit, Rank rank): suit(suit), rank(rank) {}
    
    void printCard() const { // Вывод карты
        std::string suits[] = {"CLUBS", "DIAMONDS", "HEARTS", "SPADES"};
        std::string ranks[] = {"","","2","3","4","5","6","7","8","9","10","Jack","Quenn","King","Ace"}; // Нумерация ранков, 2 пустые строчки для удобной сортировки
        std::cout << ranks[rank] << "of" << suits[suit] << std::endl;
    }
    
    Rank getRank() const { return rank;}
    Suit getSuit() const { return suit;}
 
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
      std::srand(static_cast<unsigned int>(std::time(0)));
      std::random_shuffle(cards.begin(), cards.end());
   }       
 
   Card dealCard() {
      if (cards.empty()) {
          std::cerr << "No more cards!" << std::endl;
          exit(1);
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
   void addCard(Card card) {
      hand.push_back(card);
   }
   
   void showCard() const {
       std::cout << "You have: \n";
       for (const auto& card: hand) {
          card.printCard();
       }
   }

   bool hasCard() const {
         return !hand.empty();
   }
   
private:
   std::vector<Card> hand;
}; 
   
void game() {
   Deck deck;
   deck.shuffle();
   
   Player player1;
   for (int i = 0; i < 6; ++i){
      player1.addCard(deck.dealCard());
  }
  player1.showCard();
};

  
int main(){
   game();
   return 0;
};
   
   
   

   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
