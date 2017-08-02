/*
 * unittest2.c
 * unit test for updateCoins function
 */

/*
 * Include the following lines in your makefile:
 *
 * unittest2: unittest1.c dominion.o rngs.o
 *      gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
 */

/*
* Business rules:
* 1. Gather the value of the treasure cards in the player's hand, plus the bonus for the round.
* 2. Copper is worth 1, silver is worth 2, gold is worth 3.
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNCTION "updateCoins()"

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
	//enum copper = 4, silver = 5, gold = 6.
	
	//gain 1 copper
	// copy the game state to a test case	
	memcpy(&testG, &G, sizeof(struct gameState));
	gainCard(4, &testG, 2, testG.whoseTurn);
	updateCoins(testG.whoseTurn, &testG, 0);
	assertTrue(testG.coins == G.coins + 1, "Test 1: Copper value");
	printf("Expected %d coins. Got %d coins.\n", G.coins + 1, testG.coins);

	//gain 1 silver
	// copy the game state to a test case	
	memcpy(&testG, &G, sizeof(struct gameState));
	gainCard(5, &testG, 2, testG.whoseTurn);
	updateCoins(testG.whoseTurn, &testG, 0);
	assertTrue(testG.coins == G.coins + 2, "Test 2: Silver value");
	printf("Expected %d coins. Got %d coins.\n", G.coins + 2, testG.coins);
	
	//gain 1 gold
	// copy the game state to a test case	
	memcpy(&testG, &G, sizeof(struct gameState));
	gainCard(6, &testG, 2, testG.whoseTurn);
	updateCoins(testG.whoseTurn, &testG, 0);
	assertTrue(testG.coins == G.coins + 3, "Test 3: Gold value");
	printf("Expected %d coins. Got %d coins.\n", G.coins + 3, testG.coins);
	
	//gain 1 bonus coin
	// copy the game state to a test case	
	memcpy(&testG, &G, sizeof(struct gameState));
	updateCoins(testG.whoseTurn, &testG, 1);
	assertTrue(testG.coins == G.coins + 1, "Test 4: +1 bonus coin");
	printf("Expected %d coins. Got %d coins.\n", G.coins + 1, testG.coins);
	
	//gain 1 copper, silver, gold, and bonus
	// copy the game state to a test case	
	memcpy(&testG, &G, sizeof(struct gameState));
	gainCard(4, &testG, 2, testG.whoseTurn);
	gainCard(5, &testG, 2, testG.whoseTurn);
	gainCard(6, &testG, 2, testG.whoseTurn);
	updateCoins(testG.whoseTurn, &testG, 1);
	assertTrue(testG.coins == G.coins + 7, "Test 5: +1 copper, silver, gold, bonus");
	printf("Expected %d coins. Got %d coins.\n", G.coins + 7, testG.coins);	
	
	printf("-----------------%d/%d TESTS PASSED FOR %s----------------\n", passedTest, numTest, TESTFUNCTION);	
	
}