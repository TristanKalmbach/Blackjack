#include "Card.h"

import std.core;
import std.memory;

Card::Card(int suit, int value): m_cardSuit(suit), m_cardValue(value), m_realValue(0)
{
}

Card::~Card()
{
}

std::string Card::GetNameFromValue(int value) const
{
    switch (value)
    {
    case Ace:
        return "Ace";
    case Jack:
        return "Jack";
    case Queen:
        return "Queen";
    case King:
        return "King";
    default:
        return std::to_string(value + 1);
    }
}

std::string Card::GetNameFromSuit(int suit)
{
    switch (suit)
    {
    case 0:
        return "Clubs";
    case 1:
        return "Diamonds";
    case 2:
        return "Hearts";
    case 3:
        return "Spades";
    default:
        return "Error";
    }
}

void Card::PrintCardDetails(bool dealer) const
{
    if (dealer)
    {
        Color(14);
        std::cout << "\nDEALER: " << GetNameFromValue(GetValue()) << " of " << GetNameFromSuit(GetSuit()) << std::endl;
        Color();
        return;
    }

    std::cout << GetNameFromValue(GetValue()) << " of " << GetNameFromSuit(GetSuit()) << std::endl;
}

char* Card::Color(int color, char* Message)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    return Message;
}

bool Card::IsFaceCard() const
{
    // It's a face card if it's a Jack, Queen or King.
    if (GetValue() == Jack
        || GetValue() == Queen
        || GetValue() == King)
        return true;

    return false;
}
