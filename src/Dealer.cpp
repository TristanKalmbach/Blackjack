/************************************************************************/
/*                          DEALER METHODS                              */
/************************************************************************/

#include "Dealer.h"
#include "Blackjack.h"

Dealer::Dealer(boost::shared_ptr<Deck> deck) : m_Deck(std::move(deck))
{
    Reset();
}

Dealer::~Dealer()
{
}

void Dealer::InitializeHand()
{
    // We want to give the dealer two cards, BUT we don't want to notify the player what both the cards are. Only one and the count.
    auto card1 = m_Deck->DrawCard(false, true);
    auto card2 = m_Deck->DrawCard(true, true);

    // Add cards to dealer's hand.
    m_DealerHand.push_back(card1);
    m_DealerHand.push_back(card2);

    // Add the count of that card to the players real count.
    int count1 = sBlackjack->GetRealCount(card1, true);
    int count2 = sBlackjack->GetRealCount(card2, true);

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
    SetStanding(true);

    // Write to console.
    std::cout << "\nDealer stands!" << std::endl;
}

void Dealer::Win(bool blackjack)
{
    // Set win state.
    SetWon(true);

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
    SetBust(true);

    // Write to console.
    std::cout << "\nDealer busts!" << std::endl;
}

void Dealer::AddCardToHand(Card card)
{
    m_DealerHand.push_back(card);
}

bool Dealer::HasFaceCard() const
{
    for (auto const &cards : m_DealerHand)
        if (cards.IsFaceCard())
            return true;

    return false;
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

int Dealer::GetNumWins() const
{
    return m_numWins;
}
