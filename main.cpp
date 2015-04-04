#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <ctime>
#include "class.h"

using namespace std;

void inputCards( card* deck );
void shuffle( card* deck, card* shuffledDeck );
void inputPlayers( player* players, int numOfPlayers );
void deal( player* players, card* shuffledDeck, card* discard, card* stock, int discardNumber, int stockNumber, int numOfPlayers );

int main()
{
	card* deck = new card[52];
	card* shuffledDeck = new card [52];
	card* discard = new card[40];
	card* stock = new card[52];

	int discardNumber = 0;
	int stockNumber = 0;

	//Gets number of players from user
	int numOfPlayers;
	cout << "Please enter number of players (2-8): ";
	cin >> numOfPlayers;
	player* players = new player[numOfPlayers];

	int menuInput = 0;

	do
	{
		cout << "Main Menu\n";
		cout << "1. Read in deck from file" << endl;
		cout << "2. Shuffle deck" << endl;
		cout << "3. Print unshuffled deck" << endl;
		cout << "4. Print shuffled deck" << endl; 
		cout << "5. Read in list of players" << endl;
		cout << "6. Print player information" << endl;
		cout << "7. Deal first round of cards" << endl;
		cout << "8. Print current stock pile" << endl;
		cout << "9. Print current discard pile" << endl;
		cout << "0. Exit" << endl << endl;

		cout << "What do you want to do?  ";
		cin >> menuInput;

		switch( menuInput )
		{
			case 1:

				inputCards( deck );
				break;

			case 2:

				shuffle( deck, shuffledDeck );
				break;

			case 3:

				for(int i = 0; i < 52; i++)
				{
					cout << "Card " << ( i + 1 ) << ": " << deck[i] << endl;
				}
				break;

			case 4:

				for( int j = 0; j < 52; j++ )
				{
					cout << "Card " << ( j + 1 ) << ": " << shuffledDeck[j] << endl;
				}
				break;

			case 5:

				inputPlayers( players, numOfPlayers );
				break;

			case 6:

				for(int k = 0; k < numOfPlayers; k++)
				{
					cout << "Player " << ( k + 1 ) << ": " << players[k] << endl;
				}
				break;

			case 7:

				deal( players, shuffledDeck, discard, stock, discardNumber, stockNumber, numOfPlayers );
				break;

			case 8:

				for(int x = 0; x < stockNumber; x++)
				{
					cout << "Card " << ( x + 1 ) << ": " << stock[x] << endl;
				}
				break;

			case 9:

				for(int y = 0; y < discardNumber; y++)
				{
					cout << "Card " << ( y + 1 ) << ": " << discard[y] << endl;
				}
				break;

			case 0:

				cout << "Exiting" << endl;
				break;

		}

	}while ( menuInput != 0 );

return 0;
}

void inputCards( card* deck )
{
	char* fileName = new char [20];

	cout << "Please enter file name: ";
	cin >> fileName;

	ifstream fin;
	fin.open(fileName);
	for(int i = 0; i < 52; i++)
	{
		fin >> deck[i];
	}
	fin.close();
}

void shuffle( card* deck, card* shuffledDeck )
{
	int random;

	srand(time(NULL));
	int i = 0;

	while(i < 52)
	{
		random = rand() % 52;

		if(deck[random].getLocation() != "shuffled")
		{
			shuffledDeck[i] = deck[random];
			shuffledDeck[i].setLocation("shuffled");
			deck[random].setLocation("shuffled");
			i++;
		}
	}

	for(int j = 0; j < 52; j++)
	{
		deck[j].setLocation("unshuffled");
	}
}

void inputPlayers( player* players, int numOfPlayers )
{
	char* fileName = new char [20];

	cout << "Please enter file name: ";
	cin >> fileName;

	ifstream fin;
	fin.open(fileName);

	for(int i = 0; i < numOfPlayers; i++)
	{
		fin >> players[i];
	}
	
	fin.close();
}

void deal( player* players, card* shuffledDeck, card* discard, card* stock, int discardNumber, int stockNumber, int numOfPlayers )
{
	int playerNumber = 0;
	int handNumber = 0;
	int deckNumber = 0;

	for(int i = 0; i < 5; i++)
	{
		while(playerNumber < numOfPlayers)
		{
			players[playerNumber].setHand( shuffledDeck[deckNumber], handNumber );
			deckNumber++;
			playerNumber++;
		}

		shuffledDeck[deckNumber].setLocation("discard");
		discard[discardNumber] = shuffledDeck[deckNumber];

		discardNumber++;
		deckNumber++;
		handNumber++;

		playerNumber = 0;
	}
	
	while(deckNumber < 52)
	{
		shuffledDeck[deckNumber].setLocation("stock");
		stock[stockNumber] = shuffledDeck[deckNumber];

		stockNumber++;
		deckNumber++;
	}
}



