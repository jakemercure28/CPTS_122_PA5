#include "stack.h"
#include "cardData.h"
#include "PlayerQueue.h"

#include <iostream>
#include <stdlib.h>
#include <fstream>
using namespace std;

int main() {

	// card variables
	DynamicStack cardDeck;
	cardData current, current2;

	// player variables
	PlayerQueue p1, p2;
	
	int option, p1card, p2card, p1card2, p2card2, p1mode, p2mode, health;

	string name;
	
	// open card file
	fstream infile;
	infile.open("Yu_Gi_Oh_card_list.csv", ios::in);

	// parse each card from file into the card DynamicStack class
	string token;
	getline(infile, token, '\n');
	while (infile) {
		
		getline(infile, token, ',');
		current.name = token;
		getline(infile, token, ',');
		current.type = token;
		getline(infile, token, ',');
		current.level = stoi(token);
		getline(infile, token, ',');
		current.race = token;
		getline(infile, token, ',');
		current.attribute = token;
		getline(infile, token, ',');
		current.ATK = stoi(token);
		getline(infile, token, '\n');
		current.DEF = stoi(token);


		// push card to the stack of cards
		cardDeck.push(current);
	}

	infile.close();

	//pop garbage card off top of deck
	cardDeck.pop(current);

	// main gameplay loop starts
	do {
		cout << "Enter an option:\n";
		cout << "(1)\tCreate Players\n";
		cout << "(2)\tAdd Cards to Player\n";
		cout << "(3)\tBattle Other Player\n";
		cout << "(4)\tSwap Cards With Other Player\n";
		cout << "(5)\tQuit Game\n";
		cin >> option;

		switch (option) {

		case 1: // get player names
			cout << "Enter player 1 name:\n";
			cin >> name;
			p1.setName(name);
			cout << "Enter player 2 name:\n";
			cin >> name;
			p2.setName(name);
			break;
		case 2: // pop 5 cards from the deck to each player of the game
			
			cout << "Adding 5 cards to each players hand...\n";

			for (int i = 0; i < 5; i++){
				
				cardDeck.pop(current);
				p1.addCard(current);
				cardDeck.pop(current);
				p2.addCard(current);
			}
			break;

		case 3:// each player places one card in the play queue to battle

			// defense first
			system("cls");
			cout << "Player 1, Select a card to put in defense mode: \n";
			p1.viewHand();
			cin >> p1card;
			// defense card for player 1 put into card queue
			p1.enqueueDEF(p1.getCard(p1card));
			system("cls");
			
			cout << "Player 2, Select a card to put in defense mode: \n";
			p2.viewHand();
			cin >> p2card;
			p2.enqueueDEF(p2.getCard(p2card));
			system("cls");


			// offense mode
			cout << "Player 1, Select a card to put in offense mode: \n";
			p1.viewHand();
			cin >> p1card2;
			p1.enqueueATK(p1.getCard(p1card2));
			system("cls");

			cout << "Player 2, Select a card to put in offense mode: \n";
			p2.viewHand();
			cin >> p2card2;
			p2.enqueueATK(p2.getCard(p2card2));
			system("cls");

			// pop new card from deck to add to hand
			cardDeck.pop(current);
			p1.swapCard(current, p1card - 1);

			// pop new card from deck to add to hand
			cardDeck.pop(current);
			p1.swapCard(current, p1card2 - 1);

			// pop new card from deck to add to hand
			cardDeck.pop(current);
			p2.swapCard(current, p2card - 1);

			// pop new card from deck to add to hand
			cardDeck.pop(current);
			p2.swapCard(current, p2card2 - 1);
			
			// get mode for player 1
			do{
				cout << "Player 1, select the card ATK or DEF mode.\n(1)\tATK\n(2)\tDEF";
				cin >> p1mode;
				p1.setMode(p1mode);
			} while (p1mode != 1 && p1mode != 2);

			//get mode for player 2
			do{
				cout << "\nPlayer 2, select the card ATK or DEF mode.\n(1)\tATK\n(2)\tDEF";
				cin >> p2mode;
				p2.setMode(p2mode);
			} while (p2mode != 1 && p2mode != 2);

			// compare cards and amend each players health points
			cout << "Okay, lets battle and see who wins!\n";
			system("pause");

			
			// player 1 selects ATK and player 2 selects DEF
			if (p1.getMode() == 1 && p2.getMode() == 2){

				p1.dequeueATK(current);
				p2.dequeueDEF(current2);
				health = current.ATK - current2.DEF;

				if (health < 0) {
					cout << "Successfully defended, no points taken.\n";
					
				}
				else if (health > 0) {
					p2.subtractHealth(health);
				}
				cout << "Player 2 new health is: " << p2.getHealthPTS() << endl;
				system("pause");
				system("cls");
			}
			// player 2 selects ATK and player 1 selects DEF
			if (p1.getMode() == 2 && p2.getMode() == 1) {

				p2.dequeueATK(current);
				p1.dequeueDEF(current2);
				
				health = current.ATK - current2.DEF;

				if (health < 0) {
					cout << "Successfully defended, no points taken.\n";
				}
				else if (health > 0) {
					p1.subtractHealth(health);
				}

				cout << "Player 1 health is: " << p1.getHealthPTS() << endl;
				system("pause");
				system("cls");
			}
			// player 2 selects DEF and player 1 selects DEF
			if (p1.getMode() == 2 && p2.getMode() == 2) {

				p1.dequeueDEF(current);
				p2.dequeueDEF(current2);
				
				cout << "Both players selected defense, no life points taken\n";
				system("pause");
				system("cls");
			}

			// player 2 selects ATK and player 1 selects ATK
			if (p1.getMode() == 1 && p2.getMode() == 1) {

				p1.dequeueATK(current);
				p2.dequeueATK(current2);

				if (current.ATK > current2.ATK) {
					cout << "Both players selected Attack mode, player 1 has a higher ATK value, player 1 wins this battle.\n";
					health = current.ATK - current2.ATK;
					p2.subtractHealth(health);
					cout << "Player 1 new health is: " << p1.getHealthPTS() << endl;
					system("pause");
					system("cls");
				}
				else if (current2.ATK > current.ATK) {
					cout << "Both players selected Attack mode, player 2 has a higher ATK value, player 2 wins this battle.\n";
					health = current2.ATK - current.ATK;
					p1.subtractHealth(health);
					cout << "Player 2 new health is: " << p2.getHealthPTS() << endl;
					system("pause");
					system("cls");
				}
			}
				break;

			case 4:
				// trade cards with players
				cout << "Player 1, select a card to trade\n\n";
				p1.viewHand();
				cin >> p1card;
				
				system("cls");
				cout << "Player 2, select a card to trade\n\n";
				p2.viewHand();
				cin >> p2card;

				// temp card holder
				current = p1.getCard(p1card);

				p1.swapCard(p2.getCard(p2card), p1card-1);
				p2.swapCard(current, p2card-1);
				break;
		}

		

		// check for winner
		if (p1.getHealthPTS() <= 0) {
			cout << "Player 2 wins the game!\n";
			option = 5;
		}
		if (p2.getHealthPTS() <= 0) {
			cout << "Player 1 wins the game!\n";
			option = 5;
		}

		// while the game isnt quit and any player hasnt lost all health
	} while (option != 5);

	return 0;
}