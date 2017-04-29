#include "Deck.h"

Deck::Deck()
{
	InitializeDeck();
}

void Deck::InitializeDeck()
{
	// Iterate a total of 13 x 4 (52) times and push back a card per iteration.
	for (int i = 0; i < MAX_VALUE; ++i)
	{
		for (int j = 0; j < MAX_SUITS; ++j)
		{
			Card card(j, i);
			m_Cards.push_back(card);
		}
	}

	// Now shuffle the deck.
	ShuffleDeck();
}

void Deck::ListDeckContents()
{
	for (auto const &cards : m_Cards)
	{
		if (m_Cards.empty())
			return;

		std::cout << cards.GetNameFromValue(cards.GetValue()) << " of " << cards.GetNameFromSuit(cards.GetSuit()) << std::endl;
	}
}

void Deck::ShuffleDeck()
{
	std::random_shuffle(m_Cards.begin(), m_Cards.end());
}

Card Deck::DrawCard(bool identifyCard, bool dealer)
{
	// Randomly select a card from the shuffled deck.
	auto card = select_randomly(m_Cards.begin(), m_Cards.end());

	// Only identify the card if told.
	if (identifyCard)
		card->PrintCardDetails(dealer);

	// Return a pointer to the card.
	return *card;
}

std::string Card::GetNameFromValue(int value) const
{
	switch (value)
	{
		case 0:
			return "Ace";
			break;
		case 10:
			return "Jack";
			break;
		case 11: 
			return "Queen";
			break;
		case 12:
			return "King";
			break;
		default:
			return std::to_string(value + 1);
			break;
	}

	return std::string();
}

std::string Card::GetNameFromSuit(int suit) const
{
	switch (suit)
	{
		case 0:
			return "Clubs";
			break;
		case 1:
			return "Diamonds";
			break;
		case 2:
			return "Hearts";
			break;
		case 3:
			return "Spades";
			break;
		default:
			return "Error";
			break;
	}

	return std::string();
}

void Card::PrintCardDetails(bool dealer)
{
	if (dealer)
	{
		Color(14);
		std::cout << "\nDEALER: " << this->GetNameFromValue(GetValue()) << " of " << this->GetNameFromSuit(GetSuit()) << std::endl;
		Color();
		return;
	}

	std::cout << this->GetNameFromValue(GetValue()) << " of " << this->GetNameFromSuit(GetSuit()) << std::endl;
}