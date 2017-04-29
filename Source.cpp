#include <iostream>
#include "Deck.h"
#include "Blackjack.h"

int main()
{
    std::unique_ptr<Blackjack> game(new Blackjack());
    game->GameLoop();

    // No system("pause");
    std::cin.ignore();
    std::cin.get();

    return 0;
}