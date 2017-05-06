#include "Controller.h"

import std.core;
import std.memory;

Controller* Controller::Instance()
{
    static Controller instance;
    return &instance;
}

void Controller::DisplayGameMenu()
{
    std::cout << " ----------------------------------------- " << std::endl;
    std::cout << " |               BLACKJACK               |"  << std::endl;
    std::cout << " |           By Tristan Kalmbach         |" << std::endl;
    std::cout << " |                                       |" << std::endl;
    std::cout << " |                                       |" << std::endl;
    std::cout << " |                                       |" << std::endl;
    std::cout << " |             1.) Play Game             |" << std::endl;
    std::cout << " |             2.) Quit Game             |" << std::endl;
    std::cout << " |                                       |" << std::endl;
    std::cout << " ----------------------------------------- " << std::endl;
}

void Controller::DisplayWait(int loops)
{
    std::cout << "Thinking ";
    std::cout << "-" << std::flush;
    for (int i = 0; i < loops; i++) {
        Sleep(1);
        std::cout << "\b\\" << std::flush;
        Sleep(1);
        std::cout << "\b|" << std::flush;
        Sleep(1);
        std::cout << "\b/" << std::flush;
        Sleep(1);
        std::cout << "\b-" << std::flush;
    }

}

void Controller::HandleChoice(int choice)
{
    std::shared_ptr<Blackjack> game(new Blackjack());
    if (!game)
        return;

    switch (choice)
    {
        case 1:
            game->InitializeGame();
        case 2:
            exit(EXIT_SUCCESS);
        default:
            return;
    }
}
