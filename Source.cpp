#include <iostream>
#include "Deck.h"
#include "Blackjack.h"

int main()
{
    std::unique_ptr<Blackjack> game(new Blackjack());

    // Prompt the menu and get the user input. We don't want to run this inside the game loop.
    game->PromptStartingMenu();

    int choice;
    std::cin >> choice;
    std::cout << std::endl; // Add another line

    // Act based on the choice.
    game->ParseChoice(choice);

    // Start the game loop.
    game->GameLoop();

    // No system("pause");
    std::cin.ignore();
    std::cin.get();

    return 0;
}