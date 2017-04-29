#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <memory>
#include <random>
#include <iterator>
#include <windows.h>

#define MAX_DECK_SIZE 52
#define MAX_SUITS 4
#define MAX_VALUE 13

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
    
    // Handle text color.
    char* Color(int color = 7, char* Message = "") {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
        return Message;
    }

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

    // Handle random elements.
    template<typename Iter, typename RandomGenerator>
    auto select_randomly(Iter start, Iter end, RandomGenerator& g) {
        std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
        std::advance(start, dis(g));
        return start;
    }

    template<typename Iter>
    auto select_randomly(Iter start, Iter end) {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        return select_randomly(start, end, gen);
    }

private:
    std::vector<Card> m_Cards;

};

