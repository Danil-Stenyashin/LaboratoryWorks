#include <gtest/gtest.h>
#include "Durak.cpp"

TEST(CardTest, CardCreation) {
    Card card(Suit::HEARTS, Rank::ACE);
    EXPECT_EQ(card.getSuit(), Suit::HEARTS);
    EXPECT_EQ(card.getRank(), Rank::ACE);
}

TEST(DeckTest, DeckHas36Cards) {
    Deck deck;
    int count = 0;
    while (!deck.empty()) {
        deck.dealCard();
        count++;
    }
    EXPECT_EQ(count, 36);
}

TEST(PlayerTest, PlayerReceivesCard) {
    Player player("TestPlayer");
    Card card(Suit::DIAMONDS, Rank::TEN);
    player.takeCard(card);
    
    EXPECT_TRUE(player.hasCards());
}

TEST(GameTest, CreateGame) {
    EXPECT_NO_THROW(Game game(4));
}

TEST(GameTest, DealCards) {
    Game game(4);
    EXPECT_NO_THROW(game.dealCards());
}

