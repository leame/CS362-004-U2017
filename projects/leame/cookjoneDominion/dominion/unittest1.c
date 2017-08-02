/*
 * unittest1.c
 * unit test for buyCard function
 */

/*
 * Include the following lines in your makefile:
 *
 * unittest1: unittest1.c dominion.o rngs.o
 *      gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
 */

/*
* Business rules:
* 1. Player gains 1 card to discard pile.
* 2. Player loses the cost of the card.
* 3. Player loses 1 buy.
* 4. supplyCount loses 1 card.
* 5. Last card in discard pile is the card bought.
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNCTION "buyCard()"
#define SUPPLYPOS 0

int numTest = 0;
int passedTest = 0;

int assertTrue(int testVal, char* testName)
{
	numTest++;
	
	if (testVal)
	{
		printf("PASS: %s\n", testName);
		passedTest++;
	}
	else
	{
		printf("FAIL: %s\n", testName);
	}
	
	return 0;
}

int main() {
	int seed = 1000;
	int numPlayers = 2;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing %s ----------------\n", TESTFUNCTION);
	
	// copy the game state to a test case	
	memcpy(&testG, &G, sizeof(struct gameState));
	
	if (buyCard(SUPPLYPOS, &testG) == -1)
	{
		printf("Could not buy a card.");
		return -1;
	}
	
	else
	{
		//1. Player gains 1 card to discard pile.
		assertTrue(testG.discardCount[testG.whoseTurn] == G.discardCount[G.whoseTurn] + 1, "Test 1: +1 card to discard pile");
		printf("Expected %d cards. Got %d cards.\n", G.discardCount[G.whoseTurn] + 1, testG.discardCount[testG.whoseTurn]);
		
		//2. Player loses the cost of the card.
		assertTrue(testG.coins == G.coins - getCost(SUPPLYPOS), "Test 2: Subtract coins");
		printf("Expected %d coins. Got %d coins.\n", G.coins - getCost(SUPPLYPOS), testG.coins);
		
		//3. Player loses 1 buy.
		assertTrue(testG.numBuys == G.numBuys - 1, "Test 3: Substract buys");
		printf("Expected %d buys. Got %d buys.\n", G.numBuys - 1, testG.numBuys);
		
		//4. supplyCount loses 1 card.
		assertTrue(testG.supplyCount[SUPPLYPOS] == G.supplyCount[SUPPLYPOS] - 1, "Test 4: Subtract supplyCount");
		printf("Expected %d supplyCount. Got %d supplyCount.\n", G.supplyCount[SUPPLYPOS] - 1, testG.supplyCount[SUPPLYPOS]);
		
		//5. Last card in discard pile is the card bought.
		assertTrue(testG.discard[testG.whoseTurn][testG.discardCount[testG.whoseTurn]] == SUPPLYPOS, "Test 5: Check last discarded card.");
		printf("Tried to buy enum %d. Bought enum %d.\n", SUPPLYPOS, testG.discard[testG.whoseTurn][testG.discardCount[testG.whoseTurn]]);
	
		printf("-----------------%d/%d TESTS PASSED FOR %s----------------\n", passedTest, numTest, TESTFUNCTION);
		return 0;
	}
}