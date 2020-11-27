#include <string>
#include "stack.h"

class PlayerQueue{

private:

	string name;
	cardData hand[5];
	int healthPts;
	int mode;
	int cardCount; // counts cards in hand

	// queue operations
	struct QueueNode
	{
		cardData data;      // value in node
		QueueNode* next; // Pointer to the next node
	};

	QueueNode* frontDEF;  // The front of the queue
	QueueNode* frontATK;
	QueueNode* rearDEF;   // The rear of the queue
	QueueNode* rearATK;
	int numATKItems;      // Number of items in the queue
	int numDEFItems;

public:

	// Constructor
	PlayerQueue();
	// Destructor
	~PlayerQueue();

	// player operations
	// setter
	void addCard(cardData input);
	void swapCard(cardData input, int position);
	void setName(string input) {
		name = input;
	}
	void setMode(int input) {
		mode = input;
	}
	void subtractHealth(int input) {
		healthPts -= input;
	}
	// getter
	int getMode() {
		return mode;
	}
	string getName() {
		return name;
	}
	int getHealthPTS() {
		return healthPts;
	}
	cardData getCard(int input) {

		return hand[input-1];
	}
	void viewHand();
	

	// Queue operations
	void enqueueDEF(cardData current);
	void enqueueATK(cardData current);
	void dequeueDEF(cardData& curent);
	void dequeueATK(cardData& current);
	bool isDEFEmpty() const;
	bool isATKEmpty() const;
	void clear();
};