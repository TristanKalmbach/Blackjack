#pragma once

#include "Deck.h"
#include "Player.h"

#define BUST 22
#define WIN 21

class Blackjack
{
public:
    Blackjack();
    ~Blackjack() { }

    static Blackjack* Instance();

    // Misc.
    void GameLoop();
    void InitializeGame() const;
    void PlayAgain();
    void HandleStandoff() const;

    bool HasEitherPlayerBust() const { return m_Dealer->HasBust() || m_Player->HasBust(); }
    bool HasEitherPlayerWon() const { return m_Dealer->HasWon() || m_Player->HasWon(); }

    // Menu
    static void PromptStartingMenu();
    void ParseChoice(int choice) const;
    void HitOrStand() const;

    // Determine the real count of the card drawn.
    int GetRealCount(Card card, bool dealer) const;

    // Dealer AI
    void HandleDealerAI() const;
    static bool ShouldStand(int probibility);

    // Updates counts.
    void UpdateCount() const;

    // Handle text color.
    static char* Color(int color = 7, char* Message = "")
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
        return Message;
    }

private:
    boost::shared_ptr<Deck> m_Deck;

    boost::shared_ptr<Dealer> m_Dealer;
    boost::shared_ptr<Player> m_Player;
};

#define sBlackjack Blackjack::Instance()