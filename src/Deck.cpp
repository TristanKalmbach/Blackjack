#include "Deck.h"

Deck::Deck()
{
    InitializeDeck();
}

void Deck::InitializeDeck()
{
    // Iterate a total of 13 x 4 (52) times and push back a card per iteration.
    for (int i = 0; i < MAX_VALUE; ++i)
    {
        for (int j = 0; j < MAX_SUITS; ++j)
        {
            Card card(j, i);
            m_Cards.push_back(card);
        }
    }

    // Now shuffle the deck.
    ShuffleDeck();
}

void Deck::ListDeckContents()
{
    for (auto const &cards : m_Cards)
    {
        if (m_Cards.empty())
            return;

        std::cout << cards.GetNameFromValue(cards.GetValue()) << " of " << cards.GetNameFromSuit(cards.GetSuit()) << std::endl;
    }
}

void Deck::ShuffleDeck()
{
    // Randomly shuffle the deck.
    std::mt19937 g(std::random_device{}());    
    std::shuffle(m_Cards.begin(), m_Cards.end(), g);
}

Card Deck::DrawCard(bool identifyCard, bool dealer)
{
    auto GetRandom = [](auto vec)
    {
        boost::container::stable_vector<Card> out;
        std::sample(vec.begin(), vec.end(), std::back_inserter(out),
            3, std::mt19937{ std::random_device{}() });

        return out.front();
    };

    auto card =  GetRandom(m_Cards);

    // Only identify the card if told.
    if (identifyCard)
        card.PrintCardDetails(dealer);

    return card;
}

std::string Card::GetNameFromValue(int value) const
{
    switch (value)
    {
        case CardValues::Ace:
            return "Ace";
        case CardValues::Jack:
            return "Jack";
        case CardValues::Queen:
            return "Queen";
        case CardValues::King:
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

void Card::PrintCardDetails(bool dealer)
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

bool Card::IsFaceCard() const
{
    if (GetValue() == CardValues::Jack 
        || GetValue() == CardValues::Queen 
        || GetValue() == CardValues::King)
        return true;

    return false;
}