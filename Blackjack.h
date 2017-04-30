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

    static Blackjack& Instance()
    {
        static Blackjack instance;
        return instance;
    }

    // Misc.
    void GameLoop();
    void InitializeGame();
    void PlayAgain();
    void HandleStandoff();

    bool HasEitherPlayerBust() { return m_Dealer->HasBust() || m_Player->HasBust(); }
    bool HasEitherPlayerWon() { return m_Dealer->HasWon() || m_Player->HasWon(); }

    // Menu
    void PromptStartingMenu();
    void ParseChoice(int choice);
    void HitOrStand();

    // Determine the real count of the card drawn.
    int GetRealCount(Card card, bool dealer);

    // Dealer AI
    void HandleDealerAI();
    bool ShouldStand(int probibility);

    // Updates counts.
    void UpdateCount();

    // Add win
    void AddWin(bool dealer) { dealer ? ++m_numDealerWins : ++m_numPlayerWins; }

    // Handle text color.
    char* Color(int color = 7, char* Message = "") {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
        return Message;
    }

private:
    // Win totals
    int m_numPlayerWins;
    int m_numDealerWins;

    std::shared_ptr<Deck> m_Deck;

    Dealer* m_Dealer;
    Player* m_Player;
};

#define sBlackjack Blackjack::Instance()