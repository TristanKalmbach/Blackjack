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
    int count1 = sBlackjack.GetRealCount(card1, true);
    int count2 = sBlackjack.GetRealCount(card2, true);

    // Sum the count of the initial two cards.
    int finalCountOfInitialHand = count1 + count2;
    m_RealCount += finalCountOfInitialHand;
}

void Dealer::Reset()
{
    SetBust(false);
    SetRealCount(0);
    SetStanding(false);
    SetWon(false);
}

void Dealer::Hit()
{
    // Write to console.
    std::cout << "\nDealer hits!" << std::endl;

    // Draw a card and get its count.
    auto newCard = m_Deck->DrawCard(true, true);
    int count = sBlackjack.GetRealCount(newCard, true);

    // Update real count.
    m_RealCount += count;

    // Handle dealer win
    if (GetRealCount() == WIN)
        Dealer::Win();

    // Handle player bust.
    if (GetRealCount() >= BUST)
        Dealer::Bust();
}

void Dealer::Stand()
{
    // Set standing true.
    SetStanding(true);

    // Write to console.
    std::cout << "\nDealer stands!" << std::endl;
}

void Dealer::Win()
{
    // Set win state.
    SetWon(true);

    // Write to console.
    std::cout << "\nDealer wins!" << std::endl;

    // Add win to counter.
    sBlackjack.AddDealerWin();
}

void Dealer::Bust()
{
    // Set bust state
    SetBust(BUST_STATE_BUST);

    // Write to console.
    std::cout << "\nDealer busts!" << std::endl;

    // Add win to counter.
    sBlackjack.AddDealerWin();
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
    int count1 = sBlackjack.GetRealCount(card1, false);
    int count2 = sBlackjack.GetRealCount(card2, false);

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
}

void Player::Hit()
{
    // Draw a card and get its count.
    auto newCard = m_Deck->DrawCard(true, false);
    int count = sBlackjack.GetRealCount(newCard, false);

    // Update real count.
    m_RealCount += count;

    // Handle player win
    if (GetRealCount() == WIN)
        Player::Win();

    // Handle player bust.
    if (GetRealCount() >= BUST)
        Player::Bust();
}

void Player::Stand()
{
    // Set standing true.
    SetStanding(true);
}

void Player::Win()
{
    // Write to console.
    std::cout << "\nYou win!" << std::endl;

    // Set win state.
    SetWon(true);

    // Add win to counter.
    sBlackjack.AddPlayerWin();
}

void Player::Bust()
{
    // Set bust state
    SetBust(BUST_STATE_BUST);

    // Write to console.
    std::cout << "\nYou bust" << std::endl;

    // Add win to counter.
    sBlackjack.AddPlayerWin();
}

bool Player::HasFaceCard()
{
    for (auto cards : GetCards())
        if (cards.IsFaceCard())
            return true;

    return false;
}
