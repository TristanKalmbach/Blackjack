#include "Player.h"
#include "Blackjack.h"

/************************************************************************/
/*                          DEALER METHODS                              */
/************************************************************************/

void Dealer::InitializeHand()
{
    // We want to give the dealer two cards, BUT we don't want to notify the player what both the cards are. Only one and the count.
    auto card1 = m_Deck->DrawCard(false, true);
    auto card2 = m_Deck->DrawCard(true, true);

    // Add the count of that card to the players real count.
    int count1 = sBlackjack->GetRealCount(card1, true);
    int count2 = sBlackjack->GetRealCount(card2, true);

    // Sum the count of the initial two cards.
    int finalCountOfInitialHand = count1 + count2;
    m_RealCount += finalCountOfInitialHand;
}

void Dealer::Reset()
{
    SetBust(BUST_STATE_NO_BUST);
    SetRealCount(0);
    SetStanding(STANDING_STATE_NOT_STANDING);
    SetWon(WIN_STATE_LOSE);

    // Erase the hand on reset.
    m_DealerHand.clear();

    // Reset win count.
    m_numWins = 0;
}

void Dealer::Hit()
{
    // Write to console.
    std::cout << "\nDealer hits!" << std::endl;

    // Draw a card and get its count.
    auto newCard = m_Deck->DrawCard(true, true);

    // Add the card to the hand.
    AddCardToHand(newCard);

    // Get the count.
    int count = sBlackjack->GetRealCount(newCard, true);

    // Update real count.
    m_RealCount += count;

    // Handle blackjack
    if (HasBlackJack())
        Win(true);

    // Handle dealer win
    if (GetRealCount() == WIN)
        Win(false);

    // Handle player bust.
    if (GetRealCount() >= BUST)
        Bust();
}

void Dealer::Stand()
{
    // Set standing true.
    SetStanding(STANDING_STATE_STANDING);

    // Write to console.
    std::cout << "\nDealer stands!" << std::endl;
}

void Dealer::Win(bool blackjack)
{
    // Set win state.
    SetWon(WIN_STATE_WIN);

    if (blackjack)
    // Write to console
        std::cout << "\nDEALER BLACKJACK!!!" << std::endl;
    else
    // Write to console.
        std::cout << "\nDealer wins!" << std::endl;

    ++m_numWins;
}

void Dealer::Bust()
{
    // Set bust state
    SetBust(BUST_STATE_BUST);

    // Write to console.
    std::cout << "\nDealer busts!" << std::endl;
}

void Dealer::AddCardToHand(Card card)
{
    m_DealerHand.push_back(card);
}

bool Dealer::HasBlackJack()
{
    // Check if the hand has only two cards.
    if (m_DealerHand.size() == 2)
        return false;

    // Check for ace.
    auto hasAce = [&]
    {
        for (auto const& card : m_DealerHand)
        {
            if (card.GetValue() == Ace)
                return true;
        }

        return false;
    };

    // Check for jack.
    auto hasJack = [&]
    {
        for (auto const& card : m_DealerHand)
        {
            if (card.GetValue() == Ace)
                return true;
        }

        return false;
    };

    // Return true or false based on what we find.
    return (hasAce() && hasJack());
}

/************************************************************************/
/*                          PLAYER METHODS                              */
/************************************************************************/

void Player::InitializeHand()
{
    // Now, give player a hand.
    auto card1 = m_Deck->DrawCard(true, false);
    auto card2 = m_Deck->DrawCard(true, false);

    // Add the count of that card to the players real count.
    int count1 = sBlackjack->GetRealCount(card1, false);
    int count2 = sBlackjack->GetRealCount(card2, false);

    // Sum the count of the initial two cards.
    int finalCountOfInitialHand = count1 + count2;
    m_RealCount += finalCountOfInitialHand;
}

void Player::Reset()
{
    SetBust(BUST_STATE_NO_BUST);
    SetRealCount(0);
    SetStanding(STANDING_STATE_NOT_STANDING);
    SetWon(WIN_STATE_LOSE);

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
    SetStanding(STANDING_STATE_STANDING);
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
    SetBust(BUST_STATE_BUST);

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
