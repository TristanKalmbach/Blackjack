#pragma once

#include "Common.h"
#include "Card.h"

import std.core;
import std.memory;

class Deck
{
public:
    Deck();

    ~Deck();


    /**
     * \brief Initialize the deck by iterating [13][4] times to place cards into the card vector.
     * \brief The cards will be shuffled on initialization.
     */
    void InitializeDeck();


    /**
     * \brief Will use the standard std::shuffle with Mersenne Twister randomization.
     * \brief The deck will be shuffled completely.
     */
    void ShuffleDeck();


    /**
     * \brief Will randomly select an elemnt from the m_Cards vector and return the card object.
     * \param identifyCard Identifies the card based on a boolean value.
     * \param dealer Ensures that some processes will only happen if the dealer is the one drawing.
     * \return Returns a card object so we can use its details.
     */
    Card DrawCard(bool identifyCard, bool dealer);

private:
    /**
     * \brief The choice container for storing the cards. Consider this a deck.
     */
    std::vector<Card> m_Cards;
};
