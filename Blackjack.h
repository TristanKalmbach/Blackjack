#pragma once

#include "Deck.h"

#define BUST 22
#define WIN 21

class Blackjack
{
public:
	Blackjack();
	~Blackjack() { }

	// Misc.
	void GameLoop();
	void InitializeGame();
	bool HasEitherPlayerBust();
	void ClearCounts();
	void PlayAgain();

	// Game Mechanics
	void Hit(bool dealer);
	void Stay(bool dealer);
	void Win(bool dealer);

	// Helper methods.
	int GetPlayerCount() const { return m_realCount; }
	int GetDealerCount() const { return m_dealerCount; }

	bool HasDealerBust() const { return m_dealerBusted; }
	bool HasPlayerBust() const { return m_hasBusted; }

	void SetPlayerBust(bool value) { m_hasBusted = value; }
	void SetDealerBust(bool value) { m_dealerBusted = value; }

	// Menu
	void PromptStartingMenu();
	void ParseChoice(int choice);
	void AskHitOrStay();

	// Determine the real count of the card drawn.
	int GetRealCount(Card card, bool firstHand);

	// Dealer AI
	void HandleDealerAI();
	void InitializeDealerHand();

	// Updates counts.
	void UpdateCount();

private:
	// Busting mechanic
	bool m_hasBusted;
	bool m_dealerBusted;

	// Card counts
	int m_realCount;
	int m_dealerCount;

	// Staying mechanic
	bool m_playerStay;
	bool m_dealerStay;

	// Win bools
	bool m_playerWon;
	bool m_dealerWon;

	Deck* m_Deck;
};

