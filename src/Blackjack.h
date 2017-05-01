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

    inline bool HasEitherPlayerBust() { return m_Dealer->HasBust() || m_Player->HasBust(); }
    inline bool HasEitherPlayerWon() { return m_Dealer->HasWon() || m_Player->HasWon(); }
    inline bool IsDealerStanding() const { return m_DealerStanding; }
    inline bool IsPlayerStanding() const { return m_PlayerStanding; }

    void SetDealerStanding(bool val) { m_DealerStanding = val; }
    void SetPlayerStanding(bool val) { m_PlayerStanding = val; }

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
    inline void AddDealerWin() { m_numDealerWins += 1; }
    inline void AddPlayerWin() { m_numPlayerWins += 1; }

    // Handle text color.
    inline char* Color(int color = 7, char* Message = "") {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
        return Message;
    }

private:
    // Win totals
    int m_numPlayerWins;
    int m_numDealerWins;

    boost::shared_ptr<Deck> m_Deck;

    boost::shared_ptr<Dealer> m_Dealer;
    boost::shared_ptr<Player> m_Player;

    bool m_DealerStanding;
    bool m_PlayerStanding;
};

#define sBlackjack Blackjack::Instance()