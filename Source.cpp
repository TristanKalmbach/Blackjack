#include <iostream>
#include "Deck.h"
#include "Blackjack.h"

int main()
{
	std::unique_ptr<Blackjack> game(new Blackjack());
	game->GameLoop();

	system("pause");
	return 0;
}