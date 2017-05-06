#pragma once
#include "Deck.h"
#include <memory>

import std.core;
import std.memory;

class Dealer
{
public:
    /**
     * \brief Initializes the dealer class.
     * \param deck The dealer's deck.
     */
    explicit Dealer(std::shared_ptr<Deck> deck);

    /**
     * \brief Destroys dealer class.
     */
    ~Dealer();

    /**
     * \brief Gives the dealer the initial two cards for their hand as well 
     * \brief as update their hand count.
     */
    void InitializeHand();

    /**
     * \brief Resets the game and all member variables to default values.
     */
    void Reset();

    /**
     * \brief Determines the real count of the dealer's hand.
     * \return Returns the integer value of the dealer's count.
     */
    int GetRealCount() const { return m_RealCount; }

    /**
     * \brief Sets the dealers real count.
     * \param count The count being set.
     */
    void SetRealCount(int count) { m_RealCount = count; }

    /**
     * \brief Determines if the dealer is standing or not.
     * \return Returns true or false if the dealer is standing.
     */
    bool IsStanding() const { return m_Standing; }

    /**
     * \brief Sets the dealers standing state to true or false.
     * \param val True or false if dealer is standing.
     */
    void SetStanding(bool val) { m_Standing = val; }

    /**
     * \brief Determines if the dealer is busted or not.
     * \return Has the dealer bust?
     */
    bool HasBust() const { return m_Busted; }

    /**
     * \brief Sets the dealers bust state.
     * \param val True or false, is busted.
     */
    void SetBust(bool val) { m_Busted = val; }

    /**
     * \brief Has the dealer won the game?
     * \return If the dealer has won or not.
     */
    bool HasWon() const { return m_Won; }

    /**
     * \brief Sets the state of the dealer winning. True or false.
     * \param val Has the dealer won.
     */
    void SetWon(bool val) { m_Won = val; }

    /**
     * \brief Adds a card to the dealer's hand and determines if he/she has won the game, bust etc.
     */
    void Hit();

    /**
     * \brief Will set stand state to standing, 
     * \brief and eventually the game will determine that the dealer has stand.
     */
    void Stand();

    /**
     * \brief Sets the win state and considers blackjack.
     * \param blackjack Is it a blackjack?
     */
    void Win(bool blackjack);

    /**
     * \brief Handles bust mechanics.
     */
    void Bust();

    /**
     * \brief Adds card ot he m_dealerHand vector.
     * \param card The card being added.
     */
    void AddCardToHand(Card card);

    /**
     * \brief Is there a face card in the hand?
     * \return If there is a face card or not.
     */
    bool HasFaceCard() const;

    /**
     * \brief Determines if dealer has blackjack or not.
     * \return True or false if blackjack is had.
     */
    bool HasBlackJack();

    /**
     * \brief Gets dealer's win count.
     * \return Number of wins the dealer has.
     */
    int GetNumWins() const;

    /**
     * \brief Gets the container that contains the dealers card objects.
     * \return Returns the dealers hand as a vector.
     */
    std::vector<Card> GetCards() const { return m_DealerHand; }

private:
    std::shared_ptr<Deck> m_Deck;

    std::vector<Card> m_DealerHand;

    int m_RealCount;
    int m_numWins;

    bool m_Standing;
    bool m_Busted;
    bool m_Won;
};
