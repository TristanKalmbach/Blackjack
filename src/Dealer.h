#pragma once
#include "Deck.h"

class Dealer
{
public:
    explicit Dealer(boost::shared_ptr<Deck> deck) : m_Deck(std::move(deck))
    {
        Reset();
    }

    ~Dealer()
    {
    }

    // Give the initial hand.
    void InitializeHand();

    // Reset all values.
    void Reset();

    // Get and Set the count.
    int GetRealCount() const { return m_RealCount; }
    void SetRealCount(int count) { m_RealCount = count; }

    // Get and Set standing.
    bool IsStanding() const { return m_Standing; }
    void SetStanding(bool val) { m_Standing = val; }

    // Get and Set busting.
    bool HasBust() const { return m_Busted; }
    void SetBust(bool val) { m_Busted = val; }

    // Get and Set winning.
    bool HasWon() const { return m_Won; }
    void SetWon(bool val) { m_Won = val; }

    // Game mechanics
    void Hit();
    void Stand();
    void Win(bool blackjack);
    void Bust();

    // Handle the dealers hand.
    void AddCardToHand(Card card);
    boost::container::stable_vector<Card> m_DealerHand;

    // Figure out if blackjack is in the hand.
    bool HasBlackJack();

    // Get the wincounter.
    int GetNumWins() const { return m_numWins; }

private:
    boost::shared_ptr<Deck> m_Deck;

    int m_RealCount;
    bool m_Standing;
    bool m_Busted;
    bool m_Won;

    int m_numWins;
};
