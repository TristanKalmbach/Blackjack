#pragma once

#include <memory>
#include "Deck.h"

enum BustState
{
    BUST_STATE_OK,
    BUST_STATE_BUST
};

class Dealer
{
public:
    explicit Dealer(std::shared_ptr<Deck> deck) : m_Deck(std::move(deck)) 
    {
        Reset();
    }

    ~Dealer() { }

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
    void Win();
    void Bust();

private:
    std::shared_ptr<Deck> m_Deck;

    int m_RealCount;
    bool m_Standing;
    bool m_Busted;
    bool m_Won;
};

class Player
{
public:
    explicit Player(std::shared_ptr<Deck> deck) : m_Deck(std::move(deck)) 
    {
        Reset();
    }

    ~Player() { }

    // Give the initial hand.
    void InitializeHand();

    // Reset all values.
    void Reset();

    // Get and Set the count.
    int GetRealCount() const { return m_RealCount; }
    void SetRealCount(int count) { m_RealCount = count; }

    // Get and Set standing.
    bool IsStanding() { return m_Standing; }
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
    void Win();
    void Bust();

    std::vector<Card> GetCards() { return m_Deck->GetCards(); }
    bool HasFaceCard();

private:
    std::shared_ptr<Deck> m_Deck;

    int m_RealCount;
    bool m_Standing;
    bool m_Busted;
    bool m_Won;
};

