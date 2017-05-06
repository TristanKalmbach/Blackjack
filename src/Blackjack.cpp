#include "Blackjack.h"
#include "Controller.h"
#include "Player.h"

Blackjack::Blackjack()
{
    m_Deck.reset(new(Deck));

    m_Player.reset(new Player(m_Deck));
    m_Dealer.reset(new Dealer(m_Deck));
}

Blackjack::~Blackjack()
{
}

Blackjack* Blackjack::Instance()
{
    static Blackjack instance;
    return &instance;
}

void Blackjack::GameLoop()
{
    // Loop until someone wins or busts.
    while (!IsGameOver())
    {
        // If both parties are standing, figure out who has the higher count. Then, break the loop.
        if (m_Dealer->IsStanding() && m_Player->IsStanding())
        {
            HandleStandoff();
            break;
        }

        // Handle the game mechanics for the player.
        DoAction();

        // Update the counts to the player after he hits or stands.
        UpdateCount();

        // Now, we're going to ask before the dealer AI starts, if someone won or busted. If they did, break the loop.
        if (IsGameOver())
            break;

        // Now that the player has either hit or stand, nobody has won or lost and both parties
        // Aren't standing the dealer AI needs to do some work.
        m_Dealer->HandleAI();
    }

    // By reaching this point, someone has either bust or won.
    // Now, we'll ask if the player would like to play again.
    PlayAgain();
}

void Blackjack::PlayAgain()
{
    auto replay = sController->AskReplay();

    // Ask if they'd like to play again!
    if (!replay)
    {
        sController->UpdateEndGame(m_Player->GetNumWins(), m_Dealer->GetNumWins());
        return;
    }

    // Clear saved data.
    m_Dealer->Reset();
    m_Player->Reset();

    // Restart the game.
    InitializeGame();
    GameLoop();
}

void Blackjack::HandleStandoff() const
{
    auto dealerWin = m_Dealer->GetRealCount() > m_Player->GetRealCount();
    return dealerWin ? m_Dealer->Win(false) : m_Player->Win(false);
}

void Blackjack::InitializeGame()
{
    // Initialize the deck of cards and shuffle them.
    m_Deck->InitializeDeck();

    // Give initial hand to dealer.
    m_Dealer->InitializeHand();

    // Give initial hand to player.
    m_Player->InitializeHand();

    // Start the loop.
    GameLoop();
}

void Blackjack::DoAction() const
{
    auto mechanic = sController->GetMechanicChoice();
    switch (mechanic)
    {
        case Mechanic::Hit:
            m_Player->Hit();
        case Mechanic::Stand: 
            m_Player->Stand();
        case Mechanic::Double:
            break;
        case Mechanic::Split: 
            break;
        default:
            break;
    }
}

int Blackjack::GetRealCount(Card card, bool dealer) const
{
    // Get the count, so we can later determine if Ace will be used as 11 or 1.
    auto count = dealer ? m_Dealer->GetRealCount() : m_Player->GetRealCount();

    // Returns 11 for face cards.
    if (card.IsFaceCard())
        return 10;

    if (card.GetValue() == Ace)
    {
        // In the event that you draw an ace, we want to be sure it won't bust you. E.g., two aces.
        if (count + 11 >= BUST)
            return 1;

        // By default, aces will return as 11.
        return 11;
    }

    // Every other card is 1 more than it's value.
    return card.GetValue() + 1;
}

void Blackjack::UpdateCount() const
{
    auto dealerCount = m_Dealer->GetRealCount();
    auto playerCount = m_Player->GetRealCount();

    // If player has a winning count and neither party has won, let player win.
    if (dealerCount == WIN && !(m_Dealer->HasWon() || m_Player->HasWon()))
        m_Dealer->Win(false);
    // If dealer has a winning count and neither party has won, let dealer win.
    else if (playerCount == WIN && !(m_Dealer->HasWon() || m_Player->HasWon()))
        m_Player->Win(false);
    // No party has a winning count, and nobody has won yet. Update the counts.
    else
    {
        Color(13);
        std::cout << "\nYour Count: " << m_Player->GetRealCount() << std::endl;
        std::cout << "Dealer Count: " << m_Dealer->GetRealCount() << std::endl;
        Color();
    }
}

char* Blackjack::Color(int color, char* Message)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    return Message;
}

bool Blackjack::IsGameOver() const
{
    if (m_Dealer->HasWon())
        return true;

    if (m_Dealer->HasBust())
        return true;

    if (m_Player->HasWon())
        return true;

    if (m_Player->HasBust())
        return true;

    return false;
}