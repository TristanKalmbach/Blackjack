#pragma once
#include "Common.h"
#include <conio.h>
#include "Blackjack.h"

class Controller
{
public:
    Controller() { }
    ~Controller() { }

    static Controller* Instance();

    /**
     * \brief Displays the initial game menu.
     */
    static void DisplayGameMenu();

    /**
     * \brief Will wait to make the game more engaging.
     * \param loops Number of times it'll slseep.
     */
    static void DisplayWait(int loops);

    /**
     * \brief Will either start the game or end the game.
     * \param choice Choice to start the game or close the window.
     */
    static void HandleChoice(int choice);

    /**
     * \brief Gets a mechanic for the game.
     * \return Returns the game mechanic the player wants to do.
     */
    static Mechanic GetMechanicChoice();

    /**
     * \brief Determines if a new game is created.
     * \return True or false, if they want to play again.
     */
    static bool AskReplay();

    /**
     * \brief Writes to console whe game ends.
     * \param playerWinCount Number of player wins.
     * \param dealerWinCount Number of dealer wins.
     */
    static void UpdateEndGame(int playerWinCount, int dealerWinCount);
};

#define sController Controller::Instance()