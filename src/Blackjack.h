#pragma once

#include "Deck.h"
#include "Player.h"
#include "Dealer.h"
#include "Controller.h"

import std.core;
import std.memory;

#define BUST 22
#define WIN 21

class Blackjack
{
public:
    Blackjack();

    ~Blackjack()
    {
    }

    static Blackjack* Instance();

    void GameLoop();

    void InitializeGame();

    void PlayAgain();

    void HandleStandoff() const;

    void HitOrStand() const;

    int GetRealCount(Card card, bool dealer) const;

    void HandleDealerAI() const;

    static bool ShouldStand(int probibility);

    void UpdateCount() const;

    static char* Color(int color = 7, char* Message = "");

    bool IsGameOver() const;

private:
    std::shared_ptr<Deck> m_Deck;

    std::shared_ptr<Dealer> m_Dealer;
    std::shared_ptr<Player> m_Player;
};

#define sBlackjack Blackjack::Instance()
