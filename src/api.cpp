#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <vector>

#include "api.h"
#include "player.h"
#include "table.h"


API::API()
	: table()
	, players()
{}

API::~API() {}

int API::run()
{
	create();

	cout << "------------------------------------------" << endl;
	deal(INITIAL_HAND_SIZE);
	pickFirstTurn();

	while(!isBlocked())
	{
		if(playTurn())
		{
			Player* player = &players[currPlayerIndex];
			cout << "------------------------------------------" << endl;
			cout << player->getName() << " has won!" << endl;
			printRanking();

			return EXIT_SUCCESS;
		} else {
			++turnCount;
			nextPlayer();
		}
	}

	cout << "------------------------------------------" << endl;
	cout << "All players are blocked. Game over!" << endl;
	printRanking();

	return EXIT_SUCCESS;
}

void API::create()
{
	Random::create();
	table.create();
	createPlayers(PLAYER_COUNT);
}

void API::createPlayers(int playerCount)
{
	for(int playerIndex = 0; playerIndex < playerCount; ++playerIndex)
	{
		stringstream playerName;
		playerName << "Player" << (playerIndex+1);
		createPlayer(playerName.str());
	}
}

void API::createPlayer(string playerName)
{
	Player player = Player(playerName);
	players.push_back(player);
}


void API::pickFirstTurn()
{
	currPlayerIndex = randomInt(0, players.size()-1);
	Player* currPlayer = getCurrentPlayer();
	cout << currPlayer->getName() << " goes first." << endl << endl;
}


void API::deal(int amount)
{
	for(size_t i = 0; i < players.size(); ++i)
	{
		Player* player = &players[i];
		player->draw(&table, amount);
		
		cout << player->getName() << " draws 10 dominoes." << endl;
	}
}


bool API::playTurn()
{
	
	Player* player = getCurrentPlayer();

	cout << "------------------------------------------" << endl;
	cout << "Turn: " << turnCount << endl;
	cout << "Player: " << player->getName() << endl;

	printPlayersHands();

	cout << "Boneyard: ";
	table.printBoneyard();

	cout << "Chain: ";
	table.printChain();

	cout << endl << "Moves:" << endl;

	player->playTurn(&table);

	cout << endl;

	// If player has an empty hand, the game is over!
	if(player->handEmpty()) return true;

	return false;
}


Player* API::nextPlayer()
{
	currPlayerIndex = (currPlayerIndex+1) % players.size();
	Player* currentPlayer = getCurrentPlayer();
	return currentPlayer;
}


Player* API::getCurrentPlayer()
{
	return &players[currPlayerIndex];
}


bool API::isBlocked()
{
	bool blocked = true;
	for(size_t i = 0; i < players.size(); ++i)
	{
		blocked &= players[i].isBlocked();
	}

	return blocked;
}


void API::printPlayersHands()
{
	for(size_t i = 0; i < players.size(); ++i)
	{
		players[i].printHand();
	}
}


bool comparePlayerHands(Player* a, Player* b)
{
	return a->handSize() < b->handSize();
}


void API::printRanking()
{
	// Make list of pointers to players
	vector<Player*> rankedPlayers;
	rankedPlayers.reserve(players.size());
	for (unsigned playerIndex = 0; playerIndex < players.size(); ++playerIndex)
		rankedPlayers.push_back(&players[playerIndex]);

	// Sort the ranked list by handsize
	sort(rankedPlayers.begin(), rankedPlayers.end(), comparePlayerHands);

	cout << "------------------------------------------" << endl;
	cout << "Rankings:" << endl;
	for (unsigned playerIndex = 0; playerIndex < rankedPlayers.size(); ++playerIndex)
	{
		Player* player = rankedPlayers[playerIndex];
		int rank = playerIndex + 1;

		cout << rank << ". " << player->getName();
		if(!player->handEmpty())
		{
			cout << " (" << player->handSize() << " pieces left): " << player->showHand();
		} else
		{
			cout << " (winner!)";
		}
		cout << endl;
	}

	cout << "Total Turns: " << turnCount << endl;
	cout << endl << "Final Boneyard: ";
	table.printBoneyard();

	cout << "Final Chain: ";
	table.printChain();
}