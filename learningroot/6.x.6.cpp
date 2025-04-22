#include <iostream>
#include <array>
#include <string>
#include <ctime>

enum suits
{
	SUIT_CLUBS,
	SUIT_SPADES,
	SUIT_DIAMONDS,
	SUIT_HEARTS,
	SUIT_MAX
};

enum ranks
{
	RANK_2,
	RANK_3,
	RANK_4,
	RANK_5,
	RANK_6,
	RANK_7,
	RANK_8,
	RANK_9,
	RANK_10,
	RANK_J,
	RANK_Q,
	RANK_K,
	RANK_A,
	RANK_MAX,
};

struct card
{
	ranks rank;
	suits suit;
};

void printCard(card *a)
{
	switch (a->rank)
	{
	case 	RANK_2: 
		std::cout << "2";
		break;
	case	RANK_3:
		std::cout << "3";
		break;
	case	RANK_4: 
		std::cout << "4";
		break;
	case	RANK_5:
		std::cout << "5";
		break;
	case	RANK_6:
		std::cout << "6";
		break;
	case	RANK_7:
		std::cout << "7";
		break;
	case	RANK_8:
		std::cout << "8";
		break;
	case	RANK_9:
		std::cout << "9";
		break;
	case	RANK_10:
		std::cout << "10";
		break;
	case	RANK_J:
		std::cout << "J";
		break;
	case	RANK_Q:
		std::cout << "Q";
		break;
	case	RANK_K:
		std::cout << "K";
		break;
	case	RANK_A:
		std::cout << "A";
		break;
	default:
		std::cout << "unknown";
		break;
	};
	switch (a->suit)
	{
	case SUIT_CLUBS:
		std::cout << "C";
		break;
	case SUIT_SPADES:
		std::cout << "S";
		break;
	case SUIT_DIAMONDS:
		std::cout << "D";
		break;
	case SUIT_HEARTS:
		std::cout << "H";
		break;
	default:
		std::cout << "unknown";
		break;
	};
};

void swapCards(card &a, card &b)
{
	card c = a;
	a = b;
	b = c;
};

int getRandomNumber(int min, int max)
{
	static constexpr double fraction{ 1.0 / (RAND_MAX + 1.0) };
	return min + static_cast<int>((max - min + 1) * (std::rand() * fraction));
}

void shuffleDeck(std::array<card, 52> &deck)
{
	for (int index = 0; index < 52; ++index)
		swapCards(deck[index], deck[getRandomNumber(0, 51)]);
};

int getCardValue(card* a)
{
	switch (a->rank)
	{
	case 	RANK_2:
		return 2;
	case	RANK_3:
		return 3;
	case	RANK_4:
		return 4;
	case	RANK_5:
		return 5;
	case	RANK_6:
		return 6;
	case	RANK_7:
		return 7;
	case	RANK_8:
		return 8;
	case	RANK_9:
		return 9;
	case	RANK_10:
		return 10;
	case	RANK_J:
		return 10;
	case	RANK_Q:
		return 10;
	case	RANK_K:
		return 10;
	case	RANK_A:
		return 10;
	default:
		return 0;
	};
	return 0;
};

bool playBlackjack(std::array<card, 52> deck)
{
	card* cardptr = &deck[0];
	int playerScore = 0;
	int dealerScore = 0;
	std::cout << "You have been dealt a ";
	printCard(cardptr);
	std::cout << " and a ";
	playerScore += getCardValue(cardptr++);
	printCard(cardptr);
	std::cout << '\n';
	playerScore += getCardValue(cardptr++);
	std::cout << "The dealer has been dealt a ";
	printCard(cardptr);
	std::cout << '\n';
	dealerScore += getCardValue(cardptr++);
	std::cout << "Your score is: " << playerScore << '\n';
	std::cout << "The dealer's score is: " << dealerScore << '\n';
	while (true)
	{
		std::cout << "Enter 0 to hit or 1 to stand" << '\n';
		int turn;
		std::cin >> turn;
		if (turn == 0)
		{
			playerScore += getCardValue(cardptr++);
			std::cout << "Your score is: " << playerScore << '\n';
			
			if (playerScore > 21)
				return false;
		}
		else if (turn == 1)
		{
			std::cout << "Your final score is: " << playerScore << '\n';
			break;
		}
		else
			std::cout << "Invalid input";

	};
	while (dealerScore < 17)
	{
		dealerScore += getCardValue(cardptr++);
		std::cout << "Dealer score is now: " << dealerScore << '\n';
	};
	std::cout << "Dealer's final score is: " << dealerScore << '\n';
	if (playerScore > dealerScore)
		return true;
	else if (dealerScore > 21)
		return true;
	else
		return false;
};


int main()
{	
	std::array<card, 52> deck;
	using cardindextype = std::array<card, 52>::size_type;
	cardindextype cardindex = 0;
	for (int indexrank = 0; indexrank < 13; ++indexrank)
	{
		for (int indexsuit = 0; indexsuit < 4; ++indexsuit)
		{
			deck[cardindex].rank = static_cast<ranks>(indexrank);
			deck[cardindex].suit = static_cast<suits>(indexsuit);
			++cardindex;
		};
	}
	srand(static_cast<unsigned int>(time(0)));
	rand();


	int play = 1;
	while (play == 1)
	{
		shuffleDeck(deck);
		bool win = playBlackjack(deck);
		if (win == 0)
			std::cout << "You lost" << '\n';
		else std::cout << "You won" << '\n';
	std::cout << "Would you like to play again? Enter (1) if yes or (0) to exit: ";
	std::cin >> play;
	
	}
	return 0;
}
