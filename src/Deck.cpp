#include "Deck.h"

Deck::Deck()
{
    InitializeDeck();
}

Deck::~Deck()
{
}

void Deck::InitializeDeck()
{
    // Iterate a total of 13 x 4 (52) times and push back a card per iteration.
    for (int i = 0; i < MAX_VALUE; ++i)
    {
        for (int j = 0; j < MAX_SUITS; ++j)
        {
            // Create a new card and add it to the deck.
            Card card(j, i);
            m_Cards.push_back(card);
        }
    }

    // Now shuffle the deck.
    ShuffleDeck();
}

void Deck::ShuffleDeck()
{
    // Randomly shuffle the deck.
    std::mt19937 g(std::random_device{}());
    std::shuffle(m_Cards.begin(), m_Cards.end(), g);
}

Card Deck::DrawCard(bool identifyCard, bool dealer)
{
    // Randomize the elements and select whichever is in the front of the vector.
    auto GetRandom = [](auto vec)
    {
        Cards out;
        std::sample(vec.begin(), vec.end(), std::back_inserter(out), 3, std::mt19937{std::random_device{}()});
        return out.front();
    };

    // Assign whatever random card we just got to a card object.
    auto card = GetRandom(m_Cards);

    // Only identify the card if told.
    if (identifyCard)
        card.PrintCardDetails(dealer);

    return card;
}