#include "Blackjack.h"
#include "Player.h"

Blackjack::Blackjack()
{
    m_Deck.reset(new(Deck));

    m_Player.reset(new Player(m_Deck));
    m_Dealer.reset(new Dealer(m_Deck));
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

        // First thing that happens is the game is initialized and both parties are given a hand.
        // Next step is that we need to ask if they want to hit or stand.
        if (!m_Dealer->IsStanding() && !m_Player->IsStanding())
            HitOrStand();

        // Update the counts to the player after he hits or stands.
        UpdateCount();

        // Now, we're going to ask before the dealer AI starts, if someone won or busted. If they did, break the loop.
        if (IsGameOver())
            break;

        // Now that the player has either hit or stand, nobody has won or lost and both parties
        // Aren't standing the dealer AI needs to do some work.
        HandleDealerAI();
    }

    // By reaching this point, someone has either bust or won.
    // Now, we'll ask if the player would like to play again.
    PlayAgain();
}

void Blackjack::PlayAgain()
{
    int choice;
    std::cout << "\nWould you like to play again? 1.) Yes, 2.) No.";
    std::cin >> choice;

    // Ask if they'd like to play again!
    if (choice == 2)
    {
        system("cls"); // BAD NEWS BEARS. DON'T USE THIS IN THE REAL WORLD!!!
        std::cout << "You won " << m_Player->GetNumWins() << " times." << std::endl;
        std::cout << "Dealer won " << m_Dealer->GetNumWins() << " times." << std::endl;
        std::cout << "Thanks for playing!" << std::endl;
        return;
    }

    // If the player decides to play again, we'll reset the game and start over.
    m_Dealer->Reset();
    m_Player->Reset();
    InitializeGame();
    GameLoop();
}

void Blackjack::HandleStandoff() const
{
    // If the dealer has a higher count than the player, he wins.
    if (m_Dealer->GetRealCount() > m_Player->GetRealCount())
        m_Dealer->Win(false);
    else
        m_Player->Win(false);
}

void Blackjack::InitializeGame() const
{
    // Initialize the deck of cards and shuffle them.
    m_Deck->InitializeDeck();

    // Give initial hand to dealer.
    m_Dealer->InitializeHand();

    // Give initial hand to player.
    m_Player->InitializeHand();
}

void Blackjack::PromptStartingMenu()
{
    std::cout << "---------- BLACKJACK	----------" << std::endl;
    std::cout << "---------- 1.) Start Game ----------" << std::endl;
    std::cout << "---------- 2.) Close Game ----------" << std::endl;
}

void Blackjack::ParseChoice(int choice) const
{
    switch (choice)
    {
    case 1:
        InitializeGame();
        break;
    case 2:
        exit(EXIT_FAILURE);
    default:
        break;
    }
}

void Blackjack::HitOrStand() const
{
    std::cout << "\nHit: 1.) or Stand: 2.) ";
    int choice;
    std::cin >> choice;

    switch (choice)
    {
    case 1:
        m_Player->Hit();
        break;
    case 2:
        m_Player->Stand();
        break;
    default: // @TODO: Implement double/split.
        std::cout << "Error. Choice does not exit." << std::endl;
        break;
    }
}

int Blackjack::GetRealCount(Card card, bool dealer) const
{
    // Get the count, so we can later determine if Ace will be used as 11 or 1.
    int count = dealer ? m_Dealer->GetRealCount() : m_Player->GetRealCount();

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
    int dealerCount = m_Dealer->GetRealCount();
    int playerCount = m_Player->GetRealCount();

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

// ---------------------------------------------
//					DEALER AI
// ---------------------------------------------

void Blackjack::HandleDealerAI() const
{
    // Don't do anything if standing.
    if (m_Dealer->IsStanding())
        return;

    // If the dealer's count is 21, stand. This should never execute.
    if (m_Dealer->GetRealCount() == WIN)
    {
        m_Dealer->Stand();
        return;
    }

    // If the dealer has an exact count of 17 and the player has a face card, we'll stand.
    if (m_Dealer->GetRealCount() == 17 && m_Player->HasFaceCard())
    {
        m_Player->Stand();
        return;
    }

    // If the dealer's count is 17 or more and there is a face card, make it a 85% chance the dealer stays.
    if (m_Dealer->GetRealCount() >= 17 && ShouldStand(85) && !m_Player->HasFaceCard())
    {
        m_Dealer->Stand();
        return;
    }

    // By default, we want the dealer to hit.
    m_Dealer->Hit();
}

// Returns true or false based on a probability of whether or not the dealer should stand.
bool Blackjack::ShouldStand(int probibility)
{
    std::uniform_int_distribution<int> distribution(1, 100);
    std::mt19937 engine(std::random_device{}()); // Mersenne twister MT19937

    int value = distribution(engine);
    if (value > probibility)
        return false;

    return true;
}
