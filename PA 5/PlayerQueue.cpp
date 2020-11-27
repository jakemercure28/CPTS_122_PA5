#include "PlayerQueue.h"

PlayerQueue::PlayerQueue()
{
	name = "Chad";
	cardCount = 0;
	healthPts = 8000;
	mode = 0;

	frontATK = nullptr;
	frontDEF = nullptr;
	rearATK = nullptr;
	rearDEF = nullptr;
	numATKItems = 0;
	numDEFItems = 0;

}

PlayerQueue::~PlayerQueue()
{
	cardData value;   // Dummy variable for dequeue

	while (!isATKEmpty()) {
		dequeueATK(value);
	}
	while (!isDEFEmpty()) {
		dequeueDEF(value);
	}
}

void PlayerQueue::addCard(cardData input) {

	if (cardCount < 5) {
		hand[cardCount] = input;
		cardCount++;
	}
	else
		cout << "\nMax cards in hand!\n";
}

void PlayerQueue::swapCard(cardData input, int position) {

	hand[position] = input;
}

void PlayerQueue::viewHand() {

	cout << "Name\t\t\tType\t\t\tLevel\tRace\tAttribute\tATK\tDEF\n";
	for (int i = 0; i < 5; i++) {
		cout << "(" << i + 1 << ")";
		cout << hand[i].name << "\t";
		cout << hand[i].type << "\t\t";
		cout << hand[i].level << "\t";
		cout << hand[i].race << "\t";
		cout << hand[i].attribute << "\t\t";
		cout << hand[i].ATK << "\t";
		cout << hand[i].DEF << endl << endl;
	}
}

void PlayerQueue::enqueueDEF(cardData current)
{
	QueueNode* newNode = nullptr;

	// Create a new node and store num there.
	newNode = new QueueNode;
	newNode->data = current;
	newNode->next = nullptr;

	// Adjust front and rear as necessary.
	if (isDEFEmpty())
	{
		frontDEF = newNode;
		rearDEF = newNode;
	}
	else
	{
		rearDEF->next = newNode;
		rearDEF = newNode;
	}

	// Update numItems.
	numDEFItems++;
}

void PlayerQueue::enqueueATK(cardData current)
{
	QueueNode* newNode = nullptr;

	// Create a new node and store num there.
	newNode = new QueueNode;
	newNode->data = current;
	newNode->next = nullptr;

	// Adjust front and rear as necessary.
	if (isATKEmpty())
	{
		frontATK = newNode;
		rearATK = newNode;
	}
	else
	{
		rearATK->next = newNode;
		rearATK = newNode;
	}

	// Update numItems.
	numATKItems++;
}

void PlayerQueue::dequeueDEF(cardData& current)
{
	QueueNode* temp = nullptr;

	if (isDEFEmpty())
	{
		cout << "The queue is empty.\n";
	}
	else
	{
		// Save the front node value in num.
		current = frontDEF->data;

		// Remove the front node and delete it.
		temp = frontDEF;
		frontDEF = frontDEF->next;
		delete temp;

		// Update numItems.
		numDEFItems--;
	}
}

void PlayerQueue::dequeueATK(cardData& current)
{
	QueueNode* temp = nullptr;

	if (isATKEmpty())
	{
		cout << "The queue is empty.\n";
	}
	else
	{
		// Save the front node value in num.
		current = frontATK->data;

		// Remove the front node and delete it.
		temp = frontATK;
		frontATK = frontATK->next;
		delete temp;

		// Update numItems.
		numATKItems--;
	}
}

bool PlayerQueue::isATKEmpty() const
{
	bool status;

	if (numATKItems > 0)
		status = false;
	else
		status = true;
	return status;
}

bool PlayerQueue::isDEFEmpty() const
{
	bool status;

	if (numDEFItems > 0)
		status = false;
	else
		status = true;
	return status;
}

void PlayerQueue::clear()
{
	cardData value;   // Dummy variable for dequeue

	while (!isATKEmpty()) {
		dequeueATK(value);
		
	}

	while (!isDEFEmpty()) {
		dequeueDEF(value);
	}
}