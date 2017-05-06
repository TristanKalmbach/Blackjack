#include "Player.h"
#include "Blackjack.h"

/************************************************************************/
/*                          PLAYER METHODS                              */
/************************************************************************/

Player::Player(std::shared_ptr<Deck> deck): m_Deck(std::move(deck))
{
    Reset();
}

Player::~Player()
{
}

void Player::InitializeHand()
{
    // Now, give player a hand.
    auto card1 = m_Deck->DrawCard(true, false);
    auto card2 = m_Deck->DrawCard(true, false);

    // Add the count of that card to the players real count.
    int count1 = sBlackjack->GetRealCount(card1, false);
    int count2 = sBlackjack->GetRealCount(card2, false);

    // Add cards to hand.
    m_PlayerHand.push_back(card1);
    m_PlayerHand.push_back(card2);

    // Sum the count of the initial two cards.
    int finalCountOfInitialHand = count1 + count2;
    m_RealCount += finalCountOfInitialHand;
}

void Player::Reset()
{
    SetBust(false);
    SetRealCount(0);
    SetStanding(false);
    SetWon(false);

    // Clear hand on reset.
    m_PlayerHand.clear();

    // Set win count to 0.
    m_numWins = 0;
}

void Player::Hit()
{
    // Draw a card and get its count.
    auto newCard = m_Deck->DrawCard(true, false);

    // Add card to the hand.
    AddCardToHand(newCard);

    // Get the count.
    int count = sBlackjack->GetRealCount(newCard, false);

    // Update real count.
    m_RealCount += count;

    // Handle blackjack
    if (HasBlackJack())
        Win(true);

    // Handle player win
    if (GetRealCount() == WIN)
        Win(false);

    // Handle player bust.
    if (GetRealCount() >= BUST)
        Bust();
}

void Player::Stand()
{
    // Set standing true.
    SetStanding(true);
}

void Player::Win(bool blackjack)
{
    if (blackjack)
    {
        // Write to the console.
        std::cout << "\n BLACKJACK!!!" << std::endl;
    }
    else
    {
        // Write to console.
        std::cout << "\nYou win!" << std::endl;
    }

    ++m_numWins;

    // Set win state.
    SetWon(true);
}

void Player::Bust()
{
    // Set bust state
    SetBust(true);

    // Write to console.
    std::cout << "\nYou bust" << std::endl;
}

void Player::AddCardToHand(Card card)
{
    m_PlayerHand.push_back(card);
}

bool Player::HasFaceCard() const
{
    for (auto cards : GetCards())
    {
        // Make sure the card has a suit and value.
        if (!cards.GetSuit() || !cards.GetValue())
            return false;

        // If it's a face card, return true.
        if (cards.IsFaceCard())
            return true;
    }

    return false;
}

bool Player::HasBlackJack()
{
    // Check if the hand has only two cards.
    if (m_PlayerHand.size() == 2)
        return false;

    // Check for ace.
    auto hasAce = [&]
    {
        for (auto const& card : m_PlayerHand)
        {
            if (card.GetValue() == Ace)
                return true;
        }

        return false;
    };

    // Check for jack.
    auto hasJack = [&]
    {
        for (auto const& card : m_PlayerHand)
        {
            if (card.GetValue() == Ace)
                return true;
        }

        return false;
    };

    // Return true or false based on what we find.
    return hasAce() && hasJack();
}

int Player::GetNumWins() const
{
    return m_numWins;
}
