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

    static void HandleChoice(int choice);
};

#define sController Controller::Instance()