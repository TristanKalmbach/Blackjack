#pragma once

#include "Common.h"

enum CardValues
{
    Ace = 0,
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King
};

class Card
{
public:
    Card(int suit, int value) : m_cardSuit(suit), m_cardValue(value), m_realValue(0) { }
    ~Card() { }

    // Get Set
    int GetSuit() const { return m_cardSuit; }
    void SetSuit(int suit) { m_cardSuit = suit; }
    int GetValue() const { return m_cardValue; }
    void SetValue(int value) { m_cardValue = value; }

    std::string GetNameFromValue(int value) const;
    std::string GetNameFromSuit(int suit) const;

    // Will output the details of the card.
    void PrintCardDetails(bool dealer);
    
#ifdef _WIN32
    // Handle text color.
    char* Color(int color = 7, char* Message = "") {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
        return Message;
    }
#endif

    // Will return true or false if the card is a face card.
    bool IsFaceCard() const;

private:
    int m_cardSuit;
    int m_cardValue;

    int m_realValue;
};

class Deck
{
public:
    Deck();
    ~Deck() { }

    void InitializeDeck();
    void ListDeckContents();
    void ShuffleDeck();

    Card DrawCard(bool identifyCard, bool dealer);

    // Get random element from container.
    Card GetRandomCard(boost::container::stable_vector<Card> cards);

    // Gets cards for iteration outside of class.
    boost::container::stable_vector<Card> GetCards() { return m_Cards; }

private:
    boost::container::stable_vector<Card> m_Cards;

};
