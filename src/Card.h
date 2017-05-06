#pragma once

#include "Common.h"

import std.core;
import std.memory;

class Card
{
public:
    /**
     * \brief Initializes this card class.
     * \param suit The card's suit.
     * \param value The card's value.
     */
    Card(int suit, int value);

    /**
     * \brief Destroys the class.
     */
    ~Card();

    /**
     * \brief Determines the suit of this card instantiation.
     * \return Returns the suit as an integer.
     */
    int GetSuit() const { return m_cardSuit; }

    /**
    * \brief Assigns a suit to this card instantiation.
    * \param suit The suit that's being assigned to this card.
    */
    void SetSuit(int suit) { m_cardSuit = suit; }

    /**
    * \brief Determines the face value of this card instantiation.
    * \return Returns the value as an integer.
    */
    int GetValue() const { return m_cardValue; }

    /**
    * \brief Assigns a face value to this card instantiation.
    * \param value The value that's being assigned to this card.
    */
    void SetValue(int value) { m_cardValue = value; }

    /**
     * \brief Determines a name e.g., "Ace, Two, Three" for the integer value of this card.
     * \param value The int value previously assigned to this card.
     * \return Retruns a value as a string for later use.
     */
    std::string GetNameFromValue(int value) const;

    /**
     * \brief Determines a name e.g., "Club, Spade, Diamond, Heart" for the int value of the suit.
     * \param suit The suit integer value that was previously assigned.
     * \return Returns a string with the name of the suit.
     */
    static std::string GetNameFromSuit(int suit);

    /**
     * \brief Prints the details of the card like the suit and value.
     * \param dealer Determine if this is the dealer or not. That affects the output.
     */
    void PrintCardDetails(bool dealer) const;

    /**
     * \brief Changes the text color to a specified color.
     * \param color The color chosen.
     * \param Message The message to display.
     * \return returns color char.
     */
    static char* Color(int color = 7, char* Message = "");

    /**
     * \brief Determine if this card is a face card. I.e., King, Queen or Jack.
     * \return Returns true or false based on the card.
     */
    bool IsFaceCard() const;

private:
    /**
     * \brief Card's suit.
     */
    int m_cardSuit;

    /**
     * \brief Cards value.
     */
    int m_cardValue;

    /**
     * \brief Cards real, numerical value.
     */
    int m_realValue;
};
