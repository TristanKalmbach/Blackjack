#pragma once

#include "Deck.h"
#include "Player.h"
#include "Dealer.h"
#include "Controller.h"

#define BUST 22
#define WIN 21

class Blackjack
{
public:
    Blackjack();

    ~Blackjack();

    /**
     * \brief A singleton to the Blackjack class.
     * \return Returns an instance of Blackjack
     */
    static Blackjack* Instance();

    /**
     * \brief Loops the game until specific conditions break it.
     */
    void GameLoop();

    /**
     * \brief Gives the initial hands and shuffles the deck.
     */
    void InitializeGame();

    /**
     * \brief Determines if the game will be played again or not.
     */
    void PlayAgain();

    /**
     * \brief Handles what happens in the case of all parties standing. The highest real count wins.
     */
    void HandleStandoff() const;

    /**
     * \brief Handles the hits, stands, doubles and splits.
     */
    void DoAction() const;

    /**
     * \brief Will determine the real count of the card.
     * \param card Card that needs its count determined.
     * \param dealer Is this the dealer?
     * \return The real count of the card.
     */
    int GetRealCount(Card card, bool dealer) const;

    /**
     * \brief Will update the players and dealers counts. 
     * \brief Handles cases that are determined by card count. Winning, busting etc.
     */
    void UpdateCount() const;

    /**
     * \brief Changles console text color.
     * \param color The color we want.
     * \param Message Message being sent.
     * \return Returns the color.
     */
    static char* Color(int color = 7, char* Message = "");

    /**
     * \brief Will determine if the game is complete or not.
     * \return Is the game over?
     */
    bool IsGameOver() const;

private:
    std::shared_ptr<Deck> m_Deck;

    std::shared_ptr<Dealer> m_Dealer;
    std::shared_ptr<Player> m_Player;
};

#define sBlackjack Blackjack::Instance()
