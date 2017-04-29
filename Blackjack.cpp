#include "Blackjack.h"

Blackjack::Blackjack()
{
	ClearCounts();
	m_Deck = new Deck();
}

void Blackjack::GameLoop()
{
	// DisplayMenu & Options.
	PromptStartingMenu();

	int choice;
	std::cin >> choice;
	ParseChoice(choice);

	// Loop until either party busts.
	while (!HasEitherPlayerBust())
	{
		// Asks user if they want to hit or stay. The individual methods provide the logic.
		AskHitOrStay();

		// Update Counts
		UpdateCount();

		// This will handle the dealers logic.
		HandleDealerAI();
	}

	// Notify player if he busts or not!
	if (HasPlayerBust())
		std::cout << "\nYou bust!" << std::endl;
	else
		std::cout << "\nDealer busts!" << std::endl;

	// Update the counts for final notification.
	UpdateCount();

	// Ask if player would like to play again.
	PlayAgain();
}

void Blackjack::PlayAgain()
{
	int choice;
	std::cout << "\nWould you like to play again? 1.) Yes, 2.) No.";
	std::cin >> choice;

	// Ask if they'd like to play again!
	if (choice == 1)
	{
		ClearCounts();
		GameLoop();
	}
	else
		std::cout << "Thanks for playing!" << std::endl;
}

void Blackjack::InitializeGame()
{
	// Initialize the deck of cards and shuffle them.
	m_Deck->InitializeDeck();

	// Now, give player a hand.
	auto card1 = m_Deck->DrawCard(true, false);
	auto card2 = m_Deck->DrawCard(true, false);

	// Add the count of that card to the players real count.
	int count1 = GetRealCount(card1, true);
	int count2 = GetRealCount(card2, true);

	// Sum the count of the initial two cards.
	int finalCountOfInitialHand = count1 + count2;
	m_realCount += finalCountOfInitialHand;

	InitializeDealerHand();
}

bool Blackjack::HasEitherPlayerBust()
{
	// Check players count to determine if a bust occurred.
	if (GetPlayerCount() >= BUST)
	{	
		SetPlayerBust(true);
		return true;
	}

	// Check dealers count to determine if a bust occurred.
	if (GetDealerCount() >= BUST)
	{
		SetDealerBust(true);
		return true;
	}

	return false;
}

void Blackjack::ClearCounts()
{
	SetDealerBust(false);
	SetPlayerBust(false);

	m_dealerCount = 0;
	m_realCount = 0;

	m_playerStay = false;
	m_dealerStay = false;

	m_dealerWon = false;
	m_playerWon = false;
}

void Blackjack::Hit(bool dealer)
{
	auto newCard = m_Deck->DrawCard(true, dealer);
	int count = GetRealCount(newCard, false);

	// Check if dealer. If yes, update dealer count.
	if (dealer)
	{
		m_dealerCount += count;
		return;
	}

	// Update player count.
	m_realCount += count;
}

void Blackjack::Stay(bool dealer)
{
	// Set the values of the staying mechanic.
	if (dealer)
		m_dealerStay = true;
	else
		m_playerStay = true;

	// Now, we can check if the dealer and player have stayed. If so, compare results and stop game.
	if (m_dealerStay && m_playerStay)
	{
		// Compare totals. Whoever is highest wins the game.
		int dealerCount = GetDealerCount();
		int playerCount = GetPlayerCount();

		if (dealerCount > playerCount)
			Win(true);
		else
			Win(false);
	}

	return;
}

void Blackjack::Win(bool dealer)
{
	if (dealer)
	{
		m_dealerWon = true;
		std::cout << "\nDealer wins!" << std::endl;
		UpdateCount();
		PlayAgain();
		return;
	}
	else
	{
		m_playerWon = true;
		std::cout << "\nYou win!" << std::endl;
		UpdateCount();
		PlayAgain();
		return;
	}
}

void Blackjack::PromptStartingMenu()
{
	std::cout << "---------- BLACKJACK	----------" << std::endl;
	std::cout << "---------- 1.) Start Game ----------" << std::endl;
	std::cout << "---------- 2.) Close Game ----------" << std::endl;
}

void Blackjack::ParseChoice(int choice)
{
	switch (choice)
	{
		case 1:
			InitializeGame();
			break;
		case 2:
			exit(EXIT_FAILURE);
			break;
		default:
			break;
	}
}

void Blackjack::AskHitOrStay()
{
	std::cout << "\nHit: 1.) or Stay: 2.) ";
	int choice;
	std::cin >> choice;

	switch (choice)
	{
		case 1:
			Hit(false);
			break;
		case 2:
			Stay(false);
			break;
		default:
			std::cout << "Error. Choice does not exit." << std::endl;
			break;
	}

}

int Blackjack::GetRealCount(Card card, bool firstHand)
{
	// Returns 11 for face cards.
	if (card.GetValue() == 12 || card.GetValue() == 11 || card.GetValue() == 10)
		return 10;
	else if (card.GetValue() == 0) // TODO: Fix logic allowing player OR dealer to use Aces as 1. By default, if you're dealt an Ace on hand one, it's a value of 1.
		return firstHand ? 1 : 11;
	else 
		return card.GetValue() + 1; // Every other card is 1 less than it's value.
}

// ---------------------------------------------
//					DEALER AI
// ---------------------------------------------

void Blackjack::HandleDealerAI()
{
	// We want the dealer to use basic strategy to win the game.
	// So, dealer will weigh card values and the algorithm will determine if he hits, or stays.
	if (GetDealerCount() >= 17)
	{
		std::cout << "\nDEALER STAYS" << std::endl;
		Stay(true);
	}

	Hit(true);
}

void Blackjack::InitializeDealerHand()
{
	// We want to give the dealer two cards, BUT we don't want to notify the player what both the cards are. Only one and the count.
	auto card1 = m_Deck->DrawCard(false, true);
	auto card2 = m_Deck->DrawCard(true, true);

	// Add the count of that card to the players real count.
	int count1 = GetRealCount(card1, true);
	int count2 = GetRealCount(card2, true);

	// Sum the count of the initial two cards.
	int finalCountOfInitialHand = count1 + count2;
	m_dealerCount += finalCountOfInitialHand;
}

void Blackjack::UpdateCount()
{
	if (GetDealerCount() == WIN && !(m_dealerWon || m_playerWon))
		Blackjack::Win(true);
	else if (GetPlayerCount() == WIN && !(m_dealerWon || m_playerWon))
		Blackjack::Win(false);
	else
	{
		std::cout << "\nYour Count: " << GetPlayerCount() << std::endl;
		std::cout << "Dealer Count: " << GetDealerCount() << std::endl;
	}
}
