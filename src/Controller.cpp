#include "Controller.h"
#include <cctype>

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
    for (int i = 0; i < loops; ++i) {
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

Mechanic Controller::GetMechanicChoice()
{
    int userChoice;
    std::cout << "\n\n1.) Hit -- 2.) Stand -- 3.) Double -- 4.) Split";
    std::cin >> userChoice;

    switch(userChoice)
    {
        case 1:
            return Mechanic::Hit;
        case 2:
            return Mechanic::Stand;
        case 3:
            return Mechanic::Double;
        case 4:
            return Mechanic::Split;
        default:
            return Mechanic::None;
    }
}

bool Controller::AskReplay()
{
    std::cout << "Would you like to play again? Y/N: ";
    char userChoice;

    std::cin >> userChoice;

    while (std::tolower(userChoice) != 'y' || std::tolower(userChoice) != 'n')
    {
        std::cout << "Invalid answer. Y/N!" << std::endl;
        std::cin >> userChoice;
    }

    if (std::tolower(userChoice) == 'y')
        return true;

    return false;
}

void Controller::UpdateEndGame(int playerWinCount, int dealerWinCount)
{
    system("cls"); // BAD NEWS BEARS. DON'T USE THIS IN THE REAL WORLD!!!
    std::cout << "You won " << playerWinCount << " times." << std::endl;
    std::cout << "Dealer won " << dealerWinCount << " times." << std::endl;
    std::cout << "Thanks for playing!" << std::endl;
}
