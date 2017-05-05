#include <iostream>
#include "Deck.h"
#include "Blackjack.h"

int main()
{
    // Prompt the menu and get the user input. We don't want to run this inside the game loop.
    sController->DisplayGameMenu();

    int choice;
    std::cin >> choice;
    std::cout << std::endl; // Add another line

    // Act based on the choice.
    sController->HandleChoice(choice);

    // No system("pause");
    std::cin.ignore();
    std::cin.get();

    return 0;
}