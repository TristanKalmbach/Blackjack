#pragma once

#include "Common.h"
#include "Deck.h"

class Player
{
public:
    /**
     * \brief Initializes the player class.
     * \param deck The player's deck.
     */
    explicit Player(boost::shared_ptr<Deck> deck);

    /**
     * \brief Destroys player class.
     */
    ~Player();

    /**
     * \brief Gives the player the initial two cards for their hand as well 
     * \brief as update their hand count.
     */
    void InitializeHand();

    /**
     * \brief Resets the game and all member variables to default values.
     */
    void Reset();

    /**
     * \brief Determines the real count of the player's hand.
     * \return Returns the integer value of the player's count.
     */
    int GetRealCount() const { return m_RealCount; }

    /**
     * \brief Sets the players real count.
     * \param count The count being set.
     */
    void SetRealCount(int count) { m_RealCount = count; }

    /**
     * \brief Determines if the player is standing or not.
     * \return Returns true or false if the player is standing.
     */
    bool IsStanding() const { return m_Standing; }

    /**
     * \brief Sets the players standing state to true or false.
     * \param val True or false if player is standing.
     */
    void SetStanding(bool val) { m_Standing = val; }

    /**
     * \brief Determines if the player is busted or not.
     * \return Has the player bust?
     */
    bool HasBust() const { return m_Busted; }

    /**
     * \brief Sets the players bust state.
     * \param val True or false, is busted.
     */
    void SetBust(bool val) { m_Busted = val; }

    /**
     * \brief Has the player won the game?
     * \return If the player has won or not.
     */
    bool HasWon() const { return m_Won; }

    /**
     * \brief Sets the state of the player winning. True or false.
     * \param val Has the player won.
     */
    void SetWon(bool val) { m_Won = val; }

    /**
     * \brief Adds a card to the player's hand and determines if he/she has won the game, bust etc.
     */
    void Hit();

    /**
     * \brief Will set stand state to standing, 
     * \brief and eventually the game will determine that the player has stand.
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
     * \brief Adds card ot he m_PlayerHand vector.
     * \param card The card being added.
     */
    void AddCardToHand(Card card);

    /**
     * \brief Is there a face card in the hand?
     * \return If there is a face card or not.
     */
    bool HasFaceCard() const;

    /**
     * \brief Determines if player has blackjack or not.
     * \return True or false if blackjack is had.
     */
    bool HasBlackJack();

    /**
     * \brief Gets player's win count.
     * \return Number of wins the player has.
     */
    int GetNumWins() const;

    /**
     * \brief Gets the container that contains the players card objects.
     * \return Returns the players hand as a vector.
     */
    boost::container::stable_vector<Card> GetCards() const { return m_PlayerHand; }

private:
    boost::shared_ptr<Deck> m_Deck;

    boost::container::stable_vector<Card> m_PlayerHand;

    int m_RealCount;
    int m_numWins;

    bool m_Standing;
    bool m_Busted;
    bool m_Won;
};
